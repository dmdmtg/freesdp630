/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)user.c	1.1.1.2	(5/10/87)";

#include <dmd.h>
#include <layer.h>
#include <dmdproc.h>
#include <font.h>

extern Point add();
extern Point string();
extern Point transform();

Rectangle
rtransform(r)
Rectangle r;
{
	r.origin=transform(r.origin);
	r.corner=transform(r.corner);
	return r;
}


jline(p, f)
	Point p;
	Code f;
{
	Point next;
	next=add(P->curpt, p);
	jsegment(P->curpt, next, f);
}
jlineto(p, f)
	Point p;
	Code f;
{
	jsegment(P->curpt, p, f);
}
jmove(p)
	Point p;
{
	P->curpt=add(P->curpt, p);
}
jmoveto(p)
	Point p;
{
	P->curpt=p;
}
jpoint(p, f)
	Point p;
	Code f;
{
	point(P->layer, transform(p), f);
}
jrectf(r, f)
	Rectangle r;
	Code f;
{
	rectf(P->layer, rtransform(r), f);
}
jsegment(p, q, f)
	Point p, q;
	Code f;
{
	Point pp,qq;
	pp=transform(p);
	qq=transform(q);
	if(!eqpt(pp, qq))
		segment(P->layer, transform(p), transform(q), f);
	P->curpt=q;
}

Point
jstring(s)
	char *s;
{
	int x;
	Point p;
	p=string(&mediumfont, s, P->layer, transform(P->curpt), F_XOR);
	x=p.x;
	P->curpt.x+=muldiv(jstrwidth(s),XMAX,P->rect.corner.x-P->rect.origin.x);
	while(transform(P->curpt).x<x)
		P->curpt.x++;
	return P->curpt;
}
jtexture(r, t, f)
	Rectangle r;
	Texture16 *t;
	Code f;
{
	texture(P->layer, rtransform(r), t, f);
}

labelicon(bp, pos)
Bitmap *bp;
int pos;
{
	Labelicon(P, bp, pos);
}


