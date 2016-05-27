/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */

/* static char _loadfont_sccsid[]="@(#)loadfont.h	1.1.1.2	(5/10/87)"; */


/* possible message types sent to terminal */
#define T_SLOAD		1	/* start loading a font */
#define T_LOAD		2	/* part of load of font */
#define T_TERM		3	/* terminate load */
#define T_ERR		4	/* error message to be displayed */
#define T_REMOVE	5	/* remove the given font */
#define T_QUIT		6	/* exit terminal program */
#define T_MENU		7	/* add a menu item */
#define T_START		8	/* tell the terminal side to look at bttn 2 */
#define T_ICON		9	/* put an icon in the menu */
#define T_DEBUG		10	/* set for debugging */
#define T_PROTO		11	/* change the protocol */

/* possible message types sent to host */
#define H_LOAD		1	/* load the given font */
#define H_TERM		2	/* terminate load */
#define H_QUIT		3	/* quit the program */
/*
 * SUCCEEDED and FAILED added by DWD 7/12/93 mostly for flow control:
 *  the terminal sends a message back at the end of the load so the
 *  host knows it's done.  While I was at it I figured I might as well
 *  give some feedback to the host on whether or not the fontcache() call
 *  suceeded.
 */
#define H_SUCCEEDED	4	/* font cache after load succeeded */
#define H_FAILED	5	/* font cache after load failed */

/* possible menu selections */
#define M_TERM		1	/* terminate download of font */
#define M_LOAD		2	/* load a font */
#define M_REMOVE	3	/* remove a font from the cache */
#define M_QUIT		4	/* quit the program */
#define M_KEYBOARD	5	/* keyboard load of font */

/* possible receive packet states */
#define R_NULL		0	/* not in a packet */
#define R_SIZE		1	/* expecting size */
#define R_DATA		2	/* expecting data */

#define MAXPACKETSIZE	128

typedef struct Rpacket { /* received packet */
	int state;	/* current state */
	int numread;	/* number of characters read into buffer so far */
	unsigned char buf[MAXPACKETSIZE];
	int size;	/* size of this packet */
	int typ;	/* type of packet */
	/* more to be added when non-mux protocol defined */
} Rpacket;

