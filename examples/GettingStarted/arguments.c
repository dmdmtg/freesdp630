/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)arguments.c	1.1.1.1	(5/12/87)";

#include <dmd.h>

/* Library Routines and associated manual page. */
void  lprintf();        /* PRINTF(3L)           */
int   wait();           /* RESOURCES(3R)        */

main(argc, argv)
int argc;
char **argv;
{
	int i;
	/*
	** Print command line arguments.
	*/
	for (i=0; argc; argc--, i++)
		lprintf("\n argument %d = %s", i, argv[i]);

        /*
        ** Share the CPU with other applications
        ** and 630 system processes.
        */
	for (;;) wait(CPU);
}
