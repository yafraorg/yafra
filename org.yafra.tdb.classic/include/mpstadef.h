/*D***********************************************************
 * Header:    MPsta_def.h
 *            Statusobjektdefinitionen
 *            betrifft jene Stati die der Benutzer n i c h t
 *            mutieren kann sondern nur Uebersetzen !
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/source/include/mpstadef.h,v 1.3 2008-11-23 15:44:38 mwn Exp $ */

/* _BSTA   M�gliche Zust�nde der Buchung */
#define _BCH_ENTER  1  /* Eingabe immer als Default    */

/* _R_STA  M�gliche Zust�nde der Reservation */
#define _RES_ENTER  	1  	/* Eingabe immer als Default 	*/
#define _RES_ANF  	2  	/* Anfrage    						*/
#define _RES_ANFOK  	3  	/* Anfrage bestaetigt    		*/
#define _RES_MOD  	4  	/* Modifikation    				*/
#define _RES_MODOK  	5  	/* Modifikation bestaetigt    */
#define _RES_OPT  	6  	/* Option    						*/
#define _RES_DEF  	7  	/* Definitiv    					*/
#define _RES_REOPEN  8  	/* Rechnung offen    			*/
#define _RES_REOK  	9  	/* Rechnung bezahlt   			*/
#define _RES_OK  		10  	/* Erledigt    					*/
#define _RES_ANN  	11  	/* Annullation    				*/
#define _RES_ANNOK  	12  	/* Annullation bestaetigt		*/

/* _SEX   Geschlechtstypen */
#define _FRAU   1  /* weibliches Geschlecht        */
#define _MANN   2  /* m�nnliches Geschlecht        */

/* _A_FLAG  Aktionsausf�hrungsflag */
#define _AKT_NOEXEC           1  /* Aktion nicht ausf�hren       */
#define _AKT_AUTOIMM          2  /* Aktion automatisch sofort    */
#define _AKT_AUTOSPOOL        3  /* Aktion automatisch gespoolt  */
#define _AKT_MAN              4  /* Aktion manuell ausf�hren     */

/* _AKTSTA  Aktionszustandsflag (Z_FLAG in AKT_DETAIL) */
#define _AKT_READYTOSTART     1  /* Aktion bereit                */
#define _AKT_ONEXECUTION      2  /* Aktion in Ausf�hrung         */
#define _AKT_OK               3  /* Aktion ausgef�hrt            */
#define _AKT_ERROR            4  /* Fehler in Aktionsausfuehrung */
#define _AKT_FATALERROR       5  /* Aktion ist unausfuehrbar     */

/* _RES_F  Reservationsarten einer Teildienstleistung */
#define _RES_IMPOSSIBLE       1  /* DL ohne Reservationen          */
#define _RES_STATIC           2  /* DL mit voller statischer Res.  */
#define _RES_DYNAMIC          3  /* DL mit voller dynamischer Res. */
#define _RES_BOOLEAN          4  /* DL mit ja/nein Res.            */

/* _DEVICE  Devices */
#define _DEVPRINTER           1  /* Druckerausgabe               */
#define _DEVFAX               2  /* FAX-Ausgabe                  */
#define _DEVTELEX             3  /* Telexausgabe                 */
#define _DEVMODEM             4  /* MODEM-Ausgabe                */
#define _DEVSCREEN            5  /* Bildschirmausgabe via Mail   */
#define _DEVFILE              6  /* Ausgabe in Datei             */
#define _DEVPRINTER2          7  /* Drucker 2                    */
#define _DEVPRINTER3          8  /* Drucker 3                    */
#define _DEVPRINTER4          9  /* Drucker 4                    */

/* _MSGTYP   MSG Typen */
#define MSGTYP_ERROR          1  /* hard errors or program error */
#define MSGTYP_WARNING        2  /* warning message              */
#define MSGTYP_INFO           3  /* just for information (raw)   */
#define MSGTYP_DBERROR        4  /* DBMS error                   */
#define MSGTYP_SYSTEM         5  /* System interne Meldungen     */
#define MSGTYP_ACTION         6  /* Aktionsmeldungen (raw)       */
#define MSGTYP_MSG            2  // TODO obsolete - replace with WARNING

/* _PERSTYP  Personentyp */
#define _PERS_PRIVAT          1  /* private Personen */
#define _PERS_FIRMEN          2  /* juristische Personen */

/* _PREIS    Preisstatus */
#define _PREIS_NORMAL         1  /* normaler Preis */
#define _PREIS_NOREDUCTIONS   2  /* Es duerfen keine KOM vergeben werden */

/* _PERS     Personenstatus */
/* unused */

/* _KOL      Kollektivstatus */
/* unused */

/* _PERSADR  Versandcode fuer Adressen */
#define _PERSADR_NORMAL        1  /* Versandart normal */
#define _PERSADR_EXPRESS       2  /* Versandart express */

/* _KURSTYP Waehrungskurs Typ */
#define _KURS_CASH             1  /* BAR Kurs */
#define _KURS_CREDIT           2  /* DEVISEN Kurs */

/* _SATZTYP Satz/Wert Typ */
#define _SATZ_PROZENT          1  /* Prozentualer Wert */
#define _SATZ_ABSOLUT          2  /* Uebersteuerungs-Wert */
#define _SATZ_NORMAL           3  /* normaler Wert */

/* _KOMMTYP Kommissionstypen */
#define _KOMM_REISENDER        1
#define _KOMM_DLN              1  /* DLN Kommissionen */
#define _KOMM_KUNDE            2  /* KUN Kommissionen */
#define _KOMM_KOLLEKTIV        3  /* KOL Kommissionen */
#define _KOMM_MWST             4  /* Mehrwertsteuer / VAT */

/* _BCHAST Ausloesestatus der Buchung */
#define _BCH_LOCAL          1  /* lokale Buchungen via MARCO POLO classic */
#define _BCH_LOCALWWW       2  /* lokale Buchungen via MARCO POLO bookingmask */
#define _BCH_EXTMPCLASSIC   3  /* Buchungen ueber externes MARCO POLO classic */
#define _BCH_EXTKK          4  /* Buchungen ueber K&K */
#define _BCH_EXTWWW         5  /* Buchungen ueber internet via WorldWideWeb */

/* _SECURITY Sicherheitsstufe im Benutzerprofil */
#define _SECLEVEL_DBA       1  /* database adiministrator - all privileges */
#define _SECLEVEL_USER      2  /* database user - most upd/del/ins privileges */
#define _SECLEVEL_BOOKING   3  /* only booking privileges */
#define _SECLEVEL_READONLY  4  /* only select privileges */
#define _SECLEVEL_NOP       5  /* NO PRIVILEGES */
