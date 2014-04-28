/*D*************************************************************/
/* SQL script: demonstration data                              */
/*             a small set of data to run the examples and     */
/*             tests - some types are already set              */
/*             by def_d_types.sql                              */
/*                                                             */
/* copyright:  yafra.org, 2008, Switzerland                    */
/***************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/def_demo.sql,v 1.6 2009-01-02 16:50:09 mwn Exp $ */

/* settings: */
/* currency: 182 EUR, 32 CHF, 165 USD */

/*********************************************************/
/* Core data                                             */
/*********************************************************/

delete from preis where PRE_ID > -1;
delete from host_kont where HOSTKONT_ID > -1;
delete from arrangement where ARR_ID > -1;
delete from programm where PRG_ID > -1;
delete from dlg_dlg;
delete from dlg_parts where DL_ID > -1;
delete from dienstleistung where DLG_ID > -1;
delete from dienst_angebot where DLA_ID > -1;
delete from traeger_detail;
delete from dienst_traeger where DLT_ID > -1;
delete from kategorie where KAT_ID > -1;
delete from kollektiv where K_ID > -1;
delete from persadr where PERS_ID > -1;
delete from kunden where PERS_ID > -1;
delete from reisender where PERS_ID > -1;
delete from personen where PERS_ID > -1;
delete from saison where SAI_ID > -1;
delete from land_whr;

/* exchange rates */
insert into land_whr (LAND_ID, WHR_ID, KURS_TYP, A_KURS, V_KURS, VON_DAT)
 values (840, 32, 1, 0.8, 0.7, 0);

/* Saison */
insert into saison (SAI_ID, CODE, BEZ_ID, VON, BIS, TEXTID)values ( 1, 'S2020', 1, 1577833200, 1609369200, -1);

delete from bezeichnung where TYP = 9 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 9 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Saison 2020', 9);
insert into bezeichnung values (1, 25, 'Saison 2020', 9);

delete from texte where TYP = 9 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 9 and S_ID = 25 and TEXTID > 0;
insert into texte values ( 1, 1, 1, 'Saison fï¿½r das Jahr 2020 - 1.1.2020 bis 31.12.2020', 9);
insert into texte values ( 1, 1, 2, 'Dies ist eine Test Saison und fï¿½r Demozwecke gedacht', 9);
insert into texte values ( 1, 25, 1, 'Season covering year 2020', 9);

/* Persons (type 1=private, 2=company) */

/* 2 travellers with one child and a company sales */
insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (1, 1, 'Traveller', 1, 1, -1);
insert into reisender (PERS_ID, VOR, RKR_ID, SEX, MUTTERS_ID, AGE, PASSNR, ATTR1, ATTR2, TEXTID)
values (1, 'Peter', 1, 1, 2, '45', '38298239', 'Demo traveller', '', -1);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (1, 1, 'Mr.', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'thomas.muster@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (2, 1, 'Traveller', 1, 1, -1);
insert into reisender (PERS_ID, VOR, RKR_ID, SEX, MUTTERS_ID, AGE, PASSNR, ATTR1, ATTR2, TEXTID)
values (2, 'Maria', 1, 1, 2, '45', '38298239', 'Demo traveller', '', -1);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (2, 1, 'Mrs.', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'thomas.muster@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (3, 1, 'Muster', 1, 1, -1);
insert into reisender (PERS_ID, VOR, RKR_ID, SEX, MUTTERS_ID, AGE, PASSNR, ATTR1, ATTR2, TEXTID)
values (3, 'Thomas', 1, 1, 2, '45', '38298239', 'Demo sales manager', '', -1);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (3, 1, 'Mr.', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'thomas.muster@tdb.org', '');

/* a booking company, hotel owner company and an agent */
insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (4, 2, 'tdb main office', 25, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (4, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (4, 1, 'Company', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (5, 2, 'tdb hotel owner', 25, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (5, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (5, 1, 'Company', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (6, 2, 'tdb agent office', 25, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (6, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (6, 1, 'Company', 'Main street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (7, 2, 'cruise owner office', 25, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (7, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (7, 1, 'Company', 'Cruise street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (8, 2, 'cruise agent office', 25, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (8, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (8, 1, 'Company', 'Cruise street, 10', '5th floor', '', '83340', 'New York', 'NY', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (9, 2, 'Reisebï¿½ro Paradis BER', 1, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (9, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (9, 1, 'Company', 'Cruise street, 10', '5th floor', '', '83340', 'Berlin', 'DE', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');

insert into personen (PERS_ID, PERS_TYP, NAME, S_ID, STA_ID, TEXTID) values (10, 2, 'Reisebï¿½ro Paradis FRA', 1, 1, -1);
insert into kunden (PERS_ID, TEL, HANDY, FAX, TLX, EMAIL, WEB, KONTO, LEITER, ATTR1, ATTR2, K_TYP_ID, WHR_ID)
values (10, '+4144112334', '', '', '', 'info@tdb.org', 'http://www.tdb.org/', 'CH32 33 3232 2323', 3, 'Demo', '', 1, 32);
insert into persadr (PERS_ID, ADR_TYP, ANS, ADR1, ADR2, ADR3, PLZ, ORT, KANT, LAND_ID, STA_ID, HAUPT_FLAG, RCH_FLAG, MAIL_FLAG, TEL, HANDY, FAX, TLX, EMAIL, WEB)
values (10, 1, 'Company', 'Cruise street, 10', '5th floor', '', '83340', 'Frankfurt', 'DE', 1, 1, 1, 1, 1, '', '', '', '', 'info@tdb.org', '');


insert into kollektiv (K_ID, REF, NAME, K_TYP_ID, KBST, K_STA, HAUPTPERS, KID, TEXTID) values (1, 'grp1', 'Group Alpha', 2, 4, 1, 2, 1, -1);


/* Category */
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (1, 1, -1, 1, -1, 1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (2, 2, -1, 2, -1, -1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (3, 3, 2, 2, -1, -1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (4, 4, 3, 2, -1, -1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (5, 5, -1, 5, -1, -1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (6, 6, 5, 7, -1, -1);
insert into kategorie (KAT_ID, BEZ_ID, H_KAT_ID, TYP_ID, GA, TEXTID) values (7, 7, 5, 7, -1, -1);

delete from bezeichnung where TYP = 16 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 16 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, '5 Sterne *****', 16);
insert into bezeichnung values (1, 25, '5 star *****', 16);
insert into bezeichnung values (2, 1, 'Suite', 16);
insert into bezeichnung values (2, 25, 'Suite', 16);
insert into bezeichnung values (3, 1, 'Standard room', 16);
insert into bezeichnung values (3, 25, 'Standard room', 16);
insert into bezeichnung values (4, 1, 'Single room', 16);
insert into bezeichnung values (4, 25, 'Single room', 16);
insert into bezeichnung values (5, 1, 'Luxus Kreuzer', 16);
insert into bezeichnung values (5, 25, 'Delux cruiser', 16);
insert into bezeichnung values (6, 1, 'Luxus Kabine', 16);
insert into bezeichnung values (6, 25, 'Top cabin', 16);
insert into bezeichnung values (7, 1, 'Standard Kabine', 16);
insert into bezeichnung values (7, 25, 'Standard cabin', 16);

delete from texte where TYP = 16 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 16 and S_ID = 25 and TEXTID > 0;
insert into texte values (1, 1, 1, 'Super Hotel Kategorie', 16);
insert into texte values (1, 25, 1, 'Super Hotel Kategorie', 16);

/* service host like a hotel or ship */
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (1, 'MGMLV', 1, 1, -1, -1, -1, 1, -1, 1, 1, 7000);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (2, 'MR1001', 2, 2, 1, 1, 1, 2, -1, 2, 1, 2);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (3, 'MR1002', 3, 3, 1, 1, 1, 2, -1, 2, 1, 2);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (4, 'MR1003', 4, 4, 1, 1, 1, 2, -1, 2, 1, 1);

insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (5, 'CRVIENNA', 5, 5, -1, -1, 5, 5, -1, 1, 1, 1);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (6, 'CRVIENNAD1', 6, 5, 5, 5, 5, 6, -1, 1, 1, 1);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (7, 'CVCAB1001', 7, 6, 6, 5, 5, 7, -1, 2, 1, 1);
insert into dienst_traeger (DLT_ID, CODE, BEZ_ID, KAT_ID, H_DLT_ID, DLT_GRP_ID, HOST_ID, TYP_ID, TEXTID, STUFE, STA_ID, ANZ)
                    values (8, 'CVCAB1002', 8, 7, 6, 5, 5, 7, -1, 2, 1, 1);

delete from bezeichnung where TYP = 17 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 17 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'MGM Grand Las Vegas', 17);
insert into bezeichnung values (1, 25, 'MGM Grand Las Vegas', 17);
insert into bezeichnung values (2, 1, 'Zimmer 1001', 17);
insert into bezeichnung values (2, 25, 'Room 1001', 17);
insert into bezeichnung values (3, 1, 'Zimmer 1002', 17);
insert into bezeichnung values (3, 25, 'Room 1002', 17);
insert into bezeichnung values (4, 1, 'Zimmer 1003', 17);
insert into bezeichnung values (4, 25, 'Room 1003', 17);
insert into bezeichnung values (5, 1, 'Kreuzfahrtschiff Vienna', 17);
insert into bezeichnung values (5, 25, 'Ship Vienna', 17);
insert into bezeichnung values (6, 1, 'Deck Alpha', 17);
insert into bezeichnung values (6, 25, 'Deck alpha', 17);
insert into bezeichnung values (7, 1, 'Kabine 1001', 17);
insert into bezeichnung values (7, 25, 'Cabin 1001', 17);
insert into bezeichnung values (8, 1, 'Kabine 1002', 17);
insert into bezeichnung values (8, 25, 'Cabin 1002', 17);

delete from texte where TYP = 17 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 17 and S_ID = 25 and TEXTID > 0;

insert into traeger_detail (DLT_ID, FIRMA) values (1, 4);
insert into traeger_detail (DLT_ID, FIRMA) values (5, 4);

/* servic offering */
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (1, 'LV3day', -1, 1, 2, 1, 1, 'Las Vegas', 2, 259200, -1, -1, -1);
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (2, 'LV1night', -1, 1, 2, 2, 1, 'Las Vegas', 2, 86400, -1, -1, -1);
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (3, 'CRUISE12', -1, 1, 5, 3, 1, 'Genua', 2, 259200, -1, -1, -1);
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (4, 'GEN-BAR', 3, 1, 5, 4, 1, 'Genua', 2, 86400, -1, -1, -1);
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (5, 'BAR-SIZ', 3, 2, 5, 5, 1, 'Bari', 2, 86400, -1, -1, -1);
insert into dienst_angebot (DLA_ID, CODE, H_DLA_ID, ORD, DLT_ID, BEZ_ID, AKT_ID, ORT, ART_ID, DAU, TEXTID, VON, NACH)
 values (6, 'SIZ-GEN', 3, 3, 5, 6, 1, 'Sizilia', 2, 86400, -1, -1, -1);

delete from bezeichnung where TYP = 23 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 23 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Las Vegas 3 Tage im MGM Grand', 23);
insert into bezeichnung values (1, 25, 'Las Vegas 3 day stay at MGM Grand', 23);
insert into bezeichnung values (2, 1, 'Las Vegas 1 Nacht MGM Grand', 23);
insert into bezeichnung values (2, 25, 'Las Vegas 1 night stay at MGM Grand', 23);
insert into bezeichnung values (3, 1, 'Mittelmeer Kreuzfahrt', 23);
insert into bezeichnung values (3, 25, 'Cruise europe', 23);
insert into bezeichnung values (4, 1, 'Mittelmeer Kreuzfahrt GEN-BAR', 23);
insert into bezeichnung values (4, 25, 'Cruise europe gen-bar', 23);
insert into bezeichnung values (5, 1, 'Mittelmeer Kreuzfahrt BAR-SIZ', 23);
insert into bezeichnung values (5, 25, 'Cruise europe bar-siz', 23);
insert into bezeichnung values (6, 1, 'Mittelmeer Kreuzfahrt SIZ-GEN', 23);
insert into bezeichnung values (6, 25, 'Cruise europe siz-gen', 23);

delete from texte where TYP = 23 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 23 and S_ID = 25 and TEXTID > 0;

/* service details / parts - 1h = 3600s / 1d = 86400s */
insert into dlg_parts (DL_ID, CODE, BEZ_ID, H_DL_ID, DLA_ID, ORD, A_ZEIT, E_ZEIT, RES_F, KID, KONTO, TEXTID, SAI_ID, RECHST)
 values (1, 'LV3day', 1, -1, 1, 1, 0, 0, 3, 1, 'CH32 3333 3333', -1, 1, 1);
insert into dlg_parts (DL_ID, CODE, BEZ_ID, H_DL_ID, DLA_ID, ORD, A_ZEIT, E_ZEIT, RES_F, KID, KONTO, TEXTID, SAI_ID, RECHST)
 values (2, 'CRUISE12', 2, -1, 3, 1, 1583071200, 1583330400, 2, 7, 'CH32 3333 3333', -1, 1, 8);
insert into dlg_parts (DL_ID, CODE, BEZ_ID, H_DL_ID, DLA_ID, ORD, A_ZEIT, E_ZEIT, RES_F, KID, KONTO, TEXTID, SAI_ID, RECHST)
 values (3, 'GEN-BAR', 3, 2, 4, 1, 1583071200, 1583157600, 2, 7, 'CH32 3333 3333', -1, 1, 8);
insert into dlg_parts (DL_ID, CODE, BEZ_ID, H_DL_ID, DLA_ID, ORD, A_ZEIT, E_ZEIT, RES_F, KID, KONTO, TEXTID, SAI_ID, RECHST)
 values (4, 'BAR-SIZ', 4, 2, 5, 2, 1583157600, 1583244000, 2, 7, 'CH32 3333 3333', -1, 1, 8);
insert into dlg_parts (DL_ID, CODE, BEZ_ID, H_DL_ID, DLA_ID, ORD, A_ZEIT, E_ZEIT, RES_F, KID, KONTO, TEXTID, SAI_ID, RECHST)
 values (5, 'SIZ-GEN', 5, 2, 6, 3, 1583244000, 1583330400, 2, 7, 'CH32 3333 3333', -1, 1, 8);

delete from bezeichnung where TYP = 26 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 26 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Las Vegas 3 Tage im MGM Grand', 26);
insert into bezeichnung values (1, 25, 'Las Vegas 3 day stay at MGM Grand', 26);
insert into bezeichnung values (2, 1, 'Mittelmeer Kreuzfahrt', 26);
insert into bezeichnung values (2, 25, 'Cruise europe', 26);
insert into bezeichnung values (3, 1, 'Mittelmeer Kreuzfahrt GEN-BAR', 26);
insert into bezeichnung values (3, 25, 'Cruise europe gen-bar', 26);
insert into bezeichnung values (4, 1, 'Mittelmeer Kreuzfahrt BAR-SIZ', 26);
insert into bezeichnung values (4, 25, 'Cruise europe bar-siz', 26);
insert into bezeichnung values (5, 1, 'Mittelmeer Kreuzfahrt SIZ-GEN', 26);
insert into bezeichnung values (5, 25, 'Cruise europe siz-gen', 26);

delete from texte where TYP = 26 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 26 and S_ID = 25 and TEXTID > 0;

/* services */
insert into dienstleistung (DLG_ID, CODE, BEZ_ID, TEXTID, SAI_ID, A_ZEIT, AKT_ID)
 values (1, 'LV3D', 1, -1, 1, 0, 1);
insert into dienstleistung (DLG_ID, CODE, BEZ_ID, TEXTID, SAI_ID, A_ZEIT, AKT_ID)
 values (2, 'CRUISE12', 2, -1, 1, 1583071200, 1);

delete from bezeichnung where TYP = 27 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 27 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Las Vegas 3 Tage', 27);
insert into bezeichnung values (1, 25, 'Las Vegas 3 days', 27);
insert into bezeichnung values (2, 1, 'Mittelmeer Kreuzfahrt', 27);
insert into bezeichnung values (2, 25, 'Cruise europe', 27);

delete from texte where TYP = 27 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 27 and S_ID = 25 and TEXTID > 0;

/* service link */
insert into dlg_dlg (DLG_ID, DL_ID, ORD) values (1, 1, 0);
insert into dlg_dlg (DLG_ID, DL_ID, ORD) values (2, 2, 0);
insert into dlg_dlg (DLG_ID, DL_ID, ORD) values (2, 3, 1);
insert into dlg_dlg (DLG_ID, DL_ID, ORD) values (2, 4, 2);
insert into dlg_dlg (DLG_ID, DL_ID, ORD) values (2, 5, 3);

/* programs */
insert into programm (PRG_ID, CODE, BEZ_ID, TEXTID, SAI_ID)
 values (1, 'CIT', 1, -1, 1);
insert into programm (PRG_ID, CODE, BEZ_ID, TEXTID, SAI_ID)
 values (2, 'CRU', 2, -1, 1);

delete from bezeichnung where TYP = 29 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 29 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Stï¿½dte', 29);
insert into bezeichnung values (1, 25, 'Cities', 29);
insert into bezeichnung values (2, 1, 'Kreuzfahrten', 29);
insert into bezeichnung values (2, 25, 'Cruises', 29);

delete from texte where TYP = 29 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 29 and S_ID = 25 and TEXTID > 0;

/* packages */
insert into arrangement (ARR_ID, CODE, BEZ_ID, A_DAT, PRG_ID, TEXTID, SAI_ID) values (1, 'LV3D', 1, 0, 1, -1, 1);
insert into arrangement (ARR_ID, CODE, BEZ_ID, A_DAT, PRG_ID, TEXTID, SAI_ID) values (2, 'CRUEUR', 2, 1583071200, 2, -1, 1);

delete from bezeichnung where TYP = 30 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 30 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Las Vegas 3 Nï¿½chte mit Flug', 30);
insert into bezeichnung values (1, 25, 'Las Vegas 3 days with flight', 30);
insert into bezeichnung values (2, 1, 'Kreuzfahrt im Mittelmeer und LV', 30);
insert into bezeichnung values (2, 25, 'Cruise europe and LV', 30);

delete from texte where TYP = 30 and S_ID = 1 and TEXTID > 0;
delete from texte where TYP = 30 and S_ID = 25 and TEXTID > 0;

/* package link */
insert into arr_dlg (ARR_ID, TEIL, PRIO, DLG_ID) values (1, 1, 1, 1);
insert into arr_dlg (ARR_ID, TEIL, PRIO, DLG_ID) values (2, 1, 1, 1);
insert into arr_dlg (ARR_ID, TEIL, PRIO, DLG_ID) values (2, 2, 1, 2);


/* allotments */
insert into host_kont (HOSTKONT_ID, BEZ_ID, FROM_PERS, KBST, DLA_ID, DL_ID, DL_VONDAT, DL_BISDAT, TEXTID, OPT_DAT, SAI_ID, REF, HISTORY)
 values (1, 1, 7, 4, 3, -1, 0, 0, -1, 0, 1, 'PK32323', -1);
delete from bezeichnung where TYP = 38 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 38 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Mittelmeer Paradis Kontingent', 38);
insert into bezeichnung values (1, 25, 'Cruise europ paradis allotment', 38);

insert into kontingent (KONT_ID, BEZ_ID, HOSTKONT_ID, KUNDEN_ID, OPT_DAT, REF, SAI_ID, TEXTID)
 values (1, 1, 1, 9, 0, 'K0001*mwn', 1, -1);
insert into kontingent (KONT_ID, BEZ_ID, HOSTKONT_ID, KUNDEN_ID, OPT_DAT, REF, SAI_ID, TEXTID)
 values (2, 2, 1, 10, 0, 'K0002*mwn', 1, -1);
delete from bezeichnung where TYP = 39 and S_ID = 1 and BEZ_ID > 0;
delete from bezeichnung where TYP = 39 and S_ID = 25 and BEZ_ID > 0;
insert into bezeichnung values (1, 1, 'Mittelmeer Paradis BER Kontingent', 39);
insert into bezeichnung values (1, 25, 'Cruise europ paradis ber allotment', 39);
insert into bezeichnung values (2, 1, 'Mittelmeer Paradis FRA Kontingent', 39);
insert into bezeichnung values (2, 25, 'Cruise europ paradis fra allotment', 39);

insert into kont_detail (HOSTKONT_ID, KONT_ID, KAT_ID, DLT_ID, STA_ID, ANZ, BUSY, MINANZ, VON_DAT, BIS_DAT)
 values (1, -1, 7, -1, 1, 10, -1, 2, 0, 0);
insert into kont_detail (HOSTKONT_ID, KONT_ID, KAT_ID, DLT_ID, STA_ID, ANZ, BUSY, MINANZ, VON_DAT, BIS_DAT)
 values (-1, 1, 7, -1, 1, 5, -1, 2, 0, 0);
insert into kont_detail (HOSTKONT_ID, KONT_ID, KAT_ID, DLT_ID, STA_ID, ANZ, BUSY, MINANZ, VON_DAT, BIS_DAT)
 values (-1, 2, 7, -1, 1, 5, -1, 2, 0, 0);


/* pricing */
insert into preis (PRE_ID, APR, EPR, VPR, GLT, WHR_ID, KBST, KAR_ID, DLTT_ID, KAT_ID, RKR_ID, DLA_ID, ARR_ID, DL_ID, EXT_ID, DL_VONDAT, DL_BISDAT, KONT_ID, STA_ID, TEXTID, HISTORY, SAI_ID, UNIT_TYP, UNIT_VON, UNIT_BIS, DAU, DAU_VON, DAU_BIS)
 values (1, 1400.0, 1600.0, 1800.0, 1167606000, 182, 4, 1, -1, 4, -1, -1, -1, -1, 0, -1, -1, -1, 2 -1, 0, -1, 1, 1, -1, 0, 0, 0, 0);
insert into preis (PRE_ID, APR, EPR, VPR, GLT, WHR_ID, KBST, KAR_ID, DLTT_ID, KAT_ID, RKR_ID, DLA_ID, ARR_ID, DL_ID, EXT_ID, DL_VONDAT, DL_BISDAT, KONT_ID, STA_ID, TEXTID, HISTORY, SAI_ID, UNIT_TYP, UNIT_VON, UNIT_BIS, DAU, DAU_VON, DAU_BIS)
 values (2, 2400.0, 2600.0, 2800.0, 1167606000, 182, 4, 1, -1, 6, -1, -1, -1, -1, 0, -1, -1, -1, 2 -1, 0, -1, 1, 1, -1, 0, 0, 0, 0);
insert into preis (PRE_ID, APR, EPR, VPR, GLT, WHR_ID, KBST, KAR_ID, DLTT_ID, KAT_ID, RKR_ID, DLA_ID, ARR_ID, DL_ID, EXT_ID, DL_VONDAT, DL_BISDAT, KONT_ID, STA_ID, TEXTID, HISTORY, SAI_ID, UNIT_TYP, UNIT_VON, UNIT_BIS, DAU, DAU_VON, DAU_BIS)
 values (3, 3400.0, 3600.0, 3800.0, 1167606000, 182, 4, 1, -1, 7, -1, -1, -1, -1, 0, -1, -1, -1, 2 -1, 0, -1, 1, 1, -1, 0, 0, 0, 0);

 /* profiles */
delete from mp_profil where mpid > 0;
insert into mp_profil values (1, 'mwn', 4, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
insert into mp_profil values (2, 'demo', 4, 3, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
insert into mp_profil values (3, 'tdbinternet', -1, 2, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
insert into mp_profil values (4, 'tdbserver', 4, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
insert into mp_profil values (5, 'tdbadmin', 4, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
