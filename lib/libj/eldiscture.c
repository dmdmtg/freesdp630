/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)eldiscture.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
/* pandora function - ltexture */
/* pandora function - lsegment */

/*static*/ int yaxis;
/*static*/ int xaxis;
/*static*/ Point lp;

Texture16 *tfill;

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
		ltexture(bp, Rect(lp.x, lp.y, x+1, lp.y+1), tfill, f);
		ltexture(bp, Rect(lp.x, y, x+1, y+1), tfill, f);
	}
	lp = p;
}
void
eldiscture(bp, p, a, b, t, f)
	Bitmap *bp;
	Point p;
	int a, b;
	Texture16 *t;
	Code f;
{
	register x0 = p.x;
	register y0 = p.y;

	tfill = t;

	yaxis = 2*p.y;
	xaxis = 2*p.x;
	lp.y = -1;

	if(f!=F_XOR)
		cursinhibit();
	if(a==0 || b==0)
		lsegment(bp, Pt(x0-a,y0-b), Pt(x0+a,y0+b), f);
	else
	{
		ltexture(bp, Rect(p.x-a, p.y, p.x+a+1, p.y+1), t, f);
		ellip1(bp, p, a, b, scan, Pt(0, -b), Pt(-a, 0), f);
		scan(bp, Pt(0, -1), f);
	}
	if(f!=F_XOR)
		cursallow();
}
