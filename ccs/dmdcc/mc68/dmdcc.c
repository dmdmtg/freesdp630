/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */

/* VERSION(@(#)dmdcc.c	1.1.1.8	(6/15/87)); */

/* dmdcc - front end for C compiler for 630
 *
 * This is a modification of the mc68cc command that came with the sgs.
 *
 * Modified to:
 *	+) Use the DMD variable to find BINDIR and LIBDIR
 *	+) give -DDMD630
 *	+) give -I$DMD/include to cpp
 *	+) give -L$DMD/lib to ld
 *	+) make run time startoff for ld crtm.o
 *	+) give "-r -a" to ld
 *	+) give dmd libraries to ld
 *		+) libj
 *		+) libfw
 *		+) libc
 *	+) default outfile called dmda.out
 *
 * Other changes:
 *	+) stripped out support for blit terminals
 *	+) ifdef'ed out support for -p option because the mc68000 sgs
 *	   does not seem to support this. Their manual page says the
 *	   flag is reserved - using the flag would cause an error. I
 *	   thought it would be better to remove the option.
 */

#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include "filehdr.h"
#include "scnhdr.h"

#define	BINDIR	"/bin"		/* only a component in the path - actual path */
#define	LIBDIR	"/lib"		/*    is built in main() */

#ifndef	NAMEcpp
#define	NAMEcpp	"cpp"			/* base preprocessor name */
#endif
#ifndef	NAMEccom
#define	NAMEccom	"ccom"		/* base compiler name */
#endif
#ifndef	NAMEas
#define	NAMEas	"as"			/* base assembler name */
#endif
#ifndef	NAMEoptim
#define	NAMEoptim	"optim"		/* base optimizer name */
#endif
#ifndef	NAMEld
#define	NAMEld	"ld"			/* base loader name */
#endif
#ifndef	NAMEcrt0
#define	NAMEcrt0	"crtm.o"	/* base startup routine name */
#endif
#ifdef PROFILE_SUPPORT
#ifndef	NAMEmcrt0
#define	NAMEmcrt0	"mcrt0.o"
#endif
#endif

char	*getfst();
char	*tempnam();
char	*fst;				/* pointer to $DMD */

char	*cpp;				/* pointer to true cpp name */
char	*ccom;				/* same for compiler */
char	*as;				/* ... etc. */
char	*c2;
char	*ld;
char	*crt0;

char	*prefix;			/* prefixing string in cc command;
					** i.e., "mc68" in "mc68cc"
					*/
#define	Xc0	0			/* numbers for passes */
#define	Xc1	1
#define	Xc2	2
#define	Xcp	3
#define	Xas	4
#define	Xld	5
#define	NPASS	6
#define MINSTACK 2048		/* minimum allowable stack size */
#define NSECTS 2		/* number of sections of output file that will
				 * be read back in to write stack size */
#define TEXTSECT 0
#define DATASECT 1

char	*tmp0;				/* holds temp. file template */
char	*tmp1, *tmp2, *tmp3, *tmp4, *tmp5;
char	*outfile;
char	*savestr(), *strspl(), *setsuf(), *makename();
char	*strtok();
void	idexit();
char	**av, **clist, **llist, **plist;
char	**list[NPASS];
int	nlist[NPASS];
int	cflag, eflag, gflag, pflag, sflag, wflag, Rflag, exflag, oflag, xflag, debug;
int	Zflag;		/* stack siZe */
int truncflag;				/* non-zero to truncate flexnames */
char	*dflag;
int	exfail;
char	*chpass;
char	*npassname;
extern	int	optind;
extern	int	opterr;
extern	char	*optarg;
extern	int	optopt;

int	nc, nl, np, nxo, na;
unsigned long stksize = MINSTACK;

char	file[1024];
int 	obj;
struct filehdr fileheader;
struct scnhdr secthdrs[NSECTS];
extern int access(), open();

#define	cunlink(x)	if (x) unlink(x)

main(argc, argv)
	char **argv;
{
	char *t;
	char *assource;
	int i, j, c, ic;
	int nargs = argc + 1;

	/* build initially assumed program names */

	/* get $DMD */
	fst = getfst();
	if(fst == (char *)0)
		exit(1);

	/* prefix always mc68 */
	prefix = "mc68";

	cpp  = makename(fst,LIBDIR,prefix,NAMEcpp);	/* C preprocessor */
	ccom = makename(fst,LIBDIR,prefix,NAMEccom); 	/* compiler */
	as   = makename(fst,BINDIR,prefix,NAMEas);	/* assembler */
	c2   = makename(fst,LIBDIR,prefix,NAMEoptim);	/* optimizer */
	ld   = makename(fst,BINDIR,prefix,NAMEld);	/* loader */
	crt0 = makename(fst,LIBDIR,"",NAMEcrt0);/* run-time start-up */

	if (0 != access(ccom,2)) {
	    error("cannot access compiler: %s", ccom);
	    exit(1);
	}

	/* ld currently adds upto 5 args; 10 is room to spare */
	/* I upped it anyway -- rob */
	av = (char **)calloc(argc+20, sizeof (char **));

	/* initialize arrays for extra arguments (-W) */

	for (i = NPASS; i-- > 0; ) {
	    nlist[i] = 0;
	    list[i] = (char **) calloc(nargs, sizeof(char **));
	}
	clist = (char **)calloc(argc, sizeof (char **));
	llist = (char **)calloc(argc, sizeof (char **));
	plist = (char **)calloc(argc, sizeof (char **));
	opterr = 0;

#define	OPTS	"xsSTo:ROP#gwEPcD:I:U:C:t:B:l:W:L:Z:"

	while (optind<argc) switch (c = getopt(argc, argv, OPTS)) {
	case 'x':
		xflag++;
		continue;
	case 'S':
		sflag++;
		cflag++;
		continue;
	case 'l':
		llist[nl++] = strspl("-l", optarg);
		continue;
	case 'o':
		outfile = optarg;
		switch (getsuf(outfile)) {

		case 'c':
		case 'o':
			error("-o would overwrite %s", outfile);
			exit(8);
		}
		continue;
	case 'R':
		Rflag++;
		continue;
	case 'O':
		oflag++;
		continue;
#ifdef PROFILE_SUPPORT
	case 'p':
		proflag++;
		continue;
#endif
	case '#':
		debug = 1;
		continue;
	case 'g':
		gflag++;
		continue;
	case 'w':
		wflag++;
		continue;
	case 'E':
		exflag++;
	case 'P':
		pflag++;
		if (optarg != 0)
		    plist[np++] = optarg;
	case 'c':
		cflag++;
		continue;
	case 'D':
	case 'I':
	case 'U':
	case 'C':
		plist[np] = strspl("-X", optarg);
		plist[np++][1] = c;
		continue;
	case 't':
		if (chpass)
			error("-t overwrites earlier option", 0);
		chpass = optarg;
		if (chpass[0]==0)
			chpass = "012p";
		continue;
	case 'B':
		if (npassname)
			error("-B overwrites earlier option", 0);
		npassname = optarg;
		if (npassname[0]==0)
			npassname = makename(fst,LIBDIR,"o",prefix);
		continue;
	case 'W':
		if((optarg[1] != ',')
			|| ((t = strtok(optarg, ",")) != optarg)){
			error("Invalid subargument: -W%s", optarg);
			continue;
		}
		if((i = getXpass((ic = *t), "-W")) == -1)
			continue;
		while((t = strtok(NULL, ",")) != NULL) {
			if(nlist[i] >= nargs){
				error("Too many arguments for pass -W%c", ic);
				continue;
			}
			list[i][nlist[i]++] = t;
		}
		continue;

	case 'd':
		dflag = optarg;
		continue;

	case 'L':
		llist[nl++] = strspl("-L",optarg);
		continue;
	case '?':
	case 's':
		t = strspl("-", "x");
		t[1] = optopt;
		llist[nl++] = t;
		continue;

	case 'T':			/* to truncate flexnames */
		truncflag++;
		continue;

	case 'Z':			/* stack size overide */
		if ((*optarg < '0') && (*optarg > '9'))
			error("Bad stack size argument: %s",optarg);
		stksize = (unsigned long) atoi(optarg);
		if (stksize < MINSTACK) stksize = MINSTACK;
		Zflag++;
		continue;

	case EOF:
		t = argv[optind];
		optind++;
		c = getsuf(t);
		if (c=='c' || c=='s' || exflag) {
			clist[nc++] = t;
			t = setsuf(t, 'o');
		}
		if (nodup(llist, t)) {
			llist[nl++] = t;
			if (getsuf(t)=='o')
				nxo++;
		}
	}
	if (npassname && chpass ==0)
		chpass = "012p";
	if (chpass && npassname==0)
		npassname = makename(fst,LIBDIR,"n",prefix);
	if (chpass)
	for (t=chpass; *t; t++) {
		switch (*t) {

		case '0':
			ccom = strspl(npassname, NAMEccom);
			continue;
		case '2':
			c2 = strspl(npassname, NAMEoptim);
			continue;
		case 'p':
			cpp = strspl(npassname, NAMEcpp);
			continue;
		case 'a':
			as = strspl(npassname, NAMEas);
			continue;
		case 'l':
			ld = strspl(npassname, NAMEld);
			continue;
		}
	}
#ifdef PROFILE_SUPPORT
	if (proflag)
		crt0 = makename(fst,LIBDIR,prefix,NAMEmcrt0);
#endif
	if (nc==0)
		goto nocom;
	if (eflag)
		dexit();

	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, idexit);
	if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
		signal(SIGTERM, idexit);
	tmp0 = tempnam(NULL,"ctm");	/* form temporary filename template */
	if (pflag==0) {
		tmp1 = strspl(tmp0, "1");
		tmp2 = strspl(tmp0, "2");
		tmp3 = strspl(tmp0, "3");
		tmp4 = strspl(tmp0, "4");
	}
	if (oflag)
		tmp5 = strspl(tmp0, "5");
	for (i=0; i<nc; i++) {
		if (nc > 1) {
			printf("%s:\n", clist[i]);
			fflush(stdout);
		}
		if (getsuf(clist[i]) == 's' && !pflag) {
			assource = clist[i];
			goto assemble;
		} else
			assource = tmp3;
		if (pflag)
			tmp4 = setsuf(clist[i], 'i');
		na = 0;			/* start building arguments */
		av[na++] = NAMEcpp;
		av[na++] = "-Dmc68000";
		av[na++] = "-Dmc68k16";		/* signify 16-bit version */
		if (!xflag)
			av[na++] = "-DDMD630";		/* for 630 */

		for (j = 0; j < np; j++)
			av[na++] = plist[j];

		/* -I$DMD/include */
		if (!xflag) {
			av[na++] = strspl("-I", strspl(fst, "/include"));
			av[na++] = strspl("-I", strspl(fst, "/include/dmd"));
		}

		if (truncflag)			/* pass -XT if truncating */
		    av[na++] = "-T";

		av[na++] = clist[i];
		av[na++] = exflag ? "-" : tmp4;
		for (j = 0; j < nlist[Xcp]; j++)
		    av[na++] = list[Xcp][j];
		av[na++] = 0;
		switch(callsys(cpp, av)){
		case 0:
			break;
#define	CLASS 27
		case CLASS:
			if(callsys("/lib/cpre", av)==0)
				break;
			/* fall through */
		default:
			exfail++;
			eflag++;
		}
		if (pflag || exfail) {
			cflag++;
			continue;
		}
		if (sflag)
			assource = tmp3 = setsuf(clist[i], 's');
		na = 0;
		av[na++] = NAMEccom;
		if (gflag)		/* must be first arg */
		    av[na++] = "-g";
		if (truncflag)		/* if truncating names */
		    av[na++] = "-XT";	/* pass flag */
		for (j = 0; j < nlist[Xc0]; j++)
		    av[na++] = list[Xc0][j];
		av[na++] = tmp4;
		av[na++] = oflag ? tmp5 : tmp3;
#ifdef PROFILE_SUPPORT
		if (proflag)
			av[na++] = "-XP";
#endif
		if (wflag)
			av[na++] = "-w";
		av[na] = 0;
		if (callsys(ccom, av)) {
			cflag++;
			eflag++;
			continue;
		}
		if (oflag) {
			na = 0;
			av[na++] = NAMEoptim;
			av[na++] = tmp5;
			av[na++] = tmp3;
			for (j = 0; j < nlist[Xc2]; j++)
			    av[na++] = list[Xc2][j];
			av[na] = 0;

			if (callsys(c2, av)) {
				unlink(tmp3);
				tmp3 = assource = tmp5;
			} else
				unlink(tmp5);
		}
		if (sflag)
			continue;
	assemble:
		cunlink(tmp1); cunlink(tmp2); cunlink(tmp4);
		na = 0;
		av[na++] = NAMEas;
		for (j = 0; j < nlist[Xas]; j++)
		    av[na++] = list[Xas][j];
		av[na++] = "-o";
		av[na++] = setsuf(clist[i], 'o');
		if (Rflag)
			av[na++] = "-R";
		if (dflag)
			av[na++] = dflag;
		av[na++] = assource;
		av[na] = 0;
		if (callsys(as, av) > 0) {
			cflag++;
			eflag++;
			continue;
		}
	}
nocom:
	if (cflag==0 && nl!=0) {
		i = 0;
		av[0] = NAMEld; na=1;

		if (!xflag) {
			av[na++] = "-o";
			if (outfile)
				av[na++] = outfile;
		   	else
				av[na++] = "dmda.out";

			/* -L$DMD/lib */
			av[na++] = strspl("-L", strspl(fst, LIBDIR));

			av[na++] = "-r";
			av[na++] = "-a";
			av[na++] = crt0;
		} else {
			if (outfile) {
				av[na++] = "-o";
				av[na++] = outfile;
			}
		}


		for (j = 0; j < nlist[Xld]; j++)
		    av[na++] = list[Xld][j];

		while (i < nl)
			av[na++] = llist[i++];

		if (!xflag) {
			av[na++] = "-ljx";
			av[na++] = "-lj";
			av[na++] = "-lfw";
			av[na++] = "-lc";
		}

		av[na++] = 0;

		eflag |= callsys(ld, av);
		if (nc==1 && nxo==1 && eflag==0)
			unlink(setsuf(clist[0], 'o'));
		if (eflag == 0 && debug == 0)  gosetstacksize();
	}
	dexit();
}

void
idexit()
{

	eflag = 100;
	dexit();
}

dexit()
{

	if (!pflag) {
		cunlink(tmp1);
		cunlink(tmp2);
		if (sflag==0)
			cunlink(tmp3);
		cunlink(tmp4);
		cunlink(tmp5);
	}
	exit(eflag);
}

