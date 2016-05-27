/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Menu1.c	1.1.1.2	(5/22/87)";

#include <dmd.h>

/* Library Routines and associated manual page. */
void exit();		/* EXIT(3R)		*/
void lprintf();         /* LPRINTF      	*/
int menuhit();		/* MENUHIT(3L)		*/
int request();          /* RESOURCES(3R)        */
void sleep();		/* SLEEP(3R)		*/
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.	*/
/*int button1();	   BUTTONS(3R)		*/
/*int button2();	   BUTTONS(3R)		*/
/*int button3();	   BUTTONS(3R)		*/

#define BUTTON2 2

/* 
** Declare array of menu items 
*/
char *MainItems [] = {
        "Breakfast",
        "Lunch",
        "Dinner",
        (char *)0,
};

Menu MainMenu = { MainItems };

main()
{
        int m;
        request(MOUSE);
        for(;;) {
                wait(MOUSE);
                if (button1())
			/*
			** Terminate execution.
			*/
                        exit();
                else if (button2()) {
			/*
			** Application menus are normally handled on
			** button 2. Call "menuhit" to get user's menu
			** selection and print out selection made.
			*/
                        m = menuhit(&MainMenu, BUTTON2);
                        lprintf("Your selection was %s\n", MainItems[m]);
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
