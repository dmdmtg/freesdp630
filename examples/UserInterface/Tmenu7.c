/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)Tmenu7.c	1.1.1.1	(5/12/87)";

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
#define MAP1    TM_TEXT | TM_UFIELD | TM_NEXT | TM_ICON | TM_FONT | TM_HFN 

/*
** definition for flags parameter passed to tmenuhit 
*/
#define FLAGS	TM_STATIC 

/*
** definition of customized Titem structure 
*/
typedef struct MyTitem {
        char    *text;
	struct {
		unsigned short uval;
		unsigned short grey;
	} ufield;
	struct Tmenu	*next;
	Bitmap	*icon;
	Font	*font;
	void	(*hfn)();
} MyTitem;


/*
** declare hfn function 
*/
void SetGrey();


/*
** Initialize array of MyTitem's for Breakfast submenu 
** Menu items do not have submenus 
*/
MyTitem BreakfastItems [] = {
	"Pancakes",     {0, 0}, 0, &pancake,   0, SetGrey,
	"French Toast", {0, 0}, 0, &toast,     0, SetGrey,
	"Bacon & Eggs", {0, 0}, 0, &bacneggs,  0, SetGrey,
	"Coffee",       {0, 0}, 0, &coffee,    0, SetGrey,
	"Orange Juice", {0, 0}, 0, &juice,     0, SetGrey,
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
	"Hamburger",    {0, 0}, 0, &hamburger, 0, SetGrey,
	"Hot Dog",      {0, 0}, 0, &hotdog,    0, SetGrey,
	"French Fries", {0, 0}, 0, &fries,     0, SetGrey,
	"Root Beer",    {0, 0}, 0, &rootbeer,  0, SetGrey,
	"Grape Soda",   {0, 0}, 0, &grapesoda, 0, SetGrey,
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
	"Steak",        {0, 0}, 0, &steak,     0, SetGrey,
	"Fish",         {0, 0}, 0, &fish,      0, SetGrey,
	"Salad",        {0, 0}, 0, &salad,     0, SetGrey,
	"Baked Potato", {0, 0}, 0, &potato,    0, SetGrey,
	"Wine",         {0, 0}, 0, &wineglass, 0, SetGrey,
	"Anti-Acid",    {0, 0}, 0, &antiacid,  0, SetGrey,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Dinner menu 
*/
Tmenu DinnerMenu    = { (Titem *)DinnerItems, 0, 0, 0, MAP1 };

/*
** Initialize array of MyTitem's for Dessert submenu 
** Menu items do not have submenus 
*/
MyTitem DessertItems [] = {
	"Cupcake1",         {0, 0}, 0, &Cupcake,   0, SetGrey,
	"Cake",             {0, 0}, 0, &cake,      0, SetGrey,
	"Cupcake2",         {0, 0}, 0, &cup_cake,  0, SetGrey,
	"Fruit",            {0, 0}, 0, &fruit,     0, SetGrey,
	"Ice Cream",        {0, 0}, 0, &ice_cream, 0, SetGrey,
	"Parfait",          {0, 0}, 0, &parfait,   0, SetGrey,
	"Pie",              {0, 0}, 0, &pie,       0, SetGrey,
	"Banana Split",     {0, 0}, 0, &split,     0, SetGrey,
	(char *)0,
};

/*
** Initialization of Tmenu structure  for Dessert menu 
*/
Tmenu DessertMenu    = { (Titem *)DessertItems, 0, 0, 0, MAP1 };


/*
** Initialization of array of Titem1's for root menu 
** Each Titem in the root menu has a submenu 
*/
MyTitem  MainItems [] = {
        "Breakfast", {0, 0}, &BreakfastMenu, 0, 0, 0,
        "Lunch",     {0, 0}, &LunchMenu,     0, 0, 0,
        "Dinner",    {0, 0}, &DinnerMenu,    0, 0, 0,
	"Dessert",   {0, 0}, &DessertMenu,   0, 0, 0,
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
	lprintf("\n Click button 2 to get Menu.\n");
        for(;;) {
                wait(MOUSE);
                if (button1())
                        exit();
                else if (button2()) {
			/*
			** Wait for all buttons to be released.
			*/
			bttns(0);

			/*
			** Display Menu.
			*/
                        (void)tmenuhit(&MainMenu, BUTTON2, FLAGS);

			/*
			** Wait for all buttons to be released.
			*/
			bttns(0);
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

void
SetGrey(item)
MyTitem *item;
{
	item->ufield.grey = 1;
}

