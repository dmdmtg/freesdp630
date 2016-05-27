#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)itoc.s	1.1.1.2	(5/12/87)

	text
	def	itoc;	val	itoc;	scl	2;	type	0142;	endef

	global	itoc
itoc:
	mov.l	_addrSys,%a0
	mov.l	4*393(%a0),%a0
	jmp	(%a0)
	def	itoc;	val	~;	scl	-1;	endef
