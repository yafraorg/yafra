/*D************************************************************/
/* project:   travelDB NEW database views                     */
/*                                                            */
/*            ATTENTION !! types are hardcoded here !!!       */
/*            see tdb_tabletypes.xml                          */
/*                                                            */
/* copyright: yafra.org, Switzerland, 2004                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/dbe_tdbviews.sql,v 1.10 2008-12-23 21:59:44 mwn Exp $ */

/* check for mpstadef.h and mpobjdef.h for codes */

/* LANGUAGE */
drop view tdbv_langsel;
create view tdbv_langsel (S_ID, BEZ, SYSBEZ, BEZSPRID) as
select spr.s_id, bez.bez, spr.sysbez, bez.s_id
from 	sprachen spr, bezeichnung bez
where	spr.s_id > 0 and bez.typ = 1 and bez.bez_id = spr.bez_id;

drop view tdbv_lang;
create view tdbv_lang (S_ID, BEZ_ID, BEZ, SYSBEZ, DIALOG, OUTPUT, GUI, BEZSPRID) as
select spr.s_id, spr.bez_id, bez.bez, spr.sysbez, spr.dialog, spr.output, spr.gui, bez.s_id
from 	sprachen spr, bezeichnung bez
where	spr.s_id > 0 and bez.typ = 1 and bez.bez_id = spr.bez_id;

/* STATUS */
drop view tdbv_stasel;
create view tdbv_stasel (STA_ID, BEZ, CODE, S_ID, TYP) as
select sta.sta_id, bez.bez, sta.sta, bez.s_id, sta.typ
from 	status_werte sta, bezeichnung bez
where	sta.sta_id > -1 and bez.typ = sta.typ and bez.bez_id = sta.bez_id;

drop view tdbv_sta;
create view tdbv_sta (STA_ID, BEZ_ID, ABK, STA, BEZ, S_ID, KOND, TYP) as
select sta.sta_id, sta.bez_id, sta.abk, sta.sta, bez.bez, bez.s_id, sta.kond, sta.typ
from 	status_werte sta, bezeichnung bez
where	sta.sta_id > -1 and bez.typ = sta.typ and bez.bez_id = sta.bez_id;

/* SEASON */
drop view tdbv_saisel;
create view tdbv_saisel (SAI_ID, BEZ, CODE, S_ID) as
select sai.sai_id, bez.bez, sai.code, bez.s_id
from 	saison sai, bezeichnung bez
where	sai.sai_id > 0 and bez.typ = 9 and bez.bez_id = sai.bez_id;

drop view tdbv_sai;
create view tdbv_sai (SAI_ID, BEZ_ID, BEZ, CODE, VON, BIS, S_ID, TEXTID) as
select sai.sai_id, sai.bez_id, bez.bez, sai.code, todate(sai.von), todate(sai.bis), bez.s_id, sai.textid
from 	saison sai, bezeichnung bez
where	sai.sai_id > 0 and bez.typ = 9 and bez.bez_id = sai.bez_id;


/* COUNTRY  */
drop view tdbv_countrysel;
create view tdbv_countrysel (LAND_ID, BEZ, KRZL, S_ID) as
select land.land_id, bez.bez, land.krzl, bez.s_id
from 	land, bezeichnung bez
where	land.land_id > 0 and bez.typ = 10 and bez.bez_id = land.bez_id;

drop view tdbv_country;
create view tdbv_country (LAND_ID, BEZ_ID, BEZ, S_ID, KRZL, HAUPT_ORT,
 HAUPT_SPR, HAUPT_WHR, TEXTID, VAT, DATEFORMAT) as
select land.land_id, land.bez_id, bez.bez, bez.s_id, land.krzl, land.haupt_ort,
 land.haupt_spr, land.haupt_whr, land.textid, land.vat, land.dateformat
from 	land, bezeichnung bez
where	land.land_id > 0 and bez.typ = 10 and bez.bez_id = land.bez_id;

drop view tdbv_countryd;
create view tdbv_countryd (LAND_ID, BEZ_ID, BEZ, S_ID, KRZL, CAPITALID, CAPITAL,
 LANGID, LANG, CURID, CURRENCY, TEXTID, VAT, DATEFORMAT) as
select land.land_id, land.bez_id, bez.bez, bez.s_id, land.krzl, land.haupt_ort, ortbez.bez,
 land.haupt_spr, bezs.bez, land.haupt_whr, bezw.bez, land.textid, land.vat, land.dateformat
from 	land, bezeichnung bez, ort, bezeichnung ortbez, sprachen, bezeichnung bezs,
 waehrung whr, bezeichnung bezw
where	land.land_id > 0 and (bez.typ = 10 and bez.bez_id = land.bez_id)
and ((ort.ort_id = land.haupt_ort)
and (ortbez.typ = 11 and ortbez.bez_id = ort.bez_id))
and ((sprachen.s_id = land.haupt_spr)
and (bezs.typ = 1 and bezs.bez_id = sprachen.bez_id))
and ((whr.whr_id = land.haupt_whr)
and (bezw.typ = 12 and bezw.bez_id = whr.bez_id))
and bezs.s_id = bez.s_id and ortbez.s_id = bez.s_id and bezw.s_id = bez.s_id;