error(s, x)
	char *s, *x;
{
	FILE *diag = exflag ? stderr : stdout;

	fprintf(diag, "dmdcc:  ");
	fprintf(diag, s, x);
	putc('\n', diag);
	exfail++;
	cflag++;
	eflag++;
}

getsuf(as)
char as[];
{
	register int c;
	register char *s;
	register int t;

	s = as;
	c = 0;
	while (t = *s++)
		if (t=='/')
			c = 0;
		else
			c++;
	s -= 3;
	if (c <= 1024 && c > 2 && *s++ == '.')
		return (*s);
	return (0);
}

char *
setsuf(as, ch)
	char *as;
{
	register char *s, *s1;

	s = s1 = savestr(as);
	while (*s)
		if (*s++ == '/')
			s1 = s;
	s[-1] = ch;
	return (s1);
}

callsys(f, v)
	char *f, **v;
{
	int t, status;
	char	**p;

	if (debug) {
		printf("callsys %s:", f);
		for (p=v; *p != NULL; p++)
			printf(" '%s'", *p);
		printf(" .\n");
		return(0);
	}

	t = fork();
	if (t == -1) {
		printf("No more processes\n");
		return (100);
	}
	if (t == 0) {
		execv(f, v);
		printf("Can't find %s\n", f);
		fflush(stdout);
		_exit(100);
	}
	while (t != wait(&status))
		;
	if ((t=(status&0377)) != 0 && t!=14) {
		if (t!=2) {
			printf("Fatal error in %s\n", f);
			eflag = 8;
		}
		dexit();
	}
	return ((status>>8) & 0377);
}

nodup(l, os)
	char **l, *os;
{
	register char *t, *s;
	register int c;

	s = os;
	if (getsuf(s) != 'o')
		return (1);
	while (t = *l++) {
		while (c = *s++)
			if (c != *t++)
				break;
		if (*t==0 && c==0)
			return (0);
		s = os;
	}
	return (1);
}

#define	NSAVETAB	1024
char	*savetab;
int	saveleft;

char *
savestr(cp)
	register char *cp;
{
	register int len;

	len = strlen(cp) + 1;
	if (len > saveleft) {
		saveleft = NSAVETAB;
		if (len > saveleft)
			saveleft = len;
		savetab = (char *)malloc(saveleft);
		if (savetab == 0) {
			fprintf(stderr, "ran out of memory (savestr)\n");
			exit(1);
		}
	}
	strncpy(savetab, cp, len);
	cp = savetab;
	savetab += len;
	saveleft -= len;
	return (cp);
}

char *
strspl(left, right)
	char *left, *right;
{
	char buf[BUFSIZ];

	strcpy(buf, left);
	strcat(buf, right);
	return (savestr(buf));
}

/* make absolute program name from path, prefix, and base program name */

char *
makename(fst, path,prefix,name)
char * fst;				/* $DMD */
char * path;				/* initial path name */
char * prefix;				/* string to prepend to name */
char * name;				/* command name, as in "ccom" */
{
    char buf[BUFSIZ];		/* for building name */

    (void) strcpy(buf,fst);		/* concatenate pieces */
    (void) strcat(buf,path);
    (void) strcat(buf,"/");
    (void) strcat(buf,prefix);
    (void) strcat(buf,name);
    return( savestr(buf) );		/* return completed string */
}

getXpass(c, opt)
char	c, *opt;
{
	switch (c) {
	default:
		error("Unrecognized pass name: '%s%c'", opt, c);
		return(-1);
	case '0':
	case '1':
	case '2':
		return(c - '0');
	case 'p':
		return(Xcp);
	case 'a':
		return(Xas);
	case 'l':
		return(Xld);
	}
}

char *
getfst()
{
	char *str;
	extern char *getenv();

	str = getenv("DMD");
	if ((str == (char *)0) || (*str == '\0'))
	{
		return(savestr(DEFDMD));
	}
	return( savestr(str) );
}



gosetstacksize()
/*  This routine opens up the load file and writes the stack size into the
 *  first long word of .data ( first word of data section of crtm.o).
 *  The stack size is either specified by the -Z option or is defaulted
 *  to MINSTACK.
 */
{


	int errflag = 0;
	char *p;
	int i;

	if (outfile) p = outfile;
	else p = "dmda.out";

	if (0 != (errflag = access(strcpy(file,p),2))) error("cannot access file to set stack size: %s", file);

	if (!errflag) {
		obj = (errflag = open(strcpy(file,p),2));
		if (obj<0)  error("cannot open file to set stack size: %s", file);
	}
/*
**	Reads the headers for the m68a.out
**	file and stores the data read into the global
**	structures declared for this purpose
**
*/

   if (errflag >= 0) {
	Read ((char *) &fileheader, sizeof(struct filehdr));
	if (fileheader.f_magic!=MC68MAGIC)
		error( "'%s' is not a MC68000 family a.out", file);


	if(!(fileheader.f_flags&F_EXEC))
		error ("%s is not an executable file",file);



	
	for (i = 0 ; i <= DATASECT; ++i) {
				
		/* make sure first 2 sections are text and data */
		Read ((char *) &secthdrs[i], sizeof(struct scnhdr));
		switch (i) {
			case TEXTSECT:
		    	if (!strequal(secthdrs[i].s_name,".text"))
			    error( "%s not in proper text, data, bss format, missing: text", file);
			break;

			case DATASECT:
	  	    	if (!strequal(secthdrs[i].s_name,".data"))
			    error( "%s not in proper text, data, bss format, missing: data", file);

	    		break;
		}
	}
	if (lseek(obj,secthdrs[DATASECT].s_scnptr,0) < 0)
		error("stack size seek error on file: %s",file);
	else if (write(obj,&stksize,sizeof(long)) < 0)
		error("stack size write error on file: %s",file);
	}
}






int
Read(a, n)
	char *a;
{
	register i;
	i=read(obj, a, n);
	if(i<0)
		error( "read error on '%s'", file);
	return(i);
}

/*  strequal compares 2 strings */

int strequal(s1,s2)
 	char s1[], s2[];
{
	int i = 0;
	while ( (s1[i] == s2[i]) && (s1[i] != '\0') 
				 && (s2[i] != '\0') )  ++i;

	if ( (s1[i] == '\0') && (s2[i] == '\0') )
		return(1);
	else
		return(0);
}


