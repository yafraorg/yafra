/*D************************************************************/
/* project:   MARCO POLO                                      */
/*                                                            */
/* DBMS:      Oracle                                          */
/*            JAVA views                                      */
/*                                                            */
/* copyright: yafra.org, 2004, Switzerland                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvstdbadmin/mapo/db/mysql/dbe_javaviews.sql,v 1.1 2008-11-23 15:37:05 mwn Exp $ */

set echo off;
set autocommit off;

/***************************************************************************/
/*                                                                         */
/*  N E W     V I E W S   used by     M P    B O O K E R    2 0 0 0        */
/*                                                                         */
/***************************************************************************/

/* view used to read cctypes of table mp_preferences */
CREATE OR REPLACE VIEW "TDBADMIN"."MPCC_PREFERENCES" AS select mpid, fullname
  , nvl(to_number(rtrim(tdbadmin.getcctype('isReseller:',custom), CHR(13))),1) reseller
  , nvl(to_number(rtrim(tdbadmin.getcctype('useContingent:',custom),  CHR(13))),1) contingent
  , nvl(to_number(rtrim(tdbadmin.getcctype('corporateCurrency:',custom), CHR(13))),-1) corp_currency
  , nvl(to_number(rtrim(tdbadmin.getcctype('exchangeCountry:',custom),  CHR(13))),-1) ex_country
  , nvl(to_number(rtrim(tdbadmin.getcctype('dataLanguage:',gui),  CHR(13))),1) data_lang
  , nvl(to_number(rtrim(tdbadmin.getcctype('statusInGuiLanguage:',gui),  CHR(13))),0) status_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('languagesInGuiLanguage:',gui), CHR(13))),0) languages_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('countriesInGuiLanguage:',gui),  CHR(13))),0) countries_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('currenciesInGuiLanguage:',gui),  CHR(13))),0) currencies_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('travelerTypeInGuiLanguage:',gui),  CHR(13))),0) travelertype_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('canOverbookCarrier:',custom),  CHR(13))),0) overbook_igl
  , nvl(to_number(rtrim(tdbadmin.getcctype('onlySeeFreeCarrier:',custom),  CHR(13))),0) freecarrier_igl
  from tdbadmin.mp_preferences;

/* view used to search a service by season, starting or arrival place, date or offre type */
CREATE OR REPLACE VIEW MP2000_DIENSTLEISTUNG 
AS SELECT
myd.DLG_ID, d.BEZ_ID, a.VON, a.NACH,
myd.RES_F ZEIT_TYP,
myd.A_ZEIT, myd.E_ZEIT,
d.SAI_ID,
myd.DL_ID H_DL_ID,
a.DLA_ID, a.DLT_ID,
a.ART_ID TYP_ID,
todate(myd.A_ZEIT) A_DZEIT, todate(myd.E_ZEIT) E_DZEIT,
d.code CODE
FROM tdbadmin.dienstleistung d, tdbadmin.dienst_angebot a,
(SELECT UNIQUE dd.DLG_ID, hp.DL_ID, hp.RES_F, 
 hp.A_ZEIT, hp.E_ZEIT, hp.DLA_ID
 FROM tdbadmin.dlg_parts p1, tdbadmin.dlg_parts hp, tdbadmin.dlg_dlg dd
WHERE dd.DLG_ID > 0
AND dd.DL_ID = p1.DL_ID
AND hp.DL_ID = decode(p1.H_DL_ID,-1, p1.DL_ID,p1.H_DL_ID)) myd
WHERE d.DLG_ID = myd.DLG_ID
AND a.DLA_ID = myd.DLA_ID;

commit;

