include ../../stand.defs

# these are not necessary for newer pseudo-tty layers but install them
# for compatibility with older layers

SRCS= lsys.8\;0\;5 lsys.8\;0\;7 lsys.8\;4\;5 lsys.8\;4\;6 lsys.8\;6\;6 \
	lsys.8\;7\;5 lsys.8\;8\;5 lsys.8\;8\;6 lsys.8\;8\;7 \
	lsys.8\;8\;8 lsys.8\;8\;9

all:

clean:
clobber:

install: all
	-mkdir $(DMD)/lib $(DMD)/lib/layersys
	for i in $(SRCS); do \
	    touch $(DMD)/lib/layersys/$$i; \
	    chmod $(MODE644) $(DMD)/lib/layersys/$$i; \
	done
