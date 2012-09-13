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

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/mpnetwww.c,v 1.2 2008-11-02 19:55:51 mwn Exp $";

extern MEMOBJ sqlmem;
extern BUCHUNG bch;
extern ARRANGEMENT arr;
extern STATUS_WERTE sta;
extern KUNDEN kun;
extern KUN_VIEW kunv;
extern KOLLEKTIV kol;
extern KONTINGENT kon;
extern int AnzRes;
extern int AnzRei;
extern int sprache;


int MPNETdbToWWW(int MPtableid, char *MPquery, PSmemobj *outmem)
{
	register int len, i;
	int cret = (int)MPOK;
	int MPobjid;
	DLG_PART tdl;

	switch(MPtableid)
		{
		/* BUCHUNG */
		case (int)_BUCHUNG: /* Tabelle 41 */
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
		case (int)_RESERVATION: /* Tabelle 46 */
			/* start transaction in EXCLUSIVE mode */
			cret = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
			if (cret != (int)MPOK)
				{
				UtilMsg(cret, MSGTYP_ERROR, NULL);
				return(MPERROR);
				}
			len = (int)strlen(MPquery);
			MPquery[len] = (char)NULL;
			cret = RESinsert(MPquery, outmem);
			/* end transaction if error then make rollback */
			if (cret != (int)MPOK)
				MPAPIdb_rollbacktrx();
			else
				MPAPIdb_committrx();
			break;
		case (int)_MPV_KAPA: /* 284 */
			cret = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
			cret = KAPAVinfo(MPquery, outmem);
			MPAPIdb_committrx();
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

	return(cret);
}
