/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)dmdversion.c	1.2";

/* dmdversion.c
 *		return the terminal and host version and if lan
 *		encoding is set
 *		
 *	FW vers id
 *	(8;T;X)		Terminal Version
 *	-------		----------------
 *	   7		     5620
 *	   8		     630
 *	   0		     620
 *	   4		     615
 *
 *
 * Usage: $DMD/bin/dmdversion [-h] [-t] [-l] [-e] [-s]
 *
 *		-h	Host. Print host version of software.
 *		-l	LAN check.  Find out if LAN Encoding is set.
 *		-t	Terminal. Find what type of terminal it is.
 *		-e	ESC seq.  Use an escape sequence instead of ioctl.
 *			(Not useful in layers unless windowproc down there).
 *		-s	Silent.  Only supply return value.
 *
 *
 */

#include "dmd.h"
#undef NULL
#include <termio.h>
#include "quiet.h"
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <sys/jioctl.h>
#ifndef TIOCEXCL
#include <sgtty.h>
#endif

#if sun
/* for compatibility with older pseudo-tty based layers */
#ifndef USE_LIBWINROMVERSION
#define USE_LIBWINROMVERSION
#endif
#endif

#ifdef USE_HOSTAGENT
/* newer libwindows */
#ifndef USE_LIBWINROMVERSION
#define USE_LIBWINROMVERSION
#endif
#endif

#define SENDTERMID "\033[c"
#define TERM_FST "\033[?8;"
#define TERM_FST_IOCTL	"8;"
#define TERMIDSIZE 20
#define ENC_CHK "\033[F"
#define	ENC_LEN	4
#define FSTVFILE	"/VERSION"	/* This is where the host version is stored */

extern char *getenv();
extern int	optind;

#ifndef NO_AGENTVERSION
#ifndef USE_LIBWINROMVERSION
#define DADDR /* some agent.h's key off of this to define agentRectangle */
typedef struct Point {
	short	x;
	short	y;
} Point;

typedef struct Rectangle {
	Point origin;
	Point corner;
} Rectangle;
#include "agent.h"
extern union	bbuf	{
		struct	agentrect	ar;
		char	buf[MAXPKTDSIZE];
};
extern union	bbuf	ret;
#endif
#endif

int	forbgs;	
int	cntlfd;			/* FD for xt control channel */

int eflag, sflag, lflag, tflag, hflag, errflag, iflag;
int retval, ttyfd, debug, abort;

#ifdef NO_TERMIO
struct sgttyb	ttysave,	/* save the state of tty */
		ttyraw;
#else
struct termio	ttysave,	/* save the state of tty */
		ttyraw;
#endif

void
Time_out ()
{
	if (debug)	fprintf(stderr,"Timed out.\n");
	abort = 1;
}

main (argc, argv)
int argc;
char **argv;
{
	iflag = 1;
	while ((retval = getopt (argc, argv, "deslth")) != EOF)
		switch ( retval ) {
		case 'e':
			eflag++;
			break;
		case 's':
			sflag++;
			break;
		case 'l':
			lflag++;
			break;
		case 'd':
			debug++;
			break;
		case 't':
			tflag++;
			break;
		case 'h':
			hflag++;
			break;
		default:
			errflag++;
			break;
		}

	if (optind < argc || errflag) {
		fprintf(stderr,"usage: dmdversion [-htels]\n");
		exit(1);
	}

	if (argc == 1) { /* set defaults */
		hflag++;
		tflag++;
	}

	if (tflag && !eflag) {
		retval = byioctl();		/* may set eflag!!! */
		if (debug)	printf("retval(ioctl) = %d\n",retval);
	}
	if (lflag || eflag) {
		for (ttyfd = 0; ttyfd <= 2; ttyfd++)
			if (isatty(ttyfd))
				break;
		if (ttyfd > 2) {
			fprintf(stderr, "Not on a tty\n");
			exit(1);
		}
		raw();
		if(eflag)
		{
			retval = byescseq();
			if (retval == -1) {
				cooked();
				if (!sflag)
					fprintf(stderr, "No response to terminal ID request\n");
				if (debug)
					printf("retval(byescseq) = %d\n",retval);
				goto out;
			}
		}
		if(lflag)
		{
			retval = lbyescseq();
			if (retval == -1) {
				cooked();
				if (!sflag)
					fprintf(stderr, "No response to terminal encoding enquire\n");
				if (debug)
					printf("retval(lbyescseq) = %d\n",retval);
				goto out;
			}
		}
		cooked();
	}

    out:
	if (sflag) {
		exit(retval);
	} else if (hflag) {
		printhost();
	}
	exit(0);
}

