/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)read.c	1.1.1.3	(7/1/87)";

#include <dmd.h>
#include <dmdio.h>
#include <font.h>
#include "icon.h"

extern FILE *SearchFile();

void
perror(chstring)
char *chstring;
{
	if(P->state&RESHAPED)
		return;
	string(&mediumfont, chstring, &display, add(icon.corner, Pt(15, -20)), F_XOR);
	sleep(120);
	if(!(P->state&RESHAPED))
		string(&mediumfont, chstring, &display, add(icon.corner, Pt(15, -20)), F_XOR);
}


putnibble(ch, b, clipr, p)
int	ch;
Bitmap *b;
Rectangle clipr;
Point p;
{
	int	nibble;
	if (ch <= '9') 
		nibble = ch - '0';
	else if (ch <= 'F') 
		nibble = 10 + (ch - 'A');
	else 
		nibble = 10 + (ch - 'a');
	if (nibble / 8 == 1) {
		if (ptinrect(p, clipr)) 
			point(b, p, F_OR);
		nibble = nibble % 8;
	}
	p.x += 1;
	if (nibble / 4 == 1) {
		if (ptinrect(p, clipr)) 
			point(b, p, F_OR);
		nibble = nibble % 4;
	}
	p.x += 1;
	if (nibble / 2 == 1) {
		if (ptinrect(p, clipr)) 
			point(b, p, F_OR);
		nibble = nibble % 2;
	}
	p.x += 1;
	if (nibble == 1)
		if (ptinrect(p, clipr)) 
			point(b, p, F_OR);
}

Rectangle OpLoad(bitmap, filename)
Bitmap *bitmap;
char	*filename;
{
	FILE * fp;
	Rectangle rect;
	Texture16 * oldcursor;
	char	*filefound;
	int	flag, ch, i, j;
	int	xsize, ysize;
	rect = bitmap->rect;
	oldcursor = (Texture16 *) cursswitch(&clock);
	fp = SearchFile(filename, "r", &filefound);
	if (fp == ((FILE * ) 0)) {
		perror("Error: File not found ");
		cursswitch((Texture16 * ) 0); 
		return(nullrect);
	}
	ch = getc(fp);
	if (((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
		if (((ch = getc(fp)) != 'x') && (ch != 'X')) {
			/* old format */
			fclose(fp); 
			fp = fopen(filefound, "r");
			if (fp == ((FILE * ) 0)) {
				cursswitch((Texture16 * ) 0); 
				return(nullrect);
			}
			i = rect.origin.x; 
			j = rect.origin.y;
			xsize = 0;
			while ((ch = getc(fp)) != EOF) {
				if (((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <=
				    'f'))) {
					putnibble(ch, bitmap, rect, Pt(i, j));
					i = i + 4;
				} else if (ch == '\n') {
					xsize = max(xsize, i - rect.origin.x);
					i = rect.origin.x;
					j++;
				} else 
					break;
			}
			ysize = j - rect.origin.y;
		} else {
			i = rect.origin.x; 
			j = rect.origin.y;
			xsize = 0;
			for (; ; ) {
				putnibble(getc(fp), bitmap, rect, Pt(i, j)); 
				i += 4;
				putnibble(getc(fp), bitmap, rect, Pt(i, j)); 
				i += 4;
				putnibble(getc(fp), bitmap, rect, Pt(i, j)); 
				i += 4;
				putnibble(getc(fp), bitmap, rect, Pt(i, j)); 
				i += 4;
				ch=getc(fp); /* ',' */
				if ( (ch != ',') && (ch != EOF) ) {
					flag = 1;
					putnibble(ch, bitmap, rect, 
						Pt(i, j));
						i += 4;
					putnibble(getc(fp), bitmap, rect, 
						Pt(i, j));
						i += 4;
					putnibble(getc(fp), bitmap, rect, 
						Pt(i, j));
						i += 4;
					putnibble(getc(fp), bitmap, rect, 
						Pt(i, j));
						i += 4;
					getc(fp); /* ',' */
				}
				ch = getc(fp);
				if (ch == '0') {
					getc(fp); /* 'x' */
				} else if (ch == '\n') {
					xsize = max(xsize, i - rect.origin.x);
					i = rect.origin.x;
					j++;
					getc(fp); /* '0' */
					getc(fp); /* 'x' */
				} else 
					break;
			}
			ysize = j - rect.origin.y;
		}
	} else {
		while ((ch != '{') && (ch != EOF)) 
			ch = getc(fp);
		flag = 0;
		for (j = rect.origin.y; ; j++) {
			while (((ch = getc(fp)) != 'x') && (ch != 'X') && (ch != EOF)) {
			};
			if (ch== EOF) break;
			putnibble(getc(fp), bitmap, rect, Pt(rect.origin.x, j));
			putnibble(getc(fp), bitmap, rect, Pt(rect.origin.x + 4, j));
			putnibble(getc(fp), bitmap, rect, Pt(rect.origin.x + 8, j));
			putnibble(getc(fp), bitmap, rect, Pt(rect.origin.x + 12, j));
			ch = getc(fp);
			if ( (ch != ',') && (ch != EOF) ) {
				flag = 1;
				putnibble(ch, bitmap, rect, 
					Pt(rect.origin.x + 16, j));
				putnibble(getc(fp), bitmap, rect, 
					Pt(rect.origin.x + 20, j));
				putnibble(getc(fp), bitmap, rect, 
					Pt(rect.origin.x + 24, j));
				putnibble(getc(fp), bitmap, rect, 
					Pt(rect.origin.x + 28, j));
			}
		}
		if (flag == 0) xsize = ysize = 16;
		else 	xsize = ysize = 32;
	}
	fclose(fp);
	rect.origin.x = 0; 
	rect.origin.y = 0;
	rect.corner.x = xsize; 
	rect.corner.y = ysize;
	if ( (rect.corner.x == 0) && (rect.corner.y == 0)) 
		perror("Error: File is in invalid format ");
	cursswitch(oldcursor);
	if(P->state&RESHAPED)
		rect = nullrect;
	return(rect);
}

/***********************************************************************
    This routine is called when the menu command READ is selected.
***********************************************************************/
OpRead(bitmap)
Bitmap *bitmap;
{
	Rectangle rect;
	Bitmap * buffer;
	Point p;
	GetFNAME();
	if (!FNAME[0]) 
		return(0);
	buffer = balloc(bitmap->rect);
	if (buffer == ((Bitmap * ) 0)) {
		cursswitch((Texture16 * ) 0); 
		return(0);
	}
	rectf(buffer, buffer->rect, F_CLR);
	rect = OpLoad(buffer, FNAME);
	if (!eqrect(rect, nullrect)) {
		p = TrackBorder(raddp(rect, IconPoint(mouse.xy)), true).origin;
		while (bttn3())
			nap(1);
		bitblt(buffer, buffer->rect, bitmap, p, F_OR);
	}
	bfree(buffer);
}

