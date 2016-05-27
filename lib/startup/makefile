#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.3	(5/27/87)

include ../../stand.defs


PRODUCTS = crtm.o
INSTALL =  $(DMDLIB)/crtm.o
CLEAN=$(PRODUCTS)
CLOBBER=$(PRODUCTS)

include ../../stand.targ


crtm.o: crtm.s
	$(MCC) -Wa,-m -c crtm.s

$(DMDLIB)/crtm.o: crtm.o
	cp crtm.o $(DMDLIB)/crtm.o
	chmod $(MODE644) $(DMDLIB)/crtm.o
