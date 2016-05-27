#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)move.s	1.1.1.4	(5/12/87)

	text
	def	_move;	val	_move;	scl	2;	type	044;	endef

	global	_move
_move:
	mov.l	_addrSys,%a0
	mov.l	4*481(%a0),%a0
	jmp	(%a0)
	def	_move;	val	~;	scl	-1;	endef
