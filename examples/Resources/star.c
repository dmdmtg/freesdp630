/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)star.c	1.1.1.1	(5/10/87)";

#include <dmd.h>

/*Library routines and associated manual pages.	*/
Point add();		/* PTARITH(3R)		*/
void exit();		/* EXIT(3R)		*/
void jmoveto();		/* JMOVE(3L)		*/
void jlineto();		/* JSEGMENT(3L)		*/
void jrectf();		/* JRECTF(3L)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
int local();		/* LOCAL(3R)		*/
void nap();		/* SLEEP(3R)		*/
Point mul();		/* PTARITH(3R)		*/
int request();		/* RESOURCES(3R)	*/
void sleep();		/* SLEEP(3R)		*/
Point sub();		/* PTARITH(3R)		*/
int wait();		/* RESOURCES(3R)	*/

/*Library macros and associated manual pages.	*/
/*int bttn1()		/* BUTTONS(3R)		*/
/*int button1()		/* BUTTONS(3R)		*/
/*int button2()		/* BUTTONS(3R)		*/
/*int button3()		/* BUTTONS(3R)		*/

/* Routines local to star.c */
void draw();
void GetDelta();
void GetPoints();
int WhichQuadrant();

#define QUADRANT1 1
#define QUADRANT2 2
#define QUADRANT3 3
#define QUADRANT4 4

typedef struct QuadrantPoints {
	Point quadrant1, quadrant2, quadrant3, quadrant4;
} QuadrantPoints;

QuadrantPoints InitialPoint;
QuadrantPoints FinalPoint;

Point MousePosition;

Point Delta;

Point WindowCenter = {XMAX/2, YMAX/2};

/*
** star.c takes an initial point selected by depressing mouse button
** 1, maps that initial point into the four quadrants of the window
** (see the routine WhichQuadrant and SetPoints ) and then while
** mouse button 1 is depressed, tracks mouse movement by drawing
** line segments from the initial points in each quadrant to the
** corresponding final points in each quadrant determined by mapping
** the current mouse position into each quadrant.  The result is a
** drawing that is symmetrical about the x and y axis.  Releasing and
** then depressing mouse button 1 will allow you to select new initial
** points.  Mouse button 2 will erase the current drawing.  
** star.c exits when the user types a 'q'.
*/
main()
{
	/*
	** Release the host connection.
	*/
	local();

	/*
	** Request the use of the mouse and
	** keyboard application resources.
	*/
	request(MOUSE|KBD);

	/*
	** Main loop.
	*/
	for(;;) {
		/*
		** Release the CPU until the mouse or
		** the keyboard need service.
		*/
		wait(MOUSE|KBD);

		if (button1()) {
			/*
			** If mouse button 1 is depressed,
			** set initial points in each quadrant.
			*/
			GetPoints(&InitialPoint);
			for (;bttn1();) {
				/*
				** As long as button 1 stays depressed,
				** get final points in each quadrant
				** and draw the line segments.
				*/
				GetPoints(&FinalPoint);
				draw();
				/*
				** Busy loop for two clock ticks
				** in order to allow the user to
				** move the mouse.
				*/
				nap(2);
			}
		} else if (button2())
			/*
			** If mouse button two is depressed
			** erase the current drawing.
			*/
			jrectf(Jrect, F_CLR);
		else if (button3()) {
			/*
			** If buttons 3 is depressed, release
			** the mouse resource and allow the control
			** process to run.
			*/
			request(KBD);
			sleep(2);
			request(MOUSE|KBD);
		}
		if (kbdchar() == 'q')
			/*
			** If the user types a 'q', then exit.
			*/
			exit();
	}
}

int
WhichQuadrant()
/*
** star.c divides the window into four equal quadrants.
**		|
**	2	|	1
**		|
** ---------------------------> x
**		|
**	3	|	4
**		|
**		V
**		y
** WhichQuadrant will return the number corresponding to
** the quadrant that the mouse cursor is currently in.
*/
{
	if (MousePosition.x >= XMAX/2) {
		if (MousePosition.y <= YMAX/2)
			return(QUADRANT1);
		else
			return(QUADRANT4);
	} else { 
		if (MousePosition.y <= YMAX/2)
			return(QUADRANT2);
		else
			return(QUADRANT3);
	}
}

void
GetDelta()
/*
** The x and y coordinate of the Point Delta helps in
** mapping the current mouse position into the four
** quadrants.
** Delta.x = 2*((XMAX/2) - MousePosition.x)
** Delta.y = 2*((YMAX/2) - MousePosition.y)
*/
{
	MousePosition = mouse.jxy;
	Delta = mul( sub(WindowCenter, MousePosition), 2);
}

void
GetPoints(Qp)
struct QuadrantPoints *Qp;
/*
** Map the current mouse position into the four quadrants.
*/
{
	Point p1, p2, p3, p4;

	GetDelta();
	p1 = MousePosition;
	p2 = MousePosition; p2.x += Delta.x;
	p3 = add(MousePosition, Delta);
	p4 = MousePosition; p4.y += Delta.y;
	switch(WhichQuadrant()) {
	case QUADRANT1:
		Qp->quadrant1 = p1;
		Qp->quadrant2 = p2;
		Qp->quadrant3 = p3;
		Qp->quadrant4 = p4;
		break;
	case QUADRANT2:
		Qp->quadrant1 = p2;
		Qp->quadrant2 = p1;
		Qp->quadrant3 = p4;
		Qp->quadrant4 = p3;
		break;
	case QUADRANT3:
		Qp->quadrant1 = p3;
		Qp->quadrant2 = p4;
		Qp->quadrant3 = p1;
		Qp->quadrant4 = p2;
		break;
	case QUADRANT4:
		Qp->quadrant1 = p4;
		Qp->quadrant2 = p3;
		Qp->quadrant3 = p2;
		Qp->quadrant4 = p1;
		break;
	}
}

void
draw()
/*
** Draw line segments from the initial point in the quadrant
** to the final point.
*/
{
	int i;
	for (i=0;i<4;i++) {
		jmoveto(((Point *)(&InitialPoint))[i]);
		jlineto(((Point *)(&FinalPoint))[i], F_OR);
	}
}
