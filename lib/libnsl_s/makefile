#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.10	(5/12/87)

include ../../stand.defs

# TLI local management functions:
OBJS1= t_alloc.o t_bind.o t_close.o t_error1.o t_free.o t_getinfo.o \
       t_getstate.o t_look.o t_open.o t_optmgmt.o t_sync.o t_unbind.o

# TLI connection establishment functions:
OBJS2= t_accept.o t_connect.o t_listen.o t_rcvcon.o

# TLI connection mode data transfer functions:
OBJS3= t_rcv.o t_snd.o

# TLI connection release functions:
OBJS4= t_rcvdis.o t_snddis.o t_sndrel.o t_rcvrel.o

# TLI connectionless mode data transfer functions:
OBJS5= t_rcvudata.o t_rcvuderr.o t_sndudata.o

# STREAMS specific
OBJS6= poll.o ioctl.o fcntl.o

# Terminal specific
OBJS7= flowcntl.o

OBJ= $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7)

PRODUCTS=libnsl_s.a
INSTALL=$(DMDLIB)/libnsl_s.a
CLEAN=$(OBJ) tmp.o peid.o
CLOBBER=$(PRODUCTS)

include ../../stand.targ

.s.o:
	$(MAS) -o tmp.o $<
	$(MLD) -r -o $*.o peid.o tmp.o
	rm tmp.o

libnsl_s.a:	$(OBJ)
	$(MAR) cr libnsl_s.a $(OBJ)

$(DMDLIB)/libnsl_s.a:	libnsl_s.a
	cp libnsl_s.a $(DMDLIB)/libnsl_s.a
	chmod $(MODE644) $(DMDLIB)/libnsl_s.a

$(OBJ):	peid.o

peid.o:		peid.ifile
peid.o: 	peid.s
	$(MAS) -o tmp.o peid.s
	$(MLD) -r -o peid.o tmp.o peid.ifile
	rm tmp.o

flowcntl.o:	flowcntl.c
	$(MCC) -c $(MCFLAGS) flowcntl.c

fcntl.o:	fcntl.c
fcntl.o:	$(DMDINC)/dmd.h
fcntl.o:	$(DMDINC)/dmdti.h
fcntl.o:	$(DMDINC)/dmdfcntl.h
	$(MCC) -c $(MCFLAGS) fcntl.c

