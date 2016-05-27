/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)TrackMouse.c	1.1.1.3	(6/10/87)";

#include <dmd.h>
#include "world.h"

/* Library Routines and associated manual page. */
void bitblt();		/* BITBLT(3R)		*/
int request();		/* RESOURCES(3R)	*/
void sleep();		/* SLEEP(3R)		*/

main()
{
	Point MousePosition;

	/*
	** Request the use of the MOUSE resource.
	*/
	request(MOUSE);

	/*
	** Allow the 630 control process to run
	** and update the mouse position.
	*/
	sleep(2);

	/*
	** Record the current mouse position.
	*/
	MousePosition = mouse.xy;

	/*
	** Draw the world Bitmap at the current
	** mouse position.
	*/
	bitblt(&world, world.rect, &display, MousePosition, F_XOR);
	for(;;) {
		/*
		** Erase the world Bitmap from the old
		** mouse position.
		*/
		bitblt(&world, world.rect, &display, MousePosition, F_XOR);

		/*
		** Update the MousePosition.
		*/
		MousePosition = mouse.xy;

		/*
		** Draw the world at the new position.
		*/
		bitblt(&world, world.rect, &display, MousePosition, F_XOR);

		/*
		** Sleep for two ticks of the 60Hz clock to
		** release the CPU and synchronize with the
		** 60Hz refresh rate of the 630 screen.
		*/
		sleep(2);
	}
}

