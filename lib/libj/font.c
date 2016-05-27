/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)font.c	1.1.1.4	(5/10/87)";

#include <dmd.h>
#include <dmdio.h>
#include <font.h>
#include <object.h>
#define ISIZE(n)	((n+1)*sizeof(Fontchar))

extern char *alloc();
extern Bitmap *balloc();

/*
 * read a font from an input stream
 * 	<font header>
 *	<f->info>
 *	<f->bits>	no bitmap header!!
 *
 * WARNING! This code believes it knows what the Font structure looks like
 */

/* The following few routines will later be taken out and replaced by
   firmware routines */

#define FCHARSIZE	8	/* sizeof(Fontchar) on host */

#ifdef JRG

Font *
infont(inch)
	register char (*inch)();
{
/*
 * Following line changed for the DMD!
 *
 */
	short n;
	register Font *f;
	register Bitmap *b;
	char dummy[FCHARSIZE - sizeof(Fontchar)];
	register int i;

	if(ninch(2,&n,inch))
		return((Font *)0);
	if((f = (Font *) alloc(sizeof(Font)+ISIZE(n))) == (Font *)0)
		return(f);
	f->n = n-1;
	if(ninch(6,2 + (char *)f,inch))	/* 6 == sizeof(height+ascent+unused) */
		goto err;
	for(i=0; i<=n; i++)
		if(ninch(sizeof(Fontchar), &(f->info[i]), inch))
			goto err;
		else
			if(ninch(FCHARSIZE - sizeof(Fontchar), dummy, inch))
				goto err;
	if((b = balloc(Rect(0,0,(f->info[n].x+31)&0xFFE0,f->height))) == (Bitmap *)0)
		goto err;
	f->bits = b;
	if(ninch(2*f->height*b->width,b->base,inch))
		goto berr;
	return(f);

	berr:
		bfree(f->bits);
	err:
		free(f);
	return((Font *)0);
}

static
ninch(n,s,inch)
	register n;
	register char *s,(*inch)();
{
	register x;

	do {
		*s++ = x = (*inch)();
		if(x == -1)
			return(1);
	} while (--n > 0);
	return(0);
}

ffree(f)
	register Font *f;
{
	if (f != (Font *) NULL) {
		bfree(f->bits);
		free(f);
	}
}

#endif JRG

outfont(f,ouch)
	register Font *f;
	register (*ouch)();
{
	register Bitmap *b = f->bits;
	register int i, rval;
	char dummy[FCHARSIZE - sizeof(Fontchar)];
	Font f2;
	char *dummyp, *outp;

	f2 = *f;
	rval = 0;
	f2.n++;
	outp = (char *)&f2;
	dummyp = dummy;
	if( nouch(8,&outp,ouch) )
		rval = -1;
	else
		for(i=0; i<=f2.n; i++)
		{
			outp = (char *)(f->info+i);
			if(nouch(sizeof(Fontchar),&outp,ouch) ||
			   nouch(FCHARSIZE - sizeof(Fontchar), &dummyp, ouch))
			{
				rval = -1;
				break;
			}
		}
	if(rval != -1)
		if(nouch(2*f->height*b->width,&b->base,ouch))
			rval = -1;
		return(rval);
}

static
nouch(n,s,ouch)
	register n,(*ouch)();
	register char **s;
{
	register int i = 0;
	do {
		if((*ouch)(*(*s + i++)) == -1)
			return(-1);
	} while (--n > 0);
	return(0);
}

/*
**	FONT CACHING
*/

extern Obj *f_cache();
extern Obj *findfont();
extern char *alloc();
extern Bitmap *balloc();


/* fontsave -	cache a font by duplicating into memory
**
**	This function is needed if the font is downloaded inside
**	an application.
*/
Font *
fontsave(name,f)
char *name;
register Font *f;
{
	register int n;
	register Font *f2;
	register Bitmap *b;

	n = f->n+1; /* number of entries in info */

	 /* alloc a font structure */
	if (f2 = (Font *)alloc(sizeof(Font) + ISIZE(n))) {
		if(b = balloc(Rect(0,0,f->info[n].x,f->height))) {
			*f2 = *f;
			memcpy(&(f2->info[0]), &(f->info[0]), ISIZE(n));
			f2->bits = b;
			bitblt(f->bits, Rect(0,0,f->info[n].x, f->height),
			      f2->bits, Pt(0,0), F_STORE);
			if (!fontcache(name,f2)) /* try to add it to the list */
				ffree(f2);
			else
				return(f2);
		}
		else
			free(f);
	}
	return((Font *)0);
}


/* fontcache -	cache a font that is already in alloc space
**
**	Caching can fail due to:
**	- a font of same name is already cached
**	- there is no more memory to set up the cache and the
**	  subsequent request.
*/
int
fontcache(name, f)
register char *name;
register Font *f;
{
	register Obj *obj;
	register char *null = (char *)0;
	Obj *f_cache();
	Obj *findfont();

        if (!findfont(name) && (obj = f_cache(name, f))) {
		if (reqobj(P, obj)) {
                	allocown(f, null);
                	allocown(f->bits, null);
                	gcallocown(f->bits->base, null);
                	return(1);
		}
		else 
			uncache (obj);
        }
        return(0);
}


/* fontremove -		Remove a cached font 
*/
void
fontremove(name)
char *name;
{
        register Obj *obj;

        if ((obj = findfont(name)) && uncache(obj))
                ffree (obj->info.cfont);        /* "obj" is freed, but its pointers */
                                                /* ... are still valid */
}

