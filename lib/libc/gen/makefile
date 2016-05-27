#ident	"@(#)libc-port:gen/makefile	1.17.3.5"
#
#	MC68000	GENERAL	LIBRARY	ROUTINES MAKEFILE
#
#
include ../../../stand.defs

LINT=lint
AFLAGS=r
LFLAGS=-p
LDFLAGS=
CC_CMD=$(MCC) $(MCFLAGS) -c

OFILES=	abs.o atof.o atoi.o atol.o bsearch.o ctype.o drand48.o ecvt.o fakcu.o \
	gcvt.o lsearch.o memccpy.o memchr.o memcmp.o memcpy.o memset.o qsort.o \
	rand.o ssignal.o strcat.o strchr.o strcmp.o strcpy.o strcspn.o \
	strlen.o strncat.o strncmp.o strncpy.o strpbrk.o strrchr.o strspn.o \
	strtok.o strtol.o swab.o tolower.o toupper.o

CFILES=	a64l.c abort.c abs.c assert.c atof.c atoi.c atol.c bsearch.c calloc.c \
	clock.c crypt.c	ctime.c	ctype.c	dial.c drand48.c ecvt.c errlst.c \
	execvp.c fakcu.c ftok.c ftw.c gcvt.c getcwd.c getenv.c getgrent.c \
	getgrgid.c getgrnam.c getlogin.c getopt.c getpw.c getpwent.c \
	getpwnam.c getpwuid.c getut.c hsearch.c isatty.c l3.c l64a.c lsearch.c \
	memccpy.c memchr.c memcmp.c memcpy.c memset.c mktemp.c mon.c nlist.c \
	perror.c putpwent.c qsort.c rand.c ssignal.c strcat.c strchr.c \
	strcmp.c strcpy.c strcspn.c strlen.c strncat.c strncmp.c strncpy.c \
	strpbrk.c strrchr.c strspn.c strtok.c strtol.c swab.c tell.c tolower.c \
	toupper.c tsearch.c ttyname.c ttyslot.c

SOURCE=abs.c atof.c atoi.c atol.c bsearch.c ctype.c drand48.c\
	ecvt.c fakcu.c gcvt.c getopt.c lsearch.c makefile memccpy.c\
	memchr.c memcmp.c memcpy.c memset.c qsort.c rand.c ssignal.c\
	strcat.c strchr.c strcmp.c strcpy.c strcspn.c strlen.c strncat.c\
	strncmp.c strncpy.c strpbrk.c strrchr.c strspn.c strtok.c strtol.c\
	swab.c tolower.c toupper.c tsearch.c

build:		$(OFILES)

#-------------------------

abs.o:		abs.c
		$(CC_CMD) abs.c

atof.o:		atof.c
		$(CC_CMD) atof.c

atoi.o:		atoi.c
		$(CC_CMD) atoi.c

atol.o:		atol.c
		$(CC_CMD) atol.c

bsearch.o:	bsearch.c
		$(CC_CMD) bsearch.c

ctype.o:	ctype.c
		$(CC_CMD) ctype.c

drand48.o:	drand48.c
		$(CC_CMD) drand48.c

ecvt.o:		ecvt.c
		$(CC_CMD) ecvt.c

fakcu.o:	fakcu.c
		$(CC_CMD) fakcu.c

gcvt.o:		gcvt.c
		$(CC_CMD) gcvt.c

#getopt.o:	getopt.c
#		$(CC_CMD) getopt.c

lsearch.o:	lsearch.c
		$(CC_CMD) lsearch.c

memccpy.o:	memccpy.c
		$(CC_CMD) memccpy.c

memchr.o:	memchr.c
		$(CC_CMD) memchr.c

memcmp.o:	memcmp.c
		$(CC_CMD) memcmp.c

memcpy.o:	memcpy.c
		$(CC_CMD) memcpy.c

memset.o:	memset.c
		$(CC_CMD) memset.c

qsort.o:	qsort.c
		$(CC_CMD) qsort.c

rand.o:		rand.c
		$(CC_CMD) rand.c

ssignal.o:	ssignal.c
		$(CC_CMD) ssignal.c

strcat.o:	strcat.c
		$(CC_CMD) strcat.c

strchr.o:	strchr.c
		$(CC_CMD) strchr.c

strcmp.o:	strcmp.c
		$(CC_CMD) strcmp.c

strcpy.o:	strcpy.c
		$(CC_CMD) strcpy.c

strcspn.o:	strcspn.c
		$(CC_CMD) strcspn.c

strlen.o:	strlen.c
		$(CC_CMD) strlen.c

strncat.o:	strncat.c
		$(CC_CMD) strncat.c

strncmp.o:	strncmp.c
		$(CC_CMD) strncmp.c

strncpy.o:	strncpy.c
		$(CC_CMD) strncpy.c

strpbrk.o:	strpbrk.c
		$(CC_CMD) strpbrk.c

strrchr.o:	strrchr.c
		$(CC_CMD) strrchr.c

strspn.o:	strspn.c
		$(CC_CMD) strspn.c

strtok.o:	strtok.c
		$(CC_CMD) strtok.c

strtol.o:	strtol.c
		$(CC_CMD) strtol.c

swab.o:		swab.c
		$(CC_CMD) swab.c

tolower.o:	tolower.c
		$(CC_CMD) tolower.c

toupper.o:	toupper.c
		$(CC_CMD) toupper.c

#tsearch.o:	tsearch.c
#		$(CC_CMD) tsearch.c


#-------------------------

install:	$(OFILES)
		-ln $(OFILES) ..

#--------------------------

clean:
	-rm -f $(OFILES)
	cd ..; rm -f $(OFILES)

#--------------------------

clobber:	clean

#--------------------------


lint:	$(CFILES)
	$(LINT)	$(LFLAGS) $(CFILES) >lint.out
