/*D***********************************************************
 * header:    global vars for DB API library
 *
 * copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpvarapi.h,v 1.3 2008-11-23 15:44:38 mwn Exp $
*/


/* global SPRACH-ID and USER-ID (from system) */

int  sprache;                 /* Momentan g�ltige Sprach Id */
char userid[_USERLEN+1];		/* User Bezeichnung */
char userpassword[_PWDLEN+1];	/* User Password */

/* SQL */
MEMOBJ         apimem;
char sqlquery[_QUERYLEN];              /* global SQL query buffer */

/* interne admin tabellen */
MP_GLOBALPROFIL globprof;
MP_PROFIL      prof;
SPRACHEN			spr;
STATUS_WERTE	sta;
BEZEICHNUNG		bez;
TEXTE				txt;
MP_MSG			msg;
HISTORY			his;
SAISON			sai;

/* GEOGRAFIE  LAND/ORT/WAEHRUNG */
LAND      land;
ORT       ort;
WAEHRUNG  whr;
LAND_WHR  lw;
LAND_SPR  ls;

/* PERSONEN / GRUPPEN */
PERSONEN			pers;
PERSADR			adr;
REISENDER		dln;
REISENDER_TYP	dlnt;
KUNDEN			kun;
KUNDEN_TYP		kunt;
KOLLEKTIV		kol;
KOLLEKTIV_TYP	kolt;

/* STAMMDATEN */
TRAEGER_TYP		dltt;
KATEGORIE		kat;
DIENST_TRAEGER	dlt;
ANGEBOTS_TYP	dlat;
AKTIONEN			akt;
AKTIONSGRP     aktgrp;
AKTIONS_TYP		aktt;
AKTIONSPARA    para;
DIENST_ANGEBOT	dla;
DLG_PART			tdl;
DLG_DLG			dd;
DIENSTLEISTUNG	dl;
PROGRAMM			prg;
ARRANGEMENT		arr;
ARR_DLG			ad;

/* KONTINGENTE */
HOST_KONT		hkon;
KONTINGENT		kon;
KONT_DETAIL		kond;

/* BUCHUNG / PREIS / RESERVATION */
BUCHUNG			bch;
BCH_DLN        bd;
KOSTEN_ART		kar;
KOMMISSION		kom;
MP_ARRKOM      arrkom;
KOMM_DETAIL		komd;
PREIS				pre;
RESERVATION		res;
KAPA				kapa;

/* GRAFIK / PCX / REGIONS  */
GRAPHIK		gra;
PCX_FILES	pcx;



/***********************************************
 * DATABASE VIEWS OBJECTS
 ***********************************************/
DLN_VIEW			dlnv;
KUN_VIEW			kunv;
MPV_KUNADR		kunadrv;
TTYP_VIEW		ttyp;
TRAEGER_VIEW	trv;
AKT_VIEW			aktv;
RES_DL_VIEW		resdlv;



// TODO review old struct variables if still needed and replace
/***********************************************
 *  O L D     S T U F F
 *
 *  delete these names at the time !!!
 ***********************************************/
STATUS_WERTE	sta_old;
REISENDER		rei;
REISENDER_TYP	reit;
DLG_PART			dlg;
DLG_DLG			dd_old;
DIENSTLEISTUNG	dtg;
ARR_DLG			ad_old;
KONT_DETAIL		k_d;
KONT_DETAIL		k_d_old;
RESERVATION		res_old;
KOMM_DETAIL		kd;
KOMM_DETAIL		kd_old;
PREIS				pre_old;


// TODO delete these things - ARR detail buffers and flags
char *ad_buffer;		/* Buffer mit den Dienstleistungen eines Arrangementes */
int AnzParts;			/* Anzahl Teilstrecken eines Arrangements */
int AnzDlg;				/* Anzahl Dienstleistungen eines Arrangements */
