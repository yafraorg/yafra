/*D***********************************************************
 * modul:     API - database select one entry
 *
 * paras:     int table      to select from
 *            int id         which entry to select
 *            char *pointer  data pointer for found entry
 *
 * return:    _UNDEF  if error or the number of the entry
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlbez.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectOneId.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

// TODO local define IGNORE is not used anymore in DBI
#define IGNORE       (int)-2

/*
* Definition aller verwendbaren SQL-Select Befehlen
*/
#define _SELECT_MAX	"SELECT * FROM TDBADMIN.MAXIMA WHERE TABELLE=%d AND TYP=%d;"
#define _SELECT_SPR	"SELECT * FROM TDBADMIN.SPRACHEN WHERE S_ID = %d;"
#define _SELECT_STA	"SELECT * FROM TDBADMIN.STATUS_WERTE WHERE STA_ID = %d AND TYP = %d;"
#define _SELECT_HIS	"SELECT * FROM TDBADMIN.HISTORY WHERE HIS_ID = %d AND TEXTNR = %d AND S_ID = %d;"
#define _SELECT_SAI	"SELECT * FROM TDBADMIN.SAISON WHERE SAI_ID = %d;"

#define _SELECT_PROF	"SELECT * FROM TDBADMIN.MP_PROFIL WHERE MPID = %d;"

#define _SELECT_WHR	"SELECT * FROM TDBADMIN.WAEHRUNG WHERE WHR_ID=%d;"
#define _SELECT_LAND	"SELECT * FROM TDBADMIN.LAND WHERE LAND_ID=%d;"
#define _SELECT_ORT	"SELECT * FROM TDBADMIN.ORT WHERE ORT_ID=%d;"
#define _SELECT_LW	"SELECT * FROM TDBADMIN.LAND_WHR WHERE LAND_ID=%d AND WHR_ID=%d AND KURS_TYP=%d;"

#define _SELECT_PERS	"SELECT * FROM TDBADMIN.PERSONEN WHERE PERS_ID=%d;"
#define _SELECT_REIT	"SELECT * FROM TDBADMIN.REISENDER_TYP WHERE RKR_ID = %d;"
#define _SELECT_REI	"SELECT * FROM TDBADMIN.REISENDER WHERE PERS_ID = %d;"
#define _SELECT_KUNT	"SELECT * FROM TDBADMIN.KUNDEN_TYP WHERE K_TYP_ID = %d;"
#define _SELECT_KUN	"SELECT * FROM TDBADMIN.KUNDEN WHERE PERS_ID = %d;"
#define _SELECT_KOLT	"SELECT * FROM TDBADMIN.KOLLEKTIV_TYP WHERE K_TYP_ID = %d;"
#define _SELECT_KOL	"SELECT * FROM TDBADMIN.KOLLEKTIV WHERE K_ID = %d;"
#define _SELECT_PERSADR	"SELECT * FROM TDBADMIN.PERSADR WHERE PERS_ID=%d;"

