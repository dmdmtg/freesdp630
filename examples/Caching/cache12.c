/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache12.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <object.h>

/* List of routines and associated manual page  */
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/* local routines */
void print();

typedef struct Globals {
        int global1;
        int global2;
} Globals;

main()
{
        Globals myglobals;

	/*
	** Release the host connection. 
	*/
        local();

	/*
	** Put application in the cache
	** as a shared application.
	*/
        cache((char *)0, A_SHARED);

        myglobals.global1 = 0;
        myglobals.global2 = 0;

        print(&myglobals);
        myglobals.global1++;
        myglobals.global2++;
        print(&myglobals);

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

void
print(globals)
Globals *globals;
{
        lprintf("\n global1 = %d, global2 = %d", globals->global1, globals->global2);
}

