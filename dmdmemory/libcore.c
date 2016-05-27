/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)libcore.c	1.1.1.1	(5/10/87)";

/*
**	FIRMWARE VERSION DEPENDENT CODE
**
**	These routines and structures depend on the memory
**	management system as implemented for firmware release 1.0.
**	Future releases may change the allocation schemes.
*/
#include <dmd.h>


typedef struct aheader {
	struct aheader *next;
	long *proc;
} aheader;

typedef struct gheader {
	struct gheader *next;
	long *proc;
	long **backptr;
} gheader;

#define ASTARTP	(aheader *)memstartp
#define ALEVELP	(aheader *)alloclevel
#define GSTARTP	(gheader *)memendp
#define GLEVELP	(gheader *)gclevel

#define clrbusy(a)	(aheader *)((long)a & ~3)



aheader *
a_fndblk (addr, psize)
long addr;
long *psize;
{
	register aheader *p, *q;

	for (p = ASTARTP; p <= ALEVELP; p = q) {
		q = clrbusy (p->next);
		if (addr < (long)q) {
			*psize = (long)q - addr;
			return (p);
		}
	}

	return ((aheader *)0);
}

aheader *
a_header (addr, psize)
long addr;
long *psize;
{
	aheader *p = (aheader *)(addr - sizeof(aheader));
	*psize = (long)clrbusy(p->next) - (long)p;
	return (p);
}

aheader *
a_nxtblk (hdr, psize)
aheader *hdr;
long *psize;
{
	register aheader *p = clrbusy (hdr->next);

	*psize = (long)clrbusy(p->next) - (long)p;
	return (p);
}

a_lstblk (hdr)
aheader *hdr;
{
	return (hdr->next > ALEVELP);
}

a_blk (hdr)
aheader *hdr;
{
	switch ((long)hdr->next & 3l) {
		case 0:
			return (0);
		case 1:
			return (1);
		case 3:
			return (2);
	}
}

char *
a_own (hdr)
aheader *hdr;
{
	if (!(long)hdr->next & 3l)
		return ((char *)-1);
	else
		return ((char *)hdr->proc);
}




gheader *
gc_fndblk (addr, psize)
long addr;
long *psize;
{
	register gheader *p, *q;

	for (p = GSTARTP; p; p = q) {
		q = p->next;
		if (addr >= (long)q) {
			*psize = addr - (long)q;
			return (q);
		}
	}

	return ((gheader *)0);
}

gheader *
gc_nxtblk (hdr, psize)
gheader *hdr;
long *psize;
{
	register gheader *p = hdr->next;

	*psize = (long)hdr - (long)p;
	return (p);
}


gc_lstblk (hdr)
gheader *hdr;
{
	return (hdr->next ? 0: 1);
}

gc_blk (hdr)
gheader *hdr;
{
	return (((long)hdr->backptr & 1) ? 0 : 1);
}
			
char *
gc_own (hdr)
gheader *hdr;
{
	if ((long)hdr->backptr & 1) 
		return ((char *)-1);
	else
		return ((char *)hdr->proc);
}
