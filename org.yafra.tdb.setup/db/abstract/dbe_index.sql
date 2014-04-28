/*D************************************************************/
/* project:   travelDB                                        */
/*                                                            */
/*            create indexes                                  */
/*                                                            */
/* copyright: yafra.org, 2003, Switzerland                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/dbe_index.sql,v 1.5 2008-11-29 22:09:58 mwn Exp $ */

/*********************************************************/
/* CODEs and TEXTE/BEZ                                   */
/*********************************************************/

/* SPRACHEN Tabelle */
drop index spr_index from sprachen;
drop index sprbez_index from sprachen;
create unique index spr_index on sprachen (S_ID);
create unique index sprbez_index on sprachen (BEZ_ID);

/* STATUS_WERTE Tabelle */
drop index statyp_index from status_werte;
drop index sta_index from status_werte;
drop index staid_index from status_werte;
drop index stabezid_index from status_werte;
drop index stabez_index from status_werte;
create clustering index statyp_index on status_werte (TYP);
create unique index sta_index on status_werte (STA_ID, TYP);
create unique index stabez_index on status_werte (BEZ_ID, TYP);
create index staid_index on status_werte (STA_ID);
create index stabezid_index on status_werte (BEZ_ID);

/* BEZEICHNUNG Tabelle */
drop index bezspr_index from bezeichnung;
drop index bezeich_index from bezeichnung;
drop index bez_index from bezeichnung;
drop index bezid_index from bezeichnung;
drop index bezidtyp_index from bezeichnung;
drop index btyp_index from bezeichnung;
drop index btypspr_index from bezeichnung;
create clustering index bezspr_index on bezeichnung (S_ID);
create unique index bezeich_index on bezeichnung (BEZ_ID, S_ID, TYP);
/*create index bez_index on bezeichnung (BEZ);*/
create index bezid_index on bezeichnung (BEZ_ID);
create index bezidtyp_index on bezeichnung (BEZ_ID, TYP);
create index btyp_index on bezeichnung (TYP);
create index btypspr_index on bezeichnung (S_ID, TYP);

/* TEXTE Tabelle */
drop index textspr_index from texte;
drop index textid_index from texte;
drop index text_index from texte;
drop index textidtyp_index from texte;
drop index texttypspr_index from texte;
drop index texttyp_index from texte;
create clustering index textspr_index on texte (S_ID);
create unique index textid_index on texte (TEXTID, TEXTNR, S_ID, TYP);
create index text_index on texte (TEXTID, S_ID, TYP);
create index textidtyp_index on texte (TEXTID, TYP);
create index texttypspr_index on texte (S_ID, TYP);
create index texttyp_index on texte (TYP);

/* AKTIONSTEXTE Tabelle */
drop index atextspr_index from aktionstexte;
drop index atextid_index from aktionstexte;
drop index atext_index from aktionstexte;
drop index atexttypspr_index from aktionstexte;
drop index atexttyp_index from aktionstexte;
create clustering index atextspr_index on aktionstexte (S_ID);
create unique index atextid_index on aktionstexte (TEXTID, TEXTNR, S_ID, TYP);
create index atext_index on aktionstexte (TEXTID, S_ID, TYP);
create index atexttypspr_index on aktionstexte (S_ID, TYP);
create index atexttyp_index on aktionstexte (TYP);

/* HISTORY Tabelle */
drop index hisspr_index from history;
drop index his_index from history;
drop index hisid_index from history;
create clustering index hisspr_index on history (S_ID);
create unique index his_index on history (HIS_ID, S_ID, TEXTNR);
create index hisid_index on history (HIS_ID);

/* HELP Tabelle */
drop index hlpspr_index from help;
drop index hlp_index from help;
drop index hlptyp_index from help;
create clustering index hlpspr_index on help (S_ID);
create unique index hlp_index on help (HELP_TYP, HELP_ID, S_ID, TEXTNR);
create index hlptyp_index on help (HELP_TYP);

/* MSG Tabelle */
drop index msgspr_index from msg;
drop index msg_index from msg;
drop index msgtyp_index from msg;
create clustering index msgspr_index on msg (S_ID);
create unique index msg_index on msg (MSG_TYP, MSG_ID, S_ID, TEXTNR);
create index msgtyp_index on msg (MSG_TYP);

/* LABEL Tabelle */
drop index labelspr_index from label;
drop index label_index from label;
create clustering index labelspr_index on label (S_ID);
create unique index label_index on label (LABEL_PRG, LABEL_TYP,
 STUFE1, STUFE2, S_ID);

/* SAISON Tabelle */
drop index sai_index from saison;
drop index saibez_index from saison;
create unique index sai_index on saison (SAI_ID);
create unique index saibez_index on saison (BEZ_ID);




/**********************************************/
/* GEOGRAPHIE                                 */
/**********************************************/

/* WAEHRUNG Tabelle */
drop index whr_index from waehrung;
drop index whrbez_index from waehrung;
create unique index whr_index on waehrung (WHR_ID);
create unique index whrbez_index on waehrung (BEZ_ID);

/* LAND Tabelle */
drop index land_index from land;
drop index landbez_index from land;
create unique index land_index on land (LAND_ID);
create unique index landbez_index on land (BEZ_ID);

/* ORT Tabelle */
drop index ort_index from ort;
drop index ortbez_index from ort;
create unique index ort_index on ort (ORT_ID, LAND_ID);
create unique index ortbez_index on ort (BEZ_ID);

/* LAND_WHR Tabelle */
drop index lw_index from land_whr;
drop index lw_land_index from land_whr;
drop index lw_whr_index from land_whr;
create unique index lw_index on land_whr (LAND_ID, WHR_ID, KURS_TYP);
create index lw_land_index on land_whr (LAND_ID);
create index lw_whr_index on land_whr (WHR_ID);

/* LAND_SPR Tabelle */
drop index land_spr_index from land_spr;
create unique index land_spr_index on land_spr (LAND_ID, S_ID);



/**********************************************/
/* PERSONEN STAMM  (KUNDEN, REISENDE)         */
/**********************************************/

/* PERSONEN Tabelle */
drop index persid_index from personen;
drop index perstyp_index from personen;
drop index pers_index from personen;
create unique index persid_index on personen (PERS_ID);
create index perstyp_index on personen (PERS_TYP);
create index pers_index on personen (NAME);

/* REISENDER_TYP Tabelle */
drop index rkr_index from reisender_typ;
drop index rkrbez_id_index from reisender_typ;
create unique index rkr_index on reisender_typ (RKR_ID);
create unique index rkrbez_id_index on reisender_typ (BEZ_ID);

/* REISENDER Tabelle */
drop index dlnid_index from reisender;
create unique index dlnid_index on reisender (PERS_ID);

/* PERSADR Tabelle */
drop index persadrid_index from persadr;
drop index persadr_index from persadr;
create unique index persadrid_index on persadr (PERS_ID);
create index persadr_index on persadr (PLZ, ADR1, ADR2, ADR3);

/* KUNDENTYP Tabelle */
drop index kun_typ_index from kunden_typ;
drop index kunbez_id_index from kunden_typ;
create unique index kun_typ_index on kunden_typ (K_TYP_ID);
create unique index kunbez_id_index on kunden_typ (BEZ_ID);

/* KUNDEN Tabelle */
drop index kid_index from kunden;
create unique index kid_index on kunden (PERS_ID);

/* KOLLEKTIVTYP Tabelle */
drop index koltid_index from kollektiv_typ;
drop index kolt_bezid_index from kollektiv_typ;
create unique index koltid_index on kollektiv_typ (K_TYP_ID);
create unique index kolt_bezid_index on kollektiv_typ (BEZ_ID);

/* KOLLEKTIV Tabelle */
drop index kolid_index from kollektiv;
drop index kol_koltid_index from kollektiv;
create unique index kolid_index on kollektiv (K_ID);
create index kol_koltid_index on kollektiv (K_TYP_ID);




/**********************************************/
/* RESERVATIONSKERN  (TRAEGER, ANGEBOT)       */
/**********************************************/

/* TRAEGERTYP Tabelle */
drop index dltthost_index from traeger_typ;
drop index dltt_index from traeger_typ;
drop index dlttbez_index from traeger_typ;
drop index dltt_beztyp_index from traeger_typ;
drop index dltt_htyp_index from traeger_typ;
create clustering index dltthost_index on traeger_typ (HOST_TYP);
create unique index dltt_index on traeger_typ (TYP_ID);
create unique index dlttbez_index on traeger_typ (BEZ_ID);
create index dltt_beztyp_index on traeger_typ (BEZ_ID, TYP_ID);
create index dltt_htyp_index on traeger_typ (H_TYP_ID);

/* KATEGORIE Tabelle */
drop index kat_index from kategorie;
drop index katbez_index from kategorie;
drop index kat_bezid_index from kategorie;
drop index kathost_index from kategorie;
drop index kattxt_index from kategorie;
create unique index kat_index on kategorie (KAT_ID);
create unique index katbez_index on kategorie (BEZ_ID);
create index kat_bezid_index on kategorie (BEZ_ID, KAT_ID);
create index kathost_index on kategorie (H_KAT_ID);
create index kattxt_index on kategorie (TEXTID);

/* DIENSTLEISTUNGSTRAEGER Tabelle */
drop index dlthost_index from dienst_traeger;
drop index dlt_index from dienst_traeger;
drop index dlt_host_index from dienst_traeger;
drop index dlthhost_index from dienst_traeger;
drop index dltu_index from dienst_traeger;
drop index dltbezid_index from dienst_traeger;
drop index dlth_index from dienst_traeger;
drop index dlthdlt_index from dienst_traeger;
drop index dlth_host_index from dienst_traeger;
drop index dlthbez_index from dienst_traeger;
drop index dltdltt_index from dienst_traeger;
drop index dlth_dltt_index from dienst_traeger;
drop index dlthost_dltt_index from dienst_traeger;
drop index dltkat_index from dienst_traeger;
drop index dltkat_host_index from dienst_traeger;
drop index dlttxt_index from dienst_traeger;
create clustering index dlthost_index on dienst_traeger (HOST_ID);
create unique index dlt_index on dienst_traeger (DLT_ID);
create unique index dlt_host_index on dienst_traeger (DLT_ID, HOST_ID);
create unique index dlthhost_index on dienst_traeger (DLT_ID,
 H_DLT_ID, HOST_ID);
create unique index dltu_index on dienst_traeger (BEZ_ID, H_DLT_ID, HOST_ID);
create index dltbezid_index on dienst_traeger (BEZ_ID);
create index dlth_index on dienst_traeger (H_DLT_ID);
create index dlthdlt_index on dienst_traeger (DLT_ID, H_DLT_ID);
create index dlth_host_index on dienst_traeger (H_DLT_ID, HOST_ID);
create index dlthbez_index on dienst_traeger (DLT_GRP_ID);
create index dltdltt_index on dienst_traeger (TYP_ID);
create index dlth_dltt_index on dienst_traeger (H_DLT_ID, TYP_ID);
create index dlthost_dltt_index on dienst_traeger (HOST_ID, TYP_ID);
create index dltkat_index on dienst_traeger (KAT_ID);
create index dltkat_host_index on dienst_traeger (HOST_ID, KAT_ID);
create index dlttxt_index on dienst_traeger (TEXTID);

/* ANGEBOTSTYP Tabelle */
drop index art_index from angebots_typ;
drop index artbezid_index from angebots_typ;
create unique index art_index on angebots_typ (ART_ID);
create unique index artbezid_index on angebots_typ (BEZ_ID);

/* AKTIONSTYP Tabelle */
drop index aktt_index from aktions_typ;
drop index akttbez_index from aktions_typ;
create unique index aktt_index on aktions_typ (A_TYP_ID);
create unique index akttbez_index on aktions_typ (BEZ_ID);

/* AKTIONSPARA Tabelle */
drop index aparatyp_index from aktionspara;
drop index apara_index from aktionspara;
create clustering index aparatyp_index on aktionspara (A_TYP_ID);
create unique index apara_index on aktionspara (A_TYP_ID, NR);

/* AKTIONEN Tabelle */
drop index akttyp_index from aktionen;
drop index akt_index from aktionen;
drop index aktbez_index from aktionen;
create clustering index akttyp_index on aktionen (A_TYP_ID);
create unique index akt_index on aktionen (AKT_ID);
create unique index aktbez_index on aktionen (BEZ_ID);

/* AKTIONSGRP Tabelle */
drop index aktghost_index from aktionsgrp;
drop index aktg_index from aktionsgrp;
drop index aktg_child_index from aktionsgrp;
create clustering index aktghost_index on aktionsgrp (PARENTAKT);
create unique index aktg_index on aktionsgrp (PARENTAKT, CHILDAKT, ORD);
create index aktg_child_index on aktionsgrp (CHILDAKT);

/* DIENSTLEISTUNGSANGEBOT Tabelle */
drop index dlahost_index from dienst_angebot;
drop index dla_index from dienst_angebot;
drop index dlabez_index from dienst_angebot;
drop index dlaord_index from dienst_angebot;
drop index dladlt_index from dienst_angebot;
drop index dlaakt_index from dienst_angebot;
drop index dlatxt_index from dienst_angebot;
create clustering index dlahost_index on dienst_angebot (H_DLA_ID);
create unique index dla_index on dienst_angebot (DLA_ID);
create unique index dlabez_index on dienst_angebot (BEZ_ID);
create unique index dlaord_index on dienst_angebot (DLA_ID, ORD);
create index dladlt_index on dienst_angebot (DLT_ID);
create index dlaakt_index on dienst_angebot (AKT_ID);
create index dlatxt_index on dienst_angebot (TEXTID);

/* DLG_PARTS Tabelle */
drop index tdlhost_index from dlg_parts;
drop index tdl_index from dlg_parts;
drop index tdlbez_index from dlg_parts;
drop index tdl_host_index from dlg_parts;
drop index tdldla_index from dlg_parts;
drop index tdl_dla_index from dlg_parts;
drop index tdlzeit_index from dlg_parts;
drop index tdlazeit_index from dlg_parts;
drop index tdlezeit_index from dlg_parts;
drop index tdlbezid_index from dlg_parts;
drop index tdltxt_index from dlg_parts;
create clustering index tdlhost_index on dlg_parts (H_DL_ID);
create unique index tdl_index on dlg_parts (DL_ID);
create unique index tdlbez_index on dlg_parts (BEZ_ID, A_ZEIT);
create index tdl_host_index on dlg_parts (H_DL_ID, DL_ID);
create index tdldla_index on dlg_parts (DLA_ID);
create index tdl_dla_index on dlg_parts (DL_ID, DLA_ID);
create index tdlzeit_index on dlg_parts (A_ZEIT, E_ZEIT);
create index tdlazeit_index on dlg_parts (A_ZEIT);
create index tdlezeit_index on dlg_parts (E_ZEIT);
create index tdlbezid_index on dlg_parts (BEZ_ID);
create index tdltxt_index on dlg_parts (TEXTID);

