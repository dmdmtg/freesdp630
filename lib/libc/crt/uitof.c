#ident	"@(#)libc-mc68:crt/uitof.c	1.3"
/*
 *	unsigned integer to float
 */

#include "fp.h"

fp
uitof (x)
	register unsigned x;
{
	fp result;
	long frac;
	register int exp;
	
	/* converting zero? */
	if (x == 0)
		return zero;
	
	/* create an unnormalized fraction and exponent */
	frac = x;
	exp = EXPOFFSET + FRACSIZE + 1;

	/* normalize */
	while ((frac & HIDDENBIT) == 0) {
		frac <<= 1;
		exp--;
	}

	/* store the result */
	result.sign = 0;
	result.exp = exp;
	result.frac = frac & ~HIDDENBIT;

	return result;
}
