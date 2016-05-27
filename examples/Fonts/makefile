#
#
include ../../stand.defs

STD=	font1.c font2.c font3.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/Fonts
	-chmod $(MODE755) $(DMD)/examples/Fonts
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Fonts/$$i" || \
		    cp $$i $(DMD)/examples/Fonts/$$i; \
		chmod $(MODE644) $(DMD)/examples/Fonts/$$i; \
	done
clean:
