/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistung
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

static int DLdeleteDL_DLPART(DIENSTLEISTUNG *);

int DLdelete(void)
{
	extern DIENSTLEISTUNG dtg;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	extern int sprache;

	int status=(int)MPOK;

	if (dtg.dlg_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch in RES vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_RESERVATION, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_RES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch in AKT_DETAIL vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_AKT_DETAIL, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_AKTDET, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch im PREIS vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_PREIS, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_PRE, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch in KOMMISSION vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_KOMMISSION, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_KOM, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch im HOST_KONT vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_HOST_KONT, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_KON, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch im ARR_DL vorhanden ? */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_ARR_DLG, (char *)&dtg) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLDEL_ARRDL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DL noch in DL_DLPART vorhanden, so loesche alle */
	if (MPAPIid_count((int)_DIENSTLEISTUNG, (int)_DLG_DLG, (char *)&dtg) != (int)EMPTY)
		{
		status = DLdeleteDL_DLPART(&dtg);
		if (status != MPOK)
			{
			UtilMsg((int)MPE_NODLDEL_DLPART, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	status=MPAPIdeleteEntry((int)_DIENSTLEISTUNG, (char *)&dtg);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_DIENSTLEISTUNG;
		bez.bez_id=dtg.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_DIENSTLEISTUNG,
		     (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry(_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (dtg.textid != _UNDEF)
			{
			txt.typ=(int)_DIENSTLEISTUNG;
			txt.textid=dtg.textid;
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

/*************************************************************
 * Function:  DLdeleteDL_DLPART
 * Typ:       private for DLdelete
 * Desc:      delete all DL - DLPARTS relations
 *************************************************************/
static int DLdeleteDL_DLPART(DIENSTLEISTUNG *localdl)
{
	DLG_DLG dd;
	int status = MPOK;

	/* L�sche nun DLT */
	dd.dlg_id = localdl->dlg_id;
	dd.dl_id  = (int)_UNDEF;
	dd.ord    = (int)_UNDEF;
	status=MPAPIdeleteEntry((int)_DLG_DLG, (char *)&dd);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
