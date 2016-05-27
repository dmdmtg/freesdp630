/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)kbd3.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include <keycodes.h>
#include "positions.h"
#include "keys.h"
#include "keyrects.h"

/*Library routines and associated manual pages.	*/
Point add();		/* PTARITH(3R)		*/
void box();		/* BOX(3R)		*/
int cache();		/* CACHE(3L)		*/
Rectangle inset();	/* INSET(3R)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
int local();		/* LOCAL(3R)		*/
int min();		/* INTEGER(3R)		*/
Point mul();		/* PTARITH(3R)		*/
Rectangle raddp();	/* RECTARITH(3R)	*/
void rectf();		/* RECTF(3R)		*/
int request();		/* RESOURCES(3R)	*/
int wait();		/* RESORUCES(3R)	*/

/* Local routines */
void ClearAllKeys();
void DrawKeyboard();
Rectangle GetKeyRect();
void PaintTheKey();

main()
{
	unsigned char c;

	local(); 
	cache("Keyboard", 0);

	request(KBD); 
	P->state |= NOTRANSLATE;

	DrawKeyboard();
	for(;;) {
		wait(KBD);
		c = (unsigned char)kbdchar();
		switch(c) {
		case KEYSTROKE:
			c = (unsigned char)kbdchar();
			if (c & DOWNSTROKE)
				PaintTheKey(c &~DOWNSTROKE, 1);
			else
				PaintTheKey(c, 0);
			break;
		case BEFOREID:
			c = (unsigned char)kbdchar();
			break;
		case SWITCHCHAR:
			c = (unsigned char)kbdchar();
			ClearAllKeys();
		}
	}
}

void
PaintTheKey(RawCode, KeyDown)
unsigned char RawCode;
int KeyDown;
{
	int KeyPosition;
	KeyPosition = Positions[RawCode];
	/*
	** If the state of the key has changed, then
	** F_XOR the keys rectangle.
	*/
	if (Keys[KeyPosition].depressed != KeyDown) {
		Keys[KeyPosition].depressed = KeyDown;
		rectf(&display, GetKeyRect(KeyPosition), F_XOR);
	}
}

void
ClearAllKeys()
{
	int KeyPosition;
	Rectangle r;
	/*
	** Clear all the rectangles for each key.
	*/
	for(KeyPosition=0; KeyPosition<128; KeyPosition++) {
		if((Keys[KeyPosition].RectType != -1) && 
		   (Keys[KeyPosition].depressed)) {
			Keys[KeyPosition].depressed = 0;
			rectf(&display, r = GetKeyRect(KeyPosition), F_CLR);
			box(&display, r, F_STORE);
		}
			
	}
}

void
DrawKeyboard()
{
	int KeyPosition;
	for(KeyPosition=0; KeyPosition<128; KeyPosition++) {
		if(Keys[KeyPosition].RectType != -1) {
			Keys[KeyPosition].depressed = 0;
			box(&display, GetKeyRect(KeyPosition), F_STORE);
		}
			
	}
}

Rectangle
GetKeyRect(KeyPosition)
{
        Point TmpPoint;
        Rectangle TmpRect;
        int mx, my, mult;

	/*
	** Return the Rectangle for a given key position.
	*/
        mx = (Drect.corner.x - Drect.origin.x)/125 + 1;
        my = (Drect.corner.y - Drect.origin.y)/125 + 1;
        mult = min(mx, my);

        TmpRect = KeyRects[Keys[KeyPosition].RectType];
        TmpRect = raddp(TmpRect, Keys[KeyPosition].Location);
        TmpRect.origin = mul(TmpRect.origin, mult);
        TmpRect.corner = mul(TmpRect.corner, mult);
        TmpPoint = add(display.rect.origin, Pt(2*mult, 2*mult));
	TmpRect= raddp(TmpRect, TmpPoint);
	return(TmpRect);
}
