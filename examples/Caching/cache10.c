/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache10.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include <object.h>

/* List of routines and associated manual page  */
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/*
** temp1 is an uninitialized global variable
** an is placed in the bss section.
*/
int temp1;

main()
{
	/*
	** temp2 is an uninitialized static variable
	** an is placed in the bss section.
	*/
        static temp2;

	/*
	** Release the host connection. 
	*/
        local();

	/*
	** Put application in the cache and do not
	** initialize the bss section to zero on
	** subsequent invocations.  Note that the
	** bss section is initialized to zero the
	** first time the application runs.
	*/
        cache((char *)0, A_BSS);

        lprintf("\n temp1 = %d, temp2 = %d", temp1, temp2);
        temp1++;
        temp2++;
        lprintf("\n temp1 = %d, temp2 = %d", temp1, temp2);

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

