/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)fstcore.c	1.1.1.9	(6/12/87)";

#include <dmd.h>
#include <label.h>
#include "defines.h"
#include "globals.h"
#include <object.h>

Slot slot[SLOTNUM] = {	/* 8 slots need to be updated when memory changes */
	{ 0l, VINSET, VINSET },
	{ 0l, VINSET+SW+sw, VINSET },
	{ 0l, VINSET+SW+sw+SW+sw, VINSET },
	{ 0l, VINSET, YSET },
	{ 0l, VINSET+SW+sp, YSET },
	{ 0l, VINSET+SW+sw, YSET },
	{ 0l, VINSET+SW+sw+SW+bp, YSET },
	{ 0l, VINSET+SW+sw+SW+sw, YSET }
};

long CoreUnit;		/* number of bytes per dot */
int CoreBase;		/* base of display numerical information */
long CoreSpan;		/* difference between CoreStart and CoreEnd */


extern long *acfindblk(), *gcfindblk();
extern long *acnext(), *gcnext();
extern int aclast(), gclast();
extern int acis(), gcis();
extern char *a_own(), *gc_own();
extern Point add();

Foos foo[2] = {
	{ ALLOC, acfindblk, acnext, aclast, acis, a_own},
	{ GCALLOC, gcfindblk, gcnext, gclast, gcis, gc_own }
};


Texture16 *txtr[TXTNUM];

static long coricon [] = {
	0xC0000003, 0xE0018007, 0x701FF80E, 0x387FFE1C,
	0x19FFFF98, 0x03FFFFC0, 0x07FFFFE0, 0x0FFFFFF0,
	0x0FFFFFF0, 0x1FFC3FF8, 0x1FF00FF8, 0x3FE007FC, 
	0x3FCC33FC, 0x3FCE73FC, 0x3F84E1FC, 0x7F81C1FC,
	0x7F8381FC, 0x3F8721FC, 0x3FCE73FC, 0x3F9C39FC,
	0x3F381CFC, 0x1E700E78, 0x1CE42738, 0x09CFF390,
	0x039FF9C0, 0x073FFCE0, 0x0E7FFE70, 0x1CFFFF38,
	0x387FFE1C, 0x701FF80E, 0xE0000007, 0xC0000003
};
static Bitmap cormap = { (Word *)coricon, 2, 0,0,32,32, 0 };


#ifdef NEEDED
/* texture to fill window that is not correct shape */
Texture16 coretext ={
0x0180, 0x07E0, 0x1E78, 0x381C,
0x318C, 0x6186, 0x0006, 0x7FF3,
0x7FF3, 0x0006, 0x6186, 0x318C,
0x399C, 0x1DB8, 0x05A0, 0x0000,
};


Texture16 menu = {
	 0xFFC0, 0x8040, 0x8040, 0x8040,
	 0xFFC0, 0xFFC0, 0xFE00, 0xFEF0,
	 0x80E0, 0x80F0, 0x80B8, 0xFE1C,
	 0x800E, 0x8047, 0x8042, 0xFFC0,
};

#endif


/* menu functions */
char *fitems[] = { "base", "process", "stack", "scope", "limit", /* "quit", "bug",*/ NULL };
Menu fmenu = { fitems };

/* startup reshape menu */
char *reshapeitem[] = { "reshape", NULL };
Menu reshapemenu = { reshapeitem };


void debug();
extern void exit();
void (*viewfunc[])() = { setbase, peekproc, peekstak, setscope, setlimit /*,exit ,debug*/ };

main (argc, argv)
int argc;
char *argv[];
{   
	register int value;
	Point setsize();
	extern long memtest();

#ifdef NEEDED
	/* Check for the option (-c) 
	** More thorough checking can be done 
	** in the future by using getopt(3).
	*/
	if (argc > 2 || (argc > 1 && argv[1][1] != 'c')) {
		jstring ("Usage: dmdld ");
		jstring (argv[0]);
		jstring (" [-c] -- Type `q' to quit");
		request (KBD);
		while (wait(KBD))
			if (kbdchar() == 'q')
				exit();
	}
#endif

	P->ctob = setsize;	/* for "Reshape" outline */
	local();		/* make local */
	if (argc > 1 && argv[1][1] == 'c')		/* -c option specified */	
		cache("dmdmemory", 0);
	request (MOUSE);



	/* The firmware textures are accessed indirectly,  
	** so they cannot be used for explicit initialization.
	*/
	txtr[A_BUSY /*0*/] = &T_black;
	txtr[GC_ASTRAY /*1*/] = &T_background;
	txtr[GC_BUSY /*2*/] = &T_grey;

	/* initialization */
	setbound (memstartp, memendp);
	CoreBase = 16;		/* default is base hex */
	setdisplay ();

	for (; ;) {		/* infinite loop */
		wait (CPU);	/* let everybody runs */


		/* check if the window has been reshaped */
		if ((P->state & RESHAPED) && !(P->state & MOVED))
			setdisplay ();
		/* check if memory has been updated from last run */
		if (checkmem())
			viewupdate();

		/* check if any button is depressed */
		if (button2()) {
			if ((value = menuhit (&fmenu, 2)) != -1) {
				P->state |= NO_RESHAPE;
				(*viewfunc[value])();
				P->state &= ~NO_RESHAPE;
			}
		}
		else if (button3())
			giveupmouse (CPU);
	}
	
}


checkmem()
{
	static long old = 0l;
	register long new = memtest();

	if (new != old) {
		old = new;
		return 1;
	}
	else
		return 0;
}
	     			
 
/* Set the viewing boundary.
** On entry, it is the whole user memory (from memstartp to memendp).
** When the user does a zoom-in, the viewing boundary may change.
*/
void
setbound (lower, upper)
register long lower, upper;
{
	CoreStart = lower;
	CoreEnd = upper;
	CoreSpan = upper - lower;
	/* CoreUnit = (upper - lower)/(long)BARL; */
}


/* Toggle the base between decimal and hexadecimal base.
** The hex base is the default on power up.
*/
void
setbase ()
{
	static int num[2] = {16, 10};
	register int n = 0;

	if (CoreBase == 16) 
		n = 1;

	CoreBase = num[n];
	scopestrg ();
}


/* Set the display screen area.
** This program only works with a certain layer size. On entry or after a reshape
**  if the current layer size is not the required one, the program displays
** a texture in the window and a menu icon.  It waits for button 2 and 
** reshapes to the right size.
*/


void
setdisplay ()
{
    register Layer *l;
    register int value;
    Point temporigin;

    P->state &= ~RESHAPED;
    l=P->layer;
    if ((display.rect.corner.x - display.rect.origin.x == XSPAN) &&
	(display.rect.corner.y - display.rect.origin.y == YSPAN) ) 
		drawview();
	
    else {

    	labelon();
	labeltext("dmdmemory",9,L_LEFT);
	bitblt(&cormap,cormap.rect,&display,add(Drect.origin, Pt(4,4)),F_STORE);
	setstrg(" menu on button 2");
	
	for (; ;) { 
	    wait(CPU);

	    /* if the user reshaped the window with button 3 instead of the
	     * menu, startup if the window is the right size, else fill it
	     */

 	    if ((P->state & RESHAPED) && !(P->state & MOVED)) {
		P->state &= ~RESHAPED;
    		if ((display.rect.corner.x - display.rect.origin.x == XSPAN) &&
		    (display.rect.corner.y - display.rect.origin.y == YSPAN) ) {
			labeloff();
			drawview();
			break;
		}
		else {
		    labeltext("dmdmemory",9,L_LEFT);
		    bitblt(&cormap,cormap.rect,&display,add(Drect.origin, Pt(4,4)),F_STORE);
		    setstrg(" menu on button 2");
		}
	    }

	    if (button2()) {
		if ((value = menuhit(&reshapemenu,2)) != -1) {

		    temporigin.x = mouse.xy.x-(XSPAN/2);
		    if ( temporigin.x < 6 ) temporigin.x = 6;
		    else if (temporigin.x > (XMAX-XSPAN-6)) temporigin.x=(XMAX-XSPAN-6);

		    temporigin.y = mouse.xy.y-(YSPAN/2);
		    if ( temporigin.y < 6 ) temporigin.y = 6;
		    else if (temporigin.y > (YMAX-YSPAN-6)) temporigin.y=(YMAX-YSPAN-6);
			
	   	    if (reshape(Rpt(temporigin,
	       			Pt(temporigin.x+XSPAN,
				   temporigin.y+YSPAN)))) {
		        labeloff();
		        P->state &= ~RESHAPED;
	 	        drawview();
		        break;
		    }
		}
	    }
	    else if (button3()) giveupmouse (CPU);
        }
    }
}



/* Draw the display.
** From top to bottom:
** - upper numerical field
** - graphical bar
** - lower numerical field
** - alpha field
*/
void
drawview ()
{
	register x1, x2, y1, y2;
	register v = VINSET;	/* code saver */
	register b = BORDER;	/* code saver */

	/* draw the 2-pixel thick border of the graphical bar */
	x1 = Drect.origin.x + v;
	y1 = Drect.origin.y+VINSET+CH+DIV;
	x2 = Drect.corner.x - v;
	y2 = y1+BORDER+BARW+BORDER;
	rectf (&display, Rect(x1, y1, x2, y2), F_XOR);
	rectf (&display, Rect(x1+b, y1+b, x2-b, y2-b), F_XOR);

	/* draw markings, there are 99 of them, separated by 8 pixels */
	x1 += (BORDER+MARKINC);
	y1 -= 1;
	for (x2=0; ++x2<MARKNUM; x1+=MARKINC)
		segment (&display, Pt(x1,y1), Pt(x1,y1+MARKHI), F_XOR);

	/* draw the limit bar */
	drawlim();

	/* update the graphical bar */
	viewupdate();

	scopestrg ();
}


/* Advertise the default size for RESHAPE
*/
Point
setsize ()
{
	extern Point fPt();

	return (fPt(XSPAN, YSPAN));
}




/* Temporarily give up button control, wait for the given resource,
** and request back the mouse
*/
giveupmouse (res)
{
	unrequest (MOUSE);	/* give up mouse's button */
	if (res==CPU)
		sleep (2);
	else
		wait (res);
	dorequest (MOUSE);
}


