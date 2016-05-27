/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)smprintf.c	1.1.1.3	(5/10/87)";

#include <dmdio.h>
extern putchar();

printf(fmt, args)
char *fmt;
int args;
{
	if(whathost() == -1)
		return;
        _doprnt(putchar, fmt, &args);
}

/*
**	fprintf()
**
*/

static FILE *_fp;

_fputc(c)
char c;
{
        putc(c, _fp);
}

fprintf(f, fmt, args)
FILE *f;
char *fmt;
int args;
{
	if(whathost() == -1)
		return;
        _fp = f;
        _doprnt(_fputc, fmt, &args);
}
