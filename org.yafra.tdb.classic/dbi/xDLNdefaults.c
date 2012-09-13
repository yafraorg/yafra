/*D***********************************************************
 * Modul:     DBI - DLN
 *            write default entries
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNdefaults.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Write default RES and AKTDETAIL entries
 *            for a DLN
 *            it's only used in ARR book mode
 *
 * In/Out:    arr and rei structur
 * Out:       status
 **************************************************************/
int DLNdefaults(ARRANGEMENT *arr , REISENDER *rei )
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern BUCHUNG bch;
	extern DIENSTLEISTUNG dtg;
	extern RESERVATION res;
	extern unsigned char bm_obj;

	ARR_DLG *Pad;
	AKT_DETAIL aktdet;
	DIENSTLEISTUNG dl;
	AKTIONEN akt;
	DLG_PART tmp_tdl;
	int i;
	int anzahl;
	int id;
	int status = (int)MPOK;
	unsigned char akt_art;

	/* init */
	res.dlt_id    = (int)_UNDEF;
	res.typ_id    = (int)_UNDEF;
	res.kat_id    = (int)_UNDEF;
	res.kont_id   = (int)_UNDEF;
	res.k_kon     = (int)_UNDEF;
	res.b_kon     = (int)_UNDEF;
	res.textid    = (int)_UNDEF;
	res.bid       = bch.bid;
	res.pers_id   = rei->pers_id;
	res.sai_id    = bch.sai_id;
	aktdet.sai_id = bch.sai_id;

	if (bm_obj == (unsigned char)_DIENSTLEISTUNG)
		return(status);

	/* ARRANGEMENT defaults */

	/* check that no entries are there */
	i = MPAPIid_count((int)_REISENDER, (int)_RESERVATION, (char *)rei);
	if (i != (int)EMPTY)
		return(MPE_NOUNIQUEBEZ);

	(void)sprintf(sqlquery, _SEL_ARRDL_ARRPRIO, arr->arr_id, (int)1);
	status=MPAPIdb_sqlquery((int)_ARR_DLG, &sqlmem.buffer, sqlquery, &anzahl,
	                          &sqlmem.datalen, &sqlmem.alloclen);
	Pad = (ARR_DLG *)sqlmem.buffer;
	/* schreibe RESERVATION und AKT_DETAIL pro DLN von Prioritaet 1 */
	for (i=0; i < anzahl; i++)
		{
		res.dl_id = (int)_UNDEF;
		res.dlg_id = Pad[i].dlg_id;
		res.teil = Pad[i].teil;
		res.r_sta = (int)_RES_ENTER;
		status = MPAPIinsertEntry((int)_RESERVATION, (char *)&res, (BEZEICHNUNG *)NULL);

		/* AKT_DETAIL default entries */
		if (status == MPOK)
			{
			dl.dlg_id = res.dlg_id;
			id = MPAPIselectOneId((int)_DIENSTLEISTUNG, res.dlg_id, (char *)&dl);
			if (id != _UNDEF)
				{
				akt.akt_id = dl.akt_id;
				id = MPAPIselectOneId((int)_AKTIONEN, akt.akt_id, (char *)&akt);
				if (id != _UNDEF)
					{                    /* _UNDEF w�rde keine Aktion bedeuten */
					if (akt.a_typ_id == (int)_UNDEF)
						akt_art = MULTIPLEAKT;
					else
						akt_art = SINGLEAKT;

					/* get HOST DLG_PARTS for DIENSTLEISTUNG */
					status = MPAPIselectTDL(dl.dlg_id, &tmp_tdl);
					if (status != (int)MPOK)
						break;

					aktdet.bid = res.bid;
					aktdet.pers_id = res.pers_id;
					aktdet.dl_id = tmp_tdl.dl_id;
					aktdet.dlg_id = res.dlg_id;
					aktdet.teil = res.teil;
					aktdet.z_flag = _AKT_READYTOSTART;
					aktdet.akt_nr = (int)_UNDEF;

					if (akt_art == SINGLEAKT)
						{
						aktdet.akt_id = akt.akt_id;
						aktdet.a_typ_id = akt.a_typ_id;
						aktdet.parentakt = (int)_UNDEF;
						aktdet.ord = (int)1;
						aktdet.file_id = (int)_UNDEF;
						status = MPAPIinsertEntry((int)_AKT_DETAIL, (char *)&aktdet, (BEZEICHNUNG *)NULL);
						}
					else
						status = AKTDwritegroup(&aktdet, akt.akt_id);
					}
				}
			else
				status = (int)MPERROR;
			}
		} /* end of for */

	return( status );
}
