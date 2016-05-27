/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Menu2.c	1.1.1.1	(5/12/87)";

#include <dmd.h>

/* Library Routines and associated manual page. */
void exit();            /* EXIT(3R)             */
void lprintf();         /* LPRINTF              */
int menuhit();          /* MENUHIT(3L)          */
int request();          /* RESOURCES(3R)        */
void sleep();           /* SLEEP(3R)            */
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.   */
/*int button1();           BUTTONS(3R)          */
/*int button2();           BUTTONS(3R)          */
/*int button3();           BUTTONS(3R)          */

#define BUTTON2 2

/*
** Declare main menu.
*/
char *MainItems [] = { 
	"Breakfast", 
	"Lunch", 
	"Dinner", 
	(char *)0, 
};

/*
** Declare breakfast menu.
*/
char *BreakfastItems [] = { 
	"Pancakes", 
	"French Toast", 
	"Bacon & Eggs",
        "Coffee", 
	"Orange Juice", 
	"Main Menu", 
	(char *)0, 
};

/*
** Declare lunch menu.
*/
char *LunchItems [] = { 
	"Hamburger", 
	"Hot Dog", 
	"French Fries", 
	"Root Beer",
        "Grape Soda", 
	"Main Menu", 
	(char *)0, 
};

/*
** Declare dinner menu.
*/
char *DinnerItems [] = { 
	"Salad", 
	"Steak", 
	"Fish", 
	"Baked Potato", 
	"Wine",
        "Main Menu", 
	(char *)0, 
};

char **Menus [] = { 
	MainItems, 
	BreakfastItems, 
	LunchItems, 
	DinnerItems, 
};

main()
{
    int MenuSelection, WhichMenu;
    Menu CurrentMenu;

    WhichMenu = 0;
    CurrentMenu.item =  Menus[WhichMenu];

    request(MOUSE);
    lprintf("\n Press button2 for main menu.");
    for(;;) {
        wait(MOUSE);
        if (button1())
            exit();
        else if (button2()) {
            switch(WhichMenu) {
            case 0: /*MainItems*/
		/*
		** Display main menu.
		*/
                MenuSelection = menuhit(&CurrentMenu, BUTTON2);
                if (MenuSelection != -1) {
		    /*
		    ** Print main menu selection.
		    */
                    lprintf("\n Press button 2 for %s selections.",
                              MainItems[MenuSelection]);
                    WhichMenu = MenuSelection + 1;
                    CurrentMenu.item =  Menus[WhichMenu];
                }
                break;
            case 1: /*BreakfastItems*/
            case 2: /*LunchItems*/
            case 3: /*DinnerItems*/
		/*
		** Display submenu.
		*/
                MenuSelection = menuhit(&CurrentMenu, BUTTON2);
                switch(MenuSelection) {
                case -1:
                    break;
                case 5: /* Go back to main menu */
                    WhichMenu = 0;
                    CurrentMenu.item =  Menus[WhichMenu];
    		    lprintf("\n Press button2 for main menu.");
		    break;
                default:
		    /*
		    ** Print submenu selections.
		    */
                    lprintf("\n \t%s", CurrentMenu.item[MenuSelection]);
                }
	    }
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

