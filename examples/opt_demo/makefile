#
#
include ../../stand.defs

STD=	opt_demo.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/opt_demo
	-chmod $(MODE755) $(DMD)/examples/opt_demo
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/opt_demo/$$i" || \
		    cp $$i $(DMD)/examples/opt_demo/$$i; \
		chmod $(MODE644) $(DMD)/examples/opt_demo/$$i; \
	done
clean:
