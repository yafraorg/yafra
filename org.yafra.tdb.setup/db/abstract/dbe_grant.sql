/*D************************************************************/
/* project:   travelDB                                        */
/*                                                            */
/*            create groups for grant and make grants         */
/*                                                            */
/* copyright: yafra.org, 2003, Switzerland                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/dbe_grant.sql,v 1.3 2004-01-26 21:03:24 mwn Exp $ */

/* there are three groups here:      */
/* mpuser for _SECLEVEL_USER         */
/* mpbooker for _SECLEVEL_BOOKING   */
/* mpreadonly for _SECLEVEL_READONLY */

/* users are assigned in file DBE_grantuser */

/**************************************************************/
/* group for security level USER                              */
/**************************************************************/

/* CODE tables */
revoke all privileges on tdbadmin.maxima from public;
grant select, insert, update, delete on tdbadmin.MAXIMA to mpuser;
grant select, insert, update, delete on tdbadmin.MAXIMA to mpbooker;
grant select, insert, update, delete on tdbadmin.MAXIMA to mpreadonly;

revoke all privileges on tdbadmin.sprachen from public;
grant select, update on tdbadmin.SPRACHEN to mpuser;
grant select on tdbadmin.SPRACHEN to mpbooker;
grant select on tdbadmin.SPRACHEN to mpreadonly;

revoke all privileges on tdbadmin.status_werte from public;
grant select, insert, update, delete on tdbadmin.STATUS_WERTE to mpuser;
grant select on tdbadmin.STATUS_WERTE to mpbooker;
grant select on tdbadmin.STATUS_WERTE to mpreadonly;

revoke all privileges on tdbadmin.bezeichnung from public;
grant select, insert, update, delete on tdbadmin.BEZEICHNUNG to mpuser;
grant select, insert, update, delete on tdbadmin.BEZEICHNUNG to mpbooker;
grant select on tdbadmin.BEZEICHNUNG to mpreadonly;

revoke all privileges on tdbadmin.tmp_bezeichnung from public;
grant select, insert, update, delete on tdbadmin.TMP_BEZEICHNUNG to mpuser;
grant select, insert, update, delete on tdbadmin.TMP_BEZEICHNUNG to mpbooker;
grant select on tdbadmin.TMP_BEZEICHNUNG to mpreadonly;

revoke all privileges on tdbadmin.texte from public;
grant select, insert, update, delete on tdbadmin.TEXTE to mpuser;
grant select, insert, update, delete on tdbadmin.TEXTE to mpbooker;
grant select on tdbadmin.TEXTE to mpreadonly;

revoke all privileges on tdbadmin.tmp_texte from public;
grant select, insert, update, delete on tdbadmin.TMP_TEXTE to mpuser;
grant select, insert, update, delete on tdbadmin.TMP_TEXTE to mpbooker;
grant select on tdbadmin.TMP_TEXTE to mpreadonly;

revoke all privileges on tdbadmin.MP_TEXTE from public;
grant select, insert, update, delete on tdbadmin.MP_TEXTE to mpuser;
grant select, insert, update, delete on tdbadmin.MP_TEXTE to mpbooker;
grant select on tdbadmin.MP_TEXTE to mpreadonly;

revoke all privileges on tdbadmin.MP_MULTIMEDIA from public;
grant select, insert, update, delete on tdbadmin.MP_MULTIMEDIA to mpuser;
grant select, insert, update, delete on tdbadmin.MP_MULTIMEDIA to mpbooker;
grant select on tdbadmin.MP_MULTIMEDIA to mpreadonly;

revoke all privileges on tdbadmin.MP_TEXT_DOC from public;
grant select, insert, update, delete on tdbadmin.MP_TEXT_DOC to mpuser;
grant select, insert, update, delete on tdbadmin.MP_TEXT_DOC to mpbooker;
grant select on tdbadmin.MP_TEXT_DOC to mpreadonly;

revoke all privileges on tdbadmin.aktionstexte from public;
grant select, insert, update, delete on tdbadmin.AKTIONSTEXTE to mpuser;
grant select on tdbadmin.AKTIONSTEXTE to mpbooker;
grant select on tdbadmin.AKTIONSTEXTE to mpreadonly;

revoke all privileges on tdbadmin.history from public;
grant select, insert, update, delete on tdbadmin.HISTORY to mpuser;
grant select, insert, update, delete on tdbadmin.HISTORY to mpbooker;
grant select, insert on tdbadmin.HISTORY to mpreadonly;

revoke all privileges on tdbadmin.help from public;
grant select, update on tdbadmin.HELP to mpuser;
grant select on tdbadmin.HELP to mpbooker;
grant select on tdbadmin.HELP to mpreadonly;

revoke all privileges on tdbadmin.msg from public;
grant select, update on tdbadmin.MSG to mpuser;
grant select on tdbadmin.MSG to mpbooker;
grant select on tdbadmin.MSG to mpreadonly;

revoke all privileges on tdbadmin.label from public;
grant select, update on tdbadmin.LABEL to mpuser;
grant select on tdbadmin.LABEL to mpbooker;
grant select on tdbadmin.LABEL to mpreadonly;

revoke all privileges on tdbadmin.MP_LABEL from public;
grant select, update on tdbadmin.MP_LABEL to mpuser;
grant select on tdbadmin.MP_LABEL to mpbooker;
grant select on tdbadmin.MP_LABEL to mpreadonly;

revoke all privileges on tdbadmin.saison from public;
grant select, insert, update, delete on tdbadmin.SAISON to mpuser;
grant select  on tdbadmin.SAISON to mpbooker;
grant select on tdbadmin.SAISON to mpreadonly;


/* GEOGRAFIE tables */
revoke all privileges on tdbadmin.waehrung from public;
grant select, insert, update, delete on tdbadmin.WAEHRUNG to mpuser;
grant select on tdbadmin.WAEHRUNG to mpbooker;
grant select on tdbadmin.WAEHRUNG to mpreadonly;

revoke all privileges on tdbadmin.land from public;
grant select, insert, update, delete on tdbadmin.LAND to mpuser;
grant select, insert  on tdbadmin.LAND to mpbooker;
grant select on tdbadmin.LAND to mpreadonly;

revoke all privileges on tdbadmin.ort from public;
grant select, insert, update, delete on tdbadmin.ORT to mpuser;
grant select, insert on tdbadmin.ORT to mpbooker;
grant select on tdbadmin.ORT to mpreadonly;

revoke all privileges on tdbadmin.MP_PROX from public;
grant select, insert, update, delete on tdbadmin.MP_PROX to mpuser;
grant select, insert on tdbadmin.MP_PROX to mpbooker;
grant select on tdbadmin.MP_PROX to mpreadonly;

revoke all privileges on tdbadmin.land_whr from public;
grant select, insert, update, delete on tdbadmin.LAND_WHR to mpuser;
grant select, insert on tdbadmin.LAND_WHR to mpbooker;
grant select on tdbadmin.LAND_WHR to mpreadonly;

revoke all privileges on tdbadmin.land_spr from public;
grant select, insert, update, delete on tdbadmin.LAND_SPR to mpuser;
grant select  on tdbadmin.LAND_SPR to mpbooker;
grant select on tdbadmin.LAND_SPR to mpreadonly;


/* PERSONEN tables */
revoke all privileges on tdbadmin.personen from public;
grant select, insert, update, delete on tdbadmin.PERSONEN to mpuser;
grant select, insert, update on tdbadmin.PERSONEN to mpbooker;
grant select on tdbadmin.PERSONEN to mpreadonly;

revoke all privileges on tdbadmin.persadr from public;
grant select, insert, update, delete on tdbadmin.PERSADR to mpuser;
grant select, insert, update on tdbadmin.PERSADR to mpbooker;
grant select on tdbadmin.PERSADR to mpreadonly;

revoke all privileges on tdbadmin.reisender_typ from public;
grant select, insert, update, delete on tdbadmin.REISENDER_TYP to mpuser;
grant select on tdbadmin.REISENDER_TYP to mpbooker;
grant select on tdbadmin.REISENDER_TYP to mpreadonly;

revoke all privileges on tdbadmin.reisender from public;
grant select, insert, update, delete on tdbadmin.REISENDER to mpuser;
grant select, insert, update on tdbadmin.REISENDER to mpbooker;
grant select on tdbadmin.REISENDER to mpreadonly;

revoke all privileges on tdbadmin.kunden_typ from public;
grant select, insert, update, delete on tdbadmin.KUNDEN_TYP to mpuser;
grant select on tdbadmin.KUNDEN_TYP to mpbooker;
grant select on tdbadmin.KUNDEN_TYP to mpreadonly;

revoke all privileges on tdbadmin.kunden from public;
grant select, insert, update, delete on tdbadmin.KUNDEN to mpuser;
grant select, insert, update on tdbadmin.KUNDEN to mpbooker;
grant select on tdbadmin.KUNDEN to mpreadonly;

revoke all privileges on tdbadmin.kollektiv_typ from public;
grant select, insert, update, delete on tdbadmin.KOLLEKTIV_TYP to mpuser;
grant select on tdbadmin.KOLLEKTIV_TYP to mpbooker;
grant select on tdbadmin.KOLLEKTIV_TYP to mpreadonly;

revoke all privileges on tdbadmin.kollektiv from public;
grant select, insert, update, delete on tdbadmin.KOLLEKTIV to mpuser;
grant select, insert, update         on tdbadmin.KOLLEKTIV to mpbooker;
grant select on tdbadmin.KOLLEKTIV to mpreadonly;


/* RESERVATIONSKERN Stammdaten tables */
revoke all privileges on tdbadmin.traeger_typ from public;
grant select, insert, update, delete on tdbadmin.TRAEGER_TYP to mpuser;
grant select on tdbadmin.TRAEGER_TYP to mpbooker;
grant select on tdbadmin.TRAEGER_TYP to mpreadonly;

revoke all privileges on tdbadmin.kategorie from public;
grant select, insert, update, delete on tdbadmin.KATEGORIE to mpuser;
grant select on tdbadmin.KATEGORIE to mpbooker;
grant select on tdbadmin.KATEGORIE to mpreadonly;

revoke all privileges on tdbadmin.dienst_traeger from public;
grant select, insert, update, delete on tdbadmin.DIENST_TRAEGER to mpuser;
grant select on tdbadmin.DIENST_TRAEGER to mpbooker;
grant select on tdbadmin.DIENST_TRAEGER to mpreadonly;

revoke all privileges on tdbadmin.traeger_detail from public;
grant select, insert, update, delete on tdbadmin.TRAEGER_DETAIL to mpuser;
grant select, update on tdbadmin.TRAEGER_DETAIL to mpbooker;
grant select  on tdbadmin.TRAEGER_DETAIL to mpreadonly;

revoke all privileges on tdbadmin.angebots_typ from public;
grant select, insert, update, delete on tdbadmin.ANGEBOTS_TYP to mpuser;
grant select on tdbadmin.ANGEBOTS_TYP to mpbooker;
grant select on tdbadmin.ANGEBOTS_TYP to mpreadonly;

revoke all privileges on tdbadmin.aktions_typ from public;
grant select, insert, update, delete on tdbadmin.AKTIONS_TYP to mpuser;
grant select  on tdbadmin.AKTIONS_TYP to mpbooker;
grant select on tdbadmin.AKTIONS_TYP to mpreadonly;

revoke all privileges on tdbadmin.aktionspara from public;
grant select, insert, update, delete on tdbadmin.AKTIONSPARA to mpuser;
grant select on tdbadmin.AKTIONSPARA to mpbooker;
grant select on tdbadmin.AKTIONSPARA to mpreadonly;

revoke all privileges on tdbadmin.MP_FILE from public;
grant select, insert, update, delete on tdbadmin.MP_FILE to mpuser;
grant select  on tdbadmin.MP_FILE to mpbooker;
grant select on tdbadmin.MP_FILE to mpreadonly;

revoke all privileges on tdbadmin.MP_PARAM from public;
grant select, insert, update, delete on tdbadmin.MP_PARAM to mpuser;
grant select  on tdbadmin.MP_PARAM to mpbooker;
grant select on tdbadmin.MP_PARAM to mpreadonly;

revoke all privileges on tdbadmin.aktionen from public;
grant select, insert, update, delete on tdbadmin.AKTIONEN to mpuser;
grant select on tdbadmin.AKTIONEN to mpbooker;
grant select on tdbadmin.AKTIONEN to mpreadonly;

revoke all privileges on tdbadmin.aktionsgrp from public;
grant select, insert, update, delete on tdbadmin.AKTIONSGRP to mpuser;
grant select on tdbadmin.AKTIONSGRP to mpbooker;
grant select on tdbadmin.AKTIONSGRP to mpreadonly;

revoke all privileges on tdbadmin.dienst_angebot from public;
grant select, insert, update, delete on tdbadmin.DIENST_ANGEBOT to mpuser;
grant select  on tdbadmin.DIENST_ANGEBOT to mpbooker;
grant select on tdbadmin.DIENST_ANGEBOT to mpreadonly;

revoke all privileges on tdbadmin.dlg_parts from public;
grant select, insert, update, delete on tdbadmin.DLG_PARTS to mpuser;
grant select  on tdbadmin.DLG_PARTS to mpbooker;
grant select on tdbadmin.DLG_PARTS to mpreadonly;

revoke all privileges on tdbadmin.dienstleistung from public;
grant select, insert, update, delete on tdbadmin.DIENSTLEISTUNG to mpuser;
grant select  on tdbadmin.DIENSTLEISTUNG to mpbooker;
grant select on tdbadmin.DIENSTLEISTUNG to mpreadonly;

