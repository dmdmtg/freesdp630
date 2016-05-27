#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.2	(5/10/87)

include ../stand.defs

OBJ=ucache.o

PRODUCTS = ucache.m
INSTALL=$(DMDLIB)/ucache.m $(DMDBIN)/ucache
CLEAN = $(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDLIB)/ucache.m:	ucache.m
	cp ucache.m $(DMDLIB)
	$(MSTRIP) -m $(DMDLIB)/ucache.m	
	chmod $(MODE644) $(DMDLIB)/ucache.m

$(DMDBIN)/ucache:	ucache.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g ucache.sh > $(DMDBIN)/ucache
	chmod $(MODE755) $(DMDBIN)/ucache

ucache.m:	$(OBJ)
	$(MCC) -o ucache.m $(OBJ)

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

ucache.o:	ucache.c
ucache.o:	$(DMDINC)/dmd.h
ucache.o:	$(DMDINC)/mpx.h
ucache.o:	$(DMDINC)/dmdproc.h
ucache.o:	$(DMDINC)/layer.h
ucache.o:	$(DMDINC)/object.h
ucache.o:	$(DMDINC)/menu.h
	$(MCC) $(MCFLAGS) -c ucache.c
