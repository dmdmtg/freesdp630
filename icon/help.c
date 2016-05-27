/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)help.c	1.1.1.3	(5/10/87)";

#include <dmd.h>
#include <font.h>
#include "icon.h"

helpline(b, i, icon, str)
Bitmap *b;
int	i;
Texture16 *icon;
char	*str;
{
	texture(b, raddp(rect16x16, Pt(16, 16 * i)), icon, F_XOR);
	string(&mediumfont, str, b, Pt(44, 16 * i), F_XOR);
}


HelpSorry()
{
	string(&mediumfont, "Not enough space on dmd",
	    &display, add(icon.corner, Pt(15, -20)), F_XOR);
}


/***********************************************************************
    This routine is called when the menu command HELP is selected.
***********************************************************************/
Help()
{
	Rectangle s;
	int overx, overy;
	Bitmap * buffer;
	buffer = balloc(Rect(0, 0, 282, 466));

	if (buffer == 0) {
		HelpSorry();
		while (!bttn123()) 
			wait(MOUSE);
		HelpSorry();
		while (bttn123()) 
			wait(MOUSE);
		return(0);
	}
	rectf(buffer, buffer->rect, F_CLR);
	Outline(buffer, Rpt(buffer->rect.origin, sub(buffer->rect.corner, Pt(1, 1))));
	helpline(buffer, 0, &white, "button 1: draw");
	helpline(buffer, 1, &white, "button 2: undraw");
	helpline(buffer, 2, &white, "");
	helpline(buffer, 3, &Cmove, "move");
	helpline(buffer, 4, &Ccopy, "copy");
	helpline(buffer, 5, &Cinvert, "invert");
	helpline(buffer, 6, &Cerase, "erase");
	helpline(buffer, 7, &Creflx, "reflect y");
	helpline(buffer, 8, &Crefly, "reflect x");
	helpline(buffer, 9, &Crotplus, "rotate +");
	helpline(buffer, 10, &Crotminus, "rotate -");
	helpline(buffer, 11, &Cshearx, "shear x");
	helpline(buffer, 12, &Csheary, "shear y");
	helpline(buffer, 13, &Cstretch, "stretch");
	helpline(buffer, 14, &Ctexture16, "duplicate");
	helpline(buffer, 15, &Cread, "read file");
	helpline(buffer, 16, &Cgrid, "background grid");
	helpline(buffer, 17, &Ccursor, "pick cursor icon");
	helpline(buffer, 18, &Cwrite, "write file");
	helpline(buffer, 19, &Cblit, "bitblit");
	helpline(buffer, 20, &Chelp, "press a button to continue");
	helpline(buffer, 21, &Cexit, "exit (confirm butt 3)");
	helpline(buffer, 22, &white, "");
	helpline(buffer, 23, &clock, "wait");
	helpline(buffer, 24, &deadmouse, "mouse inactive");
	helpline(buffer, 25, &menucursor,  "menu on button 3");
	helpline(buffer, 26, &sweepcursor, "sweep rect (butt 3)");
	helpline(buffer, 27, &sweeportrack, "sweep rect (butt 3) or");
	helpline(buffer, 28, &white, "get 16x16 frame (butt 2)");
	s = raddp(buffer->rect, add(Drect.origin, Pt(5, 5)));
	if ((overx=s.origin.x - 518) > 0)
		s.origin.x = s.origin.x - overx;
	if ((overy=s.origin.y - 558) > 0)
		s.origin.y = s.origin.y - overy;
	screenswap(buffer, buffer->rect, s);
	while (!bttn123()) ;
	screenswap(buffer, buffer->rect, s);
	while (bttn123()) ;
	bfree(buffer);
}