/* view used to search a arrangement by season, starting or arrival place, date or catalog */
create or replace view MP2000_ARRANGEMENT (ARR_ID, BEZ_ID, VON, NACH, A_ZEIT, E_ZEIT, SAI_ID, PRG_ID) AS
SELECT UNIQUE a.ARR_ID, a.BEZ_ID, ao.VON, eo.NACH, a.A_DAT, ez.E_ZEIT, a.SAI_ID, a.PRG_ID
FROM 	arrangement a,
	( SELECT ad1.ARR_ID, d1.VON
	  FROM arr_dlg ad1, mp2000_dienstleistung d1
	  WHERE ad1.dlg_id = d1.DLG_ID
	  AND (( ad1.teil IN (SELECT min(teil) 
		   	     FROM arr_dlg ad2, mp2000_dienstleistung d2 
		   	     WHERE ad2.arr_id = ad1.arr_id
		   	     AND d2.VON <> -1
		   	     AND   ad2.dlg_id = d2.DLG_ID
			     AND   ad1.PRIO IN (SELECT min(PRIO)
			    			FROM arr_dlg ad3
			    			WHERE ad3.arr_id = ad2.arr_id)) )
	    OR ( ad1.teil IN (SELECT min(teil) 
		   	     FROM arr_dlg ad2, mp2000_dienstleistung d2 
		   	     WHERE ad2.arr_id = ad1.arr_id
		   	     AND   ad2.dlg_id = d2.DLG_ID
			     AND   ad1.PRIO IN (SELECT min(PRIO)
			    			FROM arr_dlg ad3
			    			WHERE ad3.arr_id = ad2.arr_id)) ))) ao,
	( SELECT UNIQUE ad1.ARR_ID, d1.NACH
	  FROM arr_dlg ad1, mp2000_dienstleistung d1
	  WHERE ad1.dlg_id = d1.DLG_ID
	  AND ((ad1.teil IN (SELECT max(teil) 
		   	     FROM  arr_dlg ad2, mp2000_dienstleistung d2 
		   	     WHERE ad2.arr_id = ad1.arr_id
		   	     AND d2.NACH <> -1
		   	     AND ad2.dlg_id = d2.DLG_ID
			     AND   ad2.PRIO  IN (SELECT min(PRIO)
			      			 FROM arr_dlg ad3
			      			 WHERE ad3.arr_id = ad2.arr_id)) )
	     OR ( ad1.teil IN (SELECT max(teil)
			     FROM arr_dlg ad2, mp2000_dienstleistung d2
			     WHERE ad2.arr_id = ad1.arr_id
		   	     AND ad2.dlg_id = d2.DLG_ID
			     AND ad2.PRIO  IN   (SELECT min(PRIO)
			      			 FROM arr_dlg ad3
			      			 WHERE ad3.arr_id = ad2.arr_id))  ))) eo,
	( SELECT UNIQUE ad1.ARR_ID, d1.E_ZEIT
	 FROM arr_dlg ad1, mp2000_dienstleistung d1
	 WHERE ad1.dlg_id = d1.DLG_ID
	 AND  ((ad1.teil IN (SELECT max(teil) 
		   	    FROM arr_dlg ad2, mp2000_dienstleistung d2 
		   	    WHERE ad2.arr_id = ad1.arr_id
		   	    AND	d2.E_ZEIT > 0
		   	    AND ad2.dlg_id = d2.DLG_ID
			    AND   ad1.PRIO IN  (SELECT min(PRIO)
			    			FROM arr_dlg ad3
			    			WHERE ad3.arr_id = ad1.arr_id)) )
	   OR ( ad1.teil IN (SELECT max(teil) 
		   	    FROM arr_dlg ad2, mp2000_dienstleistung d2 
		   	    WHERE ad2.arr_id = ad1.arr_id
		   	    AND ad2.dlg_id = d2.DLG_ID
			    AND   ad1.PRIO IN  (SELECT min(PRIO)
			    			FROM arr_dlg ad3
			    			WHERE ad3.arr_id = ad1.arr_id)) ))) ez
WHERE a.ARR_ID = ao.ARR_ID
AND   a.ARR_ID = eo.ARR_ID
AND   a.ARR_ID = ez.ARR_ID;




/* view used to help Oracle Report */

create or replace view mpv_buchung as
select b.D_BID, b.BID, b.REF, b.ARR_ID, b.KID,
b.SACH, p.BCHST, b.ANW, todate(b.B_DAT) B_DAT, todate(b.M_DAT) M_DAT,
b.M_DAT MAPO_DAT,
b.OPT_BST MAPO_OPT_BST,
todate(b.OPT_BST) OPT_BST, 
b.OPT_KID MAPO_OPT_KID, 
todate(b.OPT_KID) OPT_KID,
b.STA, b.AST, b.SAI_ID,
b.K_ID, b.HISTORY, b.TEXTID
from buchung b, mp_profil p
where b.ANW = p.MPID;

create or replace view mpv_reisender as
select reisender.PERS_ID, reisender.VOR, personen.NAME,
(RTrim(personen.NAME)||' '||reisender.VOR) complete_name,
reisender.RKR_ID, reisender.SEX, reisender.TEXTID EXT_TXT,
persadr.LAND_ID, reisender.AGE, reisender.PASSNR,
reisender.ATTR1, reisender.ATTR2, personen.PERS_TYP,
persadr.ORT, personen.S_ID, personen.STA_ID, personen.TEXTID
from
reisender, personen, persadr
where
reisender.PERS_ID=personen.PERS_ID
and personen.PERS_ID = persadr.PERS_ID and persadr.haupt_flag = 1;

create or replace view mpv_reservation as
select 
PERS_ID, DLG_ID, DL_ID, TEIL, DLT_ID, TYP_ID, BID, KONT_ID, KAT_ID, K_KON,
B_KON, R_STA, SAI_ID, A_ZEIT mapo_AZEIT, todate(A_ZEIT) A_ZEIT, 
E_ZEIT mapo_EZEIT, todate(E_ZEIT) E_ZEIT, TEXTID
from tdbadmin.reservation;


CREATE OR REPLACE VIEW MPV_KONTINGENT AS select  
kontin.kont_id,  
hostk.hostkont_id,  
kontin.bez kontingent,  
hostk.bez hostkontingent,  
hkd.kat_id,  
hkkat.bez kategory,  
kd.anz kont_anz,  
kd.busy kont_busy,  
hkd.anz host_anz,  
hkd.busy host_busy  
from  
(select  
kon.*, bez.bez  
from  
tdbadmin.host_kont kon,  
tdbadmin.bezeichnung bez  
where bez.typ = 38  
and bez.bez_id = kon.bez_id  
and bez.s_id=25) hostk,  
(select  
kon.*, bez.bez  
from  
tdbadmin.kontingent kon,  
tdbadmin.bezeichnung bez  
where bez.typ = 39  
and bez.bez_id = kon.bez_id  
and bez.s_id=25) kontin,  
tdbadmin.kont_detail kd,  
tdbadmin.kont_detail hkd,  
tdbadmin.mpv_kat hkkat  
where  
kontin.kont_id >0  
and kontin.hostkont_id=hostk.hostkont_id  
and kd.kont_id=kontin.kont_id  
and hkd.hostkont_id=hostk.hostkont_id  
and hkd.kat_id=hkkat.kat_id  
and hkkat.s_id=25  
and hkd.kont_id=-1  
and kd.kat_id=hkd.kat_id;


