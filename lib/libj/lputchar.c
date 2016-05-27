/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)lputchar.c	1.1.1.2	(5/10/87)";

/*
** FUNCTION:	lputchar
**
** SYNOPSIS:	lputchar(c)
**
** See comments in lprintf.c
*/ 

/* This currently always uses largefont. I would prefer to use the font set
** in setup, but there is currently no way to determine this.
*/
 
#include <dmd.h>
#include <font.h>

#define  DO		Drect.origin
#define  DC		Drect.corner

extern int didmoveto;	/* defined in moveto.c */
extern Point string();

lputchar (c)
register char c;
{
	char s[2];
	Point curpos;
	register int num, more;
	extern Point sPtCurrent();

	/* Initialize sPtCurrent if necessary */
	curpos = sPtCurrent();
	if(!didmoveto || !ptinrect(curpos, Rpt(DO, Pt(DC.x -
	   FONTWIDTH(largefont), DC.y - FONTHEIGHT(largefont)))))
	{
		moveto(Drect.origin);
		curpos = sPtCurrent();
	}

	c &= 0x7f;  /* protect against bad arguments */
	s[0] = c;
	s[1] = '\0';

	switch (c) {

	case '\n' :	/* newline */
		if ( (curpos.y + (2 * FONTHEIGHT(largefont)) ) > DC.y )
			lputchar_scroll(DC.y - curpos.y);
		else
			curpos.y += FONTHEIGHT(largefont);
		/* no break */

	case '\r' :	/* carriage return */
		curpos.x = DO.x;
		break;

	case '\t' :	/* tab */
		num = (curpos.x - DO.x)/FONTWIDTH(largefont);
		more = (num|7) + 1 - num;
		while (more--)
			lputchar(' ');
		curpos = sPtCurrent();
		break;

	default:
		curpos = string(&largefont, s, &display, curpos, F_STORE);
		if(curpos.x + FONTWIDTH(largefont) >= DC.x) {
			lputchar('\n');
			curpos = sPtCurrent();
		}
		break;
	}

	moveto(curpos);
}

lputchar_scroll(n)
short n;
{
	Rectangle s;

	s = Drect;
	s.origin.y += FONTHEIGHT(largefont);
	bitblt (&display, s, &display, DO, F_STORE);
	rectf (&display, Rect(DO.x, DC.y-n, DC.x, DC.y), F_CLR);
}
