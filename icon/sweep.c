/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)sweep.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include "icon.h"



Rectangle sweeprect()
{
	Rectangle r;
	Point p1, p2;
	Texture16 * oldcursor;
	oldcursor = (Texture16 *) cursswitch(&sweepcursor);
	while (!bttn123()) 
		wait(MOUSE);
	p1 = mouse.xy;
	p2 = p1;
	r = canon(p1, p2);
	Outline(&display, r);
	for (; bttn3(); nap(2)) {
		Outline(&display, r);
		p2 = mouse.xy;
		r = canon(p1, p2);
		Outline(&display, r);
	}
	Outline(&display, r);
	cursswitch(oldcursor);
	return r;
}


bool getr(cliprect, sweep)
Rectangle cliprect;
Rectangle *sweep;
{
	int	j;
	*sweep = sweeprect();
	return(rectclip(sweep, cliprect));
}



Point IconPoint(p)
/* convert screen coord to icon coord */
Point p;
{
	p.x = (p.x + Xsize - modx) / Xsize - divx - 1;
	p.y = (p.y + Ysize - mody) / Ysize - divy - 1;
	return(p);
}


Point ScreenPoint(p)
/* convert icon coord to screen coord */
Point p;
{
	p.x = p.x * Xsize + ICON.origin.x;
	p.y = p.y * Ysize + ICON.origin.y;
	return(p);
}


Rectangle IconRect(r)
/* convert a screen rectangle to the biggest totally contained icon rectangle */
Rectangle r;
{
	r.origin = IconPoint(add(r.origin, Pt(Xsize - 1, Ysize - 1)));
	r.corner = IconPoint(r.corner);
	return(r);
}


Rectangle TrackBorder(r, bttnup)
/* tracks a rectangle "r" (in icon coords) and returns it as it is
   at the end of tracking, clipped to the icon */
Rectangle r;
bool bttnup;
{
	Point newP, oldP;
	Texture16 * oldcursor;

	oldcursor = (Texture16 *) cursswitch(&white);
	outl.origin = nullpoint;
	outl.corner.x = horsize(r) * Xsize;
	outl.corner.y = versize(r) * Ysize;
	newP = ScreenPoint(r.origin);
	while (bttnup ? (bttn123()) : (!bttn123())) 
		wait(MOUSE);
	cursset(newP);
	oldP = newP;
	border(raddp(outl, newP));
	while (bttnup ? (!bttn123()) : (bttn123())) {
		wait(MOUSE);
		if (bttnup) 
			wait(MOUSE);
		newP = ScreenPoint(IconPoint(mouse.xy));
		if (!eqpt(newP, oldP)) {
			border(raddp(outl, oldP));
			border(raddp(outl, newP));
			oldP = newP;
		}
	}
	border(raddp(outl, newP));
	cursswitch(oldcursor);
	return(IconRect(raddp(outl, newP)));
}

bool SweepIconRect(r)
Rectangle *r;
{
	Point p;
	if (!getr(ICON, &sweep)) 
		return(false);
	*r = IconRect(sweep);
	return(true);
}


int	GetIconRect(r)
/* returns: 0 if no rectangle is provided;
            2 if bttn2 is used (tracking a 16x16 rectangle);
            3 if bttn3 is used (sweeping a rectangle);
   if a rectangle is provided, r returns it in icon coordinated */
Rectangle *r;
{
	int	result;
	Texture16 * oldcursor;
	oldcursor = (Texture16 *) cursswitch(&sweeportrack);
	while (!bttn123()) 
		wait(MOUSE);
	if (bttn3()) {
		if (SweepIconRect(r)) 
			result = 3;
		else 
			result = 0;
	} else if (bttn2()) {
		*r = TrackBorder(raddp(rect16x16, add(IconPoint(mouse.xy), Pt(1, 1))), false);
		result = 2;
	} else {
		while (bttn1())
			wait(MOUSE);
		result = 0;
	}
	cursswitch(oldcursor);
	return(result);
}


bool GetIconPoint(p)
Point *p;
{
	Rectangle r;
	r = TrackBorder(raddp(Rect(0, 0, 1, 1), IconPoint(mouse.xy)), true);
	while (bttn123())
		wait(MOUSE);
	*p = r.origin;
	return((horsize(r) == 1) && (versize(r) == 1));
}


