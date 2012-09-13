/*D***********************************************************
 * Header:    MPnewlev.h
 *            NEWLEVEL definition for GUI and DBI                 
 *            this is the resolution key for XXXXchoose
 *            and XXXXselect functions
 *
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpmenlev.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/

/* Globalmenu 15 Felder */
int GLOBlevel[] = { _UNDEF, _UNDEF, _KUNDEN, _SPRACHEN, _LAND, _TRAEGER_TYP,
                    _KATEGORIE, _DIENST_TRAEGER, _ANGEBOTS_TYP, _REISENDER_TYP,
                    _SAISON, _PROGRAMM, _DATUM, _DATUM, _UNDEF };

/* Buchung  18 Felder */
int BCHlevel[] =  { _BUCHUNG, _BUCHUNG, _STATUS_WERTE, _DATUM, _ARRANGEMENT,
                  _DIENSTLEISTUNG, _KUNDEN, _KUNDEN, _DIENST_TRAEGER, _DIENST_ANGEBOT,
                  _KOLLEKTIV, _BUCHUNG, _UNDEF, _UNDEF, _UNDEF,
                  _UNDEF, _REISENDER, _TEXTE };
/* Kunden  16 Felder */
int KUNlevel[] = { _UNDEF, _KUNDEN, _UNDEF, _KUNDEN_TYP, _LAND, _WAEHRUNG, _SPRACHEN, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _TEXTE };
/* Reservation Buchungsmaske  8 Felder */
int RESlevel[] = { _REISENDER, _STATUS_WERTE, _DIENST_TRAEGER, _TRAEGER_TYP, _DLG_PART, _DATUM, _DATUM, _KONTINGENT, _TEXTE };
/* Dienstleistungsnehmer DLN Buchungsmaske  6 Felder */
int BMDLNlevel[] = { _REISENDER, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _SPRACHEN };
/* Reisender  14 Felder */
int REIlevel[] = { _UNDEF, _REISENDER, _UNDEF, _UNDEF, _REISENDER_TYP,
                   _STATUS_WERTE, _SPRACHEN, _LAND, _UNDEF, _UNDEF, _UNDEF,
                   _UNDEF, _TEXTE, _TEXTE };
/* Gruppe  7 Felder */
int KOLlevel[] = { _KOLLEKTIV, _REISENDER, _KOLLEKTIV_TYP, _TEXTE, _KUNDEN, _KUNDEN, _UNDEF };
/* Output  4 Felder */
int OUTlevel[] = { _AKTIONEN, _STATUS_WERTE, _STATUS_WERTE, _STATUS_WERTE };
/* Kommission/Reduktion  16 Felder */
int KOMlevel[] = { _KOMMISSION, _STATUS_WERTE, _STATUS_WERTE, _UNDEF, _KUNDEN, _KOSTEN_ART, _KATEGORIE, _REISENDER_TYP, _DIENST_ANGEBOT, _DIENSTLEISTUNG, _DATUM, _DATUM, _KONTINGENT, _BUCHUNG, _TEXTE, _TRAEGER_TYP };
/* Kommissionsdetail / Verknuepfung  6 Felder */
int KOMDlevel[] = { _KOMMISSION, _BUCHUNG, _REISENDER, _KUNDEN, _KOLLEKTIV, _UNDEF };
/* Adresse  9 Felder */
int ADRlevel[] = { _KUNDEN, _REISENDER, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _STATUS_WERTE };


/* Saison  5 Felder */
int SAIlevel[] = { _SAISON, _UNDEF, _UNDEF, _UNDEF, _TEXTE };
/* Programm  4 Felder */
int PRGlevel[] = { _PROGRAMM, _UNDEF, _TEXTE, _SAISON };
/* Arrangement  8 Felder */
int ARRlevel[] = { _ARRANGEMENT, _DATUM, _PROGRAMM, _STATUS_WERTE, _TEXTE, _DIENSTLEISTUNG, _UNDEF, _UNDEF };
/* Dienstleistung  7 Felder */
int DTGlevel[] = { _DIENSTLEISTUNG, _DLG_PART, _TEXTE, _DATUM, _AKTIONEN, _UNDEF, _UNDEF };
/* Dienstleistungsteile  12 Felder */
int DLGlevel[] = { _DLG_PART, _DLG_PART, _DIENST_ANGEBOT, _DATUM, _DATUM, _STATUS_WERTE, _KUNDEN, _UNDEF, _TEXTE, _SAISON, _KUNDEN, _UNDEF };
/* Dienstleistungsangebot  12 Felder */
int DLAlevel[] = { _DIENST_ANGEBOT, _DIENST_ANGEBOT, _UNDEF, _DIENST_TRAEGER, _AKTIONEN, _UNDEF, _ANGEBOTS_TYP, _UNDEF, _TEXTE, _ORT, _ORT, _UNDEF };
/* Aktionen  7 Felder */
int AKTlevel[] = { _AKTIONEN, _STATUS_WERTE, _TEXTE, _STATUS_WERTE, _STATUS_WERTE, _AKTIONS_TYP, _STATUS_WERTE };
/* Aktionsgruppe  3 Felder */
int AKTGlevel[] = { _AKTIONEN, _AKTIONEN, _UNDEF };
/* Host-Kontingent  10 Felder */
int HKONlevel[] = { _HOST_KONT, _KUNDEN, _KUNDEN, _DIENST_ANGEBOT, _DIENSTLEISTUNG, _DATUM, _DATUM, _DATUM, _UNDEF, _TEXTE };
/* Kontingent  6 Felder */
int KONlevel[] = { _KONTINGENT, _HOST_KONT, _KUNDEN, _DATUM, _UNDEF, _TEXTE };
/* Kontingent-Detail  7 Felder */
int KONDlevel[] = { _HOST_KONT, _KONTINGENT, _KATEGORIE, _UNDEF, _UNDEF, _DIENST_TRAEGER, _STATUS_WERTE };
/* Preis  22 Felder */
int PRElevel[] = { _PREIS, _WAEHRUNG, _UNDEF, _UNDEF, _UNDEF, _DATUM, _KUNDEN, _KOSTEN_ART, _TRAEGER_TYP, _KATEGORIE, _REISENDER_TYP, _DIENST_ANGEBOT, _DIENSTLEISTUNG, _DATUM, _DATUM, _KONTINGENT, _STATUS_WERTE, _TEXTE, _ARRANGEMENT, _STATUS_WERTE, _UNDEF, _UNDEF };


/* Tr�gertyp  3 Felder */
int DLTTlevel[] = { _TRAEGER_TYP, _TRAEGER_TYP, _TEXTE };
/* Kategorie 5 Felder */
int KATlevel[] = { _KATEGORIE, _TRAEGER_TYP, _KATEGORIE, _STATUS_WERTE, _TEXTE };
/* Dienstleistungstr�ger  9 Felder */
int DLTlevel[] = { _DIENST_TRAEGER, _KATEGORIE,  _DIENST_TRAEGER, _TRAEGER_TYP, _TEXTE, _DIENST_TRAEGER, _STATUS_WERTE, _UNDEF, _UNDEF };
/* Pixelbilder  7 Felder */
int PCXlevel[] = { _PCX_FILES, _UNDEF, _BEZEICHNUNG, _PCX_FILES, _UNDEF, _UNDEF, _UNDEF };
/* Grafik  3 Felder */
int GRAlevel[] = { _GRAPHIK, _DIENST_TRAEGER, _TEXTE };
/* Kostenart  2 Felder */
int KARlevel[] = { _KOSTEN_ART, _TEXTE };
/* Dienstleistungsangebots-Typ  2 Felder */
int DLATlevel[] = { _ANGEBOTS_TYP, _TEXTE };
/* Kundentyp  3 Felder */
int KUNTlevel[] = { _KUNDEN_TYP, _TEXTE, _UNDEF };
/* Reisendertyp  5 Felder */
int REITlevel[] = { _REISENDER_TYP, _TEXTE, _UNDEF, _UNDEF, _UNDEF };
/* Kollektivtyp  3 Felder */
int KOLTlevel[] = { _KOLLEKTIV_TYP, _TEXTE, _UNDEF };
/* Aktionstyp  9 Felder */
int AKTTlevel[] = { _AKTIONS_TYP, _UNDEF, _TEXTE, _AKTIONS_TYP, _BEZEICHNUNG, _UNDEF, _UNDEF, _UNDEF, _TEXTE };
/* Statuswerte  5 Felder */
int STAlevel[] = { _STATUS_WERTE, _UNDEF, _UNDEF, _UNDEF, _STATUS_WERTE };


/* Sprachen  5 Felder */
int SPRlevel[] = { _SPRACHEN, _UNDEF, _UNDEF, _UNDEF, _UNDEF };
/* Waehrung  4 Felder */
int WHRlevel[] = { _WAEHRUNG, _UNDEF, _UNDEF, _TEXTE };
/* Land  8 Felder */
int LANDlevel[] = { _LAND, _ORT, _WAEHRUNG, _SPRACHEN, _UNDEF, _UNDEF, _TEXTE, _UNDEF };
/* Ort   8 Felder */
int ORTlevel[] = { _ORT, _LAND, _STATUS_WERTE, _UNDEF, _UNDEF, _UNDEF, _UNDEF, _TEXTE };
/* Kurse 6 Felder */
int LWlevel[] = { _LAND, _WAEHRUNG, _STATUS_WERTE, _UNDEF, _UNDEF, _DATUM };


/* Bezeichnung  5 Felder */
int BEZlevel[] = { _SPRACHEN, _BEZEICHNUNG, _BEZEICHNUNG, _SPRACHEN, _UNDEF };
/* Texte  4 Felder */
int TXTlevel[] = { _SPRACHEN, _TEXTE, _SPRACHEN, _TEXTE };
/* Label  6 Felder */
int LABlevel[] = { _LABEL, _SPRACHEN, _UNDEF, _UNDEF, _UNDEF, _UNDEF };
/* Message  4 Felder */
int MSGlevel[] = { _STATUS_WERTE, _MSG, _SPRACHEN, _UNDEF };
/* Help  4 Feld */
int HELPlevel[] = { _STATUS_WERTE, _HELP, _SPRACHEN, _UNDEF };
/* Backup  1 Feld */
int BKPlevel[] = { _UNDEF };
/* Restore  1 Feld */
int RESTlevel[] = { _UNDEF };

/*************************************************************
 * create the 'where to go next' Levels only for DBI
 * index to this structur are the mpobjdef.h object numbers
 *************************************************************/
int *NewLevel[] = {
	NULL,
	SPRlevel,
	STAlevel,
	BEZlevel,
	TXTlevel,
	NULL,
	HELPlevel,
	MSGlevel,
	LABlevel,
	SAIlevel,
	LANDlevel,
	ORTlevel,
	WHRlevel,
	LWlevel,
	NULL,
	DLTTlevel,
	KATlevel,
	DLTlevel,
	DLATlevel,
	AKTTlevel,
	NULL,
	AKTlevel,
	AKTGlevel,
	DLAlevel,
	KUNTlevel,
	KUNlevel,
	DLGlevel,
	DTGlevel,
	NULL,
	PRGlevel,
	ARRlevel,
	NULL,
	KOLTlevel,
	KOLlevel,
	NULL,
	REITlevel,
	REIlevel,
	ADRlevel,
	HKONlevel,
	KONlevel,
	KONDlevel,
	BCHlevel,
	NULL,
	KARlevel,
	KOMlevel,
	KOMDlevel,
	RESlevel,
	PRElevel,
	GRAlevel,
	PCXlevel,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	GLOBlevel,
	OUTlevel,
	BKPlevel,
	RESTlevel,
	NULL,
	NULL,
	NULL,
	BMDLNlevel,
	NULL,
	NULL,
	NULL,
	NULL
};
