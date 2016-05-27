/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)vsterm1.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include <font.h>

/* Library Routines and associated manual page. */
Point add();		/* PTARITH(3R)		*/
Point fPt();		/* fPt(3L)		*/
void lputchar();	/* LPUTCHAR(3L)		*/
void moveto();		/* MOVETO(3L)		*/
int own();		/* RESOURCES(3R)        */
void rectf();		/* RECTF(3R)		*/
int request();		/* RESOURCES(3R)	*/
void ringbell();	/* RINGBELL(3R)		*/
Point sPtCurrent();     /* MOVETO(3L)           */
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.	*/
/* int FONTWIDTH	   STRING(3R)		*/
/* int FONTHEIGHT	   STRING(3R)		*/

/* Local routines in this file */
void init_screen();
void cursor();
void dispchar();


main()
{
	/*
	** Initialize the current screen point and
	** draw a cursor.
	*/
	init_screen();

	/*
	** Request the RCV resource.
	*/
	request(RCV);

	/*
	** Main loop of program.
	*/
	for (;;) {
		/*
		** Wait for chars from host.
		*/
		wait(RCV);

		if (own() & RCV) {
			/*
			** Erase the current cursor.
			*/
			cursor();

			/*
			** Display characters received.
			*/
			dispchar();

			/*
			** Redraw cursor.
			*/
			cursor();
		}
	}
}

void
init_screen()
{
	Point p;

	p = Drect.origin;
	p.y += 3;
	/*
	** Initialize the current screen point.
	*/
	moveto(p);
	cursor();
}

void
cursor()
{
	/*
	** This routine is used to draw and erase the cursor.
	*/
	Rectangle r;
	extern Point sPtCurrent();
	extern Point add();
	extern Point fPt();

	/*
	** Set dimension and position of cursor Rectangle.
	*/
	r.origin = sPtCurrent();
	r.corner = add(r.origin, fPt(FONTWIDTH(mediumfont),FONTHEIGHT(mediumfont)));
	/*
	** the following rectf will erase the cursor if it already exists
	** and draw it if it does not.
	*/
	rectf(&display, r, F_XOR);
}

void
dispchar()
{
	register int c;
	Point curpos;

	/*
	** Process all characters received.
	*/
	while ( own() & RCV ) {
		switch(c = rcvchar()) {

		case '\007':
			ringbell();
			break;

		case '\b' :	/* backspace */
			curpos = sPtCurrent();
			if(curpos.x - FONTWIDTH(largefont) >= Drect.origin.x)
				curpos.x -= FONTWIDTH(largefont);
			moveto(curpos);
			break;

		default:
			lputchar(c);
			break;
		}
	}
}
