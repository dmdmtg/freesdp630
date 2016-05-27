/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)doodle.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
extern Texture16 *cursswitch();
Texture16 mesg= {
	 0x0000, 0x43DC, 0x4208, 0x4388,
	 0x4208, 0x7BC8, 0x0000, 0x0000,
	 0x7BC8, 0x4248, 0x5A48, 0x4A40,
	 0x7BC8, 0x0000, 0x0000, 0x0000,
};

main()
{
	Point p;
	request(MOUSE|KBD);

	local();
	for(;;){
		wait(MOUSE);
		if(button1()){  /* draw lines with button 1 */
			jmoveto(mouse.jxy);
			for(;bttn1();nap(2)){ /* nap to allow update */
				jlineto(mouse.jxy,F_OR);
			}
		}
		else if(button2()){
			rectf(&display, Drect, F_CLR);
			/* display "let go" message */
			cursswitch(&mesg);
			/* allow other processes to run */
		        /* while the button is down     */
			while(bttn2())
				sleep(2);
			cursswitch((Texture16 *)0);
		}
		else if(bttn3()){
			/* unrequest mouse so can get the main control menu */
			request(KBD);
			/* let process which controls the mouse run */
			sleep(2);
			/* request mouse again */
			request(MOUSE|KBD);
		}
		if(kbdchar() == 'q')
			exit();
	}
}
