/*D***********************************************************
 * File:      cmdoperation.c
 * Modul:     Send and receive operations for client/server
 *                                                            
 * Copyright: yafra.org     
 **************************************************************/
static char rcsid[]="$Header: see github.com yafra $";

#include <pscmd.h> 

/*F--------------------------------------------------------------------------
 *  Function:	CMDmesg_send()
 *					-send a message by writing a file descriptor
 *					The mesg_len type and data must be filled by caller
 *  In:			-file desc,  ptr ot message 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void CMDmesg_send( int fd, Mesg *mesgptr)
{
	int n;

	/*--- total length ---------*/
	n = MESGHDRSIZE + mesgptr->mesg_len;

	/*--- write message ---------*/
	if (write (fd,  (char*)mesgptr, n) != n)
		perror("CMDSRV fifo write error"); 
}


/*F--------------------------------------------------------------------------
 *  Function:	CMDmesg_recv()
 *					-receive  a message by reading a file descriptor
 *					
 *  In:			-file desc,  ptr ot message 
 *  out:			-
 *  Return:		-message length
 *---------------------------------------------------------------------------
 */
int CMDmesg_recv( int fd, Mesg *mesgptr)
{
	int n;

	/*--- read header first ---------*/
	if ( (n = read(fd, (char*)mesgptr, MESGHDRSIZE)) == 0)
		return(0);                                           /* end of file */
	else if (n != MESGHDRSIZE)
		return(-1);

	/*--- read actual data ----------*/
	if ( (n = mesgptr->mesg_len) > 0)
		if (read (fd,  mesgptr->mesg_data, n) != n)
			return (-1);                                         
		else
			return(n);
}
