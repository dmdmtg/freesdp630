#
#
include ../../stand.defs

STD=	TrackMouse.c mouse.c type.c vsterm1.c world.h star.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/Resources
	-chmod $(MODE755) $(DMD)/examples/Resources
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Resources/$$i" || \
		    cp $$i $(DMD)/examples/Resources/$$i; \
		chmod $(MODE644) $(DMD)/examples/Resources/$$i; \
	done
clean:
