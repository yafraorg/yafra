/*D***********************************************************
 * Modul:     DBI - table ID count
 *            send back the count of ID's in a table
 *            send back _UNDEF if nothing or error
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>
#include <mpsqlcnt.h>		/* SQL COUNT statements */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilIDcount.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

int MPAPIid_count(int id_typ , int table , char *pointer )
{
	extern MEMOBJ apimem;

	DIENST_TRAEGER *dlt_ptr;
	TRAEGER_TYP *dltt_ptr;
	DIENST_ANGEBOT *dla_ptr;
	ANGEBOTS_TYP *art_ptr;
	STATUS_WERTE *sta_ptr;
	AKTIONEN *akt_ptr;
	AKTIONS_TYP *aktt_ptr;
	KATEGORIE *kat_ptr;
	KUNDEN *kun_ptr;
	KUNDEN_TYP *kunt_ptr;
	REISENDER_TYP *rkr_ptr;
	KOSTEN_ART *kar_ptr;
	KOLLEKTIV_TYP *kolt_ptr;
	PROGRAMM *prg_ptr;
	REISENDER *rei_ptr;
	KOLLEKTIV *kol_ptr;
	SAISON *sai_ptr;
	ARRANGEMENT *arr_ptr;
	DLG_PART *dlg_ptr;
	DIENSTLEISTUNG *dtg_ptr;
	BUCHUNG *bch_ptr;
	KONTINGENT *kont_ptr;
	KONT_DETAIL *kd_ptr;
	PCX_FILES *pcx_ptr;
	BEZEICHNUNG *bez_ptr;
	TEXTE *txt_ptr;
	SPRACHEN *spr_ptr;
	KOMMISSION *kom_ptr;
	PREIS *pre_ptr;
	HOST_KONT *Phkon;

	char query[_QUERYLEN];
	int anzahl, i;
	int status=(int)MPOK;
	int count;

	switch(table)
		{
		case _SPRACHEN:
			switch(id_typ)
				{
				case _BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_SPR_BEZ, bez_ptr->bez_id);
					break;
				}
			break;
		case _STATUS_WERTE:
			switch(id_typ)
				{
				case _BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_STA_BEZ, bez_ptr->bez_id, bez_ptr->typ);
					break;
				}
			break;
		case _BEZEICHNUNG:
			switch(id_typ)
				{
				case _BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					if (bez_ptr->bez_id == (int)_UNDEF && bez_ptr->s_id == (int)_UNDEF)
						(void)sprintf(query, _COUNT_BEZ_TYP, bez_ptr->typ);
					else if (bez_ptr->bez_id != (int)_UNDEF && bez_ptr->s_id == (int)_UNDEF)
						(void)sprintf(query, _COUNT_BEZ_BEZTYP, bez_ptr->bez_id, bez_ptr->typ);
					else
						(void)sprintf(query, _COUNT_BEZ_SPRBEZTYP, bez_ptr->bez_id,
										  bez_ptr->s_id, bez_ptr->typ);
					break;
				case _SPRACHEN:
					spr_ptr=(SPRACHEN *)pointer;
					(void)sprintf(query, _COUNT_BEZ_SPR, spr_ptr->s_id);
					break;
				}
			break;
		case _TEXTE:
			switch(id_typ)
				{
				case _SPRACHEN:
					spr_ptr=(SPRACHEN *)pointer;
					(void)sprintf(query, _COUNT_TXT_SPR, spr_ptr->s_id);
					break;
				}
			break;
		case _SAISON:
			switch(id_typ)
				{
				case _BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_SAI_BEZ, bez_ptr->bez_id);
					break;
				case _TEXTE:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_SAI_TXT, txt_ptr->textid);
					break;
				}
			break;




		case _PERSONEN:
			switch(id_typ)
				{
				case _SPRACHEN:
					spr_ptr = (SPRACHEN *)pointer;
					(void)sprintf(query, _COUNT_PERS_SPR, spr_ptr->s_id);
					break;
				}
			break;
		case _KUNDEN		:
			switch(id_typ) {
				case	_KUNDEN_TYP	:
					kunt_ptr=(KUNDEN_TYP *)pointer;
					(void)sprintf(query, _COUNT_KUN_KUNT, kunt_ptr->k_typ_id);
					break;
			}
			break;
		case _KUNDEN_TYP	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KUNT_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KUNT_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _REISENDER:
			switch(id_typ) {
				case	_REISENDER_TYP	:
					rkr_ptr=(REISENDER_TYP *)pointer;
					(void)sprintf(query, _COUNT_DLN_DLNT, rkr_ptr->rkr_id);
					break;
			}
			break;
		case _REISENDER_TYP	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DLNT_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_DLNT_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _KOLLEKTIV		:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KOL_BEZ, bez_ptr->bez_id);
					break;
				case	_REISENDER	:
					rei_ptr=(REISENDER *)pointer;
					(void)sprintf(query, _COUNT_KOL_DLN, rei_ptr->pers_id);
					break;
				case	_KOLLEKTIV_TYP		:
					kolt_ptr=(KOLLEKTIV_TYP *)pointer;
					(void)sprintf(query, _COUNT_KOL_KOLT, kolt_ptr->k_typ_id);
					break;
				case	_KUNDEN			:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_KOL_KUN, kun_ptr->pers_id, kun_ptr->pers_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KOL_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _KOLLEKTIV_TYP:
			switch(id_typ) {
				case	_BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KOLT_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KOLT_TXT, txt_ptr->textid);
					break;
			}
			break;





		case _TRAEGER_TYP	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DLTT_BEZ, bez_ptr->bez_id);
					break;
				case	_TRAEGER_TYP	:
					dltt_ptr=(TRAEGER_TYP *)pointer;
					(void)sprintf(query, _COUNT_DLTT_DLTT, dltt_ptr->typ_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_DLTT_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _KATEGORIE		:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KAT_BEZ, bez_ptr->bez_id);
					break;
				case	_KATEGORIE	:
					kat_ptr=(KATEGORIE *)pointer;
					(void)sprintf(query, _COUNT_KAT_KAT, kat_ptr->kat_id);
					break;
				case	_TRAEGER_TYP	:
					dltt_ptr=(TRAEGER_TYP *)pointer;
					(void)sprintf(query, _COUNT_KAT_DLTT, dltt_ptr->typ_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KAT_TXT, txt_ptr->textid);
					break;
				case	_STATUS_WERTE		:
					sta_ptr=(STATUS_WERTE *)pointer;
					(void)sprintf(query, _COUNT_KAT_STA, sta_ptr->sta_id);
					break;
			}
			break;
		case _DIENST_TRAEGER	:
			switch(id_typ) {
				case	_DIENST_TRAEGER	:
					dlt_ptr=(DIENST_TRAEGER *)pointer;
					(void)sprintf(query, _COUNT_DLT_DLT, dlt_ptr->dlt_id);
					break;
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DLT_BEZ, bez_ptr->bez_id);
					break;
				case	_KATEGORIE	:
					kat_ptr=(KATEGORIE *)pointer;
					(void)sprintf(query, _COUNT_DLT_KAT, kat_ptr->kat_id);
					break;
				case	_TRAEGER_TYP	:
					dltt_ptr=(TRAEGER_TYP *)pointer;
					(void)sprintf(query, _COUNT_DLT_DLTT, dltt_ptr->typ_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_DLT_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _ANGEBOTS_TYP	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_ART_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE	:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_ART_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _AKTIONS_TYP	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_AKTT_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_AKTT_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _AKTIONSPARA:
			switch(id_typ) {
				case _AKTIONS_TYP:
					aktt_ptr=(AKTIONS_TYP *)pointer;
					(void)sprintf(query, _COUNT_AKTP_AKTT, aktt_ptr->a_typ_id);
					break;
			}
			break;
		case _AKTIONEN:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_AKT_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_AKT_TXT, txt_ptr->textid);
					break;
				case	_AKTIONS_TYP	:
					aktt_ptr=(AKTIONS_TYP *)pointer;
					(void)sprintf(query, _COUNT_AKT_AKTT, aktt_ptr->a_typ_id);
					break;
			}
			break;
		case _AKTIONSGRP:
			switch(id_typ) {
				case _AKTIONEN:
					/* search for AKTIONEN as parent or child */
					akt_ptr=(AKTIONEN *)pointer;
					(void)sprintf(query, _COUNT_AKTG_AKT, akt_ptr->akt_id,
					              akt_ptr->akt_id);
					break;
			}
			break;
		case _DIENST_ANGEBOT	:
			switch(id_typ) {
				case	_DIENST_ANGEBOT	:
					dla_ptr=(DIENST_ANGEBOT *)pointer;
					(void)sprintf(query, _COUNT_DLA_DLA, dla_ptr->dla_id);
					break;
				case	_DIENST_TRAEGER	:
					dlt_ptr=(DIENST_TRAEGER *)pointer;
					(void)sprintf(query, _COUNT_DLA_DLT, dlt_ptr->dlt_id);
					break;
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DLA_BEZ, bez_ptr->bez_id);
					break;
				case	_AKTIONEN	:
					akt_ptr=(AKTIONEN *)pointer;
					(void)sprintf(query, _COUNT_DLA_AKT, akt_ptr->akt_id);
					break;
				case	_ANGEBOTS_TYP	:
					art_ptr=(ANGEBOTS_TYP *)pointer;
					(void)sprintf(query, _COUNT_DLA_ART, art_ptr->art_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_DLA_TXT, txt_ptr->textid);
					break;
// TODO what's that
				case	_KATEGORIE	:
					pre_ptr=(PREIS *)pointer;
					(void)sprintf(query, _COUNT_DLA_KAT, pre_ptr->dla_id, pre_ptr->kat_id);
					break;
			}
			break;
		case _DLG_PART	:
			switch(id_typ) {
				case	_DIENST_ANGEBOT	:
					dla_ptr=(DIENST_ANGEBOT *)pointer;
					(void)sprintf(query, _COUNT_DLG_DLA, dla_ptr->dla_id);
					break;
				case	_DLG_PART	:
					dlg_ptr=(DLG_PART *)pointer;
					(void)sprintf(query, _COUNT_DLG_DLG, dlg_ptr->dl_id);
					break;
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DLG_BEZ, bez_ptr->bez_id);
					break;
				case	_KUNDEN		:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_DLG_KUN, kun_ptr->pers_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_DLG_TXT, txt_ptr->textid);
					break;
				case	_SAISON		:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_DLG_SAI, sai_ptr->sai_id);
					break;
// TODO what's that
				case	_KATEGORIE	:
					pre_ptr=(PREIS *)pointer;
					(void)sprintf(query, _COUNT_DLG_KAT, pre_ptr->dl_id, pre_ptr->kat_id);
					break;
			}
			break;
		case _DIENSTLEISTUNG	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_DL_BEZ, bez_ptr->bez_id);
					break;
				case	_AKTIONEN	:
					akt_ptr=(AKTIONEN *)pointer;
					(void)sprintf(query, _COUNT_DL_AKT, akt_ptr->akt_id);
					break;
				case	_SAISON		:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_DL_SAI, sai_ptr->sai_id);
					break;
// TODO what's that
				case	_KATEGORIE	:
					pre_ptr=(PREIS *)pointer;
					(void)sprintf(query, _COUNT_DLG_KAT, pre_ptr->dl_id, pre_ptr->kat_id);
					break;
			}
			break;
		case _DLG_DLG:
			switch(id_typ) {
				case	_DLG_PART	:
					dlg_ptr=(DLG_PART *)pointer;
					(void)sprintf(query, _COUNT_DD_DLG, dlg_ptr->dl_id);
					break;
				case	_DIENSTLEISTUNG	:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_DD_DL, dtg_ptr->dlg_id);
					break;
			}
			break;
		case _PROGRAMM:
			switch(id_typ) {
				case	_BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_PRG_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_PRG_TXT, txt_ptr->textid);
					break;
				case	_SAISON:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_PRG_SAI, sai_ptr->sai_id);
					break;
			}
			break;
		case _ARRANGEMENT	:
			switch(id_typ) {
				case	_BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_ARR_BEZ, bez_ptr->bez_id);
					break;
				case	_PROGRAMM:
					prg_ptr=(PROGRAMM *)pointer;
					(void)sprintf(query, _COUNT_ARR_PRG, prg_ptr->prg_id);
					break;
				case	_TEXTE:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_ARR_TXT, txt_ptr->textid);
					break;
				case	_SAISON:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_ARR_SAI, sai_ptr->sai_id);
					break;
			}
			break;
		case _ARR_DLG		:
			switch(id_typ) {
				case	_ARR_DLG	:
					arr_ptr=(ARRANGEMENT *)pointer;
					(void)sprintf(query, _COUNT_ARRD_MAX, arr_ptr->arr_id);
					break;
				case	_ARRANGEMENT:
					arr_ptr=(ARRANGEMENT *)pointer;
					(void)sprintf(query, _COUNT_ARRD_ARR, arr_ptr->arr_id);
					break;
				case	_DIENSTLEISTUNG:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_ARRD_DL, dtg_ptr->dlg_id);
					break;
				case	_STATUS_WERTE:
					sta_ptr=(STATUS_WERTE *)pointer;
					(void)sprintf(query, _COUNT_ARRD_STA, sta_ptr->sta_id);
					break;
			}
			break;





		case _HOST_KONT:
			switch(id_typ)
				{
				case _BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_HKON_BEZ, bez_ptr->bez_id);
					break;
				case _KUNDEN:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_HKON_KUN, kun_ptr->pers_id,
					              kun_ptr->pers_id);
					break;
				case	_DIENST_ANGEBOT:
					dla_ptr=(DIENST_ANGEBOT *)pointer;
					(void)sprintf(query, _COUNT_HKON_DLA, dla_ptr->dla_id);
					break;
				case	_DIENSTLEISTUNG:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_HKON_DL, dtg_ptr->dlg_id);
					break;
				}
			break;
		case _KONTINGENT:
			switch(id_typ)
				{
				case _HOST_KONT:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_KON_HKON, kun_ptr->pers_id);
					break;
				case _KUNDEN:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_KON_KUN, kun_ptr->pers_id);
					break;
				case	_BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KON_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KON_TXT, txt_ptr->textid);
					break;
				case	_SAISON:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_KON_SAI, sai_ptr->sai_id);
					break;
				}
			break;
		case _KONT_DETAIL:
			switch(id_typ)
				{
				case _KONTINGENT:
					kont_ptr=(KONTINGENT *)pointer;
					(void)sprintf(query, _COUNT_KOND_KON, kont_ptr->kont_id);
					break;
				case _HOST_KONT:
					Phkon=(HOST_KONT *)pointer;
					(void)sprintf(query, _COUNT_KOND_HKON, Phkon->hostkont_id);
					break;
				case	_DIENST_TRAEGER:
					kd_ptr=(KONT_DETAIL *)pointer;
					(void)sprintf(query, _COUNT_KOND_DLT, kd_ptr->dlt_id);
					break;
				case	_KATEGORIE:
					/* In Preis Menu gefragt */
					/*************************/
					kat_ptr=(KATEGORIE *)pointer;
					(void)sprintf(query, _COUNT_KOND_KAT, kat_ptr->kat_id);
					break;
				}
			break;






		case _BUCHUNG:
			switch(id_typ) {
				case _BUCHUNG:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_BCH_BCH, bch_ptr->bid);
					break;
				case	_ARRANGEMENT:
					arr_ptr=(ARRANGEMENT *)pointer;
					(void)sprintf(query, _COUNT_BCH_ARR, arr_ptr->arr_id);
					break;
				case	_KUNDEN		:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_BCH_KUN, kun_ptr->pers_id, kun_ptr->pers_id);
					break;
				case	_AKTIONEN	:
					akt_ptr=(AKTIONEN *)pointer;
					(void)sprintf(query, _COUNT_BCH_AKT, akt_ptr->akt_id);
					break;
				case	_SAISON		:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_BCH_SAI, sai_ptr->sai_id);
					break;
				case	_R_STA		:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_BCH_RSTA, bch_ptr->bid);
					break;
				case	_KOLLEKTIV	:
					kol_ptr=(KOLLEKTIV *)pointer;
					(void)sprintf(query, _COUNT_BCH_KOL, kol_ptr->k_id);
					break;
			}
			break;
		case _BCH_DLN:
			switch(id_typ) {
				case _BUCHUNG:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_BD_BCH, bch_ptr->bid);
					break;
				case _REISENDER:
					rei_ptr=(REISENDER *)pointer;
					(void)sprintf(query, _COUNT_BD_DLN, rei_ptr->pers_id);
					break;
			}
			break;
		case _AKT_DETAIL	:
			switch(id_typ) {
				case	_AKTIONEN	:
					akt_ptr=(AKTIONEN *)pointer;
					(void)sprintf(query, _COUNT_AD_AKT, akt_ptr->akt_id);
					break;
				case	_AKTIONS_TYP	:
					aktt_ptr=(AKTIONS_TYP *)pointer;
					(void)sprintf(query, _COUNT_AD_AKTT, aktt_ptr->a_typ_id);
					break;
				case	_BUCHUNG	:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_AD_BCH, bch_ptr->bid);
					break;
				case	_DLG_PART	:
					dlg_ptr=(DLG_PART *)pointer;
					(void)sprintf(query, _COUNT_AD_DLG, dlg_ptr->dl_id);
					break;
				case	_DIENSTLEISTUNG	:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_AD_DL, dtg_ptr->dlg_id);
					break;
				case	_REISENDER	:
					rei_ptr=(REISENDER *)pointer;
					(void)sprintf(query, _COUNT_AD_DLN, rei_ptr->pers_id);
					break;
			}
			break;
		case _KOSTEN_ART	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KAR_BEZ, bez_ptr->bez_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_KAR_TXT, txt_ptr->textid);
					break;
			}
			break;
		case _KOMMISSION	:
			switch(id_typ) {
				case	_BEZEICHNUNG	:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_KOM_BEZ, bez_ptr->bez_id);
					break;
				case	_DIENST_ANGEBOT	:
					dla_ptr=(DIENST_ANGEBOT *)pointer;
					(void)sprintf(query, _COUNT_KOM_DLA, dla_ptr->dla_id);
					break;
				case	_DIENSTLEISTUNG	:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_KOM_DL, dtg_ptr->dlg_id);
					break;
				case	_KUNDEN		:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_KOM_KUN, kun_ptr->pers_id);
					break;
			}
			break;
		case _KOMM_DETAIL	:
			switch(id_typ) {
				case _KOMMISSION:
					kom_ptr=(KOMMISSION *)pointer;
					(void)sprintf(query, _COUNT_KOMD_KOM, kom_ptr->komm_id);
					break;
				case _BUCHUNG:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_KOMD_BCH, bch_ptr->bid);
					break;
				case _REISENDER:
					rei_ptr=(REISENDER *)pointer;
					(void)sprintf(query, _COUNT_KOMD_DLN, rei_ptr->pers_id);
					break;
				case _KUNDEN:
					kun_ptr=(KUNDEN *)pointer;
					(void)sprintf(query, _COUNT_KOMD_KUN, kun_ptr->pers_id);
					break;
				case _KOLLEKTIV:
					kol_ptr=(KOLLEKTIV *)pointer;
					(void)sprintf(query, _COUNT_KOMD_KOL, kol_ptr->k_id);
					break;
			}
			break;
		case _PREIS		:
			switch(id_typ) {
				case	_KOSTEN_ART	:
					kar_ptr=(KOSTEN_ART *)pointer;
					(void)sprintf(query, _COUNT_PRE_KAR, kar_ptr->kar_id);
					break;
				case	_DIENST_ANGEBOT	:
					dla_ptr=(DIENST_ANGEBOT *)pointer;
					(void)sprintf(query, _COUNT_PRE_DLA, dla_ptr->dla_id);
					break;
				case	_DIENSTLEISTUNG	:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_PRE_DL, dtg_ptr->dlg_id);
					break;
				case	_KATEGORIE	:
					kat_ptr=(KATEGORIE *)pointer;
					(void)sprintf(query, _COUNT_PRE_KAT, kat_ptr->kat_id);
					break;
				case	_KONTINGENT	:
					kont_ptr=(KONTINGENT *)pointer;
					(void)sprintf(query, _COUNT_PRE_KON, kont_ptr->kont_id);
					break;
				case	_REISENDER_TYP	:
					rkr_ptr=(REISENDER_TYP *)pointer;
					(void)sprintf(query, _COUNT_PRE_DLNT, rkr_ptr->rkr_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_PRE_TXT, txt_ptr->textid);
					break;
				case	_SAISON		:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_PRE_SAI, sai_ptr->sai_id);
					break;
			}
			break;
		case _RESERVATION	:
			switch(id_typ) {
				case _TRAEGER_TYP:
					dltt_ptr=(TRAEGER_TYP *)pointer;
					(void)sprintf(query, _COUNT_RES_DLTT, dltt_ptr->typ_id);
					break;
				case	_DIENST_TRAEGER	:
					dlt_ptr=(DIENST_TRAEGER *)pointer;
					(void)sprintf(query, _COUNT_RES_DLT, dlt_ptr->dlt_id);
					break;
				case	_BUCHUNG	:
					bch_ptr=(BUCHUNG *)pointer;
					(void)sprintf(query, _COUNT_RES_BCH, bch_ptr->bid);
					break;
				case	_KONTINGENT	:
					kont_ptr=(KONTINGENT *)pointer;
					(void)sprintf(query, _COUNT_RES_KON, kont_ptr->kont_id);
					break;
				case	_KATEGORIE	:
					kat_ptr=(KATEGORIE *)pointer;
					(void)sprintf(query, _COUNT_RES_KAT, kat_ptr->kat_id);
					break;
				case	_SAISON		:
					sai_ptr=(SAISON *)pointer;
					(void)sprintf(query, _COUNT_RES_SAI, sai_ptr->sai_id);
					break;
				case	_REISENDER		:
					rei_ptr=(REISENDER *)pointer;
					(void)sprintf(query, _COUNT_RES_DLN, rei_ptr->pers_id);
					break;
				case	_DLG_PART		:
					dlg_ptr=(DLG_PART *)pointer;
					(void)sprintf(query, _COUNT_RES_DLG, dlg_ptr->dl_id);
					break;
				case	_DIENSTLEISTUNG		:
					dtg_ptr=(DIENSTLEISTUNG *)pointer;
					(void)sprintf(query, _COUNT_RES_DL, dtg_ptr->dlg_id);
					break;
			}
			break;





		case _PCX_FILES		:
			switch(id_typ) {
				case _DIENST_TRAEGER:
					dlt_ptr=(DIENST_TRAEGER *)pointer;
					(void)sprintf(query, _COUNT_PCX_DLT, dlt_ptr->dlt_id);
					break;
				case	_BEZEICHNUNG:
					bez_ptr=(BEZEICHNUNG *)pointer;
					(void)sprintf(query, _COUNT_PCX_BEZ, bez_ptr->bez_id);
					break;
			}
			break;
		case _GRAPHIK:
			switch(id_typ) {
				case	_DIENST_TRAEGER	:
					dlt_ptr=(DIENST_TRAEGER *)pointer;
					(void)sprintf(query, _COUNT_GRA_DLT, dlt_ptr->dlt_id);
					break;
				case	_TEXTE		:
					txt_ptr=(TEXTE *)pointer;
					(void)sprintf(query, _COUNT_GRA_TXT, txt_ptr->textid);
					break;
			}
			break;

		default:
			return((int)_UNDEF);
			break;
		}

	status=MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, query, &anzahl,
	                         &apimem.datalen, &apimem.alloclen);
	if (status == (int)MPOK && anzahl > 0)
		(void)memcpy((void *)&count, (void *)apimem.buffer, sizeof(int));
	else
		count = (int)_UNDEF;

	return(count);
}
