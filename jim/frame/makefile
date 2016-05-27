#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.3	(5/8/87)

include ../../stand.defs

OBJ=deltext.o fralloc.o frameop.o instext.o ptofchar.o

PRODUCTS=frame.a
INSTALL=frame.a
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

frame.a:	$(OBJ)
	$(MAR) uv frame.a $(OBJ)

deltext.o:	deltext.c
deltext.o:	../term/jim.h
deltext.o:	../term/menu.h
deltext.o:	../term/msgs.h
deltext.o:	$(DMDINC)/dmd.h
deltext.o:	$(DMDINC)/mpx.h
deltext.o:	$(DMDINC)/dmdproc.h
deltext.o:	$(DMDINC)/layer.h
deltext.o:	$(DMDINC)/font.h
deltext.o:	frame.h
	$(MCC) $(MCFLAGS) -c deltext.c

fralloc.o:	fralloc.c
fralloc.o:	../term/jim.h
fralloc.o:	../term/menu.h
fralloc.o:	../term/msgs.h
fralloc.o:	$(DMDINC)/dmd.h
fralloc.o:	$(DMDINC)/mpx.h
fralloc.o:	$(DMDINC)/dmdproc.h
fralloc.o:	$(DMDINC)/layer.h
fralloc.o:	$(DMDINC)/font.h
fralloc.o:	frame.h
	$(MCC) $(MCFLAGS) -c fralloc.c

frameop.o:	frameop.c
frameop.o:	frame.h
frameop.o:	../term/jim.h
frameop.o:	../term/menu.h
frameop.o:	$(DMDINC)/dmd.h
frameop.o:	$(DMDINC)/mpx.h
frameop.o:	$(DMDINC)/dmdproc.h
frameop.o:	$(DMDINC)/layer.h
frameop.o:	$(DMDINC)/font.h
frameop.o:	../term/msgs.h
	$(MCC) $(MCFLAGS) -c frameop.c

instext.o:	instext.c
instext.o:	frame.h
instext.o:	../term/jim.h
instext.o:	../term/menu.h
instext.o:	../term/msgs.h
instext.o:	$(DMDINC)/dmd.h
instext.o:	$(DMDINC)/mpx.h
instext.o:	$(DMDINC)/dmdproc.h
instext.o:	$(DMDINC)/layer.h
instext.o:	$(DMDINC)/font.h
	$(MCC) $(MCFLAGS) -c instext.c

ptofchar.o:	ptofchar.c
ptofchar.o:	frame.h
profchar.o:	../term/jim.h
profchar.o:	../term/menu.h
profchar.o:	../term/msgs.h
ptofchar.o:	$(DMDINC)/dmd.h
ptofchar.o:	$(DMDINC)/mpx.h
ptofchar.o:	$(DMDINC)/dmdproc.h
ptofchar.o:	$(DMDINC)/layer.h
ptofchar.o:	$(DMDINC)/font.h
	$(MCC) $(MCFLAGS) -c ptofchar.c
