/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)kbd2.c	1.1.1.2	(5/22/87)";

/*
 *	Program to allow the user to control the mode of the keyboard.
 *	This is done through menu selections.  Keyboard data that is
 *	received is displayed in character, hex, and decimal format.
 */
#include <dmd.h>
#include <font.h>
#include <menu.h>

/*Library routines and associated manual pages.	*/
void exit();            /* EXIT(3R)             */
int kbdchar();          /* KBDCHAR(3R)          */
int local();		/* LOCAL(3R)		*/
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
void sleep();		/* ALARM(3R)		*/
Titem *tmenuhit();	/* TMENUHIT(3R)		*/
int wait();             /* RESOURCE(3R)         */

/*Library macros and associated manual pages	*/
/*int button23()	   BUTTONS(3R)		*/


#define KBD_NORM	0
#define KBD_NOTRAN	1
#define KBD_NOPFXPAN	2
#define KBD_NOPADXPAN	3
#define KBD_NOCURXPAN	4
#define KBD_EXIT	5

Titem kbditems[] = {
	"Normal", 		KBD_NORM,      0, 0, 0, 0, 0, 0, 0,
	"No Translate",		KBD_NOTRAN,    0, 0, 0, 0, 0, 0, 0,
	"No PF Expand",		KBD_NOPFXPAN,  0, 0, 0, 0, 0, 0, 0,
	"No Pad Expand",	KBD_NOPADXPAN, 0, 0, 0, 0, 0, 0, 0,
	"No Cursor Expand",	KBD_NOCURXPAN, 0, 0, 0, 0, 0, 0, 0,
	"Exit",			KBD_EXIT,      0, 0, 0, 0, 0, 0, 0,
	(char *)0
};

Tmenu kbdmenu = { kbditems };

main()
{
	int c;
	Titem *titemptr;
	int kbdstart = 0;
		
	/*
	** Release the host connection.
	*/

	local();
	/*
	** Place check mark in menu next to
	** current mode.
	*/
	kbditems[KBD_NORM].icon = &B_checkmark;

	/*
	** Request keyboard and mouse resources.
	*/
	request(KBD | MOUSE);

	/*
	** Main loop of program.
	*/
	while (1) {
		/*
		** Wait on MOUSE, means wait until I'm current.
		** Wait on KBD, means wait until I receive a char.
		*/
		wait(KBD | MOUSE);
		switch(button23()) {
		case 1:		/* button 3 */
			/*
			** Let control process handle
			** button 3.
			*/
			request(KBD);
			sleep(2);
			request(KBD | MOUSE);
			break;
		case 2:		/* button 2 */
			if ((titemptr = tmenuhit(&kbdmenu, 2, 0)) == (Titem *) 0)
				break;
			switch(titemptr->ufield.uval) {
			/*
			** Normal Keyboard processing.
			*/
			case KBD_NORM:
				kbditems[KBD_NORM].icon = &B_checkmark;
				kbditems[KBD_NOTRAN].icon = 0;
				kbditems[KBD_NOPFXPAN].icon = 0;
				kbditems[KBD_NOPADXPAN].icon = 0;
				kbditems[KBD_NOCURXPAN].icon = 0;
				P->state &= ~(NOPFEXPAND | NOCURSEXPAND |
					    NOPADEXPAND | NOTRANSLATE);
				break;
			/*
			** Turn of the normal translation of
			** all keys typed on the keyboard.
			*/
			case KBD_NOTRAN:
				kbditems[KBD_NOTRAN].icon = &B_checkmark;
				kbditems[KBD_NORM].icon = 0;
				kbditems[KBD_NOPFXPAN].icon = 0;
				kbditems[KBD_NOPADXPAN].icon = 0;
				kbditems[KBD_NOCURXPAN].icon = 0;
				P->state |= NOTRANSLATE;
				P->state &= ~(NOPFEXPAND | NOCURSEXPAND |
					    NOPADEXPAND);
				break;
			/*
			** Turn off pf key expansion.
			*/
			case KBD_NOPFXPAN:
				kbditems[KBD_NOPFXPAN].icon = &B_checkmark;
				kbditems[KBD_NORM].icon = 0;
				kbditems[KBD_NOTRAN].icon = 0;
				P->state |= NOPFEXPAND;
				P->state &= ~NOTRANSLATE;
				break;
			/*
			** Turn off expansion of keypad.
			*/
			case KBD_NOPADXPAN:
				kbditems[KBD_NOPADXPAN].icon = &B_checkmark;
				kbditems[KBD_NORM].icon = 0;
				kbditems[KBD_NOTRAN].icon = 0;
				P->state |= NOPADEXPAND;
				P->state &= ~NOTRANSLATE;
				break;
			/*
			** Turn of expansion of cursor keys.
			*/
			case KBD_NOCURXPAN:
				kbditems[KBD_NOCURXPAN].icon = &B_checkmark;
				kbditems[KBD_NORM].icon = 0;
				kbditems[KBD_NOTRAN].icon = 0;
				P->state |= NOCURSEXPAND;
				P->state &= ~NOTRANSLATE;
				break;
			case KBD_EXIT:
				exit();
				break;
			}
		}
		/*
		** display data received from the keyboard.
		*/
		while((c = kbdchar()) != -1) {
			kbdstart=1;
			lprintf("\n hex=0x%x", c);
		}
		if (kbdstart) {
			kbdstart = 0;
			lprintf("\n");
		}
	}
}
