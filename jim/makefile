#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.2	(5/8/87)

#
# jim master makefile
#
# To make default action, type "make".
# To make an action (like make install) type "make ACTION=install"
#


### Standard Defines ###

include ../stand.defs

all:		build

build:		FRC
	cd host; make $(MAKE_ARGS) build
	cd frame; make $(MAKE_ARGS) build
	cd term; make $(MAKE_ARGS) build

install:	all
	cd host; make $(MAKE_ARGS) install
	cd frame; make $(MAKE_ARGS) install
	cd term; make $(MAKE_ARGS) install

strip:	FRC
	-rm -f $(DMDBIN)/jim
	-rm -f $(DMDLIB)/jim.m

lint: 	FRC
	cd host; make $(MAKE_ARGS) lint

clean:		clobber

clobber:	FRC
	cd host; make $(MAKE_ARGS) clobber
	cd frame; make $(MAKE_ARGS) clobber
	cd term; make $(MAKE_ARGS) clobber

FRC:
