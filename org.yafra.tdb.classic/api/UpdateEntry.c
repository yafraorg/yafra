/**************************************************************/
/* Modul:     API - database update                           */
/*            update a table entry                            */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlupd.h>
#include <mpsqlins.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UpdateEntry.c,v 1.3 2008-11-02 19:55:48 mwn Exp $";

int MPAPIupdateEntry (int table , char *datastring , BEZEICHNUNG *bez)
{
	extern char userid[];  /* needed for making references REF */
	extern int DebugFlag;
	extern PREIS pre_old;

	AKTIONEN *akt;
	AKTIONS_TYP *aktt;
	AKTIONSPARA *apara;
	AKT_DETAIL *akt_det;
	ARRANGEMENT *arr;
	BUCHUNG *bch;
	DIENST_ANGEBOT *dla;
	ANGEBOTS_TYP *dlat;
	DLG_PART *dlg;
	DIENSTLEISTUNG *dtg;
	DLG_DLG *dd;
	DIENST_TRAEGER *dlt;
	TRAEGER_TYP *dltt;
	GRAPHIK *gra;
	KAPA *kapa;
	KATEGORIE *kat;
	KOLLEKTIV *kol;
	KOLLEKTIV_TYP *kolt;
	HOST_KONT *hkon;
	KONTINGENT *kon;
	KONT_DETAIL *kond;
	KUNDEN *kun;
	KUNDEN_TYP *kunt;
	PERSADR *Padr;
	PCX_FILES *pcx;
	PREIS *pre;
	PROGRAMM *prg;
	REISENDER *rei;
	REISENDER_TYP *reit;
	KOSTEN_ART *kar;
	SAISON *sai;
	STATUS_WERTE *sta;
	KOMMISSION *kom_ptr;
	SPRACHEN *spr;
	LAND *land;
	ORT *ort;
	WAEHRUNG *whr;
	LAND_SPR *ls;
	LAND_WHR *lw;
	BEZEICHNUNG *bez_ptr;
	TEXTE *txt;
	MP_MSG *msg;
	PERSONEN *pers;

	char message[_RECORDLEN];
	char command[_QUERYLEN];
	char ref[_CHAR30 + 1];
	int status=(int)MPOK;
	int bez_id = (int)0;
	int anzahl;

	/* replace BEZEICHNUNG in db 	*/
	switch(table)
		{
		case (int)_KOLLEKTIV:
		case (int)_ARRANGEMENT:
		case (int)_DIENSTLEISTUNG:
		case (int)_BEZEICHNUNG:
			break;
		default:
			if (bez != (BEZEICHNUNG *)NULL)
				{
				bez_id = InsertBEZ(bez);
				if (bez_id == (int)_UNDEF)
					return((int)MPE_NOBEZINSERT);
				status = DeleteBEZ(table, datastring, bez_id);
				if (status != (int)MPOK)
					return(status);
				}
			break;
		}


	switch(table)
		{
		case _SPRACHEN:
			spr = (SPRACHEN *)datastring;
			spr->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_SPR, spr->bez_id, spr->dialog,
			              spr->sysbez, spr->output, spr->gui, spr->s_id);
			break;
		case	_STATUS_WERTE	:
			sta=(STATUS_WERTE *)datastring;
			sta->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_STA, sta->bez_id, sta->abk,
			              sta->sta, sta->kond, sta->sta_id, sta->typ);
			break;
		case _TEXTE	:
			txt=(TEXTE *)datastring;
			(void)sprintf(command, _INSERT_TXT, txt->textid, txt->s_id, txt->textnr,
							  txt->text, txt->typ);
			break;
		case _BEZEICHNUNG:
			bez_ptr=(BEZEICHNUNG *)datastring;
			(void)sprintf(command, _UPDATE_BEZ, bez_ptr->bez, bez_ptr->bez_id, bez_ptr->s_id, bez_ptr->typ);
			break;
		case _MSG:
			msg = (MP_MSG *)datastring;
			(void)sprintf(command, _UPDATE_MSG, msg->msg_typ, msg->text,
			              msg->msg_id, msg->textnr, msg->s_id);
			break;
		case	_SAISON	:
			sai=(SAISON *)datastring;
			sai->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_SAI, sai->code, sai->bez_id, sai->von,
							  sai->bis, sai->textid, sai->sai_id);
			break;



		case _WAEHRUNG:
			whr = (WAEHRUNG *)datastring;
			whr->bez_id = bez_id;
			(void)sprintf(command, _UPDATE_WHR, whr->bez_id, whr->textid,
			               whr->status, whr->krzl, whr->whr_id);
			break;
		case _LAND:
			land = (LAND *)datastring;
			land->bez_id = bez_id;
			(void)sprintf(command, _UPDATE_LAND, land->bez_id, land->textid,
			               land->krzl, land->haupt_ort, land->haupt_whr,
			               land->haupt_spr, land->vat, land->dateformat,
			               land->land_id);
			break;
		case _ORT:
			ort = (ORT *)datastring;
			ort->bez_id = bez_id;
			(void)sprintf(command, _UPDATE_ORT, ort->bez_id, ort->land_id,
			               ort->textid, ort->krzl, ort->zeitver, ort->koord1,
			               ort->koord2, ort->ort_typ, ort->ort_id);
			break;
		case _LAND_WHR:
			lw = (LAND_WHR *)datastring;
			(void)sprintf(command, _UPDATE_LW, lw->a_kurs, lw->v_kurs, lw->von_dat,
			                       lw->land_id, lw->whr_id, lw->kurs_typ);
			break;



		case _PERSONEN:
			pers=(PERSONEN *)datastring;
			(void)sprintf(command, _UPDATE_PERS, pers->name, pers->s_id,
							  pers->sta_id, pers->textid, pers->pers_id);
			break;
		case _PERSADR:
			Padr=(PERSADR *)datastring;
			(void)sprintf(command, _UPDATE_PERSADR, Padr->ans, Padr->adr1, Padr->adr2,
			              Padr->adr3, Padr->ort, Padr->plz, Padr->sta_id, Padr->adr_typ,
                       Padr->kant, Padr->land_id, Padr->haupt_flag, Padr->rch_flag,
                       Padr->mail_flag, Padr->tel, Padr->handy, Padr->fax,
                       Padr->email, Padr->web, Padr->pers_id);
			break;
		case	_REISENDER	:
			rei=(REISENDER *)datastring;
			(void)sprintf(command, _UPDATE_REI, rei->vor, rei->rkr_id,
							  rei->sex, rei->mutters_id, rei->age,
			              rei->passnr, rei->attr1, rei->attr2, rei->pers_id);
			break;
		case	_REISENDER_TYP	:
			reit=(REISENDER_TYP *)datastring;
			reit->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_REIT, reit->bez_id, reit->textid,
			              reit->dlncode, reit->vonalter, reit->bisalter,
			              reit->rkr_id);
			break;
		case	_KUNDEN	:
			kun=(KUNDEN *)datastring;
			(void)sprintf(command, _UPDATE_KUN, kun->handy, kun->tel, kun->fax,
							  kun->tlx, kun->konto, kun->leiter, kun->attr1,
							  kun->attr2, kun->email, kun->web, kun->k_typ_id,
			              kun->whr_id, kun->pers_id);
			break;
		case	_KUNDEN_TYP	:
			kunt=(KUNDEN_TYP *)datastring;
			kunt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_KUNT, kunt->bez_id, kunt->textid,
							  kunt->kuncode, kunt->k_typ_id);
			break;
		case _KOLLEKTIV:
			kol=(KOLLEKTIV *)datastring;
			(void)sprintf(command, _UPDATE_KOL, kol->name, kol->ref,
			              kol->hauptpers, kol->k_sta,
							  kol->k_typ_id, kol->textid, kol->kid,
							  kol->kbst, kol->k_id);
			break;
		case	_KOLLEKTIV_TYP	:
			kolt=(KOLLEKTIV_TYP *)datastring;
			kolt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_KOLT, kolt->bez_id, kolt->textid,
							  kolt->kolcode, kolt->k_typ_id);
			break;



		case	_TRAEGER_TYP	:
			dltt=(TRAEGER_TYP *)datastring;
			dltt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_DLTT, dltt->bez_id, dltt->h_typ_id,
							  dltt->host_typ, dltt->textid, dltt->typ_id);
			break;
		case	_KATEGORIE	:
			kat=(KATEGORIE *)datastring;
			kat->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_KAT, kat->bez_id, kat->h_kat_id, kat->typ_id,
							  kat->ga, kat->textid, kat->kat_id);
			break;
		case	_DIENST_TRAEGER	:
			dlt=(DIENST_TRAEGER *)datastring;
			dlt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_DLT, dlt->code, dlt->bez_id, dlt->kat_id, dlt->h_dlt_id,
							  dlt->host_id, dlt->typ_id, dlt->textid, dlt->stufe,
							  dlt->sta_id, dlt->anz, dlt->dlt_id, dlt->h_dlt_id);
			break;
		case	_ANGEBOTS_TYP	:
			dlat=(ANGEBOTS_TYP *)datastring;
			dlat->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_DLAT, dlat->bez_id, dlat->textid, dlat->art_id);
			break;
		case	_AKTIONS_TYP	:
			aktt=(AKTIONS_TYP *)datastring;
			aktt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_AKTT, aktt->bez_id, aktt->proz, aktt->textid,
							  aktt->a_typ_id);
			break;
		case	_AKTIONSPARA:
			apara=(AKTIONSPARA *)datastring;
			(void)sprintf(command, _UPDATE_AKTP, apara->typ, apara->bez,
			       apara->textid, apara->muss, apara->flag, apara->a_typ_id, apara->nr);
			break;
		case _AKTIONEN:
			akt=(AKTIONEN *)datastring;
			akt->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_AKT, akt->bez_id, akt->textid,
							  akt->a_flag, akt->b_flag, akt->m_flag, akt->a_typ_id,
							  akt->b2_flag, akt->file_id, akt->akt_id);
			break;
		case	_DIENST_ANGEBOT	:
			dla=(DIENST_ANGEBOT *)datastring;
			dla->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_DLA, dla->h_dla_id, dla->ord, dla->dlt_id,
							  dla->code, dla->bez_id, dla->akt_id, dla->ort, dla->art_id,
							  dla->dau, dla->textid, dla->von, dla->nach, dla->dla_id);
			break;
		case	_DLG_PART	:
			dlg=(DLG_PART *)datastring;
			dlg->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_DLG, dlg->h_dl_id, dlg->dla_id, dlg->code,
							  dlg->bez_id, dlg->ord, dlg->a_zeit, dlg->e_zeit,
							  dlg->res_f, dlg->kid, dlg->konto, dlg->textid,
							  dlg->sai_id, dlg->rechst, dlg->dl_id);
			if (DebugFlag)
				{
				(void)sprintf(message, "Update DLG_PART mit ID: %d", dlg->dl_id);
				MPdebug(_LOGMP, message, __FILE__);
				}
			break;
		case	_DIENSTLEISTUNG	:
			dtg=(DIENSTLEISTUNG *)datastring;
			(void)sprintf(command, _UPDATE_DTG, dtg->code, dtg->bez_id, dtg->textid,
							  dtg->sai_id, dtg->a_zeit, dtg->akt_id, dtg->dlg_id);
			if (DebugFlag)
				{
				(void)sprintf(message, "Update DIENSTLEISTUNG mit ID: %d", dtg->dlg_id);
				MPdebug(_LOGMP, message, __FILE__);
				}
			break;
		case	_DLG_DLG	:
			dd=(DLG_DLG *)datastring;
			(void)sprintf(command, _UPDATE_DLGDLG, dd->ord, dd->dlg_id, dd->dl_id);
			break;
		case	_PROGRAMM	:
			prg=(PROGRAMM *)datastring;
			prg->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_PRG, prg->code, prg->bez_id, prg->textid, prg->sai_id,
							  prg->prg_id);
			break;
		case _ARRANGEMENT:
			arr=(ARRANGEMENT *)datastring;
			(void)sprintf(command, _UPDATE_ARR, arr->code, arr->bez_id, arr->a_dat, arr->prg_id,
							  arr->textid, arr->sai_id, arr->arr_id);
			break;

		case _HOST_KONT:
			hkon=(HOST_KONT *)datastring;
			hkon->bez_id=bez_id;
			if (*hkon->ref == NULL)   /* create reference */
				{
				sprintf(ref, "HK%04d*%s", hkon->hostkont_id, userid);
				(void)strcpy(hkon->ref, ref);
				}

			(void)sprintf(command, _UPDATE_HKON, hkon->bez_id,
							  hkon->from_pers, hkon->kbst, hkon->dla_id, hkon->dl_id,
			              hkon->dl_vondat, hkon->dl_bisdat, hkon->textid,
							  hkon->opt_dat, hkon->sai_id, hkon->ref, hkon->history,
							  hkon->hostkont_id);
			break;

		case	_KONTINGENT	:
			kon=(KONTINGENT *)datastring;
			kon->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_KON, kon->bez_id, kon->hostkont_id,
			              kon->kunden_id, kon->textid, kon->opt_dat,
							  kon->sai_id, kon->ref, kon->kont_id);
			break;
		case _KONT_DETAIL:
			kond=(KONT_DETAIL *)datastring;
			if (kond->busy != (int)_UNDEF)
				{
				(void)sprintf(command, _UPDATE_KOND_BUSY, kond->busy,
				              kond->hostkont_id, kond->kont_id, kond->kat_id);
				}
			else
				{
				(void)sprintf(command, _UPDATE_KOND_ANZ, kond->anz, kond->minanz,
				              kond->hostkont_id, kond->kont_id, kond->kat_id);
				}
			break;




		case	_BUCHUNG:
			bch=(BUCHUNG *)datastring;
			(void)sprintf(command, _UPDATE_BCH, bch->d_bid, bch->ref, bch->arr_id,
							  bch->kid, bch->sach, bch->mpid, bch->anw, bch->b_dat, bch->m_dat,
							  bch->opt_bst, bch->opt_kid, bch->sta, bch->ast,
							  bch->sai_id, bch->k_id ,bch->history, bch->b_text,
                       bch->bid);
			if (DebugFlag)
				{
				(void)sprintf(message, "Update BUCHUNG mit ID: %d", bch->bid);
				MPdebug(_LOGMP, message, __FILE__);
				}
			break;
		case	_AKT_DETAIL	:
			akt_det=(AKT_DETAIL *)datastring;
			(void)sprintf(command, _UPDATE_AKT_DET, akt_det->z_flag, akt_det->akt_nr,
			              akt_det->exec_dat, akt_det->file_id, akt_det->bid, akt_det->pers_id,
			              akt_det->teil, akt_det->akt_id, akt_det->ord);
			break;
		case	_KOSTEN_ART	:
			kar=(KOSTEN_ART *)datastring;
			kar->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_KAR, kar->bez_id, kar->textid, kar->kar_id);
			break;
		case	_KOMMISSION	:
			kom_ptr=(KOMMISSION *)datastring;
			(void)sprintf(command, _UPDATE_KOM, kom_ptr->bez_id, kom_ptr->satz_art,
			              kom_ptr->satz, kom_ptr->komm_typ, kom_ptr->kar_id, kom_ptr->dltt_id,
							  kom_ptr->kat_id, kom_ptr->rkr_id, kom_ptr->dla_id,
							  kom_ptr->dl_id, kom_ptr->dl_vondat, kom_ptr->dl_bisdat,
							  kom_ptr->kont_id, kom_ptr->bid, kom_ptr->sai_id,
							  kom_ptr->history, kom_ptr->textid, kom_ptr->komm_id);
			break;
		case	_PREIS	:
			pre=(PREIS *)datastring;
			(void)sprintf(command, _UPDATE_PRE, pre->apr, pre->vpr, pre->epr,
				pre->glt, pre->whr_id, pre->kbst, pre->kar_id, pre->dltt_id, pre->kat_id,
				pre->rkr_id, pre->dla_id, pre->dl_id, pre->dl_vondat,
				pre->dl_bisdat, pre->kont_id, pre->sta_id, pre->textid,
				pre->history, pre->sai_id, pre->arr_id, pre->ext_id, pre->unit_typ, pre->unit_von,
	         pre->unit_bis, pre->dau, pre->dau_von, pre->dau_bis, pre->pre_id);
			break;
		case _KAPA:
			kapa = (KAPA *)datastring;
			if (kapa->busy != (int)_UNDEF)
				{
				(void)sprintf(command, _UPDATE_KAPA_BUSY, kapa->busy,
				              kapa->kat_id, kapa->tdl_id);
				}
			else
				{
				(void)sprintf(command, _UPDATE_KOND_ANZ, kapa->anz,
				              kapa->kat_id, kapa->tdl_id);
				}
			break;



		case	_GRAPHIK	:
			gra=(GRAPHIK *)datastring;
			(void)sprintf(command, _UPDATE_GRA, gra->bez_id, gra->textid, gra->dlt_id,
			               gra->gra_id);
			break;
		case	_PCX_FILES	:
			pcx=(PCX_FILES *)datastring;
			pcx->bez_id=bez_id;
			(void)sprintf(command, _UPDATE_PCX, pcx->x, pcx->y, pcx->filename, pcx->bez_id,
							  pcx->typ, pcx->typcode, pcx->folge, pcx->pcx_id);
			break;


		/* wrong object or not yet implemented */
		default:
			status = (int)MPE_WRONGOBJECT;
			break;
		}

	/* Update entry command */
	if (status == (int)MPOK)
		status = MPAPIdb_sqlcommand(command, &anzahl);

	/* if anzahl is 0 then set error code */
	if (status == (int)MPOK && anzahl == 0)
		status = (int)MPE_NOINSUPDDEL;

	return(status);
}
