/*D***********************************************************
 * Modul:     DBI - database delete                           
 *            Arrangements
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xARRdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int ARRdelete(void)
{
	extern ARRANGEMENT arr;
	extern ARR_DLG ad;
	extern BEZEICHNUNG bez;
	extern MP_ARRKOM arrkom;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;

	if (arr.arr_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist ARR noch in BCH vorhanden ? */
	if (MPAPIid_count((int)_ARRANGEMENT, (int)_BUCHUNG, (char *)&arr) != (int)EMPTY)
		{
		UtilMsg((int)MPW_ARRSTILLINBCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist ARR noch in ARR-DL vorhanden ? */
	if (MPAPIid_count((int)_ARRANGEMENT, (int)_ARR_DLG, (char *)&arr) != (int)EMPTY)
		{
		UtilMsg((int)MPW_ARRDLGPRESENT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* delete ARRKOMM entries */
	arrkom.arr_id = arr.arr_id;
	arrkom.komm_id = (int)_UNDEF;
	(void)MPAPIdeleteEntry((int)_MP_ARRKOM, (char *)&arrkom);

	/* delete ARR_DLG entries */
	ad.arr_id = arr.arr_id;
	ad.dlg_id = (int)_UNDEF;
	(void)MPAPIdeleteEntry((int)_ARR_DLG, (char *)&ad);

	/* delete ARRANGEMENT */
	status=MPAPIdeleteEntry((int)_ARRANGEMENT, (char *)&arr);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_ARRANGEMENT;
		bez.bez_id=arr.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_ARRANGEMENT, (char *)&bez) == (int)EMPTY)
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
