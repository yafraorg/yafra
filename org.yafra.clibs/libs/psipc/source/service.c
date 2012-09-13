/*************************************************************
 * Modul:     open a Windows Service
 *
 * Copyright: yafra.org, Switzerland, 2004
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/service.c,v 1.4 2004-02-05 21:22:58 mwn Exp $";

#if defined(ps_winnt) || defined(ps_mingw)
#pragma warning (disable: 4001 4201 4214)

#include <windows.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <process.h>

#include "socket.h"
#include <psipc.h>

/* PSIPC externals */
extern int DebugFlag;
extern void (*PSclient)(int, char**, int);
extern char *PSIPCservicetitle;
extern char *PSIPCservicename;
extern char *PSIPCprot;
extern char *PSIPCservicedeps;

#define SRV_STOP_SIGNAL SIGTERM
#define SRV_MAX_STOP_TIME 20

/* ANSI function prototypes */
int PSIPCservice(int, char **);
static void IPCserviceMain(DWORD, LPTSTR *);
int IPCsocketServerMain(int, char **);

void IPCserviceStop(void);
void IPCserviceInstall(void);
void IPCserviceRemove(void);
void IPCserviceDebug(int, char **);

void WINAPI IPCserviceCtrl(DWORD);
static BOOL SrvUnsecureProcess(void);
int IPCsocketAcceptConnection(SOCKET *);
int IPCsocketSetupListen(void);
BOOL WINAPI SrvConCtrlHdlr(DWORD);
LPTSTR GetLastErrorText(LPTSTR, DWORD);
BOOL ReportStatusToSCMgr(DWORD, DWORD, DWORD, DWORD);

/* local variables */
SOCKET skListen; /* add right close of this socket */
SERVICE_STATUS	ssStatus;
SERVICE_STATUS_HANDLE	sshStatusHandle;
HANDLE	hServDoneEvent = NULL;
TCHAR    szErr[PATH_MAX];
int cservicerun = TRUE;


/************************************************************
 * IPC server function implemented as Windows NT service
 *
 * start a IPC server service. Needs the following externals:
 * extern int DebugFlag;
 * extern void (*PSclient)(int, char**, int);
 * extern char *PSIPCservicetitle;
 * extern char *PSIPCservicename;
 * extern char *PSIPCprot;
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * author:     Administrator
 **************************************************************/
int PSIPCservice(int aArgc, char **aArgv)
{
	SERVICE_TABLE_ENTRY dispatchTable[] =
		{
			{ TEXT(PSIPCservicename), (LPSERVICE_MAIN_FUNCTION)IPCserviceMain},
			{ NULL, NULL }
		};

	(void)SrvUnsecureProcess();

	if ( (aArgc > 1) && ((*aArgv[1] == '-') || (*aArgv[1] == '/')))
		{
		if ( strcmp( "daemon", aArgv[1]+1 ) == 0 || strcmp( "install", aArgv[1]+1 ) == 0)
			{
			IPCserviceInstall();
			}
		else if ( strcmp( "kill", aArgv[1]+1 ) == 0 )
			{
			IPCserviceRemove();
			}
		else if ( strcmp( "debug", aArgv[1]+1 ) == 0 )
			{
			IPCserviceDebug(aArgc, aArgv);
			}
		else if ( (strcmp( "?", aArgv[1]+1 ) == 0) || (strcmp( "h", aArgv[1]+1 ) == 0) )
			{
			printf( "%s -daemon  to install the service\n", PSIPCservicename );
			printf( "%s -kill    to remove the service\n", PSIPCservicename );
			printf( "%s -debug   to run as a console app for debugging\n", PSIPCservicename );
			}
		else
			{
			goto dispatch;
			}
		exit(0);
		}


	// if it doesn't match any of the above parameters
	// the service control manager may be starting the service
	// so we must call StartServiceCtrlDispatcher
dispatch:

	if (!StartServiceCtrlDispatcher(dispatchTable))
		{
 		switch ( GetLastError())
			{
			case ERROR_FAILED_SERVICE_CONTROLLER_CONNECT:
			case ERROR_CALL_NOT_IMPLEMENTED:
				IPCserviceDebug(1, NULL);
				break;
			default:
				break;
			}
		}

	return(0);
}

