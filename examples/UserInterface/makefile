#
#
include ../../stand.defs

STD=	Menu1.c Menu2.c MenuIcons.h Tmenu1.c Tmenu2.c Tmenu3.c Tmenu4.c \
	Tmenu5.c Tmenu6.c Tmenu7.c Tmenu8.c Tmenu9.c label1.c label2.c \
	label3.c msgbox1.c msgbox2.c

all:

build:	install

install:
	-mkdir $(DMD)/examples/UserInterface
	-chmod $(MODE755) $(DMD)/examples/UserInterface
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/examples/UserInterface/$$i" || \
		    cp $$i $(DMD)/examples/UserInterface/$$i; \
		chmod $(MODE644) $(DMD)/examples/UserInterface/$$i; \
	done
clean:
