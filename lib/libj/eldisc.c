/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)eldisc.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
/* pandora function - lrectf */
/* pandora function - lsegment */

/*static*/ int yaxis;
/*static*/ int xaxis;
/*static*/ Point lp;

static void
scan(bp, p, f)
	Bitmap *bp;
	Point p;
	Code f;
{
	register x, y;

	if((p.y != lp.y) && (lp.y != -1))
	{
		x = xaxis - lp.x;
		y = yaxis - lp.y;
		lrectf(bp, Rect(lp.x, lp.y, x+1, lp.y+1), f);
		lrectf(bp, Rect(lp.x, y, x+1, y+1), f);
	}
	lp = p;
}
void
eldisc(bp, p, a, b, f)
	Bitmap *bp;
	Point p;
	int a, b;
	Code f;
{
	register x0 = p.x;
	register y0 = p.y;

	yaxis = 2*p.y;
	xaxis = 2*p.x;
	lp.y = -1;

	if(f!=F_XOR)
		cursinhibit();
	if(a==0 || b==0)
		lsegment(bp, Pt(x0-a,y0-b), Pt(x0+a,y0+b), f);
	else
	{
		lrectf(bp, Rect(p.x-a, p.y, p.x+a+1, p.y+1), f);
		ellip1(bp, p, a, b, scan, Pt(0, -b), Pt(-a, 0), f);
		scan(bp, Pt(0, -1), f);
	}
	if(f!=F_XOR)
		cursallow();
}
