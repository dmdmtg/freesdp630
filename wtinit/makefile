#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.1	(5/8/87)


include ../stand.defs 
OBJ=
PRODUCTS=
INSTALL=$(DMDBIN)/wtinit
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../stand.targ

$(DMDBIN)/wtinit:	wtinit.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g wtinit.sh > $(DMDBIN)/wtinit
	chmod $(MODE755) $(DMDBIN)/wtinit
