#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.8	(6/17/87)

include ../stand.defs

CFLAGS=$(EXTRACFLAGS)
OBJ=

PRODUCTS=loadfont loadfont.m
INSTALL=$(DMDBIN)/loadfont $(DMDLIB)/loadfont.m
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/loadfont:	loadfont
	cp loadfont $(DMDBIN)/loadfont
	strip $(DMDBIN)/loadfont
	chmod $(MODE755) $(DMDBIN)/loadfont

loadfont:	loadfont.c
loadfont:	loadfont.h
	@HOSTAGENT=""; set -x; \
	for F in $(DMDSYS)/lib/libwindows.a ; do \
		if [ -f "$$F" ]; then HOSTAGENT=$$F; break; fi; done; \
	$(CC) -DDEFDMD=\"$(DEFDMD)\" -I$(DMDSYSINC) -o loadfont \
					loadfont.c $$HOSTAGENT $(CFLAGS) 

$(DMDLIB)/loadfont.m:	loadfont.m
	cp loadfont.m $(DMDLIB)/loadfont.m
	$(MSTRIP) -m $(DMDLIB)/loadfont.m
	chmod $(MODE644) $(DMDLIB)/loadfont.m

loadfont.m:	loadterm.c
loadfont.m:	loadfont.h
loadfont.m:	$(DMDINC)/dmd.h
loadfont.m:	$(DMDINC)/mpx.h		# nested in dmd.h
loadfont.m:	$(DMDINC)/layer.h	# nested in mpx.h
loadfont.m:	$(DMDINC)/dmdproc.h	# nested in mpx.h
loadfont.m:	$(DMDINC)/font.h
loadfont.m:	$(DMDINC)/menu.h
loadfont.m:	$(DMDINC)/label.h
loadfont.m:	$(DMDINC)/object.h
	$(MCC) $(MCFLAGS) -o loadfont.m loadterm.c
