/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)clock.c	1.1.1.3	(5/10/87)";

#include <dmd.h>
#include <font.h>

#define	atoi2(p)	((*(p)-'0')*10 + *((p)+1)-'0')
#define	itoa2(n, s)	{ (*(s) = (n)/10 + '0'); (*((s)+1) = n % 10 + '0'); }

extern Point string();
extern Point add();
extern long realtime();

Point	ctr; 		 	/* center point of window */
int	h, m, s;         	/* hour, min, sec */
int	rh, rm, rs;		/* radius of h m and s */
int     rspread;        	/* spread of base of hands at ctr */
int	ah = 0, am = 0, as = 0;	/* angles based on 360 degrees of circle */
int	lah, lam, las;	        /* last angles */
int     first ;

main(argc, argv)
char *argv[];
{
	char date[40];
	register long oldtime;
	register long ds;
	register olds;

	/* do initialization */
	oldtime=realtime();
	request(KBD);
	rectf(&display, Drect, F_XOR);
	if(argc!=2){
		jmoveto(Pt(0, 0));
		jstring("Usage: dmdld clock \"`date`\"");
		sleep(200);
		exit();
	}
	local();
	initface();
	strcpy(date, argv[1]);
	h = atoi2(date+11);
	m = atoi2(date+14);
	s = atoi2(date+17);

	/* main loop for clock */
	for ( ds = 0l;; ) {
		/* process times */
		while (realtime() <= oldtime)
			sleep(20);
		ds += realtime()-oldtime;  /* elapsed ticks (1/60 sec) */
		oldtime=realtime();
		s += ds / 60;   /* calulate seconds */
		ds %= 60;       /* left over ticks  */
		if (olds == s)
			continue;
		/* calculate seconds, minutes and hours */
		while (s >= 60) {
			s -= 60;
			m++;
		}
		olds = s;
		while (m >= 60) {
			m -= 60;
			h++;
			if (h >= 24)
				h = 0;
		}

		/* save old angle */
		lah = ah;
		lam = am;
		las = as;
		/* calulate new angles */
		ah = (30 * (h%12) + 30 * m / 60);
		am = 6 * m;
		as = 6 * s;

		if (P->state & RESHAPED) {
			initface();
			P->state &= ~RESHAPED;
		}
	        if ( kbdchar() == 'q' )
			exit();

		/* write digital time to display */
		strcpy(date, "00:00:00");
		itoa2(h, date);
		itoa2(m, date+3);
		itoa2(s, date+6);
		string(&mediumfont,date,&display,add(Drect.origin,Pt(1,1)),
		       F_STORE);

		/* draw the hands of the clock */
		if(first) {
			ray(rs, as, rspread/2);	/* longest */
			ray(rm, am, rspread);
			ray(rh, ah, rspread);
			first = 0;
		}

		else {
			if(lah != ah) {
				ray(rh, lah, rspread);
				ray(rh, ah, rspread);
			}
			if(lam != am) {
				ray(rm, lam, rspread);
				ray(rm, am, rspread);
			}
			ray(rs, las, rspread/2);
			ray(rs, as, rspread/2);
		}

	}
}

/* set up clock circle in window */
initface()
{
	int	rad;

	rectf(&display, Drect, F_CLR);
	ctr.x = (Drect.corner.x + Drect.origin.x) / 2;
	ctr.y = (Drect.corner.y + Drect.origin.y) / 2;
	rad = Drect.corner.x - Drect.origin.x;
	if (rad > Drect.corner.y - Drect.origin.y)
		rad = Drect.corner.y - Drect.origin.y;
	rad = rad/2 - 2;
	rh = 6 * rad / 10;
	rm = 9 * rad / 10;
	rs = rad - 1;
	rspread = rad / 10;
	disc(&display, ctr, rad, F_STORE);
	first = 1;
}


/* draw ray r at angle ang.                                     */
/* actually draws a clock hand at angle ang, with the hand at a */
/* point length r from the ctr, and the base of the hand spread */
/* by rspr.                                                      */

ray(r,ang,rspr)
register int r, ang, rspr;
{
	register int dx, dy;
	register int ddx1, ddx2, ddy1, ddy2;

	dx = muldiv(r, Isin(ang), 1024);
	ddx1 = muldiv(rspr, Isin(ang-90), 1024);
	ddx2 = muldiv(rspr, Isin(ang+90), 1024);
	dy = muldiv(-r, Icos(ang), 1024);
	ddy1 = muldiv(-rspr, Icos(ang-90), 1024);
	ddy2 = muldiv(-rspr, Icos(ang+90), 1024);
	segment(&display, add(ctr, Pt(ddx1,ddy1)), add(ctr, Pt(dx,dy)), F_XOR);
	segment(&display, add(ctr, Pt(ddx2,ddy2)), add(ctr, Pt(dx,dy)), F_XOR);
}
