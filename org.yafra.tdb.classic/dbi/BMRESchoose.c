/*D***********************************************************
 * Modul:     DBI - booking modul
 *            send choice of RES's in DLN in BCH
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/BMRESchoose.c,v 1.2 2008-11-02 19:55:36 mwn Exp $

 Log Information:
 $Log: BMRESchoose.c,v $
 Revision 1.2  2008-11-02 19:55:36  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:33:11  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  15:58:53  15:58:53  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/09/09  16:32:27  16:32:27  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMRESchoose.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int BMRESchoose(int len, char *buffer)
{
	extern BUCHUNG bch;
	extern REISENDER rei;

	int status = (int)MPOK;

	return(status);
}

