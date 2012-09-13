/*D***********************************************************
 * Modul:     DBI - database delete
 *            W�hrung
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xWHRdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $

 Log Information:
 $Log: xWHRdelete.c,v $
 Revision 1.2  2008-11-02 19:55:36  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:37:16  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  18:21:13  18:21:13  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/05/18  11:52:43  11:52:43  mw (Administrator)
 * "bug fix in delete"
 * 
 * Revision 1.2  93/03/30  20:37:55  20:37:55  mw ()
 * "maintenance"
 * 
 * Revision 1.1  93/01/18  16:06:04  16:06:04  mw ()
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xWHRdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int WHRdelete(void)
{
	extern WAEHRUNG whr;
	extern BEZEICHNUNG bez;
	extern int sprache;

	char message[RECLAENGE];
	int status = MPOK;

	if (whr.whr_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_WAEHRUNG, (char *)&whr);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_AKTIONS_TYP;
		bez.bez_id=whr.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_WAEHRUNG, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
