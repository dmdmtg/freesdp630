/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)msgbox1.c	1.1.1.1	(5/12/87)";

#include <dmd.h>

/* Library routines and associated manual page.	*/
void bttns();		/* BUTTONS(3R)		*/
void exit();		/* EXIT(3R)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
int msgbox();		/* MSGBOX(3R)		*/
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/* Library macros and associated manual page.	*/
/* int button123()	   BUTTONS(3R)		*/

main()
{
	request(MOUSE|KBD);

	for(;;) {
		wait(MOUSE);
		if(button123()) {
			/*
			** Draw message box in response
			** to any button pressed.
			*/
			msgbox("This is a Message",
				"Box Demonstration",
				(char *)0);
			/*
			** Busy loop until all mouse
			** mouse buttons are released.
			*/
			bttns(0);
		}
		/*
		** Exit if the user has typed any keys.
		*/
		if(kbdchar() != -1)
			exit();
	}
}
