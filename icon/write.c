/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)write.c	1.1.1.4	(7/1/87)";

#include <dmd.h>
#include <dmdio.h>
#include "icon.h"

char	exa[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

#define BUFSIZE 100
char	buffer[BUFSIZE];
char	*bufend;
unsigned int	error;

bclear()
{
	bufend = buffer;
}


bsend(fp)
FILE *fp;
{
	*bufend = '\0';
	error = error|fputs(buffer, fp);
	bclear();
}


bputc(c, fp)
char	c;
FILE *fp;
{
	if (bufend >= buffer + BUFSIZE - 3) 
		bsend(fp);
	*bufend++ = c;
}


char	getnibble(b, p)
Bitmap *b;
Point p;
{
	int	nibble;
	nibble = 8 * bitmapbit(b, p) + 4 * bitmapbit(b, Pt(p.x + 1, p.y)) + 
	    2 * bitmapbit(b, Pt(p.x + 2, p.y)) + bitmapbit(b, Pt(p.x + 3, p.y));
	return(exa[nibble]);
}

/***********************************************************************
    This routine is called when the menu command WRITE is selected.
***********************************************************************/
unsigned int OpWrite(bitmap, drawrect)
Bitmap *bitmap;
Rectangle drawrect;
{
	FILE * fp;
	char * Bnptr;
	Rectangle r;
	Point p;
	int	i, j, butt;

	error = 0x0;
	butt = GetIconRect(&r);
	if (butt == 3) { /* write in hex format */
		GetFNAME();
		if (!FNAME[0]) 
			return(0);
		fp = fopen(FNAME, "w");
		if (fp == ((FILE * ) 0) || (P->state&RESHAPED)) 
			return(1);
		rectf(&display, drawrect, F_XOR);
		bclear();
		for (j = r.origin.y; j < r.corner.y; j++) {
			for (i = r.origin.x; i < r.corner.x; i += 32) {
				bputc('0', fp);
				bputc('x', fp);
				bputc(getnibble(bitmap, Pt(i, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 4, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 8, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 12, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 16, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 20, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 24, j)), fp);
				bputc(getnibble(bitmap, Pt(i + 28, j)), fp);
				bputc(',', fp);
			}
			bputc('\n', fp);
			bsend(fp);
		}
		error = error|fclose(fp);
		if(!(P->state&RESHAPED))
			rectf(&display, drawrect, F_XOR);
		return(error);
	} else if (butt == 2) { /* write in texture16 format */
		GetFNAME();
		if (!FNAME[0]) 
			return(1);
		fp = fopen(FNAME, "w");
		if (fp == ((FILE * ) 0) || (P->state&RESHAPED))  return(1); 
		rectf(&display, drawrect, F_XOR);
		error = error|fputs("Texture16 ", fp); 
		strcpy(FNAME, ((Bnptr=strrchr(FNAME,'/')) ? (Bnptr + 1) : (FNAME)));
		error = error|fputs(FNAME,fp);
		error = error|fputs(" = {\n", fp);
		j = r.origin.y; 
		i = r.origin.x;
		bclear();
		while (j < r.corner.y) {
			if (((j - r.origin.y) % 4) == 0) 
				bputc('\t', fp);
			bputc(' ', fp);
			bputc('0', fp);
			bputc('x', fp);
			bputc(getnibble(bitmap, Pt(i, j)), fp);
			bputc(getnibble(bitmap, Pt(i + 4, j)), fp);
			bputc(getnibble(bitmap, Pt(i + 8, j)), fp);
			bputc(getnibble(bitmap, Pt(i + 12, j)), fp);
			bputc(',', fp);
			if (((j - r.origin.y) % 4) == 3) 
				bputc('\n', fp);
			j = j + 1;
			bsend(fp);
		}
		error = error|fputs("};\n", fp);
		error = error|fclose(fp);
		if(!(P->state&RESHAPED))
			rectf(&display, drawrect, F_XOR);
		return(error);
	}
}

