#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.6	(6/17/87)

include ../stand.defs

CFLAGS=-I$(DMDINC) -I$(DMDSYSINC) $(EXTRACFLAGS)
LDFLAGS=
OBJ=jx.o sysint.o ver.o

PRODUCTS=jx sysint
INSTALL=$(DMDBIN)/jx $(DMDLIB)/sysint
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/jx:	jx
	cp jx $(DMDBIN)/jx
	strip $(DMDBIN)/jx
	chmod $(MODE755) $(DMDBIN)/jx

$(DMDLIB)/sysint:	sysint
	cp sysint $(DMDLIB)/sysint
	strip $(DMDLIB)/sysint
	chmod $(MODE755) $(DMDLIB)/sysint

jx:	jx.c ver.c
jx:	$(DMDINC)/quiet.h 
jx:	$(DMDSYSINC)/sys/jioctl.h 
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -o jx -DDEFDMD=\"$(DEFDMD)\" jx.c ver.c $$HOSTAGENT $(CFLAGS)

sysint:	sysint.c 
sysint:	comm.h 
sysint:	$(DMDSYSINC)/sys/jioctl.h 
	$(CC) $(LDFLAGS) -o sysint sysint.c $(CFLAGS)


########
