/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)menu.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include <font.h>
#include <menu.h>

/*
 * The following code is used to make tmenuhit() backwards compatible.
 * This code emulates the old menuhit() exactly, by massaging the old
 * menuhit data structures into the variable size Titem data structures.
 */

extern Titem *tmenuhit();

typedef struct Ctitem {
	char *text;
} Ctitem;
static Ctitem tempitem;
static Tmenu tempmenu;
static char *(*usergen)();

menuhit(m, n)
register Menu *m;
int n;
{
	register Tmenu *tm;
	register int ret;
	extern Ctitem *tmgen();

	tm = &tempmenu;
	if (m->item == 0) {
		tm->item = 0;
		usergen = m->generator;
		tm->generator = (Titem *(*)()) tmgen;
	}
	else {
		tm->item = (Titem *) m->item;
	}
	tm->prevtop = m->prevtop;
	tm->prevhit = m->prevhit;
	tm->menumap = TM_TEXT;
	if (tmenuhit(tm, n, 0))
		ret = (m->prevtop = tm->prevtop) + (m->prevhit = tm->prevhit);
	else
		ret = -1;
	return(ret);
}

Ctitem *
tmgen(i)
register int i;
{
	/*
	 * This generator is used only to call the user supplied generator
	 * from Menu data structures from the old menuhit() and returns the
	 * proper data structure for a specific menu item.
	 */
	tempitem.text = usergen(i);
	return(&tempitem);
}
