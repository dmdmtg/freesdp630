
include ../stand.defs

### Specific Defines ###

CFLAGS=$(EXTRACFLAGS)

PRODUCTS= startup libc libm libfw libjx libj libnsl_s layersys

### Targets ###

all:		$(PRODUCTS)

build:		install

install:
		-mkdir $(DMDLIB)
		-chmod $(MODE755) $(DMDLIB)
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) install; \
		done

$(PRODUCTS):	FRC
		cd $@; make $(MAKE_ARGS)

clobber:	clean
clean:
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) clobber; \
		done

### Additional Dependencies ###
FRC:
