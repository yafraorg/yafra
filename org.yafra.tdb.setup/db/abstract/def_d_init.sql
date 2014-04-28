/*D*************************************************************/
/* SQL script: global INIT                                     */
/*             all -1 entries and bez_id 0 entries             */
/*                                                             */
/* copyright:  yafra.org, 2003, Switzerland                    */
/***************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/def_d_init.sql,v 1.12 2009-01-02 16:50:09 mwn Exp $ */

/* loeschen aller Eintraege */
delete from bezeichnung where (bez_id = -1 or bez_id = 0);

delete from texte where textid = -1;

commit work;

/*********************************************************/
/* CODEs - INTERNALS - TEXTE/BEZ                         */
/*********************************************************/

/* tdb database version */
insert into tdb_version (DBVERSION, DBDATE) values (5, STR_TO_DATE('26-11-2008', '%d-%m-%Y'));

/* DB interne Daten */
insert into bezeichnung values (0, 1, 'INT-Maxima', 0);
insert into bezeichnung values (0, 25, 'INT-Maxima', 0);

/* set language (1) with init-lang.xls before you start this script !! */

/* Statuswerte */
insert into status_werte values ( -1, '-', '-', -1, -1, -1);
insert into bezeichnung values (-1, 1, 'kein Status', 2);
insert into bezeichnung values (-1, 25, 'no state', 2);
insert into bezeichnung values (0, 1, 'Statuswerte', 2);
insert into bezeichnung values (0, 25, 'Status values', 2);
insert into texte values ( -1, 1, 1, 'n/a', 2);
insert into texte values ( -1, 25, 1, 'n/a', 2);

/* descriptions and texts */
insert into bezeichnung values (0, 1, 'Bezeichnungen', 3);
insert into bezeichnung values (0, 25, 'Description', 3);
insert into bezeichnung values (0, 1, 'Texte', 4);
insert into bezeichnung values (0, 25, 'Text', 4);
insert into bezeichnung values (0, 1, 'Aktionstexte', 5);
insert into bezeichnung values ( 0, 25, 'Classic transaction text', 5);

/* Help */
insert into help values ( -1, -1, 1, 1, '-');
insert into help values ( -1, -1, 25, 1, '-');
insert into bezeichnung values (0, 1, 'Hilfetexte', 6);
insert into bezeichnung values (0, 25, 'Helptext', 6);

/* messages */
insert into msg values (0, 1, 1, 1, 'Fehlermeldung');
insert into msg values (0, 1, 25, 1, 'Error');
insert into msg values (0, 2, 1, 1, 'Warnung');
insert into msg values (0, 2, 25, 1, 'Warning');
insert into msg values (0, 3, 1, 1, 'Information');
insert into msg values (0, 3, 25, 1, 'Information');
insert into msg values (0, 4, 1, 1, 'RDBMS Meldung');
insert into msg values (0, 4, 25, 1, 'RDBMS message');
insert into msg values (0, 5, 1, 1, 'Systemmeldung');
insert into msg values (0, 5, 25, 1, 'System');
insert into msg values (0, 6, 1, 1, 'Aktionen-Meldung');
insert into msg values (0, 6, 25, 1, 'Transaction message');
insert into bezeichnung values (0, 1, 'Meldungen', 7);
insert into bezeichnung values (0, 25, 'Messages', 7);

/* labels */
insert into bezeichnung values (0, 1, 'Labels', 8);
insert into bezeichnung values (0, 25, 'Labels', 8);

/* History */
insert into history values ( -1, 1, 1, '-', -1, -1);
insert into history (HIS_ID, S_ID, TEXTNR, TEXT, DAT, TYP) values ( -1, 25, 1, '-', -1, -1);
insert into bezeichnung values (0, 1, 'History', 52);
insert into bezeichnung values (0, 25, 'History', 52);

/* Saison */
insert into saison values ( -1, '-', -1, 0, 0, -1);
insert into bezeichnung values (-1, 1, 'keine Saison', 9);
insert into bezeichnung values (0, 1, 'Saison', 9);
insert into bezeichnung values (0, 25, 'Season', 9);
insert into texte values ( -1, 1, 1, 'n/a', 9);
insert into texte values ( -1, 25, 1, 'n/a', 9);

/* additional texts and multimedia definitions */
insert into mp_multimedia (MULT_ID, MULT_TYP, S_ID, MULT) values (-1, -1, 1, '');
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Multimedien Dokumente', 57);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Multimedia documents', 57);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Text zu multimedia Dokument', 58);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Text to multimedia document', 58);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'INT-Temporï¿½rer Text', 70);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'INT-Temporary text', 70);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'INT-Temporï¿½re Bezeichnung', 71);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'INT-Temporary description', 71);

insert into mp_file (FILE_ID, FILE_TYP, CODE, LABEL_ID, FILENAME) values (-1, -1, '-', -1, '-');



/**********************************************/
/* GEOGRAPHIE                                 */
/**********************************************/

insert into waehrung values (-1, -1, -1, -1, '-');
insert into bezeichnung values (-1, 1, 'keine Wï¿½hrung', 12);
insert into bezeichnung values (-1, 25, 'no currency', 12);
insert into bezeichnung values (0, 1, 'Wï¿½hrung', 12);
insert into bezeichnung values (0, 25, 'Curency', 12);
insert into texte values (-1, 1, 1, 'n/a', 12);
insert into texte values (-1, 25, 1, 'n/a', 12);

insert into land values (-1, -1, -1, '-', -1, -1, 1, 0, '-');
insert into bezeichnung values (-1, 1, 'kein Land', 10);
insert into bezeichnung values (-1, 25, 'no country', 10);
insert into bezeichnung values (0, 1, 'Land', 10);
insert into bezeichnung values (0, 25, 'Country', 10);
insert into texte values ( -1, 1, 1, 'n/a', 10);
insert into texte values ( -1, 25, 1, 'n/a', 10);

insert into ort values (-1, -1, -1, -1, '-', -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'kein Ort', 11);
insert into bezeichnung values (0, 1, 'Ortschaft', 11);
insert into bezeichnung values ( 0, 25, 'Place', 11);
insert into texte values ( -1, 1, 1, 'n/a', 11);

insert into bezeichnung values (0, 1, 'INT-Land-Wï¿½hrung', 13);
insert into bezeichnung values (0, 25, 'Country to currency', 13);

insert into bezeichnung values (0, 1, 'INT-Land-Sprache', 14);
insert into bezeichnung values (0, 25, 'Country to language ', 14);

insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Proximity', 59);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Proximity', 59);




/**********************************************/
/* PERSONEN STAMM  (KUNDEN, REISENDE)         */
/**********************************************/

insert into personen values(-1, -1, '-', 1, -1, -1);
insert into bezeichnung values(-1, 1, 'n/a', 34);
insert into bezeichnung values (0, 1, 'INT-Personen', 34);
insert into bezeichnung values (0, 25, 'Persons', 34);
insert into texte values (-1, 1, 1, 'n/a', 34);

insert into reisender_typ values (-1, '-', -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 35);
insert into bezeichnung values (0, 1, 'Reisendertyp', 35);
insert into bezeichnung values (0, 25, 'Traveler type', 35);
insert into texte values ( -1, 1, 1, 'n/a', 35);

insert into reisender values (-1, '-', -1, -1, -1, '-', '-', '-', '-', -1);
insert into bezeichnung values (-1, 1, 'n/a', 36);
insert into bezeichnung values (0, 1, 'Reisender', 36);
insert into bezeichnung values (0, 25, 'Traveler', 36);
insert into texte values ( -1, 1, 1, 'n/a', 36);

insert into persadr values(-1, -1, '-', '-', '-', '-', '-', '-', '-', -1,-1,0,0,0,'-', '-', '-', '-', '-', '-');
insert into bezeichnung values (0, 1, 'INT-Personenadresse', 37);
insert into bezeichnung values (0, 25, 'Adress', 37);

insert into kunden_typ values(-1, '-', -1, -1);
insert into bezeichnung values(-1, 1, 'n/a', 24);
insert into bezeichnung values (0, 1, 'Kundentypen', 24);
insert into bezeichnung values (0, 25, 'Client or partner type', 24);
insert into texte values (-1, 1, 1, 'n/a', 24);

insert into kunden values (-1, '-', '-', '-', '-', '-', '-', '-', -1, '-', '-', -1, -1);
insert into bezeichnung values(-1, 1, 'n/a', 25);
insert into bezeichnung values (0, 1, 'Kunden oder Partner', 25);
insert into bezeichnung values (0, 25, 'Client or partner', 25);
insert into texte values (-1, 1, 1, 'n/a', 25);

insert into kollektiv_typ values (-1, '-', -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 32);
insert into bezeichnung values (0, 1, 'Gruppen- / Kollektivtyp', 32);
insert into bezeichnung values (0, 25, 'Group type', 32);
insert into texte values ( -1, 1, 1, 'n/a', 32);

insert into kollektiv values (-1, '-', '-', -1, -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 33);
insert into bezeichnung values (0, 1, 'Gruppe / Kollektiv', 33);
insert into bezeichnung values ( 0, 25, 'Goup', 33);
insert into texte values ( -1, 1, 1, 'n/a', 33);




/**********************************************/
/* RESERVATIONSKERN  (TRAEGER, ANGEBOT)       */
/**********************************************/

insert into traeger_typ values(-1, -1, -1, -1, -1);
insert into bezeichnung values (0, 1, 'Dienstleistungstrï¿½gertyp', 15);
insert into bezeichnung values ( 0, 25, 'Carrier type', 15);
insert into bezeichnung values(-1, 1, 'kein Trï¿½ger', 15);
insert into texte values( -1, 1, 1, 'n/a', 15);

insert into kategorie values (-1, -1, -1, -1, 1, -1);
insert into bezeichnung values (-1, 1, 'keine Kategorie', 16);
insert into bezeichnung values (0, 1, 'Kategorie', 16);
insert into bezeichnung values ( 0, 25, 'Category', 16);
insert into texte values ( -1, 1, 1, 'n/a', 16);

insert into dienst_traeger values(-1, '-', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
insert into bezeichnung values(-1, 1, 'kein DLT', 17);
insert into bezeichnung values (0, 1, 'Dienstleistungstrï¿½ger', 17);
insert into bezeichnung values (0, 25, 'Carrier', 17);
insert into texte values(-1, 1, 1, 'n/a', 17);

insert into traeger_detail (DLT_ID, FIRMA) values (-1, -1);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Dienstleistungstrï¿½gerdetail', 60);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Carrier detail', 60);

insert into angebots_typ values (-1, -1, -1);
insert into bezeichnung values (-1, 1, 'kein Angebotstyp', 18);
insert into bezeichnung values (0, 1, 'Angebotstyp', 18);
insert into bezeichnung values ( 0, 25, 'Offer type', 18);
insert into texte values (-1, 1, 1, 'n/a', 18);

insert into aktions_typ values (-1, -1, '-', -1);
insert into bezeichnung values (-1, 1, 'kein Aktionstyp', 19);
insert into bezeichnung values (0, 1, 'Aktionstyp', 19);
insert into bezeichnung values (0, 25, 'Transaction type', 19);
insert into texte values (-1, 1, 1, 'n/a', 19);


insert into aktionspara values (-1, -1, -1, '-', -1, -1, -1);
insert into bezeichnung values (0, 1, 'Aktionsparameter', 20);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Transaction parameter', 20);

