/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)fopen.c	1.1.1.6	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>
#define _SYSOPEN	1
#define _SYSCLOSE	2
#define _SYSACCESS	8

extern char *alloc();

access(file,mode)
char *file;
{
	if(whathost() == -1)
		return(-1);
	tag(_SYSACCESS);
	jputstr(file);
	jputshort(mode);
	jflush();
	return(jgetshort());
}

FILE *
_open(file,mode,f,i)
char *file,*mode;
FILE *f;
{
	if(whathost() == -1)
		return((FILE *)NULL);
	if ((f->base = f->cp = alloc (BUFSIZ)) == NULL)
		return((FILE *) NULL);
	tag(_SYSOPEN);
	jputshort(i);
	jputstr(file);
	jputchar(*mode);
	jflush();
	if (i != jgetshort())
	{
		free(f->cp);
		return((FILE *) NULL);
	}
	f->file = i;
	if (*mode == 'r') {
		f->count = 0;
		f->flag |= _IOREAD;
	}
	else {
		f->count = BUFSIZ;
		f->flag |= _IOWRT;
	}
	return(f);
}

FILE *
fopen(file,mode)
char *file,*mode;
{
	register int i;
	register FILE *f;
	extern FILE *_lastbuf;

	for (f = _iob, i = 0; f->flag & (_IOREAD | _IOWRT); f++, i++)
		if (f >= _lastbuf)
			return((FILE *) NULL);
	return(_open(file,mode,f,i));
}

FILE *
freopen(file,mode,f)
char *file,*mode;
FILE *f;
{
	fclose(f);
	return(_open(file,mode,f,fileno(f)));
}

fclose(f)
FILE *f;
{
	int rtn = -1;
	extern char _sibuf[], _sobuf[], _sebuf[];

	if (f->flag != 0 && whathost() != -1) {
		rtn = fflush(f);
		if(f->base != _sibuf && f->base != _sobuf && f->base != _sebuf)
			free(f->base);
		f->base = f->cp = 0;
		f->flag = 0;
		tag(_SYSCLOSE);
		jputshort(fileno(f));
		jflush();
		if(jgetshort() < 0)
			rtn = -1;
	}
	return rtn;
}