/* view specific to amexco for Oracle Report */
create or replace view amexcotexte (TEXTID, TYP, S_ID,
TEXT, SHAREWITH, COMPANY, CONFIRMATIONTO, TELEPHONE, FAX,
EMAIL, CCTYPE, CCHOLDER, CCNUMBER, CCVALID, TEAMREF) AS
select textid, typ, s_id, text,
getcctype('sharewith:',text),
getcctype('company:',text),
getcctype('confirmationto:',text),
getcctype('telephone:',text),
getcctype('fax:',text),
getcctype('email:',text),
getcctype('CCtype:',text),
getcctype('CCholder:',text),
getcctype('CCnumber:',text),
getcctype('CCvalid:',text),
getcctype('TEAMref:',text)
from tdbadmin.mp_texte;


CREATE OR REPLACE VIEW "TDBADMIN"."AMEXCOSYNCHTEAM" AS select prs.pers_id, dln2.bid,prs.name lastname,rsd.vor firstname,rsd.sex,pad.ans anrede,
to_number(ate.teamref) teamref,
ate.SHAREWITH, ate.COMPANY, ate.CONFIRMATIONTO, 
ate.TELEPHONE, ate.FAX, ate.EMAIL, ate.CCTYPE, 
ate.CCHOLDER, ate.CCNUMBER, ate.CCVALID,
decode(texte.textid,-1,null,texte.text) comments,
texte.textid commentsid
from
tdbadmin.amexcotexte ate,
tdbadmin.personen prs,
tdbadmin.persadr pad,
tdbadmin.reisender rsd,
tdbadmin.bch_dln dln2,
tdbadmin.mp_texte texte
where
prs.textid=ate.textid
and prs.pers_id=rsd.pers_id
and pad.pers_id=prs.pers_id
and pad.haupt_flag=1
and dln2.dln_id=prs.pers_id
AND rsd.TEXTID=texte.textid
AND texte.typ=36
AND texte.s_id=1;



CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_PREIS" AS (SELECT /*+ ordered */ --DISTINCT
-- reservation info
        r.BID, r.PERS_ID, rei.RKR_ID, r.TEIL, r.dlg_id, hp.DL_ID, r.r_sta, r.kat_id, r.kont_id, hp.kid, hp.res_f zeittyp, hp.a_zeit, hp.e_zeit, hp.dla_id,
-- price
				p.PRE_ID 					preis_id, p.WHR_ID local_whr_id, p.VPR local_preis, p.APR local_cost,
        whrland.land_id 	whr_land_id,        whrland.haupt_whr whr_id,
        round(p.VPR*plw.v_kurs,2) 	whr_preis, round(p.APR*plw.v_kurs,2) whr_cost,
        plw.land_id lwchg_id,
-- reductions on travel
				nvl(dla_red.komm_id, -1) dla_red_id, nvl(dla_red.satz, 0) dla_red,
				nvl(dlg_red.komm_id, -1) dlg_red_id, nvl(dlg_red.satz, 0) dlg_red,
				nvl(kont_red.komm_id, -1) kont_red_id, nvl(kont_red.satz, 0) kont_red,
				round(p.VPR*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100),2) red_price,
-- reductions on folder
				nvl(kun_red.komm_id, -1) kun_red_id, nvl(kun_red.satz, 0) kun_red,
				nvl(kol_red.komm_id, -1) kol_red_id, nvl(kol_red.satz, 0) kol_red,
				nvl(bid_red.komm_id, -1) bid_red_id, nvl(bid_red.satz, 0) bid_red,
				round(p.VPR*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100)
												*(1-nvl(kun_red.satz, 0)/100)
												*(1-nvl(kol_red.satz, 0)/100)
												*(1-nvl(bid_red.satz, 0)/100),2) whr_excl,
-- vat
				nvl(vat.KOMM_ID, -1)                             vat_id,
				landvat.LAND_ID                                  vat_land_id,
				decode(vat.KOMM_ID, null, landvat.vat, vat.SATZ) vat,
				round(p.VPR*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100)
												*(1-nvl(kun_red.satz, 0)/100)
												*(1-nvl(kol_red.satz, 0)/100)
												*(1-nvl(bid_red.satz, 0)/100)
												*(1+decode(vat.KOMM_ID, null, landvat.vat, vat.SATZ)/100),2) whr_inkl
