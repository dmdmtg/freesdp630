/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)gcalloc.c	1.1.1.1	(5/10/87)";

#include <dmd.h>

char *realgcalloc();

char *
gcalloc(n, p)
long n;
char **p;
{
	return( realgcalloc(n, p, P) );
}

