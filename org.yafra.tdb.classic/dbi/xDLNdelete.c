/*D***********************************************************
 * Modul:     DBI - database delete
 *            DLN Dienstleistungsnehmer
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNdelete.c,v 1.3 2008-11-02 19:55:41 mwn Exp $";

int DLNdelete(void)
{
	extern BCH_DLN bd;
	extern RESERVATION res;
	extern REISENDER rei;
	extern PERSADR adr;
	extern PERSONEN pers;
	extern TEXTE txt;

	AKT_DETAIL ad;
	KOMM_DETAIL komd;
	int id;
	int status=(int)MPOK;

	/* check if ID is set */
	if (rei.pers_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* check if DLN is in a KOLLEKTIV */
	if (MPAPIid_count((int)_REISENDER, (int)_KOLLEKTIV, (char *)&rei) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLNDEL_KOL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* set ID's */
	komd.bid = ad.bid = res.bid = bd.bid;
	adr.pers_id = komd.dln_id = ad.pers_id = res.pers_id = bd.dln_id = rei.pers_id;
	ad.teil = res.teil = (int)_UNDEF;

	/* get PERSONEN entry for textid and validation */
	id = MPAPIselectOneId((int)_PERSONEN, rei.pers_id, (char *)&pers);
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* DELETE */

	/* delete BCHDLN entries */
	status = MPAPIdeleteEntry((int)_BCH_DLN, (char *)&bd);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* delete KOMMISSIONS DETAIL entries for this DLN in this BCH */
	komd.komm_id = (int)_UNDEF;
	komd.kun_id = (int)_UNDEF;
	komd.kol_id = (int)_UNDEF;
	status = MPAPIdeleteEntry((int)_KOMM_DETAIL, (char *)&komd);
	if (status != (int)MPOK)
		{
		if (status == (int)MPE_NOINSUPDDEL)
			status = (int)MPOK; /* if there are no KOMD entries, it's ok */
		else
			{
			UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	/* delete RES entries */
	status = MPAPIdeleteEntry((int)_RESERVATION, (char *)&res);
	if (status != (int)MPOK)
		{
		if (status == (int)MPE_NOINSUPDDEL)
			status = (int)MPOK; /* if there are no RES entries, it's ok */
		else
			{
			UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	/* delete AKTD entries */
	status = MPAPIdeleteEntry((int)_AKT_DETAIL, (char *)&ad);
	if (status != (int)MPOK)
		{
		if (status == (int)MPE_NOINSUPDDEL)
			status = (int)MPOK; /* if there are no AKTDET entries, it's also ok */
		else
			{
			UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	/* delete REISENDER entry with TEXTE */
	status = MPAPIdeleteEntry((int)_REISENDER, (char *)&rei);
	if (status == (int)MPOK)
		{
		if (rei.mutters_id != (int)_UNDEF)
			{
			txt.typ=(int)_REISENDER;
			txt.textid=rei.mutters_id;
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
		return((int)MPERROR);
		}

	/* delete PERSADR entry */
	status = MPAPIdeleteEntry((int)_PERSADR, (char *)&adr);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		}

	/* last but not least - delete PERSONEN entry with TEXTE */
	status=MPAPIdeleteEntry((int)_PERSONEN, (char *)&pers);
	if (status == (int)MPOK)
		{
		if (pers.textid != (int)_UNDEF)
			{
			txt.typ=(int)_PERSONEN;
			txt.textid=pers.textid;
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
