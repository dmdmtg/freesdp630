/*      Copyright (c) 1987 AT&T */
/*        All Rights Reserved   */

/*      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T     */
/*      The copyright notice above does not evidence any        */
/*      actual or intended publication of such source code.     */


static char _2Vsccsid[]="@(#)bprintf.c	1.1.1.1	(5/8/87)";

/* bprintf / bputchar
**
** The same as printf / putchar except they display at the *B*ottom of the
** screen.
*/

#include <dmd.h>
#include <font.h>

extern Point add();
extern Point string();

static Rectangle rect = {
	12, 650, XMAX-12, YMAX-12
	};

static Point PtCur;
static int first;

#define  DO		rect.origin
#define  DC		rect.corner

bprintf(fmt, args)
register char *fmt;
int args;
{
	register c;
	register int *p = &args;
	register long num;
	register int longflag = 0;
	register char *s;


	while ( (c=*fmt++) ) {
		if (c != '%')
			bputchar (c);
		else {
			c = *fmt++;

			if(c == 'l') {		/* long specification */
				++longflag;
				c = *fmt++;
				num = *((long *)p);
			}
			else {
				num = (long)*p;
			}

			if (c=='d') {			/* decimal */
				if(num < 0) {
					bputchar ('-');
					num = -num;
				}
				bprintf_putnum (num, 10);
			}
			else if (c == 'o') {		/* octal */
				if(num < 0 && !longflag)
					num &= 0xFFFF;
				bprintf_putnum (num, 8);
			}
			else if (c == 'x') {		/* hexadecimal */
				if(num < 0 && !longflag)
					num &= 0xFFFF;
				bprintf_putnum (num, 16);
			}
			else if (c == 'c') {		/* single character */
				bputchar ((char)*p);
			}
			else if (c == 's') {		/* string */
				++longflag;
				s = *((char **)p);
				while (c = *s++)
					bputchar (c);
			}
			else {				/* not conversion char */
				bputchar (c);
				/* so p will be unchanged when incremented below */
				longflag = 0; --p;
			}

			++p;
			if(longflag) {
				longflag = 0;
				++p;
			}
		}
	}
}

bprintf_putnum (n, base)
register long n;
register unsigned base;
{
	register long a;
	static char digits[] = "0123456789ABCDEF";

	if (a = n/base)
		bprintf_putnum (a, base);
	bputchar (digits[n%base]);
}

bputchar (c)
register char c;
{
	char s[2];
	Point curpos;
	register int num, more;

	if(!first) {
		first = 1;
		myLgrey( Rect(0,rect.origin.y-10,XMAX,YMAX) );
		rectf(&physical, rect, F_CLR);
		PtCur = add(rect.origin, Pt(2,2));
	}

	c &= 0x7f;  /* protect against bad arguments */
	s[0] = c;
	s[1] = '\0';
	curpos = PtCur;

	switch (c) {

	case '\n' :	/* newline */
		if ( (curpos.y + (2 * FONTHEIGHT(largefont)) ) > DC.y )
			bputchar_scroll(DC.y - curpos.y);
		else
			curpos.y += FONTHEIGHT(largefont);
		/* no break */

	case '\r' :	/* carriage return */
		curpos.x = DO.x;
		break;

	case '\t' :	/* tab */
		num = (curpos.x - DO.x)/FONTWIDTH(largefont);
		more = (num|7) + 1 - num;
		while (more--)
			bputchar(' ');
		curpos = PtCur;
		break;

	default:
		curpos = string(&largefont, s, &physical, curpos, F_STORE);
		if(curpos.x + FONTWIDTH(largefont) >= DC.x) {
			bputchar('\n');
			curpos = PtCur;
		}
		break;
	}

	PtCur = curpos;
}

bputchar_scroll(n)
short n;
{
	Rectangle s;

	s = rect;
	s.origin.y += FONTHEIGHT(largefont);
	bitblt (&physical, s, &physical, DO, F_STORE);
	rectf (&physical, Rect(DO.x, DC.y-n, DC.x, DC.y), F_CLR);
}

static
myLgrey(r)
Rectangle r;
{
	static Word greymap[16]={
		0x1111, 0x4444, 0x1111, 0x4444,
		0x1111, 0x4444, 0x1111, 0x4444,
		0x1111, 0x4444, 0x1111, 0x4444,
		0x1111, 0x4444, 0x1111, 0x4444,
	};

	texture(&physical, r, greymap, F_STORE);
}
