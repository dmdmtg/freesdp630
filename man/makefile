# 
#									
#	Copyright (c) 1987,1988,1989,1990,1991,1992   AT&T		
#			All Rights Reserved				
#									
#	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		
#	    The copyright notice above does not evidence any		
#	   actual or intended publication of such source code.		
#									
# 
include ../stand.defs

MDIR=	$(DMD)/man
CATMDIR=$(DMD)/catman
DIRS=	man1 man3 man3n man4 man4n man5

all:	subdir

strip:

subdir: FRC
	for i in $(DIRS); do \
		(cd $$i; make $(MAKE_ARGS)); \
	done

install: all
	-mkdir $(MDIR) 
	-chmod $(MODE755) $(MDIR)
	for i in $(DIRS); do \
		(cd $$i; make $(MAKE_ARGS) install); \
	done

catman: all
	-mkdir $(CATMDIR) $(CATMDIR)/DMD
	-chmod $(MODE755) $(CATMDIR) $(CATMDIR)/DMD
	for i in $(DIRS); do \
		(cd $$i; make $(MAKE_ARGS) catman); \
	done

clean: FRC
	for i in $(DIRS); do \
		(cd $$i; make $(MAKE_ARGS) clean); \
	done

clobber: FRC
	for i in $(DIRS); do \
		(cd $$i; make $(MAKE_ARGS) clobber); \
	done

FRC:
