/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _icon_sccsid[]="@(#)icon.h	1.1.1.7	(5/10/87)"; */


#define STRSIZE	120
char	dmdpath[STRSIZE];

#define XSIZE 50
#define YSIZE 50
#define MAXXSIZE 480
#define MAXYSIZE 480

#define bool  int
#define true  1
#define false 0

#define NOHIT    -1

#define I_NULL   -1
#define I_OR      0
#define I_STORE   1
#define I_CLR     2
#define I_XOR     3

#define SPACING 24

#define sgn(x) ((x)<0 ? -1 : (x)==0 ? 0 : 1)

extern Point add();
extern Point sub();
extern Texture16 *cursswitch();
extern Rectangle inset();
extern Rectangle raddp();
extern Bitmap *balloc();
extern Rectangle rsubp();
extern Point string();
extern Word *addr();
extern Rectangle canon();
extern Texture16 *(imenu[]); /* ***** */

#define SRC_ID     0
#define SRC_CLR    1

#define DST_STORE  0
#define DST_OR     1
#define DST_XOR    2
#define DST_CLR    3

#define MOVE        0
#define COPY        1
#define INVERT	    2
#define ERASE	    3

#define REFLECTX    5
#define REFLECTY    6
#define ROTATEPLUS  7
#define ROTATEMINUS 8

#define SHEARX      10
#define SHEARY      11
#define STRETCH     12
#define TEXTURE     13

#define READ	    15
#define GRID        16
#define PICK        17
#define WRITE	    18

#define BLIT        20
#define SPARE1      21
#define HELP        22
#define EXIT	    23

#define WINDOW_TOO_SMALL -2	/* return code from Icon */

extern Texture16 Cmove, Ccopy, Cerase, Cinvert, Cblit, Creflx,
	       Crefly, Crotplus, Crotminus, Cshearx, Csheary,
	       Cstretch, Ctexture16, Cgrid, Ccursor, Cread,
	       Cwrite, Cexit, Chelp, white, menucursor,
	       sweepcursor, sweeportrack, clock, deadmouse;

extern int	lasthitx, lasthity;
extern char	*blitsrctext[];
extern char	*blitdsttext[];
extern char	buf[100], FNAME[50];
extern Point	nullpoint, point16x16;
extern Rectangle icon, ICON, sweep, outl, nullrect, rect16x16;
extern int	Xsize, Ysize;
extern int	Xblocks, Yblocks;
extern int	modx, divx, mody, divy;
extern Menu	blitsrcmenu, blitdstmenu;

extern Rectangle TrackBorder();
extern Point imenuhit();
extern char *strrchr();
extern Bitmap *pmap;
extern void perror();