revoke all privileges on tdbadmin.dlg_dlg from public;
grant select, insert, update, delete on tdbadmin.DLG_DLG to mpuser;
grant select on tdbadmin.DLG_DLG to mpbooker;
grant select on tdbadmin.DLG_DLG to mpreadonly;

revoke all privileges on tdbadmin.programm from public;
grant select, insert, update, delete on tdbadmin.PROGRAMM to mpuser;
grant select  on tdbadmin.PROGRAMM to mpbooker;
grant select on tdbadmin.PROGRAMM to mpreadonly;

revoke all privileges on tdbadmin.arrangement from public;
grant select, insert, update, delete on tdbadmin.ARRANGEMENT to mpuser;
grant select on tdbadmin.ARRANGEMENT to mpbooker;
grant select on tdbadmin.ARRANGEMENT to mpreadonly;

revoke all privileges on tdbadmin.arr_dlg from public;
grant select, insert, update, delete on tdbadmin.ARR_DLG to mpuser;
grant select  on tdbadmin.ARR_DLG to mpbooker;
grant select  on tdbadmin.ARR_DLG to mpreadonly;


/* KONTINGENT tables */
revoke all privileges on tdbadmin.host_kont from public;
grant select, insert, update, delete on tdbadmin.HOST_KONT to mpuser;
grant select  on tdbadmin.HOST_KONT to mpbooker;
grant select  on tdbadmin.HOST_KONT to mpreadonly;

revoke all privileges on tdbadmin.kontingent from public;
grant select, insert, update, delete on tdbadmin.KONTINGENT to mpuser;
grant select  on tdbadmin.KONTINGENT to mpbooker;
grant select on tdbadmin.KONTINGENT to mpreadonly;

revoke all privileges on tdbadmin.kont_detail from public;
grant select, insert, update, delete on tdbadmin.KONT_DETAIL to mpuser;
grant select, update (BUSY) on tdbadmin.KONT_DETAIL to mpbooker;
grant select on tdbadmin.KONT_DETAIL to mpreadonly;


/* MP_PROFIL table */
revoke all privileges on tdbadmin.mp_profil from public;
grant select, 
update (S_ID, LAND_ID, DLTT_ID, DLT_ID, KAT_ID, DLAT_ID, DLNT_ID, SAI_ID, 
PRG_ID, A_ZEIT, E_ZEIT, P_RANGE)  
on tdbadmin.MP_PROFIL to mpuser;
grant select, 
update (S_ID, LAND_ID, DLTT_ID, DLT_ID, KAT_ID, DLAT_ID, DLNT_ID, 
SAI_ID, PRG_ID, A_ZEIT, E_ZEIT, P_RANGE)  
on tdbadmin.MP_PROFIL to mpbooker;
grant select on tdbadmin.MP_PROFIL to mpreadonly;

revoke all privileges on tdbadmin.MP_PREFERENCES from public;
grant select, insert, update on tdbadmin.MP_PREFERENCES to mpuser;
grant select, insert, update on tdbadmin.MP_PREFERENCES to mpbooker;
grant select on tdbadmin.MP_PREFERENCES to mpreadonly;


/* RESERVATION tables */
revoke all privileges on tdbadmin.buchung from public;
grant select, insert, update, delete on tdbadmin.BUCHUNG to mpuser;
grant select, insert, update, delete on tdbadmin.BUCHUNG to mpbooker;
grant select on tdbadmin.BUCHUNG to mpreadonly;

revoke all privileges on tdbadmin.bch_dln from public;
grant select, insert, update, delete on tdbadmin.BCH_DLN to mpuser;
grant select, insert, update, delete on tdbadmin.BCH_DLN to mpbooker;
grant select on tdbadmin.BCH_DLN to mpreadonly;

revoke all privileges on tdbadmin.akt_detail from public;
grant select, insert, update, delete on tdbadmin.AKT_DETAIL to mpuser;
grant select, insert, update, delete on tdbadmin.AKT_DETAIL to mpbooker;
grant select on tdbadmin.AKT_DETAIL to mpreadonly;

revoke all privileges on tdbadmin.kosten_art from public;
grant select, insert, update, delete on tdbadmin.KOSTEN_ART to mpuser;
grant select on tdbadmin.KOSTEN_ART to mpbooker;
grant select on tdbadmin.KOSTEN_ART to mpreadonly;

revoke all privileges on tdbadmin.kommission from public;
grant select, insert, update, delete on tdbadmin.KOMMISSION to mpuser;
grant select on tdbadmin.KOMMISSION to mpbooker;
grant select on tdbadmin.KOMMISSION to mpreadonly;

revoke all privileges on tdbadmin.komm_detail from public;
grant select, insert, update, delete on tdbadmin.KOMM_DETAIL to mpuser;
grant select, insert, update, delete on tdbadmin.KOMM_DETAIL to mpbooker;
grant select on tdbadmin.KOMM_DETAIL to mpreadonly;

revoke all privileges on tdbadmin.reservation from public;
grant select, insert, update, delete on tdbadmin.RESERVATION to mpuser;
grant select, insert, update, delete on tdbadmin.RESERVATION to mpbooker;
grant select on tdbadmin.RESERVATION to mpreadonly;

revoke all privileges on tdbadmin.preis from public;
grant select, insert, update, delete on tdbadmin.PREIS to mpuser;
grant select on tdbadmin.PREIS to mpbooker;
grant select on tdbadmin.PREIS to mpreadonly;

revoke all privileges on tdbadmin.kapa from public;
grant select, insert, update, delete on tdbadmin.KAPA to mpuser;
grant select, insert, update, delete on tdbadmin.KAPA to mpbooker;
grant select on tdbadmin.KAPA to mpreadonly;

revoke all privileges on tdbadmin.mp_arrkom from public;
grant select, insert, update, delete on tdbadmin.MP_ARRKOM to mpuser;
grant select, insert, update, delete on tdbadmin.MP_ARRKOM to mpbooker;
grant select on tdbadmin.MP_ARRKOM to mpreadonly;

revoke all privileges on tdbadmin.MP_DEBITOR from public;
grant select, insert, update, delete on tdbadmin.MP_DEBITOR to mpuser;
grant select on tdbadmin.MP_DEBITOR to mpbooker;
grant select on tdbadmin.MP_DEBITOR to mpreadonly;

revoke all privileges on tdbadmin.MP_KREDITOR from public;
grant select, insert, update, delete on tdbadmin.MP_KREDITOR to mpuser;
grant select on tdbadmin.MP_KREDITOR to mpbooker;
grant select on tdbadmin.MP_KREDITOR to mpreadonly;

/* GRAFIK tables */
revoke all privileges on tdbadmin.graphik from public;
grant select, insert, update, delete on tdbadmin.GRAPHIK to mpuser;
grant select on tdbadmin.GRAPHIK to mpbooker;
grant select on tdbadmin.GRAPHIK to mpreadonly;

revoke all privileges on tdbadmin.graform from public;
grant select, insert, update, delete on tdbadmin.GRAFORM to mpuser;
grant select on tdbadmin.GRAFORM to mpbooker;
grant select on tdbadmin.GRAFORM to mpreadonly;

revoke all privileges on tdbadmin.regions from public;
grant select, insert, update, delete on tdbadmin.REGIONS to mpuser;
grant select on tdbadmin.REGIONS to mpbooker;
grant select on tdbadmin.REGIONS to mpreadonly;

revoke all privileges on tdbadmin.pcx_files from public;
grant select, insert, update, delete on tdbadmin.PCX_FILES to mpuser;
grant select on tdbadmin.PCX_FILES to mpbooker;
grant select on tdbadmin.PCX_FILES to mpreadonly;


/* VIEWS */
grant select on tdbadmin.SPR_VIEW to mpuser;
grant select on tdbadmin.SPR_VIEW to mpbooker;
grant select on tdbadmin.SPR_VIEW to mpreadonly;

grant select on tdbadmin.STA_VIEW to mpuser;
grant select on tdbadmin.STA_VIEW to mpbooker;
grant select on tdbadmin.STA_VIEW to mpreadonly;

grant select on tdbadmin.SAI_VIEW to mpuser;
grant select on tdbadmin.SAI_VIEW to mpbooker;
grant select on tdbadmin.SAI_VIEW to mpreadonly;

grant select on tdbadmin.LAND_VIEW to mpuser;
grant select on tdbadmin.LAND_VIEW to mpbooker;
grant select on tdbadmin.LAND_VIEW to mpreadonly;

grant select on tdbadmin.KUNDEN_VIEW to mpuser;
grant select on tdbadmin.KUNDEN_VIEW to mpbooker;
grant select on tdbadmin.KUNDEN_VIEW to mpreadonly;

grant select on tdbadmin.DLN_VIEW to mpuser;
grant select on tdbadmin.DLN_VIEW to mpbooker;
grant select on tdbadmin.DLN_VIEW to mpreadonly;

grant select on tdbadmin.RKR_VIEW to mpuser;
grant select on tdbadmin.RKR_VIEW to mpbooker;
grant select on tdbadmin.RKR_VIEW to mpreadonly;

