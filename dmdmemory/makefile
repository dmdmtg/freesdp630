#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.6	(5/8/87)

include ../stand.defs

OBJ=fstcore.o update.o scope.o peek.o string.o stack.o core.o ltoa.o libcore.o

PRODUCTS = dmdmemory.m
INSTALL=$(DMDLIB)/dmdmemory.m $(DMDBIN)/dmdmemory
CLEAN = $(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDLIB)/dmdmemory.m:	dmdmemory.m
	cp dmdmemory.m $(DMDLIB)
	$(MSTRIP) -m $(DMDLIB)/dmdmemory.m	
	chmod $(MODE644) $(DMDLIB)/dmdmemory.m

$(DMDBIN)/dmdmemory:	dmdmemory.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g dmdmemory.sh > $(DMDBIN)/dmdmemory
	chmod $(MODE755) $(DMDBIN)/dmdmemory

dmdmemory.m:	$(OBJ)
	$(MCC) -o dmdmemory.m $(OBJ)

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

fstcore.o:	fstcore.c
fstcore.o:	defines.h
fstcore.o:	globals.h
fstcore.o:	$(DMDINC)/dmd.h
fstcore.o:	$(DMDINC)/mpx.h
fstcore.o:	$(DMDINC)/label.h
fstcore.o:	$(DMDINC)/dmdproc.h
fstcore.o:	$(DMDINC)/layer.h
fstcore.o:	$(DMDINC)/object.h
	$(MCC) $(MCFLAGS) -c fstcore.c

update.o:	update.c
update.o:	defines.h
update.o:	globals.h
update.o:	$(DMDINC)/dmd.h
update.o:	$(DMDINC)/mpx.h
update.o:	$(DMDINC)/label.h
update.o:	$(DMDINC)/dmdproc.h
update.o:	$(DMDINC)/layer.h
	$(MCC) $(MCFLAGS) -c update.c

libcore.o:	libcore.c
	$(MCC) $(MCFLAGS) -c libcore.c

scope.o:	scope.c
scope.o:	defines.h
scope.o:	globals.h
scope.o:	$(DMDINC)/dmd.h
scope.o:	$(DMDINC)/mpx.h
scope.o:	$(DMDINC)/dmdproc.h
scope.o:	$(DMDINC)/layer.h
	$(MCC) $(MCFLAGS) -c scope.c


ltoa.o:		ltoa.c
	$(MCC) $(MCFLAGS) -c ltoa.c

peek.o:		peek.c
peek.o:		defines.h
peek.o:		globals.h
peek.o:		$(DMDINC)/dmd.h
peek.o:		$(DMDINC)/mpx.h
peek.o:		$(DMDINC)/dmdproc.h
peek.o:		$(DMDINC)/layer.h
	$(MCC) $(MCFLAGS) -c peek.c

string.o:	string.c
string.o:	defines.h
string.o:	globals.h
	$(MCC) $(MCFLAGS) -c string.c

stack.o:	stack.c
stack.o:	defines.h
stack.o:	globals.h
	$(MCC) $(MCFLAGS) -c stack.c

core.o:		core.c
core.o:		defines.h
core.o:		globals.h
	$(MCC) $(MCFLAGS) -c core.c
