/*d************************************************************/
/* project:   traveldb database views                         */
/*                                                            */
/*            attention !! types are hardcoded here !!!       */
/*            check with mpobjdef.h                           */
/*                                                            */
/* copyright: yafra.org, switzerland, 2004                    */
/**************************************************************/
/* rcs information: */
/* $header: /yafra/cvsroot/mapo/db/abstract/dbe_views.sql,v 1.7 2006-01-18 07:23:39 mwn exp $ */

/***************************************************************************/
/* code views                                                              */
/***************************************************************************/

/* spr_view sprachen mit bez  260 */
drop view spr_view;
create view spr_view (s_id, bez, bezsprid, dialog, sysbez) as
select spr.s_id, bez.bez, bez.s_id, spr.dialog, spr.sysbez
from 	sprachen spr, bezeichnung bez
where	bez.typ = 1 and bez.bez_id = spr.bez_id;

/* sta_view statuswerte mit bez 261 */
drop view sta_view;
create view sta_view (sta_id, abk, sta, bez, s_id, kond, typ) as
select sta.sta_id, sta.abk, sta.sta, bez.bez, bez.s_id, sta.kond, sta.typ
from 	status_werte sta, bezeichnung bez
where	bez.typ = sta.typ and bez.bez_id = sta.bez_id;

/* sai_view saison mit bez 262 */
drop view sai_view;
create view sai_view (sai_id, bez, s_id, von, bis, textid) as
select sai.sai_id, bez.bez, bez.s_id, sai.von, sai.bis, sai.textid
from 	saison sai, bezeichnung bez
where	bez.typ = 9 and bez.bez_id = sai.bez_id;

/***************************************************************************/
/* geografie views                                                         */
/***************************************************************************/

/* land_view land mit bez 263 */
drop view land_view;
create view land_view (land_id, bez, s_id, krzl, haupt_ort,
 haupt_spr, haupt_whr, textid, vat) as
select land.land_id, bez.bez, bez.s_id, land.krzl, land.haupt_ort,
 land.haupt_spr, land.haupt_whr, land.textid, land.vat
from 	land, bezeichnung bez
where	bez.typ = 10 and bez.bez_id = land.bez_id;

/***************************************************************************/
/* personen                                                                */
/***************************************************************************/

/* kunden_view nur personen die kunden sind mit kundenteil  264 */
drop view kunden_view;
create view kunden_view (kun_id, name, ort, s_id, sta_id, textid, kant,
  tel, fax, tlx, konto, leiter, attr1, attr2, k_typ_id, land_id, whr_id) as
select pers.pers_id, pers.name, adr.ort, pers.s_id, pers.sta_id, pers.textid,
  adr.kant, kun.tel, kun.fax, kun.tlx, kun.konto, kun.leiter, kun.attr1,
  kun.attr2, kun.k_typ_id, adr.land_id, kun.whr_id
from personen pers, kunden kun, persadr adr
where pers.pers_typ = 2 and kun.pers_id = pers.pers_id
and adr.haupt_flag = 1 and adr.pers_id = pers.pers_id;

/* dln_view nur personen die private sind mit reisendenteil  265 */
drop view dln_view;
create view dln_view (dln_id, name, vor, ort, s_id, sta_id, textid, rkr_id,
  sex, ext_txt, land_id, age, passnr, attr1, attr2) as
select pers.pers_id, pers.name, dln.vor, adr.ort, pers.s_id, pers.sta_id,
  pers.textid, dln.rkr_id, dln.sex, dln.textid, adr.land_id, dln.age,
  dln.passnr, dln.attr1, dln.attr2
from personen pers, reisender dln, persadr adr
where pers.pers_typ = 1 and dln.pers_id = pers.pers_id
and adr.haupt_flag = 1 and adr.pers_id = pers.pers_id;

/* dl-nehmer typ bezeichnungs view  266 */
drop view rkr_view;
create view rkr_view (rkr_id, bez, s_id, textid, dlncode, vonalter,
  bisalter) as
select rkr.rkr_id, bez.bez, bez.s_id, rkr.textid, rkr.dlncode, rkr.vonalter,
  rkr.bisalter
from 	reisender_typ rkr, bezeichnung bez
where	bez.typ = 35 and	bez.bez_id = rkr.bez_id;

/* dln adr view bezeichnungs view  286 */
drop view mpv_dlnadr;
create view mpv_dlnadr (pers_id, ans, name, vor, adr1, adr2, adr3, plz,
  ort, land_id, sta_id) as
select adr.pers_id, adr.ans, pers.name, dln.vor, adr.adr1, adr.adr2,
  adr.adr3, adr.plz, adr.ort, adr.land_id, adr.sta_id
from 	persadr adr, personen pers, reisender dln
where	adr.pers_id = pers.pers_id and dln.pers_id = pers.pers_id
and adr.haupt_flag = 1;

/* kun adr view bezeichnungs view  287 */
drop view mpv_kunadr;
create view mpv_kunadr (pers_id, ans, name, adr1, adr2, adr3, plz,
  ort, kant, land_id, sta_id, k_typ_id, tel, fax) as
select adr.pers_id, adr.ans, pers.name, adr.adr1, adr.adr2, adr.adr3,
  adr.plz, adr.ort, adr.kant, adr.land_id, adr.sta_id, kun.k_typ_id,
  kun.tel, kun.fax
from    persadr adr, personen pers, kunden kun
where   adr.pers_id = pers.pers_id and kun.pers_id = pers.pers_id
and adr.haupt_flag = 1;


/***************************************************************************/
/* reservationskern / stammdaten                                           */
/***************************************************************************/

/* traeger_typ bezeichnungs view (parent/child)  267 */
drop view ttyp_view;
create view ttyp_view (spr, id, bez, hid, hbez) as
select bez_a.s_id, dltt_a.typ_id, bez_a.bez,	dltt_a.h_typ_id, bez_b.bez
from traeger_typ dltt_a, bezeichnung bez_a,
	traeger_typ dltt_b, bezeichnung bez_b
where	(bez_a.typ = 15 and	bez_b.typ = 15)
	and (dltt_a.bez_id = bez_a.bez_id and	dltt_b.bez_id = bez_b.bez_id)
	and dltt_a.h_typ_id = dltt_b.typ_id
	and bez_a.s_id = bez_b.s_id;

/* kategorie bezeichnungs view  268 */
drop view kat_view;
create view kat_view (kat_id, bez, s_id, h_kat_id,
  typ_id, ga, textid) as
select kat.kat_id, bez.bez, bez.s_id, kat.h_kat_id,
  kat.typ_id, kat.ga, kat.textid
from 	kategorie kat, bezeichnung bez
where	bez.typ = 16 and bez.bez_id = kat.bez_id;

/* dienst_traeger mit bez und h_bez (prarent/child) 269 */
drop view traeger_view;
create view traeger_view (spr, typ, id, bez, hid, host) as
select bez_a.s_id, dlt.typ_id, dlt.dlt_id, bez_a.bez,
	dlt.h_dlt_id, dlt.host_id
from bezeichnung bez_a, dienst_traeger dlt
where	(bez_a.bez_id = dlt.bez_id) and (bez_a.typ = 17);

/* dienst_traeger mit bez  270 */
drop view dlt_view;
create view dlt_view (dlt_id, bez, s_id, kat_id, h_dlt_id,
  host_id, typ_id, textid, stufe) as
select dlt.dlt_id, bez.bez, bez.s_id, dlt.kat_id, dlt.h_dlt_id,
  dlt.host_id, dlt.typ_id, dlt.textid, dlt.stufe
from 	dienst_traeger dlt, bezeichnung bez
where	bez.typ = 17 and dlt.bez_id = bez.bez_id;

/* aktionen mit bez  (parent/child) 271 */
drop view akt_view;
create view akt_view (id, bez, ubez, ord, spr) as
select child.childakt, bchild.bez, bparent.bez, child.ord, bchild.s_id
from 	aktionsgrp child, bezeichnung bchild, aktionen aktchild,
  bezeichnung bparent, aktionen aktparent
where	(bchild.typ = 21 and	bparent.typ = 21)
	and	aktchild.akt_id = child.childakt
	and	bchild.bez_id = aktchild.bez_id
	and	aktparent.akt_id = child.parentakt
	and	bparent.bez_id = aktparent.bez_id
	and 	bchild.s_id = bparent.s_id;

/* dienst_angebot mit bez  272 */
drop view dla_view;
create view dla_view (dla_id, h_dla_id, ord, dlt_id, bez, s_id,
  akt_id, ort, art_id, dau, textid, von, nach) as
