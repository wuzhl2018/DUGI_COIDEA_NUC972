# Makefile for systems with GNU tools
IFLAGS  = -idirafter dummyinc
#CFLAGS = -g
CFLAGS	+=	-O2 -fPIE -fno-stack-protector --param=ssp-buffer-size=4 \
	-Wall -W -Wshadow -Werror -Wformat-security \
	-D_FORTIFY_SOURCE=2 \
	#-pedantic -Wconversion

LIBS	=	`./vsf_findlibs.sh`
LINK	=	-Wl,-s
LDFLAGS	=	-fPIE -pie -Wl,-z,relro -Wl,-z,now

OBJS	=	main.o utility.o prelogin.o ftpcmdio.o postlogin.o privsock.o \
		tunables.o ftpdataio.o secbuf.o ls.o \
		postprivparent.o logging.o str.o netstr.o sysstr.o strlist.o \
    banner.o filestr.o parseconf.o secutil.o \
    ascii.o oneprocess.o twoprocess.o privops.o standalone.o hash.o \
    tcpwrap.o ipaddrparse.o access.o features.o readwrite.o opts.o \
    ssl.o sslslave.o ptracesandbox.o ftppolicy.o sysutil.o sysdeputil.o \
    seccompsandbox.o


.c.o:
	$(CC) -c $*.c $(CFLAGS) $(IFLAGS)

vsftpd: $(OBJS) 
	$(CC) -o vsftpd $(OBJS) $(LINK) $(LDFLAGS) $(LIBS)

install:
	cp vsftpd           $(PREFIX)/usr/sbin/
	cp dugi.vsftpd.conf $(PREFIX)/etc/vsftpd.conf

clean:
	rm -f *.o *.swp vsftpd

