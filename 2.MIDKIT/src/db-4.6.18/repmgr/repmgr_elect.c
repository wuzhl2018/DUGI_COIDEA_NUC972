/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2005,2007 Oracle.  All rights reserved.
 *
 * $Id: repmgr_elect.c,v 1.31 2007/05/17 15:15:50 bostic Exp $
 */

#include "db_config.h"

#define	__INCLUDE_NETWORKING	1
#include "db_int.h"

static int __repmgr_is_ready __P((DB_ENV *));
static int __repmgr_elect_main __P((DB_ENV *));
static void *__repmgr_elect_thread __P((void *));
static int start_election_thread __P((DB_ENV *));

/*
 * Starts the election thread, or wakes up an existing one, starting off with
 * the specified operation (an election, or a call to rep_start(CLIENT), or
 * nothing).  Avoid multiple concurrent elections.
 *
 * PUBLIC: int __repmgr_init_election __P((DB_ENV *, int));
 *
 * !!!
 * Caller must hold mutex.
 */
int
__repmgr_init_election(dbenv, initial_operation)
	DB_ENV *dbenv;
	int initial_operation;
{
	DB_REP *db_rep;
	int ret;

	db_rep = dbenv->rep_handle;
	if (db_rep->finished) {
		RPRINT(dbenv, (dbenv,
		    "ignoring elect thread request %d; repmgr is finished",
		    initial_operation));
		return (0);
	}

	db_rep->operation_needed = initial_operation;
	if (db_rep->elect_thread == NULL)
		ret = start_election_thread(dbenv);
	else if (db_rep->elect_thread->finished) {
		RPRINT(dbenv, (dbenv, "join dead elect thread"));
		if ((ret = __repmgr_thread_join(db_rep->elect_thread)) != 0)
			return (ret);
		__os_free(dbenv, db_rep->elect_thread);
		db_rep->elect_thread = NULL;
		ret = start_election_thread(dbenv);
	} else {
		RPRINT(dbenv, (dbenv, "reusing existing elect thread"));
		if ((ret = __repmgr_signal(&db_rep->check_election)) != 0)
			__db_err(dbenv, ret, "can't signal election thread");
	}
	return (ret);
}

/*
 * !!!
 * Caller holds mutex.
 */
static int
start_election_thread(dbenv)
	DB_ENV *dbenv;
{
	DB_REP *db_rep;
	REPMGR_RUNNABLE *elector;
	int ret;

	db_rep = dbenv->rep_handle;

	if ((ret = __os_malloc(dbenv, sizeof(REPMGR_RUNNABLE), &elector))
	    != 0)
		return (ret);
	elector->dbenv = dbenv;
	elector->run = __repmgr_elect_thread;

	if ((ret = __repmgr_thread_start(dbenv, elector)) == 0)
		db_rep->elect_thread = elector;
	else
		__os_free(dbenv, elector);

	return (ret);
}

static void *
__repmgr_elect_thread(args)
	void *args;
{
	DB_ENV *dbenv = args;
	int ret;

	RPRINT(dbenv, (dbenv, "starting election thread"));

	if ((ret = __repmgr_elect_main(dbenv)) != 0) {
		__db_err(dbenv, ret, "election thread failed");
		__repmgr_thread_failure(dbenv, ret);
	}

	RPRINT(dbenv, (dbenv, "election thread is exiting"));
	return (NULL);
}

static int
__repmgr_elect_main(dbenv)
	DB_ENV *dbenv;
{
	DB_REP *db_rep;
	DBT my_addr;
#ifdef DB_WIN32
	DWORD duration;
#else
	struct timespec deadline;
#endif
	u_int nsites, nvotes;
	int done, failure_recovery, last_op;
	int need_success, ret, succeeded, to_do;

	COMPQUIET(need_success, TRUE);

	db_rep = dbenv->rep_handle;
	last_op = 0;
	failure_recovery = succeeded = FALSE;

	/*
	 * db_rep->operation_needed is the mechanism by which the outside world
	 * (running in a different thread) tells us what it wants us to do.  It
	 * is obviously relevant when we're just starting up.  But it can also
	 * be set if a subsequent request for us to do something occurs while
	 * we're still looping.
	 *
	 * ELECT_FAILURE_ELECTION asks us to start by doing an election, but to
	 * do so in failure recovery mode.  This failure recovery mode may
	 * persist through several loop iterations: as long as it takes us to
	 * succeed in finding a master, or until we get asked to perform a new
	 * request.  Thus the time for mapping ELECT_FAILURE_ELECTION to the
	 * internal ELECT_ELECTION, as well as the setting of the failure
	 * recovery flag, is at the point we receive the new request from
	 * operation_needed (either here, or within the loop below).
	 */
	LOCK_MUTEX(db_rep->mutex);
	if (db_rep->finished) {
		db_rep->elect_thread->finished = TRUE;
		UNLOCK_MUTEX(db_rep->mutex);
		return (0);
	}
	to_do = db_rep->operation_needed;
	db_rep->operation_needed = 0;
	UNLOCK_MUTEX(db_rep->mutex);

	/*
	 * The way we are invoked determines the criterion for completion (which
	 * is represented as "need_success"): if we've been asked to do an
	 * election, we're only "done" when an election has actually succeeded.
	 * If we're just here trying to find the master initially, then merely
	 * getting a valid master_eid suffices.
	 */
	switch (to_do) {
	case ELECT_FAILURE_ELECTION:
		failure_recovery = TRUE;
		to_do = ELECT_ELECTION;
		/* FALLTHROUGH */
	case ELECT_ELECTION:
		need_success = TRUE;
		break;
	case ELECT_SEEK_MASTER:
		to_do = 0;	/* Caller has already called rep_start. */
		/* FALLTHROUGH */
	case ELECT_REPSTART:
		need_success = FALSE;
		break;
	default:
		DB_ASSERT(dbenv, FALSE);
	}
	/* Here, need_success has been initialized. */

	for (;;) {
		RPRINT(dbenv, (dbenv, "elect thread to do: %d", to_do));
		switch (to_do) {
		case ELECT_ELECTION:
			nsites = __repmgr_get_nsites(db_rep);

			nvotes = ELECTION_MAJORITY(nsites);

			/*
			 * If we're doing an election because we noticed that
			 * the master failed, it's reasonable to expect that the
			 * master won't participate.  By not waiting for its
			 * vote, we can probably complete the election faster.
			 * But note that we shouldn't allow this to affect
			 * nvotes calculation.
			 */
			if (failure_recovery) {
				nsites--;

				if (nsites == 1) {
					/*
					 * We've just lost the only other site
					 * in the group, so there's no point in
					 * holding an election.
					 */
					if ((ret = __repmgr_become_master(
					    dbenv)) != 0)
						return (ret);
					break;
				}
			}

			switch (ret = __rep_elect(dbenv,
			    (int)nsites, (int)nvotes, 0)) {
			case DB_REP_UNAVAIL:
				break;

			case 0:
				succeeded = TRUE;
				if (db_rep->takeover_pending) {
					db_rep->takeover_pending = FALSE;
					if ((ret =
					    __repmgr_become_master(dbenv)) != 0)
						return (ret);
				}
				break;

			default:
				__db_err(
				    dbenv, ret, "unexpected election failure");
				return (ret);
			}
			last_op = ELECT_ELECTION;
			break;
		case ELECT_REPSTART:
			if ((ret =
			    __repmgr_prepare_my_addr(dbenv, &my_addr)) != 0)
				return (ret);
			ret = __rep_start(dbenv, &my_addr, DB_REP_CLIENT);
			__os_free(dbenv, my_addr.data);
			if (ret != 0) {
				__db_err(dbenv, ret, "rep_start");
				return (ret);
			}
			last_op = ELECT_REPSTART;
			break;
		case 0:
			/*
			 * Nothing to do: this can happen the first time
			 * through, on initialization.
			 */
			last_op = 0;
			break;
		default:
			DB_ASSERT(dbenv, FALSE);
		}

		LOCK_MUTEX(db_rep->mutex);
		while (!succeeded && !__repmgr_is_ready(dbenv)) {
#ifdef DB_WIN32
			duration = db_rep->election_retry_wait / US_PER_MS;
			ret = SignalObjectAndWait(db_rep->mutex,
			    db_rep->check_election, duration, FALSE);
			LOCK_MUTEX(db_rep->mutex);
			if (ret == WAIT_TIMEOUT)
				break;
			DB_ASSERT(dbenv, ret == WAIT_OBJECT_0);
#else
			__repmgr_compute_wait_deadline(dbenv, &deadline,
			    db_rep->election_retry_wait);
			if ((ret = pthread_cond_timedwait(
			    &db_rep->check_election, &db_rep->mutex, &deadline))
			    == ETIMEDOUT)
				break;
			DB_ASSERT(dbenv, ret == 0);
#endif
		}

		/*
		 * Ways we can get here: election succeeded, sleep duration
		 * expired, "operation needed", or thread shut-down command.
		 *
		 * If we're not yet done, figure out what to do next (which may
		 * be trivially easy if we've been told explicitly, via the
		 * "operation needed" flag).  We must first check if we've been
		 * told to do a specific operation, because that could make our
		 * completion criterion more stringent.  Note that we never
		 * lessen our completion criterion (i.e., unlike the initial
		 * case, we may leave need_success untouched here).
		 */
		done = FALSE;
		if ((to_do = db_rep->operation_needed) != 0) {
			db_rep->operation_needed = 0;
			switch (to_do) {
			case ELECT_FAILURE_ELECTION:
				failure_recovery = TRUE;
				to_do = ELECT_ELECTION;
				/* FALLTHROUGH */
			case ELECT_ELECTION:
				need_success = TRUE;
				break;
			case ELECT_SEEK_MASTER:
				to_do = 0;
				break;
			default:
				break;
			}
		} else if ((done = (succeeded ||
		    (!need_success && IS_VALID_EID(db_rep->master_eid)) ||
		    db_rep->finished)))
			db_rep->elect_thread->finished = TRUE;
		else {
			if (last_op == ELECT_ELECTION)
				to_do = ELECT_REPSTART;
			else {
				/*
				 * Generally, if what we previously did is a
				 * rep_start (or nothing, which really just
				 * means another thread did the rep_start before
				 * turning us on), then we next do an election.
				 * However, with the REP_CLIENT init policy we
				 * never do an initial election.
				 */
				to_do = ELECT_ELECTION;
				if (db_rep->init_policy == DB_REP_CLIENT &&
				    !db_rep->found_master)
					to_do = ELECT_REPSTART;
			}
		}

		UNLOCK_MUTEX(db_rep->mutex);
		if (done)
			return (0);
	}
}

