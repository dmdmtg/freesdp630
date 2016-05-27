/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)string.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
#include "defines.h"
#include "globals.h"

/* This file contains functions used in updating the alpha field */



/* Display a message in the alpha field.
** Every time a new string is displayed, its rightmost x coordinate
** is remembered, so the next display will blank the necessary only.
*/
void
setstrg (s)
char *s;
{
	register x = Drect.origin.x + VINSET;
	register y = Drect.origin.y + (YSET+CH+SEP);
	Point p;
	static int Ipt = 0;	/* so we don't erase more than we should */
	Point string();


	rectf (&display, Rect(x,y,min(Drect.corner.x, x+Ipt),y+CH), F_CLR);
	p = string (&mediumfont, s, &display, Pt(x,y), F_XOR);
	Ipt = p.x - x;
}


/* Display the information how to drag a vertical bar */
void
dragstrg ()
{
	setstrg ("drag and set with button 1");
}


/* Display the information how to pick a layer */
void
pickstrg ()
{
	setstrg ("click and pick a window with button 2");
}




/* Display the view string and the number of bytes per pixel.
** This string is displayed on initializing the display.
*/
void
scopestrg ()
{
	char s[50];
	register char *u;
	register n;

	u = (CoreStart==(long)memstartp&&CoreEnd==(long)memendp) ? "full" : "scoped";
	n = stradd (s, u);
	n += stradd (&s[n], " view: ~");
	u = ltoa ((CoreSpan/BARL), CoreBase);
	n += stradd (&s[n], u);
	stradd (&s[n], " bytes/pixel");
	setstrg (s);
}


/* Add the second string to the first string and returns the length of the second string
*/
stradd (s1, s2)
char *s1, *s2;
{
	strcpy (s1, s2);
	return (strlen(s2));
}
