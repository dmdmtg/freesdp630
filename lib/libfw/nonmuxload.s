#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)nonmuxload.s	1.1.1.2	(5/12/87)

	text
	def	nonmuxload;	val	nonmuxload;	scl	2;	type	044;	endef

	global	nonmuxload
nonmuxload:
	mov.l	_addrSys,%a0
	mov.l	4*504(%a0),%a0
	jmp	(%a0)
	def	nonmuxload;	val	~;	scl	-1;	endef
