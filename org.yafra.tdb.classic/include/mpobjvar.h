/*D***********************************************************
 * Header:    mpobjvar.h
 *            Objektstrukturen f�r das ganze MarcoPolo
 *
 * copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpobjvar.h,v 1.6 2009-01-02 16:51:35 mwn Exp $
*/

// TODO convert all date/time to long (8 bytes - 64 bits) - issue with time in 2038

/************************************************************
 * Sektion:  physische Datenbankobjekte (tables)
 *************************************************************/
/* MAXIMA  8 Felder */
typedef struct {
	int	tabelle;				/* Maximum auf welcher Tabelle */
	int	typ;					/* Typ der Maximumfunktion     */
	int	max_id;				/* Maximum                     */
	short	max_id_null;		/* Nullindikator               */
	int	min_id;				/* Minimum                     */
	short	min_id_null;		/* Nullindikator               */
	int	incr;					/* Inkrementierung             */
	short	incr_null;			/* Nullindikator               */
} MAXIMA;

/* SPRACHEN 8 Felder */
typedef struct {
	int	s_id;					/* Sprachcode                  */
	int	bez_id;				/* Bezeichnung                 */
	int	dialog;				/* Dialogflag                  */
	char	sysbez[_CHAR256];			/* Syscode der SPR   nlsinfo() */
	int	output;
	short	output_null;
	int	gui;
	short	gui_null;
} SPRACHEN;

/* STATUS_WERTE 6 Felder */
typedef struct {
	int	sta_id;				/* Statuswert_Id               */
	char	abk[_CHAR256];		/* Abkuerzung                  */
	char	sta[_CHAR2000];	/* Statuswert                  */
	int	bez_id;				/* Bezeichnungs Id             */
	double	kond;				/* Status-Konditionen          */
	int	typ;					/* Statustyp                   */
} STATUS_WERTE;

/* BEZEICHNUNG 4 Felder */
typedef struct {
	int	bez_id;				/* Beschreibung                */
	int	s_id;					/* Sprachcode                  */
	char	bez[_BEZLEN];		/* effektiver Text             */
	int	typ;					/* Bezeichnungstyp  mpobjdef.h */
} BEZEICHNUNG;

/* TEXTE 5 Felder */
typedef struct {
	int	textid;				/* Beschreibung */
	int	s_id;					/* Sprachcode */
	int	textnr;				/* Zeilennummer */
	char	text[_TEXTLEN];	/* effektiver Text */
	int	typ;					/* Texttyp */
} TEXTE;

/* AKTIONSTEXTE 5 Felder */
typedef struct {
	int	textid;				/* Beschreibung */
	int	s_id;					/* Sprachcode */
	int	textnr;				/* Zeilennummer */
	char	text[_TEXTLEN];	/* effektiver Text */
	int	typ;					/* Aktionstyp */
} AKTIONSTEXTE;

/* HISTORY 6 Felder */
typedef struct {
	int	his_id;				/* Beschreibung */
	int	s_id;					/* Sprachcode */
	int	textnr;				/* Zeilennummer */
	char	text[_TEXTLEN];	/* effektiver Text */
	long long	date;					/* Datum */
	int	typ;					/* Objekttyp */
} HISTORY;

/* HELP 5 Felder */
typedef struct {
	int	help_typ;			/* F�r welches Objekt ist dieses Help */
	int	help_id;				/* Help ID */
	int	s_id;					/* Sprachcode */
	int	textnr;				/* Zeilennummer */
	char	text[_TEXTLEN];	/* effektiver Text */
} HELP;

/* MSG 5 Felder */
typedef struct {
	int	msg_typ;				/* Art der Message */
	int	msg_id;				/* Help ID */
	int	s_id;					/* Sprachcode */
	int	textnr;				/* Zeilennummer */
	char	text[_TEXTLEN];	/* effektiver Text */
} MP_MSG;

/* LABEL 6 Felder */
typedef struct {
	int	label_prg;			/* Label f�r welches Programm */
	int	label_typ;			/* Labeltyp */
	int	stufe1;				/* 3. Dimension */
	int	stufe2;				/* 4. Dimension */
	int	s_id;					/* Sprachcode */
	char	label[_TEXTLEN];	/* Label */
} LABEL;

/* SAISON 8 Felder */
typedef struct {
	int	sai_id;				/* Saison */
	char	code[_CHAR256];	/* Season code */
	short	code_null;			/* null */
	int	bez_id;				/* Description (lang dependend) */
	long long	von;					/* From date */
	long long	bis;					/* To date */
	int	textid;				/* Text */
	short	textid_null;		/* null */
} SAISON;



/************************************************************
 * Sektion:  GEOGRAFIE (tables)
 *************************************************************/

/* WAEHRUNG 8 Felder */
typedef struct {
	int	whr_id;				/* currency */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short textid_null;		/* Nullindikator */
	int	status;				/* state */
	short status_null;		/* Nullindikator */
	char	krzl[_CHAR256];	/* code */
	short krzl_null;			/* Nullindikator */
} WAEHRUNG;

/* LAND 16 Felder */
typedef struct {
	int	land_id;				/* country */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short textid_null;		/* Nullindikator */
	char	krzl[_CHAR256];	/* Abk�rzung */
	short krzl_null;			/* Nullindikator */
	int	haupt_ort;			/* Hauptstadt */
	short haupt_ort_null;	/* Nullindikator */
	int	haupt_whr;			/* Landesw�hrung */
	short haupt_whr_null;	/* Nullindikator */
	int	haupt_spr;			/* Landessprache */
	short haupt_spr_null;	/* Nullindikator */
	double vat;					/* Landessprache */
	short vat_null;			/* Nullindikator */
	char	dateformat[_CHAR256];	/* Datumsformat */
	short datef_null;			/* Nullindikator */
} LAND;

/* ORT 13 Felder */
typedef struct {
	int	ort_id;				/* city */
	int	bez_id;				/* Bezeichnung */
	int	land_id;				/* zu welchem Land geh�rt es */
	int	textid;				/* Beschreibung */
	short textid_null;		/* Nullindikator */
	char	krzl[_CHAR256];	/* Abk�rzung */
	short krzl_null;			/* Nullindikator */
	int	zeitver;				/* Zeitverschiebung */
	short zeitver_null;		/* Nullindikator */
	int	koord1;				/* 1. Koordinate */
	short koord1_null;		/* Nullindikator */
	int	koord2;				/* 2. Koordinate */
	short koord2_null;		/* Nullindikator */
	int	ort_typ;
	short	orttyp_null;
} ORT;

/* LAND_WHR 7 Felder */
typedef struct {
	int	land_id;				/* Land */
	int	whr_id;				/* W�hrung */
	int	kurs_typ;			/* Art des Kurses (Bar/Devisen) */
	double	a_kurs;			/* Ankaufskurs */
	double	v_kurs;			/* Verkaufskurs */
	long long von_dat;
	short von_dat_null;
} LAND_WHR;

/* LAND_SPR 2 Felder */
typedef struct {
	int land_id;				/* Land */
	int s_id;					/* Sprache */
} LAND_SPR;





/************************************************************
 * Sektion:  PERSONEN (tables)
 *************************************************************/

/* PERSONEN 9 Felder */
typedef struct {
	int	pers_id;				/* Person */
	int	pers_typ;			/* Person Typ (privat/firma)  */
	char	name[_CHAR512];	/* Personenname */
	int	s_id;					/* Sprache */
	int	sta_id;				/* Personenstatus */
	short	sta_id_null;		/* Nullindikator */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} PERSONEN;

/* REISENDER_TYP 10 Felder */
typedef struct {
	int	rkr_id;				/* Reisendertyp */
	char	dlncode[_CHAR256];		/* Reisendertyp Code */
	short	dlncode_null;		/* Nullindikator */
	int	bez_id;				/* Bezeichnung */
	int	vonalter;			/* Reisendertyp von Alter */
	short	vonalter_null;		/* Nullindikator */
	int	bisalter;			/* Reisendertyp bis Alter */
	short	bisalter_null;		/* Nullindikator */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} REISENDER_TYP;

/* REISENDER 17 Felder */
typedef struct {
	int	pers_id;				/* Reisender-ID */
	char	vor[_CHAR512];				/* Vorname */
	int	rkr_id;				/* Reisendertyp */
	int	sex;					/* Geschlechtsstatus */
	short sex_null;			/* Nullindikator */
	int   mutters_id;				/*  */
	short mutters_id_null;		/* Nullindikator */
	char	age[_CHAR256];			/* Alter/Alterscode */
	short	age_null;			/* Nullindikator */
	char	passnr[_CHAR256];			/* Passport Nummer */
	short	passnr_null;		/* Nullindikator */
	char	attr1[_CHAR2000];			/* Attribut 1 */
	short	attr1_null;			/* Nullindikator */
	char	attr2[_CHAR2000];			/* Attribut 2 */
	short	attr2_null;			/* Nullindikator */
	int   textid;				/* description text */
	short textid_null;		/* Nullindikator */
} REISENDER;

/* PERSADR 38 Felder */
typedef struct {
	int	pers_id;				/* Ref: Person */
	int	adr_typ;
	char	ans[_CHAR256];				/* Anschrift */
	short	ans_null;			/* Nullindikator */
	char	adr1[_CHAR2000];				/* Adresse 1 */
	short	adr1_null;			/* Nullindikator */
	char	adr2[_CHAR2000];				/* Adresse 2 */
	short	adr2_null;			/* Nullindikator */
	char	adr3[_CHAR2000];				/* Adresse 3 */
	short	adr3_null;			/* Nullindikator */
	char	plz[_CHAR256];				/* Postleitzahl */
	short	plz_null;			/* Nullindikator */
	char	ort[_CHAR256];				/* Ort */
	short ort_null;
	char kant[_CHAR256];
	short kant_null;
	int land_id;
	short land_id_null;
	int	sta_id;				/* Versandcode */
	short	sta_id_null;		/* Nullindikator */
	int haupt_flag;
	short haupt_flag_null;
	int rch_flag;
	short rch_flag_null;
	int mail_flag;
	short mail_flag_null;
	char tel[_CHAR256];
	short tel_null;
	char handy[_CHAR256];
	short handy_null;
	char fax[_CHAR256];
	short fax_null;
	char tlx[_CHAR256];
	short tlx_null;
	char email[_CHAR2000];
	short email_null;
	char web[_CHAR2000];
	short web_null;
} PERSADR;

/* KUNDEN_TYP 6 Felder */
typedef struct {
	int	k_typ_id;			/* Kundentyp */
	char	kuncode[_CHAR256];		/* Kundentyp Code */
	short	kuncode_null;		/* Nullindikator */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} KUNDEN_TYP;

/* KUNDEN 20 Felder */
typedef struct {
	int	pers_id;				/* Kunden-ID */
	char	tel[_CHAR256];				/* Telephon-Nummer */
	short	tel_null;			/* Nullindikator */
	char	handy[_CHAR256];			/* Kanton, Kreis */
	short	handy_null;			/* Nullindikator */
	char	fax[_CHAR256];				/* Faxnummer */
	short	fax_null;			/* Nullindikator */
	char	tlx[_CHAR256];				/* Telexnummer */
	short	tlx_null;			/* Nullindikator */
	char	email[_CHAR2000];			/* Kanton, Kreis */
	short	email_null;			/* Nullindikator */
	char	web[_CHAR2000];			/* Kanton, Kreis */
	short	web_null;			/* Nullindikator */
	char	konto[_CHAR256];			/* Kontonummer */
	short	konto_null;			/* Nullindikator */
	int	leiter;			/* Name Geschaeftsleiter */
	short	leiter_null;		/* Nullindikator */
	char	attr1[_CHAR2000];			/* Attribut 1 */
	short	attr1_null;			/* Nullindikator */
	char	attr2[_CHAR2000];			/* Attribut 2 */
	short	attr2_null;			/* Nullindikator */
	int	k_typ_id;			/* Kundentyp */
	int	whr_id;				/* W�hrung */
} KUNDEN;

/* KOLLEKTIV_TYP 6 Felder */
typedef struct {
	int	k_typ_id;			/* Kollektiv-Typ */
	char	kolcode[_CHAR256];		/* Kollektivtyp Code */
	short	kolcode_null;		/* Nullindikator */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} KOLLEKTIV_TYP;

/* KOLLEKTIV 15 Felder */
typedef struct {
	int	k_id;					/* Kollektiv */
	char	ref[_CHAR256];		/* Referenz */
	short	ref_null;			/* Nullindikator */
	char	name[_CHAR512];	/* Bezeichnung */
	short	name_null;
	int	k_typ_id;			/* Kollektivtyp */
	int	kbst;					/* Kunde / Buchungsstelle */
	int	k_sta;				/* Kollektiv-Status */
	short	k_sta_null;			/* Nullindikator */
	int	hauptpers;			/* Bezugsperson im Kollektiv */
	short	hauptpers_null;	/* Nullindikator */
	int	kid;					/* Kunde / Rechnungsempfaenger */
	short	kid_null;			/* Nullindikator */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} KOLLEKTIV;






/************************************************************
 * Sektion:  STAMMDATEN / RESERVATIONSKERN (tables)
 *************************************************************/

/* TRAEGER_TYP 6 Felder */
typedef struct {
	int	typ_id;				/* Traegertyp */
	int	bez_id;				/* Bezeichnung */
	int	h_typ_id;			/* N�chst h�herer Tr�gertyp */
	int	host_typ;			/* H�chster Tr�gertyp */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} TRAEGER_TYP;

/* KATEGORIE 9 Felder */
typedef struct {
	int	kat_id;				/* Kategorie */
	int	bez_id;				/* Name */
	int	h_kat_id;			/* �bergeordnete Kategorie */
	short	h_kat_id_null;		/* Nullindikator */
	int	typ_id;				/* Traegertyp */
	int	ga;					/* gr. Attribut */
	short	ga_null;				/* Nullindikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} KATEGORIE;

/* DIENST_TRAEGER 17 Felder */
typedef struct {
	int	dlt_id;				/* Dienstleistungstraeger */
	char	code[_CHAR256];
	short	code_null;
	int	bez_id;				/* Bezeichnung */
	int	kat_id;				/* Kategorie Identifikation */
	short	kat_id_null;		/* Nullindikator */
	int	h_dlt_id;			/* naechst hoehere DLT */
	int	dlt_grp_id;			/* naechst hoehere DLT-BEZ_ID */
	int	host_id;				/* Haupt DLT */
	int	typ_id;				/* Traegertyp */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	stufe;				/* Stufe fuer Preisbildung */
	int	sta_id;				/* Bestplatz Status */
	short	sta_id_null;		/* Nullindikator */
	int	anz;
	short	anz_null;
} DIENST_TRAEGER;

/* ANGEBOTS_TYP 4 Felder */
typedef struct {
	int	art_id;				/* Angebotstyp */
	int	bez_id;				/* Name */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} ANGEBOTS_TYP;

/* AKTIONS_TYP 5 Felder */
typedef struct {
	int	a_typ_id;			/* Aktionstyp */
	int	bez_id;				/* Bezeichnung */
	char	proz[_PROZLEN];			/* Prozess */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} AKTIONS_TYP;

/* AKTIONSPARA 11 Felder */
typedef struct {
	int	a_typ_id;			/* Aktionstyp */
	int	nr;					/* Parameter Nummer */
	int	typ;					/* Typ des Parameters (als Objekt) */
	short typ_null;	      /* Nullindikator */
	char	bez[_PARALEN];	/* Parameterbezeichnung */
	int 	muss;					/* Parameter obligatorisch (true/false) */
	short muss_null;			/* Nullindikator */
	int	flag;					/* Ist Parameter nur ein Flag oder kommt ein Wert dazu*/
	short flag_null;			/* Nullindikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} AKTIONSPARA;

/* AKTIONEN 15 Felder */
typedef struct {
	int	akt_id;				/* Aktion */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	a_flag;				/* Ausfuehrungsflag */
	short	a_flag_null;		/* Nullindikator */
	int	b_flag;				/* Reservationsflag als Startkriterium */
	short	b_flag_null;		/* Nullindikator */
	int	m_flag;				/* Medium Flag */
	short	m_flag_null;		/* Nullindikator */
	int	a_typ_id;			/* Aktionstyp */
	int   b2_flag;    	   /* Reservationsflag als Ziel */
	short b2_flag_null;  	/* Nullindikator */
	int	file_id;
	short	fileid_null;
} AKTIONEN;

/* AKTIONSGRP 4 Felder */
typedef struct {
	int	parentakt;			/* Vater Aktion */
	int	childakt;			/* Kind  Aktion */
	int	ord;					/* Ordnung */
	int	h_akt_id;			/* Hostaktion */
} AKTIONSGRP;

/* DIENST_ANGEBOT 16 Felder */
typedef struct {
	int	dla_id;				/* Dienstleistungsangebot */
	char	code[_CHAR256];
	short	code_null;
	int	h_dla_id;			/* �bergeordnetes Angebot */
	int	ord;					/* Reihenfolge auf Stufe */
	int	dlt_id;				/* Dienstleistungstraeger */
	int	bez_id;				/* Name */
	int	akt_id;				/* Default-Aktion */
	char	ort[_CHAR256];				/* Ortschaft */
	int	art_id;				/* Angebotstyp */
	int	dau;					/* Dauer in dezimal Std. */
	short	dau_null;			/* Nullintikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	von;					/* Von-Abkuerzung */
	int	nach;					/* Nach-Abkuerzung */
} DIENST_ANGEBOT;

/* DLG_PART 22 Felder */
typedef struct {
	int	dl_id;				/* Dienstleistung */
	char	code[_CHAR256];
	short	code_null;
	int	bez_id;				/* Bezeichnung */
	int	h_dl_id;				/* �bergeordnete Dienstleistung */
	int	dla_id;				/* Angebot */
	int	ord;					/* Reihenfolge */
	short	ord_null;			/* Nullindikator */
	long long	a_zeit;				/* Anfangszeit */
	short	a_zeit_null;		/* Nullindikator */
	long long	e_zeit;				/* Endzeit */
	short	e_zeit_null;		/* Nullindikator */
	int	res_f;				/* Flag zur Steuerung der Reservation */
	int	kid;					/* Reservationsadresse */
	short	kid_null;			/* Nullindikator */
	char	konto[_CHAR256];	/* Ertragskontonummer */
	short	konto_null;			/* Nullindikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
	int	rechst;				/* Rechnungsstelle */
	short	rechst_null;		/* Nullindikator */
} DLG_PART;

/* DIENSTLEISTUNG 11 Felder */
typedef struct {
	int	dlg_id;				/* Dienstleistung */
	char	code[_CHAR256];
	short	code_null;
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
	long long	a_zeit;				/* Anfangszeit */
	short	a_zeit_null;		/* Nullindikator */
	int	akt_id;				/* Aktions_id */
	short	akt_id_null;		/* Nullindikator */
} DIENSTLEISTUNG;

/* DLG_DLG 3 Felder */
typedef struct {
	int	dlg_id;				/* Dienstleistung */
	int	dl_id;				/* Teil Dienstleistung */
	int	ord;					/* Reihenfolge auf Stufe */
} DLG_DLG;

/* PROGORAMM 7 Felder */
typedef struct {
	int	prg_id;				/* Programm */
	char	code[_CHAR256];
	short	code_null;
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
} PROGRAMM;

/* ARRANGEMENT 9 Felder */
typedef struct {
	int	arr_id;				/* Arrangement */
	char	code[_CHAR256];
	short	code_null;
	int	bez_id;				/* Bezeichnung */
	long long	a_dat;				/* Datum des Arrangements */
	int	prg_id;				/* Programm */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
} ARRANGEMENT;

/* ARR_DLG 4 Felder */
typedef struct {
	int	arr_id;				/* Arrangement */
	int	teil;					/* Teilst�ck des Arrangements */
	int	prio;					/* Prioritaet bei parallelen Angeboten */
	int	dlg_id;				/* Dienstleistung */
} ARR_DLG;





/************************************************************
 * Sektion:  KONTINGENTIERUNG (tables)
 *************************************************************/

/* HOST_KONT 21 Felder */
typedef struct {
	int	hostkont_id;		/* Host-Kontingent */
	int	bez_id;				/* Bezeichnung */
	int	from_pers;			/* Inhaber (wenn wir es selber sind -1) */
	int	kbst;					/* Buchungsstelle */
	int	dla_id;				/* Dienstleistungsangebot id */
	short	dla_id_null;		/* Nullindikator */
	int	dl_id;				/* Dienstleistung */
	short	dl_id_null;			/* Nullindikator */
	long long	dl_vondat;			/* DL von Datum */
	short	dl_vondat_null;	/* Nullindikator */
	long long	dl_bisdat;			/* DL bis Datum */
	short	dl_bisdat_null;	/* Nullindikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
	long long	opt_dat;				/* Optionsdatum */
	short	opt_dat_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
	char	ref[_CHAR256];		/* Referenznummer */
	short	ref_null;			/* Nullindikator */
	int	history;				/* Texteintrag */
	short	history_null;		/* Nullindikator */
} HOST_KONT;

/* KONTINGENT 11 Felder */
typedef struct {
	int	kont_id;				/* Kontingent */
	int	bez_id;				/* Kontingents Bezeichnung */
	int	hostkont_id;		/* zu welchem Host Kontingent */
	int	kunden_id;			/* an welchen Kunden */
	long long	opt_dat;				/* Optionsdatum */
	short	opt_dat_null;		/* Nullindikator */
	char	ref[_CHAR256];		/* Referenznummer */
	short	ref_null;			/* Nullindikator */
	int	sai_id;				/* Saison */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} KONTINGENT;

/* KONT_DETAIL 14 Felder */
typedef struct {
	int	hostkont_id;		/* Host-Kontingent */
	int	kont_id;			/* Kontingent */
	int	kat_id;				/* Kategorien */
	int	dlt_id;				/* Dienstleistungstraeger id */
	int	sta_id;				/* over booking factor - typ=117 */
	short	sta_id_null;	/* Nullindikator */
	int	anz;				/* Anzahl */
	short	anz_null;		/* Nullindikator */
	int   busy;				/* Anzahl besetzter Plaetze */
	short busy_null;		/* Nullindikator */
	int	minanz;				/* Mindesanzahl von Plaetzen die bestzt sein muessen*/
	short minanz_null;		/* Nullindikator */
	long long von_dat;			/* date of dynamic DLs */
	long long bis_dat;
} KONT_DETAIL;


/************************************************************
 * Sektion:  RESERVATION / PREISE (tables)
 *************************************************************/

/* MP_PROFIL 16 Felder */
typedef struct {
	int	mpid;
	char mpuser[_CHAR128];	/* User           PRIMAER SCHLUESSEL */
	int	bchst;				/* Booking office PRIMAER SCHLUESSEL */
	int	seclevel;			/* security level */
	int	s_id;				/* language       */
	int	land_id;			/* country        */
	int	dltt_id;			/* Traegertyp     */
	int	dlt_id;				/* Diensttraeger  */
	int	kat_id;				/* Kategorie      */
	int	dlat_id;			/* Angebotstyp    */
	int	dlnt_id;			/* Reisendertyp   */
	int	sai_id;				/* Saison         */
	int	prg_id;				/* Programm       */
	long long	a_zeit;			/* Anfangs-Zeit/Dat */
	long long	e_zeit;			/* End-Zeit/Dat   */
	int	p_range;			/* Planungsboardrange */
} MP_PROFIL;




/************************************************************
 * Sektion:  RESERVATION / PREISE (tables)
 *************************************************************/

/* BUCHUNG 25 Felder */
typedef struct {
	int	d_bid;				/* Buchungsnummer der Hauptbuchung bei Doppelbuchungen */
	int	bid;					/* Buchungsnummer */
	char	ref[_CHAR256];		/* Referenznummer */
	int	arr_id;				/* Arrangement */
	int	kid;					/* Kunde / Rechnungsempfaenger */
	int	sach;					/* Sachbearbeiter */
	int	anw;					/* Anwender */
	long long	b_dat;				/* Buchungsdatum */
	short	b_dat_null;			/* Nullindikator */
	long long	m_dat;				/* Modifikationsdatum */
	short	m_dat_null;			/* Nullindikator */
	int	opt_bst;				/* Option Buchungsstelle */
	short	opt_bst_null;		/* Nullindikator */
	int	opt_kid;				/* Option Kunde */
	short	opt_kid_null;		/* Nullindikator */
	int	sta;					/* Status bei History,Doppelbuchung,Warteliste*/
	int	ast;					/* Aktionsstatus */
	int	sai_id;				/* Saison */
	int	k_id;					/* Kollektiv */
	int	mpid;					/* MP Profil ID */
	short mpid_null;
	int	history;				/* Texteintrag */
	short	history_null;		/* Nullindikator */
	int   b_text;  	      /* Buchungstext */
	short b_text_null;	   /* Nullindikator */
} BUCHUNG;

/* BCH_DLN 2 Felder */
typedef struct {
	int	bid;					/* Buchungsnummer */
	int	dln_id;				/* Dienstleistungsnehmer / Reisender Nummer */
} BCH_DLN;

/* AKT_DETAIL 15 Felder */
typedef struct {
	int	bid;					/* Buchungs Id */
	int	pers_id;				/* Reisender Id */
	int	dlg_id;				/* Dienstleistungs Id */
	int	dl_id;				/* TEIL-Dienstleistungs Id */
	int	teil;					/* Teilstueck */
	int	akt_id;				/* Aktions Id */
	int	ord;					/* Reihenfolge */
	int	a_typ_id;			/* Aktions Typ mit System Befehl */
	int	z_flag;				/* Zustands Flag */
	int	akt_nr;				/* fortlaufende Nummer pro a_typ_id */
	int	sai_id;				/* Saison Id */
	int	parentakt;			/* Vater Aktion */
	long long	exec_dat;			/* letztes Ausfuehrungsdatum */
	int	file_id;
	short	fileid_null;
} AKT_DETAIL;

/* KOSTEN_ART 4 Felder */
typedef struct {
	int	kar_id;				/* Kostenart Id */
	int	bez_id;				/* Bezeichnung */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} KOSTEN_ART;

/* KOMMISSION 31 Felder */
typedef struct {
	int	komm_id;				/* Kommissions Nummer */
	int	bez_id;				/* Bezeichnungs Id */
	int	satz_art;			/* Art der Satzes (Prozent, Absolut) */
	double satz;				/* Kommissionssatz */
	int	komm_typ;			/* Kommissionstyp #REISENDER, #GRUPPE, #KUNDE */
	int	kbst;					/* Buchungsstelle */
	int	kar_id;				/* Kostenart */
	short kar_id_null;		/* Nullindikator */
	int	dltt_id;				/* Traegertyp */
	short dltt_id_null;		/* Nullindikator */
	int	kat_id;				/* Kategorie */
	short kat_id_null;		/* Nullindikator */
	int	rkr_id;				/* Reisendertyp */
	short rkr_id_null;		/* Nullindikator */
	int	dla_id;				/* Dienstleistungsangebot */
	short dla_id_null;		/* Nullindikator */
	int	dl_id;				/* Dienstleistung */
	short dl_id_null;			/* Nullindikator */
	long long	dl_vondat;			/* DL von Datum */
	short	dl_vondat_null;	/* Nullindikator */
	long long	dl_bisdat;			/* DL bis Datum */
	short	dl_bisdat_null;	/* Nullindikator */
	int	kont_id;				/* Kontingent */
	short kont_id_null;		/* Nullindikator */
	int	bid;					/* Buchungs Id */
	short bid_null;			/* Nullindikator */
	int	history;				/* History */
	short history_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
} KOMMISSION;

/* MP_ARRKOM 3 Felder */
typedef struct {
	int	arr_id;				/* Arrangement ID */
	int	komm_id;				/* Kommissions ID */
	int	komm_bezid;       /* Kommissions BEZID */
} MP_ARRKOM;

/* KOMM_DETAIL 7 Felder */
typedef struct {
	int	komm_id;				/* Kommissions Nummer */
	int	bid;					/* Buchung */
	int	dln_id;				/* Reisender */
	int	kun_id;				/* Kunde */
	int	kol_id;				/* Kollektiv */
	int	prio;					/* Typ */
	short prio_null;			/* Nullindikator */
} KOMM_DETAIL;

/* RESERVATION 21 Felder */
typedef struct {
	int	pers_id;				/* Reisender */
	int	dlg_id;				/* Dienstleistung */
	int	dl_id;				/* Teil Dienstleistung */
	int	teil;					/* Teilst�ck des Arrangements */
	int	dlt_id;				/* Dienstleistungstraeger */
	int	typ_id;				/* Dienstleistungstraeger Typ */
	int	bid;					/* Buchungsnummer */
	int	kont_id;				/* Kontingent */
	int	kat_id;				/* Kategorie */
	int	k_kon;				/* Kundenkonditionen */
	short	k_kon_null;			/* Nullindikator */
	int	b_kon;				/* Buchungskonditionen */
	short	b_kon_null;			/* Nullindikator */
	int	r_sta;				/* Reservationsstatus */
	int	sai_id;				/* Saison */
	long long	a_zeit;				/* Anfangszeitpunkt f�r zeitlose DL */
	short a_zeit_null;		/* Nullindikator */
	long long	e_zeit;				/* Endzeitpunkt f�r zeitlose DL */
	short e_zeit_null;		/* Nullindikator */
	int	textid;				/* Text */
	short textid_null;		/* Nullindikator */
} RESERVATION;

/* PREIS 44 Felder */
typedef struct {
	int	pre_id;				/* Preis ID */
	double	apr;				/* Ankaufspreis */
	double	epr;				/* Einstandspreis */
	double	vpr;				/* Verkaufspreis */
	long long	glt;					/* gueltig ab */
	int	whr_id;				/* W�hrung */
	int	kbst;					/* Buchungsstelle */
	int	kar_id;				/* Kostenart */
	short kar_id_null;		/* Nullindikator */
	int	dltt_id;				/* Traegertyp */
	short dltt_id_null;		/* Nullindikator */
	int	kat_id;				/* Kategorie */
	short kat_id_null;		/* Nullindikator */
	int	rkr_id;				/* Reisendertyp */
	short rkr_id_null;		/* Nullindikator */
	int	dla_id;				/* Dienstleistungsangebot */
	short dla_id_null;		/* Nullindikator */
	int	arr_id;
	short	arr_id_null;
	int	dl_id;				/* Dienstleistung */
	short dl_id_null;			/* Nullindikator */
	int	ext_id;
	short	ext_id_null;
	long long	dl_vondat;			/* DL von Datum */
	short	dl_vondat_null;	/* Nullindikator */
	long long	dl_bisdat;			/* DL bis Datum */
	short	dl_bisdat_null;	/* Nullindikator */
	int	kont_id;				/* Kontingent */
	short kont_id_null;		/* Nullindikator */
	int	sta_id;				/* Preisstatus */
	short sta_id_null;		/* Nullindikator */
	int	textid;				/* Textverweis */
	short	textid_null;		/* Nullindikator */
	int	history;				/* History */
	short	history_null;		/* Nullindikator */
	int	sai_id;				/* Saison */
	int	unit_typ;
	short	unit_typ_null;
	int	unit_von;
	short	unit_von_null;
	int	unit_bis;
	short	unit_bis_null;
	int	dau;
	short	dau_null;
	long long	dau_von;
	short	dau_von_null;
	long long	dau_bis;
	short	dau_bis_null;
} PREIS;

/* KAPA(ZITAET) 13 Felder */
typedef struct {
	int	kat_id;				/* Kategorie ID */
	int	katbez_id;			/* Kategoriebezeichnungs ID */
	int	tdl_id;				/* Teildienstleistung dlg_parts ID */
	int	tdlbez_id;			/* Teildienstleistung dlg_parts BEZ ID */
	int	pre_id;				/* Preis */
	int	anz;					/* Maxanzahl */
	short anz_null;			/* Nullindikator */
	int	busy;					/* Plaetze */
	short busy_null;			/* Nullindikator */
	double	vpr;				/* Verkaufspreis */
	short vpr_null;			/* Nullindikator */
	long long von_dat; /* Datum f�r dynamische DLs */
	long long bis_dat;
} KAPA;






/************************************************************
 * Sektion:  GRAFIK (tables)
 *************************************************************/

/* GRAFIK 5 Felder */
typedef struct {
	int	gra_id;				/* Grafik Identifikation */
	int   bez_id;     	   /* Bezeichnung */
	int	dlt_id;				/* DLT der ersten Stufe des Bildes */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} GRAPHIK;

/* PCX_FILES 10 Felder */
typedef struct {
	int	pcx_id;				/* Pixelbild */
	int	bez_id;				/* Bezeichnung */
	char	filename[_CHAR2000];		/* Filename */
	int	x;						/* rel. X-Wert */
	short	x_null;				/* Nullindikator */
	int	y;						/* rel. Y-Wert */
	short	y_null;				/* Nullindikator */
	int	typ;					/* Pixelbild f�r welchen Typ von Objekt */
	int   typcode;				/* effektiver Wert des obigen Typs */
	int	folge;				/* Reihenfolge */
} PCX_FILES;

/* GRAFORM 3 Felder */
typedef struct {
	int	gra_id;			/* Grafik Identifikation */
	int   formnr;        /* Grafik Format Nummer */
	char  form[_CHAR256]; /* Grafik Format Inhalt */
} GRAFORM;

/* REGIONS 6 Felder */
typedef struct {
	int	host_id;			/* DLT der ersten Stufe des Bildes */
	int	h_dlt_id;		/* DLT der �bergeordneten Stufe des Bildes */
	int	dlt_id;			/* DLT der Stufe der Region */
	int	folge;			/* Reihenfolge der Punkte bei der Definition der Region */
	int	stufe;			/* Traegertyp */
	int	nummer;			/* Absolute Punktnummer im GraphikFile */
} REGIONS;






/************************************************************
 * Sektion:  logische Datenbankobjekte (views)
 *************************************************************/

/* SPR_VIEW 5 Felder */
typedef struct {
	int	s_id;
	char	bez[_BEZLEN];
	int	bezsprid;
	int	dialog;
	char	sysbez[_CHAR256];
} SPR_VIEW;

/* STA_VIEW 7 Felder */
typedef struct {
	int	sta_id;
	char	abk[_CHAR256];
	char	sta[_CHAR2000];
	char	bez[_BEZLEN];
	int	s_id;
	double	kond;
	int	typ;
} STA_VIEW;

/* SAI_VIEW 7 Felder */
typedef struct {
	int	sai_id;
	char	bez[_BEZLEN];
	int	s_id;
	long long	von;
	long long	bis;
	int	textid;
	short	textid_null;
} SAI_VIEW;



/* LAND_VIEW 15 Felder */
typedef struct {
	int	land_id;
	char	bez[_BEZLEN];
	int	s_id;
	char	krzl[_CHAR256];
	short	krzl_null;
	int	haupt_ort;
	short	haupt_ort_null;
	int	haupt_spr;
	short	haupt_spr_null;
	int	haupt_whr;
	short	haupt_whr_null;
	int	textid;
	short	textid_null;
	double	vat;
	short	vat_null;
} LAND_VIEW;






/* KUN_VIEW 27 Felder */
typedef struct {
	int	kun_id;					/* Person */
	char	name[_CHAR512];
	char	ort[_CHAR256];
	int	s_id;
	int	sta_id;
	short	sta_id_null;
	int	textid;
	short	textid_null;
	char	kant[_CHAR256];			/* Kanton, Kreis */
	short	kant_null;			/* Nullindikator */
	char	tel[_CHAR256];				/* Telephon-Nummer */
	short	tel_null;			/* Nullindikator */
	char	fax[_CHAR256];				/* Faxnummer */
	short	fax_null;			/* Nullindikator */
	char	tlx[_CHAR256];				/* Telexnummer */
	short	tlx_null;			/* Nullindikator */
	char	konto[_CHAR256];			/* Kontonummer */
	short	konto_null;			/* Nullindikator */
	int	leiter;				/* Name Geschaeftsleiter */
	short	leiter_null;		/* Nullindikator */
	char	attr1[_CHAR2000];			/* Attribut 1 */
	short	attr1_null;			/* Nullindikator */
	char	attr2[_CHAR2000];			/* Attribut 2 */
	short	attr2_null;			/* Nullindikator */
	int	k_typ_id;			/* Kundentyp */
	int	land_id;				/* Land */
	int	whr_id;				/* W�hrung */
} KUN_VIEW;


/* DLN_VIEW 24 Felder */
typedef struct {
	int	dln_id;				/* Person */
	char	name[_CHAR512];			/* Personenname */
	char	vor[_CHAR512];				/* Vorname */
	char	ort[_CHAR256];				/* Ort */
	int	s_id;					/* Sprache */
	int	sta_id;				/* Personenstatus */
	short	sta_id_null;		/* Nullindikator */
	int	textid;				/* Text */
	short	textid_null;		/* Nullindikator */
	int	rkr_id;				/* Reisendertyp */
	int	sex;					/* Geschlechtsstatus */
	short sex_null;			/* Nullindikator */
	int   ext_txt;				/* Externer Text */
	short ext_txt_null;		/* Nullindikator */
	int   land_id;				/* Herkunfts Land */
	short land_id_null;		/* Nullindikator */
	char	age[_CHAR256];			/* Alter/Alterscode */
	short	age_null;			/* Nullindikator */
	char	passnr[_CHAR256];			/* Passport Nummer */
	short	passnr_null;		/* Nullindikator */
	char	attr1[_CHAR2000];			/* Attribut 1 */
	short	attr1_null;			/* Nullindikator */
	char	attr2[_CHAR2000];			/* Attribut 2 */
	short	attr2_null;			/* Nullindikator */
} DLN_VIEW;

/* RKR_VIEW 11 Felder */
typedef struct {
	int	rkr_id;			/* Reisendertyp */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	textid;			/* Text */
	short	textid_null;	/* Nullindikator */
	char	dlncode[_CHAR256];		/* Reisendertyp Code */
	short	dlncode_null;		/* Nullindikator */
	int	vonalter;			/* Reisendertyp von Alter */
	short	vonalter_null;		/* Nullindikator */
	int	bisalter;			/* Reisendertyp bis Alter */
	short	bisalter_null;		/* Nullindikator */
} RKR_VIEW;

/* MPV_DLNADR 18 Feld */
typedef struct {
	int	pers_id;				/* Ref: Person */
	char	ans[_CHAR256];				/* Anschrift */
	short	ans_null;			/* Nullindikator */
	char	name[_CHAR512];			/* Personenname */
	char	vor[_CHAR512];				/* Vorname */
	char	adr1[_CHAR2000];			/* Adresse 1 */
	short	adr1_null;			/* Nullindikator */
	char	adr2[_CHAR2000];			/* Adresse 2 */
	short	adr2_null;			/* Nullindikator */
	char	adr3[_CHAR2000];			/* Adresse 3 */
	short	adr3_null;			/* Nullindikator */
	char	plz[_CHAR256];				/* Postleitzahl */
	short	plz_null;			/* Nullindikator */
	char	ort[_CHAR256];				/* Ort */
	int   land_id;				/* Herkunfts Land */
	short land_id_null;		/* Nullindikator */
	int	sta_id;				/* Versandcode */
	short	sta_id_null;		/* Nullindikator */
} MPV_DLNADR;


/* MPV_KUNADR 22 Feld */
typedef struct {
	int	pers_id;				/* Ref: Person */
	char	ans[_CHAR256];				/* Anschrift */
	short	ans_null;			/* Nullindikator */
	char	name[_CHAR512];			/* Personenname */
	char	adr1[_CHAR2000];			/* Adresse 1 */
	short	adr1_null;			/* Nullindikator */
	char	adr2[_CHAR2000];			/* Adresse 2 */
	short	adr2_null;			/* Nullindikator */
	char	adr3[_CHAR2000];			/* Adresse 3 */
	short	adr3_null;			/* Nullindikator */
	char	plz[_CHAR256];				/* Postleitzahl */
	short	plz_null;			/* Nullindikator */
	char	ort[_CHAR256];				/* Ort */
	char	kant[_CHAR256];			/* Kanton, Kreis */
	short	kant_null;			/* Nullindikator */
	int	land_id;				/* Land */
	int	sta_id;				/* Versandcode */
	short	sta_id_null;		/* Nullindikator */
	int	k_typ_id;			/* Kundentyp */
	char	tel[_CHAR256];				/* Telephon-Nummer */
	short	tel_null;			/* Nullindikator */
	char	fax[_CHAR256];				/* Faxnummer */
	short	fax_null;			/* Nullindikator */
} MPV_KUNADR;

/* TTYP_VIEW 5 Felder */
typedef struct {
	int	spr;				/* Sprachcode */
	int	id;				/* TYP_id */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	hid;				/* TYP_id */
	char	hbez[_BEZLEN];		/* Bezeichnung */
} TTYP_VIEW;

/* KAT_VIEW 10 Felder */
typedef struct {
	int	kat_id;				/* Kategorie */
	char	bez[_BEZLEN];				/* Bezeichnung */
	int	s_id;					/* Sprachcode */
	int	h_kat_id;			/* �bergeordnete Kategorie */
	short	h_kat_id_null;		/* Nullindikator */
	int	typ_id;				/* Traegertyp */
	int	ga;					/* gr. Attribut */
	short	ga_null;				/* Nullindikator */
	int	textid;				/* Beschreibung */
	short	textid_null;		/* Nullindikator */
} KAT_VIEW;

/* TRAEGER_VIEW 6 Felder */
typedef struct {
	int	spr;				/* Sprachcode */
	int	typ;				/* Traeger_typ */
	int	id;				/* DLT_id */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	hid;				/* DLT_id */
	int	host;				/* DLT_id */
} TRAEGER_VIEW;

/* DLT_VIEW 11 Felder */
typedef struct {
	int	dlt_id;        /* Dienstleistungstraeger */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	kat_id;			/* Kategorie Identifikation */
	short	kat_id_null;	/* Nullindikator */
	int	h_dlt_id;		/* naechst hoehere DLT */
	int	host_id;			/* Haupt DLT */
	int	typ_id;			/* Traegertyp */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
	int	stufe;			/* Stufe fuer Preisbildung */
} DLT_VIEW;

/* AKT_VIEW 5 Felder */
typedef struct {
	int	id;				/* AktionsId */
	char	bez[_BEZLEN];			/* Bezeichnung */
	char	ubez[_BEZLEN];		/* Bezeichnung */
	int	ord;				/* Reihenfolge */
	int	spr;				/* Sprachcode */
} AKT_VIEW;

/* DLA_VIEW 15 Felder */
typedef struct {
	int	dla_id;			/* Dienstleistungsangebot */
	int	h_dla_id;		/* �bergeordnetes Angebot */
	int	ord;				/* Reihenfolge auf Stufe */
	int	dlt_id;			/* Dienstleistungstraeger */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	akt_id;			/* Default-Aktion */
	char	ort[_CHAR256];			/* Ortschaft */
	int	art_id;			/* Angebotstyp */
	int	dau;				/* Dauer in dezimal Std. */
	short	dau_null;		/* Nullintikator */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
	int	von;				/* Von-Abkuerzung */
	int	nach;				/* Nach-Abkuerzung */
} DLA_VIEW;

/* DLG_VIEW 19 Felder */
typedef struct {
	int	dl_id;			/* Dienstleistung */
	int	h_dl_id;			/* �bergeordnete Dienstleistung */
	int	dla_id;			/* Angebot */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	ord;				/* Reihenfolge */
	short	ord_null;		/* Nullindikator */
	long long	a_zeit;			/* Anfangszeit */
	short	a_zeit_null;	/* Nullindikator */
	long long	e_zeit;			/* Endzeit */
	short	e_zeit_null;	/* Nullindikator */
	int	res_f;			/* Flag zur Steuerung der Reservation */
	int	kid;				/* Reservationsadresse */
	short	kid_null;		/* Nullindikator */
	char	konto[_CHAR256];		/* Ertragskontonummer */
	short	konto_null;		/* Nullindikator */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
	int	sai_id;			/* Saison */
} DLG_VIEW;

/* DLDLG_VIEW 12 Felder */
typedef struct {
	int   dlg_id;        /* Dienstleistung */
	int   start;         /* Anfangszeit DL */
	short start_null;    /* Nullindikator */
	int   dl_id;         /* Teildienstleistung */
	char  bez[_BEZLEN];       /* Bezeichnung der Teildienstleistung */
	long long   a_zeit;        /* Startzeit DL-Teil */
	short a_zeit_null;   /* Nullindikator */
	long long   e_zeit;        /* Endzeit DL-Teil */
	short e_zeit_null;   /* Nullindikator */
	int	ord;           /* Reihenfolge Nummer */
	int   res_f;         /* Reservationsstatus (m�glich/nicht m�glich) */
	int	s_id;          /* Sprachcode */
} DLDLG_VIEW;

/* DTG_VIEW 10 Felder */
typedef struct {
	int	dlg_id;			/* Dienstleistung */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
	int	sai_id;			/* Saison */
	long long	a_zeit;			/* Anfangszeit */
	short	a_zeit_null;	/* Nullindikator */
	int	akt_id;			/* Aktions_id */
	short	akt_id_null;	/* Nullindikator */
} DTG_VIEW;


/* ROUTEN_VIEW 7 Felder */
typedef struct {
	int	dlg_id;			/* Dienstleistung */
   char	bez[_BEZLEN];			/* Bezeichnung */
   int	s_id;				/* Sprachcode */
   char	von[_CHAR256];			/* Abk�rzung Ausgangsort*/
	short von_null;		/* Nullindikator */
   char	nach[_CHAR256];		/* Abk�rzung Zielort*/
	short nach_null;		/* Nullindikator */
} ROUTEN_VIEW;


/* ARRDL_VIEW 11 Felder */
typedef struct {
	int   arr_id;        /* Arrangement */
	long long   a_dat;         /* Anfangszeit ARR */
	int   dlg_id;        /* Dienstleistung */
	char  bez[_BEZLEN];       /* Bezeichnung der Teildienstleistung */
	long long   a_zeit;        /* Startzeit DL-Teil */
	short a_zeit_null;   /* Nullindikator */
	int	teil;				/* Reihenfolge Nummer */
	int   prio;          /* Priorit�t */
	int	akt_id;				/* Aktionen */
	short	akt_null;		/* Nullindikator */
	int	s_id;         	/* Sprachcode */
} ARRDL_VIEW;

/* ARR_VIEW 8 Felder */
typedef struct {
	int	arr_id;			/* Arrangement */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	long long	a_dat;			/* Datum des Arrangements */
	int	prg_id;			/* Programm */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
	int	sai_id;			/* Saison */
} ARR_VIEW;

/* ARR_DETAIL 14 Felder */
typedef struct {
	int	arr_id;			/* Arrangement */
	int	teil;				/* AktionsId */
	int	prio;				/* Priorit�t */
	int	dlg_id;			/* Dienstleistung */
	int	dl_id;			/* Teil Dienstleistung */
	int	ord;				/* Reihenfolge in der �bergeordneten */
	long long	a_zeit;			/* Abfahrtszeit */
	short	zeit_null;		/* Nullindikator */
	int	res_f;			/* Reservationsflag */
	char	bez[_BEZLEN];			/* Bezeichnung Dienstleistung */
	char	bez1[_BEZLEN];		/* Bezeichnung Teil Dienstleistung */
	int	s_id;				/* Sprachcode */
	long long	dtg_zeit;		/* Abfahrtszeit Dienstleistung */
	short	dtg_zeit_null;	/* Nullindikator */
} ARR_DETAIL;






/* KON_VIEW 12 Felder */
typedef struct {
	int	kont_id;			/* Kontingent */
	char	bez[_BEZLEN];			/* effektiver Text */
	int	s_id;				/* Sprachcode */
	int	hostkont_id;	/* �bergeordnetes Kontingent */
	int	kunden_id;		/* zu Kunde */
	long long	opt_dat;
	short	opt_dat_null;	/* Nullindikator */
	char	ref[_CHAR256];			/* Referenznummer */
	short	ref_null;		/* Nullindikator */
	int	sai_id;			/* Saison */
	int	textid;			/* Beschreibung */
	short	textid_null;	/* Nullindikator */
} KON_VIEW;

/* KONCHECK_VIEW 8 Felder */
typedef struct {
	int	hostkont_id;
	int	kont_id;
	int	kat_id;
	int	dlt_id;
	int	anz;
	short	anz_null;	/* Nullindikator */
	int	free;
	short	free_null;	/* Nullindikator */
} KONCHECK_VIEW;






/* RES_DL_VIEW;   22 Felder */
typedef struct {
	int	bid;					/* Buchungsnummer    */
	int	pers_id;				/* Reisender         */
	char	name[_CHAR512];			/* Reisender Name    */
	int	dl_id;				/* Dienstleistung    */
	long long	dlazeit;				/* Dl a_zeit         */
	short dlazeit_null;		/* Nullindikator     */
	int	tdl_id;				/* Teil Dl id  (dlg_parts) */
	long long	tdlazeit;			/* TDl a_zeit        */
	short tdlazeit_null;		/* Nullindikator     */
	long long	tdlezeit;			/* TDl e_zeit        */
	short tdlezeit_null;		/* Nullindikator     */
	long long	resazeit;			/* Reservation  a_zeit */
	short resazeit_null;		/* Nullindikator       */
	long long	resezeit;			/* Reservation  e_zeit */
	short resezeit_null;		/* Nullindikator       */
	int	kat_id;				/* Kategorie           */
	char	kat_bez[_BEZLEN];		/* Kategorie Bez       */
	int	typ_id;				/* Traeger Typ         */
	int	dlt_id;				/* Traeger             */
	char	dlt_bez[_BEZLEN];		/* Traeger bez         */
	int	kont_id;				/* Kontingent          */
	int	r_sta;				/* reservation status  */
	int	s_id;					/* sprache             */
} RES_DL_VIEW;

/* RESDLN_VIEW;   15 Felder */
typedef struct {
	int	bid;					/* Buchungsnummer    */
	int	pers_id;				/* Reisender         */
	char	name[_CHAR512];			/* Reisender Name    */
	int	teil;					/* Teilnummber im ARR */
	int	dl_id;				/* Dienstleistung    */
	int	tdl_id;				/* Teil Dl id  (dlg_parts) */
	long long	resazeit;			/* Reservation  a_zeit */
	short resazeit_null;		/* Nullindikator       */
	long long	resezeit;			/* Reservation  e_zeit */
	short resezeit_null;		/* Nullindikator       */
	int	kat_id;				/* Kategorie           */
	int	typ_id;				/* Traeger Typ         */
	int	dlt_id;				/* Traeger             */
	int	kont_id;				/* Kontingent          */
	int	r_sta;				/* reservation status  */
} RESDLN_VIEW;

/* RESDL_VIEW;   16 Felder */
typedef struct {
	int	bid;					/* Buchungsnummer      */
	int	pers_id;				/* Reisender           */
	int	teil;					/* Teilnummber im ARR  */
	int	dl_id;				/* Dienstleistung      */
	char	dl_bez[_BEZLEN];			/* Dienstleistung BEZ  */
	int	dl_sid;				/* Dienstleistung SPR  */
	int	tdl_id;				/* Teil Dl id  (dlg_parts) */
	long long	resazeit;			/* Reservation  a_zeit */
	short resazeit_null;		/* Nullindikator       */
	long long	resezeit;			/* Reservation  e_zeit */
	short resezeit_null;		/* Nullindikator       */
	int	kat_id;				/* Kategorie           */
	int	typ_id;				/* Traeger Typ         */
	int	dlt_id;				/* Traeger             */
	int	kont_id;				/* Kontingent          */
	int	r_sta;				/* reservation status  */
} RESDL_VIEW;


/* AKT_DETAIL_VIEW 12 Felder */
typedef struct {
	int	bid;				/* Buchungs Id */
	int	pers_id;			/* Reisender Id */
	int	dlg_id;			/* Dienstleistungs Id */
	int	dl_id;			/* TEIL-Dienstleistungs Id */
	int	teil;				/* Teilstueck */
	int	z_flag;			/* Zustands Flag */
	int	akt_id;			/* Aktions Id */
	int	ord;				/* Reihenfolge */
	int	a_flag;			/* Ausfuehrungsflag */
	int   m_flag;        /* Deviceflag */
	int	a_typ_id;		/* Aktions Typ mit System Befehl */
	char	proz[_CHAR2000];		/* Prozess */
} AKT_DETAIL_VIEW;

/* KAR_VIEW 5 Felder */
typedef struct {
	int	kar_id;			/* Kostenart Id */
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	s_id;				/* Sprachcode */
	int	textid;			/* Text */
	short	textid_null;	/* Nullindikator */
} KAR_VIEW;


/* MPV_KAPA 13 Felder */
typedef struct {
	int	kat_id;			/* Kategorie ID */
	char	katbez[_BEZLEN];		/* KAT Bezeichnung */
	int	kat_s_id;		/* KAT Sprachcode */
	int	tdl_id;			/* Teildienstleistungs ID */
	char	tdlbez[_BEZLEN];		/* TDL Bezeichnung */
	int	tdl_s_id;		/* TDL Sprachcode */
	int	pre_id;			/* Preis ID */
	int	anz;
	short	anz_null;
	int	busy;
	short	busy_null;
	double	vpr;
	short	vpr_null;
} MPV_KAPA;


/* GRA_VIEW 7 Felder */
typedef struct {
	int	gra_id;
	char	bez[_BEZLEN];			/* Bezeichnung */
	int	dlt_id;
	char	dltbez[_BEZLEN];
	int	textid;			/* Text */
	short	textid_null;	/* Nullindikator */
	int	s_id;				/* Sprachcode */
} GRA_VIEW;

/************************************************************
 * Sektion:  diverse Objekte (nicht in der DB)
 *************************************************************/

/* travelDB global profile */
typedef struct {
   char   database[_CHAR200+1];
   char   user[_USERLEN+1];
   char   password[_PWDLEN+1];
	char   hostname[_CHAR200+1];
	char   displayname[_CHAR30+1];
} MP_GLOBALPROFIL;

/* travelDB GUI global mask values */
typedef struct {
   char   bchst[_BEZLEN];
   char   sprache[_BEZLEN];
	char   land[_BEZLEN];
   char   dltt[_BEZLEN];
   char   dlt[_BEZLEN];
   char   kat[_BEZLEN];
   char   dlat[_BEZLEN];
   char   dlnt[_BEZLEN];
   char   saison[_BEZLEN];
   char   programm[_BEZLEN];
   char   a_zeit[_BEZLEN];
   char   e_zeit[_BEZLEN];
   char   p_range[_BEZLEN];
} GLOBDATA;

/* colortab for GUI - maps KATEGORIE with a color */
typedef struct {
   int KAT_ID;
   int COL_IDX;
} COLORTAB;
