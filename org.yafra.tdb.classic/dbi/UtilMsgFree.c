/*D***********************************************************
 * Modul:     DBI - msg free
 *            free all global messages
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/UtilMsgFree.c,v 1.2 2008-11-02 19:55:36 mwn Exp $

 Log Information:
 $Log: UtilMsgFree.c,v $
 Revision 1.2  2008-11-02 19:55:36  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:13  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  16:12:19  16:12:19  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/09/03  23:45:22  23:45:22  mw (Administrator)
 * new free function
 * 
 * Revision 1.2  93/07/26  00:32:20  00:32:20  mw (Administrator)
 * "no entry"
 * 
 * Revision 1.1  93/07/22  23:59:28  23:59:28  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilMsgFree.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int UtilMsgFree(void)
{
	extern char **sql_message;
	extern char **sys_message;
	extern int sql_maxmessage;
	extern int sys_maxmessage;
	extern MEMOBJ msgmem;

	int i;
	int status = MPOK;

	MPfree((void *)msgmem.buffer);
	msgmem.datalen = msgmem.alloclen = 0;

	if (sql_message != NULL && sql_maxmessage > 0)
		{
		MPfreearray(sql_message, (sql_maxmessage+1));
		sql_message = NULL;
		sql_maxmessage = 0;
		}
	else
		status = MPW_NOFREE;

	if (sys_message != NULL && sys_maxmessage > 0)
		{
		MPfreearray(sys_message, (sys_maxmessage+1));
		sys_message = NULL;
		sys_maxmessage = 0;
		}
	else
		status = MPW_NOFREE;

	return(status);
}
