#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.3	(6/2/87)

include ../stand.defs

CFLAGS=-I$(DMDSYSINC) -I$(DMDINC) -I$(DMDINC)/ccs $(EXTRACFLAGS)
OBJ=32ld.o pcheck.o proto.o ver.o

PRODUCTS = 32ld 32reloc
CLEAN = $(OBJ) *.v revbyte
CLOBBER=$(PRODUCTS)
INSTALL=$(DMDBIN)/32ld $(DMDBIN)/32reloc $(DMD)/lib/layersys/set_enc.j

include ../stand.targ

32ld:	$(OBJ)
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -o 32ld $(OBJ) -DDEFDMD=\"$(DEFDMD)\" $$HOSTAGENT $(CFLAGS)

$(DMDBIN)/32ld: 32ld
	cp 32ld $(DMDBIN)/32ld
	strip $(DMDBIN)/32ld
	chmod $(MODE755) $(DMDBIN)/32ld

32reloc: 32reloc.c
	$(CC) -o 32reloc 32reloc.c $(CFLAGS)

$(DMDBIN)/32reloc: 32reloc
	cp 32reloc $(DMDBIN)/32reloc
	strip $(DMDBIN)/32reloc
	chmod $(MODE755) $(DMDBIN)/32reloc

#
# make has a problem with a target with a semicolon in it so combine
#  set_enc.j and lsys.8;7;3 in the same rule
#
$(DMDLIB)/layersys/set_enc.j: set_enc.j
	$(CC) -o revbyte revbyte.c $(CFLAGS)
	if ./revbyte; then \
		$(DMD)/bin/mc68conv -t vax set_enc.j; \
		cp set_enc.j.v $(DMDLIB)/layersys/set_enc.j; \
		$(DMD)/bin/mc68conv -t vax lsys.8\;7\;3; \
		cp lsys.8\;7\;3.v $(DMDLIB)/layersys/lsys.8\;7\;3; \
		rm -f *.v; \
	else 	cp set_enc.j lsys.8\;7\;3 $(DMDLIB)/layersys; \
	fi
	rm -f revbyte

32ld.o:		proto.h
	@ECFLAGS="-DNO_AGENTVERSION"; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then ECFLAGS=""; fi; done; \
	$(CC) $(CFLAGS) $$ECFLAGS -c 32ld.c

pcheck.o:	pcheck.c
	$(CC) $(CFLAGS) -c pcheck.c

proto.o:	proto.c
proto.o:	proto.h
	$(CC) $(CFLAGS) -c proto.c

ver.o:	ver.c
	$(CC) $(CFLAGS) -c ver.c
