#
#
include ../../stand.defs

STD=	ICON.LST acsnet adm ap bart bbc bgs bin bwk chaos cow daemon dan \
	davef dectalk dmr ecc jdj jerq ken mailerdaemon mandrill ojb owl1 \
	owl2 owl3 rob root ross sys turkey unknown uucp

all:

build:	install

install:
	-mkdir $(DMD)/icons/face48
	-chmod $(MODE755) $(DMD)/icons/face48
	-for i in ${STD}; do \
		cmp -s "$$i" "$(DMD)/icons/face48/$$i" || \
		    cp $$i $(DMD)/icons/face48/$$i; \
		chmod $(MODE644) $(DMD)/icons/face48/$$i; \
	done
clean:
