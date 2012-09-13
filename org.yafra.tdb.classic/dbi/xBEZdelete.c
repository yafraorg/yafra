/*D***********************************************************
 * Modul:     DBI - database delete
 *            BEZEICHNUNG
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xBEZdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $

 Log Information:
 $Log: xBEZdelete.c,v $
 Revision 1.2  2008-11-02 19:55:36  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:49  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  16:34:27  16:34:27  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/03/30  19:27:45  19:27:45  mw (Administrator)
 * "maintenance"
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xBEZdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

#define MSG2	(int)20
#define MSG3	(int)128

int BEZdelete(void)
{
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if(bez.bez_id != (int)_UNDEF) {
		status=MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez);

		if(status != (int)MPOK) {
			(void)find_text_nr((int)MSG3, message);
			xSqlMessage(message);
			status=(int)MPERROR;
		}
	} else {
		(void)find_text_nr((int)MSG2, message);
		xSqlMessage(message);
		status=(int)MPERROR;
	}

	return(status);
}
