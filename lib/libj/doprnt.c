/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)doprnt.c	1.1.1.3	(5/10/87)";

/*
**	FUNCTION:	_doprnt - small parser for printing routines
**
**	SYNOPSIS:	_doprnt(func, fmt, args)
**			void (*func)();
**			char *fmt;
**			int *args;
**
**	DESCRIPTION:
**			The _doprnt function does the parsing of the
**			format string for all the small print functions.
**			The first argument, func, is a function which
**			takes as an argument a single character to be
**			printed. The second argument is the format string
**			given the print function. The final argument is
**			a pointer to the first argument of the argument
**			list given the print function.
**
**			Look at printf.c for a more complete description
**			of the parsing.
**
**			There is no return value.
*/

_doprnt(func, fmt, args)
register void (*func)();
register char *fmt;
int *args;
{
	register c;
	register int *p = args;
	register long num;
	register int longflag = 0;
	register char *s;

	while ( (c=*fmt++) ) {
		if (c != '%')
			(*func) (c);
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
					(*func) ('-');
					num = -num;
				}
				doprnt_putnum (num, 10, func);
			}
			else if (c == 'o' || c == 'u' || c == 'x') {
				if(num < 0 && !longflag)
					num &= 0xFFFF;
				doprnt_putnum (num, c=='o'?8: (c=='x'? 16:10), func);
			}
			else if (c == 'D')
				doprnt_putnum(num, 10, func);
			else if (c == 'c') {		/* single character */
				(*func) ((char)*p);
			}
			else if (c == 's') {		/* string */
				++longflag;
				s = *((char **)p);
				while (c = *s++)
					(*func) (c);
			}
			else {				/* not conversion char */
				(*func) (c);
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

doprnt_putnum (n, base, func)
register long n;
register unsigned base;
void (*func)();
{ /* print an unsigned integer in the given base */
	register long a;
	static char digits[] = "0123456789ABCDEF";

	if (a = n/base)
		doprnt_putnum (a, base, func);
	(*func) (digits[n%base]);
}