/*
 * Tests whether another thread has signalled for our attention.
 */
static int
__repmgr_is_ready(dbenv)
	DB_ENV *dbenv;
{
	DB_REP *db_rep;

	db_rep = dbenv->rep_handle;

	RPRINT(dbenv, (dbenv,
	    "repmgr elect: opcode %d, finished %d, master %d",
	    db_rep->operation_needed, db_rep->finished, db_rep->master_eid));

	return (db_rep->operation_needed || db_rep->finished);
}

/*
 * PUBLIC: int __repmgr_become_master __P((DB_ENV *));
 */
int
__repmgr_become_master(dbenv)
	DB_ENV *dbenv;
{
	DB_REP *db_rep;
	DBT my_addr;
	int ret;

	db_rep = dbenv->rep_handle;
	db_rep->master_eid = SELF_EID;
	db_rep->found_master = TRUE;

	/*
	 * At the moment, it's useless to pass my address to rep_start here,
	 * because rep_start ignores it in the case of MASTER.  So we could
	 * avoid the trouble of allocating and freeing this memory.  But might
	 * this conceivably change in the future?
	 */
	if ((ret = __repmgr_prepare_my_addr(dbenv, &my_addr)) != 0)
		return (ret);
	ret = __rep_start(dbenv, &my_addr, DB_REP_MASTER);
	__os_free(dbenv, my_addr.data);
	__repmgr_stash_generation(dbenv);

	return (ret);
}
