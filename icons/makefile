#
#
include ../stand.defs

all:

lint:

build:	install

strip:	FRC
	-rm -rf $(DMD)/icons

install:
	-mkdir $(DMD)/icons
	-chmod $(MODE755) $(DMD)/icons
	cd 16x16; make $(MAKE_ARGS) install
	cd face48; make $(MAKE_ARGS) install
	cd large; make $(MAKE_ARGS) install
	cd texture; make $(MAKE_ARGS) install
clean:
clobber:
