/*       Copyright (c) 1987 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */


static char _2Vsccsid[]="@(#)dmdgetpr.c	1.1.1.5	(6/12/87)";

/*
** This program expects either 1i or i2 as an argument.
** It then goes into raw mode and sends ESC[?5; 'argv[1]' to the terminal.
** It expects the terminal to respond with ESC[?0i or ESC[?1i.
** The exit code is 1 (failure) for ESC[?0i and 0 for ESC[?1i.
*/

#include <stdio.h>
#include <signal.h>
#include <termio.h>

struct termio sttymodes, sttysave;

main(argc, argv)
int argc;
char **argv;
{

	char response[5];
	int i, count;
	void no_response();
	void cooked();
	void raw();

	alarm(5);
	signal (SIGALRM,no_response);
	signal (SIGINT,cooked);

	i = 0;
	if(argc != 2)
		exit(1);
	raw();
	write(1, "\033[?5;", 5);
	write(1, argv[1], 2);
	while(i < 5)
	{
		count = read(0, response+i, 5-i);
		if(count == -1)
		{
			cooked();
			fprintf(stderr, "dmdcat: error while reading terminal response\r\n");
			exit(1);
		}
		i += count;
	}
	cooked();
	exit(strncmp(response,"\033[?1i",5) != 0);
}

void no_response()
{
	void cooked();

	cooked();
	fprintf(stderr, "dmdcat: no response from terminal\r\n");
	exit(1);
}

void raw()
{
        ioctl(0, TCGETA, &sttysave);
        sttymodes.c_iflag = IGNBRK;
        sttymodes.c_cflag = (sttysave.c_cflag & (CBAUD | CLOCAL)) | CS8 | CREAD;        sttymodes.c_cc[VMIN] = 1;
        ioctl(0, TCSETAW, &sttymodes);
}

void cooked()
{
        ioctl(0, TCSETAW, &sttysave);
}

