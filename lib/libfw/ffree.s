#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)ffree.s	1.1.1.2	(5/12/87)

	text
	def	ffree;	val	ffree;	scl	2;	type	040;	endef

	global	ffree
ffree:
	mov.l	_addrSys,%a0
	mov.l	4*293(%a0),%a0
	jmp	(%a0)
	def	ffree;	val	~;	scl	-1;	endef
