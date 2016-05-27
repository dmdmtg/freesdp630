/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)mouse.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <font.h>

#define FW FONTWIDTH(largefont)		/* See Maunal Page STRING(3R)	*/
#define FH FONTHEIGHT(largefont)	/* See Maunal Page STRING(3R)   */

/* List of routines and associated manual page 	*/
Point add();			/* PTARITH(3R)	*/
void box();			/* BOX(3R)	*/
Point fPt();			/* fPt(3L)	*/
Rectangle fRpt();		/* fPt(3L)	*/
int eqpt();			/* EQ(3R)	*/
void lprintf();			/* LPRINTF	*/
void moveto();			/* MOVETO(3R)	*/
int own();			/* RESOURCES(3R)*/
Rectangle raddp();		/* RECTARITH(3R)*/
void rectf();			/* RECTF(3R)	*/
unsigned long realtime();	/* REALTIME(3R) */
int request();			/* RESOURCES(3R)*/
Point sub();			/* PTARITH(3R)	*/
Point sPtCurrent();		/* MOVETO(3L)	*/
int wait();			/* RESOURCES(3R)*/

/*Library macros and associated manual pages	*/
/* int button()			   BUTTONS(3R)	*/
/* int button1()		   BUTTONS(3R)	*/
/* int button2()		   BUTTONS(3R)	*/
/* int button3()		   BUTTONS(3R)	*/
/* int button12()		   BUTTONS(3R)	*/
/* int button13()		   BUTTONS(3R)	*/
/* int button23()		   BUTTONS(3R)	*/
/* int button123()		   BUTTONS(3R)	*/
/* int bttn()			   BUTTONS(3R)	*/
/* int bttn1()			   BUTTONS(3R)	*/
/* int bttn2()			   BUTTONS(3R)	*/
/* int bttn3()			   BUTTONS(3R)	*/
/* int bttn12()			   BUTTONS(3R)	*/
/* int bttn23()			   BUTTONS(3R)	*/
/* int bttn13()			   BUTTONS(3R)	*/
/* int bttn123()		   BUTTONS(3R)	*/

/* Global Variables in this Program */
int Prev[4][7];		/* previous status of button macro calls */
Rectangle Table[4][7];	/* Defines the table of button macro names */

