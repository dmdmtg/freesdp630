/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)clipfix.c	1.1.1.2	(5/10/87)";

#include <dmd.h>

/* clipprefix -	clip the pathname prefix from the filename
*/
char *
clipprefix (s)
register char *s;
{
	static char filename[128];
	register char *f;

	for (f = filename; *s; s++) {
		if (*s == '/')
			f = filename;
		else
			*f++ = *s;
	}
	*f = '\0';
	return (filename);
}


/* clipsuffix -	clip the "." suffix from the filename
*/
char *
clipsuffix (s)
register char *s;
{
	static char filename[128];
	register char *f = filename;

	while (*s != '.' && *s) {
		*f++ = *s++;
	} 
	*f = '\0';
	return (filename);
}
