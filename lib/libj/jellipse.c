/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)jellipse.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
extern Point transform();
void
jellipse(p,a,b,f)
	Point p;
	int a, b, f;
{
	ellipse(&display, transform(p),
		muldiv(a, Drect.corner.x-Drect.origin.x, XMAX),
		muldiv(b, Drect.corner.y-Drect.origin.y, YMAX),
		f);
}
