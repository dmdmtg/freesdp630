#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)outqavail.s	1.1.1.4	(6/3/87)

	text
	def	printqspace;	val	printqspace;	scl	2;	type	044;	endef

	global	printqspace
printqspace:
	mov.l	_addrSys,%a0
	mov.l	4*416(%a0),%a0
	jmp	(%a0)
	def	printqspace;	val	~;	scl	-1;	endef
