/*D***********************************************************
 * Modul:     DBI - database delete
 *            KONTINGENT
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int KONdelete(void)
{
	extern int sprache;
	extern KONTINGENT kon;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	int status=(int)MPOK;

	if (kon.kont_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist KON noch in KONT_DETAIL vorhanden ? */
	if (MPAPIid_count((int)_KONTINGENT, (int)_KONT_DETAIL, (char *)&kon) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOKONDEL_KOND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist KON noch in PREIS vorhanden ? */
	if (MPAPIid_count((int)_KONTINGENT, (int)_PREIS, (char *)&kon) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOKONDEL_PRE, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist KON noch in RESERVATION vorhanden ? */
	if (MPAPIid_count((int)_KONTINGENT, (int)_RESERVATION, (char *)&kon) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOKONDEL_RES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_KONTINGENT, (char *)&kon);
	if ( status == (int)MPOK )
		{
		bez.s_id=sprache;
		bez.typ=(int)_KONTINGENT;
		bez.bez_id=kon.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_KONTINGENT,
		    (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry(_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (kon.textid != (int)_UNDEF)
			{
			txt.typ=(int)_KONTINGENT;
			txt.textid=kon.textid;
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

	return( status );
}
