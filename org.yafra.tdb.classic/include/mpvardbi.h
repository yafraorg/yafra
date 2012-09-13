/*D***********************************************************
 * header:    global vars for DBI daemon
 *
 * copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpvardbi.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/


/* GLOBDATA globale Einschr�nkungen fuer das globale Menu */
GLOBDATA glob_buffer;        /* copy of the global values below in byte format */

KUN_VIEW			globBCHST;	 /* Kunde (Buchungsstelle) */
SPRACHEN			globSPR;     /* Systemsprache */
LAND				globLAND;    /* Laendereinstellung */
TRAEGER_TYP		globDLTT;    /* Traegertyp */
DIENST_TRAEGER	globDLT;     /* Dienstleistungstraeger */
KATEGORIE		globKAT;     /* Kategorie */
ANGEBOTS_TYP	globDLAT;    /* Angebotstyp */
REISENDER_TYP	globDLNT;    /* DL-Nehmertyp */
PROGRAMM			globPRG;     /* Programm */
SAISON			globSAI;     /* Saison  */
int            globA_ZEIT;  /* Anfangs Datum */
int            globE_ZEIT;  /* Ende Datum */
int            globP_RANGE; /* range value for 'planungsboard' */


/* admin */
int  glob_typ_sta;				/* STATUS_WERT MENU gew�hlter STATUS_TYP */
char glob_typbez_sta[_CHAR80 + 1]; /*STATUS_WERT MENU gew�hlter Status Typ */
int  glob_typ_bez;				/* BEZEICHNUNGS MENU gew�hlter BEZEICHNUNGS_TYP */
int  glob_spr_bez;				/* BEZEICHNUNGS MENU gew�hlter SPRACHCODE */
int glob_typ_msg;       /* Typ der MSG */


/* GEOGRAFIE  LAND/ORT/WAEHRUNG */
char glob_bez_land[_BEZLEN + 1];
char glob_bez_ort[_BEZLEN + 1];
char glob_bez_whr[_BEZLEN + 1];
char glob_lw_land[_BEZLEN+1];
char glob_lw_whr[_BEZLEN+1];
char glob_lw_kurstyp[_BEZLEN+1];


/* DIENST_TRAEGER */
DLT_VIEW			*globDLT_VIEW; /* DLT performance Halter */
MEMOBJ         globDLT_MEM;
MEMOBJ         dlt_mem;
int AnzglobDLT;					/* Anzahl Eintraege in der DLT_VIEW */
char glob_dltbez[_RECORDLEN];
char glob_host_dlt[_CHAR80 + 1];	/* DLT gew�hlter HOST_DLT */
char glob_kat_dlt[_CHAR80 + 1];   /* DLT Kategorie des DLTs */
char glob_hdlt_dlt[_CHAR80 + 1];  /* DLT parent pointer */

/* DIENST_ANGEBOT - ANGEBOTSTYP */
char glob_bez_dla[_CHAR80 + 1];	/* DLA */
char glob_dlt_dla[_BEZLEN+1]; /* DLA pro DLT */
int dla_selected;


/* DLG-PARTS */
MEMOBJ tdl_mem;
char glob_bez_dlg[_CHAR80 + 1];	/* TEIL-DIENSTLEISTUNGS MENU gew�hlte �bergeordnete TEIL-DIENSTLEISTUNG */

/* DIENSTLEISTUNG */
MEMOBJ dl_mem;
char glob_bez_dtg[_CHAR80 + 1];	/* DIENSTLEISTUNGS MENU gew�hlte Bezeichnung */
char glob_dat_dtg[_CHAR80 + 1];	/* DIENSTLEISTUNGS MENU gew�hltes Datum+Zeit */
char glob_dlg_dtg[_CHAR80 + 1];	/* DIENSTLEISTUNGS MENU gew�hlte DLG_PART */
int AnzOrd;				/* Ordnungen Dienstleistungen der 2. Stufe */

/* ARRANGEMENT */
char glob_bez_arr[_CHAR80 + 1];	/* ARRANGEMENT MENU gew�hlte Bezeichnung */
char glob_dtg_arr[_CHAR80 + 1];	/* gew�hlte Dienstleistung auf Arr */
int Prio;				/* Prioritaet der DLGs eines ARR-Teils */
int CurrPrio;			/* Prioritaet der DLGs eines ARR-Teils */
int Ord;					/* Ordnung der DLG eines ARR-Teils */
int glob_teil;			/* Teilstueck aus Reservation Select */
int glob_prio;			/* Prioritaet aus Reservation Select */


/* AKTIONEN / AKTIONSGRP / AKTIONS_TYP / AKTIONSPARA / OUTPUT */
char glob_bez_akt[_CHAR80 + 1];        /* AKTIONEN  gew�hlte BEZEICHNUNG */
short glob_para_aktt;                  /* AKTIONS_TYP gew�hlter Parameter */
char glob_bez_aktt[_BEZLEN + 1];       /* AKTIONS_TYP gew�hlte Bezeichnung */
int *NEWOUTlevel = NULL;               /* OUTPUT  neuer OUTlevel */
char glob_akt_out[_BEZLEN + 1];        /* OUTPUT gew�hlte Aktion */
char glob_dlg_out[_BEZLEN + 1];        /* OUTPUT gew�hlte Dienstleistung */
char glob_parent_aktg[_BEZLEN + 1];    /* AKTIONSGRP gew�hlter Vater */
char glob_child_aktg[_BEZLEN + 1];     /* AKTIONSGRP gew�hltes Kind */

