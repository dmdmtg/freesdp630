#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.10	(5/12/87)

include ../../stand.defs

OBJ=\
	Cursallow.o \
	Cursinhibi.o \
	Cursswitch.o \
	Iceil.o \
	Ifloor.o \
	abs.o \
	acia_reset.o \
	add.o \
	add_msqid.o \
	addr.o \
	alarm.o \
	alloc.o \
	allocown.o \
	allocset.o \
	attach.o \
	balloc.o \
	bfree.o \
	bitblt.o \
	bootmux.o \
	box.o \
	bttns.o \
	canon.o \
	challoc.o \
	chgcalloc.o \
	clipbttn.o \
	cursallow.o \
	cursinhibi.o \
	cursset.o \
	cursswitch.o \
	cursxyoff.o \
	cursxyon.o \
	del_msqid.o \
	delete.o \
	div.o \
	dorequest.o \
	downback.o \
	emptyoutq.o \
	enterget.o \
	enterput.o \
	eqpt.o \
	eqrect.o \
	exit.o \
	f_cache.o \
	ffree.o \
	findfont.o \
	findobj.o \
	fontfont.o \
	fontiname.o \
	fontname.o \
	fontreleas.o \
	fontreques.o \
	fontused.o \
	free.o \
	free_msq.o \
	gcallocown.o \
	gcfree.o \
	getchar.o \
	getnchars.o \
	getwbuf.o \
	greymore.o \
	inset.o \
	ismpx.o \
	itoc.o \
	jstrwidth.o \
	kbdchar.o \
	labelicon.o \
	labeloff.o \
	labelon.o \
	labeltext.o \
	last_windo.o \
	lbitblt.o \
	local.o \
	locproc.o \
	lpoint.o \
	lrectf.o \
	lsegment.o \
	ltexture.o \
	max.o \
	memcpy.o \
	memtest.o \
	min.o \
	minnewrect.o \
	move.o \
	movrect.o \
	msgbox.o \
	mul.o \
	nap.o \
	newmore.o \
	newproc.o \
	newrect.o \
	newwindow.o \
	nonmuxload.o \
	objused.o \
	olyload.o \
	outqavail.o \
	own.o \
	peel.o \
	pfkey.o \
	pfkeyset.o \
	point.o \
	printqclea.o \
	proclayer.o \
	psendchar.o \
	psendnchar.o \
	ptinrect.o \
	putwbuf.o \
	raddp.o \
	rcvchar.o \
	rcvnchars.o \
	realalloc.o \
	realcache.o \
	realgcallo.o \
	realtime.o \
	rectXrect.o \
	rectclip.o \
	rectf.o \
	reqkbdID.o \
	reqobj.o \
	request.o \
	reshape.o \
	ringbell.o \
	rsubp.o \
	screenswap.o \
	segment.o \
	sendchar.o \
	sendnchars.o \
	sendtokbd.o \
	set_msg_wa.o \
	setupval.o \
	setVal.o \
	showerror.o\
	sleep.o \
	spl0.o \
	spl1.o \
	spl2.o \
	spl3.o \
	spl4.o \
	spl5.o \
	spl6.o \
	spl7.o \
	splx.o \
	string.o \
	strlen.o \
	strwidth.o \
	sub.o \
	sw.o \
	sysctl.o \
	tell_excep.o\
	texture.o \
	tm_ret.o \
	tmenuhit.o \
	tolayer.o \
	toproc.o \
	transform.o \
	uncache.o \
	unreqcache.o \
	unreqobj.o \
	unrequest.o \
	upfront.o \
	upproc.o \
	version.o \
	wait.o \
	whathost.o \
	whichlayer.o \
	whichproc.o \
	xpsendchar.o \
	xpsendncha.o

PRODUCTS=libfw.a
INSTALL=$(DMDLIB)/libfw.a
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

.s.o:
	$(MCC) $(MCFLAGS) -c $<

libfw.a:	$(OBJ)
	$(MAR) cr libfw.a $(OBJ)

$(DMDLIB)/libfw.a:	libfw.a
	cp libfw.a $(DMDLIB)/libfw.a
	chmod $(MODE644) $(DMDLIB)/libfw.a
