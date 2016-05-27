/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)rose.c	1.1.1.2	(5/10/87)";


/*
 * ROSE
 *
 * A dmd program to generate random patterns derived from the
 * polar equation r=sin(lp*theta).  The two parameters of the
 * program are lp (number of loops) and dt (the amount by which
 * theta is incremented for each new point).  If you want continuous
 * random patterns, NONSTOP should be defined as 1 (the default).
 * Defining NONSTOP as 0 lets you enter the parameters each time.
 * Even if you enter the parameters, if you just hit <CR> you will
 * get random values.  To stop things when NONSTOP is 1 (continuous
 * random patterns), just hit any key.  To stop things when NONSTOP
 * is 0 (i.e. you are entering values), just enter a negative value
 * for 'loops'.
 */

#include <dmd.h>

#ifndef NONSTOP
#define NONSTOP 1
#endif


main()
{
	char buff[100];
	int cn, r, k, t, dt, lp, x, rx, ry;
	int oldx, oldy, newx, newy;
	int offx, offy;
	Point jstring();
	char *getstring();
	Point p;
	int nonstop = NONSTOP;

	local();
	request(MOUSE);
	/* random number seed is derived from position of dmd layer */
	srand(mouse.xy.x);
	request(KBD);
	for ( ;; ) {
		lp = dt = 0;
		if ( nonstop == 0 ) {
			/* ask for lp parameter */
			jmoveto(Pt(0,0));
			p = jstring("loops=");
			lp = getnum(p);
			jmoveto(Pt(0,0));
			jstring("loops=");
		}
		if ( lp < 0 )
			exit();
		if ( lp == 0 )
			lp = rand() % 31 + 1;

		if ( nonstop == 0 ) {
			/* ask for dt parameter */
			jmoveto(Pt(0,0));
			p = jstring("delta=");
			dt = getnum(p);
			jmoveto(Pt(0,0));
			jstring("delta=");
		}
		if ( dt <= 0 )
			dt = rand() % 358 + 1;

		/* clear screen */
		jrectf(Jrect,F_CLR);
		t=0; 
		oldx = offx = XMAX / 2;
		oldy = offy = YMAX / 2;
		cn = 1;
		/* draw rose */
		do {
			t=(t+dt)%360;
			x=(lp*t)%360;
			r = Isin(x);
			rx=muldiv(r,XMAX-1,1024);
			ry=muldiv(r,YMAX-1,1024);
			newx = offx + muldiv(rx,Icos(t),1024) / 2;
			newy = offy +  muldiv(ry,Isin(t),1024) / 2;
			jsegment(Pt(oldx,oldy),Pt(newx,newy),F_STORE);
			oldx=newx; 
			oldy=newy;
			/* give up the CPU every 10 times around */
			if ( cn++ > 10 ) {
				cn = 0;
				sleep(4);
			}
		} while ( t != 0 && (k=kbdchar()) != 'q' ) ;
		if ( nonstop == 1 ) {
			/* in nonstop mode, any key aborts */
			if ( k != -1 )
				exit();
			/* sleep 2 seconds between random patterns */
			sleep(120);
		}
	}
}

getnum(p)
Point p;
{
	static char strbuff[32];
	char s[2];
	int c;
	Point m; register int i;

	strbuff[i=0] = '\0';
	m = p;
	wait(KBD);
	for( ; (c=kbdchar())!='\r'; wait(KBD)) {
		switch (c) {
		case '@':
			jmoveto(p);
			jstring(strbuff);
			i=0;
			m=p;
			break;
		case '\b':
			jmoveto(p);
			jstring(strbuff);
			strbuff[(i>0)? --i : 0] = '\0';
			jmoveto(p);
			m = jstring(strbuff);
			break;
		case '+':
		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if ( c == '+' || c == '-' && i != 0 )
				break;
			/* add character to saved string */
			strbuff[i++] = c;
			strbuff[i] = '\0';
			/* echo character */
			jmoveto(m);
			s[0]=c; s[1] = '\0';
			m = jstring(s);
			break;
		}
	}
	jmoveto(p);
	jstring(strbuff);
	return(atoi(strbuff));
}

