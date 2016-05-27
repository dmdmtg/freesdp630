#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code. 

# @(#)makefile	1.1.1.5	(5/22/87)


include ../stand.defs

OBJ=

PRODUCTS=ball bounce clock doodle rose star
INSTALL=$(DMDLIB)/demolib/ball \
	$(DMDLIB)/demolib/bounce \
	$(DMDLIB)/demolib/clock \
	$(DMDLIB)/demolib/doodle \
	$(DMDLIB)/demolib/rose \
	$(DMDLIB)/demolib/star \
	$(DMDLIB)/demobin/clock \
	$(DMDBIN)/dmddemo
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDLIB)/demolib/ball:	ball
	cp ball $(DMDLIB)/demolib/ball
	chmod $(MODE644) $(DMDLIB)/demolib/ball

$(DMDLIB)/demolib/bounce:	bounce
	cp bounce $(DMDLIB)/demolib/bounce
	chmod $(MODE644) $(DMDLIB)/demolib/bounce

$(DMDLIB)/demolib/clock:	clock
	cp clock $(DMDLIB)/demolib/clock
	chmod $(MODE644) $(DMDLIB)/demolib/clock

$(DMDLIB)/demolib/doodle:	doodle
	cp doodle $(DMDLIB)/demolib/doodle
	chmod $(MODE644) $(DMDLIB)/demolib/doodle

$(DMDLIB)/demolib/rose:	rose
	cp rose $(DMDLIB)/demolib/rose
	chmod $(MODE644) $(DMDLIB)/demolib/rose

$(DMDLIB)/demolib/star:	star
	cp star $(DMDLIB)/demolib/star
	chmod $(MODE644) $(DMDLIB)/demolib/star

$(DMDLIB)/demobin/clock:	clock.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g clock.sh > $(DMDLIB)/demobin/clock
	chmod $(MODE755) $(DMDLIB)/demobin/clock

$(DMDBIN)/dmddemo:	dmddemo.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g dmddemo.sh > $(DMDBIN)/dmddemo
	chmod $(MODE755) $(DMDBIN)/dmddemo

########

ball:	ball.c
ball:	$(DMDINC)/dmd.h
ball:	$(DMDINC)/dmdproc.h
ball:	$(DMDINC)/layer.h
ball:	$(DMDINC)/mpx.h
	$(MCC) $(MCFLAGS) ball.c -o ball

bounce:	bounce.c
bounce:	$(DMDINC)/dmd.h
bounce:	$(DMDINC)/dmdproc.h
bounce:	$(DMDINC)/layer.h
bounce:	$(DMDINC)/mpx.h
	$(MCC) $(MCFLAGS) bounce.c -o bounce

clock:	clock.c
clock:	$(DMDINC)/dmd.h
clock:	$(DMDINC)/dmdproc.h
clock:	$(DMDINC)/layer.h
clock:	$(DMDINC)/mpx.h
clock:	$(DMDINC)/font.h
	$(MCC) $(MCFLAGS) clock.c -o clock

doodle:	doodle.c
doodle:	$(DMDINC)/dmd.h
doodle:	$(DMDINC)/dmdproc.h
doodle:	$(DMDINC)/layer.h
doodle:	$(DMDINC)/mpx.h
	$(MCC) $(MCFLAGS) doodle.c -o doodle

rose:	rose.c
rose:	$(DMDINC)/dmd.h
rose:	$(DMDINC)/dmdproc.h
rose:	$(DMDINC)/layer.h
rose:	$(DMDINC)/mpx.h
	$(MCC) $(MCFLAGS) rose.c -o rose

star:	star.c
star:	$(DMDINC)/dmd.h
star:	$(DMDINC)/dmdproc.h
star:	$(DMDINC)/layer.h
star:	$(DMDINC)/mpx.h
	$(MCC) $(MCFLAGS) star.c -o star

#clock.c needs to be in the examples directory for the dmdpi
#chapter in the 630 programming guide.
#star.c needs to be in the examples/Resources directory for
#the Application Resources chapter in the programming guide.

