/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)cache17.c	1.1.1.2	(5/22/87)";

/*
** This program is a graphical demonstration of 630 messages. The first
** instance of this program downloaded will create a global message queue
** that all instances of this program will use. Each instance of the
** program will also create its own local message queue that will
** disappear when the window is deleted. Each instance of the program
** also puts a message in the global message queue that describes its
** window's location and the key for its local message queue.
** 
** Every instance of the program then reads all the messages in the global
** message queue and checks to see that the local message queue for the
** instance of the program that put the message in the queue still
** exists. If it does, the window's location is recorded and the message
** is put back on the global queue. Otherwise, the message is thrown
** away. Then, a bullet is sent toward all know instances of the program.
*/

#include <dmd.h>
#include <message.h>
#include <object.h>

/*
** Constant definitions.
*/
#define MAX_TARGET	20		/* maximum number of targets */
#define MSG_TYPE	(long)1		/* message type on global queue */
#define MSG_SIZE	8		/* size of my message */
#define GLB_Q_KEY	0x44454d4f	/* Key for Global Queue is DEMO */
#define SS		3		/* size of a shot */
#define FAILURE		-1		/* message get failure */


/*
** Type Definitions.
*/
typedef struct MyMsgBuf {
	long	mtype;
	Point	WindowCenter;
	long	LocalMsgQid;
} MyMsgBuf;

typedef struct Shot {
	Point ShotCenter;
	Point Velocity;
} Shot;


/*
** Global Variables.
*/
typedef struct Globals {
	Point _Target[MAX_TARGET];
	int _NumOfTargets;
}Globals;

#define Target 		(((struct Globals *)(P->appl))->_Target)
#define NumOfTargets	(((struct Globals *)(P->appl))->_NumOfTargets)


/*Library routines and associated manual pages.	*/
Point add();     	/* PTARITH(3R)		*/
char  *alloc();  	/* ALLOC(3R)		*/
Point div();     	/* PTARITH(3R)		*/
int   kbdchar(); 	/* KBDCHAR(3R)		*/
int   local();   	/* LOCAL(3R)		*/
long  msgget();  	/* MSGGET(3L)		*/
int   msgctl();		/* MSGCTL(3L)		*/
int   msgsnd();  	/* MSGOP(3L)		*/
int   msgrcv();  	/* MSGOP(3L)		*/
int   request(); 	/* RESOURCES(3R)	*/
void  sleep();   	/* SLEEP(3R)		*/
Point sub();     	/* PTARITH(3R)		*/

/* local routines */
void  AddToList();
void  DrawShots();
void  Failure();
Point GetWindowCenter();
void  Shoot();
Point WindowSize();

