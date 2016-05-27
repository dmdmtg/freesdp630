include ../../stand.defs

MDIR=	$(DMD)/man/man3
CATMDIR=$(DMD)/catman/DMD/g3
MODE644=644

SRCS=	abs.3 addr.3 alloc.3 atof.3 attach.3 balloc.3 bessel.3 \
	bitblt.3 box.3 bputchar.3 bsearch.3 btoc.3 buttons.3 cache.3 \
	canon.3 circle.3 cmdcache.3 conv.3 ctype.3 cursor.3 decache.3 \
	drand48.3 ecvt.3 ellipse.3 eq.3 erf.3 exit.3 exp.3 floor.3 \
	fontname.3 fontrequest.3 fontsave.3 fontused.3 fpt.3 frexp.3 \
	gamma.3 gcalloc.3 getwbuf.3 globals.3 hypot.3 infont.3 \
	inset.3 integer.3 ismpx.3 itox.3 itrig.3 jcircle.3 jellipse.3 \
	jmove.3 jpoint.3 jrectf.3 jsegment.3 jstring.3 jtexture.3 \
	kbdchar.3 keyboard.3 labelon.3 local.3 lputchar.3 lsearch.3 \
	lsqrt.3 matherr.3 memory.3 menuhit.3 moveto.3 msgbox.3 msgctl.3 \
	msgget.3 msgop.3 muldiv.3 newrect.3 norm.3 peel.3 pfkey.3 \
	point.3 polygon.3 printf.3 printq.3 psendchar.3 pt.3 pt2win.3 \
	ptarith.3 ptinrect.3 qsort.3 rand.3 rcvchar.3 realtime.3 \
	rectarith.3 rectclip.3 rectf.3 rectxrect.3 resources.3 \
	ringbell.3 rol.3 screenswap.3 segment.3 sendchar.3 setled.3 \
	setupval.3 sinh.3 sleep.3 ssignal.3 state.3 str.3 string.3 \
	strtol.3 structures.3 strwidth.3 swab.3 texture.3 tmenuhit.3 \
	transform.3 trig.3 version.3 whathost.3 window.3

all:

clean:
clobber:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	cd $(MDIR);ls|xargs chmod $(MODE644)

catman: all
	-mkdir $(CATMDIR)
	-chmod $(MODE755) $(CATMDIR)
	for s in $(SRCS); do \
	    base=`echo $$s|sed "s/\(.*\)\..*/\1/"`; \
	    if [ ! -z "`find $(CATMDIR)/$$base.z -newer $$s -print 2>/dev/null`" ]; then continue; fi; \
	    rm -f $(CATMDIR)/$$base*; \
	    nroff -man $$s > $(CATMDIR)/$$base; \
	    pack -f $(CATMDIR)/$$base; \
	    chmod $(MODE644) $(CATMDIR)/$$base*; \
	done

