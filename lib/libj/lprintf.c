/*      Copyright (c) 1987 AT&T */
/*        All Rights Reserved   */

/*      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T     */
/*      The copyright notice above does not evidence any        */
/*      actual or intended publication of such source code.     */


static char _2Vsccsid[]="@(#)lprintf.c	1.1.1.1	(5/8/87)";

/*
** FUNCTION:	lprintf / lputchar
**
** SYNOPSIS:	lprintf(fmt, arg1, arg2, ...)
**		lputchar(c)
**
** DESCRIPTION:	lprintf
**
**   		lprintf converts, and prints its arguments on the layer
**		starting at the current point (global variable sPtCurrent),
**		under the control of the string fmt.
**
**		The fmt string contains ordinary characters, which are
**		simply copied to the layer, and conversion specifications,
**		each of which causes conversion and printing of the next
**		successive argument to lprintf.
**
**		Each conversion specification is introduced by the character
**		% and followed by a conversion character. These conversion
**		options will be accepted:
**
**			d	The argument is converted to decimal notation.
**			o	The argument is converted to unsigned octal
**				notation (without a leading 0).
**			x	The argument is converted to unsigned hex
**				notation (without a leading 0x).
**			c	The argument is taken to be a single character.
**			s	The argument is a string; characters from the
**				string are printed until a null character is
**				reached.
**
**		If the character after the % is not one of the above conversion
**		character, that character is printed.
**
**		lputchar
**
**		These blank characters are processed:
**
**			\n	Newline. Scroll if necesary.
**			\r	Carriage return. The x coord of the current
**				point is reset to layers coord 0.
**			\t	Tab. Tabs are set every 8 characters from the
**				left border of layer.
**
** NOTES :	Since lprintf/lputchar uses sPtCurrent and moveto(). That leads
**		to the following considerations:
**
**		Applications can affect where printing will occur with
**		the moveto() function.
**
**		sPtCurrent is stored as an offset off Drect.origin in
**		screen coordinates (see comments in moveto.c).
**
**		Since sPtCurrent is stored as an offset, Moves between calls
**		to lprintf are handled properly. Reshapes, however, are a
**		problem (see comments in moveto.c). After a layer is
**		reshaped, if the offset is still in the window, printing
**		will continue at the offset into the new window that printing
**		was occurring before the reshape. If the offset is no longer
**		in the window, the current point will move to Drect.origin.
**		If an application wants to do a better job of this, it
**		should watch RESHAPED and call moveto(Drect.origin):
**
**			if(P->state&RESHAPED) {
**				if(!(P->state&MOVED))
**					moveto(Drect.origin);
**				P->state &= ~(MOVED|RESHAPED);
**			}
*/ 
 
#include <dmd.h>

/* This currently always uses largefont. I would prefer to use the font set
** in setup, but there is currently no way to determine this.
*/

#define  DO		Drect.origin
#define  DC		Drect.corner

lprintf(fmt, args)
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
			lputchar (c);
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
					lputchar ('-');
					num = -num;
				}
				lprintf_putnum (num, 10);
			}
			else if (c == 'o') {		/* octal */
				if(num < 0 && !longflag)
					num &= 0xFFFF;
				lprintf_putnum (num, 8);
			}
			else if (c == 'x') {		/* hexadecimal */
				if(num < 0 && !longflag)
					num &= 0xFFFF;
				lprintf_putnum (num, 16);
			}
			else if (c == 'c') {		/* single character */
				lputchar ((char)*p);
			}
			else if (c == 's') {		/* string */
				++longflag;
				s = *((char **)p);
				while (c = *s++)
					lputchar (c);
			}
			else {				/* not conversion char */
				lputchar (c);
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

lprintf_putnum (n, base)
register long n;
register unsigned base;
{
	register long a;
	static char digits[] = "0123456789ABCDEF";

	if (a = n/base)
		lprintf_putnum (a, base);
	lputchar (digits[n%base]);
}
