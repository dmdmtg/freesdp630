#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)Cursallow.s	1.1.1.2	(5/11/87)

	text
	def	Cursallow;	val	Cursallow;	scl	2;	type	040;	endef

	global	Cursallow
Cursallow:
	mov.l	_addrSys,%a0
	mov.l	4*225(%a0),%a0
	jmp	(%a0)
	def	Cursallow;	val	~;	scl	-1;	endef
