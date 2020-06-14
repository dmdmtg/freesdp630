#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.3	(6/2/87)

include ../stand.defs

CFLAGS=-I$(DMDSYSINC) -I$(DMDINC) -I$(DMDINC)/ccs $(EXTRACFLAGS)
OBJ=dmdld.o proto.o pcheck.o io.o reloc.o shakecode.o ver.o 

PRODUCTS = dmdld
INSTALL=$(DMDBIN)/dmdld
CLEAN = $(OBJ) shake.o
CLOBBER=$(PRODUCTS)

include ../stand.targ

dmdld:	$(OBJ)
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -o dmdld $(OBJ) $$HOSTAGENT $(CFLAGS)

$(DMDBIN)/dmdld:	dmdld
		cp dmdld $(DMDBIN)/dmdld
		strip $(DMDBIN)/dmdld
		chmod $(MODE755) $(DMDBIN)/dmdld

shakecode.o : shakecode.c

shakecode.c : shake.s makecode.sh
	$(MCC) -c shake.s
	sh -x makecode.sh $(MDIS) shake.o Handshakecode >shakecode.c

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

dmdld.o:	dmdld.c
dmdld.o:	$(DMDINC)/quiet.h
dmdld.o:	$(DMDINC)/dmd.h
dmdld.o:	$(DMDINC)/mpx.h		# nested inside dmd.h
dmdld.o:	$(DMDINC)/layer.h	# nested inside mpx.h
dmdld.o:	$(DMDINC)/dmdproc.h	# nested inside mpx.h
dmdld.o:	proto.h
dmdld.o:	load.h
	$(CC) $(CFLAGS) -c dmdld.c

pcheck.o:	pcheck.c
	$(CC) $(CFLAGS) -c pcheck.c

proto.o:	proto.c
proto.o:	proto.h
	$(CC) $(CFLAGS) -c proto.c

io.o:	io.c
io.o:	proto.h
io.o:	load.h
	$(CC) $(CFLAGS) -c io.c

reloc.o:	reloc.c
	$(CC) $(CFLAGS) -c reloc.c

ver.o:	ver.c
	$(CC) $(CFLAGS) -c ver.c
