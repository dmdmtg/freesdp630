include ../../stand.defs

MDIR=	$(DMD)/man/man1
CATMDIR=$(DMD)/catman/DMD/g1
SRCS=	dmdcat.1 dmdcc.1 dmddemo.1 dmdld.1 dmdmemory.1 \
	dmdpi.1 dmdversion.1 icon.1 jim.1 jx.1 loadfont.1 mc68ar.1 \
	mc68as.1 mc68conv.1 mc68cpp.1 mc68cprs.1 mc68dis.1 mc68dump.1 mc68ld.1 \
	mc68list.1 mc68lorder.1 mc68nm.1 mc68size.1 mc68strip.1

all:

clean:
clobber:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	chmod $(MODE644) $(MDIR)/*

catman: all
	-mkdir $(CATMDIR)
	-chmod $(MODE755) $(CATMDIR)
	for s in $(SRCS); do \
	    base=`echo $$s|sed "s/\(.*\)\..*/\1/"`; \
	    if [ ! -z "`find $(CATMDIR)/$$base.z -newer $$s -print 2>/dev/null`" ]; then continue; fi; \
	    rm -f $(CATMDIR)/$$base*; \
	    nroff -man $$s > $(CATMDIR)/$$base; \
	    pack -f $(CATMDIR)/$$base; \
	    chmod $(MODE644) $(CATMDIR)/$$base*; \
	done

