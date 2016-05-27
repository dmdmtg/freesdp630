/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _globals_sccsid[]="@(#)globals.h	1.1.1.2	(5/10/87)"; */

/* This file is to declare non-integer functions and global variables */

/*
**	FUNCTIONS
*/

/* In fstcore.c */
void drawview();
void setbase();
void setbound();
void setdisplay();
Point setsize();


/* In update.c */
void addrslot();
void drawlim();
long inview();
void numslot();
void setfield();
void viewupdate();


/* In scope.c */
void blink();
long confine();
void drawbar();
void lblk();
long pixtoaddr();
void sblk();
void setlimit();
void setscope();

/* In ltoa.c */
long lmax();
long lmin();
char *ltoa();

/* In peek.c */
void peekproc();
void peekstak();
void procblk();

/* In string.c */
void dragstrg();
void scopestrg();
void setstrg();


/* In stack.c */
void stakblk();
unsigned long searchstack();

/* In core.c */
long *gcfind(), *gcnext();
long *acfind(), *acnext();


/* In firmware */
Point add();
Point string();

/* 
**	VARIABLES
*/
typedef struct Slot {
	long val;	/* value of the slot */
	int x;		/* x offset from Drect */
	int y;		/* y offset from Drect */
} Slot;


typedef struct Foos {
	int id;			/* type of memory */
	long *(*find)();	/* find the block header */
	long *(*next)();	/* find next block */
	int (*last)();		/* is it last block? */
	int (*whatzit)();	/* type of block */
	char *(*own)();		/* ownership */
} Foos;




#define CoreStart	slot[C_START].val
#define CoreEnd		slot[C_END].val

extern long CoreSpan;
extern long CoreUnit;
extern int CoreBase;
extern Slot slot[];
extern Foos foo[];
extern Texture16 *txtr[];
