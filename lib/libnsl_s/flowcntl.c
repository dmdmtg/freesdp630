/*      Copyright (c) 1989 AT&T   
**      All Rights Reserved       
**
**      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   
**      The copyright notice above does not evidence any     
**      actual or intended publication of such source code.  
*/

/*
** flowcontrol() - Call the flowcontrol function in firmware through
** the firmware vector table if the function exists. With firmware
** versions before the flowcontrol function existed, the vector
** table slot will be zero, so the call to firmware will not be
** made, and this function will, as desired, do nothing.
*/

void
flowcontrol(arg)
int arg;
{
	extern char **_addrSys;

	if( _addrSys[-12] )
		( * ((void(*)())_addrSys[-12]) )(arg);
}

