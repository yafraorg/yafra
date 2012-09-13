/*D***********************************************************
 * Header:    mpobjdef.h
 *            Objektdefinitionen f�r das ganze MarcoPolo
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpobjdef.h,v 1.3 2008-11-02 19:55:33 mwn Exp $
*/


/* Allgemeine Objekte  */
#define  UNDEF              (int)-1  /* Undefined (Obsolete form)      */
#define _UNDEF              (int)-1  /* Undefined (new convention )    */
#define _TYPENBEZID         (int)0   /* Bezeichnung der Typen          */
#define _MP_NODATE          (int)0   /* kein Datum/Zeit Wert           */

/************************************************************
 * Sektion:  physische Datenbankobjekte  (tables and views)
 *           (Einfluss auf GUI)
 *
 * Nr.Kreis: 0 - 499
 *************************************************************/
/* Tables */
#define _MAXIMA             (int)0   /* Maximum / Minimum               */
#define _SPRACHEN           (int)1   /* Sprache                         */
#define _STATUS_WERTE       (int)2   /* Statuswerte                     */
#define _BEZEICHNUNG        (int)3   /* Bezeichnung                     */
#define _TEXTE              (int)4   /* Beschreibung (mehrzeilig)       */
#define _AKTIONSTEXTE       (int)5   /* Outputmasken / Aktionstexte     */
#define _HELP               (int)6   /* Helps                           */
#define _MSG                (int)7   /* Nachrichten, Fehlermeldungen    */
#define _LABEL              (int)8   /* GUI Labels                      */
#define _SAISON             (int)9   /* Saison der Angebote/Preise/Res  */
#define _LAND               (int)10  /* GEO: Land                       */
#define _ORT                (int)11  /* GEO: Ort                        */
#define _WAEHRUNG           (int)12  /* GEO: W�hrung                    */
#define _LAND_WHR           (int)13  /* GEO: Kursverknuepfung           */
#define _LAND_SPR           (int)14  /* GEO: Sprachverknuepfung         */
#define _TRAEGER_TYP        (int)15  /* Tr�gertyp                       */
#define _KATEGORIE          (int)16  /* Kategorie                       */
#define _DIENST_TRAEGER     (int)17  /* Dienstleistungstr�ger           */
#define _ANGEBOTS_TYP       (int)18  /* Angebotstyp                     */
#define _AKTIONS_TYP        (int)19  /* Aktionstyp                      */
#define _AKTIONSPARA        (int)20  /* Aktionsparameter                */
#define _AKTIONEN           (int)21  /* Aktionen                        */
#define _AKTIONSGRP         (int)22  /* Aktionsgruppen-Definitionen     */
#define _DIENST_ANGEBOT     (int)23  /* Dienstleistungsangebot          */
#define _KUNDEN_TYP         (int)24  /* PERSONEN: Kundentyp             */
#define _KUNDEN             (int)25  /* PERSONEN: Kunden                */
#define _DLG_PART           (int)26  /* Dienstleistungsteile            */
#define _DIENSTLEISTUNG     (int)27  /* Dienstleistung                  */
#define _DLG_DLG            (int)28  /* Dienstleistung - DL-Teile       */
#define _PROGRAMM           (int)29  /* Programm als Typ des Arr.       */
#define _ARRANGEMENT        (int)30  /* Arrangement                     */
#define _ARR_DLG            (int)31  /* Arrangement - Dienstleistung    */
#define _KOLLEKTIV_TYP      (int)32  /* PERSONEN: Kollektivtyp          */
#define _KOLLEKTIV          (int)33  /* PERSONEN: Kollektiv / Gruppen   */
#define _PERSONEN           (int)34  /* PERSONEN: Personenkopf          */
#define _REISENDER_TYP      (int)35  /* PERSONEN: Reisendertyp          */
#define _REISENDER          (int)36  /* PERSONEN: Reisender             */
#define _PERSADR            (int)37  /* PERSONEN: Adresse               */
#define _HOST_KONT          (int)38  /* KONTINGENT: Kontingentkopf      */
#define _KONTINGENT         (int)39  /* KONTINGENT: Kontingent          */
#define _KONT_DETAIL        (int)40  /* KONTINGENT: Kontingentdetail    */
#define _BUCHUNG            (int)41  /* Buchung                         */
#define _AKT_DETAIL         (int)42  /* Aktionendetail                  */
#define _KOSTEN_ART         (int)43  /* Preistypen / Kostenarten        */
#define _KOMMISSION         (int)44  /* Kommission                      */
#define _KOMM_DETAIL        (int)45  /* Kommission Detail               */
#define _RESERVATION        (int)46  /* Reservation                     */
#define _PREIS              (int)47  /* Preis                           */
#define _GRAPHIK            (int)48  /* GRAFIK: Traegergrafik           */
#define _PCX_FILES          (int)49  /* GRAFIK: Pixelbilder             */
#define _GRAFORM            (int)50  /* GRAFIK: Grafikformat            */
#define _REGIONS            (int)51  /* GRAFIK: Regions fuer Grafikform */
#define _HISTORY            (int)52  /* History                         */
#define _BCH_DLN            (int)53  /* Buchung/Dienstleistungsnehmer   */
#define _KAPA               (int)54  /* Kapazitaet                      */
#define _MP_PROFIL          (int)55  /* Benutzerprofile                 */
#define _MP_ARRKOM          (int)56  /* Arrangement-Kommission          */
#define _MP_WWWTEXTE        (int)57  /* WWW Texte                       */
#define _MP_KOMJOIN         (int)58  /* Kommissionsverknuepfungen       */
#define _MP_KOMNEG          (int)59  /* Kommissionsnegation             */
#define _DATUM              (int)60  /* date field (it is a int in MP)  */
#define _SHORT              (int)61  /* short field                     */
#define _INTEGER            (int)62  /* int field                       */
#define _LONG               (int)63  /* long field                      */
#define _DOUBLE             (int)64  /* double field                    */
#define _MP_PREF            (int)65  /* Preferences for user settings   */
#define _MP_RESOURCES       (int)66  /* resources                       */
#define _MP_AKTPARA         (int)67  /* Trx parameters (Aktionenparas)  */
#define _MP_DEBIT           (int)68  /* Deb/Kred Journal                */
#define _MP_CREDIT          (int)69  /* Deb/Kred Journal                */


