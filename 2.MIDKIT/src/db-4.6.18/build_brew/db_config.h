/* DO NOT EDIT: automatically built by dist/s_brew. */
/* Define to 1 if you want to build a version for running the test suite. */
/* #undef CONFIG_TEST */

/* We use DB_WIN32 much as one would use _WIN32 -- to specify that we're using
   an operating system environment that supports Win32 calls and semantics. We
   don't use _WIN32 because Cygwin/GCC also defines _WIN32, even though
   Cygwin/GCC closely emulates the Unix environment. */
/* #undef DB_WIN32 */

/* Define to 1 if you want a debugging version. */
#if defined(_DEBUG)
#if !defined(DEBUG)
#define DEBUG 1
#endif
#endif

/* Define to 1 if you want a version that logs read operations. */
/* #undef DEBUG_ROP */

/* Define to 1 if you want a version that logs write operations. */
/* #undef DEBUG_WOP */

/* Define to 1 if you want a version with run-time diagnostic checking. */
/* #undef DIAGNOSTIC */

/* Define to 1 if 64-bit types are available. */
/* #undef HAVE_64BIT_TYPES */

/* Define to 1 if you have the `abort' function. */
/* #undef HAVE_ABORT */

/* Define to 1 if you have the `atoi' function. */
#define HAVE_ATOI 1

/* Define to 1 if you have the `atol' function. */
/* #undef HAVE_ATOL */

/* Define to 1 if building BREW. */
#define HAVE_BREW 1

/* Define to 1 if building on BREW (SDK2). */
#define HAVE_BREW_SDK2 1

/* Define to 1 if you have the `clock_gettime' function. */
/* #undef HAVE_CLOCK_GETTIME */

/* Define to 1 if Berkeley DB release includes strong cryptography. */
/* #undef HAVE_CRYPTO */

/* Define to 1 if you have the `ctime_r' function. */
/* #undef HAVE_CTIME_R  */

/* Define to 1 if ctime_r takes a buffer length as a third argument. */
/* #undef HAVE_CTIME_R_3ARG */

/* Define to 1 if you have the `directio' function. */
/* #undef HAVE_DIRECTIO */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_DIRENT_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to 1 if you have EXIT_SUCCESS/EXIT_FAILURE #defines. */
#define HAVE_EXIT_SUCCESS 1

/* Define to 1 if you have the `fchmod' function. */
/* #undef HAVE_FCHMOD */

/* Define to 1 if you have the `fclose' function. */
/* #undef HAVE_FCLOSE */

/* Define to 1 if you have the `fcntl' function. */
/* #undef HAVE_FCNTL */

/* Define to 1 if fcntl/F_SETFD denies child access to file descriptors. */
/* #undef HAVE_FCNTL_F_SETFD */

/* Define to 1 if you have the `fdatasync' function. */
/* #undef HAVE_FDATASYNC */

/* Define to 1 if you have the `fgetc' function. */
/* #undef HAVE_FGETC */

/* Define to 1 if you have the `fgets' function. */
/* #undef HAVE_FGETS */

/* Define to 1 if allocated filesystem blocks are not zeroed. */
#define HAVE_FILESYSTEM_NOTZERO 1

/* Define to 1 to build Berkeley DB with a fine-grained lock manager. */
/* #undef HAVE_FINE_GRAINED_LOCK_MANAGER */

/* Define to 1 if you have the `fopen' function. */
/* #undef HAVE_FOPEN */

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `fwrite' function. */
/* #undef HAVE_FWRITE */

/* Define to 1 if you have the `getaddrinfo' function. */
/* #undef HAVE_GETADDRINFO */

/* Define to 1 if you have the `getcwd' function. */
/* #undef HAVE_GETCWD */

/* Define to 1 if you have the `getenv' function. */
/* #undef HAVE_GETENV */

/* Define to 1 if you have the `getopt' function. */
/* #undef HAVE_GETOPT */

/* Define to 1 if you have the `getrusage' function. */
/* #undef HAVE_GETRUSAGE */

/* Define to 1 if you have the `gettimeofday' function. */
/* #undef HAVE_GETTIMEOFDAY */

/* Define to 1 if you have the `getuid' function. */
/* #undef HAVE_GETUID */

/* Define to 1 if building Hash access method. */
/* #undef HAVE_HASH */

/* Define to 1 if you have the `hstrerror' function. */
/* #undef HAVE_HSTRERROR */

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the `isspace' function. */
/* #undef HAVE_ISALPHA  */

/* Define to 1 if you have the `isspace' function. */
/* #undef HAVE_ISDIGIT  */

/* Define to 1 if you have the `isspace' function. */
/* #undef HAVE_ISPRINT  */

/* Define to 1 if you have the `isspace' function. */
/* #undef HAVE_ISSPACE  */

/* Define to 1 if you have the `localtime' function. */
/* #undef HAVE_LOCALTIME */

/* Define to 1 if you have the `memcmp' function. */
#define HAVE_MEMCMP 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
/* #undef HAVE_MEMORY_H */

/* Define to 1 if you have the `mlock' function. */
/* #undef HAVE_MLOCK */

/* Define to 1 if you have the `mmap' function. */
/* #undef HAVE_MMAP */

/* Define to 1 if you have the `mprotect' function. */
/* #undef HAVE_MPROTECT */

/* Define to 1 if you have the `munlock' function. */
/* #undef HAVE_MUNLOCK */

/* Define to 1 if you have the `munmap' function. */
/* #undef HAVE_MUNMAP */

/* Define to 1 to use the GCC compiler and 68K assembly language mutexes. */
/* #undef HAVE_MUTEX_68K_GCC_ASSEMBLY */

/* Define to 1 to use the AIX _check_lock mutexes. */
/* #undef HAVE_MUTEX_AIX_CHECK_LOCK */

/* Define to 1 to use the GCC compiler and Alpha assembly language mutexes. */
/* #undef HAVE_MUTEX_ALPHA_GCC_ASSEMBLY */

/* Define to 1 to use the GCC compiler and ARM assembly language mutexes. */
/* #undef HAVE_MUTEX_ARM_GCC_ASSEMBLY */

/* Define to 1 to use the Apple/Darwin _spin_lock_try mutexes. */
/* #undef HAVE_MUTEX_DARWIN_SPIN_LOCK_TRY */

/* Define to 1 to use the UNIX fcntl system call mutexes. */
/* #undef HAVE_MUTEX_FCNTL */

/* Define to 1 to use the GCC compiler and PaRisc assembly language mutexes.
   */
/* #undef HAVE_MUTEX_HPPA_GCC_ASSEMBLY */

/* Define to 1 to use the msem_XXX mutexes on HP-UX. */
/* #undef HAVE_MUTEX_HPPA_MSEM_INIT */

/* Define to 1 to use test-and-set mutexes with blocking mutexes. */
/* #undef HAVE_MUTEX_HYBRID */

/* Define to 1 to use the GCC compiler and IA64 assembly language mutexes. */
/* #undef HAVE_MUTEX_IA64_GCC_ASSEMBLY */

/* Define to 1 to use the GCC compiler and MIPS assembly language mutexes. */
/* #undef HAVE_MUTEX_MIPS_GCC_ASSEMBLY */

/* Define to 1 to use the msem_XXX mutexes on systems other than HP-UX. */
/* #undef HAVE_MUTEX_MSEM_INIT */

/* Define to 1 to use the GCC compiler and PowerPC assembly language mutexes.
   */
/* #undef HAVE_MUTEX_PPC_GCC_ASSEMBLY */

/* Define to 1 to use POSIX 1003.1 pthread_XXX mutexes. */
/* #undef HAVE_MUTEX_PTHREADS */

/* Define to 1 to use Reliant UNIX initspin mutexes. */
/* #undef HAVE_MUTEX_RELIANTUNIX_INITSPIN */

/* Define to 1 to use the IBM C compiler and S/390 assembly language mutexes.
   */
/* #undef HAVE_MUTEX_S390_CC_ASSEMBLY */

/* Define to 1 to use the GCC compiler and S/390 assembly language mutexes. */
/* #undef HAVE_MUTEX_S390_GCC_ASSEMBLY */

/* Define to 1 to use the SCO compiler and x86 assembly language mutexes. */
/* #undef HAVE_MUTEX_SCO_X86_CC_ASSEMBLY */

/* Define to 1 to use the obsolete POSIX 1003.1 sema_XXX mutexes. */
/* #undef HAVE_MUTEX_SEMA_INIT */

/* Define to 1 to use the SGI XXX_lock mutexes. */
/* #undef HAVE_MUTEX_SGI_INIT_LOCK */

/* Define to 1 to use the Solaris _lock_XXX mutexes. */
/* #undef HAVE_MUTEX_SOLARIS_LOCK_TRY */

/* Define to 1 to use the Solaris lwp threads mutexes. */
/* #undef HAVE_MUTEX_SOLARIS_LWP */

/* Define to 1 to use the GCC compiler and Sparc assembly language mutexes. */
/* #undef HAVE_MUTEX_SPARC_GCC_ASSEMBLY */

/* Define to 1 if the Berkeley DB library should support mutexes. */
/* #undef HAVE_MUTEX_SUPPORT */

/* Define to 1 if mutexes hold system resources. */
/* #undef HAVE_MUTEX_SYSTEM_RESOURCES */

/* Define to 1 to configure mutexes intra-process only. */
/* #undef HAVE_MUTEX_THREAD_ONLY */

/* Define to 1 to use the CC compiler and Tru64 assembly language mutexes. */
/* #undef HAVE_MUTEX_TRU64_CC_ASSEMBLY */

/* Define to 1 to use the UNIX International mutexes. */
/* #undef HAVE_MUTEX_UI_THREADS */

/* Define to 1 to use the UTS compiler and assembly language mutexes. */
/* #undef HAVE_MUTEX_UTS_CC_ASSEMBLY */

/* Define to 1 to use VMS mutexes. */
/* #undef HAVE_MUTEX_VMS */

/* Define to 1 to use VxWorks mutexes. */
/* #undef HAVE_MUTEX_VXWORKS */

/* Define to 1 to use the MSVC compiler and Windows mutexes. */
/* #undef HAVE_MUTEX_WIN32 */

/* Define to 1 to use the GCC compiler and Windows mutexes. */
/* #undef HAVE_MUTEX_WIN32_GCC */

/* Define to 1 to use the GCC compiler and 64-bit x86 assembly language
   mutexes. */
/* #undef HAVE_MUTEX_X86_64_GCC_ASSEMBLY */

/* Define to 1 to use the GCC compiler and 32-bit x86 assembly language
   mutexes. */
/* #undef HAVE_MUTEX_X86_GCC_ASSEMBLY */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the O_DIRECT flag. */
/* #undef HAVE_O_DIRECT */

/* Define to 1 if you have the `pread' function. */
/* #undef HAVE_PREAD */

/* Define to 1 if you have the `printf' function. */
/* #undef HAVE_PRINTF */

/* Define to 1 if you have the `pstat_getdynamic' function. */
/* #undef HAVE_PSTAT_GETDYNAMIC */

/* Define to 1 to configure Berkeley DB for POSIX pthread API. */
/* #undef HAVE_PTHREAD_API */

/* Define to 1 if you have the `pthread_yield' function. */
/* #undef HAVE_PTHREAD_YIELD */

/* Define to 1 if you have the `pwrite' function. */
/* #undef HAVE_PWRITE */

/* Define to 1 if building on QNX. */
/* #undef HAVE_QNX */

/* Define to 1 if you have the `qsort' function. */
/* #undef HAVE_QSORT */

/* Define to 1 if building Queue access method. */
/* #undef HAVE_QUEUE */

/* Define to 1 if you have the `raise' function. */
/* #undef HAVE_RAISE */

/* Define to 1 if you have the `rand' function. */
/* #undef HAVE_RAND */

/* Define to 1 if building replication support. */
/* #undef HAVE_REPLICATION */

/* Define to 1 if building the Berkeley DB replication framework. */
/* #undef HAVE_REPLICATION_THREADS */

/* Define to 1 if building RPC client/server. */
/* #undef HAVE_RPC */

