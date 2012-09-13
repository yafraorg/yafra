/*D***********************************************************
 * modul:     DBI - AKTTIONS-DETAIL
 *            AKTDwrite
 *            AKTDwritegroup
 *
 * (c):       yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTDwrite.c,v 1.4 2009-01-02 21:30:21 mwn Exp $";

/*F***********************************************************
 * function:  Write AKT detail
 *            in INS mode delete default entries and write new ones
 *            in UPD mode do nothing
 *            in DEL mode delete all entries
 *
 * paras:     BCH id, DLN id, DL id, RES data
 *            ACTIONTYP must be right set
 * return:    status
 **************************************************************/
int AKTDwrite(int bid, int uid, int dlid, RESERVATION *newres)
{
	extern MEMOBJ sqlmem;

	extern BUCHUNG bch;
	extern DIENSTLEISTUNG dtg;
	extern RESERVATION res;
	extern unsigned char bm_obj;

	AKT_DETAIL *adptr = NULL;
	AKT_DETAIL writeaktdet;
	DIENSTLEISTUNG dl;
	DLG_PART *dlpart = NULL;
	AKTIONEN akt;
	char query[_QUERYLEN];
	int status = (int)MPOK;
	int adcnt = (int)0;
	int i;
	int id;
	int dlpartcnt;
	unsigned char akt_art = MULTIPLEAKT;

	/* if bm_obj is ARR then let it be because of DLNdefaults */
	/* did already this job ! */
/*	if (bm_obj == _ARRANGEMENT)
		return((int)MPOK);
*/

	/* check if buffer exists */
	if (newres == NULL)
		return((int)MPERROR);

	/* init */
	writeaktdet.bid    = bid;
	writeaktdet.pers_id    = uid;
	writeaktdet.dlg_id = dlid;
	writeaktdet.sai_id = newres->sai_id;
	writeaktdet.parentakt = (int)_UNDEF;
	writeaktdet.ord = (int)1;
	writeaktdet.exec_dat = (int)0;
	writeaktdet.akt_nr = (int)_UNDEF;

	/* get typ of AKTION (single/group) */
	dl.dlg_id = dlid;
	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, dlid, (char *)&dl);
	if (id != (int)_UNDEF)
		{
		akt.akt_id = dl.akt_id;
		id = MPAPIselectOneId((int)_AKTIONEN, akt.akt_id, (char *)&akt);
		if (id != (int)_UNDEF)
			{                    /* _UNDEF w�rde keine Aktion bedeuten */
			if (akt.a_typ_id == (int)_UNDEF)
				akt_art = MULTIPLEAKT;
			else
				akt_art = SINGLEAKT;
			}
		}

	/* read all existing aktdet for bid, uid, dl */
	/* if nothing here then make new entries */
	/* if something here match it, delete old entries */
	/* and insert new entries */

	/* manage already entered reservations */
	(void)sprintf(query, _SEL_AKTDET_BCH_UID_DL, bid, uid, dlid);
	status=MPAPIdb_sqlquery((int)_AKT_DETAIL, &sqlmem.buffer,
	         query, &adcnt, &sqlmem.datalen, &sqlmem.alloclen);
	adptr = (AKT_DETAIL *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	if (adcnt > 0)
		{
		/* in UPD mode we let it be */
		/* in DEL mode we delete all aktionsdetail entries */
		if (ACTIONTYP == (unsigned char)MPDELETE)
			{
			/* delete all old entries */
			status = MPAPIdeleteEntry((int)_AKT_DETAIL, (char *)&adptr[0]);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		}

	/* write new entries only in INSERT mode - in DEL/UPD let it be */
	if ((ACTIONTYP == (unsigned char)INSERT && bm_obj != (int)_ARRANGEMENT) ||
	     adcnt == (int)0)
		{
		(void)sprintf(query, _SEL_HDLG_DL, dlid);
		status=MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer,
	         query, &dlpartcnt, &sqlmem.datalen, &sqlmem.alloclen);
		dlpart = (DLG_PART *)sqlmem.buffer;
		if (status != (int)MPOK || dlpartcnt < 1)
			{
			UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}

		for (i=0; i<dlpartcnt && status == (int)MPOK; i++)
			{
			writeaktdet.dl_id = dlpart[i].dl_id;
			writeaktdet.z_flag = _AKT_READYTOSTART;
			writeaktdet.akt_nr = (int)_UNDEF;
			writeaktdet.teil = newres->teil;          /* get same TEIL as in RES */
			writeaktdet.file_id = (int)_UNDEF;
			if (akt_art == SINGLEAKT)
				{
				writeaktdet.akt_id = akt.akt_id;
				writeaktdet.a_typ_id = akt.a_typ_id;
				status = MPAPIinsertEntry((int)_AKT_DETAIL, (char *)&writeaktdet, (BEZEICHNUNG *)NULL);
				}
			else
				{
				status = AKTDwritegroup(&writeaktdet, akt.akt_id);
				if (status != (int)MPOK)
					UtilMsg((int)MPE_NOAKTFORDLDLA, MSGTYP_ERROR, NULL);
				}
			}
		}

	return( status );
}




/*F***********************************************************
 * function:  Write AKT detail for a group of actions
 *
 * paras:     AKT-DETAIL settings, parent AKT
 * return:    status
 **************************************************************/

#define _SEL_AKTFROMPARENT "SELECT * FROM TDBADMIN.AKTIONSGRP \
	WHERE PARENTAKT = %d ORDER BY ORD;"

int AKTDwritegroup(AKT_DETAIL *aktdet, int parent)
{
	extern AKTIONEN akt;

	char query[RECLAENGE];
	int i;
	int status=(int)MPOK;
	int anzahl;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	AKTIONSGRP *aktgrp = NULL;

	(void)sprintf(query, _SEL_AKTFROMPARENT, parent);
	status = MPAPIdb_sqlquery((int)_AKTIONSGRP, (char **)&aktgrp, query,
	                &anzahl, &dlen, &alen);
	if (anzahl > (int)0 && status == (int)MPOK)
		{
		for (i=0; i<anzahl && status == (int)MPOK; i++)
			{
			akt.akt_id = aktgrp[i].childakt;
			status = MPAPIselectOneId((int)_AKTIONEN, (int)akt.akt_id,
			                     (char *)&akt);
			if (status == (int)_UNDEF)
				break;
			else
				{
				aktdet->parentakt = parent;
				aktdet->akt_id = akt.akt_id;
				aktdet->a_typ_id = akt.a_typ_id;
				aktdet->ord = aktgrp[i].ord;
				aktdet->file_id = (int)_UNDEF;
				status = MPAPIinsertEntry((int)_AKT_DETAIL, (char *)aktdet,
				                     (BEZEICHNUNG *)NULL);
				}
			}
		}
	else
		status = (int)MPERROR;

	MPfree((char *)aktgrp);
	return(status);
}
