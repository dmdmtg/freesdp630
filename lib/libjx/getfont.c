/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)getfont.c	1.1.1.2	(5/10/87)";

#include	<dmd.h>
#include	<font.h>
#include	<dmdio.h>

extern Font *infont();

/*static*/ FILE *inf;

static
cget()
{
	return(getc(inf));
}

Font *
getfont(s)
	char *s;
{
	Font *f;

	if((inf = fopen(s, "r")) == (FILE *)0)
	{
		return((Font *)0);
	}

	f = infont(cget);
	fclose(inf);
	return(f);
}
