/*D************************************************************/
/* Modul:     DBI - database select                           */
/*            manage a select request on a field              */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpnet.h>
#include <mpmsg.h>
#include <mpsqlsel.h>
#include <mpstadef.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/dbitowww.c,v 1.2 2008-11-02 19:55:51 mwn Exp $";

extern MEMOBJ sqlmem;
extern BUCHUNG bch;
extern ARRANGEMENT arr;
extern STATUS_WERTE sta;
extern KUNDEN kun;
extern KUN_VIEW kunv;
extern KOLLEKTIV kol;
extern KONTINGENT kon;
extern int sprache;
int AnzRes;
int AnzRei;


int MPNETdbiinfoToWWW(int MPtableid, char *MPquery, PSmemobj *outmem)
{
	register int len, i;
	int status = (int)MPOK;
	int j, k;
	int anzchar, id;
	int old_dlid;
	int MPobjid;
	struct tm DateTime;

	BUCHUNG *Pbch;
	BUCHUNG bch;
	KUNDEN *Pkun;
	KUNDEN kun;
	REISENDER *Prei;
	REISENDER rei;
	PERSADR *Ppadr;
	PERSADR padr;
	KOLLEKTIV *Pkol;
	KOLLEKTIV kol;
	KOMMISSION *Pkom;
	KOMMISSION kom;
	KOMM_DETAIL *Pkomdet;
	KOMM_DETAIL komdet;
	KUN_VIEW kunv;
	SAISON *Psai;
	SAISON sai;
	PROGRAMM *Pprg;
	PROGRAMM prg;
	ARRANGEMENT *Parr;
	ARR_VIEW *Parrv;
	ARR_VIEW arrv;
	DIENSTLEISTUNG *Pdlg;
	DIENSTLEISTUNG dlg;
	DTG_VIEW *Pdlv;
	DTG_VIEW dlv;
	DLG_PART *Pdlgp;
	DLG_PART dlgp;
	DIENST_ANGEBOT *Pdla;
	DIENST_ANGEBOT dla;
	ANGEBOTS_TYP *Patyp;
	ANGEBOTS_TYP atyp;
	AKTIONEN *Pakt;
	AKTIONEN akt;
	AKTIONSGRP *Paktg;
	AKTIONSGRP aktg;
	HOST_KONT *Phkont;
	HOST_KONT hkont;
	KONTINGENT *Pkont;
	KONTINGENT kont;
	KONT_DETAIL *Pkontd;
	KONT_DETAIL kontd;
	PREIS *Ppre;
	PREIS pre;
	TRAEGER_TYP *Pttyp;
	TRAEGER_TYP ttyp;
	DIENST_TRAEGER *Pdlt;
	DIENST_TRAEGER dlt;
	KATEGORIE *Pkat;
	KATEGORIE kat;
	PCX_FILES *Ppcx;
	PCX_FILES pcx;
	GRAPHIK *Pgra;
	GRAPHIK gra;
	AKTIONS_TYP *Pakttyp;
	AKTIONS_TYP akttyp;
	KOSTEN_ART *Pkar;
	KOSTEN_ART kar;
	KUNDEN_TYP *Pkutyp;
	KUNDEN_TYP kutyp;
	REISENDER_TYP *Prtyp;
	REISENDER_TYP rtyp;
	KOLLEKTIV_TYP *Pkotyp;
	KOLLEKTIV_TYP kotyp;
	STATUS_WERTE *Psta;
	STATUS_WERTE sta;
	SPRACHEN *Pspr;
	SPRACHEN spr;
	WAEHRUNG *Pwhr;
	WAEHRUNG whr;
	LAND *Pland;
	LAND land;
	ORT *Port;
	ORT ort;
	LAND_WHR *Plwhr;
	LAND_WHR lwhr;
	MP_PROFIL *Pmpp;
	MP_PROFIL mpp;
	BEZEICHNUNG *Pbez;
	BEZEICHNUNG bez;
	MP_MSG *Pmesg;
	MP_MSG mesg;

	RESERVATION *reservation = NULL;
	DLG_PART tdl;
	DIENSTLEISTUNG dl;
	DLN_VIEW *reisender;
	BEZEICHNUNG abez;
	MEMOBJ memdln;


        char **splitbuffer;
	int anzsplit;
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
	char attr1[_BEZLEN+1];

	char record[20000];
	char *outputbuffer;

	switch(MPtableid)
		{
		/* BUCHUNG */
		case (int)_BUCHUNG: /* Tabelle 41 */
			/* init */
			memdln.buffer = NULL;
			memdln.alloclen = 0;
			memdln.datalen = 0;

			outmem->datalen = _RECORDLEN;
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n\r", PSOK, 1, 1);

        		/* split incomming fields from CGI script */
        		if (MPquery != NULL && *MPquery != NULL)
                		{
                		splitbuffer = (char **)MPAPIbufferSplit(MPquery, &anzsplit, (char)'\t');
                		if (splitbuffer == NULL || anzsplit != 2)
                        		{
                        		UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
                        		return((int)MPERROR);
                        		}
                		}

			/* Check auf bch.bid ob vorhanden */
			MPobjid = atoi(splitbuffer[0]);

			status = MPAPIselectOneId((int)_BUCHUNG, MPobjid, (char *)&bch);

			if ( bch.bid > (int)0 )
				{
				id = MPAPIselectOneId((int)_KUN_VIEW, bch.kid, (char *)&kunv);
				if ( id == (int)_UNDEF )
					{
					UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				else
					{
					(void)copyTextTo((char *)attr1, kunv.attr1, (int)_BEZLEN);
					if (strcmp(splitbuffer[1], attr1) != (int)MPOK)
						{
						UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
						return((int)MPERROR);
						}
					else
						{
						/*--- Kundensprache als Outputsprache setzen ---*/
						sprache = kunv.s_id;
						}
					}
				}
			else
				{
                			UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
                			return((int)MPERROR);
				}

			/* hole Objekt ARR oder DL */
			if (bch.arr_id != (int)_UNDEF)
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
			(void)strcat(outmem->buffer, tmp_buffer);
			(void)strcat(outmem->buffer, "\n");
		
			UtilMsgGet((int)MPI_RESINFOTITEL2, MSGTYP_INFO, format);
			(void)copyTextTo(bezeichnung, (char *)bch.ref, (int)_BEZLEN);
			(void)sprintf(tmp_buffer, "%-18.18s %d  %s\n", format, bch.bid, bezeichnung);
			(void)strcat(outmem->buffer, tmp_buffer);

			/* Buchungsstatus */
			sta.typ = (int)_BSTA;
			id = MPAPIselectOneId((int)_STATUS_WERTE, bch.sta, (char *)&sta);
			if (id != (int)_UNDEF && SelectBez((int)_BSTA, sprache, sta.bez_id,
		  		bezeichnung) != (int)_UNDEF)
				(void)strcpy(bez_rsta, bezeichnung);
			else
				UtilMsgGet((int)MPI_RESINFONOTHING, MSGTYP_INFO, bez_rsta);
			(void)sprintf(tmp_buffer, "Buchungsstatus:    %s\n", bezeichnung); /*!!! hard */
			(void)strcat(outmem->buffer, tmp_buffer);
		
			anzchar=(int)4;
			for (k=0; k<anzchar; k++)
				(void)strcat(outmem->buffer, "--------------------");
			(void)strcat(outmem->buffer, "\n\n");
		
			/* ARRANGEMENT titel */
			if (bch.arr_id != (int)_UNDEF)
				{
				UtilMsgGet((int)MPI_RESINFOARRTIT, MSGTYP_INFO, format);
				(void)copyTextTo(bezeichnung, (char *)abez.bez, (int)_BEZLEN);
				(void)sprintf(tmp_buffer, "%-18.18s %s\n", format, bezeichnung);
				(void)strcat(outmem->buffer, tmp_buffer);
				}
		
			/* KUNDE/KOLLEKTIV */
			if (bch.k_id != (int)_UNDEF)
				{
				UtilMsgGet((int)MPI_RESINFOTITEL4, MSGTYP_INFO, format);
				(void)MPAPIselectOneId((int)_KOLLEKTIV, bch.k_id, (char *)&kol);
				(void)sprintf(tmp_buffer, "%-18.18s %s\n", format, kol.name);
				(void)strcat(outmem->buffer, tmp_buffer);
				}
			if (bch.kid != (int)_UNDEF)
				{
				UtilMsgGet((int)MPI_RESINFOTITEL3, MSGTYP_INFO, format);
				(void)MPAPIselectOneId((int)_KUN_VIEW, bch.kid, (char *)&kunv);
				(void)copyTextTo(bezeichnung, (char *)kunv.name, (int)_CHAR30);
				(void)sprintf(tmp_buffer, "%-18.18s %s", format, bezeichnung);
				(void)strcat(outmem->buffer, tmp_buffer);
				(void)copyTextTo(bezeichnung, (char *)kunv.ort, (int)_CHAR30);
				(void)sprintf(tmp_buffer, ",  %s\n", bezeichnung);
				(void)strcat(outmem->buffer, tmp_buffer);
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
				(void)strcat(outmem->buffer, "\n\n");
				UtilMsgGet((int)MPI_RESINFODLNTIT, MSGTYP_INFO, format);
				(void)copyTextTo(bezeichnung, (char *)reisender[i].name, (int)_BEZLEN);
				(void)copyTextTo(bezeichnung2, (char *)reisender[i].vor, (int)_BEZLEN);
				(void)sprintf(tmp_buffer, "%-18.18s %s %s\n\n", format, bezeichnung, bezeichnung2);
				(void)strcat(outmem->buffer, tmp_buffer);
		
				/* Reservationstabelle - Titel */
				UtilMsgGet((int)MPI_RESINFORESTIT, MSGTYP_INFO, format);
				(void)sprintf(tmp_buffer, "%s\n", format);
				(void)strcat(outmem->buffer, tmp_buffer);
				UtilMsgGet((int)MPI_RESINFORESTIT2, MSGTYP_INFO, format);
				(void)sprintf(tmp_buffer, "%s\n", format);
				(void)strcat(outmem->buffer, tmp_buffer);
				anzchar=(int)4;
				for (k=0; k<anzchar; k++)
					(void)strcat(outmem->buffer, "--------------------");
				(void)strcat(outmem->buffer, "\n");
		
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
							(void)strcat(outmem->buffer, tmp_buffer);
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
					(void)strcat(outmem->buffer, tmp_buffer);
		
					/* check if TDL's are booked and print TDL's */
					if (reservation[j].dl_id != (int)_UNDEF)
						{
						id = MPAPIselectOneId((int)_DLG_PART, (int)reservation[j].dl_id, (char *)&tdl);
						if (id == (int)_UNDEF || SelectBez((int)_DLG_PART, sprache, tdl.bez_id, c_dlg) == (int)_UNDEF )
							UtilMsgGet((int)MPI_RESINFOOPEN, MSGTYP_INFO, c_dlg);
						(void)sprintf(tmp_buffer, "    - %s\n", c_dlg);
						(void)strcat(outmem->buffer, tmp_buffer);
						}
		
					} /* end of DL/DL_PARTS for loop */
		
				} /* end of DLN for loop */
			MPfree((void *)memdln.buffer);

			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KUNDEN: /* Tabelle 25 */
			break;
		case (int)_REISENDER: /* Tabelle 36 */
			break;
		case (int)_PERSADR: /* Tabelle 37 */
			break;
		case (int)_KOLLEKTIV: /* Tabelle 33 */
			break;
		case (int)_KOMMISSION: /* Tabelle 44 */
			break;
		case (int)_KOMM_DETAIL: /* Tabelle 45 */
			break;


		/* ANGEBOT */
		case (int)_SAISON: /* Tabelle 9 */
			break;
		case (int)_PROGRAMM: /* Tabelle 29 */
			break;
		case (int)_ARRANGEMENT: /* Tabelle 30 */
			break;
		case (int)_ARR_VIEW: /* View 277 */
			break;
		case (int)_DIENSTLEISTUNG: /* Tabell 27 */
			break;
		case (int)_DTG_VIEW: /* View 275 */
			break;
		case (int)_DLG_PART: /* Tabelle 26 */
			break;
		case (int)_DIENST_ANGEBOT: /* Tabelle 23 */
			break; 
		case (int)_ANGEBOTS_TYP: /* Tabelle 18 */
			break;
		case (int)_AKTIONEN: /* Tabelle 21 */
			break;
		case (int)_AKTIONSGRP: /* Tabelle 22 */
			break;
		case (int)_HOST_KONT: /* Tabelle 38 */
			break;
		case (int)_KONTINGENT: /* Tabelle 39 */
			break;
		case (int)_KONT_DETAIL: /* Tabelle 40 */
			break;
		case (int)_PREIS: /* Tabelle 47 */
			break;



		/* STAMM */
		case (int)_TRAEGER_TYP:/* Tabelle 15 */
			break;
		case (int)_DIENST_TRAEGER: /* Tabelle 17 */
			break;
		case (int)_KATEGORIE: /* Tabelle 16 */
			break;
		case (int)_PCX_FILES: /* Tabelle 49 */
			break;
		case (int)_GRAPHIK: /* Tabelle 48 */
			break;
		case (int)_AKTIONS_TYP: /* Tabelle 19 */
			break;
		case (int)_KOSTEN_ART: /* Tabelle 43 */
			break;
		case (int)_KUNDEN_TYP: /* Tabelle 24 */
			break;
		case (int)_REISENDER_TYP: /* Tabelle 35 */
			break;
		case (int)_KOLLEKTIV_TYP: /* Tabelle 32 */
			break;
		case (int)_STATUS_WERTE: /* Tabelle 2 */
			break;


		/* GEOGRAFIE */
		case (int)_SPRACHEN: /* Tabelle 1 */
			break;
		case (int)_WAEHRUNG: /* Tabelle 12 */
			break;
		case (int)_LAND: /* Tabelle 10 */
			break;
		case (int)_ORT: /* Tabelle 11 */
			break;
		case (int)_LAND_WHR: /* Tabelle 13 */
			break;


		/* Administration */
		case (int)_MP_PROFIL: /* Tabelle 55 */
			break;
		case (int)_BEZEICHNUNG: /* Tabelle 3 */
			break;
		case (int)_MSG: /* Tabelle 7 */ /* _MP_MSG would be better */
			break;

		default:
			break;
		}


	return(0);
}