main()
{
    MyMsgBuf MyMsg, TempMsg;
    long GlbMsgQid;
    msqid_ds LocalMsgQ;
    int i;

    /*
    ** This application does not need a host connection.
    */
    local();

    /* 
    ** Dynamically allocate global variables.
    */
    P->appl = (long)alloc(sizeof(Globals));

    /*
    ** Init ctob function.
    */
    P->ctob = WindowSize;

    /*
    ** Cache as a local shared text application.
    ** and advertise the application with the name
    ** "Messages".
    */
    cache("Messages", A_SHARED);

    /*
    ** Request the use of the Keyboard.
    */
    request(KBD);

    if((GlbMsgQid = msgget(GLB_Q_KEY, IPC_CREAT)) == FAILURE)
        /* 
        ** Could not open global message queue.
        */
        Failure("Can't get global message queue");

    MyMsg.LocalMsgQid = msgget((long)IPC_PRIVATE, IPC_CREAT|NO_SAVE);
    if(MyMsg.LocalMsgQid == FAILURE)
        /* 
        ** Could not open my local message queue.
        */
        Failure("Can't create local message queue");

    MyMsg.mtype = MSG_TYPE;
    MyMsg.WindowCenter = GetWindowCenter();
    if(msgsnd(GlbMsgQid, &MyMsg, MSG_SIZE, IPC_NOWAIT))
        /* 
        ** Could not put my message into the global message queue.
        */
        Failure("Can't send my first message");

    /*
    ** Main loop of program.
    */
    while (kbdchar() != 'q') {
        if (msgctl(MyMsg.LocalMsgQid, IPC_STAT, &LocalMsgQ))
            /*
            ** Someone has removed my local message queue.
            ** They must want me dead.
            */
            Failure("Someone wants me dead");

        if (msgctl(GlbMsgQid, IPC_STAT, &LocalMsgQ))
            /*
            ** Someone has removed the global message queue.
            */
            Failure("global queue is gone");

        /*
        ** Get number of messages currently in the 
        ** global message queue.
        */
        i = LocalMsgQ.msg_qnum;    
        NumOfTargets =  0;

        /*
        ** If my window was reshaped, erase the window and
        ** recalculate the center of the window.
        */
        if(P->state & RESHAPED) {
            if(P->state & MOVED)
                rectf(&display, Drect, F_CLR);
            P->state &= ~RESHAPED;
            MyMsg.WindowCenter = GetWindowCenter();
        }

        /*
        ** Read all the messages off the global message queue.
        ** If the application that sent the message still exists,
        ** then add that process to the list of targets and put
        ** that applications message back on the global queue.
        ** Otherwise just throw the message away and read the
        ** next message from the queue.
        */
        while(i-- && 
              msgrcv(GlbMsgQid, &TempMsg, 
                     MSG_SIZE, MSG_TYPE,  IPC_NOWAIT|MSG_NOERROR) != -1) {
            if(msgctl(TempMsg.LocalMsgQid, IPC_STAT, &LocalMsgQ) == 0) { 
                /* 
                ** Application still exists.
                */
                if(TempMsg.LocalMsgQid != MyMsg.LocalMsgQid)
                    /* 
                    ** If it is not my own message,
                    ** then add it to the list of targets.
                    */
                    AddToList(TempMsg.WindowCenter);
                else
                    /*
                    ** I just read my own message.
                    ** Make sure my widow center is up
                    ** to date.
                    */
                    TempMsg.WindowCenter = MyMsg.WindowCenter;

                /*
                ** Put the message back on the global queue.
                */
                if (msgsnd(GlbMsgQid, &TempMsg, MSG_SIZE, IPC_NOWAIT)) 
                    /*
		    ** Oh Oh!  The message send has fail.
                    ** Remove the queue that failed.
                    */
                    msgctl(TempMsg.LocalMsgQid, IPC_RMID, &LocalMsgQ);
            }
        }

        /*
        ** If i is greater than or equal to zero, then for some reason
        ** we were not able to read all the messages from the global
        ** message queue.  Better quit.
        */
        if (i >= 0)
            Failure("I can't read from the global queue");

        /* 
        ** Shoot bullets at the other windows running this application.
        */
        Shoot();

        /* 
        ** In case the number of targets was zero, switch out
        ** here to let other applications run 
        */
        sleep(1);    
    }
}


void
AddToList(p)
Point p;
/* 
** Add a target to the list.
*/
{ 
    if (NumOfTargets == MAX_TARGET)
        /* 
        ** Over the maximum target limit.
        */
        return; 

    /*
    ** Add target to the list 
    */
    Target[NumOfTargets++] = p;    
}



void
Shoot()
{
    int i, j;
    Shot shot[MAX_TARGET];

    for (i=0; i<NumOfTargets; i++) {
        shot[i].ShotCenter = GetWindowCenter();
        shot[i].Velocity = div(sub(Target[i], shot[i].ShotCenter), 50);
    }

    DrawShots(shot);
    for (j=0; j<50; j++) {
        sleep(5);
        if (P->state & RESHAPED)
            return;

        /*
        ** Erase the old shots.
        */
        DrawShots(shot);

        /*
        ** Update the center position of each shot.
        */
        for (i=0; i<NumOfTargets; i++)
            shot[i].ShotCenter = add(shot[i].ShotCenter, shot[i].Velocity);

        /*
        ** Draw the new shots.
        */
        DrawShots(shot);
    }

    /*
    ** Erase all shots.
    */
    DrawShots(shot);
}


void
DrawShots(shot)
Shot *shot;
{
    int i;

    for(i=0; i<NumOfTargets; i++)
        /*
        ** Draw the shot in the display Bitmap.
        */
        rectf(&display, 
              Rpt(sub(shot[i].ShotCenter, Pt(SS,SS)), 
                  add(shot[i].ShotCenter, Pt(SS,SS))), 
              F_XOR);
}

void
Failure(string)
char *string;
{
    /*
    ** Print error message and wait for user to hit q.
    */
    jstring(string);
    request(KBD);
    while (kbdchar() != 'q') wait(KBD);
    exit();
}

Point
GetWindowCenter()
{
    /* 
    ** Calculate the center Point of the window 
    */
    return add(div(sub(Drect.corner, Drect.origin), 2), Drect.origin);
}

Point
WindowSize()
{
	Point p;
	p.x = 200;
	p.y = 200;
	return(p);
}