/* CITY  */
drop view tdbv_citysel;
create view tdbv_citysel (ORT_ID, BEZ, KRZL, S_ID) as
select ort.ort_id, bez.bez, ort.krzl, bez.s_id
from 	ort, bezeichnung bez
where	ort.ort_id > 0 and bez.typ = 11 and bez.bez_id = ort.bez_id;

drop view tdbv_city;
create view tdbv_city (ORT_ID, BEZ_ID, BEZ, S_ID, KRZL, LANDID, LANDBEZ, TEXTID, ZEITVER, KOORD1, KOORD2, TYPE) as
select ort.ort_id, ort.bez_id, bez.bez, bez.s_id, ort.krzl, ort.land_id, land.krzl,
 ort.textid, ort.zeitver, ort.koord1, ort.koord2, ort.ort_typ
from 	ort, land, bezeichnung bez, bezeichnung bezl
where	ort.ort_id > 0 and (bez.typ = 11 and bez.bez_id = ort.bez_id)
and ((land.land_id = ort.land_id)
and (bezl.typ = 10 and bezl.bez_id = land.bez_id and bezl.s_id = bez.s_id));

/* CURRENCY  */
drop view tdbv_cursel;
create view tdbv_cursel (WHR_ID, BEZ, KRZL, S_ID) as
select waehrung.whr_id, bez.bez, waehrung.krzl, bez.s_id
from 	waehrung, bezeichnung bez
where	waehrung.whr_id > 0 and bez.typ = 12 and bez.bez_id = waehrung.bez_id;

drop view tdbv_cur;
create view tdbv_cur (WHR_ID, BEZ_ID, BEZ, S_ID, KRZL, STATUS, TEXTID) as
select waehrung.whr_id, waehrung.bez_id, bez.bez, bez.s_id, waehrung.krzl, waehrung.status,
 waehrung.textid
from 	waehrung, bezeichnung bez
where	waehrung.whr_id > 0 and bez.typ = 12 and bez.bez_id = waehrung.bez_id;

/* EXCHANGE RATES  */
drop view tdbv_ratesel;
create view tdbv_ratesel (LAND_ID, LANDBEZ, WHR_ID, WHRBEZ, S_ID, KURS_TYP, A_KURS, V_KURS, FROMDAT) as
select lw.land_id, bezl.bez, lw.whr_id, bezw.bez, bezl.s_id, lw.kurs_typ, lw.a_kurs, lw.v_kurs, todate(lw.von_dat)
from 	land_whr lw, land, bezeichnung bezl, waehrung whr, bezeichnung bezw
where ((land.land_id = lw.land_id)
and (bezl.typ = 10 and bezl.bez_id = land.bez_id))
and bezw.s_id = bezl.s_id
and ((whr.whr_id = lw.whr_id)
and (bezw.typ = 12 and bezw.bez_id = whr.bez_id));

/* COUNTRY LANGUAGE  */
drop view tdbv_countrylang;
create view tdbv_countrylang (LAND_ID, LANDBEZ, CCODE, DATEFORMAT, S_ID, SBEZ, SCODE) as
select ls.land_id, bezl.bez, land.krzl, land.dateformat, ls.s_id, bezs.bez, lang.sysbez
from 	land_spr ls, land, bezeichnung bezl, sprachen lang, bezeichnung bezs
where	((land.land_id = ls.land_id)
and (bezl.typ = 10 and bezl.bez_id = land.bez_id))
and bezs.s_id = bezl.s_id
and ((lang.s_id = ls.s_id)
and (bezs.typ = 1 and bezs.bez_id = lang.bez_id));

/* USER PROFILE */
drop view tdbv_user;
create view tdbv_user (MPID, TDBUSER, BCHST, BCHSTID, SECLEVEL, LANG, S_ID, COUNTRY, LAND_ID,
 SUPTYPE, DLTT_ID, DLT, DLT_ID, KAT, KAT_ID, DLAT, DLAT_ID, DLNT, DLNT_ID, SEASON, SAI_ID,
 PRG, PRG_ID, STARTTIME, ENDTIME, PRANGE) as
select p.mpid, p.mpuser, pers.name, p.bchst, p.seclevel, bezs.bez, p.s_id, bezl.bez, p.land_id,
 beztt.bez, p.dltt_id, dlt.code, p.dlt_id, bezk.bez, p.kat_id, bezdlat.bez, p.dlat_id,
 rt.dlncode, p.dlnt_id, sai.code, p.sai_id, prg.code, p.prg_id, todate(p.a_zeit), todate(p.e_zeit), p.p_range
from mp_profil p, personen pers, sprachen s, bezeichnung bezs, land, bezeichnung bezl,
 traeger_typ tt, bezeichnung beztt, dienst_traeger dlt, kategorie k, bezeichnung bezk,
 angebots_typ dlat, bezeichnung bezdlat, reisender_typ rt, saison sai, programm prg
where	(pers.pers_id = p.bchst)
and ((s.s_id = p.s_id) and (bezs.typ = 1 and bezs.bez_id = s.bez_id))
and ((land.land_id = p.land_id) and (bezl.typ = 10 and bezl.bez_id = land.bez_id))
and ((tt.typ_id = p.dltt_id) and (beztt.typ = 15 and beztt.bez_id = tt.bez_id))
and (dlt.dlt_id = p.dlt_id)
and ((k.kat_id = p.kat_id) and (bezk.typ = 16 and bezk.bez_id = k.bez_id))
and ((dlat.art_id = p.dlat_id) and (bezdlat.typ = 18 and bezdlat.bez_id = dlat.bez_id))
and (rt.rkr_id = p.dlnt_id)
and (sai.sai_id = p.sai_id) and (prg.prg_id = p.prg_id)
and bezl.s_id = bezs.s_id and beztt.s_id = bezs.s_id and bezk.s_id = bezs.s_id and bezdlat.s_id = bezs.s_id;

/* PERSONTYPE  */
drop view tdbv_perstsel;
create view tdbv_perstsel (PERSTYPE_ID, BEZ, CODE, S_ID) as
select pt.rkr_id, bez.bez, pt.dlncode, bez.s_id
from 	reisender_typ pt, bezeichnung bez
where	pt.rkr_id > 0 and bez.typ = 35 and bez.bez_id = pt.bez_id;

drop view tdbv_perst;
create view tdbv_perst (PERSTYPE_ID, BEZ_ID, BEZ, S_ID, CODE, VONALTER, BISALTER, TEXTID) as
select pt.rkr_id, pt.bez_id, bez.bez, bez.s_id, pt.dlncode, pt.vonalter, pt.bisalter,
 pt.textid
from 	reisender_typ pt, bezeichnung bez
where	pt.rkr_id > 0 and bez.typ = 35 and bez.bez_id = pt.bez_id;

/* CUSTOMER TYPE  */
drop view tdbv_cuttsel;
create view tdbv_cuttsel (CUSTTYPE_ID, BEZ, CODE, S_ID) as
select kt.k_typ_id, bez.bez, kt.kuncode, bez.s_id
from 	kunden_typ kt, bezeichnung bez
where	kt.k_typ_id > 0 and bez.typ = 24 and bez.bez_id = kt.bez_id;

drop view tdbv_cutt;
create view tdbv_cutt (CUSTTYPE_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID) as
select kt.k_typ_id, kt.bez_id, bez.bez, bez.s_id, kt.kuncode, kt.textid
from 	kunden_typ kt, bezeichnung bez
where	kt.k_typ_id > 0 and bez.typ = 24 and bez.bez_id = kt.bez_id;

/* GROUP TYPE  */
drop view tdbv_grptsel;
create view tdbv_grptsel (GRPTYPE_ID, BEZ, CODE, S_ID) as
select kt.k_typ_id, bez.bez, kt.kolcode, bez.s_id
from 	kollektiv_typ kt, bezeichnung bez
where	kt.k_typ_id > 0 and bez.typ = 32 and bez.bez_id = kt.bez_id;

drop view tdbv_grpt;
create view tdbv_grpt (GRPTYPE_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID) as
select kt.k_typ_id, kt.bez_id, bez.bez, bez.s_id, kt.kolcode, kt.textid
from 	kollektiv_typ kt, bezeichnung bez
where	kt.k_typ_id > 0 and bez.typ = 32 and bez.bez_id = kt.bez_id;

/* Travelers PERS_TYP = 1*/
drop view tdbv_perssel;
create view tdbv_perssel (PERS_ID, FIRSTNAME, LASTNAME, SEX) as
select p.pers_id, r.vor, p.name, r.sex
from 	personen p, reisender r
where	p.pers_id > 0 and (r.pers_id = p.pers_id and p.pers_typ = 1);

drop view tdbv_pers;
create view tdbv_pers (PERS_ID, FIRSTNAME, LASTNAME, S_ID, STA_ID, TEXTID,
 PERSTYPEID, SEX, MUTTERSID, AGE, PASSPORT, ATTR1, ATTR2, RTEXTID) as
select p.pers_id, r.vor, p.name, p.s_id, p.sta_id, p.textid, r.rkr_id, r.sex,
 r.mutters_id, r.age, r.passnr, r.attr1, r.attr2, r.textid
from 	personen p, reisender r
where	p.pers_id > 0 and (r.pers_id = p.pers_id and p.pers_typ = 1);

drop view tdbv_persadr;
create view tdbv_persadr (PERS_ID, ANS, FIRSTNAME, LASTNAME, LANG, S_ID, PERSSTA, PERSSTAID,
 ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, LAND,
 TEXTID, PERSTYPE, PERSTYPEID, SEX, MUTTERSID, AGE, PASSPORT,
 ATTR1, ATTR2, RTEXTID, ADRTYP, ADRTYPID, ADRSTA, ADRSTAID,
 MAINFLAG, INVOICEFLAG, MAILFLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB) as
select p.pers_id, pa.ans, r.vor, p.name, bezspr.bez, p.s_id, sta.sta, p.sta_id,
 pa.adr1, pa.adr2, pa.adr3, pa.plz, pa.ort, pa.kant, pa.land_id, bezland.bez,
 p.textid, rt.dlncode, r.rkr_id, r.sex, r.mutters_id, r.age, r.passnr,
 r.attr1, r.attr2, r.textid, sta1.sta, pa.adr_typ, sta2.sta, pa.sta_id,
 pa.haupt_flag, pa.rch_flag, pa.mail_flag, pa.tel, pa.handy, pa.fax, pa.tlx,
 pa.email, pa.web
from 	personen p, reisender r, persadr pa, sprachen spr, bezeichnung bezspr, reisender_typ rt,
 status_werte sta, land, bezeichnung bezland, status_werte sta1, status_werte sta2
where	p.pers_id > 0 and (p.pers_typ = 1 and r.pers_id = p.pers_id and pa.pers_id = p.pers_id)
and ((spr.s_id = p.s_id and bezspr.s_id = p.s_id) and (bezspr.bez_id = spr.bez_id)
 and (bezspr.typ = 1))
and ((land.land_id = pa.land_id and bezland.s_id = p.s_id) and (bezland.bez_id = land.bez_id)
 and (bezland.typ = 10))
and (rt.rkr_id = r.rkr_id)
and (sta.sta_id = p.sta_id and sta.typ = 1110)
and (sta1.sta_id = pa.adr_typ and sta1.typ = 1127)
and (sta2.sta_id = pa.sta_id and sta2.typ = 1111);

/* Customers PERS_TYP = 2*/
drop view tdbv_custsel;
create view tdbv_custsel (PERS_ID, NAME) as
select p.pers_id, p.name
from 	personen p
where	p.pers_id > 0 and p.pers_typ = 2;

drop view tdbv_cust;
create view tdbv_cust (PERS_ID, NAME, S_ID, STA_ID, TEXTID, CUSTTYPEID, TEL, HANDY,
 FAX, TLX, EMAIL, WEB, ACCOUNT, MANAGER, ATTR1, ATTR2, CURID) as
select p.pers_id, p.name, p.s_id, p.sta_id, p.textid, k.k_typ_id, k.tel, k.handy,
 k.fax, k.tlx, k.email, k.web, k.konto, k.leiter, k.attr1, k.attr2, k.whr_id
from 	personen p, kunden k
where	p.pers_id > 0 and (k.pers_id = p.pers_id and p.pers_typ = 2);

drop view tdbv_custadr;
create view tdbv_custadr (PERS_ID, ANS, NAME, LANG, S_ID, PERSSTA, PERSSTAID,
 ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, LAND,
 TEXTID, CUSTTYPE, CUSTTYPEID, CTEL, CHANDY, CFAX, CTLX, CEMAIL, CWEB, ACCOUNT, MANAGER,
 ATTR1, ATTR2, ADRTYP, ADRTYPID, ADRSTA, ADRSTAID,
 MAINFLAG, INVOICEFLAG, MAILFLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB, CURID, CUR) as
select p.pers_id, pa.ans, p.name, bezspr.bez, p.s_id, sta.sta, p.sta_id,
 pa.adr1, pa.adr2, pa.adr3, pa.plz, pa.ort, pa.kant, pa.land_id, bezland.bez,
 p.textid, kt.kuncode, k.k_typ_id, k.tel, k.handy, k.fax, k.tlx, k.email, k.web, k.konto, k.leiter,
 k.attr1, k.attr2, sta1.sta, pa.adr_typ, sta2.sta, pa.sta_id,
 pa.haupt_flag, pa.rch_flag, pa.mail_flag, pa.tel, pa.handy, pa.fax, pa.tlx,
 pa.email, pa.web, k.whr_id, w.krzl
from 	personen p, kunden k, persadr pa, sprachen spr, bezeichnung bezspr, kunden_typ kt,
 status_werte sta, land, bezeichnung bezland, status_werte sta1, status_werte sta2,
 waehrung w
where	p.pers_id > 0 and (p.pers_typ = 2 and k.pers_id = p.pers_id and pa.pers_id = p.pers_id)
and ((spr.s_id = p.s_id and bezspr.s_id = p.s_id) and (bezspr.bez_id = spr.bez_id)
 and (bezspr.typ = 1))
and ((land.land_id = pa.land_id and bezland.s_id = p.s_id) and (bezland.bez_id = land.bez_id)
 and (bezland.typ = 10))
and (kt.k_typ_id = k.k_typ_id)
and (w.whr_id = k.whr_id)
and (sta.sta_id = p.sta_id and sta.typ = 1110)
and (sta1.sta_id = pa.adr_typ and sta1.typ = 1127)
and (sta2.sta_id = pa.sta_id and sta2.typ = 1111);

/* address */
drop view tdbv_adr;
create view tdbv_adr (PERS_ID, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT,
 LAND_ID, LAND, LANDSID, ADRTYP, ADRTYPID, ADRSTA, ADRSTAID, MAINFLAG,
 INVOICEFLAG, MAILFLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB) as
