#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)realalloc.s	1.1.1.2	(5/12/87)

	text
	def	realalloc;	val	realalloc;	scl	2;	type	0142;	endef

	global	realalloc
realalloc:
	mov.l	_addrSys,%a0
	mov.l	4*605(%a0),%a0
	jmp	(%a0)
	def	realalloc;	val	~;	scl	-1;	endef
