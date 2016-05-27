#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)labelicon.s	1.1.1.2	(5/12/87)

	text
	def	Labelicon;	val	Labelicon;	scl	2;	type	040;	endef

	global	Labelicon
Labelicon:
	mov.l	_addrSys,%a0
	mov.l	4*409(%a0),%a0
	jmp	(%a0)
	def	Labelicon;	val	~;	scl	-1;	endef
