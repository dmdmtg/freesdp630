#ident	"@(#)libc-mc68:crt/fltst.c	3.5"
/*
 *	floating-point test -- specific to 68000
 */

int
fltst (x)
	long x;
{

	return (x != 0);
}
