/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)bitblit.c	1.1.1.4	(7/1/87)";

#include <dmd.h>
#include "icon.h"

bool bitmapbit(b, p)
Bitmap *b;
Point p;
{
	register bit;
	register Word *wp;
	bool obitmapbit();
	if (!(ptinrect(p, b->rect))) 
		return(false);
	if(b->_null) /* obscured, use bitblt to get the bit */
		return(obitmapbit(b, p));
	wp = addr(b, p);
	bit = 1 << (WORDSIZE - 1) - (p.x & WORDMASK);
	return((*wp & bit) != 0);
}

Word wtest;
Bitmap btest = { &wtest, 1, 0, 0, 1, 1, (char *)0 };

bool obitmapbit(b,p)
Bitmap *b;
Point p;
{
   *(btest.base) = 0;
   bitblt(b,Rpt(p,add(p,Pt(1,1))),&btest,Pt(0,0),F_XOR);
   return((*(btest.base))!=0);
}


bool geticonpoint(p)
Point p;
{
	p = add(icon.origin, p);
	if (!ptinrect(p, icon)) 
		return(false);
	return(bitmapbit(&display, p));
}


flipiconpoint(p)
Point p;
{
	Point iconp;
	iconp = add(icon.origin, p);
	if (!ptinrect(iconp, icon)) 
		return(0);
	point(&display, iconp, F_XOR);
	if (bitmapbit(&display,iconp) != bitmapbit(pmap,p))
		point(pmap, p, F_XOR);
	rectf(&display, Rpt(add(Pt(p.x * Xsize, p.y * Ysize), ICON.origin),
	    add(Pt((p.x + 1) * Xsize, (p.y + 1) * Ysize), ICON.origin)),
	    F_XOR);
}


IconOp(bit, p, op)
bool bit;
Point p;
int	op;
{
	if ((p.x >= 0) && (p.x < Xblocks) && (p.y >= 0) && (p.y < Yblocks))
		switch (op) {
		case I_STORE:
			if (geticonpoint(p) != bit) 
				flipiconpoint(p);
			break;
		case I_CLR:
			if (geticonpoint(p) == true) 
				flipiconpoint(p);
			break;
		case I_OR:
			if ((geticonpoint(p) == false) && (bit == true)) 
				flipiconpoint(p);
			break;
		case I_XOR:
			if (bit == true) 
				flipiconpoint(p);
			break;
		}
}


IconBitBlit(from, to, clip, srccode, dstcode)
Rectangle from;  /* icon coords */
Point to;        /* icon coords */
Rectangle clip;  /* icon coords */
int	srccode, dstcode;
{
	Rectangle region;
	int	dx, dy, di, dj, i, j;
	int	left, up;
	bool bit;
	dx = to.x - from.origin.x;
	dy = to.y - from.origin.y;
	left = dx < 0;
	up = dy < 0;
	di = (left ? 1 : -1);
	dj = (up ? 1 : -1);
	region = from;
	if (!rectclip(&region, raddp(clip, sub(from.origin, to))))
		region = nullrect;
	for (j = (up ? from.origin.y : from.corner.y - 1); 
	    up ? (j < from.corner.y) : (j >= from.origin.y); j += dj)
		/* wait(CPU); SWMR646 */
		for (i = (left ? from.origin.x : from.corner.x - 1); 
		    left ? (i < from.corner.x) : (i >= from.origin.x); i += di) {
			bit = geticonpoint(Pt(i, j));
			IconOp(false, Pt(i, j), srccode);
			if (ptinrect(Pt(i, j), region)) 
				IconOp(bit, Pt(i + dx, j + dy), dstcode);
		}
}


/***********************************************************************
    This routine is called when the menu command MOVE or COPY is selected.
    Depending on the "srcop" argument, the region selected is moved
    or copied.
***********************************************************************/
OpBlit(srcop, dstop)
int	srcop, dstop;
{
	Rectangle r;
	Point p;
	if (GetIconRect(&r) == 0) 
		return(0);
	p = TrackBorder(r, true).origin;
	if (bttn23()) {
		while (bttn23())
			wait(MOUSE);
		IconBitBlit(r, p, Rect(0, 0, Xblocks, Yblocks), srcop, dstop);
	} else 
		while (bttn1())
			wait(MOUSE);
}


/***********************************************************************
    This routine is called when the menu command BLIT is selected.
***********************************************************************/
OpGeneralBlit()
{
	int	srcop, dstop;
	cursswitch(&menucursor);
	while (!bttn123()) 
		wait(MOUSE);
	cursswitch((Texture16 * ) 0);
	if (!bttn3()) 
		return(0);
	switch (menuhit(&blitsrcmenu, 3)) {
	case NOHIT:
		srcop = I_NULL;
		break;
	case SRC_ID:
		srcop = I_OR;
		break;
	case SRC_CLR:
		srcop = I_CLR;
		break;
	}
	if (srcop == I_NULL) {
		cursswitch((Texture16 * ) 0); 
		return(0);
	}
	cursswitch(&menucursor);
	while (!bttn123()) 
		wait(MOUSE);
	cursswitch((Texture16 * ) 0);
	if (!bttn3()) 
		return(0);
	switch (menuhit(&blitdstmenu, 3)) {
	case NOHIT:
		dstop = I_NULL;
		break;
	case DST_STORE:
		dstop = I_STORE;
		break;
	case DST_OR:
		dstop = I_OR;
		break;
	case DST_XOR:
		dstop = I_XOR;
		break;
	case DST_CLR:
		dstop = I_CLR;
		break;
	}
	if (dstop == I_NULL) {
		cursswitch((Texture16 * ) 0); 
		return(0);
	}
	OpBlit(srcop, dstop);
}

