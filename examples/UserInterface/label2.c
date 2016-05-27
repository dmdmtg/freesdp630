/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)label2.c	1.1.1.3     (6/10/87)";

#include <dmd.h>
#include <label.h>

/* Library Routines and associated manual page. */
void labelicon();       /* LABELON(3R)          */
void labelon();         /* LABELON(3R)          */
void labeltext();	/* LABELON(3R)		*/
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

Bitmap B_skull; 

Rectangle fRect();

main()
{
        /*
        ** Dynamically initialize the Bitmap B_skull
        ** with the data from the texture16 cursor
        ** C_skull.
        */
	B_skull.base = (Word *)&C_skull;
	B_skull.width = 1;
	B_skull.rect = fRect(0, 0, 16, 16);

	request(MOUSE);

        /*
        ** Turn on the label bar.
        */
	labelon();

	/*
	** Display three text strings.
	*/
	labeltext("left", 4, L_LEFT);
	labeltext("center", 6, L_CENTER);
	labeltext("right", 5, L_RIGHT);

        /*
        ** Exit when the user hits button 1.
        */
	while (!button1()) wait(MOUSE);
}
