/*D***********************************************************
 * Modul:     DBI - utilities
 *            make an immediat call to the GUI as a question
 *            with choices yes or no
 * Return:    True - yes  /  False - no
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/UtilImmediatCall.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: UtilImmediatCall.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:09  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  16:12:16  16:12:16  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/07/07  09:19:51  09:19:51  mw (Administrator)
 * "add COMMSTAT"
 * 
 * Revision 1.2  93/01/03  20:48:13  20:48:13  mw (Administrator)
 * "backup and restore old comm.typ"
 * 
 * Revision 1.1  92/12/31  11:06:30  11:06:30  mw ()
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilImmediatCall.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int UtilImmediatCall(char *buffer)
{
	COMMOBJ oldcomm;

	/* BACKUP old COMM */
	oldcomm.typ[0] = COMMTYP;
	oldcomm.typ[1] = ACTIONTYP;
	oldcomm.typ[2] = MENUNR;
	oldcomm.typ[3] = FELDNR;

	COMMSTAT  = MESSAGEOK;
	COMMTYP   = (unsigned char)IMMEDIATCALL;
	ACTIONTYP = NULL;
	MENUNR    = NULL;
	FELDNR    = NULL;

	comm.datalen = (unsigned long)strlen(buffer);
	if (comm.datalen > comm.alloclen)
		comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
	                    DEFMEMCHUNK, comm.datalen, sizeof(char));

	strcpy(comm.buffer, buffer);
	(void)MPcomm(SEND, DEFMEMCHUNK);
	(void)MPcomm(RECV, DEFMEMCHUNK);

	/* RESTORE old COMM */
	COMMSTAT  = MESSAGEOK;
	COMMTYP   = oldcomm.typ[0];
	ACTIONTYP = oldcomm.typ[1];
	MENUNR    = oldcomm.typ[2];
	FELDNR    = oldcomm.typ[3];

	return((int)comm.buffer[0]);
}
