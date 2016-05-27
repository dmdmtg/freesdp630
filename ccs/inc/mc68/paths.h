/* #ident	"@(#)sgs-inc:cmd/sgs/inc/mc68/paths.h	1.1" */

/*
 * Pathnames for UNIX MC68000
 */

/* These paths defined where things will be found at RUNTIME (as opposed
** to the directory into which they are built initiallly.
** The paths depend on the environment variable DMD.
*/

/*
** Directory containing libraries and executable files (e.g. assembler
**	pass 1)
*/
#define	LIBDIR	"/lib"

/*
** Directory containing executable ("bin") files
*/
#define	BINDIR	"/bin"

/*
** Directory for temporary files
*/
#define	TMPDIR	"/tmp"


/* Prototype name for loader output if no -o option is used. */

#define	A_OUT	"mc68a.out"


#define	M4	"m4"		/* macro processor program */

/*
** Names of various pieces called by the cc command.  The names are
** formed by prepending either BINDIR (B) or LIBDIR (L) and the cc
** command prefix (e.g., "mc68" in "mc68cc").  See cc command for
** details.
*/

#define NAMEcpp		"cpp"		/* C preprocessor:  L		*/
#define NAMEccom	"ccom"		/* C compiler:  L		*/
#define NAMEoptim	"optim"		/* optimizer:  L		*/
#define NAMEas		"as"		/* assembler:  B		*/
#define NAMEld		"ld"		/* loader:  B			*/
#define NAMEcrt0	"crt0.o"	/* C run time startoff:  L	*/
#define NAMEmcrt0	"mcrt0.o"	/* profiling startoff:  L	*/