grant select on tdbadmin.TTYP_VIEW to mpuser;
grant select on tdbadmin.TTYP_VIEW to mpbooker;
grant select on tdbadmin.TTYP_VIEW to mpreadonly;

grant select on tdbadmin.KAT_VIEW to mpuser;
grant select on tdbadmin.KAT_VIEW to mpbooker;
grant select on tdbadmin.KAT_VIEW to mpreadonly;

grant select on tdbadmin.TRAEGER_VIEW to mpuser;
grant select on tdbadmin.TRAEGER_VIEW to mpbooker;
grant select on tdbadmin.TRAEGER_VIEW to mpreadonly;

grant select on tdbadmin.DLT_VIEW to mpuser;
grant select on tdbadmin.DLT_VIEW to mpbooker;
grant select on tdbadmin.DLT_VIEW to mpreadonly;

grant select on tdbadmin.AKT_VIEW to mpuser;
grant select on tdbadmin.AKT_VIEW to mpbooker;
grant select on tdbadmin.AKT_VIEW to mpreadonly;

grant select on tdbadmin.DLA_VIEW to mpuser;
grant select on tdbadmin.DLA_VIEW to mpbooker;
grant select on tdbadmin.DLA_VIEW to mpreadonly;

grant select on tdbadmin.DLG_VIEW to mpuser;
grant select on tdbadmin.DLG_VIEW to mpbooker;
grant select on tdbadmin.DLG_VIEW to mpreadonly;

grant select on tdbadmin.DTG_VIEW to mpuser;
grant select on tdbadmin.DTG_VIEW to mpbooker;
grant select on tdbadmin.DTG_VIEW to mpreadonly;

grant select on tdbadmin.DL_DLG_VIEW to mpuser;
grant select on tdbadmin.DL_DLG_VIEW to mpbooker;
grant select on tdbadmin.DL_DLG_VIEW to mpreadonly;

grant select on tdbadmin.ARR_VIEW to mpuser;
grant select on tdbadmin.ARR_VIEW to mpbooker;
grant select on tdbadmin.ARR_VIEW to mpreadonly;

grant select on tdbadmin.ARR_DL_VIEW to mpuser;
grant select on tdbadmin.ARR_DL_VIEW to mpbooker;
grant select on tdbadmin.ARR_DL_VIEW to mpreadonly;

grant select on tdbadmin.ARR_DLG_VIEW to mpuser;
grant select on tdbadmin.ARR_DLG_VIEW to mpbooker;
grant select on tdbadmin.ARR_DLG_VIEW to mpreadonly;

grant select on tdbadmin.KON_VIEW to mpuser;
grant select on tdbadmin.KON_VIEW to mpbooker;
grant select on tdbadmin.KON_VIEW to mpreadonly;

grant select on tdbadmin.KONCHECK_VIEW to mpuser;
grant select on tdbadmin.KONCHECK_VIEW to mpbooker;
grant select on tdbadmin.KONCHECK_VIEW to mpreadonly;

grant select on tdbadmin.AKT_DETAIL_VIEW to mpuser;
grant select on tdbadmin.AKT_DETAIL_VIEW to mpbooker;
grant select on tdbadmin.AKT_DETAIL_VIEW to mpreadonly;

grant select on tdbadmin.KAR_VIEW to mpuser;
grant select on tdbadmin.KAR_VIEW to mpbooker;
grant select on tdbadmin.KAR_VIEW to mpreadonly;

grant select on tdbadmin.GRA_VIEW to mpuser;
grant select on tdbadmin.GRA_VIEW to mpbooker;
grant select on tdbadmin.GRA_VIEW to mpreadonly;

grant select on tdbadmin.ROUTEN_VIEW to mpuser;
grant select on tdbadmin.ROUTEN_VIEW to mpbooker;
grant select on tdbadmin.ROUTEN_VIEW to mpreadonly;

grant select on tdbadmin.RES_DL_VIEW to mpuser;
grant select on tdbadmin.RES_DL_VIEW to mpbooker;
grant select on tdbadmin.RES_DL_VIEW to mpreadonly;

grant select on tdbadmin.RESDL_VIEW to mpuser;
grant select on tdbadmin.RESDL_VIEW to mpbooker;
grant select on tdbadmin.RESDL_VIEW to mpreadonly;

grant select on tdbadmin.RESDLN_VIEW to mpuser;
grant select on tdbadmin.RESDLN_VIEW to mpbooker;
grant select on tdbadmin.RESDLN_VIEW to mpreadonly;

grant select on tdbadmin.MPV_DLNADR to mpuser;
grant select on tdbadmin.MPV_DLNADR to mpbooker;
grant select on tdbadmin.MPV_DLNADR to mpreadonly;

