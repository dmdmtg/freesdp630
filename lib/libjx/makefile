#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.4	(6/18/87)

include ../../stand.defs

OBJ=exit.o fgets.o getfont.o fopen.o popen.o printf.o rdwr.o get.o \
	put.o comm.o data.o sprintf.o doprnt.o bprintf.o lprintf.o smprintf.o

PRODUCTS=libjx.a
INSTALL=$(DMDLIB)/libjx.a
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

libjx.a:	$(OBJ)
	$(MAR) cr libjx.a $(OBJ)

$(DMDLIB)/libjx.a:	libjx.a
	cp libjx.a $(DMDLIB)/libjx.a
	chmod $(MODE644) $(DMDLIB)/libjx.a

########

bprintf.o:	bprintf.c
bprintf.o:	$(DMDINC)/dmdio.h
	$(MCC) $(MCFLAGS) -c bprintf.c

comm.o:	comm.c
comm.o:	$(DMDINC)/dmd.h
comm.o:	$(DMDINC)/dmdio.h
comm.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
comm.o:	$(DMDINC)/layer.h # nested include from mpx.h
comm.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c comm.c

data.o:	data.c
data.o:	$(DMDINC)/dmd.h
data.o:	$(DMDINC)/dmdio.h
data.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
data.o:	$(DMDINC)/layer.h # nested include from mpx.h
data.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c data.c

doprnt.o:	doprnt.c
doprnt.o:	$(DMDINC)/dmdio.h
doprnt.o:	$(DMDINC)/dmd/math.h
doprnt.o:	$(DMDINC)/dmd/values.h
	$(MCC) $(MCFLAGS) -I$(DMDINC) -c doprnt.c

exit.o:	exit.c
exit.o:	$(DMDINC)/dmd.h
exit.o:	$(DMDINC)/dmdio.h
exit.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
exit.o:	$(DMDINC)/layer.h # nested include from mpx.h
exit.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c exit.c

fgets.o:	fgets.c
fgets.o:	$(DMDINC)/dmd.h
fgets.o:	$(DMDINC)/dmdio.h
fgets.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
fgets.o:	$(DMDINC)/layer.h # nested include from mpx.h
fgets.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c fgets.c

fopen.o:	fopen.c
fopen.o:	$(DMDINC)/dmd.h
fopen.o:	$(DMDINC)/dmdio.h
fopen.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
fopen.o:	$(DMDINC)/layer.h # nested include from mpx.h
fopen.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c fopen.c

get.o:	get.c
get.o:	$(DMDINC)/dmd.h
get.o:	$(DMDINC)/dmdio.h
get.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
get.o:	$(DMDINC)/layer.h # nested include from mpx.h
get.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c get.c

getfont.o:	getfont.c
getfont.o:	$(DMDINC)/font.h
getfont.o:	$(DMDINC)/dmd.h
getfont.o:	$(DMDINC)/dmdio.h
getfont.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
getfont.o:	$(DMDINC)/layer.h # nested include from mpx.h
getfont.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c getfont.c

lprintf.o:	lprintf.c
lprintf.o:	$(DMDINC)/dmdio.h
	$(MCC) $(MCFLAGS) -c lprintf.c

popen.o:	popen.c
popen.o:	$(DMDINC)/dmd.h
popen.o:	$(DMDINC)/dmdio.h
popen.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
popen.o:	$(DMDINC)/layer.h # nested include from mpx.h
popen.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c popen.c

printf.o:	printf.c
printf.o:	$(DMDINC)/dmdio.h
	$(MCC) $(MCFLAGS) -c printf.c

put.o:	put.c
put.o:	$(DMDINC)/dmd.h
put.o:	$(DMDINC)/dmdio.h
put.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
put.o:	$(DMDINC)/layer.h # nested include from mpx.h
put.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c put.c

rdwr.o:	rdwr.c
rdwr.o:	$(DMDINC)/dmd.h
rdwr.o:	$(DMDINC)/dmdio.h
rdwr.o:	$(DMDINC)/dmdproc.h # nested include from mpx.h
rdwr.o:	$(DMDINC)/layer.h # nested include from mpx.h
rdwr.o:	$(DMDINC)/mpx.h # nested include from dmd.h
	$(MCC) $(MCFLAGS) -c rdwr.c

smprintf.o:	smprintf.c
smprintf.o:	$(DMDINC)/dmdio.h
	$(MCC) $(MCFLAGS) -c smprintf.c

sprintf.o:	sprintf.c
sprintf.o:	$(DMDINC)/dmdio.h
	$(MCC) $(MCFLAGS) -c sprintf.c

