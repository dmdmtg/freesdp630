#ident	"@(#)sgs-inc:makefile	1.5.3.1"
#
#	MC68000 COMMAND MAKEFILE
#
DMD=/usr/local/630
MODE644=644
MODE755=755
INCPAR=$(DMD)/include
INCDIR=$(DMD)/include/ccs

M68INC=

COMINC=../common/aouthdr.h ../common/ar.h ../common/filehdr.h \
	../common/ldfcn.h ../common/linenum.h ../common/reloc.h \
	../common/scnhdr.h ../common/sgsmacros.h \
	../common/storclass.h ../common/syms.h

CCSINC=paths.h sgs.h tv.h ../common/patch.h ../common/bool.h

build:
all:
stripit:
lint:

install:
	-mkdir $(INCPAR)
	-chmod $(MODE755) $(INCPAR)
	-mkdir $(INCDIR)
	-chmod $(MODE755) $(INCDIR)
	cp $(M68INC) $(COMINC) $(INCDIR)
	(cd $(INCDIR);\
	chmod $(MODE644) `echo $(COMINC) | sed -e 's+../common/++g'` $(M68INC) )
clean:
clobber:
