#ident	"@(#)libc-mc68:crt/frexp.c	1.3"
/*
 *	frexp - split a float into a fraction and exponent
 */

#include "fp.h"

fp
frexp (value, eptr)
	fp value;
	int *eptr;
{
	register exp;

	exp = value.exp;

	if (exp == 0) {
		*eptr = 0;
		return zero;
	}

	*eptr = exp - EXPOFFSET;
	value.exp = EXPOFFSET;

	return value;
}
