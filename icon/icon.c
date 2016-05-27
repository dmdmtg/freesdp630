/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)icon.c	1.1.1.10	(7/1/87)";

#include <dmd.h>
#include <dmdio.h>
#include <font.h>
#include "icon.h"
#include <string.h>
#include <object.h>
#include <label.h>




int	lasthitx = 0, lasthity = 0;
char	*blitsrctext[] = 
{
	"src := src", "src := 0", NULL};

char	*blitdsttext[] = 
{
	"dst := src", "dst := src or dst", "dst := src xor dst", "dst := 0", NULL};

char	buf[100], FNAME[50];
Point nullpoint, point16x16;
Rectangle icon, ICON, sweep, outl, nullrect, rect16x16;
int	xsize = XSIZE, ysize = YSIZE, Xsize, Ysize;
int	Xblocks, Yblocks;
int	modx, divx, mody, divy;
Bitmap *pmap;

/* startup reshape menu */
char *reshapeitem[] = { "reshape", NULL };
Menu reshapemenu = {reshapeitem };



/* reshape icon bitmap */
Bitmap gridmap = { (Word *)&Cgrid, 1, (short)0, (short)0, (short)16, (short)16, (char *)0 };

Bitmap *bittester;


Erase(r)
Rectangle r;
{
	int	i, j;
	for (j = r.origin.y ; j < r.corner.y ; j++)
		/* wait(CPU);  SWMR646 */
		for (i = r.origin.x ; i < r.corner.x ; i++)
			if (geticonpoint(Pt(i, j)) == true) 
				flipiconpoint(Pt(i, j));
}


/***********************************************************************
    This routine is called when the menu command ERASE is selected.
***********************************************************************/
OpErase()
{
	Rectangle r;
	if (GetIconRect(&r) == 0) 
		return(0);
	Erase(r);
}


/***********************************************************************
    This routine is called when the menu command INVERT is selected.
***********************************************************************/
OpInvert()
{
	Rectangle r;
	int	i, j;
	if (GetIconRect(&r) == 0) 
		return(0);
	for (j = r.origin.y ; j < r.corner.y ; j++)
		/* wait(CPU); SWMR646 */
		for (i = r.origin.x ; i < r.corner.x ; i++)
			flipiconpoint(Pt(i, j));
}


StoreIcon(bitmap, rect)
Bitmap *bitmap;
Rectangle rect;
{
	bitblt(&display, icon, bitmap, rect.origin, F_STORE);
}


FetchIcon(bitmap, r, p, clip)
Bitmap *bitmap;
Rectangle r;
Point p;
Rectangle clip;
{
	int	i, j, hsize, vsize;
	bool bit;
	Texture16 *oldcursor;
	Point pij, srcp;

	if (!rectclip(&r, rsubp(clip, sub(p, r.origin)))) 
		r = nullrect;
	hsize = horsize(r);
	vsize = versize(r);
	/* better put up alarm clock cursor here and wait(CPU) because this loop
	 * takes forever for large grids
	 */
	oldcursor = (Texture16 *)cursswitch(&clock);
	for (j = 0; j < vsize; j++) {
		wait(CPU);
		for (i = 0; i < hsize; i++) {
			bit = bitmapbit(bitmap, add(r.origin, Pt(i, j)));
			pij = add(p, Pt(i, j));
			if ((geticonpoint(pij) == false) && (bit == true))
				flipiconpoint(pij);
		}
	}
	cursswitch(oldcursor);
}


Bitmap *pickupmap;

/***********************************************************************
    This routine is called when the menu command PICK is selected.
***********************************************************************/
PickUpCursor()
{
	Texture16 * oldcursor;
	short *dmdptr,*blitptr;	/* used to convert bitmap to cursor */
	int i, j;

	Rectangle r;
	r = TrackBorder(raddp(rect16x16, IconPoint(mouse.xy)), true);
	r = raddp(r, icon.origin);
	bitblt(&display, r, pickupmap, Pt(0, 0), F_STORE);
	blitptr = dmdptr = (short *) (pickupmap->base);
	for (i=0; i<16; i++)	/* all scan lines of cursor */
	{
		*dmdptr++ = *blitptr++;
		for(j=16; j<WORDSIZE; j+=16)	/* changed to support different word size */
			*blitptr++;
	}
	oldcursor = (Texture16 *) cursswitch(pickupmap->base);
	while (bttn123())
		wait(MOUSE);
	while (!bttn123())
		wait(MOUSE);
	while (bttn123())
		wait(MOUSE);
	cursswitch(oldcursor);
}





/***********************************************************************
    This routine is called when the menu command TEXTURE is selected.
***********************************************************************/
OpTexture16()
{
	Bitmap * buffer;
	Rectangle source, dest;
	Point target;
	int	repx, repy, i, j, hsize, vsize;
	if (GetIconRect(&source) == 0) 
		return(0);
	if (GetIconRect(&dest) == 0) 
		return(0);
	hsize = horsize(source);
	vsize = versize(source);
	if ((hsize == 0) || (vsize == 0)) 
		return(0);
	buffer = balloc(source);
	if (buffer == ((Bitmap * ) 0)) 
		return(0);
	bitblt(&display, raddp(source, icon.origin), buffer, buffer->rect.origin, F_STORE);
	repx = horsize(dest) / hsize;
	repy = versize(dest) / vsize;
	for (j = 0; j <= repy; j++)
		for (i = 0; i <= repx; i++)
			FetchIcon(buffer, buffer->rect, add(dest.origin, Pt(i * hsize, j * vsize)), dest);
	bfree(buffer);
}


/***********************************************************************
    This routine is called when the menu command GRID is selected.
***********************************************************************/
DrawGrid()
{
	Point p;
	register int	i, j;
	for (j = 0; j <= Yblocks; j += 16) {
		p = add(ICON.origin, Pt(0, j * Ysize + 1));
		segment(&display, p, Pt(ICON.corner.x, p.y), F_XOR);
	}
	for (j = 8; j <= Yblocks; j += 16) {
		p = add(ICON.origin, Pt(0, j * Ysize + 1));
		for (i = 0; i <= Xblocks * Xsize; i += 2)
			point(&display, Pt(p.x + i, p.y), F_XOR);
	}
	for (i = 0; i <= Xblocks; i += 16) {
		p = add(ICON.origin, Pt(i * Xsize + 1, 0));
		segment(&display, p, Pt(p.x, ICON.corner.y), F_XOR);
	}
	for (i = 8; i <= Xblocks; i += 16) {
		p = add(ICON.origin, Pt(i * Xsize + 1, 0));
		for (j = 0; j <= Yblocks * Ysize; j += 2)
			point(&display, Pt(p.x, p.y + j), F_XOR);
	}
}



Icon(sourcebitmap, sourcerect, drawrect)
Bitmap *sourcebitmap;
Rectangle sourcerect, drawrect;
{
	Bitmap * b;
	Point p, cur, hit;
	int	i, j;

	if (!rectclip(&sourcerect, sourcebitmap->rect)) 
		return(0);

	Xblocks = horsize(sourcerect);
	Yblocks = versize(sourcerect);

	Xsize = (horsize(drawrect) - (Xblocks + 9)) / Xblocks;
	Ysize = (versize(drawrect) - (Yblocks + 9)) / Yblocks;

	if ((Xsize == 0) || (Ysize == 0)) 
		return(WINDOW_TOO_SMALL);

	Ysize = (Xsize = (Xsize < Ysize) ? Xsize : Ysize);

	icon.origin = add(drawrect.origin, Pt(5, 5));
	icon.corner = add(icon.origin, Pt(Xblocks, Yblocks));

	ICON.origin = sub(drawrect.corner, Pt(3 + Xsize * Xblocks, 3 + Ysize * Yblocks));
	ICON.corner = add(ICON.origin, Pt(Xsize * Xblocks, Ysize * Yblocks));

	rectf(&display, drawrect, F_CLR);	/* was stipple */

	modx = ICON.origin.x % Xsize;
	divx = ICON.origin.x / Xsize;
	mody = ICON.origin.y % Ysize;
	divy = ICON.origin.y / Ysize;

	for (j = 0; j <= Yblocks; j++) {
		p = add(ICON.origin, Pt(0, j * Ysize));
		segment(&display, p, Pt(ICON.corner.x, p.y), F_OR);
	}

	for (i = 0; i <= Xblocks; i++) {
		p = add(ICON.origin, Pt(i * Xsize, 0));
		segment(&display, p, Pt(p.x, ICON.corner.y), F_OR);
	}

	FetchIcon(sourcebitmap, sourcerect, Pt(0, 0), Rect(0, 0, Xblocks, Yblocks));

	cur.x = 0; 
	cur.y = 0;

	for (; ; ) {
		wait(CPU);
		if (P->state & RESHAPED) 
			return(0);
		if (button1()) {
			while (bttn1()) {
				if (ptinrect((p = mouse.xy), ICON)) {
					p = sub(p, ICON.origin);
					cur.x = p.x / Xsize;
					cur.y = p.y / Ysize;
					if (geticonpoint(cur) == false) 
						flipiconpoint(cur);
				}
			}
		} else if (button2()) {
			while (bttn2()) {
				if (ptinrect((p = mouse.xy), ICON)) {
					p = sub(p, ICON.origin);
					cur.x = p.x / Xsize;
					cur.y = p.y / Ysize;
					if (geticonpoint(cur) == true) 
						flipiconpoint(cur);
				}
			}
		}
		if (button3()) {
			hit = imenuhit(imenu);
			switch (5 * hit.y + hit.x) {
			case BLIT:
				OpGeneralBlit();
				break;
			case MOVE:
				OpBlit(I_CLR, I_OR);
				break;
			case COPY:
				OpBlit(I_OR, I_OR);
				break;
			case ERASE:
				OpErase();
				break;
			case INVERT:
				OpInvert();
				break;
			case REFLECTX:
				OpReflX();
				break;
			case REFLECTY:
				OpReflY();
				break;
			case ROTATEPLUS:
				OpRotPlus();
				break;
			case ROTATEMINUS:
				OpRotMinus();
				break;
			case SHEARX:
				OpHorShear();
				break;
			case SHEARY:
				OpVerShear();
				break;
			case STRETCH:
				OpStretch();
				break;
			case TEXTURE:
				OpTexture16();
				break;
			case GRID:
				DrawGrid();
				break;
			case PICK:
				PickUpCursor();
				break;
			case READ:
				b = balloc(sourcebitmap->rect);
				if (b == ((Bitmap * ) 0)) 
					break;
				StoreIcon(b, b->rect);
				OpRead(b);
				if(!(P->state&RESHAPED))
					FetchIcon(b, b->rect, Pt(0, 0), Rect(0, 0, Xblocks, Yblocks));
				bfree(b);
				break;
			case WRITE:
				b = balloc(sourcebitmap->rect);
				if (b == ((Bitmap * ) 0)) 
					break;
				StoreIcon(b, b->rect);
				if (OpWrite(b, drawrect))
					perror("error occurred in writing file ");
				bfree(b);
				break;
			case SPARE1:
				break;
			case HELP:
				Help();
				break;
			case EXIT:
				cursswitch(&Cexit);
				while (!bttn123()) {
					wait(CPU); 
					wait(MOUSE);
				}
				if (bttn3()) {
					while (bttn3()) {
						wait(CPU); 
						wait(MOUSE);
					}
					cursswitch((Texture16 * ) 0);
					StoreIcon(sourcebitmap, sourcerect);
					return(0);
				} else {
					while (bttn12()) {
						wait(CPU); 
						wait(MOUSE);
					}
					cursswitch((Texture16 * ) 0);
					break;
				}
			}
		}
	}
}


getstr(s, p)
char	*s;
Point p;
{
	char	c, *t;
	static char	str[] = "x";
	t = s;
	for (; ; ) {
		wait(KBD|RESHAPED);
		if(P->state&RESHAPED) {
			*t = '\0'; /* abort */
			return;
		}
		if (((c = kbdchar()) == '\r') || (c == '\n')) {
			*s = '\0';
			return;
		}
		if (c == '\b') {
			if (s > t) {
				str[0] = *(--s);
				string(&mediumfont, str, &display, (p = sub(p, Pt(9, 0))), F_XOR);
			}
		} else if ((c >= '!') && (c <= '~')) {
			if (s - t < 50) {
				*s++ = (str[0] = c);
				p = string(&mediumfont, str, &display, p, F_XOR);
			}
		}
	}
}


Point char_to_bits(x,y,p)
int x,y;
struct Proc *p;
{
	Point q;
	int inc=1;
	do {
		q.y = (ysize + 40) + (inc*ysize);
		q.x = (xsize + 40) + (inc*xsize);
	} while (
		 (((ysize + 40) + (++inc*ysize)) < YMAX*3/4) &&
		 (((xsize + 40) + (inc*xsize)) < XMAX*3/4) &&
		 (inc<20));
	q.x=min(max(q.x,256),XMAX);
	q.y=min(max(q.y,256),YMAX);
	return(q);
}




/*  This routine stolen from dmdmemory so not everything is needed */
void
setstrg (s)
char *s;
{
	register x = Drect.origin.x + 15;
	register y = Drect.origin.y + 40;
	Point p;
	static int Ipt = 0;	/* so we don't erase more than we should */
	Point string();


	/*rectf (&display, Rect(x,y,min(Drect.corner.x, x+Ipt),y+CH), F_CLR);
	*/p = string (&mediumfont, s, &display, Pt(x,y), F_XOR);
	Ipt = p.x - x;
}



