/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache15.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <object.h>

/* Library routines and associated manual page. */
char *alloc();		/* ALLOC(3R)		*/
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/* local routines */
void print();

typedef struct Globals {
        int _global1;
        int _global2;
} Globals;

#define global1         (((struct Globals *)(P->appl))->_global1)
#define global2         (((struct Globals *)(P->appl))->_global2)

main()
{
	/*
	** Release the host connection. 
	*/
        local();

	/*
	** Put application in the cache
	** as a shared application.
	*/
        cache((char *)0, A_SHARED);

        P->appl = (long)alloc(sizeof(Globals));

        print();
        global1++;
        global2++;
        print();

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

void
print()
{
   lprintf("\n global1 = %d, global2 = %d", global1, global2);
}


