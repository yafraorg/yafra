/*D***********************************************************
 * Modul:     DBI - database delete
 *            HOST_KONT
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONHdelete.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int KONHdelete(void)
{
	extern int sprache;
	extern HOST_KONT hkon;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	int status=(int)MPOK;

	if (hkon.hostkont_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist HKON noch in KONT_DETAIL vorhanden ? */
	if (MPAPIid_count((int)_HOST_KONT, (int)_KONT_DETAIL, (char *)&hkon) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOHKONDEL_KOND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist HKON noch in KONTINGENT vorhanden ? */
	if (MPAPIid_count((int)_HOST_KONT, (int)_KONTINGENT, (char *)&hkon) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOHKONDEL_KON, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_HOST_KONT, (char *)&hkon);
	if ( status == (int)MPOK )
		{
		bez.s_id=sprache;
		bez.typ=(int)_HOST_KONT;
		bez.bez_id=hkon.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_HOST_KONT,
		    (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry(_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (hkon.textid != (int)_UNDEF)
			{
			txt.typ=(int)_HOST_KONT;
			txt.textid=hkon.textid;
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
