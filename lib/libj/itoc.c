/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)itoc.c	1.1.1.1	(5/10/87)";

#include <dmd.h>

char *itoc();

char *
itoo(n, s)
long n;
char *s;
{
	itoc(n, s, 8);
}

char *
itoa(n, s)
long n;
char *s;
{
	itoc(n, s, 10);
}

char *
itox(n, s)
long n;
char *s;
{
	itoc(n, s, 16);
}

