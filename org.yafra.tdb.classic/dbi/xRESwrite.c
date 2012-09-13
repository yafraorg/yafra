/*D***********************************************************
 * Modul:     DBI - RESERVATION
 *            write an entry
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpsqlupd.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xRESwrite.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

/*F***********************************************************
 * Function:  Write RES
 *            in INS mode delete default entries and write new ones
 *            in UPD mode change fields KAT/DLT/KONT/RESSTA/DAT
 *            in DEL mode delete all entries
 *
 * In/Out:    BCH id, DLN id, DL id, TDL count and ids, RES data
 *            ACTIONTYP must be set right
 * Out:       status
 **************************************************************/
int RESwrite(int bid, int uid, int dlid, int tdlcnt,
             int *tdlids, RESERVATION *newres)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int DebugFlag;
	extern unsigned char bm_obj;
	extern unsigned int  bm_dlncnt;  /* num. of dln to book in sequence */
	                                 /* controlled by BMRESinput()      */
	extern ARRANGEMENT arr;
	extern DLG_PART dlg;
	extern KONTINGENT kon;
	extern TEXTE txt;
	extern int glob_teil; /* ARR part no of DL */

	RESERVATION writeres;
	RESERVATION *reservation;
	DLG_DLG *dldlg;
	ARR_DLG arrdl;
	AKT_DETAIL aktdet;
	KONT_DETAIL aKd;
	KATEGORIE reskat;
	DIENST_TRAEGER resdlt;
	char query[_QUERYLEN];
	char message[_RECORDLEN];
	char konbez[_RECORDLEN];
	char format[_RECORDLEN];
	int status = (int)MPOK;
	int cret;
	int rescnt, dlpartcnt;
	int i;
	int id;
	int space;
	int dltbchid;
	int dltkontid;
	int countdln;
	int set_tdl_undef_flag;
	int busyvalue;

	/* fucking memory job */
	if (newres == NULL)
		return((int)MPERROR);

	/* check up bid */
	if (bid < 1)
		{
		UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* init */
	space = 1;
	writeres.bid = bid;
	writeres.pers_id = uid;
	txt.typ = (int)_RESERVATION;
	txt.s_id = sprache;

	/* get host TDL from DL */
	id = MPAPIselectTDL(dlid, &dlg);

	/* set init TEIL number */
	writeres.teil = MPAPIid_max((int)_RESERVATION, (int)_ORD, (char *)&writeres);
	writeres.teil = writeres.teil + 1;
	if (writeres.teil < 1)
		writeres.teil = 1;

	/* if it's an ARRANGEMENT booking and the DIENSTLEISTUNG entered is */
	/* an other priotiry then the already entered, delete the old */
	/* priority first here */
	if (bm_obj == (unsigned char)_ARRANGEMENT)
		{
		arrdl.teil = (int)_UNDEF;
		arrdl.arr_id = arr.arr_id;
		arrdl.dlg_id = dlid;
		/* -2 means we don't know the TEIL (part) no of the DL in the ARR */
		cret = MPAPIselectOneId((int)_ARR_DLG, (int)-2, (char *)&arrdl);
		if (cret == (int)_UNDEF)
			{
			/* we found more then 1 DL with different TEIL */
			if (glob_teil != (int)_UNDEF)
				arrdl.teil = glob_teil; /* use the TEIL from the last selection BMRESsend() */
			else
				{
				/* we don't have the TEIL from last selection - exit with ERROR - user has to try */
				/* the selection again */
				UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		writeres.teil = arrdl.teil;

		/* get all TEIL-reservations to check priority */
		(void)sprintf(query, _SEL_RES_BCHDLN_TEIL, bid, uid, writeres.teil);
		status=MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer,
		         query, &rescnt, &sqlmem.datalen, &sqlmem.alloclen);
		reservation = (RESERVATION *)sqlmem.buffer;
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		if (rescnt > 0)
			{
			/* delete RES + AKT_DETAIL entry if it is another priority */
			if (reservation[0].dlg_id != dlid)
				{
				status = MPAPIdeleteEntry((int)_RESERVATION, (char *)&reservation[0]);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				/* delete TEXTE */
				txt.textid = reservation[0].textid;
				if (txt.textid > 0)
					{
					cret = MPAPIdeleteEntry((int)_TEXTE, (char *)&txt);
					if (cret != (int)MPOK && DebugFlag)
						MPsyslog(_LOGMP, MPDEBUG, "Konnte Reservationstext nicht loeschen");
					}
				aktdet.bid = reservation[0].bid;
				aktdet.pers_id = reservation[0].pers_id;
				aktdet.teil = reservation[0].teil;
				status = MPAPIdeleteEntry((int)_AKT_DETAIL, (char *)&aktdet);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				/* delete old kapa entry for this one if possilbe */
				if (reservation[0].kat_id != (int)_UNDEF && dlg.dl_id != (int)_UNDEF)
					{
					(void)sprintf(query, _UPD_KAPA_DELONE, dlg.dl_id, reservation[0].kat_id);
					status = MPAPIdb_sqlcommand(query, &i);
					if (status != (int)MPOK)
						{
						UtilMsg(status, MSGTYP_DBERROR, NULL);
						return((int)MPERROR);
						}
					}
				}
			}
		}

	/* hole alle Eintraege mit dlid und mache delete und insert */
	/* falls kein eintrag vorhanden */

	/* read already entered reservations (if there are any) and delete */
	/* them. If there are no entries, it's an INSERT of a new TEIL */
	(void)sprintf(query, _SEL_RES_BCHDLN_DL, bid, uid, dlid);
	status=MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer,
	         query, &rescnt, &sqlmem.datalen, &sqlmem.alloclen);
	reservation = (RESERVATION *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	if (rescnt > 0) /* that means something is already here with this dlid */
		{
		/* MPAPIdeleteEntry deletes all RES on a BCH - DLN - DL */
		writeres.teil = reservation[0].teil; /* take values of the first found */
		status = MPAPIdeleteEntry((int)_RESERVATION, (char *)&reservation[0]);
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		/* delete TEXTE */
		txt.textid = reservation[0].textid;
		if (txt.textid > 0)
			{
			cret = MPAPIdeleteEntry((int)_TEXTE, (char *)&txt);
			if (cret != (int)MPOK && DebugFlag)
				MPsyslog(_LOGMP, MPDEBUG, "Konnte Reservationstext nicht loeschen");
			}
		/* if it's a KONTINGENT booking and it's a KATEGORIE KONTINGENT, */
		/* decrement FREE field in KONT_DETAIL table */
		if (reservation[0].kont_id != (int)_UNDEF && reservation[0].kat_id != (int)_UNDEF)
			{
			/* look if there is a KONTINGENT with this KAT and/or DLT */

			/* decrement busy counter of KONT_DETAIL */
			(void)sprintf(query, _UPD_KOND_DELONE, reservation[0].kont_id, reservation[0].kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		/* manage KAPA table */
		if (ACTIONTYP == (unsigned char)MPDELETE)
			{
			if (reservation[0].kat_id != (int)_UNDEF && dlg.dl_id != (int)_UNDEF)
				{
				(void)sprintf(query, _UPD_KAPA_DELONE, dlg.dl_id, reservation[0].kat_id);
				status = MPAPIdb_sqlcommand(query, &i);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				}
			}
		}

	/* if upd or ins do it now, else we deleted already everything ! */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		/* init new reservation */
		writeres.dlg_id = dlid;
		writeres.kont_id = newres->kont_id;
		writeres.a_zeit = newres->a_zeit;
		writeres.e_zeit = newres->e_zeit;
		writeres.r_sta = newres->r_sta;
		writeres.sai_id = newres->sai_id;
		writeres.k_kon = newres->k_kon;
		writeres.b_kon = newres->b_kon;
		writeres.dlt_id = newres->dlt_id;
		writeres.kat_id = newres->kat_id;
		writeres.typ_id = newres->typ_id;
		writeres.textid = newres->textid;

		/* check the selected DIENST_TRAEGER and set related values if needed */
		if (writeres.dlt_id != (int)_UNDEF)
			{
			(void)MPAPIselectOneId((int)_DIENST_TRAEGER, newres->dlt_id, (char *)&resdlt);

			/* the booked category is important for the price */
			if (writeres.kat_id == (int)_UNDEF)
				writeres.kat_id = resdlt.kat_id;

			/* check if enough room to book count DLN to DLT */
			status = DLTnum_of_dln(writeres.dlt_id, &space);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			if (bm_dlncnt > space)
				{
				UtilMsgGet((int)MPE_DLTSPACE, MSGTYP_ERROR, format);
				sprintf(message, format, space, bm_dlncnt);
				UtilMsgWrite(message);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = (int)MPOK;
				else
					return((int)MPERROR);

				/*return((int)MPERROR);*/
				}

			/* check if DLT is realy free */
			status = DLTfree(writeres.dlt_id, writeres.dlg_id, (int)_UNDEF,
			       writeres.kont_id, (time_t)writeres.a_zeit,
			       &countdln, &dltbchid, &dltkontid);
			if (status != (int)MPOK)
				return((int)MPERROR);   /* msg handling is done by function */
			if (countdln > 0 && writeres.bid != dltbchid)
				{
				/* DLT is not free - dltbchid are on this DLT with countdln DLN */
				UtilMsgGet((int)MPE_DLTISNOTFREE, MSGTYP_ERROR, format);
				sprintf(message, format, dltbchid, countdln);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = (int)MPOK;
				else
					return((int)MPERROR);
				}
			if (dltkontid > 0)
				{
				/* DLT is busy by a KONTINGENT */
				(void)MPAPIselectOneId((int)_KONTINGENT, dltkontid, (char *)&kon);
				(void)SelectBez((int)_KONTINGENT, sprache, kon.bez_id, konbez);
				UtilMsgGet((int)MPE_BUSYBYKON, MSGTYP_ERROR, format);
				sprintf(message, format, konbez);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = (int)MPOK;
				else
					return((int)MPERROR);
				}
			}

		/* check reservation typ */
		switch(dlg.res_f)
			{
			case (int)_RES_IMPOSSIBLE:
				UtilMsg((int)MPE_RESIMPOSSIBLE, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				break;
			case (int)_RES_BOOLEAN:
			case (int)_RES_STATIC:
				if (writeres.a_zeit > 0 || writeres.e_zeit > 0)
					{
					UtilMsg((int)MPE_NORESDAT, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				break;
			case (int)_RES_DYNAMIC:
				if (writeres.a_zeit < 1 || writeres.e_zeit < 1)
					{
					UtilMsg((int)MPE_NORESDAT, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				break;
			}

		/* add count of booked KONTINGENTE or KAPA */
		if (newres->kont_id != (int)_UNDEF && newres->kat_id != (int)_UNDEF)
			{
			/* look if there is a KONTINGENT with this KAT and/or DLT */
			if ( newres->dlt_id == (int)_UNDEF )
				{
				/*--- Check gtee Kontingent Anzahl ---*/
				aKd.hostkont_id = (int)_UNDEF;
				aKd.kont_id = newres->kont_id;
				aKd.kat_id  = newres->kat_id;
				aKd.dlt_id  = (int)_UNDEF;
				aKd.sta_id = (int)0; /*--- Indikator ob Eintrag vorhanden ---*/
				(void)MPAPIselectOneId((int)_KONT_DETAIL, newres->kont_id, (char *)&aKd);
				if ( aKd.sta_id != (int)0 )
					{
					if ( aKd.sta_id > (int)0 )
						{
						/*--- Eintrag gefunden + ueberbuchungsfaktor gesetzt ---*/
						busyvalue = aKd.busy + 1;
						busyvalue -= aKd.sta_id;
						}
					else if ( aKd.sta_id == (int)_UNDEF )
						busyvalue = aKd.busy + 1;    /*--- Eintrag gefunden ---*/
					
					if ( busyvalue > aKd.anz )
						{
						UtilMsgGet((int)MPE_KONOVERFLOW, MSGTYP_ERROR, message);
						status = UtilImmediatCall(message);
						if (status == (int)TRUE)
							status = (int)MPOK;
						else
							return((int)MPERROR);
						}
					}
				else if (status != (int)MPOK)
					{
					UtilMsg( (int)MPE_KONKATMIS, MSGTYP_ERROR, NULL );
					return((int)MPERROR);
					}
				}

			/* increment busy counter of KONT_DETAIL */
			(void)sprintf(query, _UPD_KOND_ADDONE, newres->kont_id, newres->kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}
		/* manage KAPA table increment KAPA */
		if (writeres.kat_id != (int)_UNDEF && dlg.dl_id != (int)_UNDEF)
			{
			(void)sprintf(query, _UPD_KAPA_ADDONE, dlg.dl_id, reservation[0].kat_id);
			status = MPAPIdb_sqlcommand(query, &i);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				}
			}

		/* write new reservation for all dlparts */
		if (tdlcnt > 0)
			{
			for (i=0; i<tdlcnt; i++)
				{
				writeres.dl_id = tdlids[i];
				status = MPAPIinsertEntry((int)_RESERVATION, (char *)&writeres, (BEZEICHNUNG *)NULL);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_DBERROR, NULL);
					return((int)MPERROR);
					}
				}
			}
		else
			{
			writeres.dl_id = (int)_UNDEF;
			status = MPAPIinsertEntry((int)_RESERVATION, (char *)&writeres, (BEZEICHNUNG *)NULL);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				return((int)MPERROR);
				}
			}

		}

	/* set values to RES for further use (AKTDwrite) */
	newres->teil = writeres.teil;

	return(status);
}
