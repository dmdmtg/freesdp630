/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache6.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <object.h>

/* List of routines and associated manual page  */
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/* Local routines in this file */
Point WindowSize();

main()
{
	/*
	** Release the host connection. 
	*/
	local();

	/*
	** Initialize P->ctob.
	*/
	P->ctob = WindowSize;

	/*
	** Put application in the cache
	** as a shared application.
	*/
        cache((char *)0, A_SHARED);

        lprintf("\n Hello World.");

        /*
        ** Wait for the user to hit a key.
        */
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

Point
WindowSize()
{
	Point p;
	p.x = 250;
	p.y = 250;
	return(p);
}
