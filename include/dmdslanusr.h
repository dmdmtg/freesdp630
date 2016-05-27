/*
 *	SCCS_id:        @(#)slanuser.h	1.1.2.2     11/2/87 21:52:30
 *
 *
 *	         Copyright (c) 1988 AT&T
 *		   All Rights Reserved
 *
 *     THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
 *   The copyright notice above does not evidence any actual
 *   or intended publication of such source code.
 *
 */

/*
 * Release 3.1 STARLAN NETWORK ISO Transport Protocol TLI options.
 */

/* The following structure allows the user to change
 * transport level parameters via option management.
 * This is an extension to the 3.1 TLI option set.
 */


struct TKPARAMS {
	short defack;		/* How much before end of window to defer ack */
	short piggytime;	/* # of ticks to hold a piggyback ACK */
	short t4lcon;		/* T1  - CL4 connection over LAN */
	short tdata;		/* T1  - CL4 data */
	short twindow;		/* W   - CL4 window */
	short tinactivity;	/* I   - CL4 inactivity */
	short tdrwait;		/* wait before sending DR */
	short maxtxcount;	/* N - max number of transmissions per tpdu */
	short contxcount;	/* max number of transmissions for CR */
};

struct	TKOPTIONS	{
	unsigned int	chksum		: 1;
	unsigned int	expedited	: 1;
	unsigned int	extended	: 1;
	unsigned int	class		: 4;
	unsigned int	acktime		: 8;
	unsigned int	credit		: 4;
	unsigned int	tpdusize	:13;

};

struct sl_t_opts {
	unsigned long options;
	long gos_option;
	long tsdu_option;
	unsigned char group_option[16];
	unsigned long bcast_option;
	struct TKOPTIONS tk_opts;
	struct TKPARAMS tk_params;	/* Added for DMD 630 */
	};

typedef struct sl_t_opts U_OPTIONS;

#define U_OPTS_SIZE	sizeof(struct sl_t_opts)


/*
 * Bit positions within the "options" selection word.
 */
#define U_GOS_OPTION	0x00000001
#define U_TSDU_OPTION	0x00000002
#define U_GROUP_OPTION	0x00000004 
#define U_BCAST_OPTION	0x00000008
#define U_TK_OPTION	0x00000010

#define U_TK_PARAMS	0x00000020

/*#define U_ALL_OPTIONS	0x0000001f*/
#define U_ALL_OPTIONS	0x0000003f


/*
 * Legal values for the "gos_option" data word.
 */
#define U_CHARACTER	2
#define U_BLOCK		5 


/*
 * Legal values for the "bcast_option" data word.
 */
#define U_ON_BCAST	1
#define U_OFF_BCAST	0 
