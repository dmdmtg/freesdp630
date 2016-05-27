#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)psendnchar.s	1.1.1.2	(5/12/87)

	text
	def	psendnchars;	val	psendnchars;	scl	2;	type	044;	endef

	global	psendnchars
psendnchars:
	mov.l	_addrSys,%a0
	mov.l	4*106(%a0),%a0
	jmp	(%a0)
	def	psendnchars;	val	~;	scl	-1;	endef
