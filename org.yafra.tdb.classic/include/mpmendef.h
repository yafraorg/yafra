/*D***********************************************************
 * Header:                                         mpmendef.h       
 * 			MENU internal Field definition only for DBI       
 * 			Field type definition also for GUI       
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpmendef.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/


/**********************************************************
 * Menu allgemein
 **********************************************************/
#define    ANZGROUPS      6              /* exclusive Help menu */
#define    ANZ_MENU      49              /* normal menus        */
#define    NRANSW        ANZ_MENU+2
#define    NRGLOB        ANZ_MENU

/**********************************************************
 * Feldtypen
 **********************************************************/
#define SEDITFIELD         (int)0   /* Single Line Editfield     */
#define MEDITFIELD         (int)1   /* Multi Line Editfield      */
#define SELECTFIELD        (int)2   /* Selectfield with Newlevel */
#define TOGGLEFIELD        (int)3   /* Togglefield               */
#define ONEITEMFIELD       (int)4   /* Oneline Select Editfield  */
#define SELNOFIELD         (int)5   /* Selectfield no Newlevel   */
#define READONLYFIELD      (int)6   /* Only Output               */
#define SELECTGRAFIELD     (int)7   /* Select Graphikfeld        */
#define INPUTGRAFIELD      (int)8   /* Input Graphikfeld         */
#define INPNEWLEVEL        (int)9   /* leeres Feld               */
#define SHOWGRAFIELD       (int)10  /* Show Graphikfeld          */
#define TWINSELFIELD       (int)11  /* Selection with two fields */
#define SELMENUFIELD       (int)12  /* Select. with menu,no input */
#define MATRIXSELFIELD     (int)13  /* Matrix select field       */
#define MATRIXSELBINFIELD  (int)14  /* Matrix select binary field */
#define MATRIXEDITFIELD    (int)14  /* Matrix edit field         */




/**********************************************************
 * Felddefinitionen pro Menu
 **********************************************************/

/* BUCHUNG Menu */
#define MBCH_BCHREF        0  /* eindeutige Buchungsreferenz      */
#define MBCH_BCHNR         1  /* eindeutige Buchungsnummer        */
#define MBCH_STAZUSTAND    2  /* Zustand der Buchung              */
#define MBCH_DAT           3  /* Abfahrtsdatum                    */
#define MBCH_ARR           4  /* Arrangement der Buchung          */
#define MBCH_DL            5  /* Dienstleistung                   */
#define MBCH_KUNBCHST      6  /* Buchungsstelle                   */
#define MBCH_KUNRECH       7  /* Rechnungsempf�nger / Reiseb�ro   */
#define MBCH_DLT           8  /* Hauptdienstleistungstr�eger      */
#define MBCH_DLA           9  /* Angebot                          */
#define MBCH_KOL          10  /* Kollektiv                        */
#define MBCH_BCHHAUPT     11  /* Hauptbuchung bei Doppelbuchungen */
#define MBCH_SACHBEARB    12  /* Sachbearbeiter                   */
#define MBCH_OPTB         13  /* Optionale Buchungsstelle         */
#define MBCH_OPTK         14  /* Optionale Reisender              */
#define MBCH_HISTORY      15  /* History                          */
#define MBCH_DLN          16  /* DL-Nehmer                        */
#define MBCH_TXT          17  /* Buchungstext                     */

#define MBME_BCHREF        0  /* Buchungsreferenz                 */
#define MBME_BCHNR         1  /* Buchungsnummer                   */
#define MBME_BCHSTA        2  /* Buchungsstatus                   */
#define MBME_DAT           3  /* Datum der Reise/gew. Reservation */
#define MBME_ARR           4  /* gew. Arrangement oder            */
#define MBME_DL            5  /* gew. Dienstleistung              */
#define MBME_KUNBCH        6  /* Kunde Buchungsstelle             */
#define MBME_KUNRECH       7  /* Kunde Rechnungsstelle            */
#define MBME_DLT           8  /* Diensteleistungstr�ger/Tr�gertyp */
#define MBME_DLA           9  /* Angebot                          */
#define MBME_KOL          10  /* Kollektiv                        */
#define MBME_BCHDOPPEL    11  /* Doppelbuchungsnummer             */
#define MBME_SACH         12  /* Sachbearbeiter                   */
#define MBME_ANFOPT       13  /* Anfrage Option bis               */
#define MBME_KUNOPT       14  /* Kunden Option bis                */
#define MBME_HISTORY      15  /* History                          */
#define MBME_DLN          16  /* DLN                              */
#define MBME_TEXT         17  /* Buchungstext                     */

/* BMDLN */
#define MBMDLN_NAME        0  /* DLN Name                         */
#define MBMDLN_VORNAME     1  /* DLN Vorname                      */
#define MBMDLN_ALTER       2  /* DLN-ATTRIBUTE  Alter             */
#define MBMDLN_INTTXT      3  /* DLN firmeninterne Beschreibung   */
#define MBMDLN_EXTTXT      4  /* DLN externe Beschreibung         */
#define MBMDLN_SPR         5  /* DLN SPRACHE                      */

/* BMRES */
#define MBMRES_DLN         0  /* DLN                              */
#define MBMRES_RESSTA      1  /* STATUS_WERTE Reservationsstatus  */
#define MBMRES_DLT         2  /* DIENST_TRAEGER Buchungseinheit   */
#define MBMRES_DLTT        3  /* TRAEGER_TYP                      */
#define MBMRES_DLPART      3  /* DLPARTS Teildienstleistungen     */
#define MBMRES_ADAT        4  /* DATUM DL start date              */
#define MBMRES_EDAT        5  /* DATUM DL end date                */
#define MBMRES_TEXT        6  /* Beschreibung                     */


/* REISENDER */
#define MDLN_NR            0  /* Reisendernummer                   */
#define MDLN_NAM           1  /* Name                              */
#define MDLN_VOR           2  /* Vorname                           */
#define MDLN_ORT           3  /* Ort                               */
#define MDLN_DLNT          4  /* DLN Typ                           */
#define MDLN_SEX           5  /* Geschlechts-Status                */
#define MDLN_SPR           6  /* Sprache                           */
#define MDLN_LAND          7  /* Nationalit�t                      */
#define MDLN_ALTER         8  /* Alter                             */
#define MDLN_PASS          9  /* Passport Nummer                   */
#define MDLN_ATTR1        10  /* Attribut 1                        */
#define MDLN_ATTR2        11  /* Attribut 2                        */
#define MDLN_INTTXT       12  /* Interner Text                     */
#define MDLN_EXTTXT       13  /* Externer Text                     */

/* KUNDEN */
#define MKUN_NR            0  /* Kundennummer                      */
#define MKUN_NAME          1  /* Kundenname                        */
#define MKUN_ORT           2  /* Ortschaft                         */
#define MKUN_KUNT          3  /* Kundentyp                         */
#define MKUN_LAND          4  /* Land                              */
#define MKUN_WHR           5  /* W�hrung                           */
#define MKUN_SPR           6  /* Sprache                           */
#define MKUN_TEL           7  /* Telefon                           */
#define MKUN_FAX           8  /* Fax                               */
#define MKUN_TLX           9  /* Telex                             */
#define MKUN_KONTO        10  /* Konto                             */
#define MKUN_LEIT         11  /* Leiter                            */
#define MKUN_KANT         12  /* Kanton / Kreis                    */
#define MKUN_ATTR1        13  /* Attribut                          */
#define MKUN_ATTR2        14  /* Attribut                          */
#define MKUN_TXT          15  /* Beschreibung                      */

/* KOLLEKTIV / Gruppe */
#define MKOL_BEZ				0  /* Kollektivbezeichnung               */
#define MKOL_VERANT			1  /* Kollektiv Verantwortlicher DL-Nehm */
#define MKOL_KOLT				2  /* Kollektivtypbezeichnung            */
#define MKOL_TXT				3  /* Kollektivbeschreibung              */
#define MKOL_KUNRECH			4  /* Kollektiv Rechnungsempf�nger Kunde */
#define MKOL_KUNBCH			5  /* Kollektiv Buchungsstelle           */
#define MKOL_REF				6  /* Kollektiv Referenz                 */

/* PERSADR */
#define MADR_KUN				0  /* Kunde                              */
#define MADR_DLN				1  /* Reisender                          */
#define MADR_ANR				2  /* Anrede/Ansprache                   */
#define MADR_ADR1				3  /* Adresse                            */
#define MADR_ADR2				4  /* Adresse                            */
#define MADR_ADR3				5  /* Adresse                            */
#define MADR_ORT				6  /* Ortschaft                          */
#define MADR_PLZ				7  /* Postleitzahl                       */
#define MADR_STA				8  /* Versandcode                        */

