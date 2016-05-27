#
#
include ../../stand.defs

STD=	HELLO.c arguments.c hello.c world.h

all:

build:	install

install:
	-mkdir $(DMD)/examples/GettingStarted
	-chmod $(MODE755) $(DMD)/examples/GettingStarted
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/GettingStarted/$$i" || \
		    cp $$i $(DMD)/examples/GettingStarted/$$i; \
		chmod $(MODE644) $(DMD)/examples/GettingStarted/$$i; \
	done
clean:
