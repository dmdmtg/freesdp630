/*      Copyright (c) 1989 AT&T   
**      All Rights Reserved       
**
**      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
**      The copyright notice above does not evidence any     
**      actual or intended publication of such source code.  
*/

#include <dmd.h>
#include <dmdti.h>
#include <dmdfcntl.h>


/* fcntl - The following ioctl is used by the 630 TLI code to inform
** the stream head of a change in file mode.
*/
#define I_ONDELAY       (('S'<<8)|024)	/* internal flag */


fcntl(fildes, cmd, arg)
int fildes;
int cmd;
int arg;
{
        if (cmd == F_SETFL) {
		_TI_DMD[fildes].ti_mode = arg;
                return (ioctl(fildes, I_ONDELAY, &arg));
	}
	else
		return (-1);
}