/* DIENSTLEISTUNG Tabelle */
drop index dlbez_index from dienstleistung;
drop index dl_index from dienstleistung;
drop index dl_bez_index from dienstleistung;
drop index dlazeit_index from dienstleistung;
drop index dlakt_index from dienstleistung;
drop index dlbezid_index from dienstleistung;
drop index dltxt_index from dienstleistung;
create unique index dlbez_index on dienstleistung (BEZ_ID, A_ZEIT);
create unique index dl_index on dienstleistung (DLG_ID);
create index dl_bez_index on dienstleistung (DLG_ID, BEZ_ID);
create index dlazeit_index on dienstleistung (A_ZEIT);
create index dlakt_index on dienstleistung (AKT_ID);
create index dlbezid_index on dienstleistung (BEZ_ID);
create index dltxt_index on dienstleistung (TEXTID);

/* DLG_DLG Tabelle */
drop index dlg_dl_index from dlg_dlg;
drop index dlg_index from dlg_dlg;
drop index dl_index from dlg_dlg;
drop index dlg_dl_ord_index from dlg_dlg;
create unique index dlg_dl_index on dlg_dlg (DLG_ID, DL_ID);
create index dlg_index on dlg_dlg (DLG_ID);
create index dl_index on dlg_dlg (DL_ID);
create index dlg_dl_ord_index on dlg_dlg (DLG_ID, DL_ID, ORD);

/* PROGRAMM Tabelle */
drop index prgsai_index from programm;
drop index prg_index from programm;
drop index prgbez_index from programm;
create clustering index prgsai_index on programm (SAI_ID);
create unique index prg_index on programm (PRG_ID);
create unique index prgbez_index on programm (BEZ_ID);

/* ARRANGEMENT Tabelle */
drop index arr_index from arrangement;
drop index arrbez_index from arrangement;
drop index arradat_index from arrangement;
drop index arrprg_index from arrangement;
drop index arrbezid_index from arrangement;
drop index arrtxt_index from arrangement;
create unique index arr_index on arrangement (ARR_ID);
create unique index arrbez_index on arrangement (BEZ_ID, A_DAT);
create index arradat_index on arrangement (A_DAT);
create index arrprg_index on arrangement (PRG_ID);
create index arrbezid_index on arrangement (BEZ_ID);
create index arrtxt_index on arrangement (TEXTID);

/* ARR_DLG Tabelle */
drop index arrdl_index from arr_dlg;
drop index arrdl_tp_index from arr_dlg;
drop index arrdl_arr_index from arr_dlg;
drop index arrdl_dl_index from arr_dlg;
drop index arrdl_arr_dl_index from arr_dlg;
drop index arrdl_teilprio_index from arr_dlg;
create unique index arrdl_index on arr_dlg (ARR_ID, TEIL, DLG_ID);
create unique index arrdl_tp_index on arr_dlg (ARR_ID, TEIL, PRIO);
create index arrdl_arr_index on arr_dlg (ARR_ID);
create index arrdl_dl_index on arr_dlg (DLG_ID);
create index arrdl_arr_dl_index on arr_dlg (ARR_ID, DLG_ID);
create index arrdl_teilprio_index on arr_dlg (TEIL, PRIO);


/**********************************************/
/* KONTINGENTIERUNG                           */
/**********************************************/

/* HOST_KONT Tabelle */
drop index hkont_index from host_kont;
drop index hkontbez_index from host_kont;
drop index hkontdla_index from host_kont;
drop index hkontdl_index from host_kont;
drop index hkontpers_index from host_kont;
create unique index hkont_index on host_kont (HOSTKONT_ID);
create unique index hkontbez_index on host_kont (BEZ_ID);
create index hkontdla_index on host_kont (DLA_ID);
create index hkontdl_index on host_kont (DL_ID);
create index hkontpers_index on host_kont (FROM_PERS);

/* KONTINGENT Tabelle */
drop index kont_host_index from kontingent;
drop index kont_index from kontingent;
drop index kontbez_index from kontingent;
drop index kontkun_index from kontingent;
create clustering index kont_host_index on kontingent (HOSTKONT_ID);
create unique index kont_index on kontingent (KONT_ID);
create unique index kontbez_index on kontingent (BEZ_ID);
create index kontkun_index on kontingent (KUNDEN_ID);

/* KONT_DETAIL Tabelle */
drop index kd_konkatdlt_index from kont_detail;
drop index kd_konkat_index from kont_detail;
drop index kd_kondlt_index from kont_detail;
drop index kdh_kat_index from kont_detail;
drop index kdh_dlt_index from kont_detail;
drop index kd_kont_index from kont_detail;
drop index kd_host_index from kont_detail;
drop index kd_dlt_index from kont_detail;
drop index kd_kat_index from kont_detail;
create unique index kd_konkatdlt_index on kont_detail (HOSTKONT_ID, KONT_ID, KAT_ID, DLT_ID);
create index kd_konkat_index on kont_detail (KONT_ID, KAT_ID);
create index kd_kondlt_index on kont_detail (KONT_ID, DLT_ID);
create index kdh_kat_index on kont_detail (HOSTKONT_ID, KAT_ID);
create index kdh_dlt_index on kont_detail (HOSTKONT_ID, DLT_ID);
create index kd_kont_index on kont_detail (KONT_ID);
create index kd_host_index on kont_detail (HOSTKONT_ID);
create index kd_dlt_index on kont_detail (DLT_ID);
create index kd_kat_index on kont_detail (KAT_ID);


/********************************************************/
/* PROFIL / META                                        */
/********************************************************/

/* PROFIL Tabelle */
drop index pro_idxid from mp_profil;
drop index pro_idx from mp_profil;
drop index pro_user_idx from mp_profil;
drop index pro_bchst_idx from mp_profil;
create unique index pro_idxid on mp_profil (MPID);
create unique index pro_idx on mp_profil (MPUSER, BCHST);
create index pro_user_idx on mp_profil (MPUSER);
create index pro_bchst_idx on mp_profil (BCHST);


/**********************************************/
/* RESERVATION - BUCHUNG - PREIS              */
/**********************************************/

/* BUCHUNGS Tabelle */
drop index bchid_index from buchung;
drop index bchref_index from buchung;
drop index bcharr_index from buchung;
drop index bchkid_index from buchung;
drop index bchkol_index from buchung;
create unique index bchid_index on buchung (BID);
/* create unique index bchref_index on buchung (REF); TODO this index is too large for mysql */
create index bcharr_index on buchung (ARR_ID);
create index bchkid_index on buchung (KID);
create index bchkol_index on buchung (K_ID);

/* BCH_DLN Tabelle */
drop index bd_index from bch_dln;
drop index bd_dln_index from bch_dln;
drop index bd_bch_index from bch_dln;
create unique index bd_index on bch_dln (BID, DLN_ID);
create index bd_bch_index on bch_dln (BID);
create index bd_dln_index on bch_dln (DLN_ID);

/* AKT_DETAIL Tabelle */
drop index ad_index from akt_detail;
drop index adbid_index from akt_detail;
drop index aduid_index from akt_detail;
drop index addl_index from akt_detail;
drop index adtdl_index from akt_detail;
drop index adakt_index from akt_detail;
drop index adaktt_index from akt_detail;
drop index ad_bchdl_index from akt_detail;
drop index ad_bchtdl_index from akt_detail;
drop index ad_persdl_index from akt_detail;
drop index ad_perstdl_index from akt_detail;
drop index adaktg_index from akt_detail;
drop index adteil_index from akt_detail;
drop index addat_index from akt_detail;
create unique index ad_index on akt_detail (BID, PERS_ID, DLG_ID, DL_ID, TEIL,
 AKT_ID, ORD, PARENTAKT);
create index adbid_index on akt_detail (BID);
create index aduid_index on akt_detail (PERS_ID);
create index addl_index on akt_detail (DLG_ID);
create index adtdl_index on akt_detail (DL_ID);
create index adakt_index on akt_detail (AKT_ID);
create index adaktt_index on akt_detail (A_TYP_ID);
create index ad_bchdl_index on akt_detail (BID, DLG_ID);
create index ad_bchtdl_index on akt_detail (BID, DL_ID);
create index ad_persdl_index on akt_detail (PERS_ID, DLG_ID);
create index ad_perstdl_index on akt_detail (PERS_ID, DL_ID);
create index adaktg_index on akt_detail (PARENTAKT, AKT_ID, ORD);
create index adteil_index on akt_detail (BID, PERS_ID, TEIL);
create index addat_index on akt_detail (EXEC_DAT);

/* KOSTEN_ART Tabelle */
drop index kar_index from kosten_art;
drop index karbez_index from kosten_art;
drop index kartxt_index from kosten_art;
create unique index kar_index on kosten_art (KAR_ID);
create unique index karbez_index on kosten_art (BEZ_ID);
create index kartxt_index on kosten_art (TEXTID);

/* KOMMISSION Tabelle */
drop index komtyp_index from kommission;
drop index kom_index from kommission;
drop index kombez_index from kommission;
drop index kombezid_index from kommission;
drop index komkun_index from kommission;
drop index komkar_index from kommission;
drop index komkat_index from kommission;
drop index komrkr_index from kommission;
drop index komdla_index from kommission;
drop index komdl_index from kommission;
drop index komkont_index from kommission;
create clustering index komtyp_index on kommission (KOMM_TYP);
create unique index kom_index on kommission (KOMM_ID);
create unique index kombez_index on kommission (BEZ_ID, SATZ_ART, SATZ);
create index kombezid_index on kommission (BEZ_ID);
create index komkun_index on kommission (KBST);
create index komkar_index on kommission (KAR_ID);
create index komkat_index on kommission (KAT_ID);
create index komrkr_index on kommission (RKR_ID);
create index komdla_index on kommission (DLA_ID);
create index komdl_index on kommission (DL_ID);
create index komkont_index on kommission (KONT_ID);

/* KOMM_DETAIL Tabelle */
drop index komdet_index from komm_detail;
drop index komdet_kom_index from komm_detail;
drop index komdet_kun_index from komm_detail;
drop index komdet_dln_index from komm_detail;
drop index komdet_dlnbch_index from komm_detail;
drop index komdet_kol_index from komm_detail;
create unique index komdet_index on komm_detail (KOMM_ID,
 BID, DLN_ID, KUN_ID, KOL_ID, PRIO);
create index komdet_kom_index on komm_detail (KOMM_ID);
create index komdet_kun_index on komm_detail (KUN_ID);
create index komdet_dln_index on komm_detail (DLN_ID);
create index komdet_dlnbch_index on komm_detail (DLN_ID, BID);
create index komdet_kol_index on komm_detail (KOL_ID);
	
/* RESERVATIONS Tabelle */
drop index res_index from reservation;
drop index resbch_index from reservation;
drop index resbch_dl_index from reservation;
drop index resbch_persdl_index from reservation;
drop index resbch_pt_index from reservation;
drop index resbch_pdt_index from reservation;
drop index respers_index from reservation;
drop index respers_tdldlt_index from reservation;
drop index resdl_index from reservation;
drop index resdl_tdl_index from reservation;
create unique index res_index on reservation (BID, PERS_ID, DLG_ID,
 DL_ID, TEIL, KAT_ID, DLT_ID, KONT_ID, A_ZEIT, E_ZEIT);
create index resbch_index on reservation (BID);
create index resbch_dl_index on reservation (BID, DLG_ID);
create index resbch_persdl_index on reservation (BID, PERS_ID, DLG_ID);
create index resbch_pt_index on reservation (BID, PERS_ID, TEIL);
create index resbch_pdt_index on reservation (BID, PERS_ID,
 TEIL, DLG_ID);
create index respers_index on reservation (PERS_ID);
create index respers_tdldlt_index on reservation (PERS_ID, DL_ID, DLT_ID);
create index resdl_index on reservation (DLG_ID);
create index resdl_tdl_index on reservation (DLG_ID, DL_ID);

