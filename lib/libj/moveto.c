/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)moveto.c	1.1.1.1	(5/10/87)";

/* moveto.c
**
** This file contains routines for dealing with P->scurpt. P->scurpt is
** similar to PtCurrent in that it is a global variable to hold screen
** location. P->scurpt, however, works in screen coordinates rather than
** layer coordinates. The problem with storing in layer coordinates is
** that there is rounding errors when converting from layer to screen
** coordinates - which is necessary because all of the firmware primities
** like bitblt and segment actually use screen coordinates. P->scurpt is
** intended for use by routines that want to work completely in screen
** coordinates to avoid rounding error. The first library routine to use
** this is printf - someday there will probably be others.
** 
** P->scurpt is actually stored as an offset from Drect.origin. Storing in
** this format has the advantage of making MOVE transparent to routines
** that use P->scurpt.
*/

#include <dmd.h>

extern Point sub();
extern Point add();

/* Set when moveto is executed. Applications which use sPtCurrent can look
** at this variable to see if they must initialize. This will not work
** for second invocations of shared text applications - they will
** have to call moveto explicitly to initialize.
*/
int didmoveto;

/* moveto
**
** Set P->scurpt to an offset from Drect.origin in screen coordinates.
*/
moveto(p)
Point p;
{
	P->scurpt = sub(p, Drect.origin);
	didmoveto = 1;
}

/* sPtCurrent
**
** Returns P->scurpt in absolute screen coordinates. Checks to be sure the
** point is within Drect, which may not be true if the layer was reshaped
** smaller.
** 
** It would be nice if we could always detect reshape here, but we cannot,
** because we must leave the power to look at and reset RESHAPED to
** applications. So, if the layer is reshaped and p is still within
** Drect, we cannot tell that a reshape occurred. The current point will
** simply end up in the relative area of the layer where it was before
** the reshape. If an application wants to do a better job than this, it
** should watch RESHAPED and call moveto after reshape.
*/
Point
sPtCurrent()
{
	Point p;

	p = add(P->scurpt, Drect.origin);

	if( !ptinrect(p, Drect) )
		p = Drect.origin;

	return(p);
}
