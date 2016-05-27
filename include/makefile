#
# Doing a make install builds $(DMD)/include
#
#
include ../stand.defs

# these were originally in the network development package
NDP=	dmderrno.h dmdfcntl.h dmdpoll.h dmdslanusr.h dmdti.h dmdtiuser.h \
	nauinfo.h

STD=	5620.h dmd.h dmdio.h dmdproc.h extern.h font.h global.h\
	kbd_proc.h key122tab.h key98tab.h keycodes.h label.h layer.h\
	menu.h message.h mpx.h msgs.h object.h quiet.h sccsid.h\
	setup.h $(NDP)

# The following include files were historically installed in $(DMD)/include/ccs
#  but they don't have anything to do with the ccs (code compilation system).
#  They are all files that are dmd-specific but there are Unix header files by
#  the same name.  Some Unix programs include $(DMD)/include and /ccs so they
#  conflict with the Unix headers.  Instead install them in a "dmd" subdirectory
#  and modify dmdcc to automatically add that directory with a "-I" option.
OTHERS=	ctype.h errno.h math.h memory.h nan.h search.h signal.h string.h \
	values.h
all:

lint:

build:	install

strip:	FRC
	-rm -rf $(DMD)/include

install:
	-mkdir $(DMD)/include
	-chmod $(MODE755) $(DMD)/include
	-for i in ${STD}; do \
		cmp -s $$i $(DMD)/include/$$i || \
		    cp $$i $(DMD)/include/$$i; \
		chmod $(MODE644) $(DMD)/include/$$i; \
	done
	-mkdir $(DMD)/include/dmd
	-chmod $(MODE755) $(DMD)/include/dmd
	-for i in ${OTHERS}; do \
		cmp -s dmd/$$i $(DMD)/include/dmd/$$i || \
		    cp dmd/$$i $(DMD)/include/dmd/$$i; \
		chmod $(MODE644) $(DMD)/include/dmd/$$i; \
	done
clean:
clobber:
FRC:
