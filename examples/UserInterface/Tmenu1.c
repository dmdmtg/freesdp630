/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Tmenu1.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <menu.h>

/* Library Routines and associated manual page. */
void exit();            /* EXIT(3R)             */
void lprintf();         /* LPRINTF              */
int request();          /* RESOURCES(3R)        */
void sleep();           /* SLEEP(3R)            */
Titem *tmenuhit();      /* TMENUHIT(3R)         */
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.   */
/*int button1();           BUTTONS(3R)          */
/*int button2();           BUTTONS(3R)          */
/*int button3();           BUTTONS(3R)          */

#define BUTTON2	2

/* 
** definition for menumap 
*/
#define MAP1    TM_TEXT

/*
** definition of customized Titem structure 
*/
typedef struct MainTitem {
        char    *text;
} MainTitem;

/*
** Initialization of array of Titem1's 
*/
MainTitem  MainItems [] = {
        "Breakfast",
        "Lunch",
        "Dinner",
        (char *)0,
};

/*
** Initialization of Tmenu structure 
*/
Tmenu MainMenu = { (Titem *)MainItems, 0, 0, 0, MAP1 };


main()
{
        MainTitem *item;

        request(MOUSE);
	lprintf("\n Press button 2 to get menu.");
        for (;;) {
                wait(MOUSE);
                if (button1())
                        exit();
                else if (button2()) {
			/*
			** Display menu.
			*/
                        item = (MainTitem *)tmenuhit(&MainMenu, BUTTON2, 0);
			if (item)
                        	lprintf("\n Your selection was %s",item->text);
                } else if(button3()) {
                        /*
                        ** Release ownership of the mouse and
                        ** sleep for two ticks of the 60Hz clock
                        ** to let the control process take care
                        ** processing button 3 of the mouse.
                        */
                        request(0);
                        sleep(2);
                        /*
                        ** Back on the "air," get the mouse back.
                        */
                        request(MOUSE);
                }
        }
}

