/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */



static char _2Vsccsid[]="@(#)rotate.c	1.1.1.1	(5/8/87)";

#include <dmd.h>
#include "icon.h"

/***********************************************************************
    This routine is called when the menu command ROTATEPLUS is selected.
    The region selected is rotated 90 degress clockwise.  
***********************************************************************/
OpRotPlus()
{
	int	vsize, hsize, size;
	Rectangle r, rbuf;
	Bitmap * buffer;
	if (GetIconRect(&r) == 0) 
		return(0);
	hsize = horsize(r); 
	vsize = versize(r); 
	size = hsize + vsize;
	buffer = balloc(Rect(0, 0, size, size));
	if (buffer == ((Bitmap * ) 0)) 
		return(0);
	rectf(buffer, buffer->rect, F_CLR);
	rbuf = rsubp(r, r.origin);
	bitblt(&display, raddp(r, icon.origin), buffer, rbuf.origin, F_XOR);
	horshear(buffer, rbuf, vsize, true);
	vershear(buffer,
	    Rect(rbuf.origin.x, rbuf.origin.y, rbuf.corner.x + vsize, rbuf.corner.y),
	    size, false);
	horshear(buffer,
	    Rect(rbuf.origin.x, rbuf.corner.y - 1,
	    rbuf.corner.x + vsize, rbuf.corner.y + hsize - 1),
	    -hsize, false);
	Erase(r);
	FetchIcon(buffer,
	    Rect(rbuf.origin.x, rbuf.corner.y - 1,
	    rbuf.origin.x + vsize, rbuf.corner.y + hsize - 1),
	    add(r.origin, sub(Pt(hsize / 2, vsize / 2), Pt(vsize / 2, hsize / 2))),
	    Rect(0, 0, Xblocks, Yblocks));
	bfree(buffer);
}


/***********************************************************************
    This routine is called when the menu command ROTATEMINUS is selected.
    The region selected is rotated 90 degress counterclockwise.  
***********************************************************************/
OpRotMinus()
{
	int	vsize, hsize, size;
	Rectangle r, rbuf;
	Bitmap * buffer;
	if (GetIconRect(&r) == 0) 
		return(0);
	hsize = horsize(r); 
	vsize = versize(r); 
	size = hsize + vsize;
	buffer = balloc(Rect(0, 0, size, size));
	if (buffer == ((Bitmap * ) 0)) 
		return(0);
	rectf(buffer, buffer->rect, F_CLR);
	rbuf = raddp(r, sub(Pt(vsize, 0), r.origin));
	bitblt(&display, raddp(r, icon.origin), buffer, rbuf.origin, F_XOR);
	horshear(buffer, rbuf, -vsize, true);
	vershear(buffer,
	    Rect(rbuf.origin.x - vsize, rbuf.origin.y, rbuf.corner.x, rbuf.corner.y),
	    size, true);
	horshear(buffer,
	    Rect(rbuf.origin.x - vsize, rbuf.corner.y - 1,
	    rbuf.corner.x, rbuf.corner.y + hsize - 1),
	    hsize, false);
	Erase(r);
	FetchIcon(buffer,
	    Rect(rbuf.corner.x - vsize, rbuf.corner.y - 1,
	    rbuf.corner.x, rbuf.corner.y + hsize - 1),
	    add(r.origin, sub(Pt(hsize / 2, vsize / 2), Pt(vsize / 2, hsize / 2))),
	    Rect(0, 0, Xblocks, Yblocks));
	bfree(buffer);
}

