/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)exit.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>
#define _SYSEXIT	4
#undef exit

fstx_exit()
{
	register int i;
	register FILE *f;
	if(whathost() == -1)
		exit();
	for (i = 1, f = &_iob[1]; i < _NFILE; i++, f++)
		fflush(f);
	tag(_SYSEXIT);
	jputshort(i);
	jflush();
	jgetshort();
	exit();
}
