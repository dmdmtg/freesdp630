#
#
include ../stand.defs

TERMTYPES=630 730 730+

all:

lint:

strip:

build:	install

install:
	-mkdir $(DMD)/terminfo
	-chmod $(MODE755) $(DMD)/terminfo
	TERMINFO=$(DMD)/terminfo; export TERMINFO; \
	for t in $(TERMTYPES); do \
	    tic terminfo.$$t 2>/dev/null || true; \
	    cp termcap.$$t $(DMD)/terminfo; \
	    chmod $(MODE644) $(DMD)/terminfo/termcap.$$t; \
	done
clean:
clobber:

FRC:
