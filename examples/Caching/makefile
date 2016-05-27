#
#
include ../../stand.defs

STD=	cache1.c cache10.c cache11.c cache12.c cache13.c cache14.c cache15.c \
	cache16.c cache17.c cache2.c cache3.c cache4.c cache5.c cache6.c \
	cache7.c cache8.c cache9.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/Caching
	-chmod $(MODE755) $(DMD)/examples/Caching
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/Caching/$$i" || \
		    cp $$i $(DMD)/examples/Caching/$$i; \
		chmod $(MODE644) $(DMD)/examples/Caching/$$i; \
	done
clean:
