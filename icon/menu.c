/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)menu.c	1.1.1.3	(5/10/87)";

#include <dmd.h>
#include "icon.h"

Menu blitsrcmenu = {
	blitsrctext};


Menu blitdstmenu = {
	blitdsttext};



Texture16 *(imenu[]) 
 = 
{
	&Cmove, &Ccopy, &Cinvert, &Cerase, 0,
	    &Creflx, &Crefly, &Crotplus, &Crotminus, 0,
	    &Cshearx, &Csheary, &Cstretch, &Ctexture16, 0,
	    &Cread, &Cgrid, &Ccursor, &Cwrite, 0,
	    &Cblit, &white, &Chelp, &Cexit, 0,
	    0, 0, 0, 0
};


flipring(p)
Point p;
{
	Outline(&display, raddp(Rect(1, 1, SPACING - 2, SPACING - 2), p));
	Outline(&display, raddp(Rect(2, 2, SPACING - 3, SPACING - 3), p));
}


drawimenu(/* imenu, */ xicons, yicons, r)
/* Texture16 *(imenu[]); */
Rectangle r;
{
	Bitmap * textr;
	int	i, j;
	Bitmap  b;
	Word    bits[16];
	b.base = bits;
	b.width = 1;
	b.rect.origin.x = b.rect.origin.y = 0;
	b.rect.corner.x = b.rect.corner.y = 16;
	b._null = (char *)0;
	textr = &b;
	Outline(&display, Rpt(r.origin, sub(r.corner, Pt(1, 1))));
	for (j = 0; j < yicons; j++) {
		for (i = 0; i < xicons; i++) {
			texture(textr, textr->rect, imenu[j*(xicons+1)+i], F_STORE);
			bitblt(textr, textr->rect,
			    &display,
			    add(r.origin, Pt(i * SPACING + (SPACING - 16) / 2, j * SPACING + (SPACING - 16) / 2)),
			    F_XOR);
		}
	}
}


Point imenuhit(/* imenu */)
/* Texture16 *(imenu[]); */
{
	Bitmap * offscreen;
	Point ms, lastms, valley, diff, result, menudrift;
	Rectangle menurect;
	Texture16 * oldcursor;
	int	i, j, hitx, hity;
	int	xicons, yicons;
	oldcursor = (Texture16 *) cursswitch(&white);
	xicons = 0;
	for (j = 0; imenu[xicons*j]; j++) {
		for (i = 0; imenu[xicons*j+i]; i++)
			;
		i++;
		xicons = i;
	}
	xicons -= 1;
	yicons = j;
	while (!bttn3()) 
		wait(MOUSE);
	ms = mouse.xy;
	menurect = raddp(Rect(0, 0, SPACING * xicons, SPACING * yicons), ms);
	menurect = rsubp(menurect, Pt(SPACING * lasthitx, SPACING * lasthity));
	menudrift.x = min(menurect.corner.x, Drect.corner.x);
	menudrift.y = min(menurect.corner.y, Drect.corner.y);
	menudrift = sub(menudrift, menurect.corner);
	menurect = raddp(menurect, menudrift); 
	cursset(ms = add(ms, menudrift));
	menudrift.x = max(menurect.origin.x, Drect.origin.x);
	menudrift.y = max(menurect.origin.y, Drect.origin.y);
	menudrift = sub(menudrift, menurect.origin);
	menurect = raddp(menurect, menudrift); 
	cursset(add(ms, menudrift));
	offscreen = balloc(menurect);
	if (offscreen != ((Bitmap * ) 0)) {
		bitblt(&display, menurect, offscreen, offscreen->rect.origin, F_STORE);
		rectf(&display, menurect, F_CLR);
	}
	drawimenu(/* imenu, */ xicons, yicons, menurect);
	lastms = mouse.xy;
	flipring(lastms);
	hitx = hity - 1;
	while (bttn3()) {
		nap(3);
		ms = mouse.xy;
		if (ptinrect(add(ms, Pt(SPACING / 2, SPACING / 2)), menurect)) {
			lasthitx = hitx = (ms.x - menurect.origin.x + SPACING / 2) / SPACING;
			lasthity = hity = (ms.y - menurect.origin.y + SPACING / 2) / SPACING;
		} else 
			hitx = hity = -1;
		if (eqpt(lastms, ms) && (hitx != -1)) {
			valley = add(menurect.origin, Pt(SPACING * hitx, SPACING * hity));
			diff = sub(valley, ms);
			ms.x += sgn(diff.x);
			ms.y += sgn(diff.y);
			cursset(ms);
		}
		if (!eqpt(lastms, ms)) {
			flipring(lastms);
			flipring(ms);
		}
		lastms = ms;
	}
	flipring(ms);
	drawimenu(/* imenu, */ xicons, yicons, menurect);
	if (offscreen != ((Bitmap * ) 0)) {
		bitblt(offscreen, offscreen->rect, &display, menurect.origin, F_STORE);
		bfree(offscreen);
	}
	result.x = hitx;
	result.y = hity;
	cursswitch(oldcursor);
	return(result);
}



