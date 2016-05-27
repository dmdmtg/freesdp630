#
#
include ../stand.defs

STD=	10x21 11x17 12x18 12x18norm 12x25BOLD 12x25norm 12x25round 12x25thin \
	6x9 7x12 7x14thin 9x14 9x18 noseprint script twice_big

all:

lint:

build:	install

strip:	FRC
	-rm -rf $(DMD)/termfonts

install:
	-mkdir $(DMD)/termfonts
	-chmod $(MODE755) $(DMD)/termfonts
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/termfonts/$$i" || \
		    cp $$i $(DMD)/termfonts/$$i; \
		chmod $(MODE644) $(DMD)/termfonts/$$i; \
	done
clean:
clobber:

FRC:
