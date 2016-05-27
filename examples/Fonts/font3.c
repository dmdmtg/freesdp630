/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)font3.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <font.h>
#include <dmdio.h>

/*Library routines and associated manual pages.	*/
int fontcache();	/* FONTSAVE(3L)		*/ 
Font *getfont();	/* INFONT(3L/3R)	*/
Point sPtCurrent();	/* MOVETO(3L)		*/

/* Global Variables */
Font *fp;

/*
** This program must be downloaded using jx.
** The pathname of the desired font is passed to
** the program as a command line argument using
** "argc" and "argv".
*/
main(argc, argv)
int argc;
char *argv[];
{
	lprintf("\n Loading font %s\n ", argv[1]);

	/*
	** Download the font into 630 memory.
	*/
	fp = getfont(argv[1]);

	/*
	** Place the font into the font cache.
	*/
	fontcache(argv[1], fp);

	/*
	** Display the string "This is a test."
	** using the downloaded font.
	*/
	string(fp, "This is a test.", &display, sPtCurrent(), F_STORE);

	/*
	** Exit when the user types any key
	** on the keyboard.
	*/
	request(KBD);
	while(kbdchar() == -1) wait(KBD);
	exit();
}
