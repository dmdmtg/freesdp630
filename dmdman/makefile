#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.2	(5/8/87)

include ../stand.defs

OBJ=

PRODUCTS=
INSTALL=$(DMDBIN)/dmdman
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/dmdman:	dmdman.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g dmdman.sh > $(DMDBIN)/dmdman
	chmod $(MODE755) $(DMDBIN)/dmdman
