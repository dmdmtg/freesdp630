#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)sendchar.s	1.1.1.2	(5/12/87)

	text
	def	sendchar;	val	sendchar;	scl	2;	type	044;	endef

	global	sendchar
sendchar:
	mov.l	_addrSys,%a0
	mov.l	4*113(%a0),%a0
	jmp	(%a0)
	def	sendchar;	val	~;	scl	-1;	endef
