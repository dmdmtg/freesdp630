include ../../stand.defs

MDIR=	$(DMD)/man/man4n
CATMDIR=$(DMD)/catman/DMD/g4n
MODE644=644

SRCS=	starlan.4n starlandg.4n

all:

clean:
clobber:

install: all
	-mkdir $(MDIR)
	cp $(SRCS) $(MDIR)
	cd $(MDIR);chmod $(MODE644) $(SRCS)

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

