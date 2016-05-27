/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)jdisc.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
extern Point transform();

void
jdisc(p, r, f)
	Point p;
{
	eldisc( &display, transform(p),
		muldiv(r, Drect.corner.x-Drect.origin.x, XMAX),
		muldiv(r, Drect.corner.y-Drect.origin.y, YMAX), f);
}
