/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Pt.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
/*
 * These routines are here only for 5620 compatability.
 */

Point
fPt(x,y)
short x,y;
{
        Point p;
        p.x = x;
        p.y = y;
        return(p);
}

Rectangle
fRpt(p,q)
Point p,q;
{
        Rectangle r;
        r.origin = p;
        r.corner = q;
        return(r);
}

Rectangle
fRect(a,b,c,d)
short a,b,c,d;
{
	Rectangle r;
	r.origin = fPt(a,b);
	r.corner = fPt(c,d);
	return(r);
}

