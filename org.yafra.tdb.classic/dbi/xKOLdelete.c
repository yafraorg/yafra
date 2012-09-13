/*D***********************************************************
 * Modul:     DBI - database delete
 *            KOLLEKTIV
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOLdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

#define MSG2	(int)20

int KOLdelete(void)
{
	extern KOLLEKTIV kol;
	extern KOMM_DETAIL komd;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;

	if (kol.k_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Is KOLLEKTIV still in BUCHUNG */
	if (MPAPIid_count((int)_KOLLEKTIV, (int)_BUCHUNG, (char *)&kol) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOKOLDEL_BCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Are there any KOMMISSIONEN for this KOLLEKTIV ? */
	if (MPAPIid_count((int)_KOLLEKTIV, (int)_KOMM_DETAIL, (char *)&kol) != (int)EMPTY)
		{
		/* delete KOMM_DETAIL entries of this KOLLEKTIV */
		komd.komm_id = (int)_UNDEF;
		komd.bid = (int)_UNDEF;
		komd.dln_id = (int)_UNDEF;
		komd.kun_id = (int)_UNDEF;
		komd.kol_id = kol.k_id;
		status = MPAPIdeleteEntry((int)_KOMM_DETAIL, (char *)&komd);
		if (status != (int)MPOK)
			{
			UtilMsg((int)MPE_NOKOLDEL_KOM, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	status = MPAPIdeleteEntry((int)_KOLLEKTIV, (char *)&kol);
	if (status == (int)MPOK)
		{
		if (kol.textid != _UNDEF)
			{
			txt.typ=(int)_KOLLEKTIV;
			txt.textid=kol.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
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
