#ident	"@(#)libc-mc68:crt/flneg.c	1.3"
/* change the sign of a floating-point number */

#include "fp.h"

fp
flneg (x)
	fp x;
{
	if (x.sign)
		x.sign = 0;
	else if (x.exp)
		x.sign = 1;
	return x;
}
