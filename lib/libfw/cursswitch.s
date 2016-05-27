#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)cursswitch.s	1.1.1.2	(5/12/87)

	text
	def	Texture16;	scl	10;	type	010;	size	32;	endef
	def	bits;	val	0;	scl	8;	type	064;	dim	16;	size	32;	endef
	def	~eos;	val	32;	scl	102;	tag	Texture16;	size	32;	endef
	data	1
	def	Texture16;	scl	13;	type	010;	tag	Texture16;	size	32;	endef
	text
	def	cursswitch;	val	cursswitch;	scl	2;	type	0150;	tag	Texture16;	size	32;	endef

	global	cursswitch
cursswitch:
	mov.l	_addrSys,%a0
	mov.l	4*86(%a0),%a0
	jmp	(%a0)
	def	cursswitch;	val	~;	scl	-1;	endef
