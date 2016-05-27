/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)get.c	1.1.1.5	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>
#define _SYSREAD	5

getchar()
{
	return(getc(stdin));
}

getc(f)
register FILE *f;
{
	register int c;

	if(whathost() == -1)
		return(-1);
	if (f->count == 0) {
		f->count = _read(fileno(f),f->base,BUFSIZ);
		if (f->count == 0)
		{
			f->flag |= _IOEOF;
			return(EOF);
		}
		if(f->count == -1)
		{
			f->flag |= _IOERR;
			return(EOF);
		}
		f->cp = f->base;
	}
	f->count--;
	c = *f->cp++;
	c &= 0xff;
	return(c);
}

_read(i,buf,n)
char *buf;
{
	if(whathost() == -1)
		return(-1);
	tag(_SYSREAD);
	jputshort(i);
	jflush();
	return(jgetbuf(buf,n));
}
