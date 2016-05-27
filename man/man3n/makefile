include ../../stand.defs

MDIR=	$(DMD)/man/man3n
CATMDIR=$(DMD)/catman/DMD/g3n
MODE644=644

SRCS=	fcntl.3n flowcntl.3n intro.3n poll.3n t_accept.3n t_alloc.3n t_bind.3n \
	t_close.3n t_connect.3n t_error.3n t_free.3n t_getinfo.3n t_getstat.3n \
	t_listen.3n t_look.3n t_open.3n t_optmgmt.3n t_rcv.3n t_rcvcon.3n \
	t_rcvdis.3n t_rcvrel.3n t_rcvudat.3n t_rcvuder.3n t_snd.3n t_snddis.3n \
	t_sndrel.3n t_sndudat.3n t_sync.3n t_unbind.3n

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

