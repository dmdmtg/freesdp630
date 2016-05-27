#       Copyright (c) 1988 AT&T
#       All Rights Reserved

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#       The copyright notice above does not evidence any 
#       actual or intended publication of such source code.

# %W (%G)

	text
	def	t_getinfo;	val	t_getinfo;	scl	2;	type	044;	endef

	global	t_getinfo
t_getinfo:
	mov.l	_addrSys,%a0
	mov.l	4*924(%a0),%a0
	jmp	(%a0)
	def	t_getinfo;	val	~;	scl	-1;	endef
