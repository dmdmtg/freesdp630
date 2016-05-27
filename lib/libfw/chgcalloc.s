#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)chgcalloc.s	1.1.1.3	(5/12/87)

	text
	def	chgcalloc;	val	chgcalloc;	scl	2;	type	0142;	endef

	global	chgcalloc
chgcalloc:
	mov.l	_addrSys,%a0
	mov.l	4*320(%a0),%a0
	jmp	(%a0)
	def	chgcalloc;	val	~;	scl	-1;	endef
