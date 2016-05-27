/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */



static char _2Vsccsid[]="@(#)shear.c	1.1.1.1	(5/8/87)";

#include <dmd.h>
#include "icon.h"

Point nearestcorner(r, p)
Rectangle r;
Point p;
{
	int	mindist, dist;
	Point minq, q;
	q = r.origin;
	mindist = pttopt(p, q); 
	minq = q;
	q.x = r.origin.x; 
	q.y = r.corner.y;
	if ((dist = pttopt(p, q)) < mindist) {
		mindist = dist; 
		minq = q;
	}
	q = r.corner;
	if ((dist = pttopt(p, q)) < mindist) {
		mindist = dist; 
		minq = q;
	}
	q.x = r.corner.x; 
	q.y = r.origin.y;
	if ((dist = pttopt(p, q)) < mindist) {
		mindist = dist; 
		minq = q;
	}
	return(minq);
}


horshear(b, r, dx, top)
Bitmap *b;
Rectangle r;
int	dx;
bool top;
{
	int	i, j, hsize, vsize, shift;
	bool bit, dir;
	hsize = horsize(r);
	vsize = versize(r);
	dir = (dx > 0);
	/* replaced by a pixel by pixel move because of a bug in bitblt!
   for (j=0; j<vsize; j++) {
     shift = top ? vsize-j-1 : j;
     bitblt(b,Rect(r.origin.x,r.origin.y+j,r.corner.x,r.origin.y+j+1),
             b,Pt(r.origin.x+muldiv(shift,dx,vsize),r.origin.y+j),
             F_STORE);
   }
*/
	for (j = 0; j < vsize; j++) {
		shift = top ? vsize - j - 1 : j;
		shift = muldiv(shift, dx, vsize);
		for (i = (dir ? hsize - 1 : 0); (dir ? i >= 0 : i < hsize); (dir ? i-- : i++)) {
			bit = bitmapbit(b, Pt(r.origin.x + i, r.origin.y + j));
			if (bit) 
				point(b, Pt(r.origin.x + i + shift, r.origin.y + j), F_STORE);
			else 
				point(b, Pt(r.origin.x + i + shift, r.origin.y + j), F_CLR);
		}
	}
}


vershear(b, r, dy, lft)
Bitmap *b;
Rectangle r;
int	dy;
bool lft;
{
	int	i, j, hsize, vsize, shift;
	bool bit, dir;
	hsize = horsize(r);
	vsize = versize(r);
	dir = (dy > 0);
	/* replaced by a pixel by pixel move because of a bug in bitblt!
   for (i=0; i<hsize; i++) {
     shift = lft ? hsize-i-1 : i;
     bitblt(b,Rect(r.origin.x+i,r.origin.y,r.origin.x+i+1,r.corner.y),
             b,Pt(r.origin.x+i,r.origin.y+muldiv(shift,dy,hsize)),
             F_STORE);
   }
*/
	for (i = 0; i < hsize; i++) {
		shift = lft ? hsize - i - 1 : i;
		shift = muldiv(shift, dy, hsize);
		for (j = (dir ? vsize - 1 : 0); (dir ? j >= 0 : j < vsize); (dir ? j-- : j++)) {
			bit = bitmapbit(b, Pt(r.origin.x + i, r.origin.y + j));
			if (bit) 
				point(b, Pt(r.origin.x + i, r.origin.y + j + shift), F_STORE);
			else 
				point(b, Pt(r.origin.x + i, r.origin.y + j + shift), F_CLR);
		}
	}
}


HorShear(r, dx, top)
Rectangle r;
int	dx;
bool top;
{
	int	j, vsize, shift;
	vsize = versize(r);
	for (j = 0; j < vsize; j++) {
		shift = top ? vsize - j - 1 : j;
		IconBitBlit(Rect(r.origin.x, r.origin.y + j, r.corner.x, r.origin.y + j + 1),
		    Pt(r.origin.x + muldiv(shift, dx, vsize), r.origin.y + j),
		    Rect(0, 0, Xblocks, Yblocks),
		    I_CLR, I_OR);
	}
}


VerShear(r, dy, lft)
Rectangle r;
int	dy;
bool lft;
{
	int	i, hsize, shift;
	hsize = horsize(r);
	for (i = 0; i < hsize; i++) {
		shift = lft ? hsize - i - 1 : i;
		IconBitBlit(Rect(r.origin.x + i, r.origin.y, r.origin.x + i + 1, r.corner.y),
		    Pt(r.origin.x + i, r.origin.y + muldiv(shift, dy, hsize)),
		    Rect(0, 0, Xblocks, Yblocks),
		    I_CLR, I_OR);
	}
}


/***********************************************************************
    This routine is called when the menu command SHEARX is selected.
***********************************************************************/
OpHorShear()
{
	Rectangle r;
	int	dx;
	bool top;
	Point p, nearcorner;
	if (GetIconRect(&r) == 0) 
		return(0);
	if ((horsize(r) == 0) || (versize(r) == 0)) 
		return(0);
	if (!GetIconPoint(&p)) 
		return(0);
	nearcorner = nearestcorner(r, p);
	dx = p.x - nearcorner.x;
	top = (nearcorner.y == r.origin.y);
	HorShear(r, dx, top);
}


/***********************************************************************
    This routine is called when the menu command SHEARY is selected.
***********************************************************************/
OpVerShear()
{
	Rectangle r;
	int	dy;
	bool lft;
	Point p, nearcorner;
	if (GetIconRect(&r) == 0) 
		return(0);
	if ((horsize(r) == 0) || (versize(r) == 0)) 
		return(0);
	if (!GetIconPoint(&p)) 
		return(0);
	nearcorner = nearestcorner(r, p);
	dy = p.y - nearcorner.y;
	lft = (nearcorner.x == r.origin.x);
	VerShear(r, dy, lft);
}

