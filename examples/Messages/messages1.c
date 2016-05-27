/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)messages1.c	1.1.1.1	(5/12/87)";

#include <dmd.h>
#include <message.h>

/*Library routines and associated manual pages.	*/
void alarm();		/* RESOURCES(3R)	*/
void exit();            /* EXIT(3R)             */
int kbdchar();		/* KBDCHAR(3R)		*/
int local();		/* LOCAL(3R)		*/
void lprintf();         /* LPRINTF              */
long msgget();		/* MSGGET(3L)		*/
int msgrcv();		/* MSGOP(3L)		*/
int msgsnd();		/* MSGOP(3L)		*/
int request();          /* RESOURCES(3R)        */
void ringbell();	/* RINGBELL(3R)		*/
void sleep();           /* SLEEP(3R)            */
int wait();             /* RESOURCES(3R)        */

/*library macros and associated manual page.	*/
/* int button2();	   BUTTONS(3R)		*/
/* int button3();	   BUTTONS(3R)		*/

/*
** buffer for message being sent/received.
*/
msgbuf mbuf;	

main()
{
	/*
	** message queue identifier from msgget 
	*/
	long msqid;	

	/*
	** Release the host connection.
	*/
	local();

	lprintf("Use button 2 to send a message\n");

	/*
	** Request the needed resources.
	*/
	request(KBD|MOUSE|MSG);

	/*
	** Initialize message type.
	** type must be > 0 to be valid 
	*/
	mbuf.mtype = 1;	

	/*
	** Create a message queue if it does not
	** already exist.  Exit if queue can not
	** be created.
	*/
	if((msqid = msgget(0x10000, IPC_CREAT)) == -1)
		exit();	/* couldn't get the queue */

	/*
	** Continue execution until the user
	** hit a key on the keyboard.
	*/
	while(kbdchar() == -1)
	{
		/*
		** Release the CPU until one of the requested
		** resources needs servicing.
		*/
		wait(MOUSE|KBD|MSG);

		/*
		** Time to wake up.  Something must need service.
		** First check to see if there are any messages on
		** the queue.  If not, then check the mouse buttons.
		** If that was not it then maybe the user hit a
		** keyboard key.
		*/
		if(msgrcv(msqid, &mbuf, 1, (long)0, IPC_NOWAIT) != -1)
		{
			ringbell();
			lprintf("I got a message.\n");
		}
		if(button2())
		{
			/*
			** Try to post a message when the user
			** presses button 2.
			*/
			if(msgsnd(msqid, &mbuf, 1, IPC_NOWAIT) == -1)
				lprintf("Failed to send.\n");
			else
				lprintf("Sent a message.\n");
			/*
			** Go to sleep and let someone else read the
			** message.
			*/
			sleep(60);
		}
		if(button3())
		{
			/*
			** Release the mouse resource so that
			** the control process can process
			** button 3.
			*/
			request(KBD|MSG);
			sleep(2);
			request(MOUSE|KBD|MSG);
		}
	}
}

