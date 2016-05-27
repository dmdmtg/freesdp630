/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)rdwr.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>

fread(ptr, size, count, iop)
unsigned size, count;
register char *ptr;
register FILE *iop;
{
	register c;
	unsigned ndone, s;

	if(size <= 0 || count <= 0 || (iop->flag&_IOREAD) != _IOREAD)
		return(0);
	ndone = 0;
	for (; ndone<count; ndone++) {
		s = size;
		do {
			if ((c = getc(iop)) >= 0)
				*ptr++ = c;
			else
				return(ndone);
		} while (--s);
	}
	return(ndone);
}

fwrite(ptr, size, count, iop)
unsigned size, count;
register char *ptr;
register FILE *iop;
{
	register unsigned s;
	unsigned ndone;

	if(size <= 0 || count <= 0 || (iop->flag&_IOWRT) != _IOWRT)
		return(0);
	ndone = 0;
	for (; ndone<count; ndone++) {
		s = size;
		do {
			if(putc(*ptr++, iop) == -1)
				return(ndone);
		} while (--s);
	}
	return(ndone);
}