/************************************************************
 * Sektion:  global, logging, and program classes
 *           (Einfluss auf GUI)
 *
 * Nr.Kreis: 150 - 199
 *************************************************************/
#define _ACTIONBAR			(int)150  /* Action bar labels             */
#define _PULLDOWN				(int)151  /* Pulldown menu groups          */
#define _MESSAGEWIN			(int)152  /*                               */
#define _DBMODE				(int)153  /*                               */
#define _FRAME					(int)154  /*                               */
#define _GLOBALOBJ			(int)157  /* General miscellaneous         */
#define _TYPEN             (int)158  /* Allg. Typenauswahl f�r NewLevel */
#define _LOGBOOKING        (int)169  /* Booking log (history)         */
#define _LOGUSER           (int)170  /* User log (history)            */
#define _LOGMP             (int)171  /* MarcoPolo int. log (errors)   */
#define _LOGSQL            (int)172  /* SQL log                       */
#define _LOGOPEN           (int)173  /* open all log files            */
#define _LOGCLOSE          (int)174  /* close all log files           */
#define _XGR               (int)180  /* Graphic                       */
#define _XUI               (int)181  /* User interface                */
#define _XBM               (int)182  /* Booking mask                  */

/************************************************************
 * Sektion:  MENU Objekte ohne direkten DB bezug
 *           (Einfluss auf GUI)
 *           !! Caution: Nr are hardcoded in labels file !!
 *
 * Nr.Kreis: 200 - 254
 *************************************************************/