grant select on tdbadmin.MPV_KUNADR to mpuser;
grant select on tdbadmin.MPV_KUNADR to mpbooker;
grant select on tdbadmin.MPV_KUNADR to mpreadonly;

grant select on tdbadmin.MPV_KAPA to mpuser;
grant select on tdbadmin.MPV_KAPA to mpbooker;
grant select on tdbadmin.MPV_KAPA to mpreadonly;

grant select on tdbadmin.MPV_AKT to mpuser;
grant select on tdbadmin.MPV_AKT to mpbooker;
grant select on tdbadmin.MPV_AKT to mpreadonly;

grant select  on tdbadmin.MPV_AKT_DETAIL to mpuser;
grant select  on tdbadmin.MPV_AKT_DETAIL to mpbooker;
grant select  on tdbadmin.MPV_AKT_DETAIL to mpreadonly;

grant select on tdbadmin.MPV_ANGEBOT to mpuser;
grant select on tdbadmin.MPV_ANGEBOT to mpbooker;
grant select on tdbadmin.MPV_ANGEBOT to mpreadonly;

grant select on tdbadmin.MPV_ARR to mpuser;
grant select on tdbadmin.MPV_ARR to mpbooker;
grant select on tdbadmin.MPV_ARR to mpreadonly;

grant select on tdbadmin.MPV_ARR_DL to mpuser;
grant select on tdbadmin.MPV_ARR_DL to mpbooker;
grant select on tdbadmin.MPV_ARR_DL to mpreadonly;

grant select on tdbadmin.MPV_ARR_DLG to mpuser;
grant select on tdbadmin.MPV_ARR_DLG to mpbooker;
grant select on tdbadmin.MPV_ARR_DLG to mpreadonly;

grant select on tdbadmin.MPV_DL to mpuser;
grant select on tdbadmin.MPV_DL to mpbooker;
grant select on tdbadmin.MPV_DL to mpreadonly;

grant select on tdbadmin.MPV_DLA to mpuser;
grant select on tdbadmin.MPV_DLA to mpbooker;
grant select on tdbadmin.MPV_DLA to mpreadonly;

grant select on tdbadmin.MPV_DLN to mpuser;
grant select on tdbadmin.MPV_DLN to mpbooker;
grant select on tdbadmin.MPV_DLN to mpreadonly;

grant select on tdbadmin.MPV_DLT to mpuser;
grant select on tdbadmin.MPV_DLT to mpbooker;
grant select on tdbadmin.MPV_DLT to mpreadonly;

grant select on tdbadmin.MPV_DL_TDL to mpuser;
grant select on tdbadmin.MPV_DL_TDL to mpbooker;
grant select on tdbadmin.MPV_DL_TDL to mpreadonly;

grant select on tdbadmin.MPV_GRA to mpuser;
grant select on tdbadmin.MPV_GRA to mpbooker;
grant select on tdbadmin.MPV_GRA to mpreadonly;

grant select on tdbadmin.MPV_KAPADET to mpuser;
grant select on tdbadmin.MPV_KAPADET to mpbooker;
grant select on tdbadmin.MPV_KAPADET to mpreadonly;

grant select on tdbadmin.MPV_KAR to mpuser;
grant select on tdbadmin.MPV_KAR to mpbooker;
grant select on tdbadmin.MPV_KAR to mpreadonly;

grant select on tdbadmin.MPV_KAT to mpuser;
grant select on tdbadmin.MPV_KAT to mpbooker;
grant select on tdbadmin.MPV_KAT to mpreadonly;
                        
grant select on tdbadmin.MPV_KON to mpuser;
grant select on tdbadmin.MPV_KON to mpbooker;
grant select on tdbadmin.MPV_KON to mpreadonly;
                        
grant select on tdbadmin.MPV_KONCHECK to mpuser;
grant select on tdbadmin.MPV_KONCHECK to mpbooker;
grant select on tdbadmin.MPV_KONCHECK to mpreadonly;

grant select on tdbadmin.MPV_KUNDEN to mpuser;
grant select on tdbadmin.MPV_KUNDEN to mpbooker;
grant select on tdbadmin.MPV_KUNDEN to mpreadonly;

grant select on tdbadmin.MPV_LAND to mpuser;
grant select on tdbadmin.MPV_LAND to mpbooker;
grant select on tdbadmin.MPV_LAND to mpreadonly;

grant select on tdbadmin.MPV_LW to mpuser;
grant select on tdbadmin.MPV_LW to mpbooker;
grant select on tdbadmin.MPV_LW to mpreadonly;

grant select on tdbadmin.MPV_ORT to mpuser;
grant select on tdbadmin.MPV_ORT to mpbooker;
grant select on tdbadmin.MPV_ORT to mpreadonly;

