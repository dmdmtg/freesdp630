#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)local.s	1.1.1.2	(5/12/87)

	text
	def	local;	val	local;	scl	2;	type	044;	endef

	global	local
local:
	mov.l	_addrSys,%a0
	mov.l	4*34(%a0),%a0
	jmp	(%a0)
	def	local;	val	~;	scl	-1;	endef