select pa.pers_id, pa.ans, pa.adr1, pa.adr2, pa.adr3, pa.plz, pa.ort, pa.kant,
 pa.land_id, bezland.bez, bezland.s_id, sta1.sta, pa.adr_typ, sta2.sta, pa.sta_id, pa.haupt_flag,
 pa.rch_flag, pa.mail_flag, pa.tel, pa.handy, pa.fax, pa.tlx, pa.email, pa.web
from 	persadr pa, land, bezeichnung bezland, status_werte sta1, status_werte sta2
where	pa.pers_id > 0
and ((land.land_id = pa.land_id) and (bezland.bez_id = land.bez_id)
 and (bezland.typ = 10))
and (sta1.sta_id = pa.adr_typ and sta1.typ = 1127)
and (sta2.sta_id = pa.sta_id and sta2.typ = 1111);

/* Suppliertype */
drop view tdbv_dlttsel;
create view tdbv_dlttsel (TYP_ID, BEZ, S_ID) as
select tt.typ_id, bez.bez, bez.s_id
from 	traeger_typ tt, bezeichnung bez
where	tt.typ_id > 0 and bez.bez_id = tt.bez_id and bez.typ = 15;

drop view tdbv_dltt;
create view tdbv_dltt (TYP_ID, BEZ_ID, BEZ, S_ID, H_TYP_ID, HOST_TYP, TEXTID) as
select tt.typ_id, tt.bez_id, bez.bez, bez.s_id, tt.h_typ_id, tt.host_typ, tt.textid
from 	traeger_typ tt, bezeichnung bez
where	tt.typ_id > 0 and bez.bez_id = tt.bez_id and bez.typ = 15;

drop view tdbv_dltttree;
create view tdbv_dltttree (TYP_ID, BEZ_ID, BEZ, H_TYP_ID, HBEZ, HOST_TYP, HOSTBEZ, S_ID) as
select tt.typ_id, tt.bez_id, bez.bez, tt.h_typ_id, hbez.bez, tt.host_typ, hostbez.bez, bez.s_id
from 	traeger_typ tt, bezeichnung bez, traeger_typ htt, bezeichnung hbez,
 traeger_typ hosttt, bezeichnung hostbez
where	tt.typ_id > 0 and bez.typ = 15 and hbez.typ = 15 and hostbez.typ = 15
and bez.bez_id = tt.bez_id and hbez.s_id = bez.s_id and hostbez.s_id = bez.s_id
and ((htt.typ_id = tt.h_typ_id) and (hbez.bez_id = htt.bez_id))
and ((hosttt.typ_id = tt.host_typ) and (hostbez.bez_id = hosttt.bez_id));

/* CATEGORY */
drop view tdbv_catsel;
create view tdbv_catsel (CAT_ID, BEZ, S_ID) as
select kat.kat_id, bez.bez, bez.s_id
from 	kategorie kat, bezeichnung bez
where	kat.kat_id > 0 and bez.bez_id = kat.bez_id and bez.typ = 16;

drop view tdbv_cat;
create view tdbv_cat (CAT_ID, BEZ_ID, BEZ, S_ID, H_KAT_ID, SUPTYP, SUPTYPID, GA, TEXTID) as
select kat.kat_id, kat.bez_id, bez.bez, bez.s_id, kat.h_kat_id, beztt.bez, kat.typ_id, kat.ga, kat.textid
from 	kategorie kat, bezeichnung bez, traeger_typ tt, bezeichnung beztt
where	kat.kat_id > 0 and bez.bez_id = kat.bez_id and bez.typ = 16
and ((tt.typ_id = kat.typ_id)
and (beztt.typ = 15 and beztt.bez_id = tt.bez_id) and beztt.s_id = bez.s_id);

drop view tdbv_cattree;
create view tdbv_cattree (CAT_ID, BEZ_ID, BEZ, H_KAT_ID, HBEZ, S_ID) as
select kat.kat_id, kat.bez_id, bez.bez, kat.h_kat_id, hbez.bez, bez.s_id
from 	kategorie kat, bezeichnung bez, kategorie hk, bezeichnung hbez
where	kat.kat_id > 0 and bez.typ = 16 and hbez.typ = 16
and bez.bez_id = kat.bez_id and hbez.s_id = bez.s_id
and ((hk.kat_id = kat.h_kat_id) and (hbez.bez_id = hk.bez_id));

/* Supplier */
drop view tdbv_dltsel;
create view tdbv_dltsel (DLT_ID, BEZ, CODE, S_ID) as
select dlt.dlt_id, bez.bez, dlt.code, bez.s_id
from 	dienst_traeger dlt, bezeichnung bez
where	dlt.dlt_id > 0 and bez.bez_id = dlt.bez_id and bez.typ = 17;

drop view tdbv_dlt;
create view tdbv_dlt (DLT_ID, BEZ_ID, BEZ, CODE, S_ID, H_DLT_ID, HOSTID, DLT_GRP_ID,
 TYP, TYPID, CAT, CAT_ID, LEVELPLACE, NUMPLACE, STA, STAID, TEXTID) as
select dlt.dlt_id, dlt.bez_id, bez.bez, dlt.code, bez.s_id, dlt.h_dlt_id, dlt.host_id, dlt.dlt_grp_id,
 beztt.bez, dlt.typ_id, bezk.bez, dlt.kat_id, dlt.stufe, dlt.anz, sta.sta, dlt.sta_id, dlt.textid
from 	dienst_traeger dlt, bezeichnung bez, traeger_typ tt, bezeichnung beztt,
 kategorie kat, bezeichnung bezk, status_werte sta
where	dlt.dlt_id > 0
and (bez.bez_id = dlt.bez_id and bez.typ = 17)
and ((tt.typ_id = dlt.typ_id)
and (beztt.typ = 15 and beztt.bez_id = tt.bez_id) and beztt.s_id = bez.s_id)
and ((kat.kat_id = dlt.kat_id)
and (bezk.typ = 16 and bezk.bez_id = kat.bez_id) and bezk.s_id = bez.s_id)
and ((sta.sta_id = dlt.sta_id) and (sta.typ = 1115));

drop view tdbv_dlttree;
create view tdbv_dlttree (DLT_ID, BEZ_ID, BEZ, PARENTID, PARENT, HOSTID, HOST, S_ID) as
select dlt.dlt_id, dlt.bez_id, bez.bez, dlt.h_dlt_id, hbez.bez, dlt.host_id, hostbez.bez, bez.s_id
from 	dienst_traeger dlt, bezeichnung bez, dienst_traeger parent, bezeichnung hbez,
 dienst_traeger host, bezeichnung hostbez
where	dlt.dlt_id > 0 and bez.typ = 17 and hbez.typ = 17 and hostbez.typ = 17
and bez.bez_id = dlt.bez_id and hbez.s_id = bez.s_id and hostbez.s_id = bez.s_id
and ((parent.dlt_id = dlt.h_dlt_id) and (hbez.bez_id = parent.bez_id))
and ((host.dlt_id = dlt.host_id) and (hostbez.bez_id = host.bez_id));

drop view tdbv_dltoperator;
create view tdbv_dltoperator (DLT_ID, BEZ, CODE, S_ID, COMPANY, COMPANYID) as
select td.dlt_id, bez.bez, dlt.code, bez.s_id, pers.name, td.firma
from 	traeger_detail td, dienst_traeger dlt, bezeichnung bez, personen pers
where	dlt.dlt_id > 0 and bez.bez_id = dlt.bez_id and bez.typ = 17
and dlt.dlt_id = td.dlt_id and pers.pers_id = td.firma;


/* ACTION TYPE  */
drop view tdbv_acttsel;
create view tdbv_acttsel (ACTTYPE_ID, BEZ, CODE, S_ID) as
select at.a_typ_id, bez.bez, at.proz, bez.s_id
from 	aktions_typ at, bezeichnung bez
where	at.a_typ_id > 0 and bez.typ = 19 and bez.bez_id = at.bez_id;

drop view tdbv_actt;
create view tdbv_actt (ACTTYPE_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID) as
select at.a_typ_id, at.bez_id, bez.bez, bez.s_id, at.proz, at.textid
from 	aktions_typ at, bezeichnung bez
where	at.a_typ_id > 0 and bez.typ = 19 and bez.bez_id = at.bez_id;

drop view tdbv_actpara;
create view tdbv_actpara (ACTTYPE_ID, BEZ, CODE, NO, PARA, PARATYPEID, MAND, FLAG, TEXTID) as
select ap.a_typ_id, ap.bez, at.proz, ap.nr, ap.bez, ap.typ, ap.muss, ap.flag, ap.textid
from 	aktionspara ap, aktions_typ at
where	ap.a_typ_id > 0 and at.a_typ_id = ap.a_typ_id;

/* ACTIONS  */
drop view tdbv_actsel;
create view tdbv_actsel (ACT_ID, BEZ, S_ID) as
select a.akt_id, bez.bez, bez.s_id
from 	aktionen a, bezeichnung bez
where	a.akt_id > 0 and bez.typ = 21 and bez.bez_id = a.bez_id;

drop view tdbv_act;
create view tdbv_act (ACT_ID, BEZ_ID, BEZ, S_ID, TEXTID, AFLAG, AFLAGID, BFLAG, BFLAGID,
 B2FLAG, B2FLAGID, MFLAG, MFLAGID, ACTTYPE, ACTTYPEID, ACTTPROC, FILE_ID) as
select a.akt_id, a.bez_id, bez.bez, bez.s_id, a.textid, aflg.sta, a.a_flag, bflg.sta, a.b_flag,
 b2flg.sta, a.b2_flag, dev.sta, a.m_flag, beztyp.bez, a.a_typ_id, at.proz, a.file_id
from 	aktionen a, bezeichnung bez, aktions_typ at, bezeichnung beztyp, status_werte aflg,
 status_werte bflg, status_werte b2flg, status_werte dev
