#ident	"@(#)libc-mc68:crt/ltof.c	1.3"
/*
 *	long signed integer to float
 */

#include "fp.h"

fp
ltof (x)
	register long x;
{
	fp result;

	if (x >= 0)
		return ultof ((unsigned long) x);
	
	result = ultof ((unsigned long) -x);
	result.sign = 1;

	return result;
}
