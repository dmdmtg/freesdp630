#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.4	(6/17/87)


### Standard Defines ###

DMD=/usr/local/630
DEFDMD=$(DMD)
DMDBIN=$(DMD)/bin
DMDLIB=$(DMD)/lib
BASE=../..
USRINC=$(BASE)/inc/common
MCC=$(DMD)/bin/dmdcc $(CMSFLG)
MAR=$(DMD)/bin/mc68ar
MSTRIP=$(DMD)/bin/mc68strip
MLORDER=$(DMD)/bin/mc68lorder
MODE755=755
MODE644=644

### Specific Defines ###

EXTRACFLAGS= -O
CFLAGS= $(EXTRACFLAGS)
OBJ= dmdcc.o

PRODUCTS=dmdcc
INSTALL=$(DMDBIN)/dmdcc
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

### Standard Targets ###

all:		$(PRODUCTS)

build:		all

install:	$(INSTALL)

stripit:	strip
strip:		FRC
		-rm -f $(INSTALL)

clean:
		rm -f $(CLEAN) $(CLOBBER)

clobber:	clean

### Additional Dependencies ###
$(DMDBIN)/dmdcc: dmdcc
	rm -f $(DMDBIN)/dmdcc
	cp dmdcc $(DMDBIN)/dmdcc
	strip $(DMDBIN)/dmdcc

dmdcc:	dmdcc.o
	$(CC) -o dmdcc dmdcc.o $(CFLAGS)

dmdcc.o: dmdcc.c
	$(CC) $(CFLAGS) -I$(USRINC) -DDEFDMD=\"$(DEFDMD)\" -c dmdcc.c

lint:
	lint -abch $(CFLAGS) -I$(USRINC) -DDEFDMD=\"$(DEFDMD)\" dmdcc.c 
	
FRC:
