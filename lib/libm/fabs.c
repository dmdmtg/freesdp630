#ident	"@(#)libm:fabs.c	1.4.1.1"
/*LINTLIBRARY*/
/*
 *	fabs returns the absolute value of its double-precision argument.
 */

double
fabs(x)
register double x;
{
	return (x < 0 ? -x : x);
}
