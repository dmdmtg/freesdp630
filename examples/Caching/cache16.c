/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache16.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <object.h>

/* List of routines and associated manual page  */
char *alloc();		/* ALLOC(3R)		*/
int cache();            /* CACHE(3L)            */
int kbdchar();          /* KBDCHAR(3R)          */
int local();            /* LOCAL(3R)            */
void lprintf();         /* PRINTF(3L)           */
int request();          /* RESOURCES(3R)        */
int wait();             /* RESOURCES(3R)        */

/* local routines */
void print();
Point SetSize();

typedef struct Globals {
        int _global1;
        int _global2;
	int _width;
	int _height;
} Globals;

#define global1         (((struct Globals *)(P->appl))->_global1)
#define global2         (((struct Globals *)(P->appl))->_global2)
#define width           (((struct Globals *)(P->appl))->_width)
#define height          (((struct Globals *)(P->appl))->_height)

main()
{
	/*
	** Release the host connection. 
	*/
        local();
	/*
	** Initialize ctob.
	*/
	P->ctob = SetSize;

        P->appl = (long)alloc(sizeof(Globals));
	width = 325;
	height = 100;

	/*
	** Put application in the cache
	** as a shared application.
	*/
        cache((char *)0, A_SHARED);

        print();
        global1++;
        global2++;
        print();

	/*
	** Put application in the cache
	** as a shared application.
	*/
        request(KBD);
        while (kbdchar() == -1) wait(KBD);
}

void
print()
{
   lprintf("\n global1 = %d, global2 = %d", global1, global2);
}

Point
SetSize(x, y, p)
int x, y;
struct Proc *p;
{
	Point pt;

	pt.x = (((struct Globals *)(p->appl))->_width);
	pt.y = (((struct Globals *)(p->appl))->_height);
	return(pt);
}