grant select on tdbadmin.MPV_PRG to mpuser;
grant select on tdbadmin.MPV_PRG to mpbooker;
grant select on tdbadmin.MPV_PRG to mpreadonly;

grant select on tdbadmin.MPV_RESDL to mpuser;
grant select on tdbadmin.MPV_RESDL to mpbooker;
grant select on tdbadmin.MPV_RESDL to mpreadonly;

grant select on tdbadmin.MPV_RESDLN to mpuser;
grant select on tdbadmin.MPV_RESDLN to mpbooker;
grant select on tdbadmin.MPV_RESDLN to mpreadonly;

grant select on tdbadmin.MPV_RES_DL to mpuser;
grant select on tdbadmin.MPV_RES_DL to mpbooker;
grant select on tdbadmin.MPV_PRG to mpreadonly;

grant select on tdbadmin.MPV_RKR to mpuser;
grant select on tdbadmin.MPV_RKR to mpbooker;
grant select on tdbadmin.MPV_RKR to mpreadonly;

grant select on tdbadmin.MPV_ROUTEN to mpuser;
grant select on tdbadmin.MPV_ROUTEN to mpbooker;
grant select on tdbadmin.MPV_ROUTEN to mpreadonly;

grant select on tdbadmin.MPV_SAIDET to mpuser;
grant select on tdbadmin.MPV_SAIDET to mpbooker;
grant select on tdbadmin.MPV_SAIDET to mpreadonly;

grant select on tdbadmin.MPV_SAISON to mpuser;
grant select on tdbadmin.MPV_SAISON to mpbooker;
grant select on tdbadmin.MPV_SAISON to mpreadonly;

grant select on tdbadmin.MPV_SPRACHE to mpuser;
grant select on tdbadmin.MPV_SPRACHE to mpbooker;
grant select on tdbadmin.MPV_SPRACHE to mpreadonly;

grant select on tdbadmin.MPV_STATUS to mpuser;
grant select on tdbadmin.MPV_STATUS to mpbooker;
grant select on tdbadmin.MPV_STATUS to mpreadonly;

/*
grant select on tdbadmin.MPV_USERS to mpuser;
grant select on tdbadmin.MPV_USERS to mpbooker;
grant select on tdbadmin.MPV_USERS to mpreadonly;
*/

grant select on tdbadmin.MPV_TDL to mpuser;
grant select on tdbadmin.MPV_TDL to mpbooker;
grant select on tdbadmin.MPV_TDL to mpreadonly;

grant select on tdbadmin.MPV_TRAEGER to mpuser;
grant select on tdbadmin.MPV_TRAEGER to mpbooker;
grant select on tdbadmin.MPV_TRAEGER to mpreadonly;

grant select on tdbadmin.MPV_TTYP to mpuser;
grant select on tdbadmin.MPV_TTYP to mpbooker;
grant select on tdbadmin.MPV_TTYP to mpreadonly;

grant select on tdbadmin.MPV_WHR to mpuser;
grant select on tdbadmin.MPV_WHR to mpbooker;
grant select on tdbadmin.MPV_WHR to mpreadonly;

/*
grant select on tdbadmin.mpcc_preferences to mpuser;
grant select on tdbadmin.mpcc_preferences to mpbooker;
grant select on tdbadmin.mpcc_preferences to mpreadonly;

grant select on tdbadmin.mp2000_dienstleistung to mpuser;
grant select on tdbadmin.mp2000_dienstleistung to mpbooker;
grant select on tdbadmin.mp2000_dienstleistung to mpreadonly;

grant select on tdbadmin.mp2000_arrangement to mpuser;
grant select on tdbadmin.mp2000_arrangement  to mpbooker;
grant select on tdbadmin.mp2000_arrangement  to mpreadonly;
*/

grant select on tdbadmin.mp2000_kunden to mpuser;
grant select on tdbadmin.mp2000_kunden  to mpbooker;
grant select on tdbadmin.mp2000_kunden  to mpreadonly;

grant select on tdbadmin.mpv_buchung to mpuser;
grant select on tdbadmin.mpv_buchung to mpbooker;
grant select on tdbadmin.mpv_buchung to mpreadonly;

/*
grant select on tdbadmin.mpv_reisender to mpuser;
grant select on tdbadmin.mpv_reisender to mpbooker;
grant select on tdbadmin.mpv_reisender to mpreadonly;

grant select on tdbadmin.mpv_reservation  to mpuser;
grant select on tdbadmin.mpv_reservation  to mpbooker;
grant select on tdbadmin.mpv_reservation to mpreadonly;
*/