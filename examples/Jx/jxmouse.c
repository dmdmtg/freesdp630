/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)jxmouse.c	1.1.1.2	(5/22/87)";

#include <dmd.h>
#include <dmdio.h>	/* Needed for jx */
#include "world.h"

/* Library Routines and associated manual page. */
void bitblt();          /* BITBLT(3R)           */
int eqpt();		/* EQ(3R)		*/
void exit();		/* EXIT(3R)		*/
void fprintf();		/* PRINTF(3L)		*/
int kbdchar();		/* KBDCHAR(3R)		*/
void lprintf();		/* PRINTF(3L)		*/
int own();              /* RESOURCES(3R)        */
int request();          /* RESOURCES(3R)        */
void sleep();           /* SLEEP(3R)            */
int wait();             /* RESOURCES(3R)        */

/* Library Macros and associated manual page.   */
/* int button3		   BUTTONS(3R)		*/


#define MAXLEN 250

main()
{
	Point MousePosition;
	Point OldPosition;
	unsigned char c;
	char *p;
	char words[MAXLEN];
	short len;
	
	len = 0;
	p = words;

        /*
        ** Request the use of the MOUSE resource.
        */
	request(MOUSE);

        /*
        ** Allow the 630 control process to run
        ** and update the mouse position.
        */
        sleep(2);

        /*
        ** Record the current mouse position.
        */
	MousePosition = mouse.xy;
	
        /*
        ** Draw the world Bitmap at the current
        ** mouse position.
        */
	bitblt(&world, world.rect, &display, MousePosition, F_XOR);
	
	/* 
	** Track the mouse until button 3 pressed 
	*/
	for(wait(MOUSE); !button3();wait(MOUSE)) {
		/*
                ** Erase the world Bitmap from the old
                ** mouse position.
                */
		bitblt(&world, world.rect, &display, MousePosition, F_XOR);

                /*
                ** Update the MousePosition.
                */
		OldPosition = MousePosition;
		MousePosition = mouse.xy;

                /*
                ** Draw the world at the new position.
                */
		bitblt(&world, world.rect, &display, MousePosition, F_XOR);
                /*
                ** Sleep for two ticks of the 60Hz clock to
                ** release the CPU and synchronize with the
                ** 60Hz refresh rate of the 630 screen.
                */
		sleep(2);
		
		/*
		** If current window, write the mouse 
		** coordinates to stdout 
		*/
		if ((own()&MOUSE) && !eqpt(OldPosition, MousePosition)) {
			printf("x = %d\n", mouse.xy.x);
			printf("y = %d\n\n", mouse.xy.y);
		}
	}
	/*
        ** Erase the world Bitmap from the old
        ** mouse position.
        */
	bitblt(&world, world.rect, &display, MousePosition, F_XOR);

	fprintf(stderr, "Your last words...\n");
	lprintf("\nAbout to exit, any last words?  (type now)\n");
	lprintf("    Hit @ when ready to quit.\n");
	
	/*
	** Request the keyboard resource and wait
	** until there are keyboard characters to
	** be serviced.
	*/
	request(KBD);
	wait(KBD);
		
	/*
	** Save what is typed (up to MAXLEN characters) 
	** in the string pointed to by "p" until 
	** the user types '@' 
	*/
	while ((c=(unsigned char)kbdchar()) != '@') {
		if (len < MAXLEN) {
			len++;
			*p++ = c;
		}

		/*
		** Print character typed and then
		** wait for more input from the keyboard.
		*/
		lprintf("%c", c);
		wait(KBD);
	}
	*p = '\0';
	/*
	** Send the string to stderr.
	*/
	fprintf(stderr, "%s\n", words);

	/* 
	** Must call exit for jx.
	** stdout and stderr will be 
	** sent to the window 
	*/
	exit();
}
