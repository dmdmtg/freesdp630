/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */



static char _2Vsccsid[]="@(#)utility.c	1.1.1.1	(5/8/87)";

#include <dmd.h>
#include "icon.h"

int	horsize(r)
Rectangle r;
{
	return(r.corner.x - r.origin.x);
}


int	versize(r)
Rectangle r;
{
	return(r.corner.y - r.origin.y);
}



int	pttopt(p, q)
/* manhattan topology distance between two points */
Point p, q;
{
	return(abs(p.x - q.x) + abs(p.y - q.y));
}

Outline(b, r)
Bitmap *b;
Rectangle  r;
{
	segment(b, r.origin, Pt(r.origin.x, r.corner.y), F_XOR);
	segment(b, Pt(r.origin.x, r.corner.y), r.corner, F_XOR);
	segment(b, r.corner, Pt(r.corner.x, r.origin.y), F_XOR);
	segment(b, Pt(r.corner.x, r.origin.y), r.origin, F_XOR);
}

border(r)
Rectangle r;
{
	Outline(&display, inset(r, 1));
	Outline(&display, inset(r, -1));
}
