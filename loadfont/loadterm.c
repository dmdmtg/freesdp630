/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)loadterm.c	1.1.1.10	(6/1/87)";

#include <dmd.h>
#include <font.h>
#include <menu.h>
#include <string.h>
#include <label.h>
#include "loadfont.h"
#include <object.h>

typedef struct Global {
	Titem *_mu_load_item;	/* load menu items */
	Tmenu *_mymenu;		/* current menu to use */
	int (*_rcvpkt)();	/* receive protocol routine */
	int (*_sendpkt)();	/* send protocol routine */
	Rpacket _rpacket;	/* received packet */
	int _dflag;		/* debugging flag */
	int _started;		/* can start using the menu */
	int _inpacket;		/* read from rpacket by myinbyte */
	int _inchar;		/* number of chars read from rpacket */
	long _incount;		/* number of chars read by myinbyte */
	int _incursor;		/* clock cursor number */
	int _termdnld;		/* font download terminated by host (menu) */
} Global;

#define global		((Global *)(P->appl))
#define mu_load_item	(global->_mu_load_item)
#define mymenu		(global->_mymenu)
#define rcvpkt		(global->_rcvpkt)
#define sendpkt		(global->_sendpkt)
#define rpacket		(global->_rpacket)
#define dflag		(global->_dflag)
#define started		(global->_started)
#define inpacket	(global->_inpacket)
#define inchar		(global->_inchar)
#define incount		(global->_incount)
#define incursor	(global->_incursor)
#define termdnld	(global->_termdnld)

Titem *menugen();
Titem mi_remove;
Tmenu mu_remove = { 0, 0, 0, menugen, 0 };
Titem mi_load[] = { { "Keyboard", M_KEYBOARD }, 0 };
Tmenu mu_load = { mi_load };
Titem mi_main[] = {
	{ "Load", 0, 0, &mu_load },
	{ "Remove", 0, 0, &mu_remove },
	{ "Quit", M_QUIT },
	  0 };
Tmenu mu_main = { mi_main };
Titem mi_term[] = { { "Terminate Download", M_TERM }, 0 };
Tmenu mu_term = { mi_term };
int muxrcvpkt();	/* mux receive protocol routine */
int nonmuxrcvpkt();	/* nonmux receive protocol routine */
int muxsendpkt();	/* mux send protocol routine */
int nonmuxsendpkt();	/* nonmux send protocol routine */
Point sPtCurrent();
Font *infont();
Font *fontavail();

extern char *alloc();

Texture16 C_error =       /* thumbs down */
{
        0x0000, 0x3FE0, 0x4030, 0x401E,
        0x7812, 0x4012, 0x4012, 0x7812,
        0x401E, 0x4030, 0x3E20, 0x0320,
        0x0120, 0x0120, 0x0120, 0x00C0
};

Texture16 C_ok =          /* thumbs up */
{
        0x00C0, 0x0120, 0x0120, 0x0120,
        0x0320, 0x3E20, 0x4030, 0x401E,
        0x7812, 0x4012, 0x4012, 0x7812,
        0x401E, 0x4030, 0x3FE0, 0x0000
};

Texture16 C_clock[] =        /* cursors while font downloading */
{
        0x03c0, 0x3420, 0x37e0, 0x13c0,
        0x17f0, 0x1868, 0x2074, 0x20d4,
        0x418a, 0x430a, 0x430a, 0x418a,
        0x2094, 0x201c, 0x787e, 0x67F6,

        0x03c0, 0x6420, 0x67e0, 0x33c0,
        0x17f0, 0x1868, 0x2014, 0x2014,
        0x400a, 0x430a, 0x478a, 0x4cca,
        0x2074, 0x203c, 0x787e, 0x67f6,

        0x03c0, 0xc420, 0xc7e0, 0x63c0,
        0x37f0, 0x1868, 0x2014, 0x2414,
        0x460a, 0x430a, 0x470a, 0x4c0a,
        0x3814, 0x301c, 0x787e, 0x67f6,

        0x03c0, 0x6420, 0x67e0, 0x33c0,
        0x17f0, 0x1868, 0x3014, 0x3894,
        0x4d8A, 0x470a, 0x430a, 0x400a,
        0x2014, 0x201c, 0x787e, 0x67f6
};


#define FLIPCOUNT 22


main(argc, argv)
int argc;
char **argv;
{
	Global _global;

	if (argc > 1 && argv[1][1] == 'c')
		cache("loadfont", A_NO_SHOW | A_SHARED | A_BSS);
	P->appl = (long)&_global;
	mu_load_item = mi_load;
	mymenu = &mu_main;
	rpacket.state = R_NULL;
	dflag = 0;
	started = 0;
	doreshape();
	request(MOUSE|KBD|RCV);
	cursswitch(&C_deadmouse);
	rcvpkt = muxrcvpkt;
	sendpkt = muxsendpkt;
	while(1)
	{
		do {
			wait(KBD|RCV|MOUSE|RESHAPED);
		}
		while(!(own()&(KBD|RCV|MOUSE|RESHAPED))) ;
		if(own()&RCV)
			dorcvchar();
		if(P->state&RESHAPED)
			doreshape();
		if(button123())
			domouse();
		if(own()&KBD)
			dokbdchar();
	}
}

dokbdchar()
{ /* for now, throw away unwanted keyboard characters */
	while(kbdchar() != -1) ;
}


domouse()
{
/*
 * Mouse button depressed. If button 1 or 3, give it to control.
 */
	if(bttn13())
	{ /* may use button 1 in the future */
		request(KBD|RCV);
		sleep(3);
		request(RCV|KBD|MOUSE);
		cursswitch(started?(Texture16 *)0: &C_deadmouse);
	}
	else if(bttn2() && (started || mymenu == &mu_term))
		domenu();
}



dorcvchar()
{
	char fname[16];
	char *s;

	if((*rcvpkt)(&rpacket))
	{
		switch(rpacket.typ) {
			case T_SLOAD: /* start of download of font */
				rpacket.buf[rpacket.numread] = '\0';
				if(s = strrchr(rpacket.buf, '/'))
					s++;
				else
					s = (char *)rpacket.buf;
				strncpy(fname, s, 14);
				fname[14] = '\0';
				load(fname);
				break;
			case T_LOAD: /* middle of load, throw it away */
				break;
			case T_ERR: /* error message */
				rpacket.buf[rpacket.numread] = '\0';
				lprintf("%s",rpacket.buf);
				break;
			case T_REMOVE: /* remove the given font */
				rpacket.buf[rpacket.numread] = '\0';
				remove(rpacket.buf);
				break;
			case T_QUIT: /* I be going away */
				if(dflag)
					lprintf("exiting now");
				exit();
				break;
			case T_MENU: /* add a menu item to load */
				rpacket.buf[rpacket.numread] = '\0';
				addmenu(rpacket.buf);
				break;
			case T_START: /* start up */
				started = 1;
				cursswitch((Texture16 *)0);
				break;
			case T_DEBUG: /* print debugging messages */
				dflag++;
				break;
			default:
				if(dflag)
					lprintf("bad packet type: %x\r\n",
					   rpacket.typ);
				break;
		}
	}
}


myinbyte()
{
	char buf[15];
	char *itoa();

	while(1)
	{
		if(inpacket)
		{
			if(inchar < rpacket.size)
			{
				if((incount++ % FLIPCOUNT) == 0)
				{
					if(++incursor > 3)
						incursor = 0;
					cursswitch(C_clock + incursor);
				}
				return((unsigned int)rpacket.buf[inchar++]);
			}
			inpacket = 0;
			inchar = 0;
		}
		wait(MOUSE|RCV);
		if(own()&RCV)
		{
			if((*rcvpkt)(&rpacket))
			{
				switch(rpacket.typ) {
					case T_LOAD: /* more for infont */
						inpacket = 1;
						break;
					case T_TERM: /* terminate load */
						lprintf("Load terminated\r\n");
						termdnld = 1;
						sleep(60);
						return(-1);
					default:
						if(dflag)
							lprintf("Bad message type: %x incount: %ld\r\n",rpacket.typ, incount);
						(*sendpkt)(H_TERM, "");
						sleep(60);
						break;
				}
			}
		}
		if(button123())
			domouse();
	}
}

load(name)
char *name;
{
	Font *f;

	inpacket = inchar = 0;
	if(fontavail(name))
	{ /* font is already in terminal */
		(*sendpkt)(H_TERM, "");
		lprintf("%s already loaded\r\n", name);
		return;
	}
	lprintf("Loading %s\r\n", rpacket.buf);
	mymenu = &mu_term;
	incount = 0;
	termdnld = 0;
	if(f = infont(myinbyte))
	{
		if(fontcache(name, f))
		{
			lprintf("%s loaded\r\n", name);
			(*sendpkt)(H_SUCCEEDED, "");
			cursswitch(&C_ok);
		}
		else
		{
			lprintf("%s: unable to cache\r\n", name);
			(*sendpkt)(H_FAILED, "");
			cursswitch(&C_error);
		}
	}
	else
	{
		if(!termdnld)
		{ /* not killed by host */
			lprintf("%s: error during load\r\n", name);
			(*sendpkt)(H_TERM, "");
		}
		cursswitch(&C_error);
	}
	sleep(60);
	cursswitch(started?(Texture16 *)0: &C_deadmouse);
	fontrelease(name);
	mymenu = &mu_main;
}


getfilename()
{
	char buf[140];
	Point p;

	strcpy(buf, "File:");
	if(kbdstring(buf, 100))
	{
		(*sendpkt)(H_LOAD, buf+5);
		lprintf("\r\n");
	}
	else
	{
		p = sPtCurrent();
		moveto(Drect.origin.x, p.y);
		lprintf("     ");
		moveto(Drect.origin.x, p.y);
	}
}




/*
 * Code handling reshape/move.
 */


doreshape()
{
/*
 * Window moved or reshaped.
 */
	labelon();
	if(!(P->state & MOVED))
	{
		labeltext("loadfont", 8, L_CENTER);
		moveto(Pt(0,0));
		lprintf("use button 2 menu to load/remove fonts\r\n");
	}
	P->state &= ~(MOVED|RESHAPED);
}

greyload()
{
/*
 * grey the fonts in the load submenu that are already loaded
 */
	Titem *ti;

	for(ti = mu_load_item + 1; ti->text; ti++)
		if(fontavail(ti->text))
			ti->ufield.grey = 1;
		else
			ti->ufield.grey = 0;
}


domenu()
{
/*
 * Put up a menu on button 2
 */
	register Titem *menuitem;

	mu_load.item = mu_load_item;
	greyload();
	if(menuitem = tmenuhit(mymenu, 2, TM_EXPAND))
	{
		switch(menuitem->ufield.uval)
		{
			case M_TERM:	/* terminate download */
				(*sendpkt)(H_TERM, "");
				break;
			case M_KEYBOARD:	/* load a font */
				getfilename();
				break;
			case M_LOAD:	/* load a font */
				(*sendpkt)(H_LOAD, menuitem->text);
				break;
			case M_REMOVE:	/* remove a font from the cache */
				remove(menuitem->text);
				break;
			case M_QUIT:	/* quit the program */
				(*sendpkt)(H_QUIT, "");
				break;
		}
	}
}


Titem *
menugen(i, m)
int i;
Tmenu *m;
{
/*
 * generate remove font menu
 */
	register Titem *ti = &mi_remove;
	register Font *f;
	register char *cp;
	register int maxn;
	Font *fontavail();
	char *fontiname();

	if(ti->text = fontiname(i))
	{
                f = fontavail(ti->text);
                maxn = 0;
                for(cp=ti->text; *cp; cp++)
                        if(maxn < *cp)
                                maxn = *cp;
                if(maxn < f->n) /* enough chars in font to spell its name */
                        ti->font = f;
                else
                        ti->font = &mediumfont;
		ti->ufield.grey = fontused(ti->text);
		ti->ufield.uval = M_REMOVE;
	}
	return(ti);
}


