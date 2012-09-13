/*D***********************************************************
 * modul:     DBI - write info/history after ins/upd/del
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/WriteInfo.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";



// TODO ATTENTION   hardcoded msgs in this function




void WriteInfo(int table, char *datastring, char *buffer)
{
	AKTIONEN *akt;
	ARRANGEMENT *arr;
	DIENST_ANGEBOT *dla;
	ANGEBOTS_TYP *dlat;
	DLG_PART *dlg;
	DIENSTLEISTUNG *dtg;
	DIENST_TRAEGER *dlt;
	TRAEGER_TYP *dltt;
	GRAPHIK *gra;
	KATEGORIE *kat;
	KOLLEKTIV *kol;
	KOLLEKTIV_TYP *kolt;
	KONTINGENT *kon;
	KUNDEN *kun;
	KUNDEN_TYP *kunt;
	PCX_FILES *pcx;
	PREIS *pre;
	PROGRAMM *prg;
	REISENDER *rei;
	REISENDER_TYP *reit;
	KOSTEN_ART *kar;
	SAISON *sai;
	SPRACHEN *spr;
	TEXTE *txt;

	int status=(int)MPOK;

	switch(table)
		{
		case	_SPRACHEN:
			break;
		case	_TEXTE:
			break;
		case	_SAISON:
			break;

		case _LAND_WHR:
			MPlog(_LOGUSER, MSGTYP_INFO, "new change rate added", __FILE__);
			break;

		case	_REISENDER:
			break;
		case	_REISENDER_TYP:
			break;
		case	_KUNDEN:
			break;
		case	_KUNDEN_TYP:
			break;
		case	_KOLLEKTIV:
			break;
		case	_KOLLEKTIV_TYP:
			break;

		case	_TRAEGER_TYP:
			break;
		case	_KATEGORIE:
			break;
		case	_DIENST_TRAEGER:
			break;
		case	_ANGEBOTS_TYP:
			break;
		case	_AKTIONEN:
			break;
		case	_DIENST_ANGEBOT:
			break;
		case	_DIENSTLEISTUNG:
			break;
		case	_PROGRAMM:
			break;
		case	_ARRANGEMENT:
			break;

		case	_KONTINGENT:
			break;

		case _BUCHUNG:
			MPlog(_LOGUSER, MSGTYP_INFO, "Buchungsdossier verarbeitet", __FILE__);
			break;
		case _RESERVATION:
			MPlog(_LOGUSER, MSGTYP_INFO, "Dienstleistung im Dossier verarbeitet", __FILE__);
			break;
		case	_KOSTEN_ART:
			break;
		case	_PREIS:
			break;

		case	_GRAPHIK:
			break;
		case	_PCX_FILES:
			break;
		}

	return;
}
