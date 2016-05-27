#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.15	6/10/87

include ../../stand.defs

OBJ=Jrect.o Pt.o arc.o atan2.o bputchar.o \
	circle.o cosdeg.o disc.o discture.o elarc.o \
	eldisc.o eldiscture.o ellipse.o ferror.o font.o gcalloc.o \
	icons.o infont.o itoc.o jarc.o jcircle.o \
	jdisc.o jelarc.o jeldisc.o jellipse.o lputchar.o masks.o \
	menu.o message.o moveto.o point2win.o \
	polyf.o rol.o doprnt.o printf.o sqrt.o setjwin.o \
	user.o cache.o clipfix.o cmdcache.o lalloc.o window.o setLED.o whathost.o

PRODUCTS=libj.a
INSTALL=$(DMDLIB)/libj.a
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

libj.a:	$(OBJ)
	$(MAR) cr libj.a $(OBJ)

$(DMDLIB)/libj.a:	libj.a
	cp libj.a $(DMDLIB)/libj.a
	chmod $(MODE644) $(DMDLIB)/libj.a

########

Pt.o:	$(DMDINC)/dmd.h
Pt.o:	$(DMDINC)/dmdproc.h
Pt.o:	$(DMDINC)/layer.h
Pt.o:	$(DMDINC)/mpx.h
Pt.o:	Pt.c
	$(MCC) $(MCFLAGS) -c Pt.c

Jrect.o:	Jrect.c
Jrect.o:	$(DMDINC)/dmd.h
Jrect.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
Jrect.o:	$(DMDINC)/layer.h # nested include from mpx.h
Jrect.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c Jrect.c

arc.o:	arc.c
arc.o:	$(DMDINC)/dmd.h
arc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
arc.o:	$(DMDINC)/layer.h # nested include from mpx.h
arc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c arc.c

atan2.o:	atan2.c
	$(MCC) $(MCFLAGS) -c atan2.c

bputchar.o:	$(DMDINC)/dmd.h
bputchar.o:	$(DMDINC)/font.h
bputchar.o:	$(DMDINC)/dmdproc.h
bputchar.o:	$(DMDINC)/mpx.h
bputchar.o:	$(DMDINC)/layer.h
bputchar.o:	bputchar.c
	$(MCC) $(MCFLAGS) -c bputchar.c

cache.o:	$(DMDINC)/dmd.h
cache.o:	$(DMDINC)/dmdproc.h
cache.o:	$(DMDINC)/layer.h
cache.o:	$(DMDINC)/mpx.h
cache.o:	$(DMDINC)/object.h
cache.o:	$(DMDINC)/menu.h
	$(MCC) $(MCFLAGS) -c cache.c

circle.o:	circle.c
circle.o:	$(DMDINC)/dmd.h
circle.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
circle.o:	$(DMDINC)/layer.h # nested include from mpx.h
circle.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c circle.c

clipfix.o:	clipfix.c
clipfix.o:	$(DMDINC)/dmd.h
clipfix.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
clipfix.o:	$(DMDINC)/layer.h # nested include from mpx.h
clipfix.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c clipfix.c

cosdeg.o:	cosdeg.c
	$(MCC) $(MCFLAGS) -c cosdeg.c

cmdcache.o:	$(DMDINC)/dmd.h
cmdcache.o:	$(DMDINC)/dmdproc.h
cmdcache.o:	$(DMDINC)/layer.h
cmdcache.o:	$(DMDINC)/mpx.h
cmdcache.o:	$(DMDINC)/object.h
cmdcache.o:	$(DMDINC)/menu.h
	$(MCC) $(MCFLAGS) -c cmdcache.c

disc.o:	disc.c
disc.o:	$(DMDINC)/dmd.h
disc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
disc.o:	$(DMDINC)/layer.h # nested include from mpx.h
disc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c disc.c

discture.o:	discture.c
discture.o:	$(DMDINC)/dmd.h
discture.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
discture.o:	$(DMDINC)/layer.h # nested include from mpx.h
discture.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c discture.c

doprnt.o:	doprnt.c
	$(MCC) $(MCFLAGS) -c doprnt.c

elarc.o:	elarc.c
elarc.o:	$(DMDINC)/dmd.h
elarc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
elarc.o:	$(DMDINC)/layer.h # nested include from mpx.h
elarc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c elarc.c

eldisc.o:	eldisc.c
eldisc.o:	$(DMDINC)/dmd.h
eldisc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
eldisc.o:	$(DMDINC)/layer.h # nested include from mpx.h
eldisc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c eldisc.c

eldiscture.o:	eldiscture.c
eldiscture.o:	$(DMDINC)/dmd.h
eldiscture.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
eldiscture.o:	$(DMDINC)/layer.h # nested include from mpx.h
eldiscture.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c eldiscture.c

ellipse.o:	ellipse.c
ellipse.o:	$(DMDINC)/dmd.h
ellipse.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
ellipse.o:	$(DMDINC)/layer.h # nested include from mpx.h
ellipse.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c ellipse.c

ferror.o:	ferror.c
ferror.o:	$(DMDINC)/dmd.h
ferror.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
ferror.o:	$(DMDINC)/layer.h # nested include from mpx.h
ferror.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c ferror.c

font.o:	font.c
font.o:	$(DMDINC)/font.h
font.o:	$(DMDINC)/dmd.h
font.o:	$(DMDINC)/dmdio.h
font.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
font.o:	$(DMDINC)/layer.h # nested include from mpx.h
font.o:	$(DMDINC)/mpx.h # nested include from dmd.h
font.o:	$(DMDINC)/object.h
	$(MCC) $(MCFLAGS) -c font.c

gcalloc.o:	$(DMDINC)/dmd.h
gcalloc.o:	$(DMDINC)/dmdproc.h #nested include from mpx.h
gcalloc.o:	$(DMDINC)/layer.h # nested include from mpx.h
gcalloc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
gcalloc.o:	gcalloc.c
	$(MCC) $(MCFLAGS) -c gcalloc.c

icons.o:	$(DMDINC)/dmd.h
icons.o:	$(DMDINC)/dmdproc.h #nested include from mpx.h
icons.o:	$(DMDINC)/layer.h # nested include from mpx.h
icons.o:	$(DMDINC)/mpx.h # nested include from dmd.h
icons.o:	icons.c
	$(MCC) $(MCFLAGS) -c icons.c

infont.o:	$(DMDINC)/dmd.h
infont.o:	$(DMDINC)/dmdproc.h #nested include from mpx.h
infont.o:	$(DMDINC)/layer.h # nested include from mpx.h
infont.o:	$(DMDINC)/mpx.h # nested include from dmd.h
infont.o:	$(DMDINC)/font.h
infont.o:	infont.c
	$(MCC) $(MCFLAGS) -c infont.c

itoc.o:	$(DMDINC)/dmd.h
itoc.o:	$(DMDINC)/dmdproc.h #nested include from mpx.h
itoc.o:	$(DMDINC)/layer.h # nested include from mpx.h
itoc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
itoc.o:	itoc.c
	$(MCC) $(MCFLAGS) -c itoc.c

jarc.o:	jarc.c
jarc.o:	$(DMDINC)/dmd.h
jarc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jarc.o:	$(DMDINC)/layer.h # nested include from mpx.h
jarc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jarc.c

jcircle.o:	jcircle.c
jcircle.o:	$(DMDINC)/dmd.h
jcircle.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jcircle.o:	$(DMDINC)/layer.h # nested include from mpx.h
jcircle.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jcircle.c

jdisc.o:	jdisc.c
jdisc.o:	$(DMDINC)/dmd.h
jdisc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jdisc.o:	$(DMDINC)/layer.h # nested include from mpx.h
jdisc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jdisc.c

jelarc.o:	jelarc.c
jelarc.o:	$(DMDINC)/dmd.h
jelarc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jelarc.o:	$(DMDINC)/layer.h # nested include from mpx.h
jelarc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jelarc.c

jeldisc.o:	jeldisc.c
jeldisc.o:	$(DMDINC)/dmd.h
jeldisc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jeldisc.o:	$(DMDINC)/layer.h # nested include from mpx.h
jeldisc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jeldisc.c

jellipse.o:	jellipse.c
jellipse.o:	$(DMDINC)/dmd.h
jellipse.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
jellipse.o:	$(DMDINC)/layer.h # nested include from mpx.h
jellipse.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c jellipse.c

