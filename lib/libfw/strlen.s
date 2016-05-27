#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)strlen.s	1.1.1.2	(5/12/87)

	text
	def	strlen;	val	strlen;	scl	2;	type	044;	endef

	global	strlen
strlen:
	mov.l	_addrSys,%a0
	mov.l	4*713(%a0),%a0
	jmp	(%a0)
	def	strlen;	val	~;	scl	-1;	endef
