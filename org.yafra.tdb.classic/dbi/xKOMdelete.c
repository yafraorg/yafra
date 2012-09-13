/*D***********************************************************
 * Modul:     DBI - database delete
 *            KOMMISSION
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";
static int DeleteKommdet(KOMMISSION *);

int KOMdelete(void)
{
	extern KOMMISSION kom;
	extern MP_ARRKOM arrkom;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	/* pruefe ob eine Kommission aktiv ist */
	if (kom.komm_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* pruefe Verknuepfungen zu Kommissions Detail */
	if (MPAPIid_count((int)_KOMMISSION, (int)_KOMM_DETAIL, (char *)&kom) != (int)EMPTY)
		{
		UtilMsgGet((int)MPW_KOMMDET_DEL, MSGTYP_WARNING, message);
		status = UtilImmediatCall(message);
		if (status == (int)TRUE)
			{
			status = DeleteKommdet(&kom);
			if (status != MPOK)
				{
				UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		else
			return((int)MPOK);
		}

	/* l�sche ARRKOM der KOMM */
	arrkom.arr_id = (int)_UNDEF;
	arrkom.komm_id = kom.komm_id;
	(void)MPAPIdeleteEntry((int)_MP_ARRKOM, (char *)&arrkom);

	status=MPAPIdeleteEntry((int)_KOMMISSION, (char *)&kom);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_KOMMISSION;
		bez.bez_id=kom.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_KOMMISSION, (char *)&bez) == (int)EMPTY)
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

static int DeleteKommdet(KOMMISSION *komm)
{
	int status = MPOK;
	int anzahl = 0;
	int i;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	char query[RECLAENGE];
	KOMM_DETAIL *kommdet = NULL;

	(void)sprintf(query, _SEL_KOMMDET_KOMM, komm->komm_id);
	status=MPAPIdb_sqlquery((int)_KOMM_DETAIL, (char **)&kommdet, query, &anzahl,
		                      &dlen, &alen);
	if (status == MPOK && anzahl > 0)
		{
		for (i=0; i < anzahl && status == MPOK; i++)
			status=MPAPIdeleteEntry((int)_KOMM_DETAIL, (char *)&kommdet[i]);
		}
	return(status);
}
