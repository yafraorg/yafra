/*D***********************************************************
 * Modul:     DBI - database delete
 *            Ort
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xORTdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: xORTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:33  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  18:20:46  18:20:46  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/05/18  11:53:02  11:53:02  mw (Administrator)
 * "bug fix in delete"
 * 
 * Revision 1.2  93/03/30  20:19:03  20:19:03  mw ()
 * "maintenance"
 * 
 * Revision 1.1  93/01/18  16:06:24  16:06:24  mw ()
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xORTdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int ORTdelete(void)
{
	extern ORT ort;
	extern BEZEICHNUNG bez;
	extern int sprache;

	char message[RECLAENGE];
	int status = MPOK;

	if (ort.ort_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_ORT, (char *)&ort);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_AKTIONS_TYP;
		bez.bez_id=ort.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_ORT, (char *)&bez) == (int)EMPTY)
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
