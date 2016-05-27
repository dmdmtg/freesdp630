/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)sprintf.c	1.1.1.4	(5/10/87)";

#include <dmdio.h>

Sprintf(s, format, args)
char *s;
char *format;
char *args;
{
	FILE fout;
	FILE *f;
	int ret;

	f = &fout;
	f->file = _NFILE;
	f->base = 0;
	f->cp = s;
	f->flag = 0;
	f->count = 0;
	ret = _Doprnt(f, format, &args);
	s[ret] = '\0';
	return ret;
}

