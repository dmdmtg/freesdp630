#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)eqpt.s	1.1.1.2	(5/12/87)

	text
	def	eqpt;	val	eqpt;	scl	2;	type	044;	endef

	global	eqpt
eqpt:
	mov.l	_addrSys,%a0
	mov.l	4*277(%a0),%a0
	jmp	(%a0)
	def	eqpt;	val	~;	scl	-1;	endef
