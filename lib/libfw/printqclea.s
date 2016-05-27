#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)printqclea.s	1.1.1.3	(5/12/87)

	text
	def	printqclear;	val	printqclear;	scl	2;	type	040;	endef

	global	printqclear
printqclear:
	mov.l	_addrSys,%a0
	mov.l	4*827(%a0),%a0
	jmp	(%a0)
	def	printqclear;	val	~;	scl	-1;	endef
