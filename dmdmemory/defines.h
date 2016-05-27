/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _defines_sccsid[]="@(#)defines.h	1.1.1.1	(5/10/87)"; */

/* states */
#define	ICON	0
#define	VIEW	1


#define ULCX	6	/* Upper Left Corner */
#define	XSPAN	816	/* width of full view window */
#define YSPAN	82	/* height of full view window =
			   VINSET+CH+DIV+BORDER+BARW+BORDER+DIV2+CH+SEP+CH+VINSET */		

#define CW	9	/* medium font width */
#define CH	14	/* medium font height */
#define SW	72	/* 8(digits) * CW, width of slot */
#define sp	25	/* small pacing between bottom slots */
#define bp	195	/* big pacing between bottom slots */
#define sw	sp+SW+bp	/* pacing for upper slots */

#define VINSET	2	/* from window border to view area */
#define DIV	4	/* between upper numerical slots and graphical bar */
#define DIV2	6	/* between graphical bar and lower numerical slots */
#define SEP	6	/* between numerical slots and alpha fields */

#define MARKNUM	100	/* 100 markings on graphical bar */
#define MARKINC	8	/* 8 pixels separate the markings */
#define MARKHI	4	/* height of a marking */

#define BARW	8	/* graphical bar width */
#define BORDER	2	/* graphical bar border width */
#define BARL	800l	/* graphical bar length = MARKNUM * MARKINC */
#define BARLW	50	/* graphical bar length in terms of Word (16 pixels) */

#define YSET	VINSET+CH+DIV+BORDER+BARW+BORDER+DIV2	/* y-position of bottom field */

#define A_BUSY		0
#define GC_ASTRAY	1
#define GC_BUSY		2
#define A_FREE		3
#define GC_FREE		4

#define	C_START		3
#define A_LEVEL		4
#define A_LIM		5
#define GC_LEVEL	6
#define C_END		7
#define SLOTNUM		8

#define UPPERSLOTS	3
#define TXTNUM		3


#define ALLOC		0
#define GCALLOC		1


#define CLR	0
#define XOR	1
#define CLR_XOR	2
