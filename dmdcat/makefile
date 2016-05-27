#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.6	(6/12/87)

include ../stand.defs 

CFLAGS=-I$(DMDINC) $(EXTRACFLAGS)
OBJ=

PRODUCTS=dmdgetpr
INSTALL=$(DMDBIN)/dmdcat $(DMDLIB)/dmdgetpr
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/dmdcat:	dmdcat.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g dmdcat.sh > $(DMDBIN)/dmdcat
	chmod $(MODE755) $(DMDBIN)/dmdcat

$(DMDLIB)/dmdgetpr:	dmdgetpr
	cp dmdgetpr $(DMDLIB)/dmdgetpr
	chmod $(MODE755) $(DMDLIB)/dmdgetpr

dmdgetpr:	dmdgetpr.c
	$(CC) -o dmdgetpr dmdgetpr.c $(CFLAGS)

