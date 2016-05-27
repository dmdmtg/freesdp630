#ident	"@(#)libc-mc68:makefile	2.10"
#
#	MC68000 C LIBRARY MAKEFILE
#
#
include ../../stand.defs

build:		libc.a

#-------------------------

libc.a:
		cd gen; $(MAKE) $(MAKE_ARGS)  install
		cd crt; $(MAKE) $(MAKE_ARGS)  install
		$(MAR) r libc.a `$(MLORDER) *.o | tsort`

#-------------------------

install:	libc.a
		-rm -f $(DMDLIB)/libc.a
		cp libc.a $(DMDLIB)
		chmod $(MODE644) $(DMDLIB)/libc.a
		
#--------------------------

clean:		clobber

stripit:	strip
strip:		FRC
		-rm -f $(DMDLIB)/libc.a

#--------------------------

clobber:
		cd gen; $(MAKE) $(MAKE_ARGS)  clobber
		cd crt; $(MAKE) $(MAKE_ARGS)  clobber
		rm -f libc.a

#--------------------------

lint:
	cd gen; $(MAKE) $(MAKE_ARGS)  lint
	cd crt; $(MAKE) $(MAKE_ARGS)  lint

#--------------------------
FRC:
