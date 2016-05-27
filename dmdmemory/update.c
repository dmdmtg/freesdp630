/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)update.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include "defines.h"
#include "globals.h"


/* Update the graphical bar display
*/
void
viewupdate ()
{
	register Slot *slp = slot;

	/* There are three numerical slots displayed at the top of the graphical bar:
	**	slot 1: size of alloc space used,
	**	slot 2: size of gcastray space used,
	**	slot 3: size of gc space used.
	*/
	while (slp < &slot[UPPERSLOTS])	/* reset the values before re-computation */
		(slp++)->val = 0l;

#define X1	Drect.origin.x + (VINSET+BORDER)
#define X2	Drect.corner.x - (VINSET+BORDER)
#define Y1	Drect.origin.y + (VINSET+CH+DIV+BORDER)
#define Y2	Drect.origin.y + (VINSET+CH+DIV+BORDER+BARW)

	drawlim ();					/* undraw the limit bar */
	rectf (&display, Rect(X1,Y1,X2,Y2), F_CLR);	/* clear the graphical bar */	
	numslot (&foo[ALLOC]);				/* redraw graphical bar */
	numslot (&foo[GCALLOC]);
	addrslot ();
	drawlim ();					/* redraw the limit bar */

#undef X1
#undef X2
#undef Y1
#undef Y2

	for (slp = slot; slp < &slot[SLOTNUM]; slp++)
		setfield (slp, CLR_XOR);
}


/* Display the specific numerical or address field
*/
void 
setfield (slp, f)
register Slot *slp;
int f;
{
	register x = Drect.origin.x + slp->x;
	register y = Drect.origin.y + slp->y;

	if ((f==CLR) || (f==CLR_XOR))
		rectf (&display, Rect(x,y,x+SW,y+CH), F_CLR);	/* clear the old one */
	if ((slp->val >= 0) && ((f==XOR) || (f==CLR_XOR)) ) 
		string (&mediumfont, ltoa(slp->val, CoreBase), &display, Pt(x,y), F_XOR); 
}


/* Update the specific numerical slots and the corresponding textures in the bar:
** There are slots belonging to the alloc pool (A_BUSY and GC_ASTRAY), and
** slot belonging to the gc pool (GC_BUSY). Their computations are similar but
** not quite the same, the differences are saved in struct Foos.
*/
void
numslot (foos)
Foos *foos;
{
	register x1, x2;
	register long asize;
	register long span;
	register int it, newit;
	register f = 0;		/* last block flag */
	register long *ub;	/* for "ubiquitous", of course */
	long size;		/* we need to take its address, so no "register" */

#define y1 Drect.origin.y + (VINSET+CH+DIV+BORDER)
#define y2 Drect.origin.y + (VINSET+CH+DIV+BORDER+BARW)

	if (foos->id == ALLOC) {
		x2 = Drect.origin.x + (VINSET+BORDER);
		ub = (long *)CoreStart;
	}
	else {
		x1 = Drect.corner.x - (VINSET+BORDER);
		ub = (long *)CoreEnd;
	}

	/* Process the first block:
	** Check if the scope is totally inside the first block
	*/

	if (!(ub = foos->find(ub, &size)))	/* out of range */
		return;
	asize = size;
	it = foos->whatzit(ub);
 	if (((foos->id == ALLOC) && (it <= GC_ASTRAY)) ||
	    ((foos->id == GCALLOC) && (it == GC_BUSY)))
							/* start compounding */ 
		slot[it].val += asize;
	if (foos->last(ub)) {			/* start block is also last block */
		f = 1;
		goto disp;
	}

	while (1) {
		ub = foos->next(ub, &size);	/* next block */
		newit = foos->whatzit(ub);	/* new block type */
 		if (((foos->id == ALLOC) && (newit <= GC_ASTRAY)) ||
		    ((foos->id == GCALLOC) && (newit == GC_BUSY)))
							/* keep compounding */ 
			slot[newit].val += size;

		if (newit == it) {		/* same type as before */
			asize += size;
			if (!foos->last(ub))
				continue;
			f = 1;			/* last block processed */
		}

		/* block type has changed, or this is last block,
		** display everything compounded so far
		*/
disp:
		span = (asize*BARL)/CoreSpan;	/* more accurate than */
								/* asize / CoreUnit */
		if (foos->id == ALLOC) {
			x1 = x2;
			x2 = pconfine (x2+(int)span);
		}
		else {
			x2 = x1;
			x1 = pconfine (x1-(int)span);
			/* don't write galloc bar over past alloclevel */
			x1 = max(x1,addrtopix(alloclevel));
		}

		if ((it < A_FREE)  && (x1 != x2))
			texture (&display, Rect(x1,y1,x2,y2), txtr[it], F_STORE);

		/* To solve the sampling problem, we add any bytes that cannot fit in
		** the previous sample to the next sample, therefore no bytes will be lost.
		** The following calculation is more accurate than:
		**		asize = size + (asize % CoreUnit);
		*/
		asize = size + (asize - ((span * CoreSpan)/BARL));
		it = newit;

		if (foos->last(ub)) {		/* last block */
			if (f)			/* if already processed */
				break;		/* get out */
			else {
				f = 1;		/* process it */
				goto disp;	/* get out on next re-entrant */
			}
		}
	}

#undef y1
#undef y2
}


/* Update the address fields at the bottom of the graphical bar.
** Some fields are not present in the scoped view area, and their
** value will be negative.
**
** Also note that C_START and C_END are always up to date by setbound(),
** therefore we don't have to worry about them.
*/
void
addrslot()
{
	slot[A_LEVEL].val = inview(alloclevel);
	slot[A_LIM].val = inview(alloclimit);
	slot[GC_LEVEL].val = inview(gclevel);
}


long 
inview (addr)
long addr;
{
	return (((addr >= CoreStart) && (addr <= CoreEnd)) ? addr : -1);
}