/* Define to 1 if building on S60. */
/* #undef HAVE_S60 */

/* Define to 1 if you have the `sched_yield' function. */
/* #undef HAVE_SCHED_YIELD */

/* Define to 1 if you have the `select' function. */
/* #undef HAVE_SELECT */

/* Define to 1 if you have the `shmget' function. */
/* #undef HAVE_SHMGET */

/* Define to 1 if you have the `sigaction' function. */
/* #undef HAVE_SIGACTION */

/* Define to 1 if thread identifier type db_threadid_t is integral. */
/* #undef HAVE_SIMPLE_THREAD_TYPE */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `stat' function. */
/* #undef HAVE_STAT */

/* Define to 1 if building statistics support. */
/* #undef HAVE_STATISTICS */

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the <stdlib.h> header file. */
/* #undef HAVE_STDLIB_H */

/* Define to 1 if you have the `strcasecmp' function. */
/* #undef HAVE_STRCASECMP */

/* Define to 1 if you have the `strcat' function. */
#define HAVE_STRCAT 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
/* #undef HAVE_STRERROR */

/* Define to 1 if you have the `strftime' function. */
/* #undef HAVE_STRFTIME */

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
/* #undef HAVE_STRING_H */

/* Define to 1 if you have the `strncat' function. */
/* #undef HAVE_STRNCAT */

/* Define to 1 if you have the `strncmp' function. */
#define HAVE_STRNCMP 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the `strsep' function. */
/* #undef HAVE_STRSEP */

/* Define to 1 if you have the `strtol' function. */
/* #undef HAVE_STRTOL */

/* Define to 1 if you have the `strtoul' function. */
#define	HAVE_STRTOUL 1

/* Define to 1 if `st_blksize' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_BLKSIZE */

/* Define to 1 if you have the `sysconf' function. */
/* #undef HAVE_SYSCONF */

/* Define to 1 if port includes files in the Berkeley DB source code. */
/* #undef HAVE_SYSTEM_INCLUDE_FILES */

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/select.h> header file. */
/* #undef HAVE_SYS_SELECT_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
/* #undef HAVE_SYS_SOCKET_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
/* #undef HAVE_SYS_STAT_H */

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
/* #undef HAVE_SYS_TYPES_H 1*/

/* Define to 1 if you have the `time' function. */
/* #undef HAVE_TIME */

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Define to 1 if unlink of file with open file descriptors will fail. */
/* #undef HAVE_UNLINK_WITH_OPEN_FAILURE */

/* Define to 1 if port includes historic database upgrade support. */
/* #undef HAVE_UPGRADE_SUPPORT */

/* Define to 1 if building access method verification support. */
/* #undef HAVE_VERIFY */

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if building VxWorks. */
/* #undef HAVE_VXWORKS */

/* Define to 1 if you have the `yield' function. */
/* #undef HAVE_YIELD */

/* Define to 1 if you have the `_fstati64' function. */
/* #undef HAVE__FSTATI64 1*/

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "support@sleepycat.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Berkeley DB"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Berkeley DB 4.6.18"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "db-4.6.18"

/* Define to the version of this package. */
#define PACKAGE_VERSION "4.6.18"

/* The size of a `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of a `char *', as computed by sizeof. */
#define SIZEOF_CHAR_P 4

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG 4

/* The size of a `long long', as computed by sizeof. */
/* #undef SIZEOF_LONG_LONG */

/* The size of a `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* The size of a `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 4

/* The size of a `unsigned char', as computed by sizeof. */
#define SIZEOF_UNSIGNED_CHAR 1

/* The size of a `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT 4

/* The size of a `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG 4

/* The size of a `unsigned long long', as computed by sizeof. */
/* #undef SIZEOF_UNSIGNED_LONG_LONG */

/* The size of a `unsigned short', as computed by sizeof. */
#define SIZEOF_UNSIGNED_SHORT 2

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
/* #undef TIME_WITH_SYS_TIME */

/* Define to 1 to mask harmless uninitialized memory read/writes. */
/* #undef UMRW */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#define inline
#endif

/* type to use in place of socklen_t if not defined */
/* #undef socklen_t */
