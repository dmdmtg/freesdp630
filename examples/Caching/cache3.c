/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache3.c	1.1.1.2	(5/19/87)";

#include <dmd.h>
#include <object.h>

/* List of routines and associated manual page  */
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

main()
{
	/*
	** Put application in the cache.
	*/
        cache((char *)0, 0);

	/*
	** Release the host connection. 
	*/
	local();

        lprintf("\n Hello World.");

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