/* KOMMISSION */
#define MKOM_BEZ           0  /* Kommissionsbezeichnung             */
#define MKOM_TYP           1  /* Kommissions Typ als STATUS_WERT    */
#define MKOM_SATZTYP       2  /* Kommissions Satztyp   STATUS_WERTE */
#define MKOM_SATZ          3  /* Kommissions Satz      STATUS_WERTE */
#define MKOM_KBST          4  /* Kommissionsinhaber          Kunde  */
#define MKOM_KAR           5  /* Kostenart                          */
#define MKOM_KAT           6  /* Kategorie                          */
#define MKOM_DLNT          7  /* Reisendertyp                       */
#define MKOM_DLA           8  /* Dienstleistungsangebot             */
#define MKOM_DL            9  /* Dienstleistung                     */
#define MKOM_DLVON        10  /* Dienstleistung  von Dat            */
#define MKOM_DLBIS        11  /* Dienstleistung  bis Dat            */
#define MKOM_KON          12  /* Kontingent                         */
#define MKOM_BCH          13  /* Buchungsreferenz                   */
#define MKOM_TXT          14  /* Texte                              */
#define MKOM_DLTT         15  /* Traegertyp                         */

/* KOMM_DETAIL */
#define MKOMD_KOM          0  /* Kommission      */
#define MKOMD_BCH          1  /* Buchung fuer Verknuepfung */
#define MKOMD_DLN          2  /* Reisender       */
#define MKOMD_KUN          3  /* Kunde           */
#define MKOMD_KOL          4  /* Kollektiv       */
#define MKOMD_ORD          5  /* Reihenfolge     */

/* OUTPUT Menu */
#define MOUT_AKTT          0  /* Aktionstyp                         */
#define MOUT_DEV           1  /* Device                STATUS_WERTE */
#define MOUT_STAINRES      2  /* Source Res-Sta                     */
#define MOUT_STAOUTRES     3  /* Destination Res-Sta                */

/* SAISON Menu */
#define MSAI_BEZ				0  /* Saison Bezeichnung                 */
#define MSAI_CODE   1
#define MSAI_VON           2  /* Saisonbeginn                       */
#define MSAI_BIS           3  /* Saisonende                         */
#define MSAI_TXT           4  /* Saisonbeschreibung                 */

/* PRGRAMM */
#define MPRG_BEZ           0  /* Programmbezeichnung                */
#define MPRG_CODE          1
#define MPRG_TXT           2  /* Programmbeschreibung               */
#define MPRG_SAI           3  /* Saison                             */

/* ARRANGEMENT Menu */
#define MARR_BEZ           0
#define MARR_ARR           0  /*!! old style delete it */
#define MARR_DAT				1
#define MARR_PRG				2
#define MARR_PRIO				3
#define MARR_TXT				4
#define MARR_DL            5
#define MARR_DTG           5  /*!! old style delete it */
#define MARR_TEILNR			6
#define MARR_CODE     7

/* DIENSTLEISTUNG DTG Menu */
#define MDL_BEZ				0  /* Dienstleistung Bezeichnung         */
#define MDL_TDL            1  /* Teildienstleistung Bezeichnung     */
#define MDL_TXT				2  /* Beschreibung                       */
#define MDL_DAT            3  /* Anfangsdatum                       */
#define MDL_AKT				4  /* Aktionen                           */
#define MDL_ORD				5  /* Reihenfolge-Nummer                 */
#define MDL_CODE   6

/* DLG_PART TDL MENU */
#define MTDL_BEZ           0  /* Dienstleistungsteil Bezeichnung    */
#define MTDL_HOSTTDL       1  /* �bergeordnete DLG                  */
#define MTDL_DLA				2  /* Dienstleistungsangebot             */
#define MTDL_ADAT				3  /* Anfangszeit / -datum               */
#define MTDL_EDAT				4  /* Endzeit / -datum                   */
#define MTDL_RESSTAT			5  /* Reservations Art                   */
#define MTDL_KUN				6  /* Anbieter/Verwalter Kunde           */
#define MTDL_KUNKTO			7  /* Kontonummer                        */
#define MTDL_TXT				8  /* Beschreibung                       */
#define MTDL_SAI				9  /* Saison                             */
#define MTDL_RECHST        10 /* Abrechnungsstelle                  */
#define MTDL_CODE     11

/* old style - kill this */
#define MDLG_DLGPART       0  /* Dienstleistungsteil Bezeichnung    */
#define MDLG_DLGHOST       1  /* �bergeordnete DLG                  */
#define MDLG_DLA				2  /* Dienstleistungsangebot             */
#define MDLG_ADAT				3  /* Anfangszeit / -datum               */
#define MDLG_EDAT				4  /* Endzeit / -datum                   */
#define MDLG_RESSTAT			5  /* Reservationsstatus (muss es gebucht werden ?) */
#define MDLG_KUN				6  /* Anbieter Kunde */
#define MDLG_KUNKTO			7  /* Kontonummer */
#define MDLG_TXT				8  /* Beschreibung */
#define MDLG_SAI				9  /* Saison */

/* DIENST_ANGEBOT Menu */
#define MDLA_BEZ           0
#define MDLA_DLAHOST       1
#define MDLA_ORD           2
#define MDLA_DLT           3  /* Dienstleistungstr�ger des Angebots */
#define MDLA_AKT           4  /* Aktion */
#define MDLA_ORT           5  /* Standort */
#define MDLA_DLAT          6  /* Angebotstyp */
#define MDLA_DAU           7  /* Dauer */
#define MDLA_TXT           8  /* Beschreibung */
#define MDLA_VON           9  /* Von Ort */
#define MDLA_NACH         10  /* Nach Ort */
#define MDLA_CODE         11  /* Code f�r Bezeichnung */

/* AKTIONEN */
#define MAKT_BEZ				0  /* Aktionsbezeichnung                 */
#define MAKT_STADEV        1  /* Status: Device/Medium              */
#define MAKT_TXT           2  /* Beschreibung                       */
#define MAKT_STAAUS        3  /* Status: Ausf�hrung                 */
#define MAKT_STAINRES      4  /* Startstatus der Reservation        */
#define MAKT_AKTT          5  /* Aktionstyp                         */
#define MAKT_STAOUTRES     6  /* Zielstatus der Reservation         */

/* AKTIONGRUPPE */
#define MAKTG_HAKT			0  /* �bergeordnete Aktion               */
#define MAKTG_AKT				1  /* Kindaktion                         */
#define MAKTG_ORD          2  /* Reihenfolge innerhalb einer Grp    */

/* HOST_KONT */
#define MHKON_BEZ           0  /* Kontingentsbezeichnung             */
#define MHKON_KUN           1  /* Kontingent Verwalter  Kunde        */
#define MHKON_BST           2  /* Kontingent Buchungsstelle          */
#define MHKON_DLA           3  /* Dienstleistungsangebot             */
#define MHKON_DL            4  /* Dienstleistung                     */
#define MHKON_DLVON         5  /* Dienstleistung von DATUM           */
#define MHKON_DLBIS         6  /* Dienstleistung bis DATUM           */
#define MHKON_OPTDAT        7  /* Kontingents Optionsablaufdatum     */
#define MHKON_REF           8  /* Kontingents Referenz               */
#define MHKON_TXT           9  /* Kontingentsbeschreibung            */

/* KONTINGENT */
#define MKON_BEZ           0  /* Kontingentsbezeichnung             */
#define MKON_HKON          1  /* �bergeordnetes Kontingent          */
#define MKON_KUN           2  /* Kontingent Verwalter  Kunde        */
#define MKON_OPTDAT        3  /* Kontingents Optionsablaufdatum     */
#define MKON_REF           4  /* Kontingents Referenz               */
#define MKON_TXT           5  /* Kontingentsbeschreibung            */

/* KONT_DETAIL */
#define MKOND_HKON          0  /* �bergeordnetes Kontingent          */
#define MKOND_KON           1  /* Kontingent                         */
#define MKOND_KAT           2  /* Kategorie                          */
#define MKOND_MENGE         3  /* Menge                              */
#define MKOND_MIN           4  /* Mindestmenge                       */
#define MKOND_DLT           5  /* Dienstleistungstr�ger              */
#define MKOND_STA           6  /* Kontingents Ueberbuchungsfaktor    */

/* PREIS */
#define MPRE_NR            0  /* Preisnummer / ID                   */
#define MPRE_WHR           1  /* Preis W�hrung                      */
#define MPRE_APREIS        2  /* Ankaufs Preis                      */
#define MPRE_EPREIS        3  /* Einstands Preis                    */
#define MPRE_VPREIS        4  /* Verkaufs Preis                     */
#define MPRE_GLTAB         5  /* Preis g�ltig ab      DATUM         */
#define MPRE_BST           6  /* Buchungsstelle                     */
#define MPRE_KAR           7  /* Preistyp                           */
#define MPRE_DLTT          8  /* Traegertyp                         */
#define MPRE_KAT           9  /* Kategorie                          */
#define MPRE_DLNT          10 /* DL-Nehmer Typ                      */
#define MPRE_DLA           11 /* Dienstleistungsangebot             */
#define MPRE_DL            12 /* Dienstleistung                     */
#define MPRE_DLVON         13 /* Dienstleistung von DATUM           */
#define MPRE_DLBIS         14 /* Dienstleistung bis DATUM           */
#define MPRE_KON           15 /* Kontingent                         */
#define MPRE_STA           16 /* Preisstatus                        */
#define MPRE_TXT           17 /* Preisbeschreibung                  */
#define MPRE_ARR           18
#define MPRE_UNITTYP 19
#define MPRE_UNITVON 20
#define MPRE_UNITBIS 21




/* TRAEGER_TYP */
#define MDLTT_BEZ				0  /* Tr�gertyp Bezeichnung */
#define MDLTT_HDLTT			1  /* �bergeordneter Tr�ger */
#define MDLTT_TXT				2  /* Tr�gertyp Beschreibung */

/* DIENST_TRAEGER */
#define MDLT_BEZ				0  /* Dienstleistungstr�ger Bezeichnung */
#define MDLT_KAT				1  /* Kategorie */
#define MDLT_HDLT				2  /* �bergeordneter Dienstleistungstr�ger */
#define MDLT_DLTT				3  /* Tr�gertyp */
#define MDLT_TXT				4  /* Dienstleistungstr�ger Beschreibung */
#define MDLT_HOST				5  /* aller oberster Dienstleistungstr�ger */
#define MDLT_ATTR          6  /* Bestplatzattribut */
#define MDLT_CODE    7
#define MDLT_ANZ      8 /* Max Anzahl Personen auf Einheit */

/* KATEGORIE */
#define MKAT_BEZ				0  /* Kategorie Bezeichnung */
#define MKAT_DLTT				1  /* Tr�gertyp */
#define MKAT_HKAT				2  /* �bergeordnete Kategorie */
#define MKAT_GA				3  /* STATUS_WERTE: Grafisches Attribut - Farbe */
#define MKAT_TXT				4  /* Kategorie Beschreibung */

/* GRAPHIK Menu */
#define MGRA_BEZ           0  /* GRA Bezeichnung            */
#define MGRA_DLT           1  /* GRA Dienstleistungstraeger */
#define MGRA_TEXT          2  /* GRA Beschreibung           */

/* PCX */
#define MPCX_BEZ           0  /* PCX Bezeichnung                    */
#define MPCX_FILE          1  /* PCX Filename                       */
#define MPCX_TYP           2  /* PCX Typenspezifikation             */
#define MPCX_TYPCODE       3  /* PCX Auswahl innerhalb des Typs     */
#define MPCX_NR            4  /* PCX Nr                             */
#define MPCX_X             5  /* PCX X Koordinate                   */
#define MPCX_Y             6  /* PCX Y Koordinate                   */

/* KUNDEN_TYP */
#define MKUNT_BEZ          0  /* Kundentyp                          */
#define MKUNT_TXT          1  /* Kundentypbeschreibung              */
#define MKUNT_CODE         2  /* Kundentyp Code                     */

/* KOSTEN_ART */
#define MKAR_BEZ           0  /* Kostenart  / Preistyp              */
#define MKAR_TXT           1  /* Kostenartbeschreibung              */

/* KOLLEKTIV_TYP */
#define MKOLT_BEZ				0  /* Kollektivtyp                       */
#define MKOLT_TXT				1  /* Kollektivtypbeschreibung           */
#define MKOLT_CODE         2  /* Kollektivtyp Code                  */

/* REISENDER_TYP */
#define MDLNT_BEZ				0  /* DL-Nehmer Typ                      */
#define MDLNT_TXT				1  /* DL-Nehmer Typbeschreibung          */
#define MDLNT_CODE         2  /* DL-Nehmer Typ Code                 */
#define MDLNT_VONALTER     3  /* DL-Nehmer von Alter                */
#define MDLNT_BISALTER     4  /* DL-Nehmer bis Alter                */
#define MREIT_BEZ          0
#define MREIT_TXT          1

/* AKTIONS_TYP */
#define MAKTT_BEZ          0  /* Aktionstyp */
#define MAKTT_PROZ         1  /* Prozess */
#define MAKTT_TXT          2  /* Beschreibung */
#define MAKTT_PARANR       3  /* Parameternummer */
#define MAKTT_PARATYP      4  /* Parametertyp */
#define MAKTT_PARA         5  /* Parameter */
#define MAKTT_PARAMUSS     6  /* Muss-Parameter */
#define MAKTT_PARAFLAG     7  /* Parameter ist nur FLAG */
#define MAKTT_PARATXT      8  /* Parameterbeschreibung */

/* ANGEBOTS_TYP Menu */
#define MDLAT_BEZ          0  /* Angebotstyp */
#define MDLAT_TXT          1  /* Bezeichnung */

/* STATUS_WERTE Menu */
#define MSTA_BEZ           0  /* Status Bezeichnung                 */
#define MSTA_ABK				1  /* Status Abk�rzung                   */
#define MSTA_WERT				2  /* Statuswert (effektiver Status)     */
#define MSTA_KOND          3  /* Status Konditionen                 */
#define MSTA_TYP				4  /* Status Typ                         */



/* SPRACHEN */
#define MSPR_BEZ				0  /* Sprachbezeichnung                  */
#define MSPR_DIALOG			1  /* Dialogsprachen Flag                */
#define MSPR_SYSBEZ        2  /* NLS system Bezeichnung             */
#define MSPR_OUTPUT 3
#define MSPR_GUI    4

/* LAND */
#define MLAND_BEZ          0
#define MLAND_ORT          1  /* Hauptstadt                        */
#define MLAND_WHR          2  /* Landeswaehrung                    */
#define MLAND_SPR          3
#define MLAND_KRZL         4
#define MLAND_VAT          5  /* value added tax (mehrwertssteuer) */
#define MLAND_TXT          6  /* Text                              */
#define MLAND_DATEFORMAT   7  /* Datumsformat                      */

/* ORT */
#define MORT_BEZ           0
#define MORT_LAND          1
#define MORT_TYP           2
#define MORT_KRZL          3
#define MORT_ZEITVER       4
#define MORT_KOORD1        5
#define MORT_KOORD2        6
#define MORT_TXT           7

/* WAEHRUNG */
#define MWHR_BEZ           0
#define MWHR_STA           1
#define MWHR_KRZL          2
#define MWHR_TXT           3

/* LAND_WHR Kurse */
#define MLW_LAND				0  /* Land */
#define MLW_WHR            1  /* Waehrung */
#define MLW_KURSTYP        2  /* Kurstyp (bar,devise) */
#define MLW_AKURS          3  /* Ankaufskurs */
#define MLW_VKURS          4  /* Verkaufskurs */
#define MLW_VONDAT         5  /* Kurs g�ltig ab Datum */



/* BEZEICHNUNG Menu */
#define MBEZ_SPR				0  /* Sprache der Bezeichnung            */
#define MBEZ_BEZTYP			1  /* Typ der Bezeichnung  (BEZ_ID 0)    */
#define MBEZ_BEZ				2  /* effektive Bezeichnung              */
#define MBEZ_UEBERBEZ      3  /* Uebersetzungsbezeichnung           */

/* TEXTE Menu */
#define MTXT_SPR				0
#define MTXT_TXT				1
#define MTXT_TOSPR			2
#define MTXT_TOTXT			3


/* MSG Menu */
#define MMSG_TYP           0  /* Nachrichten Typ                    */
#define MMSG_NR            1  /* Nachrichten Nummer                 */
#define MMSG_SPR           2  /* Nachrichten Sprache                */
#define MMSG_TXT           3  /* Nachricht                          */