#define _GLOBALMENU			(int)200
#define _OUTPUT				(int)201
#define _BACKUP				(int)202
#define _RESTORE				(int)203
#define _INFORMATION			(int)204
#define _OSF_GRAPHIK			(int)205
#define _FREE1						(int)206
#define _BMDLN             (int)207
#define _FREE2             	(int)208
#define _OPTIONMENU			(int)209
#define _OPTIONTOGGLE		(int)210
#define _SETUPMENU			(int)211
#define _QUITMENU				(int)212
#define _APPLICATION			(int)213
#define _ABOUT					(int)214
									/* last Nr. must be < XUILABMAXTYPES */

/* internal RDBMS system tables */
#define _SYS_COLUMN         (int)258  /* SYSTEM  f�r dropIndex und       */
#define _SYS_INDEX          (int)259  /*         createIndex             */

/************************************************************
 * Sektion:  views
 *           (kein Einfluss auf GUI)
 *
 * Nr.Kreis: 260 - 999
 *************************************************************/
#define _SPR_VIEW           (int)260 /* Sprachen mit bez                */
#define _STA_VIEW           (int)261 /* Statuswerte mit bez             */
#define _SAI_VIEW           (int)262 /* Saison mit bez                  */

#define _LAND_VIEW          (int)263 /* Laender mit bez                 */

#define _KUN_VIEW           (int)264 /* Kunden mit bez                  */
#define _DLN_VIEW           (int)265 /* Reisende mit bez                */
#define _RKR_VIEW           (int)266 /* Reinsendertyp mit bez           */
#define _MPV_DLNADR         (int)286 /* Reinsenderdressen View          */
#define _MPV_KUNADR         (int)287 /* Kundenadresse View              */

#define _TTYP_VIEW          (int)267 /* DLTT mit bez                    */
#define _KAT_VIEW           (int)268 /* Kategorien mit bez              */
#define _TRAEGER_VIEW       (int)269 /* DLT mit bez und h_dlt_bez       */
#define _DLT_VIEW	          (int)270 /* DLT mit bez                     */
#define _AKT_VIEW           (int)271 /* AKT mit bez                     */
#define _DLA_VIEW           (int)272
#define _DLG_VIEW           (int)273
#define _DLDLG_VIEW         (int)274
#define _DTG_VIEW           (int)275
#define _ARRDL_VIEW         (int)276
#define _ARR_VIEW           (int)277
#define _ARR_DETAIL         (int)278 /*!! eliminieren !!! */

#define _KON_VIEW           (int)279
#define _KONCHECK_VIEW      (int)283

#define _AKT_DETAIL_VIEW    (int)280
#define _KAR_VIEW           (int)281

#define _GRA_VIEW           (int)282
#define _MPV_KAPA           (int)284
#define _ROUTEN_VIEW        (int)285

#define _RES_DL_VIEW        (int)290 /* RES mit dl datum                */
#define _RESDLN_VIEW        (int)291 /* RES nach PERS.NAME */
#define _RESDL_VIEW         (int)292 /* RES nach DLBEZ */

/************************************************************
 * Sektion:  Statustypen
 *           (kein Einfluss auf GUI)
 *
 * Nr.Kreis: 1000 - 1999
 *************************************************************/
