/* #ident	"@(#)sgs-inc:mc68/tv.h	2.1.1.1" */

struct tventry {
	long	tv_addr;
	};

#define TVENTRY struct tventry
#define TVENTSZ sizeof(TVENTRY)
#define MAXTVSIZE	0x7ffc		/* Maximum size of Mc68 SGS 
					   transfer vector using 
					   MC_IND16 reloc */