select dla.dla_id, dla.h_dla_id, dla.ord, dla.dlt_id, bez.bez, bez.s_id,
  dla.akt_id, dla.ort, dla.art_id, dla.dau, dla.textid,
  dla.von, dla.nach
from 	dienst_angebot dla, bezeichnung bez
where	bez.typ = 23 and bez.bez_id = dla.bez_id;

/* dlg_part teildienstleistung  mit bez  273 */
drop view dlg_view;
create view dlg_view (dl_id, h_dl_id, dla_id, bez, s_id, ord,
  a_zeit, e_zeit, res_f, kid, konto, textid, sai_id) as
select dlg.dl_id, dlg.h_dl_id, dlg.dla_id, bez.bez, bez.s_id, dlg.ord,
  dlg.a_zeit, dlg.e_zeit, dlg.res_f, dlg.kid, dlg.konto,
  dlg.textid, dlg.sai_id
from 	dlg_parts dlg, bezeichnung bez
where	bez.typ = 26 and bez.bez_id = dlg.bez_id;

/* dl_dlg view zusammensetzung dienstleistung mit dlg_parts  274 */
drop view dl_dlg_view;
create view dl_dlg_view (dlg_id, start_zeit, dl_id, bez, a_zeit, e_zeit,
  ord, res_f, s_id) as
select dl.dlg_id, dl.a_zeit, dlg.dl_id, bez.bez, dlg.a_zeit, dlg.e_zeit,
  dldlg.ord, dlg.res_f, bez.s_id
from dienstleistung dl, dlg_parts dlg, dlg_dlg dldlg, bezeichnung bez
where (dl.dlg_id = dldlg.dlg_id and dlg.dl_id = dldlg.dl_id)
  and (dlg.bez_id = bez.bez_id and bez.typ = 26);

/* dienstleistung bezeichnungs view  275 */
drop view dtg_view;
create view dtg_view (dlg_id, bez, s_id, textid, sai_id, a_zeit, akt_id) as
select dtg.dlg_id, bez.bez, bez.s_id, dtg.textid,
  dtg.sai_id, dtg.a_zeit, dtg.akt_id
from 	dienstleistung dtg, bezeichnung bez
where	bez.typ = 27 and	bez.bez_id = dtg.bez_id;

/* routen view aus dienstleistungen 285 */
drop view routen_view;
create view routen_view (dlg_id, bez, s_id, von, nach) as
select dlg.dlg_id, bez.bez, bez.s_id, von.krzl, nach.krzl
from dienstleistung dlg, bezeichnung bez, dlg_dlg ddv,
  dlg_dlg ddn, dlg_parts dlv, dlg_parts dln,
  dienst_angebot dav, dienst_angebot dan, ort von, ort nach
where ddv.ord =	(select min(ord)
							from   dlg_dlg a
							where  a.dlg_id = dlg.dlg_id)
and ddv.dlg_id = dlg.dlg_id
and ddn.ord =	(select max(ord)
							from   dlg_dlg b
							where  b.dlg_id = dlg.dlg_id)
and ddn.dlg_id = dlg.dlg_id
and bez.typ=27
and bez.bez_id = dlg.bez_id
and dlv.dl_id = ddv.dl_id
and dln.dl_id = ddn.dl_id
and dav.dla_id = dlv.dla_id
and dan.dla_id = dln.dla_id
and von.ort_id = dav.von
and nach.ort_id = dan.nach;


/* arr_dl view zusammensetzung arrangement mit dienstleistungen  276 */
drop view arr_dl_view;
create view arr_dl_view (arr_id, a_dat, dlg_id, bez, a_zeit, teil,
  prio, akt_id, s_id) as
select arr.arr_id, arr.a_dat, dl.dlg_id, bez.bez, dl.a_zeit, ad.teil,
  ad.prio, dl.akt_id, bez.s_id
from arrangement arr, arr_dlg ad, dienstleistung dl, bezeichnung bez
where (arr.arr_id = ad.arr_id and dl.dlg_id = ad.dlg_id)
  and (dl.bez_id = bez.bez_id and bez.typ = 27);

/* arrangement bezeichnungs view  277 */
drop view arr_view;
create view arr_view (arr_id, bez, s_id, a_dat,
  prg_id, textid, sai_id) as
select arr.arr_id, bez.bez, bez.s_id, arr.a_dat,
  arr.prg_id, arr.textid, arr.sai_id
from 	arrangement arr, bezeichnung bez
where	bez.typ = 30 and	bez.bez_id = arr.bez_id;

/* arr_dlg  will be obsolete with version 6.0  278 */
drop view arr_dlg_view;
create view arr_dlg_view (arr_id, teil, prio, dlg_id, dl_id, ord, a_zeit,
	res_f, bez, bez1, s_id, dtg_zeit) as
select arr_dlg.arr_id, arr_dlg.teil, arr_dlg.prio, arr_dlg.dlg_id,
	dlg_parts.dl_id, dlg_dlg.ord, dlg_parts.a_zeit,
	dlg_parts.res_f, a.bez, b.bez, a.s_id, dienstleistung.a_zeit
from	arr_dlg, dlg_dlg, dlg_parts,
	dienstleistung, bezeichnung a, bezeichnung b
where	arr_dlg.dlg_id = dlg_dlg.dlg_id
and	arr_dlg.dlg_id = dienstleistung.dlg_id
and	dlg_parts.dl_id = dlg_dlg.dl_id
and	a.typ = 26
and	a.bez_id=dlg_parts.bez_id
and	b.typ = 27
and	b.bez_id=dienstleistung.bez_id
and	a.s_id = b.s_id;




/***************************************************************************/
/* kontingentierung                                                        */
/***************************************************************************/

/* kontingent uebersicht ï¿½ber zusammensetzung des kontingents  279 */
drop view kon_view;
create view kon_view (kont_id, bez, s_id, hostkont_id, kunden_id,
  opt_dat, ref, sai_id, textid) as
select kon.kont_id, bez.bez, bez.s_id, kon.hostkont_id, kon.kunden_id,
  kon.opt_dat, kon.ref, kon.sai_id, kon.textid
from 	kontingent kon, bezeichnung bez
where	bez.typ = 39 and bez.bez_id = kon.bez_id;

/* koncheck check free space in a kont 283 */
drop view koncheck_view;
create view koncheck_view (hostkont_id, kont_id, kat_id, dlt_id, anz, busy) as
select kon.hostkont_id, kon.kont_id, kd.kat_id, kd.dlt_id, kd.anz, kd.busy
from kontingent kon, kont_detail kd
where kd.kont_id = kon.kont_id;





/***************************************************************************/
/* buchung / reservation / preise                                          */
/***************************************************************************/

/* reservation / dienstleistung  uebersicht  290 */
drop view res_dl_view;
create view res_dl_view (bid, pers_id, name,
	dl_id, dlazeit,
	tdl_id, tdlazeit, tdlezeit, 
	resazeit, resezeit, 
	kat_id, katbez, typ_id,
	dlt_id, dltbez, kont_id, r_sta, s_id ) as
select res.bid, res.pers_id, pers.name,
	res.dlg_id, dl.a_zeit, 
	res.dl_id, tdl.a_zeit, tdl.e_zeit,
	res.a_zeit, res.e_zeit, 
	res.kat_id, bez1.bez, res.typ_id, 
	res.dlt_id, bez2.bez, res.kont_id, res.r_sta, bez1.s_id
from 	reservation res, dienstleistung dl, personen pers, dlg_parts tdl,
	 kategorie kat, dienst_traeger dlt, bezeichnung bez1, bezeichnung bez2
where		dl.dlg_id = res.dlg_id
and   tdl.dl_id = res.dl_id
and   kat.kat_id = res.kat_id
and  (bez1.typ = 16 and bez1.bez_id = kat.bez_id)
and   dlt.dlt_id = res.dlt_id
and  (bez2.typ = 17 and bez2.bez_id = dlt.bez_id)
and   bez1.s_id = bez2.s_id
and   pers.pers_id = res.pers_id ;

/* reservationen nach dln bez 291 */
drop view resdln_view;
create view resdln_view (bid, pers_id, name, teil,
	dl_id, tdl_id, resazeit, resezeit, kat_id, typ_id,
   dlt_id, kont_id, r_sta ) as
select res.bid, res.pers_id, pers.name, res.teil,
	res.dlg_id, res.dl_id, res.a_zeit, res.e_zeit, 
	res.kat_id, res.typ_id, res.dlt_id, res.kont_id, res.r_sta
from 	reservation res, personen pers
where res.pers_id = pers.pers_id;

