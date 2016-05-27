/*	Copyright (c) 1987 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/


static char _2Vsccsid[]="@(#)cmdcache.c	1.1.1.2	(5/8/87)";

#include <dmd.h>
#include <menu.h>
#include <object.h>
#include <memory.h>

extern Point fPt();
extern Obj *realcache();
extern void greymore();
extern void newmore();
extern Obj *findobj();
extern void free();

extern char *challoc();
extern void _frdata();			/* defined in crtm.s */

Obj *applcache();


/* cmdcache -	Cache an instruction or command
*/
cmdcache (s, m, b, u, e)
char *s;
Tmenu *m;
Bitmap *b;
void (*u)();
void (*e)();
{
	static Appl appl;		/* unused fields are initialized to 0 */
	register Appl *ap = &appl;
	register Obj *obj;
	void nogrey(), noexec();

	ap->status |= (SHOWOFF|COMMAND);
	ap->caption = s;
	ap->next = m;
	ap->icon = b;
	ap->update = (u) ? u : nogrey;
	ap->exec = (e) ? e : noexec;

	return (applcache(s, ap, 0) ? 1 : 0);
}

void
nogrey (obj, item)
Obj *obj;
Titem1 *item;
{
	item->ufield.grey = 0;
}
void 
noexec ()
{
	return;
}


/* applcache -	cache the current application 
**
**	This function does not assume about the current state of P as
**	does cache(). However it does supply some default system
**	initialization for the user.
*/
Obj *
applcache (s, ap, f)
char *s;
register Appl *ap;
int f;	
{
	register Proc *p = P;
	register char *str;
	register Obj *obj;
	register Appl *appl;

	if (findobj("s", s) ||
	    !(str = challoc (strlen(ap->caption)+1)))
		return ((Obj *)0);		/* failure */


	if (obj = realcache(&syscache[APPLCACHE], s, f, ap, sizeof(Appl))) {
	    if (reqobj (p, obj)) {		/* current process is using the object */

		appl = obj->info.cappl;
		/* appl->status:	initialized from ap */
		appl->text = p->text;
		allocown (p->text, (char *)0);		/* in cached memory */
		appl->data = p->data;
		appl->bss = p->bss;
		appl->argc = p->uargc;
		appl->argv = p->uargv;
		allocown (p->uargv, (char *)0);		/* in cached memory */
		appl->stksize = p->stksize;
		appl->progid = prog_env_id;
		/* appl->rect: initialized from ap */
		strcpy (str, ap->caption);
		appl->caption = str;			/* in cached memory */
		
		/* those things are allocated */
		appl->status |= MEMTEXT|MEMARGV|MEMCAPTION;

		if (!appl->update)
			appl->update = greymore;	/* else initialized from ap */
		if (!appl->exec)
			appl->exec = newmore;		/* else initialized from ap */
		return (obj);
	    }
	    else
		uncache (obj);
	}

	free (str);
	return ((Obj *)0);
}



/* apdecache -	Remove a cached Application
**
**	This function is called by one application to
**	literally remove another application that is cached.
**
**	If the cached application is being used (it is running),
**	the function fails. Otherwise all memory connected to
**	the cached application is freed, and the application
**	does not exist anymore.
*/
apdecache (obj)
register Obj *obj;
{
	register Appl *ap = obj->info.cappl;
	register long stat = ap->status;

	if (uncache (obj)) {
		_frdata(ap->bss);

		if (stat & MEMTEXT)
			free (ap->text);
		if (stat & MEMDATA)
			free (ap->data);
		if (stat & MEMBSS)
			free (ap->bss);
		if (stat & MEMARGV)
			free (ap->argv);
		if (stat & MEMCAPTION)
			free (ap->caption);
		if (stat & MEMMENU)
			free (ap->next);
		if (stat & MEMICON)
			bfree (ap->icon);

		return (1);
	}
	return (0);
}

