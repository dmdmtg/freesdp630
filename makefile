# 
#									
#	Copyright (c) 1987,1988,1989,1990,1991,1992,1993   AT&T		
#			All Rights Reserved				
#									
#	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		
#	    The copyright notice above does not evidence any		
#	   actual or intended publication of such source code.		
#									

# 630 software development package master makefile

include stand.defs

#
# EXTRACFLAGS is for any extra cc options for compiling and linking for
#  a particular unix platform
#
EXTRACFLAGS="-O -w"
# Use the following for Solaris
# EXTRACFLAGS=-O -DUSE_SYSVR4LIKE -lsocket -lnsl
# Use the following for HP-PA
# EXTRACFLAGS=-O -D_CLASSIC_TYPES
#

#

### Specific Defines ###

PRODUCTS=	include ccs lib demo dmdcat dmdld dmdman dmdmemory dmdversion \
		examples icon icons jim jx loadfont man termfonts \
		terminfo ucache wtinit 32ld

### Standard Targets ###

default:	build

all:		$(PRODUCTS)

build:	mkdirs
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; \
		    case $$d in \
			include|ccs|lib) \
			    make $(MAKE_ARGS) install;; \
			*)  make $(MAKE_ARGS) ;; \
		    esac; \
		done

install:	mkdirs 
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) install; \
		done

mkdirs:
		-mkdir $(DMD)
		-chmod $(MODE755) $(DMD)
		-mkdir $(DMDBIN)
		-chmod $(MODE755) $(DMDBIN)
		-mkdir $(DMDLIB)
		-chmod $(MODE755) $(DMDLIB)
		-mkdir $(DMDLIB)/demolib $(DMDLIB)/demobin
		-chmod $(MODE755) $(DMDLIB)/demolib $(DMDLIB)/demobin
		-mkdir $(DMDINC)
		-chmod $(MODE755) $(DMDINC)
		-mkdir $(DMDINC)/ccs
		-chmod $(MODE755) $(DMDINC)/ccs
		-mkdir $(DMDINC)/dmd
		-chmod $(MODE755) $(DMDINC)/dmd

$(PRODUCTS):	FRC
		cd $@; make $(MAKE_ARGS)

clobber:
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) clobber; \
		done
clean:
		@set -x; p=`pwd`; for d in $(PRODUCTS); do \
		    cd $$p/$$d; make $(MAKE_ARGS) clean; \
		done

### Additional Dependencies ###
FRC:
