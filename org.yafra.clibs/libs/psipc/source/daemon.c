/**************************************************************/
/* Modul:     open a IPC communication for a server process   */
/*                                                            */
/* Copyright: Yafra.org     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/daemon.c,v 1.2 2008-11-13 22:27:09 mwn Exp $";

#ifdef ps_unix

#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <unistd.h>

#include <psipc.h>

int PSIPCdaemon(int, char **);
int PSIPCbackgroundProcess(char *, int);
void PSIPCkilldaemon(void);

extern int DebugFlag;
extern void (*PSclient)(int, char**, int);
extern char *PSIPCservicename;
extern char *PSIPCprot;

/************************************************************
 * IPC socket server function
 *
 * start a IPC server process (daemon in UNIX)
 * see the book "UNIX network programming"
 * chapter 2.6 for further informations
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
int PSIPCdaemon(
	int		aArgc,     /* argument counter */
	char	**aArgv       /* argument vector of strings */)
{
	extern int			errno;

	struct servent	*service;  /* service name structure ptr */
	SOCKET			connectSD;	/* socket descriptor for conn requests */
	SOCKET			dataSD;	/* socket descriptor for data transfer */
	struct sockaddr_in	serverName;	/* socket name, incoming requests */
	struct sockaddr_in	clientName;	/* socket name, conn to client */
	int 				clientNameLen;
	char				hostName[256];   /* name of server host */
	int				childPID;		  /* Returned by fork() */
	int				pid;
	int cret;

	DebugFlag = 0;
	/* get arguments */
	if ( (aArgc > 1) && ((*aArgv[1] == '-') || (*aArgv[1] == '/')))
		{
		if ( strcmp( "kill", aArgv[1]+1 ) == 0 )
			PSIPCkilldaemon();
		else if ( strcmp( "debug", aArgv[1]+1 ) == 0 )
			DebugFlag = 1;
		}

	if (DebugFlag)
		printf("debug: starting daemon\n");

	/* --- get port number for service --- */
	if ((service = getservbyname(PSIPCservicename, PSIPCprot)) == 0)
		return(IPCNOSERVICE);

	/* --- create socket for incoming requests --- */
	if ((connectSD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
		perror("IPC server error: could not create listen socket:");
		return(IPCNOSOCKET);
		}
	// address reuse - no effect - keep as reference - cret = setsockopt(connectSD, SOL_SOCKET, SO_REUSEADDR, (int)1, sizeof(int));
	/* --- bind name to socket --- */
	serverName.sin_family      = AF_INET;			/* communication domain */
	serverName.sin_port        = service->s_port;	/* port # */
	serverName.sin_addr.s_addr = INADDR_ANY;		/* accept all */
	if (bind(connectSD, &serverName, sizeof(serverName)) == -1)
		{
		perror("IPC server error: could not bind socket:");
		return(IPCNOBIND);
		}

	/* --- background the server (this closes stderr and stdin) --- */
	if (DebugFlag)
		pid = 0;
	else
		pid = PSIPCbackgroundProcess(aArgv[0], 1); /* 1 = close stdin/stderr */
	switch(pid)
		{
		/* fork error ! - oh oh ! */
		case -1:
			perror(aArgv[0]);
			exit(1);
			break;

      /* It's the child process */
		case 0:
			/*
			 * This is the child loop. It waits for
			 * a connect request, then forks a child
			 * process to handle it.
			 */
				if (listen(connectSD, IPCMAXCONN) != 0)	/* passive socket */
					{
					perror("IPC server error: can not listen to socket:");
					return(IPCNOLISTEN);
					}
			for(;;)
				{
				/* --- wait for incoming requests --- */
				clientNameLen = sizeof(clientName);
				if ( (dataSD = accept(connectSD, &clientName, &clientNameLen)) < 0)
					{
					perror("IPC server error: accept error:");
					return(IPCNOACCEPT);
					}

				if (DebugFlag)
					pid = 0;
				else
					pid = PSIPCfork();
				if (pid == 0)
					{
					/* --- child process --- */
					if (DebugFlag)
						printf("debug: starting custom function\n");
					else
						close(connectSD);	/* close unused socket */
					PSclient(aArgc, aArgv, dataSD);
					close(dataSD);
					}
				/* --- end of child process --- */
				close(dataSD);			/* close unused socket */
				}
			break;

		/* It's the parent process */
		default:
			exit(0);  /* terminate parent process, so that the child goes */
			break;    /* to the background under the init */
		}

	return(0);
}


/************************************************************
 * change process to a background process (daemon)
 *
 * change the current process to a background process, also
 * called a daemon process. There are several rules to do
 * before it's a daemon - see the book "UNIX network programming"
 * chapter 2.6 for further informations. Error handling is done
 * with perror() function.
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
int PSIPCbackgroundProcess(
	char *aProgramName,  /* program name */
	int  aCloseFlag      /* close stdin/stderr flag */)
{
	/* --- locals --- */
	int childPID = 0;
	int cret;

	/* ---
	 * Call setpgrp to disassociate the process from
	 * it's control terminal
	 */
	setpgrp();

	/* ---
	 * Call fork(). Fork() makes a copy of the process
	 * and returns 0 to the new child, and the pid to
	 * the parent.
	 */
	childPID = PSIPCfork();
	switch (childPID)
		{
		/* fork error ! - oh oh ! */
		case -1:
			perror(aProgramName);
			return(childPID);

		/* the child always comes here */
		case 0:
			/* ---
			 * Close stdin and stderr. Stdout should have been redirected.
			 */
			if (aCloseFlag == 1)	/* TRUE */
				{
				fclose(stdin);
				fclose(stdout);
				fclose(stderr);
				}

			/* ---
			 * change working directory to a temp directory,
			 * all cores will be stored there.
			 */
			cret = chdir(PSIPC_DAEMON_WORKDIR);

			/* ---
			 * clear file creation mask
			 */
/*!!!			(void)umask(0); */

			/* ---
			 * set SIGCLD to SIG_IGN to prevent the
			 * accumulation of zombie processes.
			 */
#ifdef ps_osx
			signal(SIGCHLD, SIG_IGN);
#else
			signal(SIGCLD, SIG_IGN);
#endif
			return(childPID);

		/* It's the parent process */
		default:
			return(childPID);
		}

	return(0);
}

void PSIPCkilldaemon(void)
{
	printf("debug: killing daemon\n");
	exit(0);
}
#endif
