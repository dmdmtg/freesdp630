/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Tmenu9.c	1.1.1.1	(5/12/87)";

#include	<dmd.h>
#include	<font.h>
#include	<menu.h>

/* Library Routines and associated manual page. */
Point add();		/* PTARITH(3R)		*/
void exit();            /* EXIT(3R)             */
void rectf();		/* RECTF(3R)		*/
int request();          /* RESOURCES(3R)        */
void sleep();           /* SLEEP(3R)            */
char *strcpy();		/* STRING(3L)		*/
Point string();		/* STRING(3R)		*/
Titem *tmenuhit();      /* TMENUHIT(3R)         */
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.   */
/*int button1();           BUTTONS(3R)          */
/*int button2();           BUTTONS(3R)          */
/*int button3();           BUTTONS(3R)          */
/*Point Pt();		   PT(3L)		*/

void dfn(), bfn(), hfn();
extern Tmenu dmenu;

Titem ms[] =
{
	"0", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"1", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"2", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"3", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"4", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"5", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"6", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"7", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"8", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	"9", 0, 0, &dmenu, 0, 0, dfn, bfn, hfn,
	0
};
Tmenu dmenu = { ms };
char digs[64], result[64];
int store;
int ndig = 0;

main()
{
	Point p;

	request(MOUSE);
	while (wait(MOUSE))
		if (button1())
			exit();
		else if (button2()) {
			store = 1;
			if (tmenuhit(&dmenu, 2, 0)) {
				rectf(&display, Drect, F_CLR);
				p = add(Drect.origin, Pt(8,8));
				string(&largefont, result, &display,
					p, F_XOR);
			}
                } else if (button3()) {
                        /*
                        ** Release ownership of the mouse and
                        ** sleep for two ticks of the 60Hz clock
                        ** to let the control process take care
                        ** processing button 3 of the mouse.
                        */
                        request(0);
                        sleep(2);
                        /*
                        ** Back on the "air," get the mouse back.
                        */
                        request(MOUSE);
		}
}

void
dfn(mi)
	register Titem *mi;
{
	store = 1;
	digs[ndig++] = mi->text[0];
	digs[ndig] = 0;
}

void
bfn(mi)
	register Titem *mi;
{
	digs[--ndig] = 0;
}

void
hfn(mi)
	register Titem *mi;
{
	if (store)
	{
		dfn(mi);
		strcpy(result, digs);
		bfn(mi);
		store = 0;
	}
}
