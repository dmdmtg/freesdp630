#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)set_msg_wa.s	1.1.1.3	(5/12/87)

	text
	def	set_msg_wake;	val	set_msg_wake;	scl	2;	type	040;	endef

	global	set_msg_wake
set_msg_wake:
	mov.l	_addrSys,%a0
	mov.l	4*830(%a0),%a0
	jmp	(%a0)
	def	set_msg_wake;	val	~;	scl	-1;	endef
