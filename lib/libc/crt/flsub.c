#ident	"@(#)libc-mc68:crt/flsub.c	1.3"
/* subtract two floating-point numbers */

#include "fp.h"

fp
flsub (x, y)
	fp x, y;
{
	if (x.sign != y.sign)
		return fp_addmag (x, y);
	else
		return fp_submag (x, y);
}
