/**************************************************************
 * modul:     manage system calls to system()
 *            if possible pass it to out command server
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/cmd_clnt.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* piso includes */
#include <pscmd.h>
#include <pssys.h>

#ifdef ps_win
#include <process.h>
#else
/* local prototypes */
static int	CMDclient( int readfd, int writefd, char* command);
static int	CMDmesg_send( int fd, Mesg *mesgptr);
static int	CMDmesg_recv( int fd, Mesg *mesgptr);
#endif

/************************************************************
 * execute a system command
 *
 * try to pass system command to our system command server
 * because of memory usage. see psfifo(1) for more infos
 * on our system command server
 *
 * returns     int as an error code
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSexecute(char *aCommand   /* the system command to executre */)
{
	int   cret = 0;
	char  tmpbuf[2048];

#ifdef ps_unix
	int	readfd, writefd;
	int   try_system_flag = 0;
	int   userid;
	char  userstr[255];
	char	mesg[MAXMESGDATA];

	/*--- Open the fifos. We assume the server has creted them. ------*/
	if ( (writefd = open( FIFO1, 1)) < 0 )
		{ 
		fprintf( stderr, "\nClientSystem: can't open write fifo: %s", FIFO1 );
		close(writefd);
		try_system_flag = 1;
		}
	if ( (readfd = open( FIFO2, 0)) < 0 ) 
		{ 
		fprintf( stderr, "\nClientSystem: can't open read fifo: %s", FIFO2 );
		close(readfd);
		try_system_flag = 1;
		}

	/*--- commit system command ----*/
	if (try_system_flag != 1)
		{
		cret = PSSYSgetUser(&userid, userstr);
		(void)sprintf(tmpbuf, "%s%c%s", userstr, UID_SEPAR, aCommand);
		cret = CMDclient(readfd, writefd, tmpbuf);
		}
	else
		cret = system(aCommand);

	/*--- terminate -----------*/
	if (try_system_flag != 1)
		{
		close(readfd); 
		close(writefd);
		}
#endif

#ifdef ps_win
	sprintf(tmpbuf, "%s &", aCommand);
	cret = system(tmpbuf);
#endif

	return(cret); 
}


#ifdef ps_unix

/*SF-------------------------------------------------------------------------
 *  Function:	CMDclient()
 *					client gets a filename from stdin, write it as message to IPC
 *					
 *  In:			-read and write file descriptors 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static int	CMDclient( int readfd, int writefd, char* command)
{
	Mesg	mesg;
	int	cret = 0;

	/*--- Send message -------------------------*/
	mesg.mesg_type = 1L; 
	strcpy(mesg.mesg_data, command);
	mesg.mesg_len = strlen(mesg.mesg_data); 
	cret = CMDmesg_send( writefd, &mesg ); 

#ifdef ANSWER
	/*--- Wait 1 answer message from server ----*/
	n = CMDmesg_recv(readfd, &mesg);
	if ( strlen( mesg.mesg_data) >= 0)
		printf("\nClientSystem: %s", mesg.mesg_data);
	else 
		fprintf( stderr, "\nClientSystem: data read error");
#endif

	return(cret);
}

/*SF-------------------------------------------------------------------------
 *  Function:	CMDmesg_send()
 *					-send a message by writing a file descriptor
 *					The mesg_len type and data must be filled by caller
 *  In:			-file desc,  ptr ot message 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static int CMDmesg_send( int fd, Mesg *mesgptr)
{
	int n;

	/*--- total length ---------*/
	n = MESGHDRSIZE + mesgptr->mesg_len;

	/*--- write message ---------*/
	if (write (fd,  (char*)mesgptr, n) != n)
	{
		fprintf( stderr, "\nClientSystem: Message write error "); 
		return(-1);
	}
	return(0);
}

/*SF-------------------------------------------------------------------------
 *  Function:	CMDmesg_recv()
 *					-receive  a message by reading a file descriptor
 *					
 *  In:			-file desc,  ptr to message 
 *  out:			-
 *  Return:		-message length
 *---------------------------------------------------------------------------
 */
static int CMDmesg_recv( int fd, Mesg *mesgptr)
{
	int n;

	/*--- read header first ---------*/
	if ( (n = read(fd, (char*)mesgptr, MESGHDRSIZE)) == 0)
		return (0);                                           /* end of file */
	else if ( n != MESGHDRSIZE)
		fprintf( stderr, "\nClientSystem: Message header read error "); 

	/*--- read actual data ---------*/
	if ( (n = mesgptr->mesg_len) > 0)
		if (read (fd,  mesgptr->mesg_data, n) != n)
			fprintf( stderr, "\nClientSystem: Data read error "); 

	return(n);
}

#endif
