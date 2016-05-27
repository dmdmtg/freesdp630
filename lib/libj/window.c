/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)window.c	1.1.1.2	(5/8/87)";


#include <dmd.h>

reshape(r)
Rectangle r;
{
/*
 * reshape the window. return value =
 *   1 - success
 *   0 - failure
 *   none - deleted
 */
	int retval;

	if(rectclip(&r, Rect(6, 6, XMAX-6, YMAX-6)))
		retval = _reshape(P->layer, r);
	if(retval == -2) /* I was deleted */
		sw(0);
	if(retval < 0) /* failure */
		retval = 0;
	return(retval);
}

move(p)
Point p;
{
/*
 * move the window. return value =
 *   1 - success
 *   0 - failure
 */
	if(p.x < 6) /* make sure it is on screen */
		p.x = 6;
	if(p.y < 6) /* make sure it is on screen */
		p.y = 6;
	/* _move takes care of the corner */
	return(_move(P->layer, p));
}

void
top()
{ /* put window on top */
	upfront(P->layer);
}

void
bottom()
{ /* put window on bottom */
	downback(P->layer);
}

void
current()
{ /* make window current */
	toproc(P);
}

void
delete()
{ /* delete window (and process) */
	if(!last_window(P->host))
	{
		_delete(P);
		sw(0);
	}
}


