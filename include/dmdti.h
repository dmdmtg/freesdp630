/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

typedef struct Netw {
	int (*open)();
	int (*close)();
	int (*ioctl)();
	int (*putmsg)();
	int (*getmsg)();
	int (*poll)();
	int (*unpoll)();
	int (*nauinfo)();
	long pad[7];
} Netw;

struct _ti_dmd {
	int ti_fd;			/* Device level fd */
	unsigned short ti_mode;		/* access mode */
	struct Proc *ti_proc;		/* process owning this descriptor */
	Netw *ti_netw;			/* device interface addresses */
	long pad;			/* for the future */
};

#define NETW(x) (((x)<0||(x)>max_ti_dmd)?(Netw *)0:_ti_dmd[x].ti_netw) 

typedef struct Tli {
	int (*taccept)();
	char *(*talloc)();
	int (*tbind)();
	int (*tclose)();
	int (*tconnect)();
	char *(*terror1)();
	int (*tfree)();
	int (*tgetinfo)();
	int (*tgetstate)();
	int (*tlisten)();
	int (*tlook)();
	int (*topen)();
	int (*toptmgmt)();
	int (*trcv)();
	int (*trcvconnect)();
	int (*trcvdis)();
	int (*trcvrel)();
	int (*trcvudata)();
	int (*trcvuderr)();
	int (*tsnd)();
	int (*tsnddis)();
	int (*tsndrel)();
	int (*tsndudata)();
	int (*tsync)();
	int (*tunbind)();
	int (*ttopen)();
	int (*ttclose)();
	int (*ttioctl)();
	int (*ttputmsg)();
	int (*ttgetmsg)();
	int (*ttpoll)();
	long pad[8];		/* for the future */
} Tli;
	

/*
extern struct _ti_dmd *_ti_dmd;
extern int max_ti_dmd;
*/

#define MAX_TI_DMD      I_Ref(int, 1001)
#define _TI_DMD         D_Ref(struct _ti_dmd *, -103)

