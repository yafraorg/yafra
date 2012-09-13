/************************************************************
 *
 * psclient.c
 *
 ************************************************************/
 
/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/testsuite/psclient-cons/psclient.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* PROTOKOLL DEFINITION **************************************
Client sends:
0ascii-string\0
or
1\0 (which means exit)
***********************************************************/

#include <stdio.h>
#include <psipc.h>
#include <psserver.h>

#include "version.h"

/* end of global decl. */
int main(int, char *[]);

int DebugFlag;
char *PSIPCservicetitle = "PSIPC testserver";
char *PSIPCservicename = PSTST_SERVICE;
char *PSIPCprot = "tcp";
char *PSIPCservicedeps = "tcpip\0\0";
int (*PSclient)(int, char**, int);

int main(int argc, char *argv[])
{
	int cret = 0;
	SOCKET ipcfd;
	int len;
	char infolen[PSTST_INFOLEN];
	char outputbuf[50000];

/**** for crash *
	char *ptr = NULL;
	(void)memset(outputbuf, (int)'a', 50000);
	strcpy(ptr, outputbuf);
*****/

	if (argc != 2)
		{
		printf("debug: hostname as argument please\n");
		exit(1);
		}

	/* open socket and connect */
	printf("debug: IPC init\n");
	cret = PSIPCsocketinit();
	printf("debug: IPC client call with host %s\n", argv[1]);
	ipcfd = PSIPCclient(argv[1], PSTST_SERVICE, "tcp");
	switch(ipcfd)
		{
		case IPCNOSERVICE:
			printf("mpbmclient: Service not found\n");
			exit(1);
			break;
		case IPCNOHOST:
			printf("mpbmclient: Host not found\n");
			exit(1);
			break;
		case IPCNOSOCKET:
			printf("mpbmclient: Can't create socket\n");
			exit(1);
			break;
		case IPCNOCONNECT:
			printf("mpbmclient: Can't establish connection. Try later\n");
			exit(1);
			break;
		}
	printf("debug: IPC fd is %d\n", ipcfd);

	/* send a message to server */
	(void)memset(outputbuf, (int)NULL, 50000);
	sprintf(outputbuf, "0hallo test von psclient-cons");
	(void)memset(infolen, (int)NULL, PSTST_INFOLEN);
	len = strlen(outputbuf);
	sprintf(infolen, "%d", len);
	printf("debug: IPC write to server now\n");
	cret = PSIPCwrite(ipcfd, infolen, PSTST_INFOLEN);
	cret = PSIPCwrite(ipcfd, outputbuf, len);

	/* send exit command to server */
	(void)memset(outputbuf, (int)NULL, 50000);
	sprintf(outputbuf, "1");
	(void)memset(infolen, (int)NULL, PSTST_INFOLEN);
	len = strlen(outputbuf);
	sprintf(infolen, "%d", len);
	printf("debug: IPC write to server no 2 now\n");
	cret = PSIPCwrite(ipcfd, infolen, PSTST_INFOLEN);
	cret = PSIPCwrite(ipcfd, outputbuf, len);

	/* close socket */
	printf("debug: close sockets\n");
	cret = PSIPCsocketclose(ipcfd);

	printf("debug: and exit\n");
	exit(0);
}
