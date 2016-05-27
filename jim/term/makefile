#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)makefile	1.1.1.4	(5/8/87)

include ../../stand.defs

F=../frame
OBJ=main.o frame.o menu.o msgs.o string.o $F/frame.a

PRODUCTS=jim.m
INSTALL=$(DMDLIB)/jim.m
CLEAN=$(OBJ)
CLOBBER=$(PRODUCTS)

include ../../stand.targ

$(DMDLIB)/jim.m:	jim.m
	cp jim.m $(DMDLIB)/jim.m
	$(MSTRIP) -m $(DMDLIB)/jim.m
	chmod $(MODE644) $(DMDLIB)/jim.m

jim.m:	$(OBJ)
jim.m:	$F/frame.a
	$(MCC) -o jim.m $(OBJ)

main.o:	main.c
main.o:	$F/frame.h
main.o:	$(DMDINC)/dmd.h
main.o:	$(DMDINC)/object.h
main.o:	$(DMDINC)/mpx.h		# nested in dmd.h
main.o:	$(DMDINC)/layer.h	# nested in mpx.h
main.o:	$(DMDINC)/font.h	# nested in ../frame/frame.h
main.o:	$(DMDINC)/dmdproc.h
main.o:	jim.h
main.o: menu.h
main.o: msgs.h
	$(MCC) $(MCFLAGS) -c main.c

frame.o:	frame.c
frame.o:	$F/frame.h
frame.o:	$(DMDINC)/dmd.h
frame.o:	$(DMDINC)/mpx.h		# nested in dmd.h
frame.o:	$(DMDINC)/layer.h	# nested in mpx.h
frame.o:	$(DMDINC)/font.h	# nested in ../frame/frame.h
frame.o:	$(DMDINC)/dmdproc.h
frame.o:	jim.h
frame.o:	menu.h
frame.o:	msgs.h
	$(MCC) $(MCFLAGS) -c frame.c

menu.o:	menu.c
menu.o:	$F/frame.h
menu.o:	$(DMDINC)/dmd.h
menu.o:	$(DMDINC)/mpx.h		# nested in dmd.h
menu.o:	$(DMDINC)/layer.h	# nested in mpx.h
menu.o:	$(DMDINC)/font.h	# nested in ../frame/frame.h
menu.o:	$(DMDINC)/dmdproc.h
menu.o:	jim.h
menu.o:	menu.h
menu.o:	msgs.h
	$(MCC) $(MCFLAGS) -c menu.c

msgs.o:	msgs.c
msgs.o:	msgs.h
msgs.o:	menu.h
msgs.o:	$F/frame.h
msgs.o:	jim.h
msgs.o:	$(DMDINC)/dmd.h
msgs.o:	$(DMDINC)/mpx.h		# nested in dmd.h
msgs.o:	$(DMDINC)/layer.h	# nested in mpx.h
msgs.o:	$(DMDINC)/font.h	# nested in ../frame/frame.h
msgs.o:	$(DMDINC)/dmdproc.h
	$(MCC) $(MCFLAGS) -c msgs.c

string.o:	string.c
string.o:	$F/frame.h
string.o:	$(DMDINC)/dmd.h
string.o:	$(DMDINC)/mpx.h		# nested in dmd.h
string.o:	$(DMDINC)/font.h	# nested in ../frame/frame.h
string.o:	$(DMDINC)/layer.h	# nested in mpx.h
string.o:	$(DMDINC)/dmdproc.h
	$(MCC) $(MCFLAGS) -c string.c

jim.h:	$F/frame.h
jim.h:	menu.h
jim.h:	msgs.h
