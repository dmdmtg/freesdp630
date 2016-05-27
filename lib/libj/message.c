/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)message.c	1.1.1.4	(5/10/87)";

#include <dmd.h>
#include <layer.h>
#include <dmdproc.h>
#include <message.h>

/*****************************************************************************/
/*									     */
/* These are the message handling routines. They are the same as for UNIX    */
/* except for the msqid_ds structure and a few enhancements.		     */
/*									     */
/*****************************************************************************/

#define clr_msg_wake()	(P->state &= ~MSG_WAKE)

extern char *alloc();
extern unsigned long realtime();

long
msgget(key, msgflg)
register long key;
register int msgflg;
{
/* Find the message queue id for a given key. If none is found, create a queue
   if msgflg & IPC_CREAT is true.  This routine sets the MSG_WAKE bit for the
   calling process iff a message queue has messages in it. */

	register msqid_ds *mp;

	if(key == IPC_PRIVATE)
	{ /* wants a unique key */
		for(key=1; key<10000; key++)
		{ /* try 10000 */
			for(mp = Msg_queue; mp; mp = mp->next)
				if(mp->name == key)
					break;
			if(!mp) /* no match */
				break;
		}
		if(key == 10000) /* ??? all 10000 are in use */
			return(-1);
	}

	for(mp = Msg_queue; mp; mp = mp->next)
		if(mp->name == key)
			break;
	if(mp) /* found a queue matching the key */
		if((msgflg & IPC_CREAT) && (msgflg & IPC_EXCL))
			return(-1); /* but caller wants to create a queue */
		else {
			if (add_msqid(mp) == -1)
				/* no memory to add to msqid_q */
				return(-1);
			if (((msqid_ds *) mp)->msg_qnum) /* if queue has data, set bit */
				set_msg_wake(mp, P);
			return((long)mp);
		}
	else /* could not find a matching queue */
		if(!(msgflg & IPC_CREAT))
			return(-1); /* but caller didn't what to create a queue */
		else
			if(mp = (msqid_ds *)alloc(sizeof(msqid_ds)))
			{ /* create a queue */
				if (add_msqid(mp) == -1)
				{ /* couldn't add to process msqid_q, so fail */
					free(mp);
					return(-1);
				}
				init_msq(mp, key, msgflg);
				mp->next = Msg_queue;
				Msg_queue = mp;
				return((long)mp);
			}
			else /* not enough memory */
				return(-1);
}


void
register init_msq(mp, name, msgflg)
register msqid_ds *mp;
register long name;
register int msgflg;
{ /* initialize message queue structure */
	mp->msg_qnum = 0;
	mp->msg_qbytes = MAX_QBYTES;
	mp->msg_curbytes = 0;
	mp->msg_lspid = mp->msg_lrpid = 0;
	mp->msg_stime = mp->msg_rtime = 0;
	mp->msg_ctime = realtime();
	mp->msg_list = 0;
	mp->cid = P;
	mp->state = msgflg & NO_SAVE;
	mp->name = name;
	mp->next = 0;
	allocown(mp, (char *)0);
}


int
msgctl(msqid, cmd, buf)
register int cmd;
register msqid_ds *msqid, *buf;
{ /* Either stat the queue or set some of its values or remove it.
     This routine clears the MSG_WAKE bit of the calling process 
     AND if the message queue is removed, will set the MSG_WAKE bit
     of all processes that are using this queue.
  */
	register msqid_ds *tmp;

	clr_msg_wake();
	if(!valid_msqid(msqid))
		return(-1);	/* bad id */
	switch(cmd) {
		case IPC_STAT: /* get stats */
				*buf = *msqid;
				return(0);
		case IPC_SET: /* set values in queue */
				if(buf->msg_qbytes > MAX_QBYTES)
					return(-1);
				msqid->msg_qbytes = buf->msg_qbytes;
				msqid->cid = buf->cid;
				msqid->state = buf->state;
				return(0);
		case IPC_RMID: /* remove the queue */
				tmp = Msg_queue;
				if(tmp == msqid)
					Msg_queue = tmp->next;
				else
				{
					while(tmp->next != msqid)
						tmp = tmp->next;
					tmp->next = tmp->next->next;
				}
				free_msq(msqid);
				return(0);
		default: /* bad cmd */
			return(-1);
	}
}


int
valid_msqid(msqid)
register msqid_ds *msqid;
{ /* is the given queue identifier valid? */
	register msqid_ds *mds;

	for(mds=Msg_queue; mds; mds=mds->next)
		if(mds==msqid)
			break;
	return(mds?1:0); /* return it */
}




int
msgsnd(msqid, msgp, msgsz, msgflg)
register msqid_ds *msqid;
register msgbuf *msgp;
register int msgsz, msgflg;
{ 
	/*
	** Send a message.  All processes that have done a msgget()
	** for this msqid, will have their MSG_WAKE bit set and made
	** runnable.
	*/
	register message_list *ml1, *ml2;
	register int i;

	if(msgp->mtype <= 0 || msgsz < 0)
		return(-1);	/* illegal send */
	while(1) /* loop until return */
	{
		if(!valid_msqid(msqid))
			return(-1);	/* message queue doesn't exist */
		if(msqid->msg_qbytes >= msqid->msg_curbytes + msgsz + 4)
		{ /* enough room in queue to add the message? */
			ml1 = msqid->msg_list;
			if(ml2 = (message_list *)alloc(sizeof(message_list)))
			{ /* could allocate memory */
				if(msgflg & NO_COPY)
				{
					ml2->msg = msgp;
				}
				else if(ml2->msg = (msgbuf *)alloc(msgsz + 4))
				{
					for(i=0; i<msgsz; i++)
						ml2->msg->mtext[i] = msgp->mtext[i];
					ml2->msg->mtype = msgp->mtype;
				}
				if(ml2->msg)
				{ /* can send the message */
					allocown(ml2, (char *)0);
					allocown(ml2->msg, (char *)0);
					if(ml1) /* something already on the queue */
					{
						while(ml1->next)
							ml1 = ml1->next;
						ml1->next = ml2;
					}
					else  /* empty queue */
						msqid->msg_list = ml2;
					ml2->next = 0;
					msqid->msg_curbytes += msgsz + 4;
					msqid->msg_qnum++;
					msqid->msg_lspid = P;
					msqid->msg_stime = msqid->msg_ctime = realtime();
					ml2->size = msgsz;
					set_msg_wake(msqid, (Proc *) 0);
				/* can a process wait on a message? */
				/*	if(valid_proc(msqid->cid))
						setrun(msqid->cid); */
					return(0);
				}
			}
		}
		/* get here only on a failure to alloc or queue is full */
		if(msgflg & IPC_NOWAIT)
			return(-1);
		else
			sw(1);
	}
}





int
msgrcv(msqid, msgp, msgsz, msgtyp, msgflg)
register msqid_ds *msqid;
register msgbuf *msgp;
register int msgsz, msgflg;
long msgtyp;
{ /* try to get a message off a queue */
	register message_list *ml1, *ml2;
	register int i, size;

	while(1) /* loop until return */
	{
		/*
		** Any call to msgrcv() will clear the MSG_WAKE bit
		** for the calling proc
		*/
		clr_msg_wake();

		if(!(valid_msqid(msqid)))
			return(-1);	/* message queue doesn't exist */
		if(ml1 = rcv_message(msqid, msgtyp))
		{ /* message of proper type on the queue */
			size = ml1->size;
			if(size <= msgsz || (msgflg & MSG_NOERROR))
			{ /* not too big */
				if(size > msgsz)
					size = msgsz;
				if((ml2 = msqid->msg_list) != ml1)
				{
					while(ml2->next != ml1)
						ml2 = ml2->next;
					ml2->next = ml1->next;
				}
				else /* it is at the head of the queue */
					msqid->msg_list = ml1->next;
				msqid->msg_curbytes -= size + 4;
				msqid->msg_qnum--;
				msqid->msg_lrpid = P;
				msqid->msg_rtime = msqid->msg_ctime = realtime();
				if(msgflg & NO_COPY)
				{
					*(msgbuf **)msgp = ml1->msg;
					allocown(ml1->msg, P);
				}
				else
				{
					for(i=0; i<size; i++)
						msgp->mtext[i] = ml1->msg->mtext[i];
					msgp->mtype = ml1->msg->mtype;
					free(ml1->msg);
				}
				free(ml1);
				return(size);
			}
			else /* message is too long */
				return(-1);
		}
		/* no message of that type in the queue */
		if(msgflg & IPC_NOWAIT)
			return(-1);
		else
			sw(1);
	}
}



message_list *
rcv_message(msqid, msgtyp)
register msqid_ds *msqid;
register long msgtyp;
{ /* find the first message of the given type in the given queue */
	register message_list *ml, *ml2;

	if(!valid_msqid(msqid))
		return(0);	/* message queue doesn't exist */
	if(msgtyp == 0)
		return(msqid->msg_list);	/* wants the first message */
	if(msgtyp > 0)
	{
		for(ml = msqid->msg_list; ml && ml->msg->mtype != msgtyp; ml = ml->next);
		return(ml);	/* wants a message with type msgtype */
	}
	msgtyp = -msgtyp; 	/* if negative, wants a message with type > -msgtype */
	for(ml = msqid->msg_list; ml; ml = ml->next)
		if(ml->msg->mtype <= msgtyp && (!ml2 || ml2->msg->mtype > ml->msg->mtype))
			ml2 = ml;
	return(ml2);
}


