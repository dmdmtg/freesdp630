/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)screen.c	1.1.1.1	(5/12/87)";

#include <dmd.h>

/* Library Routines and associated manual page. */
Point add();		/* PTARITH(3R)	*/
void box();		/* BOX(3R)	*/
void circle();		/* CIRCLE(3R)	*/
void disc();		/* CIRCLE(3R)	*/
void discture();	/* CIRCLE(3R)	*/
Point div();		/* PTARITH(3R)	*/
Point fPt();		/* fPt(3L)	*/
Rectangle inset();	/* INSET(3R)	*/
int min();		/* INTEGER(3R)	*/
void point();		/* POINT(3R)	*/
void polyf();		/* POLYGON(3L)	*/
void segment();		/* SEGMENT(3R)	*/
Point sub();		/* PTARITH(3R)	*/
int wait();		/* RESOURCES(3R)*/

/* Local functions declared in this file */
Point GetRectCenter();

/*
** Define the number of vertexes in polygons.
*/
#define POLYPOINTS	4

main()
{
	int Radius;
	Point WindowCenter, DrectExtent;
	Rectangle MyRect;

	/*
	** Declare three polygons.  A polygon is defined
	** by an array of Points.  Each polygon in this
	** example has four vertices.
	*/
	Point poly1[POLYPOINTS];
	Point poly2[POLYPOINTS];
	Point poly3[POLYPOINTS];

	/*
	** Get the center of the Rectangle Drect and also
	** determine its extent.
	*/
	WindowCenter = GetRectCenter(Drect);
	DrectExtent = sub(Drect.corner, Drect.origin);

	/*
	** Calculate the radius of a circle.
	*/
	Radius = min(DrectExtent.x, DrectExtent.y) / 4;

	/*
	** Draw a circle, a texture filled circle,
	** a filled circle, and a Point.
	*/
	circle (&display, WindowCenter, Radius, F_XOR);
	discture (&display, WindowCenter, 2*Radius/3, &T_checks, F_XOR);
	disc (&display, WindowCenter, Radius/3, F_STORE);
	point(&display, WindowCenter, F_XOR);

	/*
	** Draw a rectangle.
	*/
	MyRect = inset(Drect, Radius);
	box(&display, MyRect, F_XOR);

	/*
	** Initialize the points in polygon one.
	*/
	poly1[0] = Drect.origin;
	poly1[1] = MyRect.origin;
	poly1[2] = fPt(MyRect.origin.x, MyRect.corner.y);
	poly1[3] = fPt(Drect.origin.x, Drect.corner.y);

	/*
	** Initialize the points in polygon two.
	*/
	poly2[0] = fPt(Drect.origin.x, Drect.corner.y);
	poly2[1] = fPt(MyRect.origin.x, MyRect.corner.y);
	poly2[2] = MyRect.corner;
	poly2[3] = Drect.corner;

	/*
	** Initialize the points in polygon three.
	*/
	poly3[0] = fPt(Drect.corner.x, Drect.origin.y);
	poly3[1] = fPt(MyRect.corner.x, MyRect.origin.y);
	poly3[2] = MyRect.corner;
	poly3[3] = Drect.corner;

	/*
	** Draw the three texture filled polygons.
	*/
	polyf(&display, poly1, POLYPOINTS, &T_black, F_XOR);
	polyf(&display, poly2, POLYPOINTS, &T_grey, F_XOR);
	polyf(&display, poly3, POLYPOINTS, &T_black, F_XOR);

	/*
	** Draw four line segments.
	*/
	segment(&display, poly1[0], poly1[2], F_XOR);
	segment(&display, poly1[1], poly1[3], F_XOR);
	segment(&display, poly3[0], poly3[2], F_XOR);
	segment(&display, poly3[1], poly3[3], F_XOR);

        /*
        ** Share the CPU with other applications
        ** and 630 system processes.
        */
        for (;;) wait(CPU);

}

/*
** Function to find the center of a Rectangle.
*/
Point
GetRectCenter(r)
Rectangle r;
{
        Point HalfOfExtent;

        HalfOfExtent = div( sub(r.corner, r.origin), 2);
        return add(r.origin, HalfOfExtent);
}
