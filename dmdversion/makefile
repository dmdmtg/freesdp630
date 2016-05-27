#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  


# @(#)makefile	1.1.1.5	(6/2/87)

include ../stand.defs

CFLAGS=-I$(DMDINC) -I$(DMDSYSINC) $(EXTRACFLAGS)
OBJ=dmdversion.o

PRODUCTS=dmdversion
INSTALL=$(DMDBIN)/dmdversion $(DMD)/VERSION
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/dmdversion:	dmdversion
	cp dmdversion $(DMDBIN)/dmdversion
	strip $(DMDBIN)/dmdversion
	chmod $(MODE755) $(DMDBIN)/dmdversion

$(DMD)/VERSION:	VERSION
	TODAY=`date "+%m/%d/%y"`;sed "s-TODAY-$$TODAY-" VERSION >$(DMD)/VERSION
	chmod $(MODE644) $(DMD)/VERSION

dmdversion:	$(OBJ)
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -o dmdversion $(OBJ) $$HOSTAGENT $(CFLAGS)

########

dmdversion.o:	dmdversion.c
dmdversion.o:	$(DMDINC)/dmd.h
dmdversion.o:	$(DMDINC)/layer.h
dmdversion.o:	$(DMDINC)/mpx.h
dmdversion.o:	$(DMDINC)/dmdproc.h
dmdversion.o:	$(DMDSYSINC)/agent.h
dmdversion.o:	$(DMDINC)/quiet.h
	$(CC) $(CFLAGS) -DDEFDMD=\"$(DEFDMD)\" -c dmdversion.c