lalloc.o:	$(DMDINC)/dmd.h
lalloc.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
lalloc.o:	$(DMDINC)/layer.h # nested include from mpx.h
lalloc.o:	$(DMDINC)/mpx.h # nested include from dmd.h
lalloc.o:	lalloc.c
	$(MCC) $(MCFLAGS) -c lalloc.c

lputchar.o:     $(DMDINC)/dmd.h
lputchar.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
lputchar.o:	$(DMDINC)/layer.h # nested include from mpx.h
lputchar.o:	$(DMDINC)/mpx.h # nested include from dmd.h
lputchar.o:     $(DMDINC)/font.h
lputchar.o:     lputchar.c
	$(MCC) $(MCFLAGS) -c lputchar.c

masks.o:	masks.c
	$(MCC) $(MCFLAGS) -c masks.c

menu.o:	$(DMDINC)/dmd.h
menu.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
menu.o:	$(DMDINC)/layer.h # nested include from mpx.h
menu.o:	$(DMDINC)/mpx.h # nested include from dmd.h
menu.o:	$(DMDINC)/font.h
menu.o:	$(DMDINC)/menu.h
menu.o:	menu.c
	$(MCC) $(MCFLAGS) -c menu.c

message.o:	$(DMDINC)/dmd.h
message.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
message.o:	$(DMDINC)/layer.h # nested include from mpx.h
message.o:	$(DMDINC)/mpx.h # nested include from dmd.h
message.o:	$(DMDINC)/message.h
message.o:	message.c
	$(MCC) $(MCFLAGS) -c message.c

moveto.o:	$(DMDINC)/dmd.h
moveto.o:	moveto.c
	$(MCC) $(MCFLAGS) -c moveto.c

point2win.o:	$(DMDINC)/dmd.h
point2win.o:	$(DMDINC)/mpx.h
point2win.o:	$(DMDINC)/dmdproc.h
point2win.o:	$(DMDINC)/layer.h
point2win.o:	point2win.c
	$(MCC) $(MCFLAGS) -c point2win.c

polyf.o:	$(DMDINC)/dmd.h
polyf.o:	$(DMDINC)/dmdproc.h
polyf.o:	$(DMDINC)/layer.h
polyf.o:	$(DMDINC)/mpx.h
polyf.o:	polyf.c
	$(MCC) $(MCFLAGS) -c polyf.c

printf.o:	printf.c
	$(MCC) $(MCFLAGS) -c printf.c

rol.o:	rol.c
	$(MCC) $(MCFLAGS) -c rol.c

setLED.o:	$(DMDINC)/dmd.h
setLED.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
setLED.o:	$(DMDINC)/layer.h # nested include from mpx.h
setLED.o:	$(DMDINC)/mpx.h # nested include from dmd.h
setLED.o:	$(DMDINC)/kbd_proc.h
setLED.o:	$(DMDINC)/label.h
setLED.o:	setLED.c
	$(MCC) $(MCFLAGS) -c setLED.c

setjwin.o:	setjwin.c
setjwin.o:	$(DMDINC)/dmd.h
setjwin.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
setjwin.o:	$(DMDINC)/layer.h # nested include from mpx.h
setjwin.o:	$(DMDINC)/mpx.h # nested include from dmd.h
setjwin.o:	$(DMDINC)/msgs.h
	$(MCC) $(MCFLAGS) -c setjwin.c

sqrt.o:	sqrt.c
	$(MCC) $(MCFLAGS) -c sqrt.c

user.o:	$(DMDINC)/dmd.h
user.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
user.o:	$(DMDINC)/layer.h # nested include from mpx.h
user.o:	$(DMDINC)/mpx.h # nested include from dmd.h
user.o:	$(DMDINC)/font.h
user.o:	user.c
	$(MCC) $(MCFLAGS) -c user.c

whathost.o:	$(DMDINC)/dmd.h
whathost.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
whathost.o:	$(DMDINC)/layer.h # nested include from mpx.h
whathost.o:	$(DMDINC)/mpx.h # nested include from dmd.h
whathost.o:	whathost.c
	$(MCC) $(MCFLAGS) -c whathost.c

window.o:	$(DMDINC)/dmd.h
window.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
window.o:	$(DMDINC)/layer.h # nested include from mpx.h
window.o:	$(DMDINC)/mpx.h # nested include from dmd.h
window.o:	window.c
	$(MCC) $(MCFLAGS) -c window.c
