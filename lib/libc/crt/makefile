#ident	"@(#)libc-mc68:crt/makefile	2.7"
#
#	MC68000 C RUNTIME MAKEFILE
#
#
include ../../../stand.defs

LINT=lint
AFLAGS=r
LFLAGS=-p
LDFLAGS=

# C language integer size:  INT16BIT or INT32BIT
INTSIZE=INT16BIT

# frexp, ldexp, and modf don't really belong in this directory
# (they should be in gen), but since they use fp.h and the sed
# script, it's easier to have them here.

FPPO=addmag.o fladd.o flcmp.o fldiv.o flmul.o flneg.o \
	flsub.o fltst.o frexp.o ftol.o itof.o ldexp.o ltof.o \
	modf.o submag.o uitof.o ultof.o
FPPC=addmag.c fladd.c flcmp.c fldiv.c flmul.c flneg.c \
	flsub.c fltst.c frexp.c ftol.c itof.c ldexp.c ltof.c \
	modf.c submag.c uitof.c ultof.c

OTHERO=cerror.o chrtab.o index.o ldiv.o lmul.o rindex.o
OTHERC=chrtab.c index.c rindex.c

OFILES=$(FPPO) $(OTHERO)
CFILES=$(FPPC) $(OTHERC)

build:		$(OFILES)

$(FPPO):	fp.h

#-------------------------

.c.o:
# This procedure is overkill, but harmless, for the non-FPP routines
	$(MCC) $(MCFLAGS) -S $<
	sed -f massage.sed <$*.s >temp.$$$$; mv temp.$$$$ $*.s
	$(MCC) $(MCFLAGS) -c $*.s
	rm $*.s

.s.o:
	$(MAS) $<

cerror.o:	cerror.s
		$(MCC) -c cerror.s

cerror.s:	cerror.s.16 cerror.s.32
	-@if [ "$(INTSIZE)" = INT32BIT ];then	cp cerror.s.32 cerror.s; \
	else					cp cerror.s.16 cerror.s; fi

#-------------------------

install:	$(OFILES)
		-ln $(OFILES) ..

#--------------------------

clean:
	-rm -f $(OFILES) temp.*
	cd ..; rm -f $(OFILES)

#--------------------------

clobber:	clean
	-rm -f cerror.s

#--------------------------

lint:	$(CFILES) fp.h
	$(LINT) $(LFLAGS) $(CFILES) >lint.out

