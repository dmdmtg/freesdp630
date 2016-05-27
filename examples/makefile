#
#
include ../stand.defs

STD=	README clock.c

all:

lint:

build:	install
strip: FRC
	-rm -fr $(DMD)/examples

install:
	-mkdir $(DMD)/examples
	-chmod $(MODE755) $(DMD)/examples
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/$$i" || \
		    cp $$i $(DMD)/examples/$$i; \
		chmod $(MODE644) $(DMD)/examples/$$i; \
	done
	cd Caching; make $(MAKE_ARGS) install
	cd Fonts; make $(MAKE_ARGS) install
	cd GettingStarted; make $(MAKE_ARGS) install
	cd Graphics; make $(MAKE_ARGS) install
	cd Jx; make $(MAKE_ARGS) install
	cd Keyboard; make $(MAKE_ARGS) install
	cd Messages; make $(MAKE_ARGS) install
	cd Resources; make $(MAKE_ARGS) install
	cd UserInterface; make $(MAKE_ARGS) install
	cd opt_demo; make $(MAKE_ARGS) install
clean:
clobber:

FRC:
