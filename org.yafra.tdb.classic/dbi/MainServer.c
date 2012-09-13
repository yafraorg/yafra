/*D***********************************************************
 * Modul:     DBI daemon process main function
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C         */
#include <psipc.h>         /* IPC Header for daemon process */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MainServer.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

/* these definitions are for the PSIPC server/service routines.
   it's prime focus is on Windows NT service behavior. The dependencies
   are services, that have to be up and running before this service is
   started.
*/
char *PSIPCservicename = SERVICE;
char *PSIPCservicetitle = "MARCO POLO TO Server";
char *PSIPCprot = PROT;
char *PSIPCservicedeps = "tcpip\0NuTCRACKER Service\0\0";
int (*PSclient)(int, char**, int);

int main(int argc, char *argv[])
{
	int cret = 0;            /* Returncode von IPC oder PIPE process */

   PSclient = MainMarco;
   cret = PSIPCserver(argc, argv);
   if (cret != IPCOK)
      {
      (void)printf("\n PSserver exit with error code %d\n", cret);
      exit(1);
		}

	exit(0);
}
