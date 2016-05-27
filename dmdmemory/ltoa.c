/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)ltoa.c	1.1.1.1	(5/10/87)";

static char *ps;
static char digits[] = "0123456789abcdef";
    
char *
ltoa (n, base)
register long n;
register unsigned base;
{
	static char asci[15];

	if (base == 16) {
		asci[0] = '0';
		asci[1] = 'x';
		ps = &asci[2];
	}
	else
		ps = asci;

	lconv(n, base);
	return (asci);
}

lconv (n, base)
register long n;
register unsigned base;
{   
    register long a;

	if (a = n/base)
	    lconv (a, base);

	*ps++ = digits[n%base];
	*ps = '\0';
}


long
lmin (a, b)
long a, b;
{
	return ((a > b) ? b : a);
}


long
lmax (a, b)
long a, b;
{
	return ((a > b) ? a : b);
}

