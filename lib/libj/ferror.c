/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)ferror.c	1.1.1.1	(5/10/87)";

#include <dmd.h>

ferror(s1,s2,crash)
 	char *s1,*s2;
	int crash;
{
	if (crash) {
		strcat(s1,s2);
		showerror(P,s1);
	}
	else
		tell_excep(P->layer,s1,s2);
}
