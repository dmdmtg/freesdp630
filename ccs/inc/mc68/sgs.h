/* #ident	"@(#)sgs-inc:cmd/sgs/inc/mc68/sgs.h	1.1" */

#define	SGS	"mc68"

/*	The symbol MC68MAGIC is defined in filehdr.h	*/


#define MAGIC	MC68MAGIC
#define TVMAGIC (MAGIC+1)

#define ISMAGIC(x)	((((unsigned short)x)==(unsigned short)MAGIC)||(((unsigned short)x)==(unsigned short)TVMAGIC))


#ifdef ARTYPE
#define	ISARCHIVE(x)	((unsigned short) x == (unsigned short) ARTYPE)
#define BADMAGIC(x)	((((x) >> 8) < 7) && !ISMAGIC(x) && !ISARCHIVE(x))
#else
#define	BADMAGIC(x)	((((x) >> 8) < 7) && !ISMAGIC(x))
#endif


/*
 *	When a UNIX aout header is to be built in the optional header,
 *	the following magic numbers can appear in that header:
 *
 *		AOUT1MAGIC : default : readonly sharable text segment
 *		AOUT2MAGIC :	      : one segment is generated
 *					(writable text)
 *		PAGEMAGIC  :	      : paging configuration
 */

#define AOUT1MAGIC 0410
#define AOUT2MAGIC 0407
#define PAGEMAGIC  0413

#define	SGSNAME	"mc68"
#define RELEASE "Release 2.0 7/8/83"
