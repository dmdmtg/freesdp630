#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)rcvchar.s	1.1.1.2	(5/12/87)

	text
	def	rcvchar;	val	rcvchar;	scl	2;	type	044;	endef

	global	rcvchar
rcvchar:
	mov.l	_addrSys,%a0
	mov.l	4*107(%a0),%a0
	jmp	(%a0)
	def	rcvchar;	val	~;	scl	-1;	endef
