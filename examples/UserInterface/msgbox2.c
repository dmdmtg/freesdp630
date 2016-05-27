/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)msgbox2.c	1.1.1.2	(6/1/87)";

#include <dmd.h>

/* Library routines and associated manual page. */
void bttns();           /* BUTTONS(3R)          */
void exit();            /* EXIT(3R)             */
int kbdchar();          /* KBDCHAR(3R)          */
int menuhit();		/* MENUHIT(3L)		*/ 
int msgbox();           /* MSGBOX(3R)           */
int request();          /* RESOURCES(3R)        */
void ringbell();	/* RINGBELL(3R)		*/
int wait();             /* RESOURCES(3R)        */

/* Library macros and associated manual page.   */
/* int button1()	   BUTTONS(3R)		*/
/* int button2()	   BUTTONS(3R)		*/

char *menutext[] = {
	"Message Boxes",
	"Help",
	"Default",
	"Small Box",
	"Medium Box",
	"Big Box",
	"DON'T CHOOSE!",
	"Style",
	"Exit",
	(char *)0
	};

Menu menu = { menutext };

char *stylemenutext[] = {
	"Confirm",
	(char *)0
	};

Menu stylemenu = { stylemenutext };

main()
{

	request(MOUSE);
	for(;;) {
		wait(MOUSE);
		if(button1())
			break;
		if(button2()) {
			switch( menuhit(&menu, 2) ) {
			case 0:
				msgbox("Hey!",
				       "Hey!",
				       "MESSAGE BOXES",
				       (char *)0
				       );
				bttns(0);
				break;
			case 1:
				msgbox( "Help is on the way.",
					(char *)0
					);
				bttns(0);
				break;
			case 2: /* default - no memory */
				msgbox((char *)0);
				bttns(0);
				break;
			case 3:
				msgbox("X", (char *)0);
				bttns(0);
				break;
			case 4:
				msgbox("This is an example",
				       "of a slightly",
				       "larger message box.",
				       "The quick brown fox jumps over the lazy dog",
				       (char *)0
				       );
				bttns(0);
				break;
			case 5:
				msgbox( "This is a",
					"REALLY",
					"BIG",
					"message",
					"box",
					"The quick brown fox jumps over the lazy dog three times, turns around twice and then drops dead",
					(char *)0
					);
				bttns(0);
				break;
			case 6:
				msgbox( "PLEASE",
					"do",
					"not",
					"choose",
					"this",
					"item",
					"again",
					(char *)0
					);
				bttns(0);
				break;
			case 7:
				msgbox( "A different style",
					"-----------------",
					"Do you want to ring the bell?",
					"Press button 2 to confirm",
					(char *)0
					);
				if(button2())
					if(menuhit(&stylemenu, 2) == 0)
						ringbell();
				bttns(0);
				break;
			case 8:
				msgbox( "Exit the message box demo",
				        "by clicking button 1",
					"When there is no box on the screen",
				       (char *)0
				       );
				bttns(0);
				break;
			}
		}
	}
}