FROM
		 tdbadmin.reservation r, tdbadmin.dlg_dlg dd, tdbadmin.dlg_parts dp, tdbadmin.dlg_parts hp, tdbadmin.dienst_angebot a,
		 tdbadmin.reisender rei,tdbadmin.preis p,
		 tdbadmin.kommission dla_red, tdbadmin.kommission dlg_red, tdbadmin.kommission kont_red,
		 tdbadmin.kommission kun_red, tdbadmin.komm_detail kun_det,
		 tdbadmin.kommission kol_red, tdbadmin.komm_detail kol_det,
		 tdbadmin.kommission bid_red,
		 tdbadmin.land_whr plw, tdbadmin.land whrland, tdbadmin.land landvat, tdbadmin.kommission vat
-- get dl_id, dla_id
WHERE r.R_STA <> 20000
AND r.dlg_id = dd.DLG_ID
AND dd.DL_ID = dp.DL_ID
AND ((hp.DL_ID = dp.H_DL_ID AND dp.H_DL_ID<>-1)
    OR (hp.DL_ID = dp.DL_ID AND dp.H_DL_ID=-1))
AND hp.DLA_ID = a.DLA_ID
-- get traveler type
AND rei.PERS_ID = r.PERS_ID
-- get price
AND (p.RKR_ID = rei.RKR_ID OR p.RKR_ID = -1)
AND (p.KAT_ID = r.KAT_ID OR p.KAT_ID = -1)
AND (p.DL_ID  = hp.DL_ID OR p.DLA_ID = a.DLA_ID)
AND p.GLT =(SELECT max(allp.GLT)
			      FROM tdbadmin.preis allp
			      WHERE(allp.RKR_ID = rei.RKR_ID OR allp.RKR_ID = -1)
						AND (allp.KAT_ID = r.KAT_ID OR allp.KAT_ID = -1)
						AND (allp.DL_ID = hp.DL_ID OR allp.DLA_ID = a.DLA_ID)
						AND  allp.GLT <= hp.A_ZEIT )
-- get reduction
AND dla_red.komm_typ(+) = 1 AND dla_red.satz_art(+) = 1 AND hp.dla_id = dla_red.dla_id(+)
AND dlg_red.komm_typ(+) = 2   AND dlg_red.satz_art(+) = 1 AND r.dlg_id = dlg_red.dl_id(+)
AND kont_red.komm_typ(+) = 3	AND kont_red.satz_art(+) = 1 AND  r.kont_id = kont_red.kont_id(+)
AND kun_red.komm_typ(+) = 5 AND kun_red.satz_art(+) = 1
								AND kun_det.komm_id = kun_red.komm_id (+) AND kun_det.bid(+) = r.bid
AND kol_red.komm_typ(+) = 6 AND kol_red.satz_art(+) = 1
								AND kol_det.komm_id = kol_red.komm_id (+) AND kol_det.bid (+)= r.bid
AND bid_red.komm_typ (+)= 7  AND bid_red.satz_art (+)= 1  AND r.bid = bid_red.bid(+)
-- get change rate
AND p.WHR_ID = plw.WHR_ID AND plw.kurs_typ = 2
AND plw.LAND_ID = whrland.land_id
AND plw.VON_DAT = (SELECT nvl(max(VON_DAT),-1)
			 						FROM tdbadmin.land_whr
			 						WHERE kurs_typ = plw.kurs_typ
			 						AND land_id    = plw.land_id
			 						AND WHR_ID     = plw.WHR_ID )
-- get vat
	AND vat.DLA_ID(+) 	= hp.DLA_ID AND vat.KOMM_TYP(+) = 4 AND vat.SATZ_ART(+) = 1
-- make an union to have fix reductions on same folder (join done at view call)
) UNION (SELECT /*+ ordered */
-- reservation info
        red.BID, -1 PERS_ID, -1 rkr_id, 1 TEIL, -1 dlg_id, -1 dl_id, 11000 r_sta, -1 kat_id, -1 kont_id, -1 kid, -1 zeittyp, -1 a_zeit, -1 e_zeit, -1 dla_id,
-- price
				-1 preis_id, -1 local_whr_id, -red.satz local_preis, 0 local_cost,
        whrland.land_id whr_land_id,  whrland.haupt_whr whr_id, -red.satz whr_preis, 0 whr_cost,
        -1 lwchg_id,
-- reductions on travel
				-1 dla_red_id, 0 dla_red,
				-1 dlg_red_id, 0 dlg_red,
				-1 kont_red_id, 0 kont_red,
				-red.satz red_price,
-- reductions on folder
				-1 kun_red_id, 0 kun_red,
				-1 kol_red_id, 0 kol_red,
				-1 bid_red_id, 0 bid_red,
				-red.satz whr_excl,
-- vat
				-1 vat_id,
				landvat.LAND_ID vat_land_id,
				landvat.vat vat,
				-red.satz*(1+landvat.vat/100) whr_inkl
FROM
		tdbadmin.kommission red, tdbadmin.land whrland,   tdbadmin.land landvat
WHERE
		red.satz_art = 2	AND red.komm_typ = 8
);

