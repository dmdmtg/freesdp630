/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)printf.c	1.1.1.4	(5/9/87)";


#include <dmdio.h>

Printf(format, args)
char *format;
char *args;
{
	if(whathost() == -1)
		return(0);
	return _Doprnt(stdout, format, &args);
}

Fprintf(f, format, args)
FILE *f;
char *format;
char *args;
{
	if(whathost() == -1)
		return(0);
	return _Doprnt(f, format, &args);
}