int
byioctl() 
{
#ifdef NO_AGENTVERSION
	eflag++;
#else
    
#ifdef USE_LIBWINROMVERSION
	char versbuf[9];
#endif

	/* find rom version by agent ioctl  -- the most reliable way */

	if ( (cntlfd = openagent()) == -1 )  { 
		if (debug) {
			fprintf(stderr, "Error:  couldn't open control channel to determine firmware version.\nError number %d\n",errno);
		}
		eflag++;	/* resort to using an escape seq */
	}
#ifdef USE_LIBWINROMVERSION
	else if (forbgs = Romversion(cntlfd, versbuf, sizeof(versbuf)) == -1) {
		if (debug) {
			fprintf(stderr, "Error: Romversion returned %d (error %d).\n   Cannot determine firmware version.\n", forbgs, errno);
		}
		closeagent();
		eflag++;	/* resort to using an escape seq */
	} else {
		closeagent();
		return ( printterm(versbuf) );
	}
#else
	else if( forbgs = ioctlagent(cntlfd, A_ROMVERSION,0,0,0,0,0)) {
		if (debug) {
			fprintf(stderr, "Error: A_ROMVERSION returned %d (error %d).\n   Cannot determine firmware version.\n", forbgs, errno);
		}

		eflag++;	/* resort to using an escape seq */
	} else {

		swab(ret.buf, ret.buf, sizeof(struct agentrect));

		if (debug) {
			fprintf(stderr,"Rom version id is ");
			for (forbgs=4; forbgs<9; forbgs++)
				fprintf(stderr,"%c",ret.buf[forbgs]);
			fprintf(stderr,"\n");
		}
		return( printterm(&ret.buf[4] );  /* the last digit of x;y;z */
	}
#endif
#endif
	return (0);
}

int
byescseq()
{
	int count, lpindex;
	char termid[TERMIDSIZE];

	abort = 0;
	signal(SIGALRM, Time_out);
	alarm(4);
	write(ttyfd,SENDTERMID,strlen(SENDTERMID));
	count = 0;
	while((count == 0 || termid[count-1] != 'c') && !abort){
		lpindex = read(ttyfd,&termid[count],TERMIDSIZE-count);
		if(lpindex > 0)  count += lpindex;
	}
	alarm(0);

	if(abort)
		return(-1);
	termid[count-1] = '\0';
	return ( printterm(termid + 3) );
}

lbyescseq()
{
	char scr_buf[ENC_LEN];
	int count, lpindex;
	char *dwnldflag;

	count = abort = 0;
	signal(SIGALRM, Time_out);
	alarm(4);
	write(ttyfd,ENC_CHK,strlen(ENC_CHK));
	while(count < ENC_LEN && !abort){
		lpindex = read(ttyfd,&scr_buf[count],ENC_LEN - count);
		if(lpindex > 0)count += lpindex;
	}
	alarm(0);
	if(abort)
		return(-1);
	if(scr_buf[2] == '0')
	{ /* see if the host way is set */
		if (((dwnldflag = getenv("DMDLOAD")) != NULL) &&
		     (dwnldflag[0] != NULL)) {
			if (strcmp(dwnldflag, "hex") == 0)
			return ( printlan(1) );
		}
	}
	return ( printlan(scr_buf[2]) );
}


printterm (s)
char *s;
{
	if (!sflag) {
		printf("terminal type: %s", s);
		if (s[3] == ';') {
			switch (s[2]) {
			case '8':
				printf(" - 630 MTG");
				break;
			case '7':
				printf(" - 5620 DMD");
				break;
			case '4':
				printf(" - 615 MTG");
				break;
			case '0':
				printf(" - 620 MTG");
				break;
			}
		}
		putchar('\r');
		putchar('\n');
	}
	if (s[3] == ';')
		return(s[4]);
	return(0);
}


printlan(n)
char n;
{
	if(!sflag)
		if(n == '1')
			printf("Encoding enabled.\r\n");
		else
			printf("Encoding not enabled.\r\n");
	return(n - '0');
}

printhost()
{
	char *fst;
	char fstvfile[128];
	int c;
	FILE *fp;

	if (((fst = getenv("DMD")) == (char *) 0) || (*fst == '\0')) {
#ifdef DEFDMD
		fst = DEFDMD;
#else
		fprintf(stderr, "DMD not set, unknown host version.\n");
		return;
#endif
	}
	strcat(strcpy(fstvfile, fst), FSTVFILE);
	if((fp = fopen(fstvfile, "r")) == NULL) {
		fprintf(stderr, "can't open host version file: %s\n", fstvfile);
	}
	else {
		while((c = getc(fp)) != EOF)
			putchar(c);
	}
}

#ifdef NO_TERMIO
raw ()
{
	(void)ioctl(ttyfd, TIOCGETP, &ttysave); /* get the current state */
#ifdef TIOCEXCL
	(void)ioctl(ttyfd, TIOCEXCL, 0);
#endif
	ttyraw = ttysave;
	ttyraw.sg_flags = RAW | ANYP;
	(void)ioctl(ttyfd, TIOCSETP, &ttyraw);
}

cooked ()
{	
#ifdef TIOCNXCL
	(void)ioctl(ttyfd, TIOCNXCL, 0);
#endif
	(void)ioctl(ttyfd, TIOCSETP, &ttysave);
}

#else

raw ()
{
	(void)ioctl(ttyfd, TCGETA, &ttysave); /* get the current state */
#ifdef TIOCEXCL
	(void)ioctl(ttyfd, TIOCEXCL, 0);
#endif
	ttyraw.c_iflag = IGNBRK;
	ttyraw.c_cflag = (ttysave.c_cflag & CBAUD) |
			 (ttysave.c_cflag & CLOCAL) | CS8 | CREAD;
	ttyraw.c_cc[VMIN] = 1;
	(void)ioctl(ttyfd, TCSETAW, &ttyraw);
}

cooked ()
{	
#ifdef TIOCNXCL
	(void)ioctl(ttyfd, TIOCNXCL, 0);
#endif
	(void)ioctl(ttyfd, TCSETAW, &ttysave);
}
#endif

/* swap bytes if necessary. target is big endian. */
swab(a, b, n)
	register char *a, *b;
	register n;
{
	register short space;

	n/=2;	/* n in bytes */
	while(n--){
		space = *(short *)a;
		*b++= space >> 8;  /* most significant byte first */
		*b++= space;
		a+=2;
	}
}