/* reservationen nach dl bez 292 */
drop view resdl_view;
create view resdl_view (bid, pers_id, teil, dl_id, dl_bez, dl_sid,
	tdl_id, resazeit, resezeit, kat_id, typ_id, dlt_id, kont_id, r_sta ) as
select res.bid, res.pers_id, res.teil, res.dlg_id, dl.bez, dl.s_id,
   res.dl_id, res.a_zeit, res.e_zeit, res.kat_id, res.typ_id, res.dlt_id,
   res.kont_id, res.r_sta
from reservation res, dtg_view dl
where dl.dlg_id = res.dlg_id;


/* akt_detail / aktionen / aktions_typ / aktionsgrp aktionen uebersicht  280 */
drop view akt_detail_view;
create view akt_detail_view (bid, pers_id, dlg_id, dl_id, teil, z_flag,
	akt_id, ord, a_flag, m_flag, a_typ_id, proz) as
select a_det.bid, a_det.pers_id, a_det.dlg_id, a_det.dl_id, a_det.teil,
	a_det.z_flag, a_det.akt_id, a_det.ord, akt.a_flag,
	akt.m_flag, a_typ.a_typ_id, a_typ.proz
from 	akt_detail a_det, aktionen akt, aktions_typ a_typ,
   aktionsgrp agrp
where	a_det.akt_id = agrp.childakt
and   akt.akt_id = agrp.childakt
and	a_det.ord = agrp.ord
and   a_det.parentakt = agrp.parentakt
and	a_det.a_typ_id = a_typ.a_typ_id;

/* kosten_art bezeichnungs view  281 */
drop view kar_view;
create view kar_view (kar_id, bez, s_id, textid) as
select kar.kar_id, bez.bez, bez.s_id, kar.textid
from 	kosten_art kar, bezeichnung bez
where	bez.typ = 43 and bez.bez_id = kar.bez_id;

/* kapa view  284 */
drop view mpv_kapa;
create view mpv_kapa (kat_id, katbez, kat_s_id, tdl_id, tdlbez, tdl_s_id,
pre_id, anz, busy, vpr) as
select k.kat_id, katbez.bez, katbez.s_id, k.tdl_id, tdlbez.bez,
tdlbez.s_id, k.pre_id, k.anz, k.busy, k.vpr
from 	kapa k, bezeichnung katbez, bezeichnung tdlbez
where	katbez.typ = 16 and katbez.bez_id = k.katbez_id and
tdlbez.typ = 26 and tdlbez.bez_id = k.tdlbez_id;


/***************************************************************************/
/* grafik                                                                  */
/***************************************************************************/

/* grafik mit bez und dltbez 282 */
drop view gra_view;
create view gra_view (gra_id, bez, dlt_id, dltbez, textid, s_id) as
select gra.gra_id, bez.bez, gra.dlt_id, dltbez.bez, gra.textid, bez.s_id
from graphik gra, bezeichnung bez, dienst_traeger dlt, bezeichnung dltbez
where	bez.typ = 48 and dltbez.typ = 17
and bez.bez_id = gra.bez_id and dlt.dlt_id = gra.dlt_id
and dltbez.bez_id = dlt.bez_id;








/***************************************************************************/
/*                                                                         */
/*  n e w     m p v     v i e w s    w i t h   date !!!                    */
/*                                                                         */
/* these views are not supported by to classic code !!                     */
/* for every new application developed, please use these new views !       */
/***************************************************************************/

/* mpv_sprache sprachen */
drop view mpv_sprache;
create view mpv_sprache(s_id, bez, bezsprid, dialog, sysbez) as
select spr.s_id, bez.bez, bez.s_id, spr.dialog, spr.sysbez
from 	sprachen spr, bezeichnung bez
where	bez.typ = 1 and bez.bez_id = spr.bez_id;

/* mpv_status statuswerte */
drop view mpv_status;
create view mpv_status (sta_id, abk, sta, bez, s_id, kond, typ) as
select sta.sta_id, sta.abk, sta.sta, bez.bez, bez.s_id, sta.kond, sta.typ
from 	status_werte sta, bezeichnung bez
where	bez.typ = sta.typ and bez.bez_id = sta.bez_id;

/* mpv_saison saison */
drop view mpv_saison;
create view mpv_saison (sai_id, bez, s_id, von, bis, textid) as
select 
	sai.sai_id, 
	bez.bez, 
	bez.s_id,
	todate(sai.von),
	todate(sai.bis),
	sai.textid
from 	saison sai, bezeichnung bez
where	bez.typ = 9 and bez.bez_id = sai.bez_id;


/* saison detail view gegliedert in programme, arrangements, dls */
drop view mpv_saidet;
create view mpv_saidet (sai_id, saibez, prg_id, prgbez, arr_id, arrbez, a_dat, teil, prio, dl_id, dlbez, a_zeit, s_id) as
select sai.sai_id, saibez.bez, prg.prg_id, prgbez.bez, arr.arr_id, arrbez.bez, todate(arr.a_dat), ad.teil, ad.prio, dl.dlg_id, dlbez.bez, todate(dl.a_zeit), dlbez.s_id
from saison sai, bezeichnung saibez, programm prg, bezeichnung prgbez, arrangement arr, bezeichnung arrbez, arr_dlg ad, dienstleistung dl, bezeichnung dlbez
where (sai.sai_id = arr.sai_id)
 and (saibez.bez_id = sai.bez_id and saibez.typ = 9)
 and (prg.prg_id = arr.prg_id)
 and (prgbez.bez_id = prg.bez_id and prgbez.typ = 29)
 and  (arr.arr_id = ad.arr_id and dl.dlg_id = ad.dlg_id)
 and (arrbez.bez_id = arr.bez_id and arrbez.typ = 30)
  and (dl.bez_id = dlbez.bez_id and dlbez.typ = 27);


/* mpv_land land  */
drop view mpv_land;
create view mpv_land (land_id, bez, s_id, krzl, haupt_ort,
 haupt_spr, haupt_whr, textid, vat) as
select land.land_id, bez.bez, bez.s_id, land.krzl, land.haupt_ort,
 land.haupt_spr, land.haupt_whr, land.textid, land.vat
from 	land, bezeichnung bez
where	bez.typ = 10 and bez.bez_id = land.bez_id;

/* mpv_ort ort  */
drop view mpv_ort;
create view mpv_ort (ort_id, bez, s_id, krzl, landbez, landbezs_id,
 textid, zeitver, koord1, koord2) as
select ort.ort_id, bez.bez, bez.s_id, ort.krzl, landbez.bez, landbez.s_id,
 ort.textid, ort.zeitver, ort.koord1, ort.koord2
from 	ort, land, bezeichnung bez, bezeichnung landbez
where	(bez.typ = 11 and bez.bez_id = ort.bez_id)
and (ort.land_id = land.land_id)
and (landbez.typ = 10 and landbez.bez_id = land.bez_id);

/* mpv_whr waehrung  */
drop view mpv_whr;
create view mpv_whr (whr_id, bez, s_id, krzl, status, textid) as
select waehrung.whr_id, bez.bez, bez.s_id, waehrung.krzl, waehrung.status,
 waehrung.textid
from 	waehrung, bezeichnung bez
where	bez.typ = 12 and bez.bez_id = waehrung.bez_id;

/* mpv_lw waehrungskurse  */
drop view mpv_lw;
create view mpv_lw (land_id, landbez, landbezs_id, whr_id, whrbez,
 whrbezs_id, kurs_typ, a_kurs, v_kurs) as
select lw.land_id, landbez.bez, landbez.s_id, lw.whr_id, whrbez.bez,
 whrbez.s_id, lw.kurs_typ, lw.a_kurs, lw.v_kurs
from 	land_whr lw, bezeichnung landbez, bezeichnung whrbez, land, waehrung
where	(lw.land_id = land.land_id and lw.whr_id = waehrung.whr_id)
and (landbez.typ = 10 and landbez.bez_id = land.bez_id)
and (whrbez.typ = 12 and whrbez.bez_id = waehrung.bez_id);

/* mpv_kunden nur personen die kunden sind mit kundenteil */
drop view mpv_kunden;
create view mpv_kunden (kun_id, name, ort, s_id, sta_id, textid, kant,
  tel, fax, tlx, konto, leiter, attr1, attr2, k_typ_id, land_id, whr_id) as
select pers.pers_id, pers.name, adr.ort, pers.s_id, pers.sta_id, pers.textid,
  adr.kant, kun.tel, kun.fax, kun.tlx, kun.konto, kun.leiter, kun.attr1,
  kun.attr2, kun.k_typ_id, adr.land_id, kun.whr_id
