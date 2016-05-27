/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)hello.c	1.1.1.2	(6/12/87)";

#include <dmd.h>

/* Library Routines and associated manual page. */
void  lprintf();        /* PRINTF(3L)           */
int   wait();           /* RESOURCES(3R)        */

main()
{
	lprintf("\n hello, world");

	/*
	** Share the CPU with other applications
        ** and 630 system processes.
        */
	for (;;) wait(CPU);
}