static void IPCserviceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{

	DWORD                   dwWait;
	PSECURITY_DESCRIPTOR    pSD;
	SECURITY_ATTRIBUTES     sa;

	// register our service control handler:
	sshStatusHandle = RegisterServiceCtrlHandler(TEXT(PSIPCservicename),
	                  IPCserviceCtrl);
	if (!sshStatusHandle)
		goto cleanup;

	// CHECKPOINT 1
	if (!ReportStatusToSCMgr(
		 SERVICE_START_PENDING, // service state
		 NO_ERROR,              // exit code
		 1,
		 3000))                 // wait hint
		goto cleanup;
  	// create the event object. The control handler function signals
  	// this event when it receives the "stop" control code.
  	hServDoneEvent = CreateEvent(
								  NULL,    // no security attributes
								  TRUE,    // manual reset event
								  FALSE,   // not-signalled
								  NULL);   // no name
  	if (hServDoneEvent == (HANDLE)NULL)
     	goto cleanup;

	// CHECKPOINT 2
   if (!ReportStatusToSCMgr(
			 SERVICE_START_PENDING, // service state
			 NO_ERROR,              // exit code
			 2,                     // checkpoint
			 3000))                 // wait hint
		goto cleanup;
	pSD = (PSECURITY_DESCRIPTOR) malloc( SECURITY_DESCRIPTOR_MIN_LENGTH );
	if (pSD == NULL)
		goto cleanup;
	if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
		goto cleanup;
	if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
		goto cleanup;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = TRUE;

	// CHECKPOINT 4 - START
	if (!ReportStatusToSCMgr(
		 SERVICE_RUNNING, // service state
		 NO_ERROR,              // exit code
		 0,
		 0))                 // wait hint
		goto cleanup;

	/********************************************************
	Use this piece of code to set the current directory of the
	service being run.
	GetEnvironmentVariable("TEMP", idir, sizeof(idir));
	SetCurrentDirectory(idir);
	********************************************************/

	//
	// Now invoke the actual service function
	//
	while ( 1 )
		{
		IPCsocketServerMain((int)dwArgc, (char **)lpszArgv);
		// check if service is stoped
		dwWait = WaitForSingleObject(hServDoneEvent, 10);
		if (dwWait == WAIT_OBJECT_0)
		 	break;
		if (cservicerun == FALSE)
			break;
		}

cleanup:
	WSASetLastError(0);
	// try to report the stopped status to the service control manager.
	if (sshStatusHandle != 0)
		(VOID)ReportStatusToSCMgr(SERVICE_STOPPED, GetLastError(), 0, 0);

	return;
}


/************************************************************
 * IPC socket server function implemented as Windows NT service
 **************************************************************/
int IPCsocketServerMain(
	int		aArgc,      /* argument counter */
	char	**aArgv       /* argument vector of strings */)
{
	extern int DebugFlag;
	extern SOCKET skListen;
	extern void (*PSclient)(int, char**, int);

	SOCKET skOut;
	int pid;
	int cret;
	struct sockaddr sad;
	int len = sizeof(sad);

	if (DebugFlag)
		printf("debug: DEBUGGING ON ! - microsoft nt service init done\n");

	/* Service initialization */
	if (DebugFlag)
		printf("debug: setting time zone\n");
	tzset();

	/* open sockets here and listen */
	if (DebugFlag)
		printf("debug: socket init\n");
	cret = PSIPCsocketinit();
	if (cret != IPCOK)
		return(cret);

	/* setup the socket for listening */
	cret = IPCsocketSetupListen();
	if (cret != IPCOK)
		return(cret);

	if (DebugFlag)
		printf("debug: start accept now\n");

	skOut = -1;
	for (;;)
		{
		skOut = accept(skListen, &sad, &len);
		if ((int)skOut < 0)
			return(IPCNOACCEPT);

		if (cservicerun == FALSE)
			{
			cret = PSIPCsocketclose(skOut);
			return(0);
			}

		if (DebugFlag)
			{
			printf("debug: accept done - NOT psforking - closing listen socket\n");
			pid = 0;
			}
		else
			pid = PSIPCfork();

		/* if 0 then it's the child */
		if (pid == 0)
			{
			if (DebugFlag)
				printf("debug: start custom func with socket %d\n", (int)skOut);
			PSclient(0, NULL, (int)skOut);
			closesocket(skOut);
			}
		}

	cret = PSIPCsocketclose(skListen);
	return(0);
}

int IPCsocketSetupListen(void)
{
	extern int DebugFlag;
	extern SOCKET skListen;
	extern char *PSIPCservicename;
	extern char *PSIPCprot;

	struct servent *service;  /* service name structure ptr */
	/* SOCKADDR_IN sin; */
	struct sockaddr_in sin;

	if (DebugFlag)
		printf("debug: setup listening on socket service %s\n", PSIPCservicename);

	/* --- get port number for service --- */
	if ((service = getservbyname(PSIPCservicename, PSIPCprot)) == 0)
		{
		if (DebugFlag)
			printf("debug: no \\winnt\\system32\\drivers\\etc\\service entry for %s\n", PSIPCservicename);
		return(IPCNOSERVICE);
		}

	/* set sockaddr_in struct */
	sin.sin_family      = AF_INET;			/* communication domain */
	sin.sin_port        = (u_short)service->s_port;	/* port # */
	sin.sin_addr.s_addr = INADDR_ANY;		/* accept all */

	if ((skListen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
		if (DebugFlag)
			printf("debug: socket() error - invalid socket\n");
		return(IPCNOSOCKET);
		}

	if (bind(skListen, &sin, sizeof(sin)))
		{
		if (DebugFlag)
			printf("debug: bind() error\n");
		return(IPCNOBIND);
		}

	if (listen(skListen, 5))
		{
		if (DebugFlag)
			printf("debug: listen() error\n");
		return(IPCNOLISTEN);
		}

	return(IPCOK);
}



/***********************************************************
PURPOSE: This function is called by the SCM whenever
         ControlService() is called on this service.
PARAMETERS:
         dwCtrlCode - type of control requested
************************************************************/
void WINAPI IPCserviceCtrl(DWORD dwCtrlCode)
{
	// Handle the requested control code.
	switch(dwCtrlCode)
		{
		// Pause the service if it is running.
		case SERVICE_CONTROL_PAUSE:
			break;

		// Resume the paused service.
		case SERVICE_CONTROL_CONTINUE:
			break;

		// Stop the service.
		case SERVICE_CONTROL_STOP:
			// Report the status, specifying the checkpoint and waithint,
			//  before setting the termination event.
			ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0, 0);
			closesocket(skListen);
			IPCserviceStop();
			return;

		// Update the service status.
		case SERVICE_CONTROL_INTERROGATE:
			break;

		// invalid control code
		default:
			break;
		}

	// send a status response.
	ReportStatusToSCMgr(ssStatus.dwCurrentState, NO_ERROR, 0, 0);
}

/* stop the service */
void IPCserviceStop(void)
{
	extern int cservicerun;

	cservicerun = FALSE;
	if ( hServDoneEvent )
		SetEvent(hServDoneEvent);
}

void IPCserviceInstall(void)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;

	TCHAR szPath[PATH_MAX];

	if ( GetModuleFileName( NULL, szPath, PATH_MAX ) == 0 )
		{
		printf(TEXT("Unable to install %s - %s\n"), TEXT(PSIPCservicetitle), GetLastErrorText(szErr, PATH_MAX));
		return;
		}

	schSCManager = OpenSCManager(
		  NULL,                   // machine (NULL == local)
		  NULL,                   // database (NULL == default)
		  SC_MANAGER_ALL_ACCESS   // access required
		  );
	if ( schSCManager )
		{
		schService = CreateService(
			schSCManager,               // SCManager database
			TEXT(PSIPCservicename),        // name of service
			TEXT(PSIPCservicetitle), // name to display
			SERVICE_ALL_ACCESS,         // desired access
			SERVICE_WIN32_OWN_PROCESS,  // service type
			SERVICE_AUTO_START,       // start type
			SERVICE_ERROR_NORMAL,       // error control type
			szPath,                     // service's binary
			NULL,                       // no load ordering group
			NULL,                       // no tag identifier
			TEXT(PSIPCservicedeps),       // dependencies
			NULL,                       // LocalSystem account
			NULL);                      // no password

		if ( schService )
			{
			printf(TEXT("%s installed.\n"), TEXT(PSIPCservicetitle) );
			CloseServiceHandle(schService);
			}
		else
			{
			printf(TEXT("CreateService failed - %s\n"), GetLastErrorText(szErr, PATH_MAX));
			}

		CloseServiceHandle(schSCManager);
		}
	else
		printf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,PATH_MAX));
}

/* KILL the service */
void IPCserviceRemove(void)
{
	SC_HANDLE   schService;
	SC_HANDLE   schSCManager;

	schSCManager = OpenSCManager(
										  NULL,                   // machine (NULL == local)
										  NULL,                   // database (NULL == default)
										  SC_MANAGER_ALL_ACCESS   // access required
										  );
	if ( schSCManager )
		{
		schService = OpenService(schSCManager, TEXT(PSIPCservicename), SERVICE_ALL_ACCESS);

		if (schService)
			{
			// try to stop the service
			if ( ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )
				{
				printf(TEXT("Stopping %s."), TEXT(PSIPCservicetitle));
				Sleep( 10 );

				while( QueryServiceStatus( schService, &ssStatus ) )
					{
					if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
						{
						printf(TEXT("."));
						Sleep( 10 );
						}
					else
						break;
					}

				if ( ssStatus.dwCurrentState == SERVICE_STOPPED )
					printf(TEXT("\n%s stopped.\n"), TEXT(PSIPCservicetitle) );
				else
					printf(TEXT("\n%s failed to stop.\n"), TEXT(PSIPCservicetitle) );
				}

			// now remove the service
			if( DeleteService(schService) )
				printf(TEXT("%s removed.\n"), TEXT(PSIPCservicetitle) );
			else
				printf(TEXT("DeleteService failed - %s\n"), GetLastErrorText(szErr,PATH_MAX));

			CloseServiceHandle(schService);
			}
		else
			printf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,PATH_MAX));

		CloseServiceHandle(schSCManager);
		}
	else
		printf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,PATH_MAX));
}

/* DEBUG the service */
void IPCserviceDebug(int argc, char ** argv)
{
	DWORD dwArgc;
	LPTSTR *lpszArgv;

	DebugFlag = 1;

	printf("debug: NT SOCKET SERVICE %s\n", TEXT(PSIPCservicename));

#ifdef UNICODE
	lpszArgv = CommandLineToArgvW(GetCommandLineW(), &(dwArgc) );
#else
	dwArgc   = (DWORD) argc;
	lpszArgv = argv;
#endif

	SetConsoleCtrlHandler( SrvConCtrlHdlr, TRUE );

	IPCsocketServerMain((int)dwArgc, (char **)lpszArgv);
}


/********************** NT service utilities ****************************/

/* controll handler for console mode (debug mode) */
BOOL WINAPI SrvConCtrlHdlr(DWORD dwCtrlType)
{
	switch( dwCtrlType )
		{
		case CTRL_BREAK_EVENT:  // use Ctrl+C or Ctrl+Break to simulate
		case CTRL_C_EVENT:      // SERVICE_CONTROL_STOP in debug mode
			printf("Stopping %s.\n", TEXT(PSIPCservicename));
			IPCserviceStop();
			return TRUE;
		}

	return FALSE;
}

/* get the last error and put it into a string */
LPTSTR GetLastErrorText(LPTSTR lpszBuf, DWORD dwSize)
{
	DWORD dwRet;
	LPTSTR lpszTemp = NULL;

	dwRet = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_ARGUMENT_ARRAY,
								 NULL,
								 GetLastError(),
								 LANG_NEUTRAL,
								 (LPTSTR)&lpszTemp,
								 0,
								 NULL );

	// supplied buffer is not long enough
	if ( !dwRet || ( (long)dwSize < (long)dwRet+14 ) )
		lpszBuf[0] = TEXT('\0');
	else
		{
		lpszTemp[lstrlen(lpszTemp)-2] = TEXT('\0');  //remove cr and newline character
		sprintf( lpszBuf, "%s (0x%x)", lpszTemp, GetLastError() );
		}

	if (lpszTemp)
		LocalFree((HLOCAL)lpszTemp);

	return lpszBuf;
}

//
//  SrvUnsecureProcess() --
// This function removes security from the current process, so the
// service, which is running as System, can be accessed.
//
// This function is not used on Windows 95.
//
static BOOL SrvUnsecureProcess(void)
{
	SECURITY_DESCRIPTOR  security;

	if (!InitializeSecurityDescriptor(
		&security,
		SECURITY_DESCRIPTOR_REVISION))
		{
		return FALSE;
		}

	if (!SetSecurityDescriptorDacl(
		&security,
		TRUE, /* replace security */
		NULL, /* security removed */
		FALSE))  /* not defaulted */
		{
		return FALSE;
		}

	if (!SetKernelObjectSecurity(
		GetCurrentProcess(),
		DACL_SECURITY_INFORMATION,
		&security))
		{
		return FALSE;
		}

return TRUE;
}


// ReportStatusToSCMgr() --
//      This function is called by the ServMainFunc() and
//      ServCtrlHandler() functions to update the service's status
//      to the service control manager.
//
BOOL ReportStatusToSCMgr(DWORD dwCurrentState,
                    DWORD dwWin32ExitCode,
                    DWORD dwCheckPoint,
                    DWORD dwWaitHint)
{
	BOOL fResult;

	// Disable control requests until the service is started.
	//
	if (dwCurrentState == SERVICE_START_PENDING)
		ssStatus.dwControlsAccepted = 0;
	else
		ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	// These SERVICE_STATUS members are set from parameters.
	//
	ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ssStatus.dwServiceSpecificExitCode = 0;
	ssStatus.dwCurrentState = dwCurrentState;
	ssStatus.dwWin32ExitCode = dwWin32ExitCode;
	ssStatus.dwCheckPoint = dwCheckPoint;
	ssStatus.dwWaitHint = dwWaitHint;

	// Report the status of the service to the service control manager.
	//
	if (!(fResult = SetServiceStatus(
		sshStatusHandle,    // service reference handle
		&ssStatus)))        // SERVICE_STATUS structure
		{
		// If an error occurs, stop the service.
		//
		IPCserviceStop();
		}

	return fResult;
}



#endif
