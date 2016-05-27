/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)atan2.c	1.1.1.2	(5/10/87)";

static Iqatan2();
Iatan2(xx, yy){
	register x, y;
	x=abs(xx);
	y=abs(yy);
	if(xx>=0 && yy>=0)
		return(Iqatan2(x, y));
	if(xx<0 && yy<0)
		return(180+Iqatan2(x, y));
	if(xx<0 && yy>0)
		return(180-Iqatan2(x, y));
	return(360-Iqatan2(x, y));
}
static
Iqatan2(x, y)
	register x, y;
{
	if(x<y)
		return(90-(45*((long)x)/y));
	if(y==0)
		return(0);
	return(45*((long)y)/x);
}
