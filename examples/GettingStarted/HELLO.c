/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)HELLO.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include "world.h"

/* Library Routines and associated manual page. */
void  bitblt();		/* BITBLT(3R)		*/
void  lprintf();	/* PRINTF(3L)		*/
Point sPtCurrent();	/* MOVETO(3L)		*/
int   wait();		/* RESOURCES(3R)	*/

main()
{
	/*
	** See manual page STRUCTURES(3R)  for the
	** Point data type.
	*/
	Point savept;	

	/*
	** Use "lprintf" to move the "current screen point"
	** and set a position at which to display the
	** image of the world.
	*/
	lprintf("\n         ");
	savept = sPtCurrent();

	lprintf("\n  Hello,      !");

	/*
	** Display the image of the world.
	*/
	bitblt(&world, world.rect, &display, savept, F_XOR);

	/*
	** Share the CPU with other applications
	** and 630 system processes.
	*/
	for (;;) wait(CPU);
}
