/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)setLED.c	1.1.1.3	(5/8/87)";


#include <dmd.h>
#include <kbd_proc.h>
#include <label.h>

setLEDscr(i)
int i;
{
/* set the scroll lock LED */
	Proc *kp = P;

	if(i) /* on */
	{
		kp->kbd_LEDs |= SCR_LED;
		kp->state |= SCR_LOCK;
		labelicon(&B_scroll, L_SCROLL_POSITION);
	}
	else /* off */
	{
		kp->kbd_LEDs &= ~SCR_LED;
		kp->state &= ~SCR_LOCK;
		labelicon((Bitmap *)0, L_SCROLL_POSITION);
	}
	if(kp == kbdproc) /* I'm current, set the LED */
		sendtokbd(kp->kbd_LEDs);
}

setLEDcap(i)
int i;
{
/* set the cap loc LED */
	Proc *kp = P;

	if(i) /* on */
	{
		kp->kbd_LEDs |= CAP_LED;
		labelicon(&B_cap, L_CAP_POSITION);
	}
	else /* off */
	{
		kp->kbd_LEDs &= ~CAP_LED;
		labelicon((Bitmap *)0, L_CAP_POSITION);
	}
	if(kp == kbdproc) /* I'm current, set the LED */
		sendtokbd(kp->kbd_LEDs);
}

click()
{
/* click from the keyboard */
/* the firmware version wouldn't work when not current */
	sendtokbd(kbdproc? kbdproc->kbd_LEDs|CLICKBIT : CLICKBIT);
}

