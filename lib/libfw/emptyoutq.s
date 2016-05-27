#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)emptyoutq.s	1.1.1.4	(6/3/87)

	text
	def	printqempty;	val	printqempty;	scl	2;	type	044;	endef

	global	printqempty
printqempty:
	mov.l	_addrSys,%a0
	mov.l	4*327(%a0),%a0
	jmp	(%a0)
	def	printqempty;	val	~;	scl	-1;	endef