from personen pers, kunden kun, persadr adr
where pers.pers_typ = 2 and kun.pers_id = pers.pers_id
and   adr.haupt_flag = 1 and adr.pers_id = pers.pers_id;

/* mpv_dln nur personen die private sind mit reisendenteil */
drop view mpv_dln;
create view mpv_dln (dln_id, name, vor, ort, s_id, sta_id, textid, rkr_id,
  sex, ext_txt, land_id, age, passnr, attr1, attr2) as
select pers.pers_id, pers.name, dln.vor, adr.ort, pers.s_id, pers.sta_id,
  pers.textid, dln.rkr_id, dln.sex, dln.textid, adr.land_id, dln.age,
  dln.passnr, dln.attr1, dln.attr2
from personen pers, reisender dln, persadr adr
where pers.pers_typ = 1 and dln.pers_id = pers.pers_id
and   adr.haupt_flag = 1 and adr.pers_id = pers.pers_id;

/* dl-nehmer typ bezeichnungs view */
drop view mpv_rkr;
create view mpv_rkr (rkr_id, bez, s_id, textid, dlncode, vonalter,
  bisalter) as
select rkr.rkr_id, bez.bez, bez.s_id, rkr.textid, rkr.dlncode, rkr.vonalter,
  rkr.bisalter
from 	reisender_typ rkr, bezeichnung bez
where	bez.typ = 35 and	bez.bez_id = rkr.bez_id;

/* traeger_typ bezeichnungs view (parent/child)  */
drop view mpv_ttyp;
create view mpv_ttyp (spr, id, bez, hid, hbez) as
select bez_a.s_id, dltt_a.typ_id, bez_a.bez,	dltt_a.h_typ_id, bez_b.bez
from traeger_typ dltt_a, bezeichnung bez_a,
	traeger_typ dltt_b, bezeichnung bez_b
where	(bez_a.typ = 15 and	bez_b.typ = 15)
	and (dltt_a.bez_id = bez_a.bez_id and	dltt_b.bez_id = bez_b.bez_id)
	and dltt_a.h_typ_id = dltt_b.typ_id
	and bez_a.s_id = bez_b.s_id;

/* kategorie bezeichnungs view */
drop view mpv_kat;
create view mpv_kat (kat_id, bez, s_id, h_kat_id,
  typ_id, ga, textid) as
select kat.kat_id, bez.bez, bez.s_id, kat.h_kat_id,
  kat.typ_id, kat.ga, kat.textid
from 	kategorie kat, bezeichnung bez
where	bez.typ = 16 and bez.bez_id = kat.bez_id;

/* dienst_traeger mit bez und h_bez (prarent/child) */
drop view mpv_traeger;
create view mpv_traeger (spr, typ, id, bez, hid, host) as
select bez_a.s_id, dlt.typ_id, dlt.dlt_id, bez_a.bez,
	dlt.h_dlt_id, dlt.host_id
from bezeichnung bez_a, dienst_traeger dlt
where	(bez_a.bez_id = dlt.bez_id)
and (bez_a.typ = 17);

/* dienst_traeger mit bez */
drop view mpv_dlt;
create view mpv_dlt (dlt_id, bez, s_id, kat_id, h_dlt_id,
  host_id, typ_id, textid, stufe) as
select dlt.dlt_id, bez.bez, bez.s_id, dlt.kat_id, dlt.h_dlt_id,
  dlt.host_id, dlt.typ_id, dlt.textid, dlt.stufe
from 	dienst_traeger dlt, bezeichnung bez
where	bez.typ = 17 and dlt.bez_id = bez.bez_id;

/* aktionen mit bez  (parent/child) */
drop view mpv_akt;
create view mpv_akt (id, bez, ubez, ord, spr) as
select child.childakt, bchild.bez, bparent.bez, child.ord, bchild.s_id
from 	aktionsgrp child, bezeichnung bchild, aktionen aktchild,
  bezeichnung bparent, aktionen aktparent
where	(bchild.typ = 21 and	bparent.typ = 21)
	and	aktchild.akt_id = child.childakt
	and	bchild.bez_id = aktchild.bez_id
	and	aktparent.akt_id = child.parentakt
	and	bparent.bez_id = aktparent.bez_id
	and 	bchild.s_id = bparent.s_id;

/* angebot bezeichnungs view */
drop view mpv_angebot;
create view mpv_angebot (art_id, bez, s_id, textid) as
select art.art_id, bez.bez, bez.s_id, art.textid
from 	angebots_typ art, bezeichnung bez
where	bez.typ = 18 and bez.bez_id = art.bez_id;

/* dienst_angebot mit bez */
drop view mpv_dla;
create view mpv_dla (dla_id, h_dla_id, ord, dlt_id, bez, s_id,
  akt_id, ort, art_id, dau, textid, von, nach) as
select dla.dla_id, dla.h_dla_id, dla.ord, dla.dlt_id, bez.bez, bez.s_id,
  dla.akt_id, dla.ort, dla.art_id, dla.dau, dla.textid,
  todate(dla.von), todate(dla.nach)
from 	dienst_angebot dla, bezeichnung bez
where	bez.typ = 23 and bez.bez_id = dla.bez_id;

/* dlg_part teildienstleistung */
drop view mpv_tdl;
create view mpv_tdl (dl_id, h_dl_id, dla_id, bez, s_id, ord,
  a_zeit, e_zeit, res_f, kid, konto, textid, sai_id) as
select dlg.dl_id, dlg.h_dl_id, dlg.dla_id, bez.bez, bez.s_id, dlg.ord,
  todate(dlg.a_zeit), todate(dlg.e_zeit), dlg.res_f, dlg.kid, dlg.konto,
  dlg.textid, dlg.sai_id
from 	dlg_parts dlg, bezeichnung bez
where	bez.typ = 26 and bez.bez_id = dlg.bez_id;

/* dl_dlg view zusammensetzung dienstleistung mit teil-dls */
drop view mpv_dl_tdl;
create view mpv_dl_tdl (dlg_id, start_zeit, dl_id, bez, a_zeit, e_zeit,
  ord, res_f, s_id) as
select dl.dlg_id, todate(dl.a_zeit), dlg.dl_id, bez.bez, todate(dlg.a_zeit), todate(dlg.e_zeit),
  dldlg.ord, dlg.res_f, bez.s_id
from dienstleistung dl, dlg_parts dlg, dlg_dlg dldlg, bezeichnung bez
where (dl.dlg_id = dldlg.dlg_id and dlg.dl_id = dldlg.dl_id)
  and (dlg.bez_id = bez.bez_id and bez.typ = 26);

/* dienstleistung bezeichnungs view */
drop view mpv_dl;
create view mpv_dl (dlg_id, bez, s_id, textid, sai_id, a_zeit, akt_id) as
select dtg.dlg_id, bez.bez, bez.s_id, dtg.textid,
  dtg.sai_id, todate(dtg.a_zeit), dtg.akt_id
from 	dienstleistung dtg, bezeichnung bez
where	bez.typ = 27 and	bez.bez_id = dtg.bez_id;

/* routen view aus dienstleistungen */
drop view mpv_routen;
create view mpv_routen (dlg_id, bez, s_id, von, nach) as
select dlg.dlg_id, bez.bez, bez.s_id, von.krzl, nach.krzl
from dienstleistung dlg, bezeichnung bez, dlg_dlg ddv,
  dlg_dlg ddn, dlg_parts dlv, dlg_parts dln, dienst_angebot dav,
  dienst_angebot dan, ort von, ort nach
where ddv.ord =	(select min(ord)
							from   dlg_dlg a
							where  a.dlg_id = dlg.dlg_id)
and ddv.dlg_id = dlg.dlg_id
and ddn.ord =	(select max(ord)
							from   dlg_dlg b
							where  b.dlg_id = dlg.dlg_id)
and ddn.dlg_id = dlg.dlg_id
and bez.typ=27
and bez.bez_id = dlg.bez_id
and dlv.dl_id = ddv.dl_id
and dln.dl_id = ddn.dl_id
and dav.dla_id = dlv.dla_id
and dan.dla_id = dln.dla_id
and von.ort_id = dav.von
and nach.ort_id = dan.nach;


/* arr_dl view zusammensetzung arrangement mit dienstleistungen */
drop view mpv_arr_dl;
create view mpv_arr_dl (arr_id, a_dat, dlg_id, bez, a_zeit, teil,
  prio, akt_id, s_id) as
select arr.arr_id, todate(arr.a_dat), dl.dlg_id, bez.bez, todate(dl.a_zeit), ad.teil,
  ad.prio, dl.akt_id, bez.s_id
