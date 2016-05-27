/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)jelarc.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
extern Point transform();
void
jelarc(p0, a, b, p1, p2, f)
	Point p0, p1, p2;
	int a, b, f;
{
	elarc(&display, transform(p0),
		muldiv(a, Drect.corner.x-Drect.origin.x, XMAX),
		muldiv(b, Drect.corner.y-Drect.origin.y, YMAX),
		transform(p1), transform(p2), f);
}
