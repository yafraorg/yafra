/**************************************************************/
/* Modul:     send / receive function for GUI and DBI         */
/*                                                            */
/* Copyright: yafra.org, Switzerland                          */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/lib/comm.c,v 1.2 2004-02-12 09:13:50 mwn Exp $
*/

#include <stdio.h>
#include <string.h>
#include <psipc.h>
#include <mpcomm.h>
#include <mpdef.h>
#include <mpprolib.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/comm.c,v 1.2 2004-02-12 09:13:50 mwn Exp $";

/**************************************************************/
/* Function:  MPcomm                                          */
/*                                                            */
/* Parameter: typ      SEND or RECV                           */
/*            len      length of data to send                 */
/*                     length of kommbuffer at recv           */
/*            memchunk chunk size for MPalloc (only recv)     */
/*                                                            */
/* Return:    laenge   effect. data length                    */
/**************************************************************/
#define LENSIZE 11
unsigned long MPcomm(unsigned short int typ, long memchunk)
{
	/* IPC filedescriptor - must be global in DBI and GUI process */
	extern int ipcfd;
	extern COMMOBJ comm;
	extern int (*MPfunction_exit)();

	int fdread, fdwrite;
	char lenbuf[LENSIZE];
	int cret;

	if (ipcfd >= 0)
		{
		fdread  = ipcfd;      /* IPC */
		fdwrite = ipcfd;
		}
	else
		{
		fdread  = 0;          /* Pipe */
		fdwrite = 1;
		}
	(void)memset(lenbuf, (int)NULL, LENSIZE);

	/* Kommunikation */
	if (typ == RECV)
		{
		PSIPCread(fdread, (char *)comm.typ, (size_t)(ANZKOMM*sizeof(unsigned char)));
		PSIPCread(fdread, (char *)lenbuf, (size_t)LENSIZE);
		comm.datalen = atol(lenbuf);

		if (comm.datalen > comm.alloclen)
			comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
			                             memchunk, comm.datalen, sizeof(char));
		if (comm.datalen > 0)
			{
			PSIPCread(fdread, (char *)comm.buffer, (size_t)(comm.datalen*sizeof(char)));
			comm.buffer[comm.datalen] = NULL; /* Ueberschreibe letztes Byte mit NULL */
			}
		else
			comm.buffer[0] = NULL; /* init first byte to NULL if no data avail. */
		}

	else if (typ == SEND)
		{
		int laenge = 0;
		cret = PSIPCwrite(fdwrite, comm.typ, (ANZKOMM*sizeof(unsigned char)));
		sprintf(lenbuf, "%lu\0", comm.datalen);
		cret = PSIPCwrite(fdwrite, lenbuf, LENSIZE);

		if (comm.datalen > 0)
			laenge = PSIPCwrite(fdwrite, comm.buffer, (comm.datalen*sizeof(char)));
		if (laenge == (int)-1)
			{
			if (MPfunction_exit != NULL)
				MPfunction_exit(1);
			exit(1);
			}
		return((unsigned long)laenge);
		}
	return((unsigned long)0);
}
