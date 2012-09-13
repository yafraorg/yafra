/**************************************************************/
/* Modul:     open a IPC communication for a server process   */
/*                                                            */
/* Copyright: Yafra.org     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/server.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include "socket.h"
#include <psipc.h>

#ifdef ps_unix
	extern int PSIPCdaemon(int, char **);
#else
	extern int PSIPCservice(int, char **);
#endif

/************************************************************
 * IPC server function
 *
 * start a server and listen on media (socket, pipes)
 * see daemon.c or service.c for more information on
 * platform dependend implementation
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCserver(
	int		aArgc,      /* argument counter */
	char	**aArgv        /* argument vector of strings */)
{
	int cret = 0;

#ifdef ps_unix
	cret = PSIPCdaemon(aArgc, aArgv);
#else
	cret = PSIPCservice(aArgc, aArgv);
#endif

	return(cret);
}
