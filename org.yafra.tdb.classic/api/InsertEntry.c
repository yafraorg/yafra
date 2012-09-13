/*D***********************************************************
 * modul:     API - database insert one entry
 *
 * paras:     int table         to select from
 *            char *datastring  data pointer of entry to insert
 *            BEZEICHNUNG *bez  bez of entry
 *
 * return:    _UNDEF  if error or the number of the entry
 *
 * copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlins.h>
#include <mpproapi.h>		/* Prototypes f?r ANSI-C */

#define	_SEL_ONE_BEZ	"SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID=%d AND TYP= %d;"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/InsertEntry.c,v 1.5 2009-01-02 16:51:35 mwn Exp $";

int MPAPIinsertEntry(int table, char *datastring, BEZEICHNUNG *bez)
{
	extern char userid[];  /* needed for making references REF */

	AKTIONEN *akt;
	AKTIONS_TYP *aktt;
	AKTIONSPARA *para;
	AKTIONSGRP *aktgrp;
	AKT_DETAIL *aktdet;
	ANGEBOTS_TYP *dlat;
	ARRANGEMENT *arr;
	ARR_DLG *ad;
	BUCHUNG *bch;
	BCH_DLN *bdptr;
	DIENST_ANGEBOT *dla;
	DLG_PART *dlg;
	DIENSTLEISTUNG *dtg;
	DLG_DLG *dd;
	DIENST_TRAEGER *dlt;
	GRAPHIK *gra;
	GRAFORM *graform;
	REGIONS *reg;
	KATEGORIE *kat;
	KOLLEKTIV *kol;
	KOLLEKTIV_TYP *kolt;
	KONTINGENT *kon;
	KONT_DETAIL *k_d_ptr;
	KUNDEN *kun;
	KUNDEN_TYP *kunt;
	MAXIMA *maxima;
	PCX_FILES *pcx;
	PREIS *pre;
	PROGRAMM *prg;
	REISENDER *rei;
	REISENDER_TYP *reit;
	TRAEGER_TYP *dltt;
	KOSTEN_ART *kar;
	RESERVATION *res;
	SAISON *sai;
	SPRACHEN *spr;
	STATUS_WERTE *sta;
	TEXTE *txt;
	BEZEICHNUNG *bez_ptr;
	KOMMISSION *kom_ptr;
	KOMM_DETAIL *kd_ptr;
	LAND *landptr;
	ORT *ortptr;
	WAEHRUNG *whrptr;
	LAND_WHR *lwptr;
	LAND_SPR *lsptr;
	MP_MSG *msg;
	HISTORY *hisptr;
	HELP *hlp;
	LABEL *lab;
	PERSONEN *pers;
	PERSADR *persadr;
	HOST_KONT *hkon;
	KAPA *kapa;
	MP_ARRKOM *arrkom;


	BEZEICHNUNG tmpbez;

	char command[_QUERYLEN];
	char ref[_CHAR30 + 1];
	char datum[_DATELEN];
	char zeit[_DATELEN];
	int status=(int)MPOK;
	int bez_id = (int)_UNDEF;
	int table_id = 0;
	int anzahl = 0;
	int addon_id = 0;
	int ret = 0;

	*command = NULL;

	/* set isolation level to highest to get the right new ID */
	status = MPAPIdb_settrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);

	/* hole neue unique table ID */
	switch(table)
		{
		case (int)_PERSADR:
		case (int)_KUNDEN:
		case (int)_REISENDER:
		case (int)_KONT_DETAIL:
		case (int)_KOMM_DETAIL:
		case (int)_REGIONS:
		case (int)_AKT_DETAIL:
		case (int)_ARR_DLG:
		case (int)_RESERVATION:
		case (int)_AKTIONSPARA:   /* es gibt auch Tables ohne unique ID */
		case (int)_AKTIONSGRP:
		case (int)_MP_ARRKOM:
		case (int)_KAPA:
		case (int)_BCH_DLN:
		case (int)_GRAFORM:
		case (int)_DLG_DLG:
		case (int)_MAXIMA:
		case (int)_LAND_WHR:
		case (int)_LAND_SPR:
		case (int)_MSG:
			break;
		default:
			table_id = MPAPIid_new(table, (int)0, (int)0);
		}

	/* hole neue Bezeichnungs ID */
	switch(table)
		{
		case (int)_MAXIMA:
		case (int)_TEXTE:
		case (int)_PERSONEN:
		case (int)_REISENDER:
		case (int)_KUNDEN:
		case (int)_PERSADR:
		case (int)_KOLLEKTIV:
		case (int)_KONT_DETAIL:
		case (int)_AKTIONSTEXTE:
		case (int)_BUCHUNG:
		case (int)_BEZEICHNUNG:
		case (int)_MP_ARRKOM:
		case (int)_KAPA:
		case (int)_DLG_DLG:
		case (int)_ARR_DLG:
		case (int)_AKT_DETAIL:   /* tables without bez_id !! */
		case (int)_PREIS:
		case (int)_RESERVATION:
		case (int)_BCH_DLN:
		case (int)_KOMM_DETAIL:
		case (int)_REGIONS:
		case (int)_GRAFORM:
		case (int)_AKTIONSPARA:
		case (int)_AKTIONSGRP:
		case (int)_LAND_WHR:
		case (int)_LAND_SPR:
		case (int)_LABEL:
		case (int)_HISTORY:
		case (int)_HELP:
		case (int)_MSG:
			break;
		default:
			if (bez != (BEZEICHNUNG *)NULL)
				{
				/* check if there is already a same BEZEICHNUNG */
				/* take care about the special cases where BEZ is identified by another key (like date) */
				addon_id = 0;
				switch(table)
					{
					case _ARRANGEMENT:
						arr=(ARRANGEMENT *)datastring;
						arr->arr_id=table_id;
						if (arr->a_dat != _MP_NODATE && arr->a_dat != _UNDEF)
							addon_id = 1;
						break;
					case _DLG_PART:
						dlg=(DLG_PART *)datastring;
						if (dlg->a_zeit != _MP_NODATE && dlg->a_zeit != _UNDEF &&
						    dlg->e_zeit != _MP_NODATE && dlg->e_zeit != _UNDEF)
							addon_id = 1;
						break;
					case _DIENSTLEISTUNG:
						dtg=(DIENSTLEISTUNG *)datastring;
						if (dtg->a_zeit != _MP_NODATE && dtg->a_zeit != _UNDEF)
							addon_id = 1;
						break;
					}
				(void)memcpy((void *)&tmpbez, (void *)bez, sizeof(BEZEICHNUNG));
				ret = MPAPIselectEntry((int)_BEZEICHNUNG, tmpbez.bez,
				   (char *)&tmpbez, sizeof(BEZEICHNUNG), sizeof(tmpbez.bez_id));
				if (ret != _UNDEF && addon_id == 0)
					{
					return((int)MPE_NOBEZINSERT); /* error for already same bez */
					}
				else if (ret != _UNDEF && addon_id == 1)
					{
					bez_id = tmpbez.bez_id; /* reuse the bez_id */
					}
				else
					{
					/* insert the unique bezeichung */
					bez_id = InsertBEZ(bez);
					if (bez_id == (int)_UNDEF)
						return((int)MPE_NOBEZINSERT);
					}
				}
			else
				return((int)MPE_NOBEZINSERT);
		}

	/* setze INSERT String */
	if (table_id == (int)_UNDEF)
		return((int)MPE_NONEWIDINSERT);

	switch(table)
		{
		case _MAXIMA:
			maxima = (MAXIMA *)datastring;
			(void)sprintf(command, _INSERT_MAX, maxima->tabelle, maxima->typ,
			              maxima->max_id, maxima->min_id, maxima->incr);
			break;
		case _SPRACHEN:
			spr=(SPRACHEN *)datastring;
			spr->s_id=table_id;
			spr->bez_id=bez_id;
			(void)sprintf(command, _INSERT_SPR, table_id, bez_id, spr->dialog,
			                                    spr->sysbez, spr->output, spr->gui);
			break;
		case	_STATUS_WERTE	:
			sta=(STATUS_WERTE *)datastring;
			sta->sta_id=table_id;
			sta->bez_id=bez_id;
			(void)sprintf(command, _INSERT_STA, sta->sta_id, sta->abk, sta->sta,
							  sta->bez_id, sta->kond, sta->typ);
			break;
		case _BEZEICHNUNG:
			bez_ptr=(BEZEICHNUNG *)datastring;
			(void)sprintf(command, _INSERT_BEZ, bez_ptr->bez_id, bez_ptr->s_id,
							  bez_ptr->bez, bez_ptr->typ);
			break;
		case _TEXTE:
			txt=(TEXTE *)datastring;
			(void)sprintf(command, _INSERT_TXT, txt->textid, txt->s_id, txt->textnr,
							  txt->text, txt->typ);
			break;
		case _HISTORY:
			hisptr=(HISTORY *)datastring;
			(void)sprintf(command, _INSERT_HIS, hisptr->his_id, hisptr->s_id,
			           hisptr->textnr, hisptr->text, hisptr->date, hisptr->typ);
			break;
		case _HELP:
			hlp=(HELP *)datastring;
			(void)sprintf(command, _INSERT_HLP, hlp->help_typ, hlp->help_id,
			              hlp->s_id, hlp->textnr, hlp->text);
			break;
		case _MSG:
			msg = (MP_MSG *)datastring;
			(void)sprintf(command, _INSERT_MSG, msg->msg_typ, msg->msg_id,
			              msg->s_id, msg->textnr, msg->text);
			break;
		case _LABEL:
			lab=(LABEL *)datastring;
			(void)sprintf(command, _INSERT_LAB, lab->label_prg, lab->label_typ,
			              lab->stufe1, lab->stufe2, lab->s_id, lab->label);
			break;
		case _SAISON:
			sai=(SAISON *)datastring;
			sai->sai_id=table_id;
			sai->bez_id=bez_id;
			(void)sprintf(command, _INSERT_SAI, table_id, sai->code, bez_id, sai->von,
							  sai->bis, sai->textid);
			break;


		case _WAEHRUNG:
			whrptr=(WAEHRUNG *)datastring;
			whrptr->whr_id=table_id;
			whrptr->bez_id=bez_id;
			(void)sprintf(command, _INSERT_WHR, table_id, bez_id, whrptr->textid,
							  whrptr->status, whrptr->krzl);
			break;
		case _LAND:
			landptr=(LAND *)datastring;
			landptr->land_id=table_id;
			landptr->bez_id=bez_id;
			(void)sprintf(command, _INSERT_LAND, table_id, bez_id, landptr->textid,
							  landptr->krzl, landptr->haupt_ort, landptr->haupt_whr,
							  landptr->haupt_spr, landptr->vat, landptr->dateformat);
			break;
		case _ORT:
			ortptr=(ORT *)datastring;
			ortptr->ort_id=table_id;
			ortptr->bez_id=bez_id;
			(void)sprintf(command, _INSERT_ORT, table_id, bez_id, ortptr->land_id,
							  ortptr->textid, ortptr->krzl, ortptr->zeitver,
							  ortptr->koord1, ortptr->koord2, ortptr->ort_typ);
			break;
		case _LAND_WHR:
			lwptr=(LAND_WHR *)datastring;
			(void)sprintf(command, _INSERT_LW, lwptr->land_id, lwptr->whr_id,
							  lwptr->kurs_typ, lwptr->a_kurs, lwptr->v_kurs, lwptr->von_dat);
			break;
		case _LAND_SPR:
			lsptr=(LAND_SPR *)datastring;
			(void)sprintf(command, _INSERT_LS, lsptr->land_id, lsptr->s_id);
			break;


		case _PERSONEN:
			pers=(PERSONEN *)datastring;
			pers->pers_id = table_id;
			(void)sprintf(command, _INSERT_PERS, pers->pers_id, pers->pers_typ,
			      pers->name, pers->s_id, pers->sta_id, pers->textid);
			break;
		case _PERSADR:
			persadr=(PERSADR *)datastring;
			(void)sprintf(command, _INSERT_PERSADR, persadr->pers_id, persadr->adr_typ,
			      persadr->ans, persadr->adr1, persadr->adr2, persadr->adr3,
			      persadr->plz, persadr->ort, persadr->kant, persadr->land_id, persadr->sta_id,
	            persadr->haupt_flag, persadr->rch_flag, persadr->mail_flag, persadr->tel,
	            persadr->handy, persadr->fax, persadr->handy, persadr->email, persadr->web);
			break;
		case _REISENDER:
			rei=(REISENDER *)datastring;
			(void)sprintf(command, _INSERT_REI, rei->pers_id, rei->vor,
							  rei->rkr_id, rei->sex, rei->mutters_id,
							  rei->age, rei->passnr, rei->attr1, rei->attr2, rei->textid);
			break;
		case	_REISENDER_TYP	:
			reit=(REISENDER_TYP *)datastring;
			reit->rkr_id=table_id;
			reit->bez_id=bez_id;
			(void)sprintf(command, _INSERT_REIT, table_id, bez_id, reit->textid,
			              reit->dlncode, reit->vonalter, reit->bisalter);
			break;
		case _KUNDEN:
			kun=(KUNDEN *)datastring;
			(void)sprintf(command, _INSERT_KUN, kun->pers_id,
							  kun->tel, kun->handy, kun->fax, kun->tlx, kun->email, kun->web,
							  kun->konto, kun->leiter, kun->attr1, kun->attr2,
							  kun->k_typ_id, kun->whr_id);
			break;
		case _KUNDEN_TYP:
			kunt=(KUNDEN_TYP *)datastring;
			kunt->k_typ_id=table_id;
			kunt->bez_id=bez_id;
			(void)sprintf(command, _INSERT_KUNT, table_id, bez_id, kunt->textid,
			              kunt->kuncode);
			break;
		case _KOLLEKTIV:
			kol=(KOLLEKTIV *)datastring;
			kol->k_id=table_id;
			if (*kol->ref == NULL)   /* create reference */
				{
				(void)sprintf(ref, "G%04d*%s", table_id, userid);
				(void)strcpy(kol->ref, ref);
				}
			(void)sprintf(command, _INSERT_KOL, table_id, kol->name, kol->k_typ_id,
			              kol->kbst, kol->ref, kol->k_sta, kol->hauptpers,
							  kol->kid, kol->textid);
			break;
		case _KOLLEKTIV_TYP:
			kolt=(KOLLEKTIV_TYP *)datastring;
			kolt->k_typ_id=table_id;
			kolt->bez_id=bez_id;
			(void)sprintf(command, _INSERT_KOLT, table_id, bez_id, kolt->kolcode,
			              kolt->textid);
			break;


		case _TRAEGER_TYP:
			dltt=(TRAEGER_TYP *)datastring;
			dltt->typ_id=table_id;
			dltt->bez_id=bez_id;
			if (dltt->host_typ == (short)UNDEF)
				dltt->host_typ = table_id;
			(void)sprintf(command, _INSERT_DLTT, table_id, bez_id, dltt->h_typ_id,
							  dltt->host_typ, dltt->textid);
			break;
		case _KATEGORIE:
			kat=(KATEGORIE *)datastring;
			kat->kat_id=table_id;
			kat->bez_id=bez_id;
			(void)sprintf(command, _INSERT_KAT, table_id, bez_id, kat->h_kat_id,
							  kat->typ_id, kat->ga, kat->textid);
			break;
		case _DIENST_TRAEGER:
			dlt=(DIENST_TRAEGER *)datastring;
			dlt->dlt_id=table_id;
			dlt->bez_id=bez_id;
			if(dlt->host_id == (int)UNDEF)
				dlt->host_id = table_id;
			(void)sprintf(command, _INSERT_DLT, table_id, dlt->code, bez_id, dlt->kat_id,
							  dlt->h_dlt_id, dlt->dlt_grp_id, dlt->host_id, dlt->typ_id,
							  dlt->textid, dlt->stufe, dlt->sta_id, dlt->anz);
			break;
		case _ANGEBOTS_TYP:
			dlat=(ANGEBOTS_TYP *)datastring;
			dlat->art_id=table_id;
			dlat->bez_id=bez_id;
			(void)sprintf(command, _INSERT_DLAT, table_id, bez_id, dlat->textid);
			break;
		case _AKTIONS_TYP:
			aktt=(AKTIONS_TYP *)datastring;
			aktt->a_typ_id=table_id;
			aktt->bez_id=bez_id;
			(void)sprintf(command, _INSERT_AKTT, aktt->a_typ_id, bez_id,
							  aktt->proz, aktt->textid);
			break;
		case _AKTIONSPARA:
			para=(AKTIONSPARA *)datastring;
			(void)sprintf(command, _INSERT_AKTP, para->a_typ_id, para->nr,
							  para->typ, para->bez, para->textid, para->muss, para->flag);
			break;
		case	_AKTIONEN	:
			akt=(AKTIONEN *)datastring;
			if(akt->akt_id == (int)UNDEF) akt->akt_id=table_id;
			akt->bez_id=bez_id;
			(void)sprintf(command, _INSERT_AKT, akt->akt_id, bez_id,
							  akt->textid, akt->a_flag, akt->b_flag, akt->m_flag,
			              akt->a_typ_id, akt->b2_flag, akt->file_id);
			break;
		case _AKTIONSGRP:
			aktgrp=(AKTIONSGRP *)datastring;
			(void)sprintf(command, _INSERT_AKTG, aktgrp->parentakt,
							  aktgrp->childakt, aktgrp->ord, aktgrp->h_akt_id);
			break;
		case	_DIENST_ANGEBOT	:
			dla=(DIENST_ANGEBOT *)datastring;
			if(dla->dla_id == (int)UNDEF) dla->dla_id=table_id;
			dla->bez_id=bez_id;
			(void)sprintf(command, _INSERT_DLA, dla->dla_id, dla->h_dla_id,
							  dla->ord, dla->dlt_id, dla->code, bez_id, dla->akt_id,
							  dla->ort, dla->art_id, dla->dau, dla->textid,
							  dla->von, dla->nach);
			break;
		case	_DLG_PART	:
			dlg=(DLG_PART *)datastring;
			if (dlg->dl_id == (int)UNDEF)
				dlg->dl_id=table_id;
			dlg->bez_id=bez_id;
			(void)sprintf(command, _INSERT_DLG, dlg->dl_id, dlg->h_dl_id,
							  dlg->dla_id, dlg->code, bez_id, dlg->ord,
							  dlg->a_zeit, dlg->e_zeit, dlg->res_f, dlg->kid,
							  dlg->konto, dlg->textid, dlg->sai_id, dlg->rechst);
			break;
		case	_DIENSTLEISTUNG	:
			dtg=(DIENSTLEISTUNG *)datastring;
			if (dtg->dlg_id == (int)UNDEF)
				dtg->dlg_id=table_id;
			dtg->bez_id=bez_id;
			(void)sprintf(command, _INSERT_DTG, dtg->dlg_id, dtg->code, dtg->bez_id,
							  dtg->textid, dtg->sai_id, dtg->a_zeit,
							  dtg->akt_id);
			break;
		case	_DLG_DLG	:
			dd=(DLG_DLG *)datastring;
			(void)sprintf(command, _INSERT_DD, dd->dlg_id, dd->dl_id, dd->ord);
			break;
		case	_PROGRAMM	:
			prg=(PROGRAMM *)datastring;
			prg->prg_id=table_id;
			prg->bez_id=bez_id;
			(void)sprintf(command, _INSERT_PRG, table_id, prg->code, bez_id, prg->textid,
							  prg->sai_id);
			break;
		case _ARRANGEMENT:
			arr=(ARRANGEMENT *)datastring;
			arr->arr_id=table_id;
			arr->bez_id=bez_id;
			(void)sprintf(command, _INSERT_ARR, table_id, arr->code, bez_id, arr->a_dat,
							  arr->prg_id, arr->textid, arr->sai_id);
			break;
		case _ARR_DLG:
			ad=(ARR_DLG *)datastring;
			(void)sprintf(command, _INSERT_AD, ad->arr_id, ad->teil,
							  ad->prio, ad->dlg_id);
			break;


		case _HOST_KONT:
			hkon=(HOST_KONT *)datastring;
			hkon->hostkont_id=table_id;
			hkon->bez_id=bez_id;
			if (*hkon->ref == NULL)   /* create reference */
				{
				sprintf(ref, "HK%04d*%s", table_id, userid);
				(void)strcpy(hkon->ref, ref);
				}
			(void)sprintf(command, _INSERT_HKON, table_id, hkon->bez_id,
							  hkon->from_pers, hkon->kbst, hkon->dla_id, hkon->dl_id,
			              hkon->dl_vondat, hkon->dl_bisdat, hkon->textid,
							  hkon->opt_dat, hkon->sai_id, hkon->ref, hkon->history);
			break;
		case _KONTINGENT:
			kon=(KONTINGENT *)datastring;
			kon->kont_id=table_id;
			kon->bez_id=bez_id;
			if (*kon->ref == NULL)   /* create reference */
				{
				sprintf(ref, "K%04d*%s", table_id, userid);
				(void)strcpy(kon->ref, ref);
				}
			(void)sprintf(command, _INSERT_KON, table_id, kon->bez_id,
							  kon->hostkont_id, kon->kunden_id, kon->opt_dat,
			              kon->ref, kon->sai_id, kon->textid);
			break;
		case _KONT_DETAIL:
			k_d_ptr=(KONT_DETAIL *)datastring;
			(void)sprintf(command, _INSERT_K_D, k_d_ptr->hostkont_id,
			              k_d_ptr->kont_id, k_d_ptr->kat_id, k_d_ptr->dlt_id,
			              k_d_ptr->sta_id, k_d_ptr->anz, k_d_ptr->busy,
			              k_d_ptr->minanz, k_d_ptr->von_dat, k_d_ptr->bis_dat);
			break;


		case _BUCHUNG:
			bch=(BUCHUNG *)datastring;
			bch->bid=table_id;
			if (*bch->ref == NULL)   /* create reference */
				{
				sprintf(ref, "B%04d*%s", table_id, userid);
				(void)strcpy(bch->ref, ref);
				}
			(void)sprintf(command, _INSERT_BCH, bch->d_bid, table_id, bch->ref,
							  bch->arr_id, bch->kid, bch->sach, bch->anw,
							  bch->b_dat, bch->m_dat, bch->opt_bst, bch->opt_kid,
							  bch->sta, bch->ast, bch->sai_id, bch->k_id,
						      bch->mpid, bch->history, bch->b_text);
			break;
		case _BCH_DLN:
			bdptr=(BCH_DLN *)datastring;
			(void)sprintf(command, _INSERT_BD, bdptr->bid, bdptr->dln_id);
			break;
		case _AKT_DETAIL:
			aktdet=(AKT_DETAIL *)datastring;
			(void)sprintf(command, _INSERT_AKTD, aktdet->bid, aktdet->pers_id,
			      aktdet->dlg_id, aktdet->dl_id, aktdet->teil, aktdet->akt_id,
			      aktdet->ord, aktdet->a_typ_id, aktdet->z_flag, aktdet->akt_nr,
			      aktdet->sai_id, aktdet->parentakt, aktdet->exec_dat, aktdet->file_id);
			break;
		case _KOSTEN_ART:
			kar=(KOSTEN_ART *)datastring;
			kar->kar_id=table_id;
			kar->bez_id=bez_id;
			(void)sprintf(command, _INSERT_KAR, table_id, bez_id, kar->textid);
			break;
		case _KOMMISSION:
			kom_ptr=(KOMMISSION *)datastring;
			kom_ptr->komm_id = table_id;
			kom_ptr->bez_id = bez_id;
			(void)sprintf(command, _INSERT_KOM, kom_ptr->komm_id, kom_ptr->bez_id,
			              kom_ptr->satz_art, kom_ptr->satz, kom_ptr->komm_typ,
			              kom_ptr->kbst, kom_ptr->kar_id, kom_ptr->dltt_id, kom_ptr->kat_id,
			              kom_ptr->rkr_id, kom_ptr->dla_id, kom_ptr->dl_id,
			              kom_ptr->dl_vondat, kom_ptr->dl_bisdat, kom_ptr->kont_id,
							  kom_ptr->bid, kom_ptr->history, kom_ptr->sai_id,
			              kom_ptr->textid);
			break;
		case _KOMM_DETAIL:
			kd_ptr=(KOMM_DETAIL *)datastring;
			(void)sprintf(command, _INSERT_KD, kd_ptr->komm_id, kd_ptr->bid,
			              kd_ptr->dln_id, kd_ptr->kun_id, kd_ptr->kol_id,
			              kd_ptr->prio);
			break;
		case _RESERVATION:
			res=(RESERVATION *)datastring;
			(void)sprintf(command, _INSERT_RES, res->pers_id, res->dlg_id,
                       res->dl_id, res->teil, res->dlt_id, res->typ_id,
			              res->bid, res->kont_id, res->kat_id, res->k_kon,
			              res->b_kon, res->r_sta, res->sai_id, res->a_zeit,
			              res->e_zeit, res->textid);
			break;
		case	_PREIS	:
			pre=(PREIS *)datastring;
			pre->pre_id = table_id;
			(void)sprintf(command, _INSERT_PRE, pre->pre_id, pre->apr,
			              pre->epr, pre->vpr, pre->glt, pre->whr_id, pre->kbst,
			              pre->kar_id, pre->dltt_id, pre->kat_id, pre->rkr_id, pre->dla_id,
							  pre->arr_id, pre->dl_id, pre->ext_id, pre->dl_vondat, pre->dl_bisdat, pre->kont_id,
							  pre->sta_id, pre->textid, pre->history, pre->sai_id, pre->unit_typ,
	                    pre->unit_von, pre->unit_bis, pre->dau, pre->dau_von, pre->dau_bis);
			break;
		case _KAPA:
			kapa=(KAPA *)datastring;
			(void)sprintf(command, _INSERT_KAPA, kapa->kat_id, kapa->katbez_id,
			              kapa->tdl_id, kapa->tdlbez_id, kapa->pre_id,
			              kapa->anz, kapa->busy, kapa->vpr, kapa->von_dat, kapa->bis_dat);
			break;
		case _MP_ARRKOM:
			arrkom=(MP_ARRKOM *)datastring;
			(void)sprintf(command, _INSERT_ARRKOM, arrkom->arr_id, arrkom->komm_id,
			              arrkom->komm_bezid);
			break;


		case _GRAPHIK:
			gra=(GRAPHIK *)datastring;
			gra->gra_id=table_id;
			(void)sprintf(command, _INSERT_GRA, table_id, bez_id, gra->dlt_id, gra->textid);
			break;
		case _GRAFORM:
			graform=(GRAFORM *)datastring;
			(void)sprintf(command, _INSERT_GRAFORM, graform->gra_id, graform->formnr,
			                  graform->form);
			break;
		case _REGIONS:
			reg=(REGIONS *)datastring;
			(void)sprintf(command, _INSERT_REG, reg->host_id, reg->h_dlt_id, reg->dlt_id,
							  reg->folge, reg->stufe, reg->nummer);
			break;
		case	_PCX_FILES	:
			pcx=(PCX_FILES *)datastring;
			pcx->pcx_id=table_id;
			(void)sprintf(command, _INSERT_PCX, table_id, bez_id, pcx->filename,
			              pcx->x, pcx->y, pcx->typ, pcx->typcode, pcx->folge);
			break;

		/* unwahrscheinliches Abfangen */
		default:
			status = (int)MPE_WRONGOBJECT;
			break;
		}

	/* Insert entry command */
	if (status == (int)MPOK)
		status = MPAPIdb_sqlcommand(command, &anzahl);

	/* if anzahl is 0 then set error code */
	if (status == (int)MPOK && anzahl == 0)
		status = (int)MPE_NOINSUPDDEL;

	return(status);
}
