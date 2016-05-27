#       Copyright (c) 1989 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# This is the Programming Environment Identification Number (PEID)
# for firmware functions that are supported by 630 MTG terminals
# running firmware version 8;8;7 ROMS or later.
#
# The PEID scheme is documented in the manual pages dmdld(1)
# and dmdcc(1) in the 630 MTG Software Reference Manual.

# %W   (%G)

# The PEID for 8;8;7 ROMS or later is the long word 0x3.

long 0x3	# This is MC68000's byte ordering.
		#
		# dmdld, when read this number from a 3B2 or
		# a machine with similar word ordering will
		# see as a 0x3.
		#
		# dmdld, when read this number from a VAX or
		# 6386 WSG or a machine with similar word 
		# ordering will see as 0x30000. There is a
		# bug in older versions of dmdld that do not
		# swap the word. The version released with the
		# NDP does.
	

