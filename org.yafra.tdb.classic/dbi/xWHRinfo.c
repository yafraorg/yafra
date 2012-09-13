/*D***********************************************************
 * Modul:     DBI - database info                           
 *            W�hrungsinformationen
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xWHRinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $

 Log Information:
 $Log: xWHRinfo.c,v $
 Revision 1.2  2008-11-02 19:55:38  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:37:16  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  18:21:17  18:21:17  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/01/18  16:06:06  16:06:06  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xWHRinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int WHRinfo(char *buffer )
{
	extern int sprache;
	extern MEMOBJ sqlmem;
	extern char glob_bez_whr[];

	char query[RECLAENGE];
	char message[RECLAENGE];
	char tmp_buffer[RECLAENGE];
	int status=(int)MPOK;
	int i, anzahl, anzchar;

	return(status);
}
