/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)scope.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include "defines.h"
#include "globals.h"


void
setscope ()
{
	register i, n;
	register long ptemp, qtemp;
	register Slot *slp;
	Slot tslot[2];

	dragstrg ();

	for (i=0, n=C_START; i<2; ++i, n=C_END) {
		tslot[i] = slot[n];
		slp = &tslot[i];
		ptemp = slp->val;

		drawbar (ptemp);	/* draw scope bar */
		blink (sblk, slp);	/* blink */

		if (button23()) 
			goto out;

		while (bttn1()) {
			drawbar (ptemp);	/* undraw scope bar */
			slp->val = ptemp = pixtoaddr ();	/* new value */
			setfield (slp, CLR_XOR);	/* display new value */
			drawbar (ptemp);	/* redraw scope bar */
			nap (2);
		}
	}

	qtemp = tslot[0].val;	/* while ptemp = tslot[1].val */

	if (ptemp < qtemp) {
		qtemp = (long)memstartp;
		ptemp = (long)memendp;
	}
	else {
		if (ptemp - qtemp < BARL)	/* smallest scope is a byte per pixel */
			ptemp = qtemp+BARL;
	}

	setbound (qtemp, ptemp);
out:
	rectf (&display, Drect, F_CLR); 	/* clear screen */
	drawview ();				/* redraw */
}

/* Draw/undraw the scope bar
*/
void
drawbar (addr)
long addr;
{
	register x = pconfine (addrtopix (addr));
	
	segment(&display,Pt(x,Drect.origin.y+VINSET),Pt(x,Drect.corner.y-VINSET),F_XOR);
}


/* For blinking the scope bar and the boundary limit.
** This function is called indirectly from blink().
*/
void
sblk (slp)
Slot *slp;
{
	drawbar (slp->val);
	setfield (slp, XOR);
}
 

long
pixtoaddr ()
{
	long n = mouse.xy.x - (Drect.origin.x+VINSET+BORDER);

	return (confine ((((n * CoreSpan)/BARL) + CoreStart) & ~3));
}

int
addrtopix (addr)
long addr;
{
	return (Drect.origin.x + (VINSET+BORDER) + (((addr-CoreStart)*BARL)/CoreSpan));
}


void
blink (foo, arg)
void (*foo)();
long arg;
{

	while (!button123()) {
		(*foo)(arg, CLR);	/* undraw */
		sleep (30);

		(*foo)(arg, XOR);	/* then draw, so when this exits, the thing is drawn */
		if (button123())
			break;
		else {
			sleep (30);
		}
		if (checkmem())
			viewupdate ();
	}
}

long
confine (addr)
register long addr;
{
	addr = lmin (addr, CoreEnd);
	addr = lmax (addr, CoreStart);
	return (addr);
}


pconfine (x)
{
	register xleft = Drect.origin.x + (VINSET+BORDER);
	register xright = Drect.corner.x - (VINSET+BORDER);

	if (x > xright)
		return (xright);
	else if (x < xleft)
		return (xleft);
	return (x);
}



/* Modify the alloc limit
** The alloc limit vertical bar is dragged along with button 1.
*/
void
setlimit ()
{
	register Slot *slp = &slot[A_LIM];
	register long lim = slp->val;
	register long temp;
	long labs();

	if (inview(slp->val) == -1)
		return;

	dragstrg ();
	blink (lblk);		/* get the user attention */

	while (bttn1()) {
		lim = pixtoaddr();

		/* track limit bar right up to allowable boundaries */
		if (lim < (long)alloclevel) lim = (long)alloclevel;

		drawlim ();		/* undraw limit bar */
		allocset (lim);		/* reset alloclevel */
		slp->val = lim;		/* reset the field */
		setfield (slp, CLR_XOR);	/* display new address */
		drawlim ();		/* redraw limit bar */
		nap (2);
		
	}

	scopestrg ();
}

/* Draw/undraw the limit bar if it is in view
*/
void
drawlim ()
{
	register x, y;

	if (inview(slot[A_LIM]) != -1) {
		x = addrtopix (slot[A_LIM]);
		y = Drect.origin.y + (VINSET+CH);
		segment (&display, Pt(x,y), Pt(x,y+DIV+BORDER+BARW+BORDER+DIV), F_XOR);
	}
}

/* For blinking the alloc limit value and bar.
** Called indirectly from blink().
*/
void
lblk ()
{
	drawlim();
	setfield (&slot[A_LIM], XOR);
}

