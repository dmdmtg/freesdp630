/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache8.c	1.1.1.1	(5/12/87)";

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
** temp1 is an initialized external variable
** that is placed in the data section.
*/
int temp1 = 1;  

main()
{
	/*
	** temp2 is an initialized static variable
	** that is placed in the data section.
	*/
        static temp2 = 2;

	/*
	** Release the host connection. 
	*/
	local();

	/*
	** Put application in the cache and give the
	** instruction not to reinitialize the data
	** section to its original contents on subsequent
	** invocations.
	*/
        cache((char *)0, A_DATA);

        lprintf("\n temp1 = %d, temp2 = %d", temp1, temp2);
        temp1++;
        temp2++;
        lprintf("\n temp1 = %d, temp2 = %d", temp1, temp2);

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while(kbdchar() == -1) wait(KBD);
}

