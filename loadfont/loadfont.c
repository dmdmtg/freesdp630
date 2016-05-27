/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/*

static char _2Vsccsid[]="@(#)loadfont.c	1.1.1.12	(6/22/87)";
*/

#include <stdio.h>
#include <signal.h>
#include <sys/jioctl.h>
#include <errno.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "loadfont.h"


#define DMDLD	"/bin/dmdld"
#define PATHM	"/lib/loadfont.m"

typedef struct Fontchar {
	short x;
	unsigned char top;
	unsigned char bottom;
	char left;
	unsigned char width;
	short unused;
} Fontchar;

typedef struct Font {
	short n;
	char height;
	char accent;
	long unused;
	Fontchar info[1];
} Font;

struct termio ttyraw, ttysave;
char pathdmdld[256];
char pathm[256];
char searchbuf[256];
char *progname;
char *bits;	/* bits part of the currently loading font */

int dflag;	/* debug */
int qflag;	/* quit */
int sflag;	/* stay */
int eflag;	/* error */

char *carg;
int (*sendpkt)();
int muxsendpkt();
int nonmuxsendpkt();
int (*rcvpkt)();
int muxrcvpkt();
int nonmuxrcvpkt();
char *malloc();
Rpacket rpacket;
int loading;
int termload;
int cachefailed;

#ifndef USE_HOSTAGENT
#define inlayers() (ioctl(1, JMPX, 0) != -1)
#endif

main(argc, argv)
int argc;
char **argv;
{
	register int c;
	register char *rfiles = "";
	register char *s;
	extern char *optarg;
	extern int optind;

	progname = argv[0];
	getdmd(searchbuf);
	strcat(searchbuf, "/termfonts");

	
	while ((c = getopt(argc, argv, "cdp:r:s")) != EOF) {
		switch (c) {

		case 'c':
			carg = "-c";
			break;

		case 'd':
			dflag++;
			break;

		case 'p':
			strcpy(searchbuf, optarg);
			break;

		case 'r':
			rfiles = optarg;
			break;

		case 's':
			sflag++;
			break;

		case '?':
			eflag++;
			break;
		}
	}

	if (eflag) {
		usage ();	/* and exit */
	}

	if(!inlayers() && !dflag) {
		/* loadfont requires layers for the error */
		/*   correction and eight bit data path   */       
		fprintf(stderr, "%s only runs under layers\n", progname);
		exit(1);
	}

	sendpkt = muxsendpkt;
	rcvpkt = muxrcvpkt;
	getdmd(pathdmdld);
	strcat(pathdmdld, DMDLD);
	getdmd(pathm);
	strcat(pathm, PATHM);
	ioctl(0, TCGETA, &ttysave);	/* in case of file error */
        if (access(pathdmdld,01))
        {
		fileerror(pathdmdld);
        }
        if (access(pathm,04))
        {
		fileerror(pathm);
        }
	if(!boot(pathm))
		quit("dmdld errors");
	ttyraw.c_iflag = IGNBRK;
        ttyraw.c_cflag = (ttysave.c_cflag & CBAUD) | 
                         (ttysave.c_cflag & CLOCAL) | CS8 | CREAD;
        ttyraw.c_cc[VMIN] = 0;
	ttyraw.c_cc[VTIME] = 1;
        (void)ioctl(0, TCSETAW, &ttyraw);       /* set new terminal parameters */
	if(dflag)
		(*sendpkt)(T_DEBUG, "", 0);


	/* load the font files and remove the font names */
	for (s = strtok (rfiles, ", "); s; s = strtok((char *)0, ", ")) {
		removef (s);
		qflag++;
		sleep(2);	/* for user to see the thump up icon */
	}

	for (; optind < argc; optind++) {
		loadf (argv[optind]);
		qflag++;
	}	

	if(qflag && !sflag)
	{
		errorm("exiting", (char *)0);
		fflush(stdout);
		sleep(3);
		myexit(cachefailed);
	}
	loadnames();
	wait4rcv();
}

loadf(name)
char *name;
{
	int fd;
	char buf[256];
	register int count, n;

	if(strlen(name) >= 100)
		name[100] = '\0';
	if((fd = open(name, 0)) == -1)
	{
		strcpy(buf, searchbuf);
		strcat(buf, "/");
		strcat(buf, name);
		if((fd = open(buf, 0)) == -1)
		{
			if(dflag)
				fprintf(stderr, "can't find file [%s]\n", name);
			errorm(name, " not found\r\n");
			return;
		}
	}

	if(infont(fd, name))
	{
		loading = 1;
		termload = 0;
		if(dflag)
			fprintf(stderr, "found file [%s]\n", name);
		(*sendpkt)(T_SLOAD, name, strlen(name));
		while(count = read(fd, buf, 256))
		{
			(*sendpkt)(T_LOAD, buf, count);
			if(n = read(0, buf, 256))
				(*rcvpkt)(buf, n);
			if(termload)
			{
				(*sendpkt)(T_TERM, "", 0);
				goto endload;
			}
		}
endload:
		if (!termload) {
			/*
			 * Wait for last packet from terminal.
			 * Change stty option to not return immediately 
			 *   from read.
			 */
			ttyraw.c_cc[VMIN] = 1;
			(void)ioctl(0, TCSETAW, &ttyraw);
			while (!termload && ((n = read(0, buf, 256)) > 0))
				(*rcvpkt)(buf, n);
			ttyraw.c_cc[VMIN] = 0;
			(void)ioctl(0, TCSETAW, &ttyraw);
		}

		loading = 0;
	}
	close(fd);
}

#define SWAPSHORT(S) S = (*((unsigned char *) &(S)) << 8) + \
			  *(((unsigned char *) &(S))+1)

infont(fd, name)
int fd;
char *name;
{
/*
 * sanity testing of the font file
 */
	struct stat buf;
	Font f;
	Fontchar fc;
	int x;

	if(fstat(fd, &buf) || buf.st_size < 24)
	{
		if(dflag)
			fprintf(stderr, "bad file stat [%s]\n", name);
no_good:
		errorm(name, ": bad size\r\n");
		return(0);
	}
	read(fd, &f, 8);
	SWAPSHORT(f.n);
	if(8 + 8 * (f.n + 1) > buf.st_size)
	{
		if(dflag)
			fprintf(stderr, "file too small [%s]\n", name);
		goto no_good;
	}
	lseek(fd, (f.n-1)*8, 1);
	read(fd, &fc, 8);
	SWAPSHORT(fc.x);
	x = fc.x;
	read(fd, &fc, 8);
	SWAPSHORT(fc.x);
	if(x < fc.x)
		x = fc.x;	/* this is needed for a bug in jf */
	if(f.height * ((x + 31)&0xFFE0) / 8 + 8 + 8 * (f.n+1) != buf.st_size)
	{
		if(dflag)
		{
			fprintf(stderr, "bad file size [%s]\n", name);
			fprintf(stderr, "is %d, expect %d\n", buf.st_size,
				f.height * ((x + 31)&0xFFE0) / 8 + 8 + 8 * (f.n + 1));
		}
		goto no_good;
	}
	lseek(fd, 0, 0);
	return(1);
}


int cmpfunc(onep, twop)
char **onep;
char **twop;
{
    return(strcmp(*onep, *twop));
}

loadnames()
{
	struct stat sbuf;
	DIR *dirp;
	struct dirent *direntp;
	int fd, n;
	char **list, **listp;

	n = 0;
	if(stat(searchbuf, &sbuf) == 0 && (sbuf.st_mode&S_IFMT) == S_IFDIR)
		if((dirp = opendir(searchbuf)) != NULL)
		{
			while(readdir(dirp) != NULL)
				n++;

			if((list = (char **) malloc(n * sizeof(char *))) != NULL)
			{
				rewinddir(dirp);
				n = 0;

				listp = list;
				while((direntp = readdir(dirp)) != NULL)
				{
					if(direntp->d_name[0] != '.')
					{
						*listp = malloc(
						    strlen(direntp->d_name)+1);
						strcpy(*listp,
							direntp->d_name);
						listp++;
						n++;
					}
				}
				qsort(list, n, sizeof(char *), cmpfunc);
				for(listp = list; n--; listp++) {
					(*sendpkt)(T_MENU, *listp, strlen(*listp));
					free(*listp);
				}
				free(list);
			}
			else
			{
				if(dflag)
					fprintf(stderr, "unable to malloc %d bytes\n", n * sizeof(char *));
			}
			closedir(dirp);
		}
		else
		{
			if(dflag)
				fprintf(stderr, "Unable to opendir %s\n", searchbuf);
		}
	else if(dflag)
		fprintf(stderr, "Unable to stat %s\n", searchbuf);
}




