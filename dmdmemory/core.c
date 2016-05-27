/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)core.c	1.1.1.1	(5/10/87)";

#include <dmd.h>
#include "defines.h"
#include "globals.h"

long *gc_fndblk(), *gc_nxtblk();
long *a_fndblk(), *a_nxtblk();


long *
gcfindblk (addr, psize)
long *addr;
long *psize;
{
	register long *p;

	p = gc_fndblk (addr, psize);
	gcclip (p, psize); 
	return (p);
}

gclast (hdr)
long *hdr;
{
	return (gc_lstblk(hdr) || hdr < (long *)CoreStart);
}

long *
gcnext (hdr, psize)
long *hdr;
long *psize;
{
	register long *p;

	p = gc_nxtblk (hdr, psize);
	gcclip (p, psize);
	return (p);
}


gcis (hdr)
long *hdr;
{
	return (gc_blk(hdr) ? GC_BUSY : GC_FREE);
}


gcclip (hdr, psize)
long *hdr;
long *psize;
{
	register long n;	

	if ((n = CoreStart - (long)hdr) > 0)
		*psize -= n;
}


long *
acfindblk (addr, psize)
long *addr;
long *psize;
{
	register long *p;

	p = a_fndblk (addr, psize);
	acclip (p, psize);
	return (p);
}


acclip (hdr, psize)
long *hdr;
long *psize;
{
	register long n;
	register long *h2;
	long dummy;

	h2 = a_nxtblk (hdr, &dummy);

	if ((n = (long)h2 - CoreEnd) > 0)
		*psize -= n;
}

long *
acnext (hdr, psize)
long *hdr;
long *psize;
{
	long *p;

	p = a_nxtblk (hdr, psize);
	acclip (p, psize);
	return (p);
}

acis (hdr)
long *hdr;
{
	switch (a_blk(hdr)) {
		case 0:	return (A_FREE);
		case 1:	return (A_BUSY);
		case 2:	return (GC_ASTRAY);
	}
}


aclast (hdr)
long *hdr;
{
	long *h2;
	long dummy;

	h2 = a_nxtblk (hdr, &dummy);
	return (a_lstblk (hdr) || h2 > (long *)CoreEnd);
}
