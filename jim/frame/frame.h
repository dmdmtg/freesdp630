/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _frame_sccsid[]="@(#)frame.h	1.1.1.2	(5/10/87)"; */

#include <dmd.h>
#include <font.h>
#define	MAXLINES	(YMAX/14)	/* 14==newlnsz */

#define CURSORON	0
#define CURSOROFF	1

typedef struct String{
	char *s;	/* pointer to string */
	short n;	/* number used, no terminal null */
	short size;	/* size of allocated area */
} String;

typedef unsigned char Nchar;	/* number of chars on a line */
typedef struct Frame{
	Rectangle rect;		/* Screen area of frame, exact #lines high */
	Rectangle scrollrect;	/* Screen area of scrollbar */
	Rectangle totalrect;	/* Screen area covered by entire frame */
	String 	str;		/* What's in the frame */
	unsigned short	s1, s2;	/* Indexes of ends of selected text */
	int	scrolly;	/* last argument to tellseek, for redrawing */
	short	nlines;		/* Number of screen lines of text */
	short	nullsel;	/* True if last selection was null */
	short	lastch;		/* Last selected char when s1==s2 */
	short	margin;		/* margin around frame */
	Nchar	cpl[MAXLINES];	/* Number of characters per line */
	short   cursorstate;	/* Tells whether cursor is on */
} Frame;

#define	SCROLLWIDTH	10	/* width of scroll bar */

extern Rectangle canon();
extern Point nullpoint,toscreen(), startline();
extern String snarfbuf;
extern void oprectf();
extern short newlnsz;
extern Point endpoint;	/* last position drawn during a frameop() */
extern complete;	/* did frameop do all it was supposed to? */
extern inscomplete;	/* is full insertion visible on screen? */
extern F_rectf;		/* function code for oprectf */
extern void opnull();	/* do nothing routine for frameop side effects */
extern void opdraw();	/* standard routine to draw the text */
extern Frame *fralloc();
extern Point ptofchar();
extern char *alloc();
extern Point string();
extern Rectangle inset();

#define	D	(&display)
#define	TRUE	1
#define	FALSE	0
#define	cwidth(c)	mediumfont.info[c].width