fileerror(s)
char *s;
{
        switch(errno)
        {
        case ENOTDIR:
                fprintf(stderr,"Error: %s contains bad dir\n",s);
                fprintf(stderr,"check for correct value of $DMD\n");
                break;
        case EACCES:
                fprintf(stderr,"Error: %s: no permission\n",s);
                break;
        default:
                fprintf(stderr,"Error: cannot access %s errno %d\n",s,errno);
                fprintf(stderr,"check for correct value of $DMD\n");
                break;
        }
        myexit(1);        /* couldnt stat the pathdmdld */
}

getdmd(s)
char *s;
{
	char *p;
	char *getenv();

	if(p = getenv("DMD"))
		strcpy(s, p);
	else
		strcpy(s, DEFDMD);
}



boot(s)
char *s;
{
	if(dflag > 1)
		return(1);
        if(psystem(pathdmdld, "dmdld", s, carg))
                return(0);
        return(1);
}

psystem(s, t, u, v)
char *s, *t, *u, *v;
{
        int status, pid, l;

        if ((pid = fork()) == 0) {
                execl(s, t, u, v, 0);
                _exit(127);
        }
        while ((l = wait(&status)) != pid && l != -1)
                ;
        if (l == -1)
                status = -1;
        return(status);
}


quit(s)
char *s;
{
	fprintf(stderr, "%s: %s\n", progname, s);
	myexit(1);
}

wait4rcv()
{
	char buf[64];
	int n;

	(*sendpkt)(T_START, (char *)0, 0);	/* start up terminal side */
	while(1)
		if(n = read(0, buf, 64))
			(*rcvpkt)(buf, n);
}

myexit(i)
int i;
{
	if(!i)
		(*sendpkt)(T_QUIT, "", 0);
	(void)ioctl(0, TCSETAW, &ttysave); /* recover original terminal setting */
	exit(i);
}


muxsendpkt(typ, s, n)
int typ, n;
char *s;
{
	int j;
	unsigned char buf[130];

	buf[0] = typ;
	j = 0;
	do
	{
		buf[1] = min(128, n);
		n -= 128;
		memcpy(&buf[2], &s[j], buf[1]);
		write(1, buf, buf[1] + 2);
		j += buf[1];
	}
	while(n>0);
	if(dflag)
	{
		fprintf(stderr, "send: %d %d\n",buf[0], buf[1]);
	}
}


errorm(s, s2)
char *s;
char *s2;
{
	char buf[140];

	strcpy(buf, s);
	if (s2)
		strcat(buf, s2);
	(*sendpkt)(T_ERR, buf, strlen(buf));
}


muxrcvpkt(buf, n)
char *buf;
int n;
{
	int i, num;

	i = 0;
	while( i < n)
	{
		switch(rpacket.state)
		{
			case R_NULL: /* beginning of a packet */
				rpacket.typ = buf[i++];
				rpacket.state = R_SIZE;
				if(i >= n)
					break;
			case R_SIZE: /* getting size field */
				rpacket.size = buf[i++];
				if(rpacket.size == 0)
				{
					dopacket();
					break;
				}
				rpacket.state = R_DATA;
				rpacket.numread = 0;
				if(i >= n)
					break;
			case R_DATA: /* getting data */
				num = min(rpacket.size - rpacket.numread, n - i);
				memcpy(rpacket.buf + rpacket.numread, buf + i, num);
				i += num;
				if((rpacket.numread += num) == rpacket.size)
					dopacket();
				break;
		}
	}
}


dopacket()
{
	rpacket.buf[rpacket.numread] = '\0';
	switch(rpacket.typ)
	{
		case H_LOAD: /* load a font */
			if(!loading) /* I am not currently loading a font */
				loadf(rpacket.buf);
			break;
		case H_FAILED:
			cachefailed++;
			/* fall through */
		case H_SUCCEEDED: /* fontcache after load succeeded */
		case H_TERM: /* terminate a load */
			if(loading) /* I am currently loading a font */
				termload = 1;
			break;
		case H_QUIT: /* quit the program */
			myexit(0);
		default: /* ??? */
			if(dflag)
			{
				fprintf(stderr, "bad packet type: %d", rpacket.typ);
				fprintf(stderr, "; size = %d\n", rpacket.size);
			}
	}
	rpacket.state = R_NULL;
	rpacket.numread = 0;
}


removef(name)
char *name;
{
	if(strlen(name) > 14)
		name[14] = '\0';
	(*sendpkt)(T_REMOVE, name, strlen(name));
}


min(a,b)
int a, b;
{
	if(a < b)
		return(a);
	return(b);
}

usage()
{
	fprintf(stderr, "Usage: loadfont [-c] [-s] [-p directory] [-r font-name[,...]] [font-file ...]\n");
	exit(2);
}


