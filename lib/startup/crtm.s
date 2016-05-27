#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)crtm.s	1.1.1.5	(5/27/87)


# there is incompatibility between VAX's and 3B's naming convention
# the include file /usr/include/syms.h documents it as follows:
#
#	#if vax
#	#define _ETEXT  "_etext"
#	#define _EDATA  "_edata"
#	#define _END    "_end"
#	#else
#	#define _ETEXT  "etext"
#	#define _EDATA  "edata"
#	#define _END    "end"
#	#endif
#
# since this is written in assembler, the above pre-processing is
# done through m4(1) macro processor as follows:

syscmd(vax)
ifelse(sysval,0,`define(vax)')
ifdef(`vax',`define(_ETEXT,_etext)',`define(_ETEXT,etext)')
ifdef(`vax',`define(_EDATA,_edata)',`define(_EDATA,edata)')
ifdef(`vax',`define(_END,_end)',`define(_END,end)')


#
# symbolic debug info should be added for dmdebug (write in cc -g and massage
# output from the compiler)
#


data
def	_stack_size;	val	_stack_size;	scl	2;	type	05;	endef
_stack_size:	long 0

data 1
def	_addrSys;	val	_addrSys;	scl	2;	type	05;	endef
comm	_addrSys,4		# first var in common pool

# The sequence of these variables must be conserved.
# See _frdata() which assumes that _ptrData is the first
# element of the .bss section

lcomm	_ptrData,4		# pointer to the saved data section
lcomm	_sizData,4		# size of the saved data section
lcomm	_savBss,4		# saving flag for bss section 
lcomm	_fstbss, 4		# dummy:
				#   if a cached application needs
				#   its bss to be re-initialized
				#   to 0, _start will do it starting
				#   from _fstbss since the values
				#   of _savBss, _ptrData, _sizData must
				#   be kept unchanged from invocation
				#   to invocation

text
def	_start;	val	_start;	scl	2;	type	044;	endef
global _start
_start:

	# If _savBss is null (default), the application is running
	# the first time, so its .bss section should be cleared by the
	# system, so there is no need to clear it again here. In this
	# case, make _savBss to 1.
	#
	# If _savBss is 1, the application has been cached and runs for
	# the second time, so by default, we clear the .bss section so
	# variables in there that are updated by the previous run are
	# un-initialized again - this is a rule of the C language.
	#
	# If _savBss is 2, the application has been cached but it also
	# indicated that it wants the .bss saved from invocation to
	# invocation. In this case we do not clear the .bss section.

	tst.l	_savBss		# what value do I have?
	bne.b	Lcrt1		# a non-null value!

	mov.l	&1, _savBss	# mark the application has run once
	bra.b	Lcrt3		# do not do any .bss clean-up

Lcrt1:
	cmp.l	_savBss, &1	# what non-null value do I have?
	bne.b	Lcrt3		# a 2! do not do any .bss clean-up	

	mov.l	&_fstbss, %a0	# NOTE:
				#  _addrSys will be cleared because it
				#  is in the common pool, but it will
				#  be re-initialized shortly.
				#
				# BEWARE:
				#  if the application is shared
				#  and implements an interrupt for
				#  device driver, its _addrSys var 
				#  will be momentarily cleared
				#  which may cause bus error!
Lcrt0:	
	clr.w	(%a0)+		# clear the remaining bss section
	cmp.l	%a0, &_END	# compare with "end" of bss
	bcs.b	Lcrt0

Lcrt3:
	# Find the address of the vector table:
	# This address is found indirectly allowing the vector table to float.
	# The unused trap vector 12 following the hardware trapUT is used to
	# point to the "real" vector address. Since this trap vector is fixed
	# (unless we change CPU), applications do not have to be modified
	# if latter versions of fw have the vector table at the different address.
  	
	mov.l	176,%d0		# find the address of the vector table
	add.l	&6,%d0		#  (_addrSys). How this is done is documented
	mov.l	%d0,%a0		#  in $Fw/xvt.s in the firmware.
	mov.l	(%a0),_addrSys

	mov.l	_addrSys, %a0
	mov.l	4*92(%a0),%a0		# jsr Ujinit through Sys[92]
	jsr	(%a0)

	mov.l	_addrSys, %a0
	mov.l	-38*4(%a0), %a0		# a0 = P


	# Clear P->scurpt and P->curpt
	# These things should be handled by Ujinit but they are not.
	# Note: I have used a clear long instead of two clear word's
	# because the variables are at even boudaries in the struct P.

	clr.l	0xb6(%a0)		# clear P->scurpt
	clr.l	0xba(%a0)		# clear P->curpt

	# Initialize P->data and P->bss
	# For cached applications invoked from the menu, the fw's newmore
	# function should take of it but it doesn't (everybody can forget).
	# For cached applications invoked from the downloader, the fw's
	# load process has initialized the pointers so in this case, the
	# following code is redundant.

	mov.l	&_ETEXT, 0x8(%a0)	# P->data = &etext
	mov.l	&_ptrData, 0xc(%a0)	# P->data = &_ptrData
					# NOTE: _ptrData is the first .bss var
					# and using it is better than edata since
					# the .bss and .data sections may be
					# disjoint. I made an assumption that
					# the .text and .data sections are continous
					# which is mostly true (dunno of counter-examples).
	
	# If _ptrData is null (default), nothing should be done.
	# If _ptrData is not null, it should point to some memory that
	# has been allocated to preserve the original .data section.
	# This happens when the application has been cached without specifying
	# that the running .data section should be saved for the next
	# invocation. Therefore when the cached application is invoked again,
	# the original .data section, preserved by _prtData, is copied back
	# into P->data to re-initialize the .data section.

	tst.l	_ptrData	# is _ptrData null?
	beq.b	Lcrt4		# it is so get lost
	mov.l	_sizData,(%sp)	# _wordcpy (P->data, _ptrData, _sizData)
	mov.l	_ptrData,-(%sp)
	mov.l	0x8(%a0),-(%sp)
	jsr	_wordcpy
	add.l	&0x8,%sp	

Lcrt4:
	mov.l	46(%a0), -(%sp)		# push P->uargv
	mov.w	44(%a0), -(%sp)		# push P->uargc

	jsr	main

	mov.l	_addrSys, %a0
	mov.l	4*89(%a0),%a0		# jsr Uexit through Sys[89]
	jsr	(%a0)			# this looks like exit.s in libfw
def	_start;	val	~;	scl	-1;	endef


# _svcbss	Save the current .bss section
#
# Synopsis:
#	void _svcbss ()
#
# Description:
#	This function is called by the cache(3) function
#	to indicate that the .bss section should not be
#	cleared at subsequent invocations. Basically the
#	application to have the .bss section shared or
#	to have it accumulating data at each invocation.
#
def	_svcbss;	val	_svcbss;	scl	2;	type	040;	endef
global _svcbss
_svcbss:
	link	%fp,&-0x4
	mov.l	&2,_savBss	# see _start
	unlk	%fp
	rts
def	_svcbss;	val	~;	scl	-1;	endef


# _svodata	Save the original .data section
#
# Synopsis:
#	void _svodata (p1)
#	int *p1;
#
# Description:
#	This function is called by the cache(3) function to
#	have the present .data section to be copied into the
#	memory pointed to by p1.
#
#	If when the cache(3) is called, the .data section has
#	not been changed, what is preserved is the original .data
#	section. This function will set some flag, so when the
#	application is invoked in subsequent times, _start() will
#	know to re-initialize the .data section to original values
#

def	_svodata;	val	_svodata;	scl	2;	type	040;
endef
global _svodata
_svodata:
	link	%fp, &-0x4

	jsr	_szdsect		# find the size of .data section
	asr.l	&0x1,%d0		# size in words
	mov.l	%d0,_sizData		# save result in _sizData in crtm.o
	mov.l	%d0, (%sp)		# size of copy in stack		

	mov.l	_addrSys,%a0
	mov.l	-38*4(%a0),%a0		# a0 = P
	mov.l	0x8(%a0),-(%sp)		# P->data in stack

	mov.l	0x8(%fp),_ptrData	# save p1 in _prtData in crtm.o
	mov.l	0x8(%fp),-(%sp)		# p1 in stack

	jsr	_wordcpy		# _wordcpy (p1, P->data, _szdsect());
	add.l	&0x8,%sp		# recover stack

	unlk	%fp
	rts
def	_svodata;	val	~;	scl	-1;	endef

# _szdsect	Find the size in bytes of the .data section
#
# Synopsis:
#	long _szdsect();
#
# Description:
#	The size of the .data section can be bigger than 64K,
#	thus a long return is necessary
#

def	_szdsect;	val	_szdsect;	scl	2;	type	045;
endef
global _szdsect
_szdsect:
	link    %fp,&-0x4
	mov.l	_addrSys, %a0
	mov.l	-38*4(%a0), %a0		# a0 = P
	mov.l   &_EDATA,%d0
	sub.l   0x8(%a0),%d0		# edata - P->data
	unlk    %fp
	rts
def	_szdsect;	val	~;	scl	-1;	endef


# _wordcpy	Copy 16-bit words from one place to another
#
# Synopsis:
# 	void _memcpy (p1, p2, size)
# 	int *p1, *p2;
# 	long size;	/* size of words, NOT bytes! */
#
# Description:
#	This function differs from memcpy in libc or libfw is
#	many areas:
#	- it returns a void: %a0 does not have to be saved in
#	  the calling routine
#	- it uses pointers to int instead of char: this function
#	  is written to copy in and out the .data section which
#	  is always at word boudary
#	- it uses a long as the size of the memory: an integer
#	  only handles up to 64K of words and the .data section
#	  can be bigger.
#

def	_wordcpy;	val	_wordcpy;	scl	2;	type	040;	endef
global _wordcpy
_wordcpy:
	link    %fp,&-0x10
	movm.l  &0xc04,-0xc(%fp)	# save registers
	mov.l	0x8(%fp),%a2
	mov.l	0xc(%fp),%a3
	mov.l   0x10(%fp),%d2
	bra.b   Lmem1
Lmem0:
	mov.w   (%a3)+,(%a2)+
Lmem1:
	sub.l  	&0x1,%d2
	bge.b   Lmem0
	movm.l  -0xc(%fp),&0xc04
	unlk    %fp
	rts
def	_wordcpy;	val	~;	scl	-1;	endef

# _frdata	Free the memory used to save the original .data section
#
# Synopsis:
#	void _frdata (p)
#	char **p;
#
# Description:
#	p is the pointer to the .bss section of the application.
#	The _prtData pointer is the first element of it, and points
#	to the allocated memory to be freed.
#

def	_frdata;	val	_frdata;	scl	2;	type	040;
endef
global _frdata
_frdata:
	link	%fp,&-0x4
	mov.l	0x8(%fp),%a0
	mov.l	(%a0),(%sp)
	jsr	free		# free (*p);
	unlk	%fp
	rts
def	_frdata;	val	~;	scl	-1;	endef





