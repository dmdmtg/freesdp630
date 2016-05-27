#ident	"@(#)libm:makefile	2.3.2.1"
#
#	MC68000 MATH LIBRARY MAKEFILE
#
# makefile for libm
#
# Note that the object list given in FILES is in the order in which the files
# should be added to the archive when it is created.  If the files are not
# ordered correctly, linking of libm fails on the pdp11 and is slowed down
# on other machines.

include ../../stand.defs

### Specific Defines ###
DMDSUBINC=$(DMDINC)/dmd
VARIANT =
LIBNAME = lib$(VARIANT)m.a
FILES = asin.o atan.o erf.o fabs.o floor.o fmod.o gamma.o hypot.o jn.o \
	j0.o j1.o pow.o log.o sin.o sinh.o sqrt.o tan.o tanh.o exp.o \
	matherr.o

build:	$(LIBNAME) 

# Note:  The funny define of write is designed to cause the
#	compiler to generate null code where error messages
#	are usually produced.  This is because the simplest
#	68000 run-time environments would not have a write
#	system call available.  For UNIX target systems the -D
#	should be removed.

$(LIBNAME): $(FILES)
	$(MCC) -c $(MCFLAGS) -Dwrite= $(?:.o=.c)
	$(MAR) r $(LIBNAME) $?
#	rm $?

$(FILES): $(DMDSUBINC)/math.h $(DMDSUBINC)/values.h $(DMDSUBINC)/errno.h

.c.a:;

.c.o:
	$(MCC) $(MCFLAGS) -c $<

install:	libm.a
		-rm -f $(DMDLIB)/libm.a
		cp libm.a $(DMDLIB)
		chmod $(MODE644) $(DMDLIB)/libm.a
		
#--------------------------

stripit:	strip
strip:		FRC
		-rm -f $(DMDLIB)/libm.a

#--------------------------

clean:
	-rm -f *.o

clobber:	clean
	-rm -f $(LIBNAME) # libp.$(LIBNAME)

#--------------------------

FRC:
