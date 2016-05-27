#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)proclayer.s	1.1.1.3	(5/12/87)

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
	def	Bitmap;	scl	10;	type	010;	size	18;	endef
	def	base;	val	0;	scl	8;	type	024;	endef
	def	width;	val	4;	scl	8;	type	016;	endef
	def	rect;	val	6;	scl	8;	type	010;	tag	Rectangle;	size	8;	endef
	def	_null;	val	14;	scl	8;	type	022;	endef
	def	~eos;	val	18;	scl	102;	tag	Bitmap;	size	18;	endef
	data	1
	def	Bitmap;	scl	13;	type	010;	tag	Bitmap;	size	18;	endef
	text
	def	Obscured;	scl	10;	type	010;	size	24;	endef
	def	rect;	val	0;	scl	8;	type	010;	tag	Rectangle;	size	8;	endef
	def	bmap;	val	8;	scl	8;	type	030;	tag	Bitmap;	size	18;	endef
	def	lobs;	val	12;	scl	8;	type	030;	endef
	def	next;	val	16;	scl	8;	type	030;	tag	Obscured;	size	24;	endef
	def	prev;	val	20;	scl	8;	type	030;	tag	Obscured;	size	24;	endef
	def	~eos;	val	24;	scl	102;	tag	Obscured;	size	24;	endef
	data	1
	def	Obscured;	scl	13;	type	010;	tag	Obscured;	size	24;	endef
	text
	def	Layer;	scl	10;	type	010;	size	30;	endef
	def	base;	val	0;	scl	8;	type	024;	endef
	def	width;	val	4;	scl	8;	type	016;	endef
	def	rect;	val	6;	scl	8;	type	010;	tag	Rectangle;	size	8;	endef
	def	obs;	val	14;	scl	8;	type	030;	tag	Obscured;	size	24;	endef
	def	front;	val	18;	scl	8;	type	030;	tag	Layer;	size	30;	endef
	def	back;	val	22;	scl	8;	type	030;	tag	Layer;	size	30;	endef
	def	lmisc;	val	26;	scl	8;	type	05;	endef
	def	~eos;	val	30;	scl	102;	tag	Layer;	size	30;	endef
	data	1
	def	Layer;	scl	13;	type	010;	tag	Layer;	size	30;	endef
	text
	def	proclayer;	val	proclayer;	scl	2;	type	0150;	tag	Layer;	size	30;	endef

	global	proclayer
proclayer:
	mov.l	_addrSys,%a0
	mov.l	4*573(%a0),%a0
	jmp	(%a0)
	def	proclayer;	val	~;	scl	-1;	endef