main()
{
	int x,y;			/* general coordinates */
	Point origin, corner;		/* general points */
	Point mxy, mjxy;		/* previous mouse coordinates */
	int Button;			/* return status of button macro */
	unsigned long time;		/* time to update mouse coordinates */
	Point scx, scy, wcx, wcy;	/* points to print mouse coord's */
	Rectangle ExitRect;		/* Exit Rectangle */

	/*
	** Request the mouse resource 
	*/
	request(MOUSE);

	/*
	** Draw The Exit Rectangle.
	** When button one of the mouse is clicked in this
	** Rectangle, the program will exit.
	*/
	ExitRect.origin = sub(Drect.corner, fPt(23*FW, 5*FH));
	ExitRect.corner = Drect.corner;
	box(&display, ExitRect, F_XOR);

	/*
	** Print message in ExitRect.
	*/
	moveto(add(ExitRect.origin, Pt(FW, FH)));
	lprintf("Click Button One");
	moveto(add(ExitRect.origin, Pt(FW, 2*FH)));
	lprintf("In This Box");
	moveto(add(ExitRect.origin, Pt(FW, 3*FH)));
	lprintf("To Exit.");

	/*
	** Initialize Table.  The Rectangles in this table define 
	** where the names of each button macro will be positioned
	** in the window.  Each rectangle is 15 "character widths" wide
	** one "character height" high.  The first row of the table is
	** on line 6 of the window.
	*/
	for (x=0; x<4; x++) {
	    for (y=0; y<7; y++) {
	        origin.x = FW*(15*x + 1);
	        origin.y = FH*(y + 6);
		corner.x = origin.x + 15*FW;
		corner.y = origin.y + FH;

		Table[x][y] = fRpt(origin, corner);
	    }
	}

	/*
	** Print Title line and label for mouse coordinates.
	*/
	moveto(Pt(0, 0));
	lprintf("\n");
	lprintf(" MOUSE TRACKING AND BUTTON STATUS\n");
	lprintf(" Screen Coordinates    Window Coordinates\n");

	/*
	** Obtain the points to print the mouse coordinate info.
	*/
	lprintf(" ");
	/* screen coordinate x */
	scx = sPtCurrent();
	lprintf ("                      ");
	/* window coordinate x */
	wcx = sPtCurrent();
	lprintf("\n ");
	/* screen coordinate y */
	scy = sPtCurrent();
	lprintf ("                      ");
	/* window coordinate y */
	wcy = sPtCurrent();

	/*
	** Print the table of button macro names.
	** Column 1
	*/
	moveto(add(Drect.origin, Table[0][0].origin));
	lprintf("bttn1()        ");

	moveto(add(Drect.origin, Table[0][1].origin));
	lprintf("bttn2()        ");

	moveto(add(Drect.origin, Table[0][2].origin));
	lprintf("bttn3()        ");

	moveto(add(Drect.origin, Table[0][3].origin));
	lprintf("bttn12()       ");

	moveto(add(Drect.origin, Table[0][4].origin));
	lprintf("bttn13()       ");

	moveto(add(Drect.origin, Table[0][5].origin));
	lprintf("bttn23()       ");

	moveto(add(Drect.origin, Table[0][6].origin));
	lprintf("bttn123()       ");

	/*
	** Column 2 
	*/
	moveto(add(Drect.origin, Table[1][0].origin));
	lprintf("button1()      ");

	moveto(add(Drect.origin, Table[1][1].origin));
	lprintf("button2()      ");

	moveto(add(Drect.origin, Table[1][2].origin));
	lprintf("button3()      ");

	moveto(add(Drect.origin, Table[1][3].origin));
	lprintf("button12()     ");

	moveto(add(Drect.origin, Table[1][4].origin));
	lprintf("button13()     ");

	moveto(add(Drect.origin, Table[1][5].origin));
	lprintf("button23()     ");

	moveto(add(Drect.origin, Table[1][6].origin));
	lprintf("button123()     ");

	/*
	** Column 3 
	*/
	moveto(add(Drect.origin, Table[2][0].origin));
	lprintf("bttn(1)        ");

	moveto(add(Drect.origin, Table[2][1].origin));
	lprintf("bttn(2)        ");

	moveto(add(Drect.origin, Table[2][2].origin));
	lprintf("bttn(3)        ");

	/* 
	** Column 4 
	*/
	moveto(add(Drect.origin, Table[3][0].origin));
	lprintf("button(1)      ");

	moveto(add(Drect.origin, Table[3][1].origin));
	lprintf("button(2)      ");

	moveto(add(Drect.origin, Table[3][2].origin));
	lprintf("button(3)      ");

	/*
	** Main loop of the Program.
	*/
	for(;;) {
	    if(own()&MOUSE) { /* If we own the mouse */

		/* 
		** Update the mouse coordinates 5 times per second.
		*/
		if( realtime() > time) {
		    time = realtime() + 12;
                    if(!eqpt(mouse.xy, mxy)) {
			mxy = mouse.xy;
		        moveto(scx);
		        lprintf("       ");	/* Erase old coordinate */
		        moveto(scx);
		        lprintf("x=%d", mouse.xy.x);/* Draw new coordinate */
		        moveto(scy);
		        lprintf("       ");	/* Erase old coordinate */
		        moveto(scy);
		        lprintf("y=%d", mouse.xy.y);/* Draw new coordinate */
                    }

                    if(!eqpt(mouse.jxy, mjxy)) {
			mjxy = mouse.jxy;
		        moveto(wcx);
		        lprintf("       ");	/* Erase old coordinate */
		        moveto(wcx);
		        lprintf("x=%d",mouse.jxy.x);/* Draw new coordinate */
		        moveto(wcy);
		        lprintf("       ");	/* Erase old coordinate */
		        moveto(wcy);
		        lprintf("y=%d",mouse.jxy.y);/* Draw new coordinate */
                    }
		}

		/*
		** The following code calls the button macros 
		** and determines whether the corresponding name
		** should be high-lighted in the table.
		*/

		/*
		** Column 1 of Table.
		*/
	        if ((Button = bttn1()) != Prev[0][0]) {
		    Prev[0][0] = Button;
		    rectf(&display, raddp(Table[0][0], Drect.origin), F_XOR);
	        }
	        if ((Button = bttn2()) != Prev[0][1]) {
		    Prev[0][1] = Button;
		    rectf(&display, raddp(Table[0][1], Drect.origin), F_XOR);
	        }
	        if ((Button = bttn3()) != Prev[0][2]) {
		    Prev[0][2] = Button;
		    rectf(&display, raddp(Table[0][2], Drect.origin), F_XOR);
	        }
		Button = bttn12();
	        if (( Button ||  Prev[0][3]) &&
	            (!Button || !Prev[0][3])) {
		    Prev[0][3] = Button;
		    rectf(&display, raddp(Table[0][3], Drect.origin), F_XOR);
	        }
		Button = bttn13();
	        if (( Button ||  Prev[0][4]) &&
	            (!Button || !Prev[0][4])) {
		    Prev[0][4] = Button;
		    rectf(&display, raddp(Table[0][4], Drect.origin), F_XOR);
	        }
		Button = bttn23();
	        if (( Button ||  Prev[0][5]) &&
	            (!Button || !Prev[0][5])) {
		    Prev[0][5] = Button;
		    rectf(&display, raddp(Table[0][5], Drect.origin), F_XOR);
	        }
		Button = bttn123();
	        if (( Button ||  Prev[0][6]) &&
	            (!Button || !Prev[0][6])) {
		    Prev[0][6] = Button;
		    rectf(&display, raddp(Table[0][6], Drect.origin), F_XOR);
	        }
		/*
		** Column 2 of Table.
		*/
	        if ((Button = button1()) != Prev[1][0]) {
		    Prev[1][0] = Button;
		    rectf(&display, raddp(Table[1][0], Drect.origin), F_XOR);
	        }
	        if ((Button = button2()) != Prev[1][1]) {
		    Prev[1][1] = Button;
		    rectf(&display, raddp(Table[1][1], Drect.origin), F_XOR);
	        }
	        if ((Button = button3()) != Prev[1][2]) {
		    Prev[1][2] = Button;
		    rectf(&display, raddp(Table[1][2], Drect.origin), F_XOR);
	        }
		Button = button12();
	        if ((Button || Prev[1][3]) && (!Button || !Prev[1][3])) {
		    Prev[1][3] = Button;
		    rectf(&display, raddp(Table[1][3], Drect.origin), F_XOR);
	        }
		Button = button13();
	        if ((Button || Prev[1][4]) && (!Button || !Prev[1][4])) {
		    Prev[1][4] = Button;
		    rectf(&display, raddp(Table[1][4], Drect.origin), F_XOR);
	        }
		Button = button23();
	        if ((Button || Prev[1][5]) && (!Button || !Prev[1][5])) {
		    Prev[1][5] = Button;
		    rectf(&display, raddp(Table[1][5], Drect.origin), F_XOR);
	        }
		Button = button123();
	        if ((Button || Prev[1][6]) && (!Button || !Prev[1][6])) {
		    Prev[1][6] = Button;
		    rectf(&display, raddp(Table[1][6], Drect.origin), F_XOR);
	        }
		/*
		** Column 3 of Table.
		*/
	        if ((Button = bttn(1)) != Prev[2][0]) {
		    Prev[2][0] = Button;
		    rectf(&display, raddp(Table[2][0], Drect.origin), F_XOR);
	        }
	        if ((Button = bttn(2)) != Prev[2][1]) {
		    Prev[2][1] = Button;
		    rectf(&display, raddp(Table[2][1], Drect.origin), F_XOR);
	        }
	        if ((Button = bttn(3)) != Prev[2][2]) {
		    Prev[2][2] = Button;
		    rectf(&display, raddp(Table[2][2], Drect.origin), F_XOR);
	        }

		/*
		** Column 4 of Table.
		*/
	        if ((Button = button(1)) != Prev[3][0]) {
		    Prev[3][0] = Button;
		    rectf(&display, raddp(Table[3][0], Drect.origin), F_XOR);
	        }
	        if ((Button = button(2)) != Prev[3][1]) {
		    Prev[3][1] = Button;
		    rectf(&display, raddp(Table[3][1], Drect.origin), F_XOR);
	        }
	        if ((Button = button(3)) != Prev[3][2]) {
		    Prev[3][2] = Button;
		    rectf(&display, raddp(Table[3][2], Drect.origin), F_XOR);
	        }

		/*
		** Check for exit. 
		*/
		if( bttn1() && ptinrect(mouse.xy, ExitRect))
			exit();

	    } else { 
		/* 
		** Window is not current. 
		** wait for mouse 
		*/
		wait(MOUSE);
            }
	}
}