main(argc, argv)
char	*argv[];
{

	int value;
	Point span,temporg;
	char	*InitFile = NULL;
	char c = ' ';

	P->ctob = char_to_bits;

	dmdpath[0] = '\0';

	while (--argc) {
		++argv;
		if (**argv == '-') {
			switch (argv[0][1]) {
			case 'd':
				argc--;
				strcpy(dmdpath, *++argv);
				strcat(dmdpath, "/icons");
				break;

			case 'c':
				cache ("icon", A_NO_SHOW);
				break;

			/* taken out because we now pass through stdin 
			case 'x':
				argc--;
				xsize = atoi(*++argv);
				break;
			case 'y':
				argc--;
				ysize = atoi(*++argv);
				break;
			*/

			}
		} else {
			InitFile = argv[0];
		}
	}

	if (dmdpath[0] == '\0') {
		fprintf(stderr,"icon: -d option required.\n");
		exit();
	}
	
	nullpoint.x = 0;
	nullpoint.y = 0;
	point16x16.x = 16;
	point16x16.y = 16;
	nullrect.origin = nullpoint;
	nullrect.corner = nullpoint;
	rect16x16.origin = nullpoint;
	rect16x16.corner = point16x16;

	bittester = balloc(Rect(0, 0, 1, 1));
	pickupmap = balloc(Rect(0, 0, 16, 16));

	request(MOUSE | SEND | KBD | RCV);


	/* this kludge is here because dmdld won't pass arguments to a
	 * cached application.  Note the code above that handled x and y as
	 * arguments.  Now they come in on standard input because the shell
	 * can pass them that way
  	 */
	xsize = 0;
	while (c == ' ') c = getchar();
	while ((c != ' ') && (c != EOF)) {
		if ((c<='9') && (c>='0')) xsize = 10*xsize + (int)(c - '0');
		c = getchar();
	}
	ysize = 0;
	while (c == ' ') c = getchar();
	while ((c != ' ') && (c != EOF)) {
		if ((c<='9') && (c>='0')) ysize = 10*ysize + (int)(c - '0');
		c = getchar();
	}


	/* *****  while (true) imenuhit(imenu); */

	if (xsize <= 0) 
		xsize = XSIZE;
	else xsize=min(xsize,MAXXSIZE);
	if (ysize <= 0) 
		ysize = YSIZE;
	else ysize=min(ysize,MAXYSIZE);

	pmap = balloc(Rect(0, 0, xsize, ysize));
	if (pmap == ((Bitmap * ) 0))  {
		fprintf(stderr,"icon: no memory in DMD.\n");
		exit();
	}
	rectf(pmap, pmap->rect, F_CLR);

	if (InitFile) {
		OpLoad(pmap, InitFile);
	}

	do {
		P->state &= ~RESHAPED;
		if (Icon(pmap, pmap->rect, Drect) == WINDOW_TOO_SMALL) {
			labelon();
			labeltext("icon",4,L_LEFT);
			bitblt(&gridmap,gridmap.rect,&display,add(Drect.origin, Pt(4,4)), F_STORE);
			bitblt(&gridmap,gridmap.rect,&display,add(Drect.origin, Pt(20,4)), F_STORE);
			bitblt(&gridmap,gridmap.rect,&display,add(Drect.origin, Pt(4,20)), F_STORE);
			bitblt(&gridmap,gridmap.rect,&display,add(Drect.origin, Pt(20,20)), F_STORE);
			setstrg ("menu on button 2");

			P->state &= ~RESHAPED;
			for (;;) {
				wait(CPU);
				if ((P->state&RESHAPED) &&
					!(P->state&MOVED))  break;
			
				if (button2()) {
				    if ((value = menuhit(&reshapemenu,2)) != -1) {

					span = char_to_bits(0,0,P);

					temporg.x = mouse.xy.x-(span.x/2);
					if (temporg.x<0) temporg.x=0;
					else if (temporg.x>(XMAX-span.x)) temporg.x=(XMAX-span.x);

					temporg.y = mouse.xy.y-(span.y/2);
					if (temporg.y<0) temporg.y=0;
					else if (temporg.y>(YMAX-span.y)) temporg.y=(YMAX-span.y);
		
					reshape(Rpt(temporg,Pt(
							temporg.x+span.x,
							temporg.y+span.y)));
					}
				}
				else if (button3()) {
					unrequest(MOUSE);
					sleep(2);
					dorequest(MOUSE);
				}
			}
			labeloff();
		}
	} while (P->state & RESHAPED);
	bfree(pmap);

	exit();

}