from arrangement arr, arr_dlg ad, dienstleistung dl, bezeichnung bez
where (arr.arr_id = ad.arr_id and dl.dlg_id = ad.dlg_id)
  and (dl.bez_id = bez.bez_id and bez.typ = 27);

/* arrangement bezeichnungs view */
drop view mpv_arr;
create view mpv_arr (arr_id, bez, s_id, a_dat,
  prg_id, textid, sai_id) as
select arr.arr_id, bez.bez, bez.s_id, todate(arr.a_dat),
  arr.prg_id, arr.textid, arr.sai_id
from 	arrangement arr, bezeichnung bez
where	bez.typ = 30 and	bez.bez_id = arr.bez_id;

/* arr_dls  will be obsolete with version 6.0 */
drop view mpv_arr_dlg;
create view mpv_arr_dlg (arr_id, teil, prio, dlg_id, dl_id, ord, a_zeit,
	res_f, bez, bez1, s_id, dtg_zeit) as
select arr_dlg.arr_id, arr_dlg.teil, arr_dlg.prio, arr_dlg.dlg_id,
	dlg_parts.dl_id, dlg_dlg.ord, todate(dlg_parts.a_zeit),
	dlg_parts.res_f, a.bez, b.bez, a.s_id, todate(dienstleistung.a_zeit)
from	arr_dlg, dlg_dlg, dlg_parts,
	dienstleistung, bezeichnung a, bezeichnung b
where	arr_dlg.dlg_id = dlg_dlg.dlg_id
	and	arr_dlg.dlg_id = dienstleistung.dlg_id
	and	dlg_parts.dl_id = dlg_dlg.dl_id
	and	a.typ = 26
	and	a.bez_id=dlg_parts.bez_id
	and	b.typ = 27
	and	b.bez_id=dienstleistung.bez_id
	and	a.s_id = b.s_id;


/* kontingent uebersicht ï¿½ber zusammensetzung des kontingents */
drop view mpv_kon;
create view mpv_kon (kont_id, bez, s_id, hostkont_id, kunden_id,
  opt_dat, ref, sai_id, textid) as
select kon.kont_id, bez.bez, bez.s_id, kon.hostkont_id, kon.kunden_id,
  kon.opt_dat, kon.ref, kon.sai_id, kon.textid
from 	kontingent kon, bezeichnung bez
where	bez.typ = 39 and bez.bez_id = kon.bez_id;

/* koncheck check free space in a kont */
drop view mpv_koncheck;
create view mpv_koncheck (hostkont_id, kont_id, kat_id, dlt_id, anz, busy) as
select kon.hostkont_id, kon.kont_id, kd.kat_id, kd.dlt_id, kd.anz, kd.busy
from kontingent kon, kont_detail kd
where kd.kont_id = kon.kont_id;

/* reservation / dienstleistung  uebersicht */
drop view mpv_res_dl;
create view mpv_res_dl (bid, pers_id, name,
	dl_id, dlazeit,
	tdl_id, tdlazeit, tdlezeit, 
	resazeit, resezeit, 
	kat_id, katbez, typ_id,
	dlt_id, dltbez, kont_id, r_sta, s_id ) as
select res.bid, res.pers_id, pers.name,
	res.dlg_id, todate(dl.a_zeit), 
	res.dl_id, todate(tdl.a_zeit), todate(tdl.e_zeit),
	todate(res.a_zeit), todate(res.e_zeit), 
	res.kat_id, bez1.bez, res.typ_id, 
	res.dlt_id, bez2.bez, res.kont_id, res.r_sta, bez1.s_id
from 	reservation res, dienstleistung dl, personen pers, dlg_parts tdl,
	 kategorie kat, dienst_traeger dlt, bezeichnung bez1, bezeichnung bez2
where		dl.dlg_id = res.dlg_id
	and   tdl.dl_id = res.dl_id
	and   kat.kat_id = res.kat_id
	and  (bez1.typ = 16 and bez1.bez_id = kat.bez_id)
	and   dlt.dlt_id = res.dlt_id
	and  (bez2.typ = 17 and bez2.bez_id = dlt.bez_id)
	and   bez1.s_id = bez2.s_id
	and   pers.pers_id = res.pers_id ;

/* reservationen nach dln bez */
drop view mpv_resdln;
create view mpv_resdln (bid, pers_id, name, teil,
	dl_id, tdl_id, resazeit, resezeit, kat_id, typ_id,
   dlt_id, kont_id, r_sta ) as
select res.bid, res.pers_id, pers.name, res.teil,
	res.dlg_id, res.dl_id, todate(res.a_zeit), todate(res.e_zeit), 
	res.kat_id, res.typ_id, res.dlt_id, res.kont_id, res.r_sta
from 	reservation res, personen pers
where res.pers_id = pers.pers_id;

/* reservationen nach dl bez */
drop view mpv_resdl;
create view mpv_resdl (bid, pers_id, teil, dl_id, dl_bez, dl_sid,
	tdl_id, resazeit, resezeit, kat_id, typ_id, dlt_id, kont_id, r_sta ) as
select res.bid, res.pers_id, res.teil, res.dlg_id, dl.bez, dl.s_id,
   res.dl_id, todate(res.a_zeit), todate(res.e_zeit), res.kat_id, res.typ_id, res.dlt_id,
   res.kont_id, res.r_sta
from reservation res, mpv_dl dl
where dl.dlg_id = res.dlg_id;


/* akt_detail / aktionen / aktions_typ / aktionsgrp aktionen uebersicht */
drop view mpv_akt_detail;
create view mpv_akt_detail (bid, pers_id, dlg_id, dl_id, teil, z_flag,
	akt_id, ord, a_flag, m_flag, a_typ_id, proz) as
select a_det.bid, a_det.pers_id, a_det.dlg_id, a_det.dl_id, a_det.teil,
	a_det.z_flag, a_det.akt_id, a_det.ord, akt.a_flag,
	akt.m_flag, a_typ.a_typ_id, a_typ.proz
from 	akt_detail a_det, aktionen akt, aktions_typ a_typ,
   aktionsgrp agrp
where	a_det.akt_id = agrp.childakt
	and   akt.akt_id = agrp.childakt
	and	a_det.ord = agrp.ord
	and   a_det.parentakt = agrp.parentakt
	and	a_det.a_typ_id = a_typ.a_typ_id;

/* kosten_art bezeichnungs view */
drop view mpv_kar;
create view mpv_kar (kar_id, bez, s_id, textid) as
select kar.kar_id, bez.bez, bez.s_id, kar.textid
from 	kosten_art kar, bezeichnung bez
where	bez.typ = 43 and bez.bez_id = kar.bez_id;

/* kapadet view  */
drop view mpv_kapadet;
create view mpv_kapadet (kat_id, katbez, kat_s_id, tdl_id, tdlbez, a_zeit,
e_zeit, tdl_s_id, pre_id, anz, busy, vpr) as
select k.kat_id, katbez.bez, katbez.s_id, k.tdl_id, tdlbez.bez, todate(tdl.a_zeit),
todate(tdl.e_zeit), tdlbez.s_id, k.pre_id, k.anz, k.busy, k.vpr
from 	kapa k, bezeichnung katbez, bezeichnung tdlbez, dlg_parts tdl
where	(katbez.typ = 16 and katbez.bez_id = k.katbez_id)
and (tdlbez.typ = 26 and tdlbez.bez_id = k.tdlbez_id)
and (k.tdl_id = tdl.dl_id);

/* grafik mit bez und dltbez 282 */
drop view mpv_gra;
create view mpv_gra (gra_id, bez, dlt_id, dltbez, textid, s_id) as
select gra.gra_id, bez.bez, gra.dlt_id, dltbez.bez, gra.textid, bez.s_id
from graphik gra, bezeichnung bez, dienst_traeger dlt, bezeichnung dltbez
where	bez.typ = 48 and dltbez.typ = 17
 and bez.bez_id = gra.bez_id and dlt.dlt_id = gra.dlt_id
 and dltbez.bez_id = dlt.bez_id;

/* mpv_prg programm *** gr, 29/09/1975 *** */
drop view mpv_prg;
create view mpv_prg (prg_id, bez, s_id, textid, sai_id) as
select prg.prg_id, bez.bez, bez.s_id, prg.textid, prg.sai_id
from 	programm prg, bezeichnung bez
where	bez.typ = 29 and bez.bez_id = prg.bez_id;

commit work;

/***************************************************************************/
/*                                                                         */
/*  n e w     v i e w s   used by     m p    b o o k e r    2 0 0 0        */
/*                                                                         */
/***************************************************************************/

/* to be migrated from oracle view mpcc_preferences */
/* same with mpv_users */

