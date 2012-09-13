/*D***********************************************************
 * Modul:     DBI - database info
 *            make info for BCH, DLN and RES
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xRESinfo.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int RESinfo(int len, char *buffer)
{
	extern MEMOBJ sqlmem;

	extern BUCHUNG bch;
	extern ARRANGEMENT arr;
	extern STATUS_WERTE sta;
	extern KUNDEN kun;
	extern KUN_VIEW kunv;
	extern KOLLEKTIV kol;
	extern KONTINGENT kon;
	extern unsigned char bm_obj;

	extern int AnzRes;
	extern int AnzRei;
	extern int sprache;

	RESERVATION *reservation = NULL;
	DIENST_TRAEGER dlt;
	DLG_PART tdl;
	DIENSTLEISTUNG dl;
	KATEGORIE kat;
	DLN_VIEW *reisender;
	BEZEICHNUNG abez;
	MEMOBJ memdln;

	char query[_QUERYLEN];
	char c_dlg[_RECORDLEN];
	char c_kat[_CHAR30 + 1];
	char c_dlt[_CHAR30 + 1];
	char c_kont[_CHAR30 + 1];
	char bez_rsta[_BEZLEN+1];
	char format[RECLAENGE];
	char bezeichnung[_BEZLEN + 1];
	char bezeichnung2[_BEZLEN + 1];
	char tmp_buffer[RECLAENGE];
	int status=(int)MPOK;
	register int i, j, k;
	int anzchar, id;
	int old_dlid;
	struct tm DateTime;

	/* init */
	memdln.buffer = NULL;
	memdln.alloclen = 0;
	memdln.datalen = 0;

	/* Check auf bch.bid ob vorhanden */
	if (bch.bid == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* hole Objekt ARR oder DL */
	if (bm_obj == (unsigned char)_ARRANGEMENT || bch.arr_id != (int)_UNDEF)
		{
		if (bch.arr_id != (int)_UNDEF)
			(void)MPAPIselectOneId((int)_ARRANGEMENT, bch.arr_id, (char *)&arr);
		abez.typ=(int)_ARRANGEMENT;
		abez.s_id=sprache;
		abez.bez_id=arr.bez_id;
		status = MPAPIselectOneId((int)_BEZEICHNUNG, arr.bez_id, (char *)&abez);
		if (status == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	/* Info Titel */
	UtilMsgGet((int)MPI_RESINFOTITEL1, MSGTYP_INFO, tmp_buffer);
	(void)sprintf(comm.buffer, "%s\n", tmp_buffer);

	UtilMsgGet((int)MPI_RESINFOTITEL2, MSGTYP_INFO, format);
	(void)copyTextTo(bezeichnung, (char *)bch.ref, (int)_BEZLEN);
	(void)sprintf(tmp_buffer, "%-18.18s %d  %s\n", format, bch.bid, bezeichnung);
	(void)strcat(comm.buffer, tmp_buffer);

	/* Buchungsstatus */
	sta.typ = (int)_BSTA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, bch.sta, (char *)&sta);
	if (id != (int)_UNDEF && SelectBez((int)_BSTA, sprache, sta.bez_id,
		  bezeichnung) != (int)_UNDEF)
		(void)strcpy(bez_rsta, bezeichnung);
	else
		UtilMsgGet((int)MPI_RESINFONOTHING, MSGTYP_INFO, bez_rsta);
	(void)sprintf(tmp_buffer, "Buchungsstatus:    %s\n", bezeichnung); /*!!! hard */
	(void)strcat(comm.buffer, tmp_buffer);

	anzchar=(int)4;
	for (k=0; k<anzchar; k++)
		(void)strcat(comm.buffer, "--------------------");
	(void)strcat(comm.buffer, "\n\n");

	/* ARRANGEMENT titel */
	if (bm_obj == (unsigned char)_ARRANGEMENT)
		{
		UtilMsgGet((int)MPI_RESINFOARRTIT, MSGTYP_INFO, format);
		(void)copyTextTo(bezeichnung, (char *)abez.bez, (int)_BEZLEN);
		(void)sprintf(tmp_buffer, "%-18.18s %s\n", format, bezeichnung);
		(void)strcat(comm.buffer, tmp_buffer);
		}

	/* KUNDE/KOLLEKTIV */
	if (bch.k_id != (int)_UNDEF)
		{
		UtilMsgGet((int)MPI_RESINFOTITEL4, MSGTYP_INFO, format);
		(void)MPAPIselectOneId((int)_KOLLEKTIV, bch.k_id, (char *)&kol);
      (void)copyTextTo(bezeichnung, kol.name, (int)_BEZLEN);
		(void)sprintf(tmp_buffer, "%-18.18s %s\n", format, bezeichnung);
		(void)strcat(comm.buffer, tmp_buffer);
		}
	if (bch.kid != (int)_UNDEF)
		{
		UtilMsgGet((int)MPI_RESINFOTITEL3, MSGTYP_INFO, format);
		(void)MPAPIselectOneId((int)_KUN_VIEW, bch.kid, (char *)&kunv);
		(void)copyTextTo(bezeichnung, (char *)kunv.name, (int)_CHAR30);
		(void)sprintf(tmp_buffer, "%-18.18s %s", format, bezeichnung);
		(void)strcat(comm.buffer, tmp_buffer);
		(void)copyTextTo(bezeichnung, (char *)kunv.ort, (int)_CHAR30);
		(void)sprintf(tmp_buffer, ",  %s\n", bezeichnung);
		(void)strcat(comm.buffer, tmp_buffer);
		}

	/* hole alle DLN der BUCHUNG bch */
	(void)sprintf(query, _SEL_DLNVIEW_BID, bch.bid, _ORDER_DLN_ID);
	status=MPAPIdb_sqlquery((int)_DLN_VIEW, &memdln.buffer, query,
                         &AnzRei, &memdln.datalen, &memdln.alloclen);
	reisender = (DLN_VIEW *)memdln.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	if (AnzRei < 1)
		{
		UtilMsg((int)MPE_NODLNINBCH, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Reservationen pro DLN */
	for (i=0; i<AnzRei; i++)
		{
		/* DLN - Titel */
		(void)strcat(comm.buffer, "\n\n");
		UtilMsgGet((int)MPI_RESINFODLNTIT, MSGTYP_INFO, format);
		(void)copyTextTo(bezeichnung, (char *)reisender[i].name, (int)_BEZLEN);
		(void)copyTextTo(bezeichnung2, (char *)reisender[i].vor, (int)_BEZLEN);
		(void)sprintf(tmp_buffer, "%-18.18s %s %s\n\n", format, bezeichnung, bezeichnung2);
		(void)strcat(comm.buffer, tmp_buffer);

		/* Reservationstabelle - Titel */
		UtilMsgGet((int)MPI_RESINFORESTIT, MSGTYP_INFO, format);
		(void)sprintf(tmp_buffer, "%s\n", format);
		(void)strcat(comm.buffer, tmp_buffer);
		UtilMsgGet((int)MPI_RESINFORESTIT2, MSGTYP_INFO, format);
		(void)sprintf(tmp_buffer, "%s\n", format);
		(void)strcat(comm.buffer, tmp_buffer);
		anzchar=(int)4;
		for (k=0; k<anzchar; k++)
			(void)strcat(comm.buffer, "--------------------");
		(void)strcat(comm.buffer, "\n");

		/* get reservation infos */
		(void)sprintf(query, _SEL_ALL_RES_BID_UID, bch.bid, reisender[i].dln_id);
		status=MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer,
		           query, &AnzRes, &sqlmem.datalen, &sqlmem.alloclen);
		reservation = (RESERVATION *)sqlmem.buffer;
		if (status != (int)MPOK)
			{
			UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}

		/* pro DLN alle Reservationen ausgeben */
		old_dlid = (int)0;
		for (j=0; j<AnzRes; j++)
			{
			if (old_dlid == reservation[j].dlg_id)
				{
				/* check if TDL's are booked and print TDL's */
				if (reservation[j].dl_id != (int)_UNDEF)
					{
					id = MPAPIselectOneId((int)_DLG_PART, (int)reservation[j].dl_id, (char *)&tdl);
					if (id == (int)_UNDEF || SelectBez((int)_DLG_PART, sprache, tdl.bez_id, c_dlg) == (int)_UNDEF )
						UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_dlg);
					(void)sprintf(tmp_buffer, "    - %s\n", c_dlg);
					(void)strcat(comm.buffer, tmp_buffer);
					}
					continue;
				}
			old_dlid = reservation[j].dlg_id;

			/*!!! get informations about DL and TDL - clean up and make error hndl */
			id = MPAPIselectOneId((int)_DIENSTLEISTUNG, (int)reservation[j].dlg_id,
			     (char *)&dl);
			if (id == (int)_UNDEF || SelectBez((int)_DIENSTLEISTUNG, sprache,
			    dl.bez_id, tmp_buffer) == (int)_UNDEF)
				(void)strcpy(c_dlg, "-");
			else
				(void)sprintf(c_dlg, "%-30.30s", tmp_buffer);

			if (reservation[j].dl_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_DLG_PART, (int)reservation[j].dl_id, (char *)&tdl);
				if (id == (int)_UNDEF)
					status = MPERROR;
				}
			else
				status = MPAPIselectTDL(reservation[j].dlg_id, &tdl);
			if (status == (int)MPOK)
				{
				if (tdl.res_f == (int)_RES_DYNAMIC)
					{
					/* DATUM  Anfangszeit der Dienstleistung */
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)0;
					DateTime.tm_min =(int)0;
					(void)WriteDate(&DateTime, (time_t *)&reservation[j].a_zeit, bezeichnung);
					(void)strcat(c_dlg, "  ");
					(void)strcat(c_dlg, bezeichnung);
					/* DATUM  Endezeit der Dienstleistung */
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)0;
					DateTime.tm_min =(int)0;
					(void)WriteDate(&DateTime, (time_t *)&reservation[j].e_zeit, bezeichnung);
					(void)strcat(c_dlg, "  ");
					(void)strcat(c_dlg, bezeichnung);
					}
				else
					{
					/* DATUM  Anfangszeit der Dienstleistung */
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)0;
					DateTime.tm_min =(int)0;
					(void)WriteDate(&DateTime, (time_t *)&dl.a_zeit, bezeichnung);
					(void)strcat(c_dlg, "  ");
					(void)strcat(c_dlg, bezeichnung);
					}
				}

			/* Kategorien Spalte */
			if (reservation[j].kat_id == (int)_UNDEF)
				UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_kat);
			else
				{
				id = MPAPIselectOneId((int)_KATEGORIE, (int)reservation[j].kat_id, (char *)&kat);
				if ( id == (int)_UNDEF || SelectBez((int)_KATEGORIE, sprache, kat.bez_id, c_kat) == (int)_UNDEF )
					UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_kat);
				}

			/* Dienstleistungstr�ger Spalte */
			if (reservation[j].dlt_id == (int)_UNDEF)
				UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_dlt);
			else
				{
				id = MPAPIselectOneId((int)_DIENST_TRAEGER, (int)reservation[j].dlt_id, (char *)&dlt);
				if ( id == (int)_UNDEF || SelectBez((int)_DIENST_TRAEGER, sprache, dlt.bez_id, c_dlt) == (int)_UNDEF )
					UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_dlt);
				}

			/* Kontingent Spalte */
			if (reservation[j].kont_id == (int)_UNDEF)
				UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_kont);
			else
				{
				id = MPAPIselectOneId((int)_KONTINGENT, (int)reservation[j].kont_id, (char *)&kon);
				if (id == (int)_UNDEF || SelectBez((int)_KONTINGENT, sprache, kon.bez_id, c_kont) == (int)_UNDEF )
					UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_kont);
				}

			/* Reservationsstatus Spalte */
			sta.typ=(int)_R_STA;
			id = MPAPIselectOneId((int)_STATUS_WERTE, reservation[j].r_sta, (char *)&sta);
			if (id != (int)_UNDEF && SelectBez((int)_R_STA, sprache, sta.bez_id,
			    bezeichnung) != (int)_UNDEF)
				(void)strcpy(bez_rsta, bezeichnung);
			else
				UtilMsgGet((int)MPI_RESINFONOTHING, MSGTYP_INFO, bez_rsta);

			/* schreibe Spalteninhalte */
			(void)sprintf(tmp_buffer, "\n %2d. %-55.55s    %-20.20s\n    %-19.19s %-19.19s %-19.19s\n",
			              reservation[j].teil, c_dlg, bez_rsta,
			              c_kat, c_dlt, c_kont);
			(void)strcat(comm.buffer, tmp_buffer);

			/* check if TDL's are booked and print TDL's */
			if (reservation[j].dl_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_DLG_PART, (int)reservation[j].dl_id, (char *)&tdl);
				if (id == (int)_UNDEF || SelectBez((int)_DLG_PART, sprache, tdl.bez_id, c_dlg) == (int)_UNDEF )
					UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_dlg);
				(void)sprintf(tmp_buffer, "    - %s\n", c_dlg);
				(void)strcat(comm.buffer, tmp_buffer);
				}

			} /* end of DL/DL_PARTS for loop */

		} /* end of DLN for loop */

	MPfree((void *)memdln.buffer);

	/* define typ of info */
	ACTIONTYP = INFOTXT;

	return(status);
}
