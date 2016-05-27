#       Copyright (c) 1988 AT&T
#       All Rights Reserved

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
#       The copyright notice above does not evidence any 
#       actual or intended publication of such source code.

# %W (%G)

	text
	def	t_unbind;	val	t_unbind;	scl	2;	type	044;	endef

	global	t_unbind
t_unbind:
	mov.l	_addrSys,%a0
	mov.l	4*941(%a0),%a0
	jmp	(%a0)
	def	t_unbind;	val	~;	scl	-1;	endef
