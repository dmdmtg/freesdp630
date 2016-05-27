#
#
include ../../stand.defs

STD=	kbd1.c kbd2.c kbd3.c keyrects.h keys.h positions.h

all:

build:	install

install:
	-mkdir $(DMD)/examples/Keyboard
	-chmod $(MODE755) $(DMD)/examples/Keyboard
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Keyboard/$$i" || \
		    cp $$i $(DMD)/examples/Keyboard/$$i; \
		chmod $(MODE644) $(DMD)/examples/Keyboard/$$i; \
	done
clean:
