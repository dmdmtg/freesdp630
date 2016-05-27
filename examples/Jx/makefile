#
#
include ../../stand.defs

STD=	jxmouse.c world.h

all:

build:	install

install:
	-mkdir $(DMD)/examples/Jx
	-chmod $(MODE755) $(DMD)/examples/Jx
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Jx/$$i" || \
		    cp $$i $(DMD)/examples/Jx/$$i; \
		chmod $(MODE644) $(DMD)/examples/Jx/$$i; \
	done
clean:
