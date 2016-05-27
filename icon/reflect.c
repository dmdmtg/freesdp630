/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */



static char _2Vsccsid[]="@(#)reflect.c	1.1.1.1	(5/8/87)";

#include <dmd.h>
#include "icon.h"

extern bool geticonpoint();

/***********************************************************************
    This routine is called when the menu command REFLECTY is selected.
    The region selected is flipped about the y-axis.  
***********************************************************************/
OpReflY()
{
	Rectangle r;
	int	i, j;
	bool bit1, bit2;
	if (GetIconRect(&r) == 0) 
		return(0);
	for (i = r.origin.x; i < r.corner.x; i += 1)
		for (j = 0; j < (versize(r) / 2); j += 1) {
			bit1 = geticonpoint(Pt(i, r.origin.y + j));
			bit2 = geticonpoint(Pt(i, r.corner.y - 1 - j));
			IconOp(bit1, Pt(i, r.corner.y - 1 - j), I_STORE);
			IconOp(bit2, Pt(i, r.origin.y + j), I_STORE);
		}
}


/***********************************************************************
    This routine is called when the menu command REFLECTX is selected.
    The region selected is flipped about the x-axis.  
***********************************************************************/
OpReflX()
{
	Rectangle r;
	int	i, j;
	bool bit1, bit2;
	if (GetIconRect(&r) == 0) 
		return(0);
	for (i = 0; i < (horsize(r) / 2); i += 1)
		for (j = r.origin.y; j < r.corner.y; j += 1) {
			bit1 = geticonpoint(Pt(r.origin.x + i, j));
			bit2 = geticonpoint(Pt(r.corner.x - 1 - i, j));
			IconOp(bit1, Pt(r.corner.x - 1 - i, j), I_STORE);
			IconOp(bit2, Pt(r.origin.x + i, j), I_STORE);
		}
}

