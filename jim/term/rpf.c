/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)rpf.c	1.1.1.1	(5/8/87)";

/* Debug function to print the value of a rectangle */
#include <dmd.h>
rpf(r_ptr) 
Rectangle *r_ptr; 
{
fpf("call to rpf:  Rectange=%ld\n", *r_ptr);
fpf("Rectange:  Origin at (%d,%d): Corner at (%d,%d)\n",r_ptr->origin.x,r_ptr->origin.y, r_ptr->corner.x, r_ptr->corner.y);
}


