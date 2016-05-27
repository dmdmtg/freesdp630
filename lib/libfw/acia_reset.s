#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)acia_reset.s	1.1.1.2	(5/12/87)

	text
	def	acia_reset;	val	acia_reset;	scl	2;	type	044;	endef

	global	acia_reset
acia_reset:
	mov.l	_addrSys,%a0
	mov.l	4*157(%a0),%a0
	jmp	(%a0)
	def	acia_reset;	val	~;	scl	-1;	endef
