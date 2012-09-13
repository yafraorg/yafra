/*************************************************************
 * header:    IPC library header file
 *
 * copyright: yafra.org, Switzerland, 2004
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafraorg/cvsroot/foundation/ansic/include/psipc.h,v 1.3 2004-02-01 22:08:22 mwn Exp $
*/

#ifndef PSIPCDEFINED
#define PSIPCDEFINED

#include <psshared.h>

/* Includes for struct in_addr */

#ifdef ps_win
#include <winsock.h>
#define PSIPC_DAEMON_WORKDIR "\\tmp"
#define PATH_MAX 1024

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
typedef int SOCKET;
#define PSIPC_DAEMON_WORKDIR "/tmp"

#endif


#define IPCOK             0
#define IPCNOSERVICE     -1
#define IPCNOSOCKET      -2
#define IPCNOCONNECT     -3
#define IPCNOHOST        -4
#define IPCNOPIPE        -5
#define IPCNOBIND        -6
#define IPCNOACCEPT      -7
#define IPCNOBACKGROUND  -8
#define IPCNOLISTEN      -9
#define IPCCLOSEERROR   -10
#define IPCNOINITDONE   -11
#define IPCSELECTERROR  -12

#define IPCMAXCONN	15	/* because of DOS-Compatibility */
#define IPCMAXHOSTLEN   1024

/* CLIENT */
PS_DLLAPI SOCKET PSIPCclient(char *, char *, char *);

/* INIT and EXIT */
PS_DLLAPI int PSIPCsocketinit(void);        /* only once called */
PS_DLLAPI int PSIPCsocketclose(SOCKET);     /* for each socket called */

/* I/O, read and write */
PS_DLLAPI int PSIPCread(SOCKET, char *, int);
PS_DLLAPI int PSIPCwrite(SOCKET, char *, int);
PS_DLLAPI int PSIPCpipeInOut(char *);

/* SERVER, service and daemon */
PS_DLLAPI int PSIPCserver(int, char **);

/* UTILS */
PS_DLLAPI int PSIPCfork(void);
PS_DLLAPI int PSIPCgetHostname(char *, int, int);
#endif
