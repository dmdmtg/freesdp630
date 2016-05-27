/*
 * Error codes
 */

#define	EPERM	1	/* Not super-user			*/
#define	ENOENT	2	/* No such file or directory		*/
#define	ESRCH	3	/* No such process			*/
#define	EINTR	4	/* interrupted system call		*/
#define	EIO	5	/* I/O error				*/
#define	ENXIO	6	/* No such device or address		*/
#define	E2BIG	7	/* Arg list too long			*/
#define	ENOEXEC	8	/* Exec format error			*/
#define	EBADF	9	/* Bad file number			*/
#define	ECHILD	10	/* No children				*/
#define	EAGAIN	11	/* No more processes			*/
#define	ENOMEM	12	/* Not enough core			*/
#define	EACCES	13	/* Permission denied			*/
#define	EFAULT	14	/* Bad address				*/
#define	ENOTBLK	15	/* Block device required		*/
#define	EBUSY	16	/* Mount device busy			*/
#define	EEXIST	17	/* File exists				*/
#define	EXDEV	18	/* Cross-device link			*/
#define	ENODEV	19	/* No such device			*/
#define	ENOTDIR	20	/* Not a directory			*/
#define	EISDIR	21	/* Is a directory			*/
#define	EINVAL	22	/* Invalid argument			*/
#define	ENFILE	23	/* File table overflow			*/
#define	EMFILE	24	/* Too many open files			*/
#define	ENOTTY	25	/* Not a typewriter			*/
#define	ETXTBSY	26	/* Text file busy			*/
#define	EFBIG	27	/* File too large			*/
#define	ENOSPC	28	/* No space left on device		*/
#define	ESPIPE	29	/* Illegal seek				*/
#define	EROFS	30	/* Read only file system		*/
#define	EMLINK	31	/* Too many links			*/
#define	EPIPE	32	/* Broken pipe				*/
#define	EDOM	33	/* Math arg out of domain of func	*/
#define	ERANGE	34	/* Math result not representable	*/
#define	ENOMSG	35	/* No message of desired type		*/
#define	EIDRM	36	/* Identifier removed			*/
#define ECHRNG	37	/* Channel number out of range		*/
#define EL2NSYNC 38	/* Level 2 not synchronized		*/
#define EL3HLT	39	/* Level 3 halted			*/
#define EL3RST	40	/* Level 3 reset			*/
#define ELNRNG	41	/* Link number out of range		*/
#define EUNATCH 42	/* Protocol driver not attached		*/
#define ENOCSI	43	/* No CSI structure available		*/
#define EL2HLT	44	/* Level 2 halted			*/

/* stream problems */
#define ENOSTR	60	/* Device not a stream			*/
#define ENODATA 61	/* no data (for no delay io)		*/
#define ETIME	62	/* timer expired			*/
#define ENOSR	63	/* out of streams resources		*/

#define ENONET	64	/* Machine is not on the network	*/
#define ENOPKG	65	/* Package not installed		*/
#define EREMOTE 66	/* The object is remote			*/
#define ENOLINK 67	/* the link has been severed */
#define EADV	68	/* advertise error */
#define ESRMNT	69	/* srmount error */

#define ECOMM	70	/* Communication error on send		*/
#define EPROTO	71	/* Protocol error			*/
#define EMULTIHOP 74	/* multihop attempted */
#define EDOTDOT 76	/* Cross mount point (not really error)*/
#define EBADMSG 77	/* trying to read unreadable message	*/

#define ENOTUNIQ 80	/* given log. name not unique */
#define EBADFD	 81	/* f.d. invalid for this operation */
#define EREMCHG	 82	/* Remote address changed */


/* Specific to the 630 */

#define EROM	123	/* ROM checksum error			*/
#define ERAM	124	/* RAM failure				*/
#define EXBOARD 125	/* Expansion board failure		*/

/* NOTE: the maximum error number is 128. The TLI functions
**	 depend on this maximum for returning errors.
*/

