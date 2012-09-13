/**************************************************************/
/* Modul:     open a pipe communication for a process         */
/*                                                            */
/* Copyright: Yafra.org     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/pipeio.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>
#ifdef ps_unix
#include <unistd.h>
#endif
#include <psipc.h>

/************************************************************
 * I/O over named pipes
 *
 * I/O over named pipes. It's the alternative of socket I/O
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCpipeInOut(char *aCommand  /* client command to execute */)
{
	int	toChild[2];
	int	toParent[2];
	int	pid;

#ifdef ps_unix
	pipe(toChild);
	pipe(toParent);

	if (pid = fork(), pid == 0)
		{
		close(0);
		dup(toChild[0]);
		close(1);
		dup(toParent[1]);
		close(toChild[0]);
		close(toChild[1]);
		close(toParent[0]);
		close(toParent[1]);
		execlp(aCommand, aCommand, NULL);
		}
	else if (pid > 0)
		{
		close(0);
		dup(toParent[0]);
		close(1);
		dup(toChild[1]);
		close(toChild[0]);
		close(toChild[1]);
		close(toParent[0]);
		close(toParent[1]);
		return(IPCOK);
		}
	else
		return(IPCNOPIPE);
#endif

	return(0);
}




