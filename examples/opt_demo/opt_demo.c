/*       Copyright (c) 1989 AT&T   */
/*       All Rights Reserved       */

/*       THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T   */
/*       The copyright notice above does not evidence any      */
/*       actual or intended publication of such source code.   */

/* %W	(%G) */

/* opt_demo.c:
**
**	The following 630 networking application illustrates
**	the use of option management to enable transport level
**	checksums. This program is written for the StarLAN
**	connection-mode driver and is also included in starlan(4N).
**
**	Refer to intro(3N) on how to compile this program.
*/

#include <dmd.h>
#include <dmdtiuser.h>
#include <dmderrno.h>
#include <dmdslanusr.h>

#define MAXBUF	1024
char buf[MAXBUF];

main()
{
	request(KBD);
	opt_demo();
	lprintf("\nHit key to exit\n");
	wait(KBD);
	kbdchar();
}


opt_demo()
{
	extern char *t_alloc();
	int fd;

	struct t_info info;
	struct t_call *call;

	struct t_optmgmt *topt;
	U_OPTIONS *opts;

	lprintf("open starlan\n");
	if ((fd = t_open("/dev/starlan",0,&info)) == -1) {
		lprintf("t_open failed\n");
		return;
	}
	lprintf("t_open ok\n");
	lprintf("size of protocol address = %ld\n",info.addr);
	lprintf("size of protocol options = %ld\n",info.options);
	lprintf("size of max. tsdu = %ld\n",info.tsdu);
	lprintf("size of expedited tsdu = %ld\n",info.etsdu);
	lprintf("max. data on connect = %ld\n",info.connect);
	lprintf("max. data on disconnect = %ld\n",info.discon);
	lprintf("provider service type = %ld\n",info.servtype);

	if (t_bind (fd, (struct t_bind *)0, (struct t_bind *)0) == -1) {
		lprintf("t_bind failed\n");
		t_close(fd);
		return;
	}
	lprintf("t_bind ok\n");

	if ((topt = (struct t_optmgmt *)t_alloc(fd, T_OPTMGMT, T_OPT)) == (struct t_optmgmt *)0) {
		lprintf("t_alloc failed!\n");
		cleanup (fd);
		return;
	}
	topt->flags = T_DEFAULT;
	lprintf("getting default options\n");
	if (t_optmgmt (fd, topt, topt) == -1) {
		lprintf("t_optmgmt failed\n");
		cleanup(fd);
		return;
	}
	opts = (U_OPTIONS *)topt->opt.buf;
	lprintf("default checksum %s\n", opts->tk_opts.chksum ? "enabled" : "disabled");
	opts->options = U_TK_OPTION;
	opts->tk_opts.chksum = 1;
	topt->flags = T_NEGOTIATE;

	lprintf("negotiating options\n");
	if (t_optmgmt (fd, topt, topt) == -1) {
		lprintf("t_optmgmt failed\n");
		cleanup(fd);
		return;
	}
	lprintf("negotiated checksum %s\n", opts->tk_opts.chksum ? "enabled" : "disabled");

	if ((call = (struct t_call *)t_alloc(fd, T_CALL, T_ALL)) == (struct t_call *)0) {
		lprintf("t_alloc failed!\n");
		cleanup (fd);
		return;
	}
	memcpy(call->addr.buf,"foo",3);
	call->addr.len = 3;
	lprintf("calling foo\n");

	if (t_connect(fd, call, call) < 0) {
		lprintf("t_connect failed\n");
		cleanup (fd);
		return;
	}
	lprintf("connect!\n");

	opts = (U_OPTIONS *)call->opt.buf;
	lprintf("after connect checksum %s\n", opts->tk_opts.chksum ? "enabled" : "disabled");

	lprintf("sending 1k of data\n");

	t_snd(fd, buf, MAXBUF, 0);
	sleep(60);

	lprintf("sending disconnect\n");

	if (t_snddis (fd, (struct t_call *)0) < 0) {
		lprintf("t_snddis failed\n");
		cleanup (fd);
		return;
	}
	lprintf("disconnect sent\n");

	cleanup (fd);
	lprintf("ALL DONE!\n");
}


cleanup (fd)
int fd;
{
        lprintf("cleanup: t_unbind %d\n", fd);
	if (t_unbind (fd) < 0) {
		lprintf("cleanup: t_unbind failed\n");
	}
	lprintf("cleanup: t_close %d\n", fd);
	if (t_close (fd) < 0) {
		lprintf("cleanup: t_close failed\n");
	}
}

