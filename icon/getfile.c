/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)getfile.c	1.1.1.3	(7/1/87)";

#include <dmd.h>
#include <dmdio.h>
#include <font.h>
#include "icon.h"

GetFNAME()
{
	Point p;
	cursswitch(&deadmouse);
	p = string(&mediumfont, "File: ", &display, add(icon.corner, Pt(15, -20)), F_XOR);
	getstr(FNAME, p);
	if(!(P->state&RESHAPED)) {
		p = string(&mediumfont, "File: ", &display, add(icon.corner, Pt(15, -20)), F_XOR);
		string(&mediumfont, FNAME, &display, p, F_XOR);
	}
	cursswitch((Texture16 * ) 0);
}

char	SFbuffer[100];

FILE *SearchFile(filename, mode, filefound)
char	*filename, *mode, **filefound;
{
	FILE * fp;
	fp = fopen(filename, mode);
	strcpy(SFbuffer, filename);
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/16x16/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/texture16/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/texture/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/large/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	if (fp == ((FILE * ) 0)) {
		strcpy(SFbuffer, dmdpath); 
		strcat(SFbuffer, "/face48/"); 
		strcat(SFbuffer, filename);
		fp = fopen(SFbuffer, mode);
	}
	*filefound = SFbuffer;
	return(fp);
}

