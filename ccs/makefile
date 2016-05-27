# Invoke the standard makefile on only dmdcc and inc; the rest of the
#    tools have been removed because they can't be freely distributed.
#
OBJECT=dmdcc inc

include ../stand.defs

build install clean clobber:
	make -f makefile.std $(MAKE_ARGS) OBJECT="$(OBJECT)" $@
