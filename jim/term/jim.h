/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


/* static char _jim_sccsid[]="@(#)jim.h	1.1.1.6	(5/10/87)"; */

#include "../frame/frame.h"
#include "msgs.h"
#include "menu.h"

typedef struct Text{
	Frame	*frame;
	unsigned char file;	/* Which file associated with frame */
	char	obscured;	/* Whether another frame covers part of this */
	int	selecthuge;	/* selection is bigger than visible */
	struct Text *next;	/* linked back to front */
}Text;
extern Rectangle diagrect;
extern int diagclr;
extern short newlnsz;
extern Text *current;	/* which guy we are typing at (can be diag) */
extern Text *worktext;	/* which guy we are working on (never diag) */
extern Text *text;	/* list of text frames */
extern Texture16  bullseye;
extern Texture16 deadmouse;
extern String typein;
extern int diagdone;
extern int diagnewline;
extern int snarfhuge;
extern Text *diag;	/* separate from the rest */
extern Text *txalloc();

#define	PRIME		0
#define	STARDOT		1

#define	INFINITY	32767
#define	M		2

Text	*textoffile(), *textofpoint();

extern Rectangle screenrect;
#define	UP	0
#define	DOWN	1
#define	MAXFILES	256
extern unsigned char menupos[];
extern int iodone, diagdone, scrolllines, filedone;

extern Point div();
extern Point add();
extern Texture16 *cursswitch();
extern Bitmap *balloc();
extern Rectangle inset();
extern char *gcalloc();
extern char *alloc();

extern Rectangle raddp();
extern Point string();

#undef text

typedef struct Globals {
	Message		_m;
	Rectangle	_diagrect;
	Rectangle	_screenrect;
	String		_typein;
	String		_snarfbuf;
	Text		*_worktext;
	Text		*_ttext;
	Text		*_diag;
	int		_diagclr;
	short		_newlnsz;
	Text		*_current;
	Point		_loadpt;		/* location of next host text to be received */
	int		_ntoload;	/* number of characters to read from unix */
	int		(*_donetest)(); /* test to decide when load is done */
	int		_snarfhuge;
	/*
	 * Event flags to wait for in protocol
	 */
	int _iodone, _diagdone, _scrolllines, _filedone;
	int _reqlimit, _nrequested, _reqposn;
	unsigned char _menupos[MAXFILES];
	int _nnames;
	char *_name1[MAXFILES+1];
	int _nc, _lasty, _wrapped, _doubleclickOK, _inscomplete;
	Point _endpoint;
	char *_lnames[6];
	Menu _locmenu;
	char _searchstring[11];
	char _unixstring[11];
	int _seenunix;
}  Globals;


#define m		(((struct Globals *)(P->appl))->_m)
#define diagrect	(((struct Globals *)(P->appl))->_diagrect)
#define screenrect	(((struct Globals *)(P->appl))->_screenrect)
#define typein		(((struct Globals *)(P->appl))->_typein)
#define snarfbuf	(((struct Globals *)(P->appl))->_snarfbuf)
#define worktext	(((struct Globals *)(P->appl))->_worktext)
#define ttext		(((struct Globals *)(P->appl))->_ttext)
#define diag		(((struct Globals *)(P->appl))->_diag)
#define diagclr		(((struct Globals *)(P->appl))->_diagclr)
#define newlnsz		(((struct Globals *)(P->appl))->_newlnsz)
#define current		(((struct Globals *)(P->appl))->_current)
#define loadpt		(((struct Globals *)(P->appl))->_loadpt)
				/* location of next host text to be received */
#define ntoload		(((struct Globals *)(P->appl))->_ntoload)
				/* number of characters to read from unix */
#define donetest	(((struct Globals *)(P->appl))->_donetest)
				 /* test to decide when load is done */
#define snarfhuge	(((struct Globals *)(P->appl))->_snarfhuge)
	/*
	 * Event flags to wait for in protocol
	 */
#define iodone		(((struct Globals *)(P->appl))->_iodone)
#define diagdone	(((struct Globals *)(P->appl))->_diagdone)
#define scrolllines	(((struct Globals *)(P->appl))->_scrolllines)
#define filedone	(((struct Globals *)(P->appl))->_filedone)
#define reqlimit	(((struct Globals *)(P->appl))->_reqlimit)
#define nrequested	(((struct Globals *)(P->appl))->_nrequested)
#define reqposn		(((struct Globals *)(P->appl))->_reqposn)
#define menupos		((struct Globals *)(P->appl))->_menupos
#define nnames		(((struct Globals *)(P->appl))->_nnames)
#define name1		(((struct Globals *)(P->appl))->_name1)
#define nc		(((struct Globals *)(P->appl))->_nc)
#define lasty		(((struct Globals *)(P->appl))->_lasty)
#define wrapped		(((struct Globals *)(P->appl))->_wrapped)
#define doubleclickOK	(((struct Globals *)(P->appl))->_doubleclickOK)
#define endpoint	(((struct Globals *)(P->appl))->_endpoint)
#define inscomplete	(((struct Globals *)(P->appl))->_inscomplete)
#define lnames		((struct Globals *)(P->appl))->_lnames
#define locmenu		(((struct Globals *)(P->appl))->_locmenu)
#define searchstring	((struct Globals *)(P->appl))->_searchstring
#define unixstring	((struct Globals *)(P->appl))->_unixstring
#define seenunix	(((struct Globals *)(P->appl))->_seenunix)