/*************************************************************************/
/* views for reports                                                     */
/*************************************************************************/
CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8F" AS select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
RTRIM(dl1.code) fullcode,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
nach_ort_bez.bez nachort
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte,
tdbadmin.dienst_angebot dla,
tdbadmin.bezeichnung dlabez,
tdbadmin.mpv_angebot angebottyp,
tdbadmin.ort von_ort,
tdbadmin.bezeichnung von_ort_bez,
tdbadmin.ort nach_ort,
tdbadmin.bezeichnung nach_ort_bez
where
reser.r_sta=2000
AND reser.kont_id=-1
AND rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25
AND dla.dla_id=dlgp.dla_id
AND dlabez.typ = 23
AND dlabez.bez_id = dla.bez_id
AND dlabez.s_id = 25
AND dla.art_id=angebottyp.art_id
AND angebottyp.s_id=25
AND von_ort.ort_id=dla.von
AND von_ort_bez.bez_id=von_ort.bez_id
AND von_ort_bez.typ=11
AND von_ort_bez.s_id=25
AND nach_ort.ort_id=dla.nach
AND nach_ort_bez.bez_id=nach_ort.bez_id
AND nach_ort_bez.typ=11
AND nach_ort_bez.s_id=25;


CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8C" AS select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
tdbadmin.getprice(buch.bid,rsd.PERS_ID,reser.teil) price,
reser.teil,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name)
name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.email,
amxt.confirmationto,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
amxt.company dcomp,
amxt.fax dfax,
amxt.CONFIRMATIONTO dattn,
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
nach_ort_bez.bez nachort
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte,
tdbadmin.dienst_angebot dla,
tdbadmin.bezeichnung dlabez,
tdbadmin.mpv_angebot angebottyp,
tdbadmin.ort von_ort,
tdbadmin.bezeichnung von_ort_bez,
tdbadmin.ort nach_ort,
tdbadmin.bezeichnung nach_ort_bez
where
reser.r_sta=9000
AND von_ort.ort_id=dla.von
AND von_ort_bez.bez_id=von_ort.bez_id
AND von_ort_bez.typ=11
AND von_ort_bez.s_id=25
AND nach_ort.ort_id=dla.nach
AND nach_ort_bez.bez_id=nach_ort.bez_id
AND nach_ort_bez.typ=11
AND nach_ort_bez.s_id=25
AND rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND kat.s_id=25
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND
dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND saison.s_id=25
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25
AND dla.dla_id=dlgp.dla_id
AND dlabez.typ = 23
AND dlabez.bez_id = dla.bez_id
AND dlabez.s_id = 25
AND dla.art_id=angebottyp.art_id
AND angebottyp.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT9A" AS select
buch.ref buchung,
buch.bid,
dlgp.kid hotelid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
reser.kont_id,
kat.bez kategory,
bezk.bez KONTINGENT, 
bezhk.bez HOSTKONTINGENT,
hostk.hostkont_id,
hkd.kat_id,
kd.anz kont_anz,
kd.busy kont_busy,
hkd.anz host_anz,
hkd.busy host_busy,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.mpv_saison saison,
tdbadmin.host_kont hostk,
tdbadmin.kontingent kontin,
tdbadmin.kont_detail kd,
tdbadmin.kont_detail hkd,
bezeichnung bezk,
bezeichnung bezhk
where
reser.kont_id>-1
and reser.r_sta<20000
AND rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND kontin.hostkont_id=hostk.hostkont_id
and kd.kont_id=kontin.kont_id
and hkd.hostkont_id=hostk.hostkont_id
and hkd.kont_id=-1
and kd.kat_id=hkd.kat_id
and kontin.kont_id=reser.kont_id
and kd.kat_id=reser.kat_id
and	bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25
and	bezhk.typ = 38 and bezhk.bez_id = hostk.bez_id and bezhk.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8D" AS select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
reser.r_sta,
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
RTRIM(dl1.code) fullcode,
nach_ort_bez.bez nachort
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte,
tdbadmin.dienst_angebot dla,
tdbadmin.bezeichnung dlabez,
tdbadmin.mpv_angebot angebottyp,
tdbadmin.ort von_ort,
tdbadmin.bezeichnung von_ort_bez,
tdbadmin.ort nach_ort,
tdbadmin.bezeichnung nach_ort_bez
where
rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25
AND reser.kont_id>-1
AND reser.r_sta=3000
AND dla.dla_id=dlgp.dla_id
AND dlabez.typ = 23
AND dlabez.bez_id = dla.bez_id
AND dlabez.s_id = 25
AND dla.art_id=angebottyp.art_id
AND angebottyp.s_id=25
AND von_ort.ort_id=dla.von
AND von_ort_bez.bez_id=von_ort.bez_id
AND von_ort_bez.typ=11
AND von_ort_bez.s_id=25
AND nach_ort.ort_id=dla.nach
AND nach_ort_bez.bez_id=nach_ort.bez_id
AND nach_ort_bez.typ=11
AND nach_ort_bez.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8E" AS select
buch.ref buchung,
buch.bid bid,
kadr2.name destname,
kadr2.fax destfax,
RTRIM(saison.bez) saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name)
name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
reser.pers_id,
amxt.company,
amxt.teamref,
texte.textid noticeid,
texte.text notice,
SUBSTR(dl1.code,1,6) code,
RTRIM(dl1.code) grcode
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte
where
reser.r_sta<20000
AND rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND
dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8G" AS select
buch.ref buchung,
amxt.company,
amxt.teamref,
kadr2.name destname,
kadr2.fax destfax,
RTRIM(saison.bez) saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
buch.bid
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte
where
rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25
AND (reser.r_sta=10001 OR reser.r_sta=4001);

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8H" AS select
buch.ref buchung,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
RTRIM(kadr.name) hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
RTRIM(kadr.ort)  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
dl1.a_dzeit ci_date, 
dl1.e_dzeit co_date,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
reser.pers_id,
dl1.code code,
reser.r_sta,
statusbez.bez status
from
tdbadmin.mpv_reservation reser,
tdbadmin.mpv_reisender rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.mp2000_dienstleistung dl1,
tdbadmin.mpv_dlt dlt,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
(select * from tdbadmin.bezeichnung
where (typ=1112 or typ=1108)
and s_id=25) statusbez
where
rsd.pers_id=reser.pers_id
AND reser.R_STA<20000
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dl1.dlg_id=reser.dlg_id
AND dl1.h_dl_id=dlgp.dl_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND dlt.dlt_id=dl1.dlt_id
AND rsd.textid=amxt.textid
AND dl1.sai_id=saison.sai_id
AND reser.R_STA=statusbez.bez_id;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT9D" AS select
reser.kont_id,
hostk.hostkont_id,
buch.ref buchung,
buch.bid,
bezk.bez KONTINGENT,
bezhk.bez HOSTKONTINGENT,
kat.bez kategory,
dlgp.kid hotelid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kat.kat_id,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
RTRIM(dl1.code) hotelcode,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.mpv_saison saison,
tdbadmin.host_kont hostk,
tdbadmin.kontingent kontin,
bezeichnung bezk,
bezeichnung bezhk
where
rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND kontin.hostkont_id=hostk.hostkont_id
and kontin.kont_id=reser.kont_id
and	bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25
and	bezhk.typ = 38 and bezhk.bez_id = hostk.bez_id and bezhk.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8I" AS select /*+ ordered*/
buch.ref buchung, buch.bid, preis.kid,
-- client
kadr2.name destname,kadr2.adr1 destadr,kadr2.plz destplz,kadr2.ort destort,kadr2.tel desttel,kadr2.fax destfax,
-- saison
saison.bez saison,
-- supplier
kadr.name hotelname,kadr.adr1 hoteladr,kadr.plz hotelplz,kadr.ort hotelort,kadr.tel hoteltel,kadr.fax hotelfax,
-- traveler
personen.pers_id pers_id,
DECODE(reisender.sex,2,'Mr ','Mrs ')||RTRIM(reisender.vor)||' '||RTRIM(personen.name) name,
amxt.cctype,amxt.ccnumber,amxt.ccvalid,amxt.sharewith,
amxt.company dcomp,amxt.fax dfax,amxt.CONFIRMATIONTO dattn,
texte.textid noticeid,texte.text notice,
-- dienstliestung
SUBSTR(dl1.code,1,6) code, RTRIM(dl1.code) fullcode,
dllbez.bez dienstleistung,
todate(preis.a_zeit) ci_date,todate(preis.e_zeit) co_date,
-- category
kat.bez kategory,
-- angebot
angebottyp.bez angebot,
dlabez.bez angt,
angebottyp.bez angebottyp, angebottyp.art_id angebottyp_id,
vonort.ort_id vonort_id,vonbez.bez vonort,
nachort.ort_id nachort_id, nachbez.bez nachort,
-- preis
preis.whr_excl price,preis.whr_inkl pricetaxed,to_char(preis.vat,'90.9')||' %' tax, w.krzl whr,
w.whr_id,
preis.whr_land_id,
preis.vat_land_id
from
tdbadmin.buchung buch
,tdbadmin.mp2000_preis preis
-- category
,tdbadmin.mpv_kat kat
-- angebot, angebotstyp, �rte
,tdbadmin.dienst_angebot dla, tdbadmin.bezeichnung dlabez, tdbadmin.mpv_angebot angebottyp
, tdbadmin.waehrung w
,tdbadmin.ort vonort, tdbadmin.bezeichnung vonbez, tdbadmin.ort nachort, tdbadmin.bezeichnung nachbez
-- dienstliestung, saison
,tdbadmin.dienstleistung dl1, tdbadmin.bezeichnung dllbez, tdbadmin.mpv_saison saison
-- traveler
, tdbadmin.personen personen, tdbadmin.amexcotexte amxt, tdbadmin.reisender reisender, tdbadmin.mp_texte texte
-- supplier
,tdbadmin.mpv_kunadr kadr
-- client
, tdbadmin.mpv_kunadr kadr2
where
-- price change land and vat land
preis.whr_id = w.whr_id
AND preis.r_sta =11000
-- dienstliestung, saison
AND preis.dlg_id = dl1.dlg_id AND dl1.bez_id = dllbez.bez_id AND dllbez.TYP=27
AND dl1.sai_id = saison.sai_id
-- angebot, angebotstyp, �rte
AND preis.dla_id=dla.dla_id AND dlabez.bez_id=dla.bez_id AND dlabez.typ=23 AND dlabez.s_id=25
AND dla.art_id=angebottyp.art_id AND angebottyp.s_id=25
AND dla.von =vonort.ort_id  AND vonbez.bez_id =vonort.bez_id  AND vonbez.typ=11  AND vonbez.s_id=25
AND dla.nach=nachort.ort_id AND nachbez.bez_id=nachort.bez_id AND nachbez.typ=11 AND nachbez.s_id=25
-- traveler
AND preis.pers_id = personen.PERS_ID AND personen.PERS_ID= reisender.PERS_ID
AND personen.textid=amxt.textid AND amxt.typ=34 AND amxt.s_id=25
AND reisender.textid=texte.textid AND texte.typ=36 AND texte.s_id=25
-- client
AND preis.bid = buch.BID AND buch.kid = kadr2.pers_id
-- supplier
AND preis.kid = kadr.pers_id
-- category
AND preis.kat_id = kat.kat_id  ;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8J" AS select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
dllbez.bez dienstleistung,
reser.r_sta,
bezk.bez KONTINGENT,
stabez.bez status
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.mpv_saison saison,
tdbadmin.bezeichnung dllbez,
tdbadmin.bezeichnung stabez,
tdbadmin.kontingent kontin,
bezeichnung bezk
where
rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND dllbez.TYP=27
AND dllbez.bez_id=dl1.bez_id
AND dllbez.s_id=25
AND stabez.s_id=25
AND (stabez.typ=1112 or stabez.typ=1108)
AND stabez.bez_id=reser.r_sta
and kontin.kont_id=reser.kont_id
and bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT8K" AS select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
DECODE(rsd.sex,2,'Mr ','Mrs ')||RTRIM(rsd.vor)||' '||RTRIM(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
SUBSTR(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
reser.r_sta,
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
RTRIM(dl1.code) fullcode,
nach_ort_bez.bez nachort
from
tdbadmin.reservation reser,
(select reisender.PERS_ID, reisender.VOR, personen.NAME,
reisender.SEX, reisender.TEXTID EXT_TXT,
personen.STA_ID, personen.TEXTID
from
reisender, personen
where
reisender.PERS_ID=personen.PERS_ID) rsd,
tdbadmin.buchung buch,
tdbadmin.mpv_kat kat,
tdbadmin.dienstleistung dl1,
tdbadmin.dlg_parts dlp,
tdbadmin.mpv_kunadr kadr,
tdbadmin.mpv_kunadr kadr2,
tdbadmin.dlg_parts dlgp,
tdbadmin.dlg_dlg dlgdlg,
tdbadmin.amexcotexte amxt,
tdbadmin.mpv_saison saison,
tdbadmin.mp_texte texte,
tdbadmin.dienst_angebot dla,
tdbadmin.bezeichnung dlabez,
tdbadmin.mpv_angebot angebottyp,
tdbadmin.ort von_ort,
tdbadmin.bezeichnung von_ort_bez,
tdbadmin.ort nach_ort,
tdbadmin.bezeichnung nach_ort_bez
where
rsd.pers_id=reser.pers_id
AND kat.kat_id= reser.kat_id
AND buch.BID=reser.bid
AND dlgdlg.dlg_id=reser.dlg_id
AND dlp.dl_id=dlgdlg.dl_id
AND ( (dlp.h_dl_id=-1 AND dlgp.dl_id=dlp.dl_id) OR (dlp.h_dl_id>-1 AND dlgp.dl_id=dlp.h_dl_id) )
AND dl1.dlg_id=reser.dlg_id
AND dl1.sai_id=saison.sai_id
AND kadr.pers_id=dlgp.kid
AND kadr2.pers_id=buch.kid
AND rsd.textid=amxt.textid
AND amxt.typ=34
AND amxt.s_id=25
AND rsd.ext_txt=texte.textid
AND texte.typ=36
AND texte.s_id=25
AND reser.r_sta=8502
AND dla.dla_id=dlgp.dla_id
AND dlabez.typ = 23
AND dlabez.bez_id = dla.bez_id
AND dlabez.s_id = 1
AND dla.art_id=angebottyp.art_id
AND angebottyp.s_id=25
AND von_ort.ort_id=dla.von
AND von_ort_bez.bez_id=von_ort.bez_id
AND von_ort_bez.typ=11
AND von_ort_bez.s_id=25
AND nach_ort.ort_id=dla.nach
AND nach_ort_bez.bez_id=nach_ort.bez_id
AND nach_ort_bez.typ=11
AND nach_ort_bez.s_id=25;

CREATE OR REPLACE VIEW "TDBADMIN"."MP2000_REPORT9E" AS select 
deb.fakt_zeit,
deb.sta_id, 
stabez.bez bez, 
deb.nachsaldo, 
deb.whr_excl, 
deb.whr_inkl, 
deb.vat_id, 
deb.vat, 
vatbez.bez vatbez, 
deb.rst_gewinn, 
deb.whr_id, 
whr.krzl whrk, 
whrbez.bez whr,
deb.deb_id, 
deb.bid
from 
tdbadmin.mp_debitor deb,
tdbadmin.bezeichnung stabez,
tdbadmin.kommission komm,
tdbadmin.bezeichnung vatbez,
tdbadmin.bezeichnung whrbez,
tdbadmin.waehrung whr
where stabez.s_id=25
AND (stabez.typ=1112 or stabez.typ=1108)
and stabez.bez_id=deb.sta_id
and vatbez.s_id = 25
and vatbez.typ = 44
and komm.komm_id = deb.vat_id
and vatbez.bez_id = komm.bez_id
and whr.whr_id=deb.whr_id
and whrbez.s_id = 25
and whrbez.typ = 12
and whrbez.bez_id=whr.bez_id;

/***************************************************************************/
/* USERS                                                                  */
/***************************************************************************/
  
/* MPV_USERS */

create or replace view MPV_USERS (MPID, FULLNAME, MPUSER, BCHST, NAME, LAND_ID,
MPSID, LANDBEZ, LANDSID, SPRSID, SPRBEZ, SECLEVEL, RESELLER, CONTINGENT, 
CORP_CURRENCY, EX_COUNTRY, DATA_LANG, STATUS_IGL, LANGUAGES_IGL, COUNTRIES_IGL,
CURRENCIES_IGL, TRAVELERTYPE_IGL, OVERBOOK_IGL, FREECARRIER_IGL)
AS
select mp.mpid, mpp.fullname, mp.mpuser, mp.BCHST,
personen.name, mp.land_id, mp.s_id mpsid, b1.bez landbez,
b1.s_id landsid, b2.s_id sprsid, b2.bez sprbez, mp.SECLEVEL
, nvl(to_number(rtrim(tdbadmin.getcctype('isReseller:',custom), CHR(13))),1) reseller
, nvl(to_number(rtrim(tdbadmin.getcctype('useContingent:',custom),  CHR(13))),1) contingent
, nvl(to_number(rtrim(tdbadmin.getcctype('corporateCurrency:',custom), CHR(13))),-1) corp_currency
, nvl(to_number(rtrim(tdbadmin.getcctype('exchangeCountry:',custom),  CHR(13))),-1) ex_country
, nvl(to_number(rtrim(tdbadmin.getcctype('dataLanguage:',mpp.gui),  CHR(13))),1) data_lang
, nvl(to_number(rtrim(tdbadmin.getcctype('statusInGuiLanguage:',mpp.gui),  CHR(13))),0) status_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('languagesInGuiLanguage:',mpp.gui), CHR(13))),0) languages_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('countriesInGuiLanguage:',mpp.gui),  CHR(13))),0) countries_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('currenciesInGuiLanguage:',mpp.gui),  CHR(13))),0) currencies_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('travelerTypeInGuiLanguage:',mpp.gui),  CHR(13))),0) travelertype_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('canOverbookCarrier:',custom),  CHR(13))),0) overbook_igl
, nvl(to_number(rtrim(tdbadmin.getcctype('onlySeeFreeCarrier:',custom),  CHR(13))),0) freecarrier_igl
 from tdbadmin.mp_preferences mpp, tdbadmin.mp_profil mp, tdbadmin.personen,
 tdbadmin.sprachen, tdbadmin.land, tdbadmin.bezeichnung b1, tdbadmin.bezeichnung b2
  where mpp.mpid = mp.mpid
  and  mp.bchst=personen.pers_id
  and mp.land_id = land.land_id
  and land.bez_id = b1.bez_id
  and b1.typ = 10
  and mp.s_id = sprachen.s_id
  and sprachen.bez_id = b2.bez_id
  and b2.typ = 1
  and b1.s_id = b2.s_id;

