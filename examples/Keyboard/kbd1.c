/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)kbd1.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <keycodes.h>

/*Library routines and associated manual pages.	*/
void exit();		/* EXIT(3R)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
void lprintf();		/* PRINTF(3L)		*/
void rectf();		/* RECTF(3R)		*/
int request();		/* RESOURCES(3R)	*/
void texture();		/* TEXTURE(3R)		*/
int wait();		/* RESOURCE(3R)		*/

extern Texture16 T_lightgrey;
extern Texture16 T_darkgrey;

main()
{
	unsigned char c;

	request(KBD);

	/*
	** Set no pf key expansion.
	*/
	P->state |= NOPFEXPAND;

	lprintf("\n Hit any PF Key.");
	lprintf("\n Use 'q' to quit");

	for(;;) {
		wait(KBD);
		c = (unsigned char)kbdchar();
		switch(c) {
		/*
		** Display a different texture for each
		** function key hit.
		*/
		case FUNC1KEY:
			texture(&display, Drect, &T_grey, F_STORE);
			break;
		case FUNC2KEY:
			texture(&display, Drect, &T_lightgrey, F_STORE);
			break;
		case FUNC3KEY:
			texture(&display, Drect, &T_darkgrey, F_STORE);
			break;
		case FUNC4KEY:
			texture(&display, Drect, &T_black, F_STORE);
			break;
		case FUNC5KEY:
			texture(&display, Drect, &T_white, F_STORE);
			break;
		case FUNC6KEY:
			texture(&display, Drect, &T_background, F_STORE);
			break;
		case FUNC7KEY:
			texture(&display, Drect, &T_checks, F_STORE);
			break;
		case FUNC8KEY:
			texture(&display, Drect, &C_target, F_STORE);
			break;
		case FUNC9KEY:
			texture(&display, Drect, &C_arrows, F_STORE);
			break;
		case FUNC10KEY:
			texture(&display, Drect, &C_insert, F_STORE);
			break;
		case FUNC11KEY:
			texture(&display, Drect, &C_cup, F_STORE);
			break;
		case FUNC12KEY:
			texture(&display, Drect, &C_deadmouse, F_STORE);
			break;
		case FUNC13KEY:
			texture(&display, Drect, &C_skull, F_STORE);
			break;
		case FUNC14KEY:
			rectf(&display, Drect, F_XOR);
			break;
		case 'q':
			exit();
		}
	}
}
	
