/**************************************************************/
/* Modul:     berkeley socket iterface                        */
/*                                                            */
/* Copyright: Yafra.org, Switzerland, www.pisoag.com   */
/**************************************************************/
static char rcsid[]="$Id: socket.c,v 1.2 2004-02-05 18:26:44 mwn Exp $";

#include <stdio.h>

#include "socket.h"
#include <psipc.h>

#include "version.h"


/************************************************************
 * IPC socket client function
 *
 * init socketlibrary functions for IPC communication
 *
 * returns     int as an error code defined in ipc.h
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCsocketinit(void)
{
#ifdef ps_win
	WORD ws_version;
	WSADATA ws_wsadata;
	int ws_err;

	ws_version = MAKEWORD(1, 1);
	ws_err = WSAStartup(ws_version, &ws_wsadata);
	if (ws_err != 0)
		return(IPCNOINITDONE);
#endif

	return(IPCOK);
}

/************************************************************
 * IPC socket client function
 *
 * close/shutdown a socket. call this function for each
 * open socket descriptor !
 *
 * returns     int as an error code defined in psipc.h
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCsocketclose(SOCKET Asocket) /* socket descriptor */
{
	int cret;

#ifdef ps_win
	closesocket(Asocket);
	/* socket argument is not needed */
	cret = WSACleanup();
	if (cret != 0)
		return(IPCCLOSEERROR);
#else
	/* shutdown is berkley socket standard, second arg is: */
	/* 0 recv disallowed, 1 send disallowed, 2 both disallowed */
	cret = shutdown(Asocket, 2);
	cret = close(Asocket);
#endif

	return(IPCOK);
}


/************************************************************
 * IPC read data from socket
 *
 * read data from an BSD IPC socket. It reads data from a standard
 * socket filde descriptor.
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCread(SOCKET aFd, /* socket file descriptor */
              char *aBuffer,        /* data buffer */
              int aLen              /* size of data buffer byte */)
{
	int count = 0;
	int recv_flag = 0;

#ifdef ps_win
/*	recv_flag = MSG_OOB; */
/* recv_flag = MSG_PEEK; */
#endif

	count = recv(aFd, aBuffer, aLen, recv_flag);

	if (count > 0 && count != aLen)
		count += PSIPCread(aFd, (void *)&aBuffer[count], aLen - count);

	return(count);
}


/************************************************************
 * IPC write data
 *
 * read data from an BSD IPC socket. It reads data from a standard
 * socket filde descriptor.
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCwrite(SOCKET aFd, /* socket file descriptor */
              char *aBuffer,         /* data buffer */
              int aLen               /* size of data buffer byte */)
{
	int count = 0;
	int send_flag = 0;

#ifdef ps_win
/*	send_flag = MSG_OOB; */
/*	send_flag = MSG_PEEK; */
#endif

	count = send(aFd, (void *)aBuffer, aLen, send_flag);

	return(count);
}
