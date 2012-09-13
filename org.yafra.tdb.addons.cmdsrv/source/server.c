/**************************************************************
 * File:      cmdserver.c
 * Modul:     open a IPC communication for a server process
 *
 * Copyright: yafra.org
 **************************************************************/
static char rcsid[]="$Header: see github.org yafra $";

#include "version.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#ifdef ps_hpux
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#endif

#ifdef ps_linux
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#ifdef ps_cygwin
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include "cmd.h"

#include <pssys.h>
#include <pscmd.h>
#include <psipc.h>

/* IPC type flag */
#define CMDSRV_SOCKETIPC  (int)1
#define CMDSRV_FIFOIPC    (int)2
int ipcflag;

char *PSIPCservicename = "5001";
char *PSIPCservicetitle = "PISO CMD Server";
char *PSIPCprot = "tcp";
char *PSIPCservicedeps = "tcpip\0\0";
int (*PSclient)(int, char**, int);

/* external for debugging */
int DebugFlag;

/* other externals */
int   readfd, dummyfd, writefd;
Mesg  mesg;
FILE  *fplog;

/* local prototypes */
static int CMDexit(void);

/*F--------------------------------------------------------------------------
 *  Function:	main()
 *					Main function of client
 *
 *  In:			-arguments
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void main(int argc, char *argv[])
{
	int	childpid;
	int	i;
	int	cret = IPCOK;

	/* init debug flag to false */
	DebugFlag = FALSE;
	ipcflag = CMDSRV_FIFOIPC;

	/* install signals */
	PSSYSinstallSignal(SIGHUP, CMDexit);
	PSSYSinstallSignal(SIGTERM, CMDexit);

	/*--- check command line options --------*/
	for (i=1; i < argc; i++)
		{

		/* fifo (named pipe) IPC */
		if (strcmp(argv[i], "-p") == 0)
			{
			ipcflag = CMDSRV_FIFOIPC;
			continue;
			}

		/* socket IPC */
		if (strcmp(argv[i], "-s") == 0)
			{
			ipcflag = CMDSRV_SOCKETIPC;
			continue;
			}

		/* debug mode */
		if (strcmp(argv[i], "-D") == 0)
			{
			DebugFlag = TRUE;
			continue;
			}

		/* version/help mode */
		if ( (strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "-v") == 0))
			{
			(void)printf( "\n version and copyright infos:\n %s", PSIDENT);
			(void)printf( "\n\n usage of %s", argv[0]);
			(void)printf( "\n\n select a mode to start in: (default is named pipes)" );
			(void)printf( "\n -s           : start in socket mode         " );
			(void)printf( "\n -p           : start in named pipes (fifo) mode " );
			(void)printf( "\n");
			(void)printf( "\n -D           : enable debug infos on stderr " );
			(void)printf( "\n -v  or  -h   : prints this text you read    " );
			(void)printf( "\n\n" );
			exit(0);                         /* >>>>>>>>>> exit here >>>>>>*/
			}
		}

	/*--- Start a DAEMON --------------------*/
	cret = CMDserverDaemon( argc, argv );                /* always as daemon */

	CMDlogClose();

	/*--- Check Returncode and terminate */
	if (cret != IPCOK)
		{
		(void)fprintf(stderr, "\nERROR: Returncode %d\n", cret);
		exit(1);
		}
	else
		exit(0);
}

/*F--------------------------------------------------------------------------
 *  Function:	CMDserverDaemon()
 *					server gets a message from fifo, write it as message to IPC
 *
 *  In:			-read and write file descriptors
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int CMDserverDaemon( int  argc, char **argv )
{
	char		hostname[256];      /* name of server host  */
	int		ChildPID;           /* Returned by fork()   */
	pid_t		PID;


	/*--- background the server (this closes stderr and stdin) -------------*/
	PID = PSIPCbackgroundProcess(argv[0], 1);
	switch(PID)
		{
		case -1:			/* fork error! */
			perror(argv[0]);
			exit(1);
			break;

		case 0:       /* It's the child process */
			/*--- This is the child loop. It does the job ----*/
			CMDlogOpen ();
			CMDlogWrite("server started and forked");

			/*************  execute command *********/
			/*--- Create FIFOs and open them, one for read one for write --------*/
			if ( (mkfifo( FIFO1, PERMS) < 0 ) && (errno != EEXIST) )
				CMDlogWrite("can't create fifo FIFO1");
			if ( (mkfifo( FIFO2, PERMS) < 0 ) && (errno != EEXIST) )
				{
				unlink(FIFO1);
				CMDlogWrite("can't create fifo FIFO2");
				}

			/*--- change the mode to give access to world ------------*/
			chmod(FIFO1, PERMS);
			chmod(FIFO2, PERMS);

			/*--- Open in THAT order! to avoid deadlock -------------------------*/
			if ( (readfd = open(FIFO1, 0)) < 0 )
				CMDlogWrite("can't open read fifo FIFO1");
			if ( (dummyfd = open(FIFO1, 1)) < 0 )
				CMDlogWrite("can't open dummy write fifo");   /* avoid eof */
			if ( (writefd = open(FIFO2, 1)) < 0 )
				CMDlogWrite("can't open write fifo FIFO2");

			/*--- start hunting for messages ------------------------------------*/
			CMDserver( readfd, writefd);

			/*--- terminate -----------------------------------------------------*/
			close(readfd);
			close(writefd);
			break;

		default:     /* It's the parent process */
			exit(0);            /* terminate parent process, so that the child goes */
			break;              /* to the background under the init */
		}
}




/*F--------------------------------------------------------------------------
 *  Function:	CMDserver()
 *					server gets a message from fifo, write it as message to IPC
 *
 *  In:			-read and write file descriptors
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void CMDserver(int ipcreadfd, int ipcwritefd)
{
	int		ChildPID;           /* Returned by fork()   */
	pid_t		PID;
	int	n, status;
	Mesg	mesgBack;
	char		logbuf[255];
	char		*command;
	struct	passwd *Passwd_ptr;
	uid_t		userid;

	/*--- Listen always ----*/
	while (1)
		{
		/*--- Read the command or wait if nothing ---------------*/
		n = CMDmesg_recv(ipcreadfd, &mesg) ;
		if ( n <= 0 )
			CMDlogWrite("fifo command read error");
		else
			{
			mesg.mesg_data[n] = '\0';

			/*--- Create p process to execute ---------*/
			if (strlen(mesg.mesg_data) > 0)
				{
				/*--- Start a new process ! -------*/
				PID = fork();
				switch(PID)
					{
					case -1:              /* fork error! */
						CMDlogWrite("Server: unable to fork command process");
						exit(1);
						break;

					case 0:               /* It's the child process */

						/*--- find user if any ------*/
						command = strchr(mesg.mesg_data, (int)UID_SEPAR);
						if (command)
							{
							/*--- set user ------*/
							*command = '\0';
							command++;                  /* set to begin of cmd */
							Passwd_ptr = getpwnam( mesg.mesg_data );
							if (Passwd_ptr != NULL)
								{
								(void)sprintf(logbuf, "set user id to: %s", mesg.mesg_data);
								CMDlogWrite(logbuf);
								setgid(Passwd_ptr->pw_gid );
								setuid(Passwd_ptr->pw_uid );
								}
							}
						else
							command = mesg.mesg_data ;

						/*--- Execute command ------*/
						(void)sprintf(logbuf, "exec command: %s", command);
						CMDlogWrite(logbuf);
						status = system(command);
						if (status == -1 )
							{
							if (errno == ECHILD )
								status = _errorFree_;     /*--- reset status ------*/
							else
								{
								status = _errorSystem_;
								CMDlogWrite("Server: _errorSystem_");
								}
							}
						exit(0);
						break;

					default:             /* It's the parent process*/
						break;
					}
				}
			else   /*------- inconsistent message --------*/
				{
				status = _errorDataLength_ ;
				CMDlogWrite("Server: _errorDataLength_");
				}
			}



#ifdef ANSWER
		/*--- Answer is only acceptable if the client furnishes a proper fifo --*/
		/*--- Check execution ------------------------------*/
		if (status != _errorFree_)
		{
			/*--- Send message ERROR ----------------*/
			mesgBack.mesg_type = 1L;
			sprintf(mesgBack.mesg_data, "System Error: %s \n", strerror(errno) );
			mesgBack.mesg_len = strlen(mesgBack.mesg_data);
			CMDmesg_send( ipcwritefd, &mesgBack );
		} else {
			/*--- OK: Copy the data and send back ---*/
			mesgBack.mesg_type = 1L;
			strcpy( mesgBack.mesg_data, mesg.mesg_data);
			mesgBack.mesg_len = strlen(mesgBack.mesg_data);
			CMDmesg_send( ipcwritefd, &mesgBack );
		}
#endif

	} /* while */
}

static int CMDexit(void)
{
	CMDlogClose();
	exit(0);
}