insert into mp_param (PARAM_ID, FILE_ID, PARAM_TYP, LABEL_ID, CODE, PARAM) values (-1, -1, -1, -1, '-', '-');
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'MP2000 Aktionsparameter', 67);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'MP2000 Transaction parameter', 67);

insert into aktionen values (-1, -1, -1, -1, -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'keine Aktion', 21);
insert into bezeichnung values (0, 1, 'Aktionen', 21);
insert into bezeichnung values (0, 25, 'Transaction', 21);
insert into texte values (-1, 1, 1, 'n/a', 21);

insert into aktionsgrp values (-1, -1, 0, -1);
insert into bezeichnung values (0, 1, 'Aktionsgruppe', 22);
insert into bezeichnung values (0, 25, 'Transaction group', 22);

insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Resourcen Ablage', 66);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Resource files', 66);

insert into dienst_angebot values( -1, '-', -1, 0, -1, -1, -1, '-', -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 23);
insert into bezeichnung values (0, 1, 'Angebot', 23);
insert into bezeichnung values (0, 25, 'Offer', 23);
insert into texte values ( -1, 1, 1, 'n/a', 23);

insert into dlg_parts values (-1, '-', -1, -1, -1, 1, -1, -1, -1, -1, '-', -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 26);
insert into bezeichnung values (0, 1, 'Teildienstleistungen', 26);
insert into bezeichnung values (0, 25, 'Service part', 26);
insert into texte values ( -1, 1, 1, 'n/a', 26);

insert into dienstleistung values (-1, '-', -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 27);
insert into bezeichnung values (0, 1, 'Dienstleistung', 27);
insert into bezeichnung values (0, 25, 'Service', 27);
insert into texte values ( -1, 1, 1, 'n/a', 27);

insert into bezeichnung values (0, 1, 'INT-Dienstleistung zu Dienstleistungsteil', 28);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Service to service parts', 28);

insert into programm values (-1, '-', -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 29);
insert into bezeichnung values (0, 1, 'Programm', 29);
insert into bezeichnung values (0, 25, 'Catalog', 29);
insert into texte values ( -1, 1, 1, 'n/a', 29);

insert into arrangement values (-1, '-', -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 30);
insert into bezeichnung values (0, 1, 'Arrangement', 30);
insert into bezeichnung values (0, 25, 'Service pack', 30);
insert into texte values ( -1, 1, 1, 'n/a', 30);

insert into bezeichnung values (0, 1, 'INT-Arrangement-DL', 31);
insert into bezeichnung values (0, 25, 'Package to services', 31);





/**********************************************/
/* KONTINGENTIERUNG                           */
/**********************************************/

insert into host_kont values (-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, '-', -1);
insert into bezeichnung values (0, 1, 'Kontingentkopf', 38);
insert into bezeichnung values (0, 25, 'Host allotment', 38);
insert into texte values ( -1, 1, 1, 'n/a', 38);

insert into kontingent values (-1, -1, -1, -1, -1, '-', -1, -1);
insert into bezeichnung values (0, 1, 'Kontingent', 39);
insert into bezeichnung values (0, 25, 'Allotment', 39);
insert into bezeichnung values (-1, 1, 'n/a', 39);
insert into texte values ( -1, 1, 1, 'n/a', 39);

insert into bezeichnung values (0, 1, 'INT-Kontingentdetail', 40);
insert into bezeichnung values ( 0, 25, 'Allotment detail', 40);


/* Benutzerberechtigungen */
insert into mp_profil values (-1, 'root', -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Benutzer', 55);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'User', 55);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Reminder', 64);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Reminder', 64);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Voreinstellung', 65);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Preferences', 65);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Gruppe zu personen', 63);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Goup to persons', 63);
insert into mp_preferences (MPID, FULLNAME, FILTER, GUI, CUSTOM) values (-1, 'root', '', 'dataLanguage:25@@@@statusInGuiLanguage:0@@@@languagesInGuiLanguage:0@@@@countriesInGuiLanguage:0@@@@currenciesInGuiLanguage:0@@@@travelerTypeInGuiLanguage:0', 'reseller:1@@@@contingent:1@@@@corporateCurrency:32@@@@exchangeCountry:756');