where	a.akt_id > 0 and bez.typ = 21 and bez.bez_id = a.bez_id
 and (at.a_typ_id = a.a_typ_id and beztyp.typ = 19 
 and beztyp.bez_id = at.bez_id and beztyp.s_id = bez.s_id)
 and (aflg.sta_id = a.a_flag and aflg.typ = 1109)
 and (bflg.sta_id = a.b_flag and bflg.typ = 1112)
 and (b2flg.sta_id = a.b2_flag and b2flg.typ = 1112)
 and (dev.sta_id = a.m_flag and dev.typ = 1119);

drop view tdbv_actgrp;
create view tdbv_actgrp (ACT_ID, BEZ, PARENTID, PARENTBEZ, ORD, HOSTID, HOST, S_ID) as
select ag.childakt, bchild.bez, ag.parentakt, bpar.bez, ag.ord, ag.h_akt_id,
 bhost.bez, bpar.s_id
from 	aktionsgrp ag, aktionen parent, bezeichnung bpar,
 aktionen child, bezeichnung bchild, aktionen host, bezeichnung bhost
where	child.akt_id = ag.childakt and parent.akt_id = ag.parentakt and host.akt_id = ag.h_akt_id
 and bpar.s_id = bchild.s_id and bhost.s_id = bchild.s_id
 and bpar.typ = 21 and bchild.typ = 21 and bhost.typ = 21
 and bpar.bez_id = parent.bez_id and bchild.bez_id = child.bez_id
 and bhost.bez_id = host.bez_id;

/* OFFER TYPE  */
drop view tdbv_otsel;
create view tdbv_otsel (OT_ID, BEZ, S_ID) as
select at.art_id, bez.bez, bez.s_id
from 	angebots_typ at, bezeichnung bez
where	at.art_id > 0 and bez.typ = 18 and bez.bez_id = at.bez_id;

drop view tdbv_ot;
create view tdbv_ot (OT_ID, BEZ_ID, BEZ, S_ID, TEXTID) as
select at.art_id, at.bez_id, bez.bez, bez.s_id, at.textid
from 	angebots_typ at, bezeichnung bez
where	at.art_id > 0 and bez.typ = 18 and bez.bez_id = at.bez_id;

/* OFFER */
drop view tdbv_osel;
create view tdbv_osel (O_ID, BEZ, CODE, S_ID) as
select dla.dla_id, bez.bez, dla.code, bez.s_id
from 	dienst_angebot dla, bezeichnung bez
where	dla.dla_id > 0 and bez.typ = 23 and bez.bez_id = dla.bez_id;

drop view tdbv_o;
create view tdbv_o (O_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID, HOSTO, HOSTO_ID, ORD,
SUP, SUPID, ACT, ACTID, LOCATION, OT, OTID, DURATION,
FROMCITY, FROMCITYID, TOCITY, TOCITYID) as
select dla.dla_id, dla.bez_id, bez.bez, bez.s_id, dla.code, dla.textid, hdla.code, dla.h_dla_id, dla.ord,
dlt.code, dla.dlt_id, actbez.bez, dla.akt_id, dla.ort, atbez.bez, dla.art_id, todate(dla.dau),
fort.krzl, dla.von, tort.krzl, dla.nach
from 	dienst_angebot dla, bezeichnung bez, angebots_typ at, bezeichnung atbez,
 dienst_angebot hdla, dienst_traeger dlt, aktionen act, bezeichnung actbez,
 ort fort, ort tort
where	(dla.dla_id > 0 and bez.typ = 23 and bez.bez_id = dla.bez_id)
and (hdla.dla_id = dla.h_dla_id)
and (dlt.dlt_id = dla.dlt_id)
and (act.akt_id = dla.akt_id and actbez.typ = 21 and actbez.bez_id = act.bez_id and actbez.s_id = bez.s_id)
and (at.art_id = dla.art_id and atbez.typ = 18 and atbez.bez_id = at.bez_id and atbez.s_id = bez.s_id)
and fort.ort_id = dla.von and tort.ort_id = dla.nach;

/* SERVICEOFFER */
drop view tdbv_sosel;
create view tdbv_sosel (SO_ID, BEZ, CODE, S_ID, STARTDAT, STOPDAT) as
select dl.dl_id, bez.bez, dl.code, bez.s_id, todate(dl.a_zeit), todate(dl.e_zeit)
from 	dlg_parts dl, bezeichnung bez
where	dl.dl_id > 0 and bez.typ = 26 and bez.bez_id = dl.bez_id;

