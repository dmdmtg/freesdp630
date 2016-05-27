#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)rcvnchars.s	1.1.1.2	(5/12/87)

	text
	def	rcvnchars;	val	rcvnchars;	scl	2;	type	044;	endef

	global	rcvnchars
rcvnchars:
	mov.l	_addrSys,%a0
	mov.l	4*108(%a0),%a0
	jmp	(%a0)
	def	rcvnchars;	val	~;	scl	-1;	endef
