/*D************************************************************/
/* modul:     catch signals                                   */
/*                                                            */
/* copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/signal.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

#include <stdio.h>
#include <signal.h>
#include <mpdef.h>
#include <mpmsg.h>
#include <mpobjdef.h>
#include <mpprolib.h>

void MPsig_term(int, int);
void MPsig_pipe(int, int);
void MPsig_hup(int, int);
void MPsig_int(int, int);
void MPsig_debugon(int, int);
void MPsig_debugoff(int, int);

/*F************************************************************
 * function:  MPinstall_signals
 *
 * parameter: typ of installing signals (unused now)
 *************************************************************/
void MPinstall_signals(int typ)
{
#ifdef ps_unix
	/* install SIGTERM handler for kill detection */
	(void)signal(SIGTERM, MPsig_term);

	/* install SIGPIPE handler for loss of sockets detection */
	(void)signal(SIGPIPE, MPsig_pipe);

	/* install SIGHUP handler for hangup detection */
	(void)signal(SIGHUP, MPsig_hup);

	/* install SIGINT handler for interupt detection */
	(void)signal(SIGINT, MPsig_int);

	/* install SIGUSR1 handler for debug flag control */
	(void)signal(SIGUSR1, MPsig_debugon);

	/* install SIGUSR2 handler for debug flag control */
	(void)signal(SIGUSR2, MPsig_debugoff);
#endif
}

/*F************************************************************
 * function:  MPsig_term
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_term(int signo, int code)
{
	extern int (*MPfunction_exit)();

	if (MPfunction_exit != NULL)
		MPfunction_exit(0);

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGTERM, make exit(0)");
	exit(0);
}

/*F************************************************************
 * function:  MPsig_pipe
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_pipe(int signo, int code)
{
	extern int (*MPfunction_exit)();

	if (MPfunction_exit != NULL)
		MPfunction_exit(1);

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGPIPE, make exit(1)");
	exit(1);
}

/*F************************************************************
 * function:  MPsig_hup
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_hup(int signo, int code)
{
#ifdef ps_unix
	/* reinstall signal handler */
	(void)signal(SIGHUP, MPsig_hup);
#endif

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGHUP, nothing done");
}

/*F************************************************************
 * function:  MPsig_int
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_int(int signo, int code)
{
	extern int (*MPfunction_exit)();

	if (MPfunction_exit != NULL)
		MPfunction_exit(0);

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGINT, make exit(0)");
	exit(0);
}

/*F************************************************************
 * function:  MPsig_debugon increment debug flag
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_debugon(int signo, int code)
{
	extern int DebugFlag;

#ifdef ps_unix
	/* reinstall signal handler */
	(void)signal(SIGUSR1, MPsig_debugon);
#endif

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGUSR1 - increment debug level");
	DebugFlag++;
}

/*F************************************************************
 * function:  MPsig_debugoff
 *
 * parameter: standard signal function arguments
 *************************************************************/
void MPsig_debugoff(int signo, int code)
{
	extern int DebugFlag;

#ifdef ps_unix
	/* reinstall signal handler */
	(void)signal(SIGUSR2, MPsig_debugoff);
#endif

	MPsyslog(_LOGMP, MPINFO, "MARCO POLO: got SIGUSR2 - decrement debug level");

	/* check that it's not going less than zero - zero means off/false */
	if (DebugFlag > 0)
		DebugFlag--;
}