#define _NAMEN       (int)1100 /* Typ fuer STATUS_WERTE Typ Bezeichnungen */
#define _PRIO        (int)1101 /* Prioritaet paralleler Angebote im Arrangement */
#define _GA          (int)1102 /* Farbattribut fuer die Kategorien */
#define _K_STA       (int)1103 /* Kollektivstatus */
#define _PERSTYP     (int)1104 /* Personentypen */
#define _PREISSTA    (int)1105 /* Preisstatus (sind Reduktionen erlaubt) */
#define _SEX         (int)1106 /* Geschlecht des Reisenden */
#define _AKTSTA      (int)1107 /* Zustand einer Aktion bei Ausf�hrung AKT_DETAIL */
#define _BSTA        (int)1108 /* Buchungs Status */
#define _A_FLG       (int)1109 /* Flag fuer die Aktionenausfuehrung */
#define _PERSSTA     (int)1110 /* Personenstatus */
#define _ADRSTA      (int)1111 /* Versandcode bei Personenadressen */
#define _R_STA       (int)1112 /* Zustand der Reservation */
#define _RES_F       (int)1113 /* Flag ob eine DTG Reserviert wird oder nicht */
#define _KURSTYP     (int)1114 /* Waehrungskurs Typ */
#define _SATZTYP     (int)1115 /* Satz/Wert Typ */
#define _DLTSTA      (int)1116 /* DLT Bestplatz-Status */
#define _U_FAK       (int)1117 /* �berbuchungsfaktor definiert beim KONT_DETAIL */
#define _MSGTYP      (int)1118 /* Message Typen */
#define _DEVICE      (int)1119 /* Device Medium */
#define _KOMMTYP     (int)1120 /* Kommissions Typen */
#define _BCHAST      (int)1121 /* Ausloesestatus der Buchung */
#define _SECURITY    (int)1122 /* Sicherheitsstufen im Benutzerprofil */
#define _STA_ORT     (int)1123 /* Typ des Ortes (Flughafen, Ort) */
#define _STA_ADR     (int)1127 /* Typ der Adresse (Privat, Ferien, Firma, ...) */
#define _STA_UNIT    (int)1128 /* Typ der Unit f�r PREIS (pro Person, pro Zimmer, ...) */



/***************** G U I *************************************************/


/*************************************************************
 * Sektion:  BOOKING MENU Objekte
 *
 * Nr.Kreis: 0 - x  (xbm label types)
 *************************************************************/
#define _BM_GLOB				(int)0
#define _BM_MAIN				(int)1
#define _DLN_FRAME			(int)2			/* Diensleistungsnehmer */
#define _DLN_MENU				(int)3
#define _CAT_FRAME			(int)4			/* Category             */
#define _CAT_RECALL			(int)5
#define _CAT_HEADER			(int)6
#define _CAT_MENU				(int)7
#define _DLT_FRAME			(int)8
#define _DLT_MENU				(int)9
#define _BOARD_MENU			(int)10
									/* last Nr. must be < XBMLABMAXTYPES */

/*************************************************************
 * Sektion:  GRAPHIC MENU Objects
 *
 * Nr.Kreis: 0 - x  (xgr label types)
 *************************************************************/
#define _GR_MAIN					(int)0
#define _GR_OPTION				(int)1
#define _GR_MENU_FILE			(int)2
#define _GR_MENU_CREATE			(int)3
#define _GR_MENU_EDIT			(int)4
#define _GR_MENU_DEFINE			(int)5
#define _GR_MENU_ZOOM			(int)6
#define _GR_MENU_HELP			(int)7
#define _GR_QUESTION				(int)8
#define _GR_DIALOG_TEXT			(int)9
#define _GR_MINI_MENU			(int)10

/*************************************************************
 * Sektion:  LABEL array subscripts max
 *
 *************************************************************/
#define    XGRLABMAXTYPES	(int)   25		/* Nb of xgr labels types   */
#define    XGRLABMAXTEXTS	(int)   40		/* Nb of xgr labels texts   */
#define    XUILABMAXTYPES	(int)  250		/* Nb of xui labels types   */
#define    XUILABMAXTEXTS	(int)   35		/* Nb of xui labels texts   */
#define    XBMLABMAXTYPES	(int)   25		/* Nb of xbm labels types   */
#define    XBMLABMAXTEXTS	(int)   30		/* Nb of xbm labels texts   */

