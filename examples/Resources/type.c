/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)type.c	1.1.1.2	(5/22/87)";

#include <dmd.h>

#define NEWLINE 0x0a
#define RETURN  0x0d

/* Library Routines and associated manual page. */
void exit();		/* EXIT(3R)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
void lprintf();		/* PRINTF(3R)		*/
void lputchar();	/* LPUTCHAR(3L);	*/
int psendchar();	/* PSENDCHAR(3R)	*/
int request();		/* RESOURCES(3R)	*/
int wait();		/* RESOURCES(3R)	*/

main()
{
	char c;
	int resources;

	/*
	** Request the use of the keyboard
	** and the printer.
	*/
	resources = request(KBD|PSEND);

	/*
	** If the request for the printer resource failed,
	** ask the user if he wants to try the request
	** again.  If not then exit.
	*/
	while (!(resources & PSEND)) {
		lprintf("\n Printer Not Available.\n");
		lprintf(" Shall I try again? (y/n)\n");

		while ((c=kbdchar()) == -1) wait(KBD);
		if(c == 'y' || c == 'Y')
			resources = request(KBD|PSEND);
		else
			exit();
	}

	lprintf(" Type @ to quit.\n");
	/*
	** Send all characters typed to the printer.
	*/
	for(;;) {
		while ((c = kbdchar()) == -1) wait(KBD);
		if (c == '@') {
			exit();
		} else {
			/*
			** Echo character on the screen
			** and then send it to the printer.
			*/
			lputchar(c);
			psendchar(c);
			if (c == RETURN) {
				lputchar(NEWLINE);
				psendchar(NEWLINE);
			}
		}
	}
}
