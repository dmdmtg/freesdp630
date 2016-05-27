#ident	"@(#)libc-mc68:crt/fladd.c	1.3"
/* add two floating-point numbers */

#include "fp.h"

fp
fladd (x, y)
	fp x, y;
{
	if (x.sign == y.sign)
		return fp_addmag (x, y);
	else
		return fp_submag (x, y);
}
