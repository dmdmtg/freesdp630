#       Copyright (c) 1988 AT&T
#       All Rights Reserved

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#       The copyright notice above does not evidence any 
#       actual or intended publication of such source code.

# %W (%G)

	text
	def	t_alloc;	val	t_alloc;	scl	2;	type	0142;	endef

	global	t_alloc
t_alloc:
	mov.l	_addrSys,%a0
	mov.l	4*917(%a0),%a0
	jmp	(%a0)
	def	t_alloc;	val	~;	scl	-1;	endef
