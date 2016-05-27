/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)bounce.c	1.1.1.3	(5/10/87)";

#include <dmd.h>

#define N 25
Point foo[] = {
	312, 799,
	650, 650,
	7, -11
	-5, 3,
	13, 7,
	3, 11,
};
char *speedText[] = {
  "fast",
  " .  ",
  " .  ",
  " .  ",
  "slow",
  NULL
};
Menu speedMenu = {
	speedText
};

main()
{
	register speed=1, item;
	register i = 0, j;
	Point from[N], to[N];
	Point dfrom, dto;

	local();
	request(KBD|MOUSE);
	P->state |= RESHAPED;
	for (; kbdchar() != 'q'; sleep (speed)) {
		if (button1 ()) {
			if ((item = menuhit (&speedMenu, 1)) != -1) {
				speed = 1<<item;
			}
		}
		if (bttn3 ()) {
		  request (KBD);	/* Unrequesting "MOUSE" */
		  sleep (1);		/* allows the DMD to display */
		  request (KBD|MOUSE);	/* the button 3 menu. */
		}
		if (P->state & RESHAPED) {
			if (!(P->state & MOVED)) {
				rectf (&display, Drect, F_XOR);
				for(j=0; j<N; j++){
					from[j].x=0; from[j].y=0;
					to[j].x=0; to[j].y=0;
				}
				from[0] = foo[0];
				from[1] = foo[0];
				to[0] = foo[1];
				to[1] = foo[1];
				dfrom = foo[2];
				dto = foo[3];
			}
			P->state &= ~(MOVED|RESHAPED);
		}
		j = i;
		if (++i >= N)
			i = 0;
		jsegment(from[i], to[i], F_XOR);
		from[i] = from[j];
		bump(&from[i], &dfrom);
		to[i] = to[j];
		bump(&to[i], &dto);
		jsegment(from[i], to[i], F_XOR);
	}
}

bump(p,dp)
register Point *p, *dp;
{
	if ((p->x += dp->x) > XMAX || p->x < 0) {
		dp->x = -dp->x;
		p->x += dp->x << 1;
	}
	if ((p->y += dp->y) > YMAX || p->y < 0) {
		dp->y = -dp->y;
		p->y += dp->y << 1;
	}
}
