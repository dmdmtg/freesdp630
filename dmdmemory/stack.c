/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)stack.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
#include <layer.h>
#include <dmdproc.h>
#include "defines.h"
#include "globals.h"


void
stakblk (p, f)
register Proc *p;
register f;
{
	register long *addr;
	register Slot *slp = slot;
	register x1, x2;
	register n;
	register long stksize = (long)p->stksize;
	long dummy;
	char s[50];
	long *a_nxtblk(), *a_header();

#define y1	Drect.origin.y + (VINSET+CH+DIV+BORDER)
#define y2	Drect.origin.y + (VINSET+CH+DIV+BORDER+BARW)


	slot[GC_ASTRAY].val = slot[GC_BUSY].val = 0l;		/* no stack is gcalloc'ed */
	slp->val = (inview (p->stack) != -1) ? stksize : 0l;

	while (slp < &slot[UPPERSLOTS])
		setfield (slp++, f);

	if (inview (p->stack)!= -1) {
		addr = a_header (p->stack, &dummy);
		x1 = addrtopix (addr);
		x2 = addrtopix ((long)a_nxtblk(addr, &dummy));
		texture (&display, Rect(x1,y1,x2,y2), txtr[ALLOC], F_XOR);
	}

	n = stradd (s, ltoa(stksize - searchstack(p), CoreBase));
	n += stradd (&s[n], " of total ");
	n += stradd (&s[n], ltoa(stksize, CoreBase));
	stradd (&s[n], " stack bytes used");
	setstrg (s);

#undef y1
#undef y2
}
	

unsigned long
searchstack (p)
Proc *p;
{
	register long *s = (long *)p->stack;
	register long *end = (long *)((unsigned long)s + p->stksize);
	register long i = 0;


	while (*s == MAGIC && s++ < end) {	/* MAGIC is defined in dmdproc.h */
		i += sizeof(long);
	}

	return (i);
}
