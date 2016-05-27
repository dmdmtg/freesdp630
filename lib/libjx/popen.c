/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)popen.c	1.1.1.6	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>
#define _SYSPOPEN	6
#define _SYSPCLOSE	7

extern char *alloc();

FILE *
popen(s,mode)
char *s,*mode;
{
	register int i;
	register FILE *f;
	extern FILE *_lastbuf;
	if(whathost() == -1)
		return((FILE *)0);
	for (f = _iob, i = 0; f->flag & (_IOREAD | _IOWRT); f++, i++)
		if (f >= _lastbuf)
			return((FILE *)0);
	f->cp = f->base = alloc (BUFSIZ);
	if (f->base == NULL)
		return ((FILE *) NULL);
	tag(_SYSPOPEN);
	jputshort(i);
	jputstr(s);
	jputchar(*mode);
	jflush();
	if (i != jgetshort())
	{
		free(f->cp);
		return((FILE *)0);
	}
	f->file = i;
	if (*mode == 'r') {
		f->count = 0;
		f->flag = _IOREAD;
	}
	else {
		f->count = BUFSIZ;
		f->flag = _IOWRT;
	}
	return(f);
}

pclose(f)
FILE *f;
{
	extern char _sibuf[], _sobuf[], _sebuf[];

	if(whathost() == -1)
		return(-1);
	fflush(f);
	if(f->base != _sibuf && f->base != _sobuf && f->base != _sebuf)
		free(f->base);
	f->cp = f->base = NULL;
	f->flag = 0;
	tag(_SYSPCLOSE);
	jputshort(fileno(f));
	jflush();
	return(jgetshort());
}

