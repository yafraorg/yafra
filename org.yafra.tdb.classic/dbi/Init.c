/*D***********************************************************
 * Modul:     DBI - admin
 *            set the global structurs for a menu or only a
 *            field to _UNDEF
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/Init.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

extern DIENST_TRAEGER	dlt;
extern TRAEGER_TYP		dltt;
extern DIENST_ANGEBOT	dla;
extern ANGEBOTS_TYP		dlat;
extern AKTIONEN			akt;
extern AKTIONS_TYP		aktt;
extern AKTIONSPARA      para;
extern AKTIONSGRP       aktgrp;
extern KATEGORIE			kat;
extern PERSONEN			pers;
extern KUNDEN				kun;
extern KUNDEN_TYP			kunt;
extern REISENDER_TYP		reit;
extern KOSTEN_ART			kar;
extern KOLLEKTIV_TYP		kolt;
extern PROGRAMM			prg;
extern PREIS				pre;
extern REISENDER			rei;
extern KOLLEKTIV			kol;
extern SAISON				sai;
extern ARRANGEMENT		arr;
extern DIENSTLEISTUNG	dtg;
extern DLG_PART			dlg;
extern BUCHUNG				bch;
extern RESERVATION		res;
extern KONTINGENT			kon;
extern GRAPHIK				gra;
extern PCX_FILES			pcx;
extern BEZEICHNUNG		bez;
extern TEXTE				txt;
extern SPRACHEN			spr;

extern char glob_dltbez[];
extern char glob_hdlt_dlt[];
extern char glob_host_dlt[];
extern char glob_bez_arr[];
extern char glob_dlt_bch[];
extern char glob_arr_bch[];
extern char glob_dl_bch[];
extern char glob_dat_bch[];
extern char glob_dln_bch[];
extern char glob_bez_dlg[];
extern char glob_bez_dtg[];
extern char glob_dat_dtg[];
extern char glob_dlg_dtg[];
extern char glob_bez_dla[];
extern char glob_bez_akt[];
extern int glob_para_aktt;
extern char glob_akt_out[];
extern char glob_dlg_out[];
extern char glob_dtg_res[];
extern char glob_dlg_res[];
extern char glob_kon_res[];
extern char glob_kat_res[];
extern char glob_dlt_res[];
extern char glob_typ_res[];
extern char glob_dtg_arr[];	 /* gew�hlte Dienstleistung auf Arr */
extern char glob_typbez_sta[]; /* gew�hlter Status Typ auf Sta */

extern char glob_kond_hkon[];
extern char glob_kond_kon[];
extern char glob_kond_kat[];
extern char glob_kond_dlt[];

extern char glob_bez_kom[];
extern char glob_typ_kom[];
extern char glob_kar_kom[];      /* Kommission */
extern char glob_satz_kom[];
extern char glob_satztyp_kom[];

extern char glob_lw_land[];
extern char glob_lw_whr[];
extern char glob_lw_kurstyp[];

extern int glob_typ_sta;
extern int glob_spr_bez;
extern int glob_typ_bez;
extern int glob_teil;
extern int glob_prio;
extern int Prio;
extern int Ord;
extern int glob_typ_msg;

extern int dla_selected;

extern unsigned char bm_obj;
extern unsigned char bm_state;
extern unsigned int  bm_dlncnt;

/*F***********************************************************
 * Function:  Init the globals of a menu
 *************************************************************/
void InitMenu(void)
{
	switch(MENUNR)
		{
		case (unsigned char)_LAND_WHR:
			glob_lw_land[0] = NULL;
			glob_lw_whr[0] = NULL;
			glob_lw_kurstyp[0] = NULL;
			break;
		case (unsigned char)_DIENST_TRAEGER:
			glob_host_dlt[0] = NULL;
			glob_hdlt_dlt[0] = NULL;
			glob_dltbez[0] = NULL;
			break;

		case	(unsigned char)_STATUS_WERTE	:
			glob_spr_bez = (int)_UNDEF;
			glob_typ_sta = (int)_UNDEF;
			glob_typbez_sta[0] = NULL;
			break;
		case	(unsigned char)_BEZEICHNUNG:
			glob_typ_bez = (int)_UNDEF;
			break;
		case	(unsigned char)_MSG:
			glob_typ_msg = (int)_UNDEF;
			break;



		case (unsigned char)_ARRANGEMENT:
			glob_bez_arr[0] = NULL;
			glob_dtg_arr[0] = NULL;
			break;
		case (unsigned char)_DIENSTLEISTUNG	:
			glob_bez_dtg[0] = NULL;
			glob_dat_dtg[0] = NULL;
			glob_dlg_dtg[0] = NULL;
			break;
		case (unsigned char)_DLG_PART:
			glob_bez_dlg[0] = NULL;
			break;
		case (unsigned char)_DIENST_ANGEBOT:
			glob_bez_dla[0] = NULL;
			break;
		case (unsigned char)_AKTIONEN:
			glob_bez_akt[0] = NULL;
			break;
		case (unsigned char)_OUTPUT:
			glob_akt_out[0] = NULL;
			glob_dlg_out[0] = NULL;
			break;
		case (unsigned char)_AKTIONS_TYP:
			glob_para_aktt = (int)NULL;
			break;


		case (unsigned char)_HOST_KONT:
		case (unsigned char)_KONTINGENT:
			break;
		case (unsigned char)_KONT_DETAIL:
			glob_kond_hkon[0] = NULL;
			glob_kond_kon[0] = NULL;
			glob_kond_kat[0] = NULL;
			glob_kond_dlt[0] = NULL;
			break;



		case	(unsigned char)_BUCHUNG:
			glob_arr_bch[0] = NULL;
			glob_dlt_bch[0] = NULL;
			glob_dat_bch[0] = NULL;
			glob_dl_bch[0] = NULL;
			glob_dln_bch[0] = NULL;
			bm_state = (unsigned char)_BM_NOP;
			bch.bid     = (int)_UNDEF;
			rei.pers_id = (int)_UNDEF;
			dtg.dlg_id  = (int)_UNDEF;
			arr.arr_id  = (int)_UNDEF;
			dla_selected = (int)FALSE;
			break;
		case (unsigned char)_RESERVATION:
			Ord=(int)0;
			glob_dlg_res[0] = NULL;
			glob_dlt_res[0] = NULL;
			glob_typ_res[0] = NULL;
			glob_kon_res[0] = NULL;
			glob_kat_res[0] = NULL;
			glob_teil = (int)0;
			Prio = glob_prio = (int)0;
			glob_dtg_res[0] = NULL;
			res.pers_id = (int)_UNDEF;
			res.bid  = (int)_UNDEF;
			break;
		case (unsigned char)_BMDLN:
			pers.pers_id = (int)_UNDEF;
			pers.name[0] = NULL;
			rei.pers_id = (int)_UNDEF;
			break;
		case (unsigned char)_REISENDER:
			bch.bid     = (int)_UNDEF;
			pers.pers_id = (int)_UNDEF;
			pers.name[0] = NULL;
			rei.pers_id = (int)_UNDEF;
			dtg.dlg_id  = (int)_UNDEF;
			arr.arr_id  = (int)_UNDEF;
			break;
		case	(unsigned char)_KOMMISSION	:
			glob_bez_kom[0] = NULL;
			glob_typ_kom[0] = NULL;
			glob_kar_kom[0] = NULL;
			glob_satz_kom[0] = NULL;
			glob_satztyp_kom[0] = NULL;
			break;
		case (unsigned char)_KOMM_DETAIL:
			glob_bez_kom[0] = NULL;
			glob_arr_bch[0] = NULL;
			arr.arr_id  = (int)_UNDEF;
			bch.bid     = (int)_UNDEF;
			rei.pers_id = (int)_UNDEF;
			break;
		case (unsigned char)_PREIS:
			pre.pre_id = (int)_UNDEF;
			break;
		}
}


/*F***********************************************************
 * Function:  Init the globals for a field
 *************************************************************/
void InitField(void)
{
	switch(MENUNR)
		{
		case (unsigned char)_LAND_WHR:
			switch(FELDNR)
				{
				case MLW_LAND:
					glob_lw_land[0] = NULL;
					break;
				case MLW_WHR:
					glob_lw_whr[0] = NULL;
					break;
				case MLW_KURSTYP:
					glob_lw_kurstyp[0] = NULL;
					break;
				}
			break;

		case (unsigned char)_DIENST_TRAEGER:
			switch(FELDNR)
				{
				case MDLT_BEZ:
					glob_dltbez[0] = NULL;
					break;
				case MDLT_HOST:
					glob_host_dlt[0] = NULL;
					break;
				case MDLT_HDLT:
					glob_hdlt_dlt[0] = NULL;
					break;
				}
			break;
		case	(unsigned char)_BEZEICHNUNG:
			switch(FELDNR)
				{
				case MBEZ_BEZTYP:
					glob_typ_bez = (int)_UNDEF;
					break;
				}
			break;
		case	(unsigned char)_MSG:
			switch(FELDNR)
				{
				case MMSG_TYP:
					glob_typ_msg = (int)_UNDEF;
					break;
				}
			break;


		case (unsigned char)_ARRANGEMENT:
			switch(FELDNR)
				{
				case MARR_ARR:
					glob_bez_arr[0] = NULL;
					break;
				case MARR_DTG:
					glob_dtg_arr[0] = NULL;
					break;
				}
			break;
		case (unsigned char)_DIENSTLEISTUNG	:
			switch(FELDNR)
				{
				case MDL_BEZ:
					glob_bez_dtg[0] = NULL;
					break;
				case MDL_TDL:
					glob_dlg_dtg[0] = NULL;
					break;
				case MDL_DAT:
					glob_dat_dtg[0] = NULL;
					break;
				}
			break;
		case (unsigned char)_DLG_PART:
			switch(FELDNR)
				{
				case MDLG_DLGPART:
					glob_bez_dlg[0] = NULL;
					break;
				}
			break;
		case (unsigned char)_DIENST_ANGEBOT:
			switch(FELDNR)
				{
				case MDLA_DLAHOST:
					glob_bez_dla[0] = NULL;
					break;
				}
			break;
		case (unsigned char)_AKTIONEN:
			switch(FELDNR)
				{
				case MAKT_BEZ:
					glob_bez_akt[0] = NULL;
					break;
				}
			break;
		case (unsigned char)_AKTIONS_TYP:
			switch(FELDNR)
				{
				case MAKTT_PARANR:
					glob_para_aktt = (int)NULL;
					break;
				}
			break;



		case (unsigned char)_KONT_DETAIL:
			switch(FELDNR)
				{
				case MKOND_HKON:
					glob_kond_hkon[0] = NULL;
					break;
				case MKOND_KON:
					glob_kond_kon[0] = NULL;
					break;
				case MKOND_KAT:
					glob_kond_kat[0] = NULL;
					break;
				case MKOND_DLT:
					glob_kond_dlt[0] = NULL;
					break;
				}
			break;
		case	(unsigned char)_PREIS:
			switch(FELDNR)
				{
				case MPRE_NR:
					pre.pre_id = (int)_UNDEF;
					break;
				}
			break;
		case	(unsigned char)_STATUS_WERTE:
			switch(FELDNR)
				{
				case MSTA_BEZ:
					glob_spr_bez = (int)_UNDEF;
					break;
				case MSTA_TYP:
					glob_typ_sta = (int)_UNDEF;
					glob_typbez_sta[0] = NULL;
					break;
				}
			break;




		case	(unsigned char)_BUCHUNG:
			switch(FELDNR)
				{
				case MBCH_ARR:
					glob_arr_bch[0] = NULL;
					break;
				case MBCH_DLT:
					glob_dlt_bch[0] = NULL;
					break;
				case MBCH_DL:
					glob_dl_bch[0] = NULL;
					break;
				case MBCH_DAT:
					glob_dat_bch[0] = NULL;
					break;
				case MBCH_DLN:
					glob_dln_bch[0] = NULL;
					break;
				case MBCH_DLA:
					dla_selected = (int)FALSE;
					break;
				}
			break;
		case	(unsigned char)_KOMMISSION	:
			switch(FELDNR)
				{
				case MKOM_BEZ:
					glob_bez_kom[0] = NULL;
					break;
				case MKOM_TYP:
					glob_typ_kom[0] = NULL;
					break;
				case MKOM_SATZ:
					glob_satz_kom[0] = NULL;
					break;
				case MKOM_SATZTYP:
					glob_satztyp_kom[0] = NULL;
					break;
				case MKOM_KAR:
					glob_kar_kom[0] = NULL;
					break;
				}
			break;

		case (unsigned char)_KOMM_DETAIL:
			switch(FELDNR)
				{
				case MKOMD_KOM:
					glob_bez_kom[0] = NULL;
					break;
				case MKOMD_BCH:
					glob_arr_bch[0] = NULL;
					arr.arr_id  = (int)_UNDEF;
					bch.bid     = (int)_UNDEF;
					break;
				case MKOMD_DLN:
					rei.pers_id = (int)_UNDEF;
					break;
				}
			break;
		}
	/* Buffer loeschen und initialisieren */
	comm.datalen   = 0;
	comm.buffer[0] = NULL;
}



/*F***********************************************************
 * Function:  Init the global-menu
 *************************************************************/
void InitGlobal(GLOBDATA *glob_buffer)
{
	int i;

	/* init flag fields */
	bm_state = (unsigned char)_BM_NOP;

	/* Init each object on the global menu */
	dlt.dlt_id = (int)_UNDEF;

	dltt.typ_id = (int)_UNDEF;

	dla.dla_id = (int)_UNDEF;
	dlat.art_id = (int)_UNDEF;

	akt.akt_id = (int)_UNDEF;
	aktt.a_typ_id = (int)_UNDEF;
	para.a_typ_id = (int)_UNDEF;
	para.nr = (int)_UNDEF;
	aktgrp.parentakt = (int)_UNDEF;
	aktgrp.childakt = (int)_UNDEF;

	kat.kat_id = (int)_UNDEF;

	kun.pers_id = (int)_UNDEF;
	kunt.k_typ_id = (int)_UNDEF;

	reit.rkr_id = (int)_UNDEF;

	kar.kar_id = (int)_UNDEF;

	kol.k_id = (int)_UNDEF;
	kolt.k_typ_id = (int)_UNDEF;

	prg.prg_id = (int)_UNDEF;

	sai.sai_id = (int)_UNDEF;

	arr.arr_id = (int)_UNDEF;

	dtg.dlg_id = (int)_UNDEF;

	dlg.dl_id = (int)_UNDEF;

	bch.bid = (int)_UNDEF;
	pers.pers_id = (int)_UNDEF;
	pers.name[0] = NULL;
	rei.pers_id = (int)_UNDEF;
	res.bid = (int)_UNDEF;
	res.pers_id = (int)_UNDEF;

	kon.kont_id = (int)_UNDEF;

	gra.gra_id = (int)_UNDEF;

	txt.textid = (int)_UNDEF;

	spr.s_id = (int)_UNDEF;
	pre.pre_id = (int)_UNDEF;

	/* Init all Menus */
	for (i=0; i < 256; i++)
		{
		MENUNR = (unsigned char)i;
		InitMenu();
		}
}