/* BUCHUNG */
char glob_dlt_bch[_BEZLEN+1];	         /* BCH gew�hlter DIENST_TRAEGER */
char glob_dl_bch[_CHAR80+1];	         /* BCH gew�hlte DIENSTLEISTUNG */
char glob_arr_bch[_CHAR80+1];	         /* BCH gew�hltes ARRANGEMENT */
char glob_dat_bch[_DATLEN+1];	         /* BCH gew�hlte DIENSTLEISTUNG */
char glob_dln_bch[_DATLEN+1];	         /* BCH gew�hlter DLN */

/* RESERVATION */
char glob_dtg_res[_CHAR80];	         /* RES gew�hlte DIENSTLEISTUNG */
char glob_dlg_res[_CHAR80];	         /* RES gew�hlte TEIL-DIENSTLEISTUNG */
char glob_kat_res[_CHAR30+1];	         /* RES gew�hlte KATEGORIE */
char glob_kon_res[_CHAR30+1];	         /* RES gew�hltes KONTINGENT */
char glob_dlt_res[_CHAR80];	         /* RES gew�hlter DIENSTLEISTUNGSTRAEGER */
char glob_typ_res[_CHAR80];	         /* RES gew�hlter TRAEGERTYP */

/* KONTINGENT */
char glob_kond_hkon[_BEZLEN+1];
char glob_kond_kon[_BEZLEN+1];
char glob_kond_kat[_BEZLEN+1];
char glob_kond_dlt[_BEZLEN+1];

/* KOMMISSION inkl Detail */
char glob_bez_kom[_CHAR30+1];	         /* Auswahl der Kommissionsbezeichnung fuer die Info */
char glob_typ_kom[_CHAR30+1];	         /* Auswahl des Kommissionstyps fuer den Select der Status_werte */
char glob_satztyp_kom[_CHAR30+1];      /* Auswahl des Satztypes */
char glob_satz_kom[_CHAR80];           /* Auswahl des Kommissionssatzes */
char glob_kar_kom[_CHAR30+1];          /* Auswahl der Kostenart */

/* GRAFIK / PCX / REGIONS  */
char glob_typ_pcx[_BEZLEN+1];          /* PCX choosed pcxtyp */
int OldGraID;                          /* GRA old graphic dlt id */


/**************************************************************/
/* other flags and buffers                                    */
/**************************************************************/

/* debug file descriptor */
FILE *mpdbifile;                       /* referenced by MP_DBIDEBUGFILE */

/* booking mask objects/flags */
unsigned char bm_obj;                  /* BCH object typ of BCH (DL/ARR) */
unsigned char bm_state;                /* state of booking  */
unsigned int  bm_dlncnt;               /* DLN count in active booking */
unsigned char bm_dlnatonce;            /* enter DLN at once or step by step */
unsigned char bm_tdl;                  /* flag for TDL entering */
int           bm_lastbid;              /* last BUCHUNG's ID */
unsigned char bm_arrkom;               /* ARRANGEMENT KOM already in memory flag */
MEMOBJ        bm_kommem;               /* KOM f�r Buchungsmaske */

/* SQL-Memory im DBI */
MEMOBJ			sqlmem;
int save_point;		                  /* savepoint in db for rollback */
char sqlquery[_QUERYLEN];              /* global SQL query buffer */

/* Farbtabelle pro Kategorie */
COLORTAB			*colorTab;
int AnzCol;                            /* Anzahl Kategorien mit colors */

/* allgemeine flags (option toggles) */
unsigned char EnterDLNatonce;
unsigned char AutoInfo;
unsigned char matrixmode;
unsigned char alphaordering;
unsigned char selectfromtemp;

/* error messages read from DB to memory for access at every point */
int sql_maxmessage;		               /* Gr�sste SQL Error Nummer */
int sys_maxmessage;                    /* count of system messages */
int akt_maxmessage;                    /* count of action messages */
char **sql_message;		               /* Adressen der SQL Error Meldungen */
char **sys_message;                    /* system messages in memory from DB */
char **akt_message;                    /* system messages in memory from DB */
char messageBuffer[5*RECLAENGE];	      /* Fehlermeldungen des Systems */
MEMOBJ msgmem;

/* error handling flags */
int FatalError;		/* fatal error in processing */
int WarningFlag;     /* if status = 0 but there's a warning */

/* counts */
int AnzAkt;                            /* Anzahl Aktionen einer Buchung */
int AnzRes;                            /* Anzahl Reservationen einer Buchung */
int AnzRei;                            /* Anzahl Reisende einer Buchung */
int AnzAktt;                           /* Anzahl Aktions_typen */
int AnzPre;				                  /* Anzahl Preise dieser Dienstleistung */