drop view tdbv_so;
create view tdbv_so (SO_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID, STARTDAT, STOPDAT,
HOSTSO, HOSTSOID, OFFER, OFFERID, ORD, RESFLAG, RESFLAGID,
OPERATOR, OPERATORID, ACCOUNT, INVOICE, INVOICEID, SEASON, SEASONID) as
select dl.dl_id, dl.bez_id, bez.bez, bez.s_id, dl.code, dl.textid, todate(dl.a_zeit), todate(dl.e_zeit),
hdl.code, dl.h_dl_id, dla.code, dl.dla_id, dl.ord, resf.sta, dl.res_f,
op.name, dl.kid, dl.konto, inv.name, dl.rechst, saibez.bez, dl.sai_id
from 	dlg_parts dl, bezeichnung bez, dienst_angebot dla, status_werte resf,
dlg_parts hdl, personen op, personen inv, saison sai, bezeichnung saibez
where	dl.dl_id > 0 and bez.typ = 26 and bez.bez_id = dl.bez_id
and hdl.dla_id = dl.h_dl_id
and dla.dla_id = dl.dla_id
and (resf.sta_id = dl.res_f and resf.typ = 1112)
and (sai.sai_id = dl.sai_id and saibez.typ = 9 and saibez.bez_id = sai.bez_id and saibez.s_id = bez.s_id)
and op.pers_id = dl.kid and inv.pers_id = dl.rechst;

/* SERVICE */
drop view tdbv_servsel;
create view tdbv_servsel (SERV_ID, BEZ, CODE, S_ID, ADAT) as
select dl.dlg_id, bez.bez, dl.code, bez.s_id, todate(dl.a_zeit)
from 	dienstleistung dl, bezeichnung bez
where	dl.dlg_id > 0 and bez.typ = 27 and bez.bez_id = dl.bez_id;

drop view tdbv_serv;
create view tdbv_serv (SERV_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID, SEASON, SEASONID,
ADAT, ACT, ACTID) as
select dl.dlg_id, dl.bez_id, bez.bez, bez.s_id, dl.code, dl.textid, saibez.bez, dl.sai_id,
todate(dl.a_zeit), actbez.bez, dl.akt_id
from 	dienstleistung dl, bezeichnung bez, saison sai, bezeichnung saibez,
 aktionen act, bezeichnung actbez
where	dl.dlg_id > 0 and bez.typ = 27 and bez.bez_id = dl.bez_id
and (sai.sai_id = dl.sai_id and saibez.bez_id = sai.bez_id and saibez.typ = 9 and saibez.s_id = bez.s_id)
and (act.akt_id = dl.akt_id and actbez.bez_id = act.bez_id and actbez.typ = 21 and actbez.s_id = bez.s_id);

/* PROGRAM  */
drop view tdbv_prgsel;
create view tdbv_prgsel (PRG_ID, BEZ, CODE, S_ID) as
select p.prg_id, bez.bez, p.code, bez.s_id
from 	programm p, bezeichnung bez
where	p.prg_id > 0 and bez.typ = 29 and bez.bez_id = p.bez_id;

drop view tdbv_prg;
create view tdbv_prg (PRG_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID, SAI_ID, SAI) as
select p.prg_id, p.bez_id, bez.bez, bez.s_id, p.code, p.textid, p.sai_id, saibez.bez
from 	programm p, bezeichnung bez, saison s, bezeichnung saibez
where	p.prg_id > 0 and bez.typ = 29 and bez.bez_id = p.bez_id
and (s.sai_id = p.sai_id and saibez.typ = 9 and saibez.bez_id = s.bez_id and saibez.s_id = bez.s_id);

/* ARRANGEMENT  */
drop view tdbv_arrsel;
create view tdbv_arrsel (ARR_ID, BEZ, CODE, S_ID, ADAT) as
select a.arr_id, bez.bez, a.code, bez.s_id, todate(a.a_dat)
from 	arrangement a, bezeichnung bez
where	a.arr_id > 0 and bez.typ = 30 and bez.bez_id = a.bez_id;

drop view tdbv_arr;
create view tdbv_arr (ARR_ID, BEZ_ID, BEZ, S_ID, CODE, TEXTID, ADAT, PRG_ID, PRG, SAI_ID, SAI) as
select a.arr_id, a.bez_id, bez.bez, bez.s_id, a.code, a.textid, todate(a.a_dat), a.prg_id, pbez.bez, a.sai_id, saibez.bez
from 	arrangement a, bezeichnung bez, programm p, bezeichnung pbez, saison s, bezeichnung saibez
where	a.arr_id > 0 and bez.typ = 30 and bez.bez_id = a.bez_id
and (p.prg_id = a.prg_id and pbez.typ = 29 and pbez.bez_id = p.bez_id and pbez.s_id = bez.s_id)
and (s.sai_id = a.sai_id and saibez.typ = 9 and saibez.bez_id = s.bez_id and saibez.s_id = bez.s_id);

/* PRICE TYPE  */
drop view tdbv_prtsel;
create view tdbv_prtsel (PRT_ID, BEZ, S_ID) as
select ka.kar_id, bez.bez, bez.s_id
from 	kosten_art ka, bezeichnung bez
where	ka.kar_id > 0 and bez.typ = 43 and bez.bez_id = ka.bez_id;

drop view tdbv_prt;
create view tdbv_prt (PRT_ID, BEZ_ID, BEZ, S_ID, TEXTID) as
select ka.kar_id, ka.bez_id, bez.bez, bez.s_id, ka.textid
from 	kosten_art ka, bezeichnung bez
where	ka.kar_id > 0 and bez.typ = 43 and bez.bez_id = ka.bez_id;
