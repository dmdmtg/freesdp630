#       Copyright (c) 1987 AT&T   
#       All Rights Reserved       

#       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
#       The copyright notice above does not evidence any     
#       actual or intended publication of such source code.  

# @(#)upproc.s	1.1.1.2	(5/12/87)

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
	def	Mouse;	scl	10;	type	010;	size	10;	endef
	def	xy;	val	0;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	jxy;	val	4;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	buttons;	val	8;	scl	8;	type	04;	endef
	def	~eos;	val	10;	scl	102;	tag	Mouse;	size	10;	endef
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
	def	Timer;	scl	10;	type	010;	size	16;	endef
	def	waketime;	val	0;	scl	8;	type	017;	endef
	def	tfire;	val	4;	scl	8;	type	0224;	endef
	def	targ;	val	8;	scl	8;	type	05;	endef
	def	tnext;	val	12;	scl	8;	type	030;	tag	Timer;	size	16;	endef
	def	~eos;	val	16;	scl	102;	tag	Timer;	size	16;	endef
	data	1
	def	Timer;	scl	13;	type	010;	tag	Timer;	size	16;	endef
	text
	def	Texture16;	scl	10;	type	010;	size	32;	endef
	def	bits;	val	0;	scl	8;	type	064;	dim	16;	size	32;	endef
	def	~eos;	val	32;	scl	102;	tag	Texture16;	size	32;	endef
	data	1
	def	Texture16;	scl	13;	type	010;	tag	Texture16;	size	32;	endef
	text
	def	Queue;	scl	10;	type	010;	size	30;	endef
	def	first;	val	0;	scl	8;	type	034;	endef
	def	last;	val	4;	scl	8;	type	034;	endef
	def	array;	val	8;	scl	8;	type	034;	endef
	def	array_last;	val	12;	scl	8;	type	034;	endef
	def	c_cc;	val	16;	scl	8;	type	016;	endef
	def	size;	val	18;	scl	8;	type	016;	endef
	def	ipl;	val	20;	scl	8;	type	016;	endef
	def	pad;	val	22;	scl	8;	type	065;	dim	2;	size	8;	endef
	def	~eos;	val	30;	scl	102;	tag	Queue;	size	30;	endef
	data	1
	def	Queue;	scl	13;	type	010;	tag	Queue;	size	30;	endef
	text
	def	Proc;	scl	10;	type	010;	size	798;	endef
	def	sp;	val	0;	scl	8;	type	025;	endef
	def	text;	val	4;	scl	8;	type	022;	endef
	def	data;	val	8;	scl	8;	type	022;	endef
	def	bss;	val	12;	scl	8;	type	022;	endef
	def	state;	val	16;	scl	8;	type	05;	endef
	def	state2;	val	20;	scl	8;	type	05;	endef
	def	state3;	val	24;	scl	8;	type	05;	endef
	def	appl;	val	28;	scl	8;	type	05;	endef
	def	uDrect;	val	32;	scl	8;	type	010;	tag	Rectangle;	size	8;	endef
	def	uJdisplayp;	val	40;	scl	8;	type	030;	tag	Bitmap;	size	18;	endef
	def	uargc;	val	44;	scl	8;	type	04;	endef
	def	uargv;	val	46;	scl	8;	type	0122;	endef
	def	umouse;	val	50;	scl	8;	type	010;	tag	Mouse;	size	10;	endef
	def	ctob;	val	60;	scl	8;	type	0230;	tag	Point;	size	4;	endef
	def	btoc;	val	64;	scl	8;	type	0230;	tag	Point;	size	4;	endef
	def	pad1;	val	68;	scl	8;	type	065;	dim	8;	size	32;	endef
	def	host;	val	100;	scl	8;	type	030;	endef
	def	layer;	val	104;	scl	8;	type	030;	tag	Layer;	size	30;	endef
	def	caches;	val	108;	scl	8;	type	05;	endef
	def	msqid_q;	val	112;	scl	8;	type	030;	endef
	def	pad2;	val	116;	scl	8;	type	065;	dim	6;	size	24;	endef
	def	rect;	val	140;	scl	8;	type	010;	tag	Rectangle;	size	8;	endef
	def	pad3;	val	148;	scl	8;	type	065;	dim	4;	size	16;	endef
	def	traploc;	val	164;	scl	8;	type	05;	endef
	def	traptype;	val	168;	scl	8;	type	04;	endef
	def	pad4;	val	170;	scl	8;	type	065;	dim	3;	size	12;	endef
	def	scurpt;	val	182;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	curpt;	val	186;	scl	8;	type	010;	tag	Point;	size	4;	endef
	def	timer;	val	190;	scl	8;	type	010;	tag	Timer;	size	16;	endef
	def	pad5;	val	206;	scl	8;	type	065;	dim	4;	size	16;	endef
	def	cursor;	val	222;	scl	8;	type	030;	tag	Texture16;	size	32;	endef
	def	inhibited;	val	226;	scl	8;	type	04;	endef
	def	pad6;	val	228;	scl	8;	type	065;	dim	12;	size	48;	endef
	def	nextproc;	val	276;	scl	8;	type	030;	tag	Proc;	size	798;	endef
	def	xtchan;	val	280;	scl	8;	type	04;	endef
	def	kbdqueue;	val	282;	scl	8;	type	010;	tag	Queue;	size	30;	endef
	def	pad7;	val	312;	scl	8;	type	065;	dim	12;	size	48;	endef
	def	kbd_LEDs;	val	360;	scl	8;	type	04;	endef
	def	enterkey;	val	362;	scl	8;	type	062;	dim	6;	size	6;	endef
	def	rcvq;	val	368;	scl	8;	type	010;	tag	Queue;	size	30;	endef
	def	pad8;	val	398;	scl	8;	type	065;	dim	6;	size	24;	endef
	def	stack;	val	422;	scl	8;	type	024;	endef
	def	stksize;	val	426;	scl	8;	type	017;	endef
	def	pad9;	val	430;	scl	8;	type	065;	dim	12;	size	48;	endef
	def	kbdqueue_buf;	val	478;	scl	8;	type	074;	dim	128;	size	128;	endef
	def	rcvq_buf;	val	606;	scl	8;	type	074;	dim	192;	size	192;	endef
	def	~eos;	val	798;	scl	102;	tag	Proc;	size	798;	endef
	data	1
	def	Proc;	scl	13;	type	010;	tag	Proc;	size	798;	endef
	text
	def	upproc;	val	upproc;	scl	2;	type	0150;	tag	Proc;	size	798;	endef

	global	upproc
upproc:
	mov.l	_addrSys,%a0
	mov.l	4*746(%a0),%a0
	jmp	(%a0)
	def	upproc;	val	~;	scl	-1;	endef
