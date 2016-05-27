#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)newrect.s	1.1.1.2	(5/12/87)

	text
	def	Point;	scl	10;	type	010;	size	4;	endef
	def	x;	val	0;	scl	8;	type	04;	endef
	def	y;	val	2;	scl	8;	type	04;	endef
	def	~eos;	val	4;	scl	102;	tag	Point;	size	4;	endef
	data	1
	def	Point;	scl	13;	type	010;	tag	Point;	size	4;	endef
	text
	def	Rectangle;	scl	10;	type	010;	size	8;	endef
	def	origin;	val	0;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	corner;	val	4;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	~eos;	val	8;	scl	102;	tag	Rectangle;	size	8;	endef
	data	1
	def	Rectangle;	scl	13;	type	010;	tag	Rectangle;	size	8;	endef
	text
	def	newrect;	val	newrect;	scl	2;	type	050;	tag	Rectangle;	size	8;	endef

	global	newrect
newrect:
	mov.l	_addrSys,%a0
	mov.l	4*497(%a0),%a0
	jmp	(%a0)
	def	newrect;	val	~;	scl	-1;	endef
