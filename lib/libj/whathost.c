/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)whathost.c	1.1.1.2	(5/8/87)";


#include <dmd.h>

whathost()
{
	if(P->host == (struct Logio *)0)
		return(-1);
	else
		return(_whathost());
}