remove(name)
char *name;
{
/*
 * remove the given font
 */
	if(fontavail(name))
	{
		fontremove(name);
		if(fontavail(name))
			lprintf("unable to remove %s\r\n", name);
		else
			lprintf("%s removed\r\n", name);
	}
	else
		lprintf("%s not in terminal\r\n", name);
}


muxrcvpkt(rp)
Rpacket *rp;
{
	int c;

	if((c = rcvchar()) != -1)
	{
		switch(rp->state)
		{
			case R_NULL:	/* not in a packet */
				rp->typ = c;
				rp->state = R_SIZE;
				break;
			case R_SIZE:	/* getting size of packet */
				rp->size = c;
				rp->numread = 0;
				if(c == 0)
				{
					rp->state = R_NULL;
					return(1);
				}
				else if(rp->size > MAXPACKETSIZE)
					rp->state = R_NULL;
				else
					rp->state = R_DATA;
				break;
			case R_DATA:	/* getting data from the packet */
				rp->buf[rp->numread++] = c;
				if(rp->numread == rp->size)
				{
					rp->state = R_NULL;
					return(1);
				}
				break;
		}
	}
	return(0);
}


muxsendpkt(typ, s)
int typ;
char *s;
{
	char buf[130];

	buf[0] = typ;
	buf[1] = strlen(s);
	strcpy(&buf[2], s);
	if(buf[1] == '\0') /* strlen messes up with a null */
		sendnchars(2, buf);
	else
		sendnchars(strlen(buf), buf);
	if(dflag)
		lprintf("%s\r\n", buf);
}


addmenu(s)
char *s;
{
	Titem *ti;
	int i;
	char *p;

	if((p = alloc(strlen(s))) == 0)
		return;
	strcpy(p, s);
	for(ti = mu_load_item, i=0; ti->text; ti++, i++);
	i+=2;
	if(ti = (Titem *)alloc(sizeof(Titem) * i))
	{
		memcpy(ti, mu_load_item, sizeof(Titem) * (i - 2));
		if(i > 3)
			free(mu_load_item);
		mu_load_item = ti;
		ti += i - 2;
		ti->text = p;
		ti->ufield.uval = M_LOAD;
	}
	else
		free(p);
}


#define kbdcurs(p)	rectf(&display,Rect(p.x,p.y,p.x+1,p.y+largefont.height), F_XOR)

kbdstring(str,nchmax)	/* read string from keyboard with echo at p */
char *str;
int nchmax;
{
	int kbd, nchars, minc, width, i;
	Point p;

	minc=strlen(str);
	lprintf("%s", str);
	p = sPtCurrent();
	kbdcurs(p);
	for (;;) {
		wait(KBD|RESHAPED|MOUSE);
		if(P->state & RESHAPED)
		{
			if(!(P->state & MOVED))
			{
				doreshape();
				lprintf("%s", str);
			}
			p = sPtCurrent();
			if(!(P->state & MOVED))
				kbdcurs(p);
			P->state &= ~(RESHAPED|MOVED);
		}
		if(button13())
		{
			domouse();
		}
		if(!(own()&KBD))
			continue;
		kbdcurs(p);
		switch (kbd=kbdchar()) {
			case '\0':
				break;
			case '\r':
			case '\n':
				return nchars;
			case '\b':
				if (nchars <= 0) break;
				width = strwidth(&largefont, str + --nchars + minc);
				str[nchars+minc]=0;
				if((p.x -= width) < Drect.origin.x)
					if(p.y - largefont.height < Drect.origin.y)
					{
						p.x = Drect.origin.x;
						i = (Drect.corner.x - Drect.origin.x) / width;
						lprintf("%s", &str[nchars+minc-i+1]);
						p = sPtCurrent();
						break;
					}
					else /* wraps */
					{
						p.y -= largefont.height;
						while(p.x < Drect.corner.x)
							p.x += width;
						p.x -= 2 * width;
					}
				moveto(p);
				lputchar(' ');
				moveto(p);
				break;
			default:
				if (nchars >= nchmax) break;
				str[minc + nchars++]=kbd;
				str[minc + nchars]=0;
				lputchar(kbd);
				p = sPtCurrent();
		}
		kbdcurs(p);
	}
}