/* view used to search a service by season, starting or arrival place, date or offre type */
/* error on mp2000_arrangement */
/* drop view mp2000_dienstleistung; */

/* view used to search a arrangement by season, starting or arrival place, date or catalog */
/* error on mp2000_arrangement */


/* view used to help oracle report */
drop view mpv_buchung;
create view mpv_buchung (d_bid, bid, ref, arr_id, kid, sach, bchst, anw,
b_dat, m_dat, mapo_dat, mapo_opt_bst, opt_bst, mapo_opt_kid, opt_kid, sta, ast,
sai_id, k_id, history, textid) as
select b.d_bid, b.bid, b.ref, b.arr_id, b.kid,
b.sach, p.bchst, b.anw, todate(b.b_dat), todate(b.m_dat),
b.m_dat, b.opt_bst, todate(b.opt_bst), b.opt_kid, todate(b.opt_kid),
b.sta, b.ast, b.sai_id, b.k_id, b.history, b.textid
from buchung b, mp_profil p
where b.anw = p.mpid;

/*drop view mpv_kontingent;
create view mpv_kontingent (kont_id, hostkont_id, kontingent,
hostkontingent, kat_id, kategory, kont_anz, kont_busy,
host_anz, host_busy) as
select kontin.kont_id, hostk.hostkont_id, kontin.bez, hostk.bez,
hkd.kat_id, hkkat.bez, kd.anz, kd.busy, hkd.anz, hkd.busy
from
(select kon.*, bez.bez  
from host_kont kon, bezeichnung bez  
where bez.typ = 38 and bez.bez_id = kon.bez_id and bez.s_id=25) hostk,  
(select kon.*, bez.bez
from kontingent kon, bezeichnung bez  
where bez.typ = 39 and bez.bez_id = kon.bez_id and bez.s_id=25) kontin,  
kont_detail kd, kont_detail hkd, mpv_kat hkkat  
where kontin.kont_id >0 and kontin.hostkont_id=hostk.hostkont_id  
and kd.kont_id=kontin.kont_id and hkd.hostkont_id=hostk.hostkont_id  
and hkd.kat_id=hkkat.kat_id and hkkat.s_id=25  
and hkd.kont_id=-1 and kd.kat_id=hkd.kat_id;
*/
/* error on mpv_reisender */
/* drop view mpv_reisender; */

/* error on mpv_reservation */
/* drop view mpv_reservation; */

/*
drop view mp2000_preis;
create view mp2000_preis as (select
-- reservation info
        r.bid, r.pers_id, rei.rkr_id, r.teil, r.dlg_id, hp.dl_id, r.r_sta, r.kat_id, r.kont_id, hp.kid, hp.res_f zeittyp, hp.a_zeit, hp.e_zeit, hp.dla_id,
-- price
				p.pre_id 					preis_id, p.whr_id local_whr_id, p.vpr local_preis, p.apr local_cost,
        whrland.land_id 	whr_land_id,        whrland.haupt_whr whr_id,
        round(p.vpr*plw.v_kurs,2) 	whr_preis, round(p.apr*plw.v_kurs,2) whr_cost,
        plw.land_id lwchg_id,
-- reductions on travel
				nvl(dla_red.komm_id, -1) dla_red_id, nvl(dla_red.satz, 0) dla_red,
				nvl(dlg_red.komm_id, -1) dlg_red_id, nvl(dlg_red.satz, 0) dlg_red,
				nvl(kont_red.komm_id, -1) kont_red_id, nvl(kont_red.satz, 0) kont_red,
				round(p.vpr*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100),2) red_price,
-- reductions on folder
				nvl(kun_red.komm_id, -1) kun_red_id, nvl(kun_red.satz, 0) kun_red,
				nvl(kol_red.komm_id, -1) kol_red_id, nvl(kol_red.satz, 0) kol_red,
				nvl(bid_red.komm_id, -1) bid_red_id, nvl(bid_red.satz, 0) bid_red,
				round(p.vpr*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100)
												*(1-nvl(kun_red.satz, 0)/100)
												*(1-nvl(kol_red.satz, 0)/100)
												*(1-nvl(bid_red.satz, 0)/100),2) whr_excl,
-- vat
				nvl(vat.komm_id, -1)                             vat_id,
				landvat.land_id                                  vat_land_id,
				decode(vat.komm_id, null, landvat.vat, vat.satz) vat,
				round(p.vpr*plw.v_kurs*(1-nvl(dla_red.satz, 0)/100)
												*(1-nvl(dlg_red.satz, 0)/100)
												*(1-nvl(kont_red.satz, 0)/100)
												*(1-nvl(kun_red.satz, 0)/100)
												*(1-nvl(kol_red.satz, 0)/100)
												*(1-nvl(bid_red.satz, 0)/100)
												*(1+decode(vat.komm_id, null, landvat.vat, vat.satz)/100),2) whr_inkl
from
		 root.reservation r, root.dlg_dlg dd, root.dlg_parts dp, root.dlg_parts hp, root.dienst_angebot a,
		 root.reisender rei,root.preis p,
		 root.kommission dla_red, root.kommission dlg_red, root.kommission kont_red,
		 root.kommission kun_red, root.komm_detail kun_det,
		 root.kommission kol_red, root.komm_detail kol_det,
		 root.kommission bid_red,
		 root.land_whr plw, root.land whrland, root.land landvat, root.kommission vat
-- get dl_id, dla_id
where r.r_sta <> 20000
and r.dlg_id = dd.dlg_id
and dd.dl_id = dp.dl_id
and ((hp.dl_id = dp.h_dl_id and dp.h_dl_id<>-1)
    or (hp.dl_id = dp.dl_id and dp.h_dl_id=-1))
and hp.dla_id = a.dla_id
-- get traveler type
and rei.pers_id = r.pers_id
-- get price
and (p.rkr_id = rei.rkr_id or p.rkr_id = -1)
and (p.kat_id = r.kat_id or p.kat_id = -1)
and (p.dl_id  = hp.dl_id or p.dla_id = a.dla_id)
and p.glt =(select max(allp.glt)
			      from root.preis allp
			      where(allp.rkr_id = rei.rkr_id or allp.rkr_id = -1)
						and (allp.kat_id = r.kat_id or allp.kat_id = -1)
						and (allp.dl_id = hp.dl_id or allp.dla_id = a.dla_id)
						and  allp.glt <= hp.a_zeit )
-- get reduction
and dla_red.komm_typ(+) = 1 and dla_red.satz_art(+) = 1 and hp.dla_id = dla_red.dla_id(+)
and dlg_red.komm_typ(+) = 2   and dlg_red.satz_art(+) = 1 and r.dlg_id = dlg_red.dl_id(+)
and kont_red.komm_typ(+) = 3	and kont_red.satz_art(+) = 1 and  r.kont_id = kont_red.kont_id(+)
and kun_red.komm_typ(+) = 5 and kun_red.satz_art(+) = 1
								and kun_det.komm_id = kun_red.komm_id (+) and kun_det.bid(+) = r.bid
and kol_red.komm_typ(+) = 6 and kol_red.satz_art(+) = 1
								and kol_det.komm_id = kol_red.komm_id (+) and kol_det.bid (+)= r.bid
and bid_red.komm_typ (+)= 7  and bid_red.satz_art (+)= 1  and r.bid = bid_red.bid(+)
-- get change rate
and p.whr_id = plw.whr_id and plw.kurs_typ = 2
and plw.land_id = whrland.land_id
and plw.von_dat = (select nvl(max(von_dat),-1)
			 						from root.land_whr
			 						where kurs_typ = plw.kurs_typ
			 						and land_id    = plw.land_id
			 						and whr_id     = plw.whr_id )
-- get vat
	and vat.dla_id(+) 	= hp.dla_id and vat.komm_typ(+) = 4 and vat.satz_art(+) = 1
-- make an union to have fix reductions on same folder (join done at view call)
) union (select 
-- reservation info
        red.bid, -1 pers_id, -1 rkr_id, 1 teil, -1 dlg_id, -1 dl_id, 11000 r_sta, -1 kat_id, -1 kont_id, -1 kid, -1 zeittyp, -1 a_zeit, -1 e_zeit, -1 dla_id,
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
				landvat.land_id vat_land_id,
				landvat.vat vat,
				-red.satz*(1+landvat.vat/100) whr_inkl
from
		root.kommission red, root.land whrland,   root.land landvat
where red.satz_art = 2	and red.komm_typ = 8);
*/

/*************************************************************************/
/* views for reports                                                     */
/*************************************************************************/
/*
drop view mp2000_report8f;
create view mp2000_report8f as select
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
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
substr(dl1.code,1,6) code,
rtrim(dl1.code) fullcode,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit),
todate(dlgp.e_zeit),
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
nach_ort_bez.bez nachort
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte,
root.dienst_angebot dla,
root.bezeichnung dlabez,
root.mpv_angebot angebottyp,
root.ort von_ort,
root.bezeichnung von_ort_bez,
root.ort nach_ort,
root.bezeichnung nach_ort_bez
where
reser.r_sta=2000
and reser.kont_id=-1
and rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25
and dla.dla_id=dlgp.dla_id
and dlabez.typ = 23
and dlabez.bez_id = dla.bez_id
and dlabez.s_id = 25
and dla.art_id=angebottyp.art_id
and angebottyp.s_id=25
and von_ort.ort_id=dla.von
and von_ort_bez.bez_id=von_ort.bez_id
and von_ort_bez.typ=11
and von_ort_bez.s_id=25
and nach_ort.ort_id=dla.nach
and nach_ort_bez.bez_id=nach_ort.bez_id
and nach_ort_bez.typ=11
and nach_ort_bez.s_id=25;

drop view mp2000_report8c;
create view mp2000_report8c as select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
root.getprice(buch.bid,rsd.pers_id,reser.teil) price,
reser.teil,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name)
name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.email,
amxt.confirmationto,
reser.pers_id,
substr(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
amxt.company dcomp,
amxt.fax dfax,
amxt.confirmationto dattn,
dlabez.bez angebot,
angebottyp.bez angebottyp,
angebottyp.art_id angebottyp_id,
von_ort.ort_id vonort_id,
von_ort_bez.bez vonort,
nach_ort.ort_id nachort_id,
nach_ort_bez.bez nachort
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte,
root.dienst_angebot dla,
root.bezeichnung dlabez,
root.mpv_angebot angebottyp,
root.ort von_ort,
root.bezeichnung von_ort_bez,
root.ort nach_ort,
root.bezeichnung nach_ort_bez
where
reser.r_sta=9000
and von_ort.ort_id=dla.von
and von_ort_bez.bez_id=von_ort.bez_id
and von_ort_bez.typ=11
and von_ort_bez.s_id=25
and nach_ort.ort_id=dla.nach
and nach_ort_bez.bez_id=nach_ort.bez_id
and nach_ort_bez.typ=11
and nach_ort_bez.s_id=25
and rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and kat.s_id=25
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and
dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and saison.s_id=25
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25
and dla.dla_id=dlgp.dla_id
and dlabez.typ = 23
and dlabez.bez_id = dla.bez_id
and dlabez.s_id = 25
and dla.art_id=angebottyp.art_id
and angebottyp.s_id=25;
*/

/*
drop view mp2000_report9a;
create view mp2000_report9a as select
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
bezk.bez kontingent, 
bezhk.bez hostkontingent,
hostk.hostkont_id,
hkd.kat_id,
kd.anz kont_anz,
kd.busy kont_busy,
hkd.anz host_anz,
hkd.busy host_busy,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
reser.pers_id,
substr(dl1.code,1,6) code,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.mpv_saison saison,
root.host_kont hostk,
root.kontingent kontin,
root.kont_detail kd,
root.kont_detail hkd,
bezeichnung bezk,
bezeichnung bezhk
where
reser.kont_id>-1
and reser.r_sta<20000
and rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and kontin.hostkont_id=hostk.hostkont_id
and kd.kont_id=kontin.kont_id
and hkd.hostkont_id=hostk.hostkont_id
and hkd.kont_id=-1
and kd.kat_id=hkd.kat_id
and kontin.kont_id=reser.kont_id
and kd.kat_id=reser.kat_id
and	bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25
and	bezhk.typ = 38 and bezhk.bez_id = hostk.bez_id and bezhk.s_id=25;

drop view mp2000_report8d;
create view mp2000_report8d as select
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
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
substr(dl1.code,1,6) code,
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
rtrim(dl1.code) fullcode,
nach_ort_bez.bez nachort
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte,
root.dienst_angebot dla,
root.bezeichnung dlabez,
root.mpv_angebot angebottyp,
root.ort von_ort,
root.bezeichnung von_ort_bez,
root.ort nach_ort,
root.bezeichnung nach_ort_bez
where
rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25
and reser.kont_id>-1
and reser.r_sta=3000
and dla.dla_id=dlgp.dla_id
and dlabez.typ = 23
and dlabez.bez_id = dla.bez_id
and dlabez.s_id = 25
and dla.art_id=angebottyp.art_id
and angebottyp.s_id=25
and von_ort.ort_id=dla.von
and von_ort_bez.bez_id=von_ort.bez_id
and von_ort_bez.typ=11
and von_ort_bez.s_id=25
and nach_ort.ort_id=dla.nach
and nach_ort_bez.bez_id=nach_ort.bez_id
and nach_ort_bez.typ=11
and nach_ort_bez.s_id=25;

drop view mp2000_report8e;
create view mp2000_report8e as select
buch.ref buchung,
buch.bid bid,
kadr2.name destname,
kadr2.fax destfax,
rtrim(saison.bez) saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name)
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
substr(dl1.code,1,6) code,
rtrim(dl1.code) grcode
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte
where
reser.r_sta<20000
and rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and
dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25;

create or replace view "root"."mp2000_report8g" as select
buch.ref buchung,
amxt.company,
amxt.teamref,
kadr2.name destname,
kadr2.fax destfax,
rtrim(saison.bez) saison,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
reser.pers_id,
substr(dl1.code,1,6) code,
texte.textid noticeid,
texte.text notice,
buch.bid
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte
where
rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25
and (reser.r_sta=10001 or reser.r_sta=4001);

drop view mp2000_report8h;
create view mp2000_report8h as select
buch.ref buchung,
kadr2.name destname,
kadr2.fax destfax,
saison.bez saison,
rtrim(kadr.name) hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
rtrim(kadr.ort)  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
dl1.a_dzeit ci_date, 
dl1.e_dzeit co_date,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
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
root.mpv_reservation reser,
root.mpv_reisender rsd,
root.buchung buch,
root.mpv_kat kat,
root.mp2000_dienstleistung dl1,
root.mpv_dlt dlt,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.amexcotexte amxt,
root.mpv_saison saison,
(select * from root.bezeichnung
where (typ=1112 or typ=1108)
and s_id=25) statusbez
where
rsd.pers_id=reser.pers_id
and reser.r_sta<20000
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dl1.dlg_id=reser.dlg_id
and dl1.h_dl_id=dlgp.dl_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and dlt.dlt_id=dl1.dlt_id
and rsd.textid=amxt.textid
and dl1.sai_id=saison.sai_id
and reser.r_sta=statusbez.bez_id;

drop view mp2000_report9d;
create view mp2000_report9d as select
reser.kont_id,
hostk.hostkont_id,
buch.ref buchung,
buch.bid,
bezk.bez kontingent,
bezhk.bez hostkontingent,
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
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
reser.pers_id,
substr(dl1.code,1,6) code,
rtrim(dl1.code) hotelcode,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.mpv_saison saison,
root.host_kont hostk,
root.kontingent kontin,
bezeichnung bezk,
bezeichnung bezhk
where
rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and kontin.hostkont_id=hostk.hostkont_id
and kontin.kont_id=reser.kont_id
and	bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25
and	bezhk.typ = 38 and bezhk.bez_id = hostk.bez_id and bezhk.s_id=25;

drop view mp2000_report8i;
create view mp2000_report8i as select
buch.ref buchung, buch.bid, preis.kid,
-- client
kadr2.name destname,kadr2.adr1 destadr,kadr2.plz destplz,kadr2.ort destort,kadr2.tel desttel,kadr2.fax destfax,
-- saison
saison.bez saison,
-- supplier
kadr.name hotelname,kadr.adr1 hoteladr,kadr.plz hotelplz,kadr.ort hotelort,kadr.tel hoteltel,kadr.fax hotelfax,
-- traveler
personen.pers_id pers_id,
decode(reisender.sex,2,'mr ','mrs ')||rtrim(reisender.vor)||' '||rtrim(personen.name) name,
amxt.cctype,amxt.ccnumber,amxt.ccvalid,amxt.sharewith,
amxt.company dcomp,amxt.fax dfax,amxt.confirmationto dattn,
texte.textid noticeid,texte.text notice,
-- dienstliestung
substr(dl1.code,1,6) code, rtrim(dl1.code) fullcode,
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
root.buchung buch
,root.mp2000_preis preis
-- category
,root.mpv_kat kat
-- angebot, angebotstyp, ï¿½rte
,root.dienst_angebot dla, root.bezeichnung dlabez, root.mpv_angebot angebottyp
, root.waehrung w
,root.ort vonort, root.bezeichnung vonbez, root.ort nachort, root.bezeichnung nachbez
-- dienstliestung, saison
,root.dienstleistung dl1, root.bezeichnung dllbez, root.mpv_saison saison
-- traveler
, root.personen personen, root.amexcotexte amxt, root.reisender reisender, root.mp_texte texte
-- supplier
,root.mpv_kunadr kadr
-- client
, root.mpv_kunadr kadr2
where
-- price change land and vat land
preis.whr_id = w.whr_id
and preis.r_sta =11000
-- dienstliestung, saison
and preis.dlg_id = dl1.dlg_id and dl1.bez_id = dllbez.bez_id and dllbez.typ=27
and dl1.sai_id = saison.sai_id
-- angebot, angebotstyp, ï¿½rte
and preis.dla_id=dla.dla_id and dlabez.bez_id=dla.bez_id and dlabez.typ=23 and dlabez.s_id=25
and dla.art_id=angebottyp.art_id and angebottyp.s_id=25
and dla.von =vonort.ort_id  and vonbez.bez_id =vonort.bez_id  and vonbez.typ=11  and vonbez.s_id=25
and dla.nach=nachort.ort_id and nachbez.bez_id=nachort.bez_id and nachbez.typ=11 and nachbez.s_id=25
-- traveler
and preis.pers_id = personen.pers_id and personen.pers_id= reisender.pers_id
and personen.textid=amxt.textid and amxt.typ=34 and amxt.s_id=25
and reisender.textid=texte.textid and texte.typ=36 and texte.s_id=25
-- client
and preis.bid = buch.bid and buch.kid = kadr2.pers_id
-- supplier
and preis.kid = kadr.pers_id
-- category
and preis.kat_id = kat.kat_id  ;

drop view mp2000_report8j;
create view mp2000_report8j as select
buch.ref buchung,
buch.bid,
dlgp.kid,
kadr.name hotelname,
kadr.adr1 hoteladr,
kadr.plz  hotelplz,
kadr.ort  hotelort,
kadr.tel  hoteltel,
kadr.fax  hotelfax,
decode(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
kat.bez kategory,
reser.pers_id,
substr(dl1.code,1,6) code,
todate(dlgp.a_zeit) ci_date,
todate(dlgp.e_zeit) co_date,
dllbez.bez dienstleistung,
reser.r_sta,
bezk.bez kontingent,
stabez.bez status
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.mpv_saison saison,
root.bezeichnung dllbez,
root.bezeichnung stabez,
root.kontingent kontin,
bezeichnung bezk
where
rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and dllbez.typ=27
and dllbez.bez_id=dl1.bez_id
and dllbez.s_id=25
and stabez.s_id=25
and (stabez.typ=1112 or stabez.typ=1108)
and stabez.bez_id=reser.r_sta
and kontin.kont_id=reser.kont_id
and bezk.typ = 39 and bezk.bez_id = kontin.bez_id and bezk.s_id=25;

drop view mp2000_report8k;
create view mp2000_report8k as select
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
de(rsd.sex,2,'mr ','mrs ')||rtrim(rsd.vor)||' '||rtrim(rsd.name) name,
kat.bez kategory,
amxt.cctype,
amxt.ccnumber,
amxt.ccvalid,
amxt.sharewith,
amxt.company,
amxt.teamref,
reser.pers_id,
substr(dl1.code,1,6) code,
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
dl1.code fullcode,
nach_ort_bez.bez nachort
from
root.reservation reser,
(select reisender.pers_id, reisender.vor, personen.name,
reisender.sex, reisender.textid ext_txt,
personen.sta_id, personen.textid
from
reisender, personen
where
reisender.pers_id=personen.pers_id) rsd,
root.buchung buch,
root.mpv_kat kat,
root.dienstleistung dl1,
root.dlg_parts dlp,
root.mpv_kunadr kadr,
root.mpv_kunadr kadr2,
root.dlg_parts dlgp,
root.dlg_dlg dlgdlg,
root.amexcotexte amxt,
root.mpv_saison saison,
root.mp_texte texte,
root.dienst_angebot dla,
root.bezeichnung dlabez,
root.mpv_angebot angebottyp,
root.ort von_ort,
root.bezeichnung von_ort_bez,
root.ort nach_ort,
root.bezeichnung nach_ort_bez
where
rsd.pers_id=reser.pers_id
and kat.kat_id= reser.kat_id
and buch.bid=reser.bid
and dlgdlg.dlg_id=reser.dlg_id
and dlp.dl_id=dlgdlg.dl_id
and ( (dlp.h_dl_id=-1 and dlgp.dl_id=dlp.dl_id) or (dlp.h_dl_id>-1 and dlgp.dl_id=dlp.h_dl_id) )
and dl1.dlg_id=reser.dlg_id
and dl1.sai_id=saison.sai_id
and kadr.pers_id=dlgp.kid
and kadr2.pers_id=buch.kid
and rsd.textid=amxt.textid
and amxt.typ=34
and amxt.s_id=25
and rsd.ext_txt=texte.textid
and texte.typ=36
and texte.s_id=25
and reser.r_sta=8502
and dla.dla_id=dlgp.dla_id
and dlabez.typ = 23
and dlabez.bez_id = dla.bez_id
and dlabez.s_id = 1
and dla.art_id=angebottyp.art_id
and angebottyp.s_id=25
and von_ort.ort_id=dla.von
and von_ort_bez.bez_id=von_ort.bez_id
and von_ort_bez.typ=11
and von_ort_bez.s_id=25
and nach_ort.ort_id=dla.nach
and nach_ort_bez.bez_id=nach_ort.bez_id
and nach_ort_bez.typ=11
and nach_ort_bez.s_id=25;


drop view mp2000_report9e;
create view mp2000_report9e as select 
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
root.mp_debitor deb,
root.bezeichnung stabez,
root.kommission komm,
root.bezeichnung vatbez,
root.bezeichnung whrbez,
root.waehrung whr
where stabez.s_id=25
and (stabez.typ=1112 or stabez.typ=1108)
and stabez.bez_id=deb.sta_id
and vatbez.s_id = 25
and vatbez.typ = 44
and komm.komm_id = deb.vat_id
and vatbez.bez_id = komm.bez_id
and whr.whr_id=deb.whr_id
and whrbez.s_id = 25
and whrbez.typ = 12
and whrbez.bez_id=whr.bez_id;
*/

/***************************************************************************/
/* users                                                                  */
/***************************************************************************/
  
/* mpv_users */

/***************************************************************************/
/* mp2000kunden                                                            */
/***************************************************************************/

/* customer view */
drop view mp2000_kunden;
create view mp2000_kunden (pers_id, name, adr1, plz, ort, land, sprache, code,
waehrung, versand, text, textid, s_id, tel, fax, email, web, konto, typ) as
select distinct k.pers_id, p.name, pa.adr1, pa.plz, pa.ort, b1.bez, b2.bez,
k.attr1, b3.bez, b4.bez, txt.text, txt.textid, b1.s_id,
k.tel, k.fax, k.email, k.web, k.konto, b5.bez
from kunden k, personen p, persadr pa, bezeichnung b1, land l,
bezeichnung b2, sprachen s, status_werte st, waehrung w, bezeichnung b3,
bezeichnung b4, mp_texte txt, kunden_typ ku, bezeichnung b5
where k.pers_id=p.pers_id and k.pers_id=pa.pers_id
and k.pers_id<>-1 and p.s_id=b2.bez_id
and l.land_id=pa.land_id and l.bez_id=b1.bez_id
and b1.typ=10 and s.bez_id=b2.bez_id
and b2.typ=1 and b2.bez_id>0
and p.sta_id=st.sta_id and st.bez_id=b4.bez_id
and b4.typ=1111 and w.whr_id=k.whr_id
and w.bez_id=b3.bez_id and b3.typ=12
and p.textid=txt.textid and txt.typ=34
and k.k_typ_id=ku.k_typ_id and ku.bez_id=b5.bez_id
and b5.bez_id>0 and b5.typ=24
and b1.s_id=b2.s_id and b1.s_id=b3.s_id
and b1.s_id=b4.s_id and b1.s_id=b5.s_id;

/* saison view */
drop view mp2000_saison;
create view mp2000_saison (sai_id, bez_id, bez, code, von, bis, text, s_id) as
select distinct s.sai_id, s.bez_id, b.bez,s.code, s.von, s.bis, t.text, b.s_id
from saison s, bezeichnung b, mp_texte t
where s.bez_id = b.bez_id and s.textid=t.textid and t.typ=9
and b.typ=9 and b.bez_id>0;
