include ../../stand.defs

MODE644=644
MDIR=	$(DMD)/man/man5
CATMDIR=$(DMD)/catman/DMD/g5
SRCS=	ascii.5 math.5 values.5

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