/* PREIS Tabelle */
drop index prekar_index from preis;
drop index pre_index from preis;
drop index preall_index from preis;
drop index prekun_index from preis;
drop index preglt_index from preis;
drop index prekarkat_index from preis;
drop index prekarkatrkr_index from preis;
drop index prekardla_index from preis;
drop index prekarkatdla_index from preis;
drop index prekarkatrkrdla from preis;
drop index prekardl_index from preis;
drop index prekarkatdl_index from preis;
drop index prekarkatrkrdl from preis;
drop index prekat_index from preis;
drop index predltt_index from preis;
drop index prerkr_index from preis;
drop index predla_index from preis;
drop index predl_index from preis;
drop index prekont_index from preis;
create clustering index prekar_index on preis (KAR_ID);
create unique index pre_index on preis (PRE_ID);
create unique index preall_index on preis 
	(KAR_ID, DLTT_ID, KAT_ID, RKR_ID, DLA_ID, DL_ID, DL_VONDAT, DL_BISDAT,
	 KONT_ID, GLT);
create index prekun_index on preis (KBST);
create index preglt_index on preis (GLT);
create index prekarkat_index on preis (KAR_ID, KAT_ID);
create index prekarkatrkr_index on preis (KAR_ID, KAT_ID, RKR_ID);
create index prekardla_index on preis (KAR_ID, DLA_ID);
create index prekarkatdla_index on preis (KAR_ID, KAT_ID, DLA_ID);
create index prekarkatrkrdla on preis (KAR_ID, KAT_ID, RKR_ID, DLA_ID);
create index prekardl_index on preis (KAR_ID, DL_ID);
create index prekarkatdl_index on preis (KAR_ID, KAT_ID, DL_ID);
create index prekarkatrkrdl on preis (KAR_ID, KAT_ID, RKR_ID, DL_ID);
create index prekat_index on preis (KAT_ID);
create index predltt_index on preis (DLTT_ID);
create index prerkr_index on preis (RKR_ID);
create index predla_index on preis (DLA_ID);
create index predl_index on preis (DL_ID);
create index prekont_index on preis (KONT_ID);

/* KAPAZITAETEN Tabelle */
drop index kapa_index from kapa;
drop index kapakat_index from kapa;
drop index kapatdl_index from kapa;
create unique index kapa_index on kapa (KAT_ID, TDL_ID);
create index kapakat_index on kapa (KAT_ID);
create index kapatdl_index on kapa (TDL_ID);


/********************************************************/
/* GRAFIK - PIXELBILDER                                 */
/********************************************************/

/* GRAPHIK Tabelle */
drop index gra_index from graphik;
drop index grabez_index from graphik;
drop index gradlt_index from graphik;
create unique index gra_index on graphik (GRA_ID);
create unique index grabez_index on graphik (BEZ_ID);
create unique index gradlt_index on graphik (DLT_ID);

/* GRAFORM Tabelle */
drop index graform_gra_index from graform;
drop index graform_index from graform;
create clustering index graform_gra_index on graform (GRA_ID);
create unique index graform_index on graform (GRA_ID, FORMNR);

/* REGIONS Tabelle */
drop index reg_host_index from regions;
drop index reg_index from regions;
drop index regdlt_index from regions;
create clustering index reg_host_index on regions (HOST_ID);
create unique index reg_index on regions (HOST_ID, H_DLT_ID, DLT_ID, FOLGE);
create index regdlt_index on regions (HOST_ID, H_DLT_ID, DLT_ID);

/* PCX-FILES Tabelle */
drop index pcx_index from pcx_files;
drop index pcxbez_index from pcx_files;
drop index pcxtyp_index from pcx_files;
drop index pcxtypcode_index from pcx_files;
create unique index pcx_index on pcx_files (PCX_ID);
create unique index pcxbez_index on pcx_files (BEZ_ID);
create index pcxtyp_index on pcx_files (TYP);
create index pcxtypcode_index on pcx_files (TYP, TYPCODE);
