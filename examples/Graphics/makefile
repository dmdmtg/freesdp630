#
#
include ../../stand.defs

STD=	rotate.h screen.c twist.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/Graphics
	-chmod $(MODE755) $(DMD)/examples/Graphics
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Graphics/$$i" || \
		    cp $$i $(DMD)/examples/Graphics/$$i; \
		chmod $(MODE644) $(DMD)/examples/Graphics/$$i; \
	done
clean:
