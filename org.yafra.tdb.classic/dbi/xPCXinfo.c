/*D***********************************************************
 * Modul:     DBI - database info                           
 *            look on every image with this info
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xPCXinfo.c,v 1.2 2008-11-02 19:55:35 mwn Exp $

 Log Information:
 $Log: xPCXinfo.c,v $
 Revision 1.2  2008-11-02 19:55:35  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:50  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  18:20:51  18:20:51  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/07/16  00:15:24  00:15:24  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPCXinfo.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int PCXinfo(int len, char *buffer)
{
	extern int sprache;
	extern PCX_FILES pcx;

	int status=(int)MPOK;

	if (pcx.pcx_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	(void)copyTextTo(comm.buffer, pcx.filename, _FILELEN);

	ACTIONTYP = (unsigned char)INFOPCX;

	return(status);
}
