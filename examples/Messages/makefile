#
#
include ../../stand.defs

STD=	messages1.c messages2.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/Messages
	-chmod $(MODE755) $(DMD)/examples/Messages
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Messages/$$i" || \
		    cp $$i $(DMD)/examples/Messages/$$i; \
		chmod $(MODE644) $(DMD)/examples/Messages/$$i; \
	done
clean:
