/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache.c	1.1.1.8	(5/10/87)";

#include <dmd.h>
#include <menu.h>
#include <object.h>
#include <memory.h>

extern Point fPt();
extern Obj *findobj();
extern void free();
extern Point sub();

extern char *clipprefix();
extern char *lchalloc();
extern unsigned long _szdsect();	/* defined in crtm.s */
extern void _svodata();			/* defined in crtm.s */
extern void _svcbss();			/* defined in crtm.s */
extern void _frdata();			/* defined in crtm.s */

Obj *applcache();

/* cache -	the application caches itself using default values
**
**	The application is assumed to be non-shared, sweepable unless
**	the NO_RESHAPE bit is set, and connectable unless the application
**	is already local.
**
**	The application is assumed to use argv[0] as the name to cache itself
**	under and to advertise itself to the user if s is null. Argv[0] is clipped
**	from its pathname for the object name.
**
**	The application is assumed to have supported a "ctob" function which
**	accepts arguments x, y as zero and returns the default rectangle size.
**	Otherwise no default is given.
**
**	Other default information is supplied by applcache().
*/
cache (s, f)
char *s;
int f;		/* A_SHARED, A_NO_SHOW, A_BSS, A_DATA, A_NO_BOOT, A_PERMANENT */
{
	static Appl appl;		/* fields initialized to zero */
	char *name;
	register Proc *p = P;
	register Appl *ap = &appl;
	register char *pdata = (char *)0;
	register long status;
	register int af;

	/* By default, we cache a copy of the .data section for subsequent
	** invocation. In order to that, we allocate memory and copy what
	** is currently in the .data section into it.
	**
	** If the A_DATA flag is set, the .data section needs not be cached.
	** The values in there will be accumulated from invocation to invocation.
	*/
	if (!(f & A_DATA)) {	/* default */
		if (!(pdata = lchalloc (_szdsect())))
			return (0);	/* not enough memory */
	}

	name = clipprefix (p->uargv[0]);
	ap->caption = s ? s : name;	/* find the filename */

	/* get the status variable */
	status = SHOWOFF|SWEEP|CONNECT;	/* default */
	if (f & A_NO_SHOW)
		status &= ~SHOWOFF;
	if (f & A_NO_BOOT)
		status |= NOTKEYABLE;
	if (p->state & NO_RESHAPE)	/* cannot be reshaped */
		status &= ~SWEEP;	/* so cannot be swept */
	if (p->host == LOCAL)		/* is a local window */
		status &= ~CONNECT;	/* does not want to be connected */
	ap->status = status;

	af = 0;			/* translate the bit field of cache() to */
	if (f & A_TEXT)		/* the one accepted by realcache() called */
		af |= SHARED;	/* from applcache() */
	if (f & A_PERMANENT)
		af |= PERMANENT;

	/* get the default rectangle outline */
	if (p->ctob)
		ap->rect.corner = p->ctob(0,0,p);
	else if (p->state & NO_RESHAPE)
		ap->rect.corner = sub(display.rect.corner, display.rect.origin);

	if (applcache(name, ap, af)) {	/* success */
		if (f & A_BSS) 
			_svcbss();

		if (!(f & A_DATA))
			_svodata (pdata);

		return (1);
	}
	else {
		free (pdata);	/* if 0, free will do nothing */
		return (0);
	}
}

/* decache -	Uncache itself
**
**	This function is the opposite of "cache" which
**	the application calls to cache itself. It is
**	preferrably called from an application that 
**	has been downloaded (i.e.not from cartridge).
**
**	Note that only the cache information of the
**	application is removed, the application still
**	exists and has to be removed by a delete.
*/
decache ()
{	
	register Obj *obj = syscache[APPLCACHE].fobj;
	register Proc *p = P;		/* calling process */
	register Appl *ap;
	register long stat;

	/* find the object the process is cached under:
	** cannot do a search with argv[0] because it
	** may get changed by the application. P->text
	** may get changed too but it is unlikely.
	**
	** The check for P->text may not be necessary,
	** because in the application cache, one process
	** can request at most one cached object (there does
	** not exist a concept of a process "using" two
	** cached applications).
	*/
	do {
		if (!(obj = findobj ("op", obj, p)))
			return (0);	/* cannot find it */
		ap = obj->info.cappl;
	} while (ap->text != p->text);

	unreqobj (p, obj);
	if (!uncache (obj)) {	/* in use by somebody or PERMANENT object */
		reqobj (p, obj);
		return (0);
	}

	/* the object information has been freed by "uncache",
	** however we have to restore the ownership of some blocks
	** of memory that belong to the process, so they can be
	** cleared when the process is deleted.
	*/
	stat = ap->status;
	if (stat & MEMTEXT)
		allocown (p->text, p);
	if (stat & MEMDATA)
		allocown (p->data, p);
	if (stat & MEMBSS)
		allocown (p->bss, p);
	if (stat & MEMARGV)
		allocown (p->uargv, p);
	if (stat & MEMCAPTION)
		free (ap->caption);
	if (stat & MEMMENU)
		free (ap->next);
	if (stat & MEMICON)
		bfree (ap->icon);
	_frdata (p->bss);

	return (1);
}

