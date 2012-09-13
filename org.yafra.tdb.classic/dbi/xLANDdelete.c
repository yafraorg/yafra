/*D***********************************************************
 * Modul:     DBI - database delete
 *            Land
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xLANDdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $

 Log Information:
 $Log: xLANDdelete.c,v $
 Revision 1.2  2008-11-02 19:55:38  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:24  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  18:20:41  18:20:41  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/05/18  11:52:21  11:52:21  mw (Administrator)
 * "bug fix in delete"
 * 
 * Revision 1.2  93/03/30  20:14:57  20:14:57  mw ()
 * "maintenance"
 * 
 * Revision 1.1  93/01/18  16:06:19  16:06:19  mw ()
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLANDdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int LANDdelete(void)
{
	extern LAND land;
	extern BEZEICHNUNG bez;
	extern int sprache;

	char message[RECLAENGE];
	int status = MPOK;

	if (land.land_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* check up here if there are still some ORT or WHR present */

	status=MPAPIdeleteEntry((int)_LAND, (char *)&land);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_AKTIONS_TYP;
		bez.bez_id=land.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_LAND, (char *)&bez) == (int)EMPTY)
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
