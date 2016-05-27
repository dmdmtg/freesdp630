#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)delete.s	1.1.1.4	(5/12/87)

	text
	def	_delete;	val	_delete;	scl	2;	type	044;	endef

	global	_delete
_delete:
	mov.l	_addrSys,%a0
	mov.l	4*241(%a0),%a0
	jmp	(%a0)
	def	_delete;	val	~;	scl	-1;	endef
