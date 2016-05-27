/*	Copyright (c) 1989 AT&T */
/*	  All Rights Reserved	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any	*/
/*	actual or intended publication of such source code.	*/


struct nauinfo {
	int type;	/* Object type */
	union {
		int i;
		char ch;
		unsigned long l;
		char *addr;
	} u;
};

/* Object types */

#define NAU_CHAR	0	/* Character */
#define NAU_INT		1	/* Integer */
#define NAU_LONG	2	/* Unsigned long */
#define NAU_STRING	3	/* Null terminated string */
#define NAU_ADDR	4	/* Address of object */

/* NAU Objects */

#define NAU_NODENAME	0	/* Node name */
#define NAU_NUMVC	1	/* Number of circuits available to user */
#define NAU_STRSTAT	2	/* STREAMS statistics structure */
#define NAU_STREAMS	3	/* Streams table */
#define NAU_NSTREAM	4	/* Max number of streams */
#define NAU_MBLOCK	5	/* Message blocks */
#define NAU_NMBLOCK	6	/* Number of message blocks */
#define NAU_QUEUE	7	/* Queue structures */
#define NAU_NQUEUE	8	/* Max number of queues */
#define NAU_NBLOCK	9	/* Max data blocks per class */
#define NAU_MEDBLOCK	10	/* Max medium priority per class */
#define NAU_LOWBLOCK	11	/* Max low priority per class */
#define NAU_STREVENT	12	/* Stream event cells */
#define NAU_NSTREVENT	13	/* Max stream cells */
#define NAU_LINKBLK	14	/* Link block structures */
#define NAU_NMUXLINK	15	/* Max link blocks */
#define NAU_DBLOCK	16	/* Data blocks */
#define NAU_TM_TABLE	17	/* Timeout table */