/**********************************************/
/* RESERVATION - BUCHUNG - PREIS              */
/**********************************************/

insert into buchung (D_BID, BID, REF, ARR_ID, KID, SACH, ANW, B_DAT, M_DAT, OPT_BST, OPT_KID, STA, AST, SAI_ID, K_ID, MPID, HISTORY, TEXTID) values (-1, -1, 'n/a -1', -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 41);
insert into bezeichnung values (0, 1, 'Buchung', 41);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Booking folder', 41);
insert into texte values ( -1, 1, 1, 'n/a', 41);

insert into bezeichnung values (0, 1, 'INT-BCH-DLN', 53);
insert into bezeichnung values (0, 25, 'Booking folder to travelers', 53);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Buchung zu Dienstleistung', 61);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Booking folder to travels', 61);

insert into bezeichnung values (0, 1, 'INT-Aktionsdetail', 42);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Transaction detail', 42);

insert into kosten_art values (-1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 43);
insert into bezeichnung values (0, 1, 'Kostenart', 43);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Payment type', 43);
insert into texte values ( -1, 1, 1, 'n/a', 43);

insert into kommission values (-1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 44);
insert into bezeichnung values (0, 1, 'Kommission', 44);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Rebate and commission', 44);
insert into texte values ( -1, 1, 1, 'n/a', 44);

insert into bezeichnung values (0, 1, 'INT-ARR-KOM', 56);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Package to rebate', 56);

insert into bezeichnung values (0, 1, 'INT-Kommissionsdetail', 45);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Rebate and commission detail', 45);

insert into bezeichnung values (0, 1, 'Reservation', 46);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Travel', 46);

insert into preis ( PRE_ID, APR, EPR, VPR, GLT, WHR_ID, KBST, KAR_ID, DLTT_ID, KAT_ID, RKR_ID, DLA_ID, ARR_ID, DL_ID, EXT_ID, DL_VONDAT, DL_BISDAT, KONT_ID, STA_ID, TEXTID, HISTORY, SAI_ID, UNIT_TYP, UNIT_VON, UNIT_BIS, DAU, DAU_VON, DAU_BIS) values (-1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, 0, 0, 0, 0, 0);
insert into bezeichnung values (0, 1, 'Preis', 47);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Price', 47);

insert into bezeichnung values (0, 1, 'INT-KapazitÃ¤t', 54);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Capacity', 54);

insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Reservation zu Gruppe', 62);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Travel to Group', 62);


/********************************************************/
/* GRAFIK - PIXELBILDER                                 */
/********************************************************/

insert into graphik values (-1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 48);
insert into bezeichnung values (0, 1, 'Grafik', 48);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'deprecated-Grafic', 48);
insert into texte values ( -1, 1, 1, 'n/a', 48);

insert into pcx_files values (-1, -1, '-', -1, -1, -1, -1, -1);
insert into bezeichnung values (-1, 1, 'n/a', 49);
insert into bezeichnung values (0, 1, 'Pixelbilder', 49);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'deprecated-Pixel Images', 49);
insert into texte values ( -1, 1, 1, 'n/a', 49);

insert into bezeichnung values (0, 1, 'INT-Grafikformat', 50);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'deprecated-Grafic format', 50);

insert into bezeichnung values (0, 1, 'INT-Regions', 51);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'deprecated-Grafic zones', 51);


/* Accounting */
insert into mp_debitor (WHR_INKL, VAT_ID, VAT_LAND_ID, VAT, VAT_TEXT, RST_EXCL, RST_INKL, RST_GEWINN, OPT_TEXT, DEB_ID, BID, STA_ID, KID, KONTO, NACHSALDO, K_ID, FAKT_ID, FAKT_ZEIT, FAKT_NR, FAKT_TEXT, DLN_DETAIL, DLG_DETAIL, WHR_ID, WHR_LAND_ID, WHR_KURS, WHR_TEXT, WHR_EXCL) values (-1, -1, -1, 0, '', 0, 0, 0, '', -1, -1, -1, -1, 0, 0, -1, -1, 0, 0, '', '', '', -1, -1, 0, -1, -1);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Debitor', 68);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Debtor', 68);
insert into mp_kreditor (KRE_ID, BID, STA_ID, KID, KONTO, NACHSALDO, K_ID, FAKT_ID, FAKT_ZEIT, FAKT_NR, FAKT_TEXT, DLN_DETAIL, DLG_DETAIL, WHR_ID, WHR_LAND_ID, WHR_KURS, WHR_TEXT, WHR_EXCL, WHR_INKL, VAT_ID, VAT_LAND_ID, VAT, VAT_TEXT, RST_EXCL, RST_INKL, RST_GEWINN, OPT_TEXT) values (-1, -1, -1, -1, -1, 0, -1, -1, 0, -1, -1, -1, -1, -1, -1, 0, '', -1, -1, -1, -1, 0, '', 0, 0, 0, '');
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 1, 'Kreditor', 69);
insert into bezeichnung (BEZ_ID, S_ID, BEZ, TYP) values ( 0, 25, 'Creditor', 69);


/* View Bezeichnungen */
insert into bezeichnung values (0, 1, 'VIEW-Sprachen', 260);
insert into bezeichnung values (0, 1, 'VIEW-Statuswerte', 261);
insert into bezeichnung values (0, 1, 'VIEW-Saison', 262);

insert into bezeichnung values (0, 1, 'VIEW-Land', 263);

insert into bezeichnung values (0, 1, 'VIEW-Kunden', 264);
insert into bezeichnung values (0, 1, 'VIEW-Reisende', 265);
insert into bezeichnung values (0, 1, 'VIEW-Reisendertyp', 266);

insert into bezeichnung values (0, 1, 'VIEW-DLTT', 267);
insert into bezeichnung values (0, 1, 'VIEW-Kategorie', 268);
insert into bezeichnung values (0, 1, 'VIEW-DLT1', 269);
insert into bezeichnung values (0, 1, 'VIEW-DLT2', 270);
insert into bezeichnung values (0, 1, 'VIEW-Aktionen', 271);
insert into bezeichnung values (0, 1, 'VIEW-DLA', 272);
insert into bezeichnung values (0, 1, 'VIEW-Dienstleistungsteile', 273);
insert into bezeichnung values (0, 1, 'VIEW-Dienstleistung', 275);
insert into bezeichnung values (0, 1, 'VIEW-DL-DL', 274);
insert into bezeichnung values (0, 1, 'VIEW-Arrangement', 277);
insert into bezeichnung values (0, 1, 'VIEW-Arrangement-DL', 276);
insert into bezeichnung values (0, 1, 'VIEW-Arrangementdetail', 278);

insert into bezeichnung values (0, 1, 'VIEW-Kontingent', 279);
insert into bezeichnung values (0, 1, 'VIEW-Kontingentueberwachung', 280);

insert into bezeichnung values (0, 1, 'VIEW-Aktionsdetail', 281);
insert into bezeichnung values (0, 1, 'VIEW-Kostenart', 282);

insert into bezeichnung values (0, 1, 'VIEW-Grafik', 283);

/* Objekte ohne Datenbankbezug */
insert into bezeichnung values (0, 1, 'INT-Globales Menu', 200);
insert into bezeichnung values (0, 1, 'INT-Output Menu',   201);
insert into bezeichnung values (0, 1, 'INT-Backup Menu',   202);
insert into bezeichnung values (0, 1, 'INT-Restore Menu',  203);
insert into bezeichnung values (0, 1, 'INT-Information',   204);
insert into bezeichnung values (0, 1, 'INT-Grafik',        205);

