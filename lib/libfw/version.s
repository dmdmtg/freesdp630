#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)version.s	1.1.1.2	(5/12/87)

	text
	def	version;	val	version;	scl	2;	type	045;	endef

	global	version
version:
	mov.l	_addrSys,%a0
	mov.l	4*752(%a0),%a0
	jmp	(%a0)
	def	version;	val	~;	scl	-1;	endef
