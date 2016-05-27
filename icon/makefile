#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  


# @(#)makefile	1.1.1.6	(5/8/87)

include ../stand.defs

LDFLAGS=

OBJ=bitblit.o getfile.o help.o icon.o menu.o read.o reflect.o rotate.o shear.o \
     stretch.o sweep.o texture.o utility.o write.o

PRODUCTS=icon.m
INSTALL=$(DMDBIN)/icon $(DMDLIB)/icon.m
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

DMDICON=$(DMD)/src/icons

include ../stand.targ

icon.m:	$(OBJ) 
	$(MCC) $(LDFLAGS) -o icon.m $(OBJ)

$(DMDLIB)/icon.m:	icon.m
	cp icon.m $(DMDLIB)/icon.m
	$(MSTRIP) -m $(DMDLIB)/icon.m
	chmod $(MODE644) $(DMDLIB)/icon.m

$(DMDBIN)/icon:	icon.sh
	sed -e s+DeFdMd+"$(DEFDMD)"+g icon.sh > $(DMDBIN)/icon
	chmod $(MODE755) $(DMDBIN)/icon

########
#
#	All dependencies and rules not explicitly stated
#	(including header and nested header dependencies)
#
########

bitblit.o:	$(DMDINC)/dmd.h
bitblit.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
bitblit.o:	$(DMDINC)/layer.h # nested include from mpx.h
bitblit.o:	$(DMDINC)/mpx.h # nested include from dmd.h
bitblit.o:	icon.h
bitblit.o:	bitblit.c
	$(MCC) $(MCFLAGS) -c bitblit.c

getfile.o:	$(DMDINC)/dmd.h
getfile.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
getfile.o:	$(DMDINC)/layer.h # nested include from mpx.h
getfile.o:	$(DMDINC)/font.h
getfile.o:	$(DMDINC)/dmdio.h
getfile.o:	$(DMDINC)/mpx.h # nested include from dmd.h
getfile.o:	icon.h
getfile.o:	getfile.c
	$(MCC) $(MCFLAGS) -c getfile.c

help.o:	$(DMDINC)/dmd.h
help.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
help.o:	$(DMDINC)/layer.h # nested include from mpx.h
help.o:	$(DMDINC)/font.h
help.o:	$(DMDINC)/mpx.h # nested include from dmd.h
help.o:	icon.h
help.o:	help.c
	$(MCC) $(MCFLAGS) -c help.c

icon.o:	$(DMDINC)/font.h
icon.o:	$(DMDINC)/label.h
icon.o:	$(DMDINC)/dmd.h
icon.o:	$(DMDINC)/dmdio.h
icon.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
icon.o:	$(DMDINC)/layer.h # nested include from mpx.h
icon.o:	$(DMDINC)/mpx.h # nested include from dmd.h
icon.o:	$(DMDINC)/object.h
icon.o:	icon.h
icon.o:	icon.c
	$(MCC) $(MCFLAGS) -c icon.c

menu.o:	$(DMDINC)/dmd.h
menu.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
menu.o:	$(DMDINC)/layer.h # nested include from mpx.h
menu.o:	$(DMDINC)/mpx.h # nested include from dmd.h
menu.o:	icon.h
menu.o:	menu.c
	$(MCC) $(MCFLAGS) -c menu.c

read.o:	$(DMDINC)/dmd.h
read.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
read.o:	$(DMDINC)/layer.h # nested include from mpx.h
read.o:	$(DMDINC)/font.h
read.o:	$(DMDINC)/dmdio.h
read.o:	$(DMDINC)/mpx.h # nested include from dmd.h
read.o:	icon.h
read.o:	read.c
	$(MCC) $(MCFLAGS) -c read.c

reflect.o:	$(DMDINC)/dmd.h
reflect.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
reflect.o:	$(DMDINC)/layer.h # nested include from mpx.h
reflect.o:	$(DMDINC)/mpx.h # nested include from dmd.h
reflect.o:	icon.h
reflect.o:	reflect.c
	$(MCC) $(MCFLAGS) -c reflect.c

rotate.o:	$(DMDINC)/dmd.h
rotate.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
rotate.o:	$(DMDINC)/layer.h # nested include from mpx.h
rotate.o:	$(DMDINC)/mpx.h # nested include from dmd.h
rotate.o:	icon.h
rotate.o:	rotate.c
	$(MCC) $(MCFLAGS) -c rotate.c

shear.o:	$(DMDINC)/dmd.h
shear.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
shear.o:	$(DMDINC)/layer.h # nested include from mpx.h
shear.o:	$(DMDINC)/mpx.h # nested include from dmd.h
shear.o:	icon.h
shear.o:	shear.c
	$(MCC) $(MCFLAGS) -c shear.c

stretch.o:	$(DMDINC)/dmd.h
stretch.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
stretch.o:	$(DMDINC)/layer.h # nested include from mpx.h
stretch.o:	$(DMDINC)/mpx.h # nested include from dmd.h
stretch.o:	icon.h
stretch.o:	stretch.c
	$(MCC) $(MCFLAGS) -c stretch.c

sweep.o:	$(DMDINC)/dmd.h
sweep.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
sweep.o:	$(DMDINC)/layer.h # nested include from mpx.h
sweep.o:	$(DMDINC)/mpx.h # nested include from dmd.h
sweep.o:	icon.h
sweep.o:	sweep.c
	$(MCC) $(MCFLAGS) -c sweep.c

texture.o:	$(DMDINC)/dmd.h
texture.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
texture.o:	$(DMDINC)/layer.h # nested include from mpx.h
texture.o:	$(DMDINC)/mpx.h # nested include from dmd.h
texture.o:	texture.c
	$(MCC) $(MCFLAGS) -c texture.c

utility.o:	$(DMDINC)/dmd.h
utility.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
utility.o:	$(DMDINC)/layer.h # nested include from mpx.h
utility.o:	$(DMDINC)/mpx.h # nested include from dmd.h
utility.o:	icon.h
utility.o:	utility.c
	$(MCC) $(MCFLAGS) -c utility.c

write.o:	$(DMDINC)/dmd.h
write.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
write.o:	$(DMDINC)/layer.h # nested include from mpx.h
write.o:	$(DMDINC)/dmdio.h
write.o:	$(DMDINC)/mpx.h # nested include from dmd.h
write.o:	icon.h
write.o:	write.c
	$(MCC) $(MCFLAGS) -c write.c

