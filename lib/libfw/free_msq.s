#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)free_msq.s	1.1.1.2	(5/12/87)

	text
	def	free_msq;	val	free_msq;	scl	2;	type	040;	endef

	global	free_msq
free_msq:
	mov.l	_addrSys,%a0
	mov.l	4*312(%a0),%a0
	jmp	(%a0)
	def	free_msq;	val	~;	scl	-1;	endef
