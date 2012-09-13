/**************************************************************/
/* Modul:     open a IPC communication for a client process   */
/*                                                            */
/* Copyright: Yafra.org, Switzerland, www.pisoag.com   */
/**************************************************************/
static char rcsid[]="$Id: client.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>
#include <string.h>

#include "socket.h"
#include <psipc.h>

static int PSIPCgetAddressByName(char *, struct in_addr *);

/************************************************************
 * IPC socket client function
 *
 * open a socket connection to a server process.
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI SOCKET PSIPCclient(char *aServer, /* TCP/IP address or hostname of server host */
                char *aServiceName,  /* TCP service name - must be in /etc/services !! */
                char *aProtocol)     /* protocol name (tcp is common) */
{
	extern int DebugFlag;

	struct servent	*service;        /* service name structure ptr */
	struct sockaddr_in serverName;  /* socket name, conn to server */
	SOCKET dataSD;	  /* socket descriptor for data transfer */
	int cret;    /* code from return */

	if (DebugFlag)
		printf("debug: client socket init start\n");

	/* get port # for service */
	if ((service = getservbyname(aServiceName, aProtocol)) == 0)
		return(IPCNOSERVICE);

	/* set sockaddr_in struct */
	serverName.sin_family      = AF_INET;
	serverName.sin_port        = service->s_port;
	cret = PSIPCgetAddressByName(aServer, &serverName.sin_addr);
	if (cret != IPCOK)
		return(cret);

	/* --- create socket for data transfer --- */
	if ((dataSD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
		perror("IPC client error: cann't create socket:");
		return(IPCNOSOCKET);
		}

	/* --- connect to server --- */
	if (connect(dataSD, (void*)&serverName, sizeof(serverName)) < 0)
		{
		perror("IPC client error: cann't connect to socket:");
		return(IPCNOCONNECT);
		}

	if (DebugFlag)
		printf("debug: client socket init done - returning data socket\n");

	return(dataSD);
}

/************************************************************
 * IPC get IP address by a hostname or FQDN
 *
 * give a hostname or fully qualified domainname and receive the 
 * IP address informations of that host
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
static int PSIPCgetAddressByName(char *aName,  /* IP hostname */
             struct in_addr *aAddress   /* IP address of hostname */)
{
	/* get internet address by internet name */
	struct hostent *entry;

	/* --- get entry from database --- */
	if ((entry = gethostbyname(aName)) == 0)
		return(IPCNOHOST);

	/* --- copy addr to return value --- */
	(void)memcpy((void *)aAddress, (void *)entry->h_addr, entry->h_length);

	return(IPCOK);
}
