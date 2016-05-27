/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Tmenu5.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <menu.h>
#include <font.h>
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
#define MAP1    TM_TEXT | TM_NEXT | TM_ICON | TM_FONT

/* definition of customized Titem structure */
typedef struct MyTitem {
        char    *text;
	struct Tmenu	*next;
	Bitmap	*icon;
	Font	*font;
} MyTitem;


/*
** Initialize array of MyTitem's for Breakfast submenu 
** Menu items do not have submenus 
*/
MyTitem BreakfastItems [] = {
	"Pancakes",     0, &pancake,   0,
	"French Toast", 0, &toast,     0,
	"Bacon & Eggs", 0, &bacneggs,  0,
	"Coffee",       0, &coffee,    0,
	"Orange Juice", 0, &juice,     0,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Breakfast menu 
*/
Tmenu BreakfastMenu = { (Titem *)BreakfastItems, 0, 0, 0, MAP1 };


/* Initialize array of MyTitem's for Lunch submenu */
/* Menu items do not have submenus */
MyTitem LunchItems [] = {
	"Hamburger",    0, &hamburger, 0,
	"Hot Dog",      0, &hotdog,    0,
	"French Fries", 0, &fries,     0,
	"Root Beer",    0, &rootbeer,  0,
	"Grape Soda",   0, &grapesoda, 0,
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
	"Steak",        0, &steak,     0,
	"Fish",         0, &fish,      0,
	"Salad",        0, &salad,     0,
	"Baked Potato", 0, &potato,    0,
	"Wine",         0, &wineglass, 0,
	"Anti-Acid",    0, &antiacid,  0,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Dinner menu 
*/
Tmenu DinnerMenu    = { (Titem *)DinnerItems, 0, 0, 0, MAP1 };

MyTitem DessertItems [] = {
	"Cupcake1",         0, &Cupcake,   0,
	"Cake",             0, &cake,      0,
	"Cupcake2",         0, &cup_cake,  0,
	"Fruit",            0, &fruit,     0,
	"Ice Cream",        0, &ice_cream, 0,
	"Parfait",          0, &parfait,   0,
	"Pie",              0, &pie,       0,
	"Banana Split",     0, &split,     0,
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
        "Breakfast", &BreakfastMenu, 0, 0,
        "Lunch",     &LunchMenu,     0, 0,
        "Dinner",    &DinnerMenu,    0, 0,
	"Dessert",   &DessertMenu,   0, 0,
        (char *)0, 
};

/*
** Initialization of Tmenu structure  for root menu 
*/
Tmenu MainMenu      = { (Titem *)MainItems, 0, 0, 0, MAP1 };

main()
{
        MyTitem *item;

	/* Initialize fonts in the MyTitem arrays */
	BreakfastItems[0].font = &largefont;
	BreakfastItems[1].font = &largefont;
	BreakfastItems[2].font = &largefont;
	BreakfastItems[3].font = &smallfont;
	BreakfastItems[4].font = &smallfont;
	
	LunchItems[0].font = &largefont;
	LunchItems[1].font = &largefont;
	LunchItems[2].font = &mediumfont;
	LunchItems[3].font = &smallfont;
	LunchItems[4].font = &smallfont;

	DinnerItems[0].font = &largefont;
	DinnerItems[1].font = &largefont;
	DinnerItems[2].font = &mediumfont;
	DinnerItems[3].font = &mediumfont;
	DinnerItems[4].font = &smallfont;
	DinnerItems[5].font = &largefont;

	DessertItems[0].font = &largefont;
	DessertItems[1].font = &largefont;
	DessertItems[2].font = &largefont;
	DessertItems[3].font = &largefont;
	DessertItems[4].font = &largefont;
	DessertItems[5].font = &largefont;
	DessertItems[6].font = &largefont;
	DessertItems[7].font = &largefont;

	MainItems[0].font = &largefont;
	MainItems[1].font = &largefont;
	MainItems[2].font = &largefont;

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

