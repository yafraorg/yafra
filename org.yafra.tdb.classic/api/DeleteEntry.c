/*D***********************************************************
 * Modul:     DBI - database delete                           
 *            delete an entry of an entity
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqldel.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/DeleteEntry.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

int MPAPIdeleteEntry(int table , char *datastring )
{
	AKTIONEN *akt;
	AKTIONS_TYP *aktt;
	AKTIONSPARA *apara;
	AKTIONSGRP *agrp;
	AKT_DETAIL *adptr;
	ARRANGEMENT *arr;
	ARR_DLG *ad;
	ANGEBOTS_TYP *dlat;
	BUCHUNG *bch;
	BCH_DLN *bdptr;
	DIENST_ANGEBOT *dla;
	DIENSTLEISTUNG *dtg;
	DLG_PART *dlg;
	DLG_DLG *dd;
	RESERVATION *res;
	DIENST_TRAEGER *dlt;
	TRAEGER_TYP *dltt;
	GRAPHIK *gra;
	KATEGORIE *kat;
	KOLLEKTIV *kol;
	KOLLEKTIV_TYP *kolt;
	KONTINGENT *kon;
	KONT_DETAIL *k_d;
	KOMMISSION *kom;
	KOMM_DETAIL *kd;
	KUNDEN *kun;
	KUNDEN_TYP *kunt;
	MAXIMA *maxima;
	PCX_FILES *pcx;
	PREIS *pre;
	PROGRAMM *prg;
	REISENDER *rei;
	REISENDER_TYP *reit;
	KOSTEN_ART *kar;
	SAISON *sai;
	SPRACHEN *spr;
	STATUS_WERTE *sta;
	TEXTE *txt;
	BEZEICHNUNG *bez_ptr;
	LAND *land;
	ORT *ort;
	WAEHRUNG *whr;
	LAND_SPR *ls;
	LAND_WHR *lw;
	MP_MSG *msg;
	HISTORY *his;
	PERSONEN *pers;
	PERSADR *persadr;
	HOST_KONT *hkon;
	KAPA *kapa;
	MP_ARRKOM *arrkom;

	char command[_QUERYLEN];
	int status=(int)MPOK;
	int anzahl;

	switch(table)
		{
		case _MAXIMA:
			maxima = (MAXIMA *)datastring;
			(void)sprintf(command, _DELETE_MAX, maxima->tabelle, maxima->typ);
			break;
		case	_SPRACHEN	:
			spr=(SPRACHEN *)datastring;
			(void)sprintf(command, _DELETE_SPR, spr->s_id);
			break;
		case	_STATUS_WERTE	:
			sta=(STATUS_WERTE *)datastring;
			(void)sprintf(command, _DELETE_STA, sta->sta_id, sta->typ);
			break;
		case	_TEXTE	:
			txt=(TEXTE *)datastring;
			if (ACTIONTYP == (unsigned char)UPDATE)
				(void)sprintf(command, _DELETE_SID_TXT, txt->textid, txt->typ, txt->s_id);
			else
				(void)sprintf(command, _DELETE_TXT, txt->textid, txt->typ);
			break;
		case	_BEZEICHNUNG	:
			bez_ptr=(BEZEICHNUNG *)datastring;
			if (bez_ptr->bez_id < 1)
				return((int)MPE_BEZDELWRONG);
			(void)sprintf(command, _DELETE_BEZ, bez_ptr->bez_id, bez_ptr->typ);
			break;
		case _HISTORY:
			his=(HISTORY *)datastring;
			(void)sprintf(command, _DELETE_HIS, his->his_id);
			break;
		case _MSG:
			msg=(MP_MSG *)datastring;
			(void)sprintf(command, _DELETE_MSG, msg->msg_id);
			break;
		case	_SAISON	:
			sai=(SAISON *)datastring;
			(void)sprintf(command, _DELETE_SAI, sai->sai_id);
			break;




		case _WAEHRUNG:
			whr=(WAEHRUNG *)datastring;
			(void)sprintf(command, _DELETE_WHR, whr->whr_id);
			break;
		case _LAND:
			land=(LAND *)datastring;
			(void)sprintf(command, _DELETE_LAND, land->land_id);
			break;
		case _ORT:
			ort=(ORT *)datastring;
			(void)sprintf(command, _DELETE_ORT, ort->ort_id);
			break;
		case _LAND_SPR:
			ls=(LAND_SPR *)datastring;
			(void)sprintf(command, _DELETE_LS, ls->land_id, ls->s_id);
			break;
		case _LAND_WHR:
			lw=(LAND_WHR *)datastring;
			if (lw->kurs_typ == (int)_UNDEF)
				(void)sprintf(command, _DELETE_LWALL, lw->land_id, lw->whr_id);
			else
				(void)sprintf(command, _DELETE_LW, lw->land_id, lw->whr_id, lw->kurs_typ);
			break;
			




		case _PERSONEN:
			pers=(PERSONEN *)datastring;
			(void)sprintf(command, _DELETE_PERS, pers->pers_id);
			break;
		case _PERSADR:
			persadr=(PERSADR *)datastring;
			(void)sprintf(command, _DELETE_PERSADR, persadr->pers_id);
			break;
		case	_REISENDER_TYP	:
			reit=(REISENDER_TYP *)datastring;
			(void)sprintf(command, _DELETE_REIT, reit->rkr_id);
			break;
		case	_REISENDER	:
			rei=(REISENDER *)datastring;
			(void)sprintf(command, _DELETE_REI, rei->pers_id);
			break;
		case	_KUNDEN_TYP	:
			kunt=(KUNDEN_TYP *)datastring;
			(void)sprintf(command, _DELETE_KUNT, kunt->k_typ_id);
			break;
		case	_KUNDEN	:
			kun=(KUNDEN *)datastring;
			(void)sprintf(command, _DELETE_KUN, kun->pers_id);
			break;
		case	_KOLLEKTIV_TYP	:
			kolt=(KOLLEKTIV_TYP *)datastring;
			(void)sprintf(command, _DELETE_KOLT, kolt->k_typ_id);
			break;
		case	_KOLLEKTIV	:
			kol=(KOLLEKTIV *)datastring;
			(void)sprintf(command, _DELETE_KOL, kol->k_id);
			break;





		case	_TRAEGER_TYP	:
			dltt=(TRAEGER_TYP *)datastring;
			(void)sprintf(command, _DELETE_DLTT, dltt->typ_id);
			break;
		case	_KATEGORIE	:
			kat=(KATEGORIE *)datastring;
			(void)sprintf(command, _DELETE_KAT, kat->kat_id);
			break;
		case	_DIENST_TRAEGER	:
			dlt=(DIENST_TRAEGER *)datastring;
			(void)sprintf(command, _DELETE_DLT, dlt->dlt_id);
			break;
		case	_ANGEBOTS_TYP	:
			dlat=(ANGEBOTS_TYP *)datastring;
			(void)sprintf(command, _DELETE_DLAT, dlat->art_id);
			break;
		case	_AKTIONS_TYP	:
			aktt=(AKTIONS_TYP *)datastring;
			(void)sprintf(command, _DELETE_AKTT, aktt->a_typ_id);
			break;
		case	_AKTIONSPARA:
			apara = (AKTIONSPARA *)datastring;
			(void)sprintf(command, _DELETE_AKTP, apara->a_typ_id, apara->nr);
			break;
		case	_AKTIONEN	:
			akt=(AKTIONEN *)datastring;
			(void)sprintf(command, _DELETE_AKT, akt->akt_id);
			break;
		case _AKTIONSGRP:
			agrp = (AKTIONSGRP *)datastring;
			(void)sprintf(command, _DELETE_AKTG, agrp->parentakt, agrp->childakt,
			                                     agrp->ord);
			break;
		case	_DIENST_ANGEBOT	:
			dla=(DIENST_ANGEBOT *)datastring;
			(void)sprintf(command, _DELETE_DLA, dla->dla_id);
			break;
		case	_DLG_PART	:
			dlg=(DLG_PART *)datastring;
			(void)sprintf(command, _DELETE_DLG, dlg->dl_id);
			break;
		case	_DIENSTLEISTUNG	:
			dtg=(DIENSTLEISTUNG *)datastring;
			(void)sprintf(command, _DELETE_DTG, dtg->dlg_id);
			break;
		case	_DLG_DLG	:
			dd=(DLG_DLG *)datastring;
			if (dd->dl_id == (int)_UNDEF && dd->ord == (short)_UNDEF)
				(void)sprintf(command, _DELETE_DD, dd->dlg_id);
			else
				(void)sprintf(command, _DELETE_ONE_DD, dd->dlg_id, dd->dl_id,
				                                       dd->ord);
			break;
		case	_PROGRAMM	:
			prg=(PROGRAMM *)datastring;
			(void)sprintf(command, _DELETE_PRG, prg->prg_id);
			break;
		case _ARRANGEMENT:
			arr=(ARRANGEMENT *)datastring;
			(void)sprintf(command, _DELETE_ARR, arr->arr_id);
			break;
		case _ARR_DLG:
			ad=(ARR_DLG *)datastring;
			if (ad->dlg_id > 0)
				(void)sprintf(command, _DELETE_ONE_AD, ad->arr_id, ad->dlg_id, ad->teil);
			else
				(void)sprintf(command, _DELETE_AD, ad->arr_id);
			break;




		case _HOST_KONT:
			hkon=(HOST_KONT *)datastring;
			(void)sprintf(command, _DELETE_HKON, hkon->hostkont_id);
			break;
		case	_KONTINGENT	:
			kon=(KONTINGENT *)datastring;
			(void)sprintf(command, _DELETE_KON, kon->kont_id);
			break;
		case _KONT_DETAIL:
			k_d=(KONT_DETAIL *)datastring;
			if (k_d->hostkont_id != (int)_UNDEF)
			   {
				if (k_d->dlt_id != (int)_UNDEF)
					(void)sprintf(command, _DELETE_KOND_HKONDLT, k_d->hostkont_id,
					              k_d->dlt_id);
				
				else if (k_d->kat_id != (int)_UNDEF)
					(void)sprintf(command, _DELETE_KOND_HKONKAT, k_d->hostkont_id,
					              k_d->kat_id);
				else
					(void)sprintf(command, _DELETE_KOND_HKON, k_d->hostkont_id);
			   }
			else
			   {
				if (k_d->dlt_id != (int)_UNDEF)
					(void)sprintf(command, _DELETE_KOND_KONDLT, k_d->kont_id,
					              k_d->dlt_id);
				
				else if (k_d->kat_id != (int)_UNDEF)
					(void)sprintf(command, _DELETE_KOND_KONKAT, k_d->kont_id,
					              k_d->kat_id);
				else
					(void)sprintf(command, _DELETE_KOND_KON, k_d->kont_id);
			   }
			break;





		case _BUCHUNG:
			bch=(BUCHUNG *)datastring;
			(void)sprintf(command, _DELETE_BCH, bch->bid);
			break;
		case _BCH_DLN:
			bdptr=(BCH_DLN *)datastring;
			if (bdptr->dln_id == (int)_UNDEF)
				(void)sprintf(command, _DELETE_BDBCH, bdptr->bid);
			else if (bdptr->bid == (int)_UNDEF)
				(void)sprintf(command, _DELETE_BDDLN, bdptr->dln_id);
			else
				(void)sprintf(command, _DELETE_BD, bdptr->bid, bdptr->dln_id);
			break;
		case	_AKT_DETAIL	:
			adptr=(AKT_DETAIL *)datastring;
			if (adptr->bid == (int)_UNDEF && adptr->teil == (int)_UNDEF &&
			    adptr->pers_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_AKTDET_DLN, adptr->pers_id);
			else if (adptr->bid != (int)_UNDEF && adptr->teil == (int)_UNDEF &&
			    adptr->pers_id == (int)_UNDEF)
				(void)sprintf(command, _DELETE_AKTDET_BCH, adptr->bid);
			else if (adptr->bid != (int)_UNDEF && adptr->teil == (int)_UNDEF &&
			    adptr->pers_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_AKTDET_BCH_DLN, adptr->bid, adptr->pers_id);
			else if (adptr->bid != (int)_UNDEF && adptr->teil != (int)_UNDEF &&
			    adptr->pers_id == (int)_UNDEF)
				(void)sprintf(command, _DELETE_AKTDET_BCH_TEIL, adptr->bid, adptr->teil);
			else
				(void)sprintf(command, _DELETE_AKTDET_BCH_DLN_TEIL, adptr->bid,
				              adptr->pers_id, adptr->teil);
			break;
		case	_KOSTEN_ART	:
			kar=(KOSTEN_ART *)datastring;
			(void)sprintf(command, _DELETE_KAR, kar->kar_id);
			break;
		case	_KOMMISSION	:
			kom=(KOMMISSION *)datastring;
			(void)sprintf(command, _DELETE_KOM, kom->komm_id);
			break;
		case	_KOMM_DETAIL:
			kd=(KOMM_DETAIL *)datastring;

			if (kd->komm_id != (int)_UNDEF && kd->bid != (int)_UNDEF && kd->dln_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOM_DLN_BCH, kd->komm_id, kd->dln_id, kd->bid);
			else if (kd->komm_id != (int)_UNDEF && kd->bid != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOM_BCH, kd->komm_id, kd->bid);
			else if (kd->komm_id != (int)_UNDEF && kd->dln_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOM_DLN, kd->komm_id, kd->dln_id);
			else if (kd->komm_id != (int)_UNDEF && kd->kun_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOM_KUN, kd->komm_id, kd->kun_id);
			else if (kd->komm_id != (int)_UNDEF && kd->kol_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOM_KOL, kd->komm_id, kd->kol_id);

			else if (kd->bid != (int)_UNDEF && kd->dln_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_DLN_BCH, kd->dln_id, kd->bid);
			else if (kd->bid != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_BCH, kd->bid);
			else if (kd->dln_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_DLN, kd->dln_id);
			else if (kd->kun_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KUN, kd->kun_id);
			else if (kd->kol_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD_KOL, kd->kol_id);
			else if (kd->komm_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KOMD, kd->komm_id);
			break;

		case	_RESERVATION	:
			res=(RESERVATION *)datastring;
			if (res->bid == (int)_UNDEF && res->teil == (int)_UNDEF &&
			    res->pers_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_RES_DLN, res->pers_id);
			else if (res->bid != (int)_UNDEF && res->teil == (int)_UNDEF &&
			    res->pers_id == (int)_UNDEF)
				(void)sprintf(command, _DELETE_RES_BCH, res->bid);
			else if (res->bid != (int)_UNDEF && res->teil == (int)_UNDEF &&
			    res->pers_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_RES_BCH_DLN, res->bid, res->pers_id);
			else if (res->bid != (int)_UNDEF && res->teil != (int)_UNDEF &&
			    res->pers_id == (int)_UNDEF)
				(void)sprintf(command, _DELETE_RES_BCH_TEIL, res->bid, res->teil);
			else
				(void)sprintf(command, _DELETE_RES_BCH_DLN_TEIL, res->bid,
				              res->pers_id, res->teil);
			break;
		case _PREIS:
			pre=(PREIS *)datastring;
			(void)sprintf(command, _DELETE_PRE, pre->pre_id);
			break;
		case _KAPA:
			kapa=(KAPA *)datastring;
			if (kapa->kat_id != (int)_UNDEF && kapa->tdl_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KAPA, kapa->kat_id, kapa->tdl_id);
			else if (kapa->tdl_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_KAPA_TDL, kapa->tdl_id);
			else
				(void)sprintf(command, _DELETE_KAPA_KAT, kapa->kat_id);
			break;
		case _MP_ARRKOM:
			arrkom=(MP_ARRKOM *)datastring;
			if (arrkom->arr_id != (int)_UNDEF && arrkom->komm_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_ARRKOM, arrkom->arr_id,
				              arrkom->komm_id);
			else if (arrkom->arr_id != (int)_UNDEF)
				(void)sprintf(command, _DELETE_ARRKOM_ARR, arrkom->arr_id);
			else
				(void)sprintf(command, _DELETE_ARRKOM_KOM, arrkom->komm_id);
			break;



		case	_GRAPHIK	:
			gra=(GRAPHIK *)datastring;
			(void)sprintf(command, _DELETE_GRA, gra->gra_id);
			break;
		case _GRAFORM:
			gra=(GRAPHIK *)datastring;
			(void)sprintf(command, _DELETE_GRAFORM, gra->gra_id);
			break;
		case	_REGIONS	:
			gra=(GRAPHIK *)datastring;
			(void)sprintf(command, _DELETE_REG, gra->dlt_id);
			break;
		case	_PCX_FILES	:
			pcx=(PCX_FILES *)datastring;
			(void)sprintf(command, _DELETE_PCX, pcx->pcx_id);
			break;

		/* unwahrscheinliches Abfangen */
		default:
			status = (int)MPE_WRONGOBJECT;
			break;
		}

	/* Delete entry command */
	if (status == (int)MPOK)
		status = MPAPIdb_sqlcommand(command, &anzahl);

	/* if anzahl is 0 then set error code */
	if (status == (int)MPOK && anzahl == 0)
		status = (int)MPE_NOINSUPDDEL;

	return(status);
}
