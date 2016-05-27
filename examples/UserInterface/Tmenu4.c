/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Tmenu4.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <menu.h>
#include "MenuIcons.h"

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
#define MAP1    TM_TEXT | TM_NEXT | TM_ICON

/*
** definition of customized Titem structure 
*/
typedef struct MyTitem {
        char    *text;
	struct Tmenu	*next;
	Bitmap	*icon;
} MyTitem;


/*
** Initialize array of MyTitem's for Breakfast submenu 
** Menu items do not have submenus 
*/
MyTitem BreakfastItems [] = {
	"Pancakes",     0, &pancake,
	"French Toast", 0, &toast,
	"Bacon & Eggs", 0, &bacneggs,
	"Coffee",       0, &coffee,
	"Orange Juice", 0, &juice,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Breakfast menu 
*/
Tmenu BreakfastMenu = { (Titem *)BreakfastItems, 0, 0, 0, MAP1 };


/*
** Initialize array of MyTitem's for Lunch submenu 
** Menu items do not have submenus 
*/
MyTitem LunchItems [] = {
	"Hamburger",    0, &hamburger,
	"Hot Dog",      0, &hotdog,
	"French Fries", 0, &fries,
	"Root Beer",    0, &rootbeer,
	"Grape Soda",   0, &grapesoda,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Lunch menu 
*/
Tmenu LunchMenu     = { (Titem *)LunchItems, 0, 0, 0, MAP1 };


/*
** Initialize array of MyTitem's for Dinner submenu 
** Menu items do not have submenus 
*/
MyTitem DinnerItems [] = {
	"Salad",        0, &salad,
	"Steak",        0, &steak,
	"Fish",         0, &fish,
	"Baked Potato", 0, &potato,
	"Wine",         0, &wineglass,
	"Anti-Acid",    0, &antiacid,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Dinner menu 
*/
Tmenu DinnerMenu    = { (Titem *)DinnerItems, 0, 0, 0, MAP1 };


MyTitem DessertItems [] = {
	"Cupcake1",         0, &Cupcake,
	"Cake",             0, &cake,
	"Cupcake2",         0, &cup_cake,
	"Fruit",            0, &fruit,
	"Ice Cream",        0, &ice_cream,
	"Parfait",          0, &parfait,
	"Pie",              0, &pie,
	"Banana Split",     0, &split,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Dinner menu 
*/
Tmenu DessertMenu    = { (Titem *)DessertItems, 0, 0, 0, MAP1 };

/*
** Initialization of array of Titem1's for root menu 
** Each Titem in the root menu has a submenu 
*/
MyTitem  MainItems [] = {
        "Breakfast", &BreakfastMenu, 0,
        "Lunch",     &LunchMenu, 0,
        "Dinner",    &DinnerMenu, 0,
	"Dessert",   &DessertMenu, 0,
        (char *)0, 
};

/*
** Initialization of Tmenu structure  for root menu 
*/
Tmenu MainMenu      = { (Titem *)MainItems, 0, 0, 0, MAP1 };

main()
{
        MyTitem *item;

        request(MOUSE);
        lprintf("\n Press button 2 to get menu.");
        for(;;) {
                wait(MOUSE);
                if (button1())
                        exit();
                else if (button2()) {
                        /*
                        ** Display menu.
                        */
                        item=(MyTitem *)tmenuhit(&MainMenu, BUTTON2, TM_EXPAND);
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

