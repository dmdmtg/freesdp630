/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)twist.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include "rotate.h"

/* Library Routines and associated manual page. */
void bitblt();          /* BITBLT(3R)           */
void lprintf();         /* PRINTF(3L)           */
void sleep();		/* SLEEP(3R)		*/
Point sPtCurrent();     /* MOVETO(3L)           */
int wait();             /* RESOURCES(3R)        */

main()
{
	int i;
	Point savept;

        /*
        ** Use "lprintf" to move the "current screen point"
        ** and set a position at which to display the
        ** image of the world.
        */
	lprintf("\n         ");
	savept = sPtCurrent();

	lprintf("\n  Hello        !");

	for (i=0; 1 ; i++) {
		/*
		** after the 18th Bitmap, go back to Bitmap zero.
		*/
		if(i==18)
			i=0;

		/*
		** Draw the current Bitmap of the world.
		*/
		bitblt(world[i], world[i]->rect, &display, savept, F_XOR);

		/*
		** Release the CPU for 10 ticks of the
		** 60 Hz system clock.
		*/
		sleep(10);

		/*
		** Erase the current Bitmap of the world in
		** preparation for drawing the next.
		*/
		bitblt(world[i], world[i]->rect, &display, savept, F_XOR);

	}
}
