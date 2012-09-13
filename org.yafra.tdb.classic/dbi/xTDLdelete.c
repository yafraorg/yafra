/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungsteile
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTDLdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

static int TDLdeleteOneEntry(DLG_PART *);

int DLGdelete(void)
{
	extern MEMOBJ sqlmem;
	extern DLG_PART dlg;

	DLG_PART *dlgptr;
	int status=(int)MPOK;
	int anzahl, i;
	char query[_QUERYLEN];

	if (dlg.dl_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist TDL noch in RES vorhanden ? */
	if (MPAPIid_count((int)_DLG_PART, (int)_RESERVATION, (char *)&dlg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOTDLDEL_RES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist TDL noch in AKTDETAIL vorhanden ? */
	if (MPAPIid_count((int)_DLG_PART, (int)_AKT_DETAIL, (char *)&dlg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOTDLDEL_AKTDET, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist TDL noch in DL_TDL vorhanden ? */
	if (MPAPIid_count((int)_DLG_PART, (int)_DLG_DLG, (char *)&dlg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOTDLDEL_DL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist TDL noch in TDL vorhanden ? */
	if (MPAPIid_count((int)_DLG_PART, (int)_DLG_PART, (char *)&dlg) != (int)EMPTY)
		{
		sprintf(query, _SEL_DLG_ALLFROMHOST, dlg.dl_id);
		status = MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != MPOK)
			{
			UtilMsg((int)MPE_NOTDLDEL_TDL, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		if (anzahl > 0)
			{
			dlgptr = (DLG_PART *)sqlmem.buffer;
			for (i = (anzahl - 1); i > -1 && status == MPOK; i--)
				status = TDLdeleteOneEntry(&dlgptr[i]);
			if (status != MPOK)
				{
				UtilMsg((int)MPE_NOTDLDEL_TDL, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		}

	status = TDLdeleteOneEntry(&dlg);

	return(status);
}


/*************************************************************
 * Function:  TDLdeleteOneEntry
 * Typ:       private for DLGdelete
 * Desc:      delete one TDL with TXT and BEZ
 *************************************************************/
static int TDLdeleteOneEntry(DLG_PART *localtdl)
{
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;
	KAPA localkapa;
	int status = MPOK;

	/* L�sche nun KAPA der TDL */
	localkapa.kat_id = (int)_UNDEF;
	localkapa.tdl_id = localtdl->dl_id;
	(void)MPAPIdeleteEntry((int)_KAPA, (char *)&localkapa);

	/* L�sche nun TDL */
	status=MPAPIdeleteEntry((int)_DLG_PART, (char *)localtdl);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_DLG_PART;
		bez.bez_id=localtdl->bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_DLG_PART,
		    (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (localtdl->textid != _UNDEF)
			{
			txt.typ=(int)_DLG_PART;
			txt.textid=localtdl->textid;
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