/***************************************************************************/
/* MP2000KUNDEN                                                            */
/***************************************************************************/

/* CUSTOMER VIEW */
create or replace view MP2000_KUNDEN
AS
select distinct k.pers_id, p.name, pa.adr1, pa.plz, pa.ort,
b1.bez land, b2.bez sprache, k.attr1 code, b3.bez waehrung,
b4.bez versand, txt.text,txt.textid, b1.s_id,
k.tel,k.fax, k.email, k.web, k.konto, b5.bez typ
from kunden k,personen p,persadr pa,bezeichnung b1,land l,
bezeichnung b2,sprachen s,status_werte st,waehrung w,bezeichnung b3,
bezeichnung b4,mp_texte txt,kunden_typ ku,bezeichnung b5
where k.pers_id=p.pers_id
and k.pers_id=pa.pers_id
and k.pers_id<>-1
and p.s_id=b2.bez_id
and l.land_id=pa.land_id
and l.bez_id=b1.bez_id
and b1.typ=10
and s.bez_id=b2.bez_id
and b2.typ=1
and b2.bez_id>0
and p.sta_id=st.sta_id
and st.bez_id=b4.bez_id
and b4.typ=1111
and w.whr_id=k.whr_id
and w.bez_id=b3.bez_id
and b3.typ=12
and p.textid=txt.textid
and txt.typ=34
and k.k_typ_id=ku.k_typ_id
and ku.bez_id=b5.bez_id
and b5.bez_id>0
and b5.typ=24
and b1.s_id=b2.s_id
and b1.s_id=b3.s_id
and b1.s_id=b4.s_id
and b1.s_id=b5.s_id;



/* SAISON VIEW */
create or replace view MP2000_SAISON
AS
select distinct s.sai_id, s.bez_id, b.bez,s.code, s.von, s.bis, t.text, b.s_id
from saison s, bezeichnung b, mp_texte t
where s.bez_id = b.bez_id
and s.textid=t.textid
and t.typ=9
and b.typ=9
and b.bez_id>0;