#ident	"@(#)libc-mc68:crt/itof.c	1.3"
/*
 *	signed integer to float
 */

#include "fp.h"

fp
itof (x)
	register int x;
{
	fp result;

	if (x >= 0)
		return uitof ((unsigned) x);
	
	result = uitof ((unsigned) -x);
	result.sign = 1;

	return result;
}
