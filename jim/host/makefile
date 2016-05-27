#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.7	(6/17/87)

include ../../stand.defs

CFLAGS=-I$(DMDSYSINC) -I$(DMDINC) $(EXTRACFLAGS)
OBJ=alloc.o file.o gcalloc.o jim.o msgs.o pattern.o string.o unix.o

PRODUCTS= jim
INSTALL=$(DMDBIN)/jim $(DMDBIN)/jimunpack
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

$(DMDBIN)/jim:	jim
	cp jim $(DMDBIN)/jim
	strip $(DMDBIN)/jim
	chmod $(MODE755) $(DMDBIN)/jim

jim:	$(OBJ)
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -o jim $(OBJ) $$HOSTAGENT $(CFLAGS)

$(DMDBIN)/jimunpack:	jimunpack.sh
	cp jimunpack.sh $(DMDBIN)/jimunpack
	chmod $(MODE755) $(DMDBIN)/jimunpack

alloc.o:	alloc.c
alloc.o:	jim.h
	$(CC) $(CFLAGS) -c alloc.c

file.o:	file.c
file.o:	jim.h
file.o:	file.h
	$(CC) $(CFLAGS) -c file.c

gcalloc.o:	gcalloc.c
gcalloc.o:	jim.h
	$(CC) $(CFLAGS) -c gcalloc.c

jim.o:	jim.c
jim.o:	jim.h
jim.o:	file.h
jim.o:	msgs.h
	$(CC) $(CFLAGS) -DDEFDMD=\"$(DEFDMD)\" -c jim.c

msgs.o:	msgs.c
msgs.o:	jim.h
msgs.o: msgs.h
	$(CC) $(CFLAGS) -c msgs.c

pattern.o:	pattern.c
pattern.o:	jim.h
pattern.o:	file.h
	$(CC) $(CFLAGS) -c pattern.c

string.o:	string.c
string.o:	jim.h
string.o:	file.h
	$(CC) $(CFLAGS) -c string.c

unix.o:	unix.c
unix.o:	jim.h
unix.o:	file.h
	$(CC) $(CFLAGS) -c unix.c
