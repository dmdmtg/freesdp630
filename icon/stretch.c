/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */



static char _2Vsccsid[]="@(#)stretch.c	1.1.1.1	(5/8/87)";

#include <dmd.h>
#include "icon.h"

Stretch(sb, sr, db, dr, op)
Bitmap *sb, *db;
Rectangle sr, dr;
Code op;
{
	int	i, j, shsize, svsize, dhsize, dvsize;
	shsize = horsize(sr);
	svsize = versize(sr);
	dhsize = horsize(dr);
	dvsize = versize(dr);
	for (j = 0; j < svsize; j++)
		for (i = 0; i < shsize; i++)
			bitblt(sb,
			    Rect(sr.origin.x + i, sr.origin.y + j, sr.origin.x + i + 1, sr.origin.y + j + 1),
			    db,
			    Pt(dr.origin.x + muldiv(dhsize, i, shsize),
			    dr.origin.y + muldiv(dvsize, j, svsize)),
			    op);
}


/***********************************************************************
    This routine is called when the menu command STRETCH is selected.
***********************************************************************/
OpStretch()
{
	Bitmap * buffer;
	Rectangle source, dest;
	if (GetIconRect(&source) == 0) 
		return(0);
	if ((horsize(source) == 0) || (versize(source) == 0)) 
		return(0);
	if (GetIconRect(&dest) == 0) 
		return(0);
	if ((horsize(dest) == 0) || (versize(dest) == 0)) 
		return(0);
	buffer = balloc(dest);
	if (buffer == ((Bitmap * ) 0)) 
		return(0);
	rectf(buffer, buffer->rect, F_CLR);
	Stretch(&display, raddp(source, icon.origin), buffer, buffer->rect, F_XOR);
	IconBitBlit(source, source.origin, Rect(0, 0, 0, 0), F_CLR, F_CLR);
	FetchIcon(buffer, buffer->rect, dest.origin, dest);
	bfree(buffer);
}

