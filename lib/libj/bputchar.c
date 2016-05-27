/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)bputchar.c	1.1.1.2	(5/10/87)";

/* bputchar
**
** The same as putchar except it displays at the *B*ottom of the
** screen.
*/

#include <dmd.h>
#include <font.h>

extern Point add();
extern Point string();
void bputchar_scroll();
void bputchar_ctl();

static Rectangle rect = {
	12, YMAX*2/3, XMAX-12, YMAX-12
	};

static Point PtCur;
static int first;
static Font *bfont;

#define  DO		rect.origin
#define  DC		rect.corner

bputchar (c)
register char c;
{
	Point curpos;
	register int num, more;
	Rectangle r;
	Fontchar *inf;

	if(!first) {
		first = 1;
		texture(&physical, Rect(0,rect.origin.y-10,XMAX,YMAX),
		    &T_background, F_STORE);
		rectf(&physical, rect, F_CLR);
		PtCur = add(rect.origin, Pt(2,2));
		if(!bfont)
			bfont = &largefont;
	}

	c &= 0x7f;  /* protect against bad arguments */
	curpos = PtCur;

	switch (c) {

	case '\n' :	/* newline */
		if ( (curpos.y + (2 * FONTHEIGHT(largefont)) ) > DC.y )
			bputchar_scroll(DC.y - curpos.y);
		else
			curpos.y += FONTHEIGHT(largefont);
		/* no break */

	case '\r' :	/* carriage return */
		curpos.x = DO.x;
		break;

	case '\t' :	/* tab */
		num = (curpos.x - DO.x)/FONTWIDTH(largefont);
		more = (num|7) + 1 - num;
		while (more--)
			bputchar(' ');
		curpos = PtCur;
		break;

	default:
		inf = bfont->info + c;
		r.origin.y = 0;
		r.corner.y = bfont->height;
		r.origin.x = inf->x;
		r.corner.x = (inf+1)->x;
		bitblt(bfont->bits, r, &physical, curpos, F_STORE);
		curpos.x += inf->width;
		if(curpos.x + FONTWIDTH((*bfont)) >= DC.x) {
			bputchar('\n');
			curpos = PtCur;
		}
		break;
	}

	PtCur = curpos;
}

void
bputchar_scroll(n)
short n;
{
	Rectangle s;

	s = rect;
	s.origin.y += FONTHEIGHT(largefont);
	bitblt (&physical, s, &physical, DO, F_STORE);
	rectf (&physical, Rect(DO.x, DC.y-n, DC.x, DC.y), F_CLR);
}

#define PF_FONT	1

void
bputchar_ctl(flag, arg)
int flag;
char *arg;
{ /* change bputchar options */
	switch(flag)
	{
		case PF_FONT: /* change font */
			if(arg)
				bfont = (Font *)arg;
			else
				bfont = &largefont;
			break;
	}
}

