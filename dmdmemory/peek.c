/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)peek.c	1.1.1.5	(5/10/87)";

#include <dmd.h>
#include <layer.h>
#include <dmdproc.h>
#include "defines.h"
#include "globals.h"


void
peekproc ()
{
	picklayer (procblk);
}

void 
peekstak ()
{
	picklayer (stakblk);
}


picklayer (foo)
void (*foo)();
{
	register Layer *l;
	register Proc *p;
	extern Layer *whichlayer();
	extern Proc *whichproc();

	setstrg ("click and pick a window with button 1");
	Cursswitch (&C_target);
	bttns (0);
	while (!bttn123());
	Cursswitch ((Texture16 *)0);

	if (bttn1() && (l=whichlayer())) {
		p = whichproc(l);
		rectf (l, l->rect, F_XOR);	/* blink the layer */
		nap (15);
		rectf (l, l->rect, F_XOR);

		blink (foo, p);
	}

	viewupdate ();
	scopestrg ();
}


void
procblk (p, f)
register Proc *p;
register f;
{
	register Slot *slp = slot;
	register Slot *endp = &slot[UPPERSLOTS];
	register n;
	char s[25];
	

	for (slp = slot; slp < endp; ) 	/* reset the values before re-computation */
		(slp++)->val = 0l;

	calcslot (&foo[ALLOC], p);
	calcslot (&foo[GCALLOC], p);

	for (slp = slot; slp < endp; ) 
		setfield (slp++, f);

	n = stradd (s, "process = ");
	stradd (&s[n], ltoa(p, CoreBase));
	setstrg (s);
}

calcslot (foos, p)
Foos *foos;
register Proc *p;
{
	register long *ub;
	register Proc *ocp, *cp;
	register x1, x2;
	register f, of;		/* just flags */
	register long asize;
	register long span;
	register it, oit;
	int last = 0;		/* last block flag */
	long size;

	int Y1 = Drect.origin.y + (VINSET+CH+DIV+BORDER);
	int Y2 = Drect.origin.y + (VINSET+CH+DIV+BORDER+BARW);
	int X1 = Drect.origin.x + (VINSET+BORDER);
	int X2 = Drect.corner.x - (VINSET+BORDER);

	if (foos->id == ALLOC) {
		x1 = x2 = X1;
		ub = (long *)CoreStart;
	}
	else {
		x1 = x2 = X2;
		ub = (long *)CoreEnd;
	}

	if (!(ub = foos->find(ub, &size)))	/* out of range */
		return;

	asize = 0l;
	ocp = (Proc *)0l;

	for (; ; ub = foos->next(ub, &size)) {
		cp = (Proc *)foos->own(ub);
		it = foos->whatzit(ub);

		/* set the flags so we don't repeat the comparaisons */
		f = (cp == p);		/* is current block belongs to process? */
		of = (ocp == p);	/* is old block belongs to process? */

		if (f)
			slot[it].val += size;

		/* if current block belongs and old block does not, we start to
		** compound belonging blocks.
		*/
		if ((f && !of) || (f && of && it!=oit)) {
			span = (asize*BARL)/CoreSpan;

			/* calculate the left x-coordinate */
			if (foos->id == ALLOC)
				x1 = pconfine (x2+(int)span);
			else
				x2 = pconfine (x1-(int)span);

			/* re-init everything */
			oit = it;
			asize -= ((span * CoreSpan)/BARL);
		}

		/* if old block belongs but current block does not belong, terminate
		** the compounding and start displaying the compounded block.
		** Do the same if both blocks still belong but the type of block
		** changes.
		*/
		else if ((!f && of) || (f && of && it!=oit)) {
disp:
			span = (asize*BARL)/CoreSpan;

			/* calculate the right x-coordinate and do the display */
			if (foos->id == ALLOC)
				x2 = pconfine (x1+(int)span);
			else {
				x1 = pconfine (x2-(int)span);
				/* make sure you don't write into gcastray on
				 * last gcalloc block
				 */
				x1 = max(x1, addrtopix(alloclevel));
			}
			if (x1 != x2)
				texture (&display,Rect(x1,Y1,x2,Y2),txtr[oit],F_XOR);

			/* re-initialize */
			oit = it;
			asize -= ((span * CoreSpan)/BARL);
		}


		ocp = cp;
		asize += size;

		if (foos->last(ub)) {	/* check here for last block */
			if (last || !f)
				break;
			last = 1;
			goto disp;
		}
	}

#undef Y1
#undef Y2
#undef X1
#undef X2
}
