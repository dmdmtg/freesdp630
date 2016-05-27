/*      Copyright (c) 1987 AT&T */
/*        All Rights Reserved   */

/*      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T     */
/*      The copyright notice above does not evidence any        */
/*      actual or intended publication of such source code.     */


static char _2Vsccsid[]="@(#)point2win.c	1.1.1.2	3/24/87";

#include <dmd.h>

Texture16 *Cursswitch();
Layer *whichlayer();

Proc *
point2window(but)
int but;
{
	register Layer *l;
	register Proc *z = 0;
	register Texture16 *old_mcurse;
	extern Proc *whichproc();

	old_mcurse = Cursswitch(&C_target);
	bttns(1);
	if ((RealMouse.buttons & (8 >> but)) && (l = whichlayer()))
		z = whichproc(l);
	bttns(0);
	Cursswitch(old_mcurse); 	/* reset to original cursor */
	return(z);
}