#define _SELECT_DLTT	"SELECT * FROM TDBADMIN.TRAEGER_TYP WHERE TYP_ID = %d;"
#define _SELECT_KAT	"SELECT * FROM TDBADMIN.KATEGORIE WHERE KAT_ID = %d;"
#define _SELECT_DLT	"SELECT * FROM TDBADMIN.DIENST_TRAEGER WHERE DLT_ID = %d;"
#define _SELECT_DLAT	"SELECT * FROM TDBADMIN.ANGEBOTS_TYP WHERE ART_ID = %d;"
#define _SELECT_AKTT	"SELECT * FROM TDBADMIN.AKTIONS_TYP WHERE A_TYP_ID = %d;"
#define _SELECT_APARA "SELECT * FROM TDBADMIN.AKTIONSPARA WHERE A_TYP_ID = %d AND NR = %d;"
#define _SELECT_AKT	"SELECT * FROM TDBADMIN.AKTIONEN WHERE AKT_ID = %d;"
#define _SELECT_AKTG	"SELECT * FROM TDBADMIN.AKTIONSGRP WHERE PARENTAKT = %d AND CHILDAKT = %d;"
#define _SELECT_DLA	"SELECT * FROM TDBADMIN.DIENST_ANGEBOT WHERE DLA_ID = %d;"
#define _SELECT_DLG	"SELECT * FROM TDBADMIN.DLG_PARTS WHERE DL_ID = %d;"
#define _SELECT_DTG	"SELECT * FROM TDBADMIN.DIENSTLEISTUNG WHERE DLG_ID = %d;"
#define _SELECT_DTGV	"SELECT * FROM TDBADMIN.DTG_VIEW WHERE DLG_ID = %d AND S_ID = %d;"
#define _SELECT_DD	"SELECT * FROM TDBADMIN.DLG_DLG WHERE DLG_ID = %d AND DL_ID = %d;"
#define _SELECT_DDO	"SELECT * FROM TDBADMIN.DLG_DLG WHERE DLG_ID = %d AND ORD = %d;"
#define _SELECT_PRG	"SELECT * FROM TDBADMIN.PROGRAMM WHERE PRG_ID = %d;"
#define _SELECT_ARR	"SELECT * FROM TDBADMIN.ARRANGEMENT WHERE ARR_ID = %d;"
#define _SELECT_AD	"SELECT * FROM TDBADMIN.ARR_DLG WHERE ARR_ID = %d AND DLG_ID = %d;"
#define _SELECT_ADT	"SELECT * FROM TDBADMIN.ARR_DLG WHERE ARR_ID = %d AND TEIL = %d AND PRIO = %d;"

#define _SELECT_HKON	"SELECT * FROM TDBADMIN.HOST_KONT WHERE HOSTKONT_ID=%d;"
#define _SELECT_KON	"SELECT * FROM TDBADMIN.KONTINGENT WHERE KONT_ID = %d;"
#define _SELECT_KD_HKON	"SELECT * FROM TDBADMIN.KONT_DETAIL WHERE HOSTKONT_ID=%d AND KAT_ID=%d AND DLT_ID=%d;"
#define _SELECT_KD_KON	"SELECT * FROM TDBADMIN.KONT_DETAIL WHERE KONT_ID=%d AND KAT_ID=%d AND DLT_ID=%d;"

#define _SELECT_BCH	"SELECT * FROM TDBADMIN.BUCHUNG WHERE BID = %d;"
#define _SELECT_KAR	"SELECT * FROM TDBADMIN.KOSTEN_ART WHERE KAR_ID=%d;"
#define _SELECT_KOM	"SELECT * FROM TDBADMIN.KOMMISSION WHERE KOMM_ID=%d;"
#define _SELECT_KOMD	"SELECT * FROM TDBADMIN.KOMM_DETAIL WHERE KOMM_ID=%d AND DLN_ID=%d AND KUN_ID=%d AND KOL_ID=%d;"
#define _SELECT_RES	"SELECT * FROM TDBADMIN.RESERVATION WHERE PERS_ID = %d AND DL_ID = %d AND TEIL = %d AND BID = %d;"
#define _SELECT_RES_DL_DIST	"SELECT DISTINCT (DLG_ID) FROM TDBADMIN.RESERVATION WHERE BID = %d;"
#define _SELECT_PRE	"SELECT * FROM TDBADMIN.PREIS WHERE KAR_ID=%d AND DLA_ID=%d AND DL_ID=%d AND KAT_ID=%d AND KONT_ID=%d AND RKR_ID=%d AND GLT=%d;"

#define _SELECT_GRA	"SELECT * FROM TDBADMIN.GRAPHIK WHERE DLT_ID = %d;"
#define _SELECT_PCX	"SELECT * FROM TDBADMIN.PCX_FILES WHERE PCX_ID = %d;"

#define _SELECT_SPRV	"SELECT * FROM TDBADMIN.SPR_VIEW WHERE S_ID = %d;"
#define _SELECT_STAV	"SELECT * FROM TDBADMIN.STA_VIEW WHERE S_ID = %d AND STA_ID = %d AND TYP = %d;"
#define _SELECT_SAIV	"SELECT * FROM TDBADMIN.SAI_VIEW WHERE SAI_ID =%d AND S_ID = %d;"
#define _SELECT_LANDV	"SELECT * FROM TDBADMIN.LAND_VIEW WHERE LAND_ID = %d AND S_ID = %d;"
#define _SELECT_KUNV	"SELECT * FROM TDBADMIN.KUNDEN_VIEW WHERE KUN_ID = %d;"
#define _SELECT_KUNADRV	"SELECT * FROM TDBADMIN.MPV_KUNADR WHERE PERS_ID = %d;"
#define _SELECT_DLNV	"SELECT * FROM TDBADMIN.DLN_VIEW WHERE DLN_ID = %d;"
#define _SELECT_REITV	"SELECT * FROM TDBADMIN.RKR_VIEW WHERE RKR_ID = %d AND S_ID = %d;"
#define _SELECT_TRV	"SELECT * FROM TDBADMIN.TRAEGER_VIEW WHERE ID = %d AND SPR = %d;"
#define _SELECT_DLTV	"SELECT * FROM TDBADMIN.DLT_VIEW WHERE DLT_ID = %d AND S_ID = %d;"
#define _SELECT_TTYP	"SELECT * FROM TDBADMIN.TTYP_VIEW WHERE ID = %d AND SPR = %d;"
#define _SELECT_KATV	"SELECT * FROM TDBADMIN.KAT_VIEW WHERE KAT_ID = %d AND S_ID = %d;"
#define _SELECT_DLAV	"SELECT * FROM TDBADMIN.DLA_VIEW WHERE DLA_ID = %d AND S_ID = %d;"
#define _SELECT_KONV	"SELECT * FROM TDBADMIN.KON_VIEW WHERE KONT_ID = %d AND S_ID = %d;"
#define _SELECT_KARV	"SELECT * FROM TDBADMIN.KAR_VIEW WHERE KAR_ID=%d AND S_ID = %d;"
#define _SELECT_GRAV	"SELECT * FROM TDBADMIN.GRA_VIEW WHERE GRA_ID=%d AND S_ID = %d;"
#define _SELECT_ROUT	"SELECT * FROM TDBADMIN.ROUTEN_VIEW WHERE DLG_ID=%d AND S_ID = 1;"

int MPAPIselectOneId(int table , int id , char *pointer )
{
	extern MEMOBJ apimem;
	extern ARRANGEMENT arr;
	extern int sprache;

	MAXIMA *maxima;
	STATUS_WERTE *sta_ptr;
	LAND_WHR *lw_ptr;
	ARR_DLG *ad_ptr;
	DLG_DLG *dd_ptr;
	KOMMISSION *kom_ptr;
	KOMM_DETAIL *kd_ptr;
	KONT_DETAIL *Pkond;
	RESERVATION *Pres;
	PREIS *pre_ptr;
	STA_VIEW *stv_ptr;

	char query[_QUERYLEN];
	int anzahl=0, bytes=0, id_type=0;
	int status=(int)MPOK;

	if (id == (int)_UNDEF || id == (int)0)
		return((int)_UNDEF);

	switch(table)
		{
		case _MAXIMA:
			maxima = (MAXIMA *)pointer;
			bytes=sizeof(MAXIMA);
			id_type=sizeof(maxima->tabelle);
			(void)sprintf(query, _SELECT_MAX, maxima->tabelle, maxima->typ);
			break;
		case _SPRACHEN:
			bytes=sizeof(SPRACHEN);
			id_type=sizeof((SPRACHEN *)pointer)->s_id;
			(void)sprintf(query, _SELECT_SPR, id);
			break;
		case _STATUS_WERTE:
			bytes=sizeof(STATUS_WERTE);
			sta_ptr=(STATUS_WERTE *)pointer;
			id_type=(int)0;
			(void)sprintf(query, _SELECT_STA, id, sta_ptr->typ);
			break;
		case _BEZEICHNUNG:
			bytes=sizeof(BEZEICHNUNG);
			id_type=sizeof((BEZEICHNUNG *)pointer)->bez_id;
			(void)sprintf(query, _SELECT_BEZ, ((BEZEICHNUNG *)pointer)->bez_id,
						    ((BEZEICHNUNG *)pointer)->s_id,
						    ((BEZEICHNUNG *)pointer)->typ);
			break;
		case _TEXTE:
			bytes=sizeof(TEXTE);
			id_type=sizeof((TEXTE *)pointer)->textid;
			(void)sprintf(query, _SELECT_TXT, ((TEXTE *)pointer)->textid, ((TEXTE *)pointer)->s_id,
						    					((TEXTE *)pointer)->typ);
			break;
		case _SAISON:
			bytes=sizeof(SAISON);
			id_type=sizeof((SAISON *)pointer)->sai_id;
			(void)sprintf(query, _SELECT_SAI, id);
			break;
		case _MP_PROFIL:
			bytes=sizeof(MP_PROFIL);
			id_type=sizeof((MP_PROFIL *)pointer)->mpid;
			(void)sprintf(query, _SELECT_PROF, id);
			break;


		case _WAEHRUNG:
			bytes=sizeof(WAEHRUNG);
			id_type=sizeof((WAEHRUNG *)pointer)->whr_id;
			(void)sprintf(query, _SELECT_WHR, id);
			break;
		case _LAND:
			bytes=sizeof(LAND);
			id_type=sizeof((LAND *)pointer)->land_id;
			(void)sprintf(query, _SELECT_LAND, id);
			break;
		case _ORT:
			bytes=sizeof(ORT);
			id_type=sizeof((ORT *)pointer)->ort_id;
			(void)sprintf(query, _SELECT_ORT, id);
			break;
		case _LAND_WHR:
			bytes=sizeof(LAND_WHR);
			lw_ptr=(LAND_WHR *)pointer;
			id_type=sizeof(lw_ptr->land_id);
			(void)sprintf(query, _SELECT_LW, lw_ptr->land_id, lw_ptr->whr_id,
			                                 lw_ptr->kurs_typ);
			break;


		case _PERSONEN:
			bytes=sizeof(PERSONEN);
			id_type=sizeof((PERSONEN *)pointer)->pers_id;
			(void)sprintf(query, _SELECT_PERS, id);
			break;
		case _REISENDER:
			bytes=sizeof(REISENDER);
			id_type=sizeof((REISENDER *)pointer)->pers_id;
			(void)sprintf(query, _SELECT_REI, id);
			break;
		case _REISENDER_TYP:
			bytes=sizeof(REISENDER_TYP);
			id_type=sizeof((REISENDER_TYP *)pointer)->rkr_id;
			(void)sprintf(query, _SELECT_REIT, id);
			break;
		case _KUNDEN_TYP:
			bytes=sizeof(KUNDEN_TYP);
			id_type=sizeof((KUNDEN_TYP *)pointer)->k_typ_id;
			(void)sprintf(query, _SELECT_KUNT, id);
			break;
		case _KUNDEN:
			bytes=sizeof(KUNDEN);
			id_type=sizeof((KUNDEN *)pointer)->pers_id;
			(void)sprintf(query, _SELECT_KUN, id);
			break;
		case _KOLLEKTIV_TYP:
			bytes=sizeof(KOLLEKTIV_TYP);
			id_type=sizeof((KOLLEKTIV_TYP *)pointer)->k_typ_id;
			(void)sprintf(query, _SELECT_KOLT, id);
			break;
		case _KOLLEKTIV:
			bytes=sizeof(KOLLEKTIV);
			id_type=sizeof((KOLLEKTIV *)pointer)->k_id;
			(void)sprintf(query, _SELECT_KOL, id);
			break;
		case _PERSADR:
			bytes=sizeof(PERSADR);
			id_type=sizeof((PERSADR *)pointer)->pers_id;
			(void)sprintf(query, _SELECT_PERSADR, id);
			break;


		case	_TRAEGER_TYP	:
			bytes=sizeof(TRAEGER_TYP);
			id_type=sizeof((TRAEGER_TYP *)pointer)->typ_id;
			(void)sprintf(query, _SELECT_DLTT, id);
			break;
		case	_KATEGORIE	:
			bytes=sizeof(KATEGORIE);
			id_type=sizeof((KATEGORIE *)pointer)->kat_id;
			(void)sprintf(query, _SELECT_KAT, id);
			break;
		case	_DIENST_TRAEGER:
			bytes=sizeof(DIENST_TRAEGER);
			id_type=sizeof((DIENST_TRAEGER *)pointer)->dlt_id;
			(void)sprintf(query, _SELECT_DLT, id);
			break;
		case	_ANGEBOTS_TYP	:
			bytes=sizeof(ANGEBOTS_TYP);
			id_type=sizeof((ANGEBOTS_TYP *)pointer)->art_id;
			(void)sprintf(query, _SELECT_DLAT, id);
			break;
		case	_AKTIONS_TYP	:
			bytes=sizeof(AKTIONS_TYP);
			id_type=sizeof((AKTIONS_TYP *)pointer)->a_typ_id;
			(void)sprintf(query, _SELECT_AKTT, id);
			break;
		case	_AKTIONSPARA:
			bytes=sizeof(AKTIONSPARA);
			id_type=sizeof((AKTIONSPARA *)pointer)->nr;
			(void)sprintf(query, _SELECT_APARA, ((AKTIONSPARA *)pointer)->a_typ_id,
			              ((AKTIONSPARA *)pointer)->nr);
			break;
		case	_AKTIONEN	:
			bytes=sizeof(AKTIONEN);
			id_type=sizeof((AKTIONEN *)pointer)->akt_id;
			(void)sprintf(query, _SELECT_AKT, id);
			break;
		case _AKTIONSGRP:
			bytes=sizeof(AKTIONSGRP);
			id_type=sizeof((AKTIONSGRP *)pointer)->childakt;
			(void)sprintf(query, _SELECT_AKTG, ((AKTIONSGRP *)pointer)->parentakt,
			      ((AKTIONSGRP *)pointer)->childakt);
			break;
		case	_DIENST_ANGEBOT	:
			bytes=sizeof(DIENST_ANGEBOT);
			id_type=sizeof((DIENST_ANGEBOT *)pointer)->dla_id;
			(void)sprintf(query, _SELECT_DLA, id);
			break;
		case	_DLG_PART	:
			bytes=sizeof(DLG_PART);
			id_type=sizeof((DLG_PART *)pointer)->dl_id;
			(void)sprintf(query, _SELECT_DLG, id);
			break;
		case	_DIENSTLEISTUNG	:
			bytes=sizeof(DIENSTLEISTUNG);
			id_type=sizeof((DIENSTLEISTUNG *)pointer)->dlg_id;
			(void)sprintf(query, _SELECT_DTG, id);
			break;
		case	_DLG_DLG	:
			dd_ptr=(DLG_DLG *)pointer;
			bytes=sizeof(DLG_DLG);
			id_type=sizeof((DLG_DLG *)pointer)->dlg_id;
			if (id == (int)IGNORE)
				(void)sprintf(query, _SELECT_DDO, dd_ptr->dlg_id, dd_ptr->ord);
			else
				(void)sprintf(query, _SELECT_DD, dd_ptr->dlg_id, dd_ptr->dl_id);
			break;
		case	_PROGRAMM	:
			bytes=sizeof(PROGRAMM);
			id_type=sizeof((PROGRAMM *)pointer)->prg_id;
			(void)sprintf(query, _SELECT_PRG, id);
			break;
		case	_ARRANGEMENT	:
			bytes=sizeof(ARRANGEMENT);
			id_type=sizeof((ARRANGEMENT *)pointer)->arr_id;
			(void)sprintf(query, _SELECT_ARR, id);
			break;
		case	_ARR_DLG	:
			ad_ptr=(ARR_DLG *)pointer;
			bytes=sizeof(ARR_DLG);
			id_type=sizeof((ARR_DLG *)pointer)->arr_id;
			if (id == (int)IGNORE) /* IGNORE means that we don't know the TEIL no */
				(void)sprintf(query, _SELECT_AD, ad_ptr->arr_id, ad_ptr->dlg_id);
			else
				(void)sprintf(query, _SELECT_ADT, ad_ptr->arr_id, ad_ptr->teil, ad_ptr->prio);
			break;


		case _HOST_KONT:
			bytes=sizeof(HOST_KONT);
			id_type=sizeof((HOST_KONT *)pointer)->hostkont_id;
			(void)sprintf(query, _SELECT_HKON, id);
			break;
		case _KONTINGENT:
			bytes=sizeof(KONTINGENT);
			id_type=sizeof((KONTINGENT *)pointer)->kont_id;
			(void)sprintf(query, _SELECT_KON, id);
			break;
		case _KONT_DETAIL:
			bytes=sizeof(KONT_DETAIL);
			id_type=sizeof((KONT_DETAIL *)pointer)->kont_id;
			Pkond = (KONT_DETAIL *)pointer;
			if (Pkond->hostkont_id != (int)_UNDEF)
				(void)sprintf(query, _SELECT_KD_HKON, Pkond->hostkont_id,
				              Pkond->kat_id, Pkond->dlt_id);
			else
				(void)sprintf(query, _SELECT_KD_KON, Pkond->kont_id,
				              Pkond->kat_id, Pkond->dlt_id);
			break;


		case _BUCHUNG:
			bytes=sizeof(BUCHUNG);
			id_type=sizeof((BUCHUNG *)pointer)->bid;
			(void)sprintf(query, _SELECT_BCH, id);
			break;
		case _KOSTEN_ART:
			bytes=sizeof(KOSTEN_ART);
			id_type=sizeof((KOSTEN_ART *)pointer)->kar_id;
			(void)sprintf(query, _SELECT_KAR, id);
			break;
		case _KOMMISSION:
			bytes=sizeof(KOMMISSION);
			kom_ptr=(KOMMISSION *)pointer;
			(void)sprintf(query, _SELECT_KOM, id);
			break;
		case _KOMM_DETAIL:
			bytes=sizeof(KOMM_DETAIL);
			kd_ptr=(KOMM_DETAIL *)pointer;
			(void)sprintf(query, _SELECT_KOMD, kd_ptr->komm_id, kd_ptr->dln_id,
			                                   kd_ptr->kun_id, kd_ptr->kol_id);
			break;
		case _RESERVATION:
			bytes=sizeof(RESERVATION);
			Pres = (RESERVATION *)pointer;
			id_type=sizeof((RESERVATION *)pointer)->pers_id;
			if ( Pres->pers_id == (int)_UNDEF && Pres->dl_id == (int)_UNDEF &&
				  Pres->teil == (int)_UNDEF )
			{
				table = (int)_INTEGER;
				(void)sprintf(query, _SELECT_RES_DL_DIST, Pres->bid);
			}
			else
			{
				(void)sprintf(query, _SELECT_RES, ((RESERVATION *)pointer)->pers_id,
								  ((RESERVATION *)pointer)->dl_id,
								  ((RESERVATION *)pointer)->teil,
								  ((RESERVATION *)pointer)->bid);
			}
			break;
		case _PREIS:
			bytes=sizeof(PREIS);
			pre_ptr=(PREIS *)pointer;
			(void)sprintf(query, _SELECT_PRE, pre_ptr->kar_id, pre_ptr->dla_id, pre_ptr->dl_id,
							pre_ptr->kat_id,pre_ptr->kont_id,pre_ptr->rkr_id,pre_ptr->glt);
			break;


		case _GRAPHIK:
			bytes=sizeof(GRAPHIK);
			id_type=sizeof((GRAPHIK *)pointer)->gra_id;
			(void)sprintf(query, _SELECT_GRA, id);
			break;
		case _PCX_FILES:
			bytes=sizeof(PCX_FILES);
			id_type=sizeof((PCX_FILES *)pointer)->pcx_id;
			(void)sprintf(query, _SELECT_PCX, id);
			break;


		case _SPR_VIEW:
			bytes=sizeof(SPR_VIEW);
			id_type=sizeof((SPR_VIEW *)pointer)->s_id;
			(void)sprintf(query, _SELECT_SPRV, id);
			break;
		case _STA_VIEW:
			bytes=sizeof(STA_VIEW);
			stv_ptr=(STA_VIEW *)pointer;
			id_type=sizeof(stv_ptr->sta_id);
			(void)sprintf(query, _SELECT_STAV, sprache, id, stv_ptr->typ);
			break;
		case _SAI_VIEW:
			bytes=sizeof(SAI_VIEW);
			id_type=sizeof((SAI_VIEW *)pointer)->sai_id;
			(void)sprintf(query, _SELECT_SAIV, id, sprache);
			break;
		case _LAND_VIEW:
			bytes=sizeof(LAND_VIEW);
			id_type=sizeof((LAND_VIEW *)pointer)->land_id;
			(void)sprintf(query, _SELECT_LANDV, id, sprache);
			break;
		case _KUN_VIEW:
			bytes=sizeof(KUN_VIEW);
			id_type=sizeof((KUN_VIEW *)pointer)->kun_id;
			(void)sprintf(query, _SELECT_KUNV, id);
			break;
		case _MPV_KUNADR:
			bytes=sizeof(MPV_KUNADR);
			id_type=sizeof((MPV_KUNADR *)pointer)->pers_id;
			(void)sprintf(query, _SELECT_KUNADRV, id);
			break;
		case _DLN_VIEW:
			bytes=sizeof(DLN_VIEW);
			id_type=sizeof((DLN_VIEW *)pointer)->dln_id;
			(void)sprintf(query, _SELECT_DLNV, id);
			break;
		case	_RKR_VIEW	:
			bytes=sizeof(RKR_VIEW);
			id_type=sizeof((RKR_VIEW *)pointer)->rkr_id;
			(void)sprintf(query, _SELECT_REITV, id, sprache);
			break;
		case	_TTYP_VIEW	:
			bytes=sizeof(TTYP_VIEW);
			id_type=sizeof((TTYP_VIEW *)pointer)->id;
			(void)sprintf(query, _SELECT_TTYP, id, sprache);
			break;
		case	_KAT_VIEW	:
			bytes=sizeof(KAT_VIEW);
			id_type=sizeof((KAT_VIEW *)pointer)->kat_id;
			(void)sprintf(query, _SELECT_KATV, id, sprache);
			break;
		case	_DLT_VIEW	:
			bytes=sizeof(DLT_VIEW);
			id_type=sizeof((DLT_VIEW *)pointer)->dlt_id;
			(void)sprintf(query, _SELECT_DLTV, id, sprache);
			break;
		case	_TRAEGER_VIEW	:
			bytes=sizeof(TRAEGER_VIEW);
			id_type=sizeof((TRAEGER_VIEW *)pointer)->id;
			(void)sprintf(query, _SELECT_TRV, id, sprache);
			break;
		case _DLA_VIEW:
			bytes=sizeof(DLA_VIEW);
			id_type=sizeof((DLA_VIEW *)pointer)->dla_id;
			(void)sprintf(query, _SELECT_DLAV, id, sprache);
			break;
		case _DTG_VIEW:
			bytes=sizeof(DTG_VIEW);
			id_type=sizeof((DTG_VIEW *)pointer)->dlg_id;
			(void)sprintf(query, _SELECT_DTGV, id, sprache);
			break;
		case _KAR_VIEW:
			bytes=sizeof(KAR_VIEW);
			id_type=sizeof((KAR_VIEW *)pointer)->kar_id;
			(void)sprintf(query, _SELECT_KARV, id, sprache);
			break;
		case _ROUTEN_VIEW:
			bytes=sizeof(ROUTEN_VIEW);
			id_type=sizeof((ROUTEN_VIEW *)pointer)->dlg_id;
			(void)sprintf(query, _SELECT_ROUT, id);
			break;
		default:
			status=(int)_UNDEF;   /* MPE_WRONGOBJECT */
			break;
		}

	if (status == (int)MPOK)
		{
		status=MPAPIdb_sqlquery(table, &apimem.buffer, query, &anzahl,
		                         &apimem.datalen, &apimem.alloclen);
		if (status == (int)MPOK)
			{
			if (anzahl == (int)1)  /* can only read one entry here !! */
				{
				(void)memcpy((void *)pointer, (void *)apimem.buffer, (size_t)bytes);
				switch(id_type)
					{
					case sizeof(short):
						id=(int)*(short *)apimem.buffer;
						break;
					case sizeof(int)  :
						id=(int)*(int *)apimem.buffer;
						break;
					}
				}
			else
				{
				if (table != (int)_BEZEICHNUNG)
					id = (int)_UNDEF;
				else
					id = (int)MPOK;
				}
			}
		else
			id = (int)_UNDEF;
		}
	else
		id = (int)_UNDEF;

	return(id);
}
