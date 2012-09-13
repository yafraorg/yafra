/*D***********************************************************
 * Programm:     MAINTbez
 * Beschreibung: wartet die Bezeichnungen (compress of id's)
 * PARAMETER:    nur -d dbpath angeben
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/mainttxt/MAINTtxtbez.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/* define the entry point of this function for the main() */
int MAINTtxtbez(int, char *[]);
#define ACTIONFUNCTION MAINTtxtbez

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standard main Funktion */

#include "version.h"       /* Standard main Funktion */

static int CleanupBEZ(int, int);
static int Selectallfrom(int);

char mailtext[256];

int MAINTtxtbez(int argc, char *argv[])
{
	/* locals */
	int Savepoint;
	int status = (int)MPOK;


	/* check for all tables TEXTE and BEZEICHNUNG referentails */
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n\n  Bezeichnungs- und Textueberpruefung\n\n");

	/* MAXIMA */

	/* SPRACHEN */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* SPRACHEN:");
	status = CleanupBEZ((int)_SPRACHEN, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_SPRACHEN);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* SAISON */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* SAISON:");
	status = CleanupBEZ((int)_SAISON, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_SAISON);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* LAND */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* LAND:");
	status = CleanupBEZ((int)_LAND, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_LAND);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* ORT */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* ORT:");
	status = CleanupBEZ((int)_ORT, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_ORT);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* WAEHRUNG */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* WAEHRUNG:");
	status = CleanupBEZ((int)_WAEHRUNG, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_WAEHRUNG);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* LAND_WHR */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* LAND_WHR:");
	status = CleanupBEZ((int)_LAND_WHR, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* LAND_SPR */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* LAND_SPR:");
	status = CleanupBEZ((int)_LAND_SPR, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* TRAEGERTYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* TRAEGER_TYP:");
	status = CleanupBEZ((int)_TRAEGER_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_TRAEGER_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KATEGROIE */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KATEGORIE:");
	status = CleanupBEZ((int)_KATEGORIE, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KATEGORIE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* DIENST_TRAEGER */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* DIENST_TRAEGER:");
	status = CleanupBEZ((int)_DIENST_TRAEGER, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_DIENST_TRAEGER);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* ANGEBOTS_TYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* ANGEBOTS_TYP:");
	status = CleanupBEZ((int)_ANGEBOTS_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_ANGEBOTS_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* AKTIONS_TYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* AKTIONS_TYP:");
	status = CleanupBEZ((int)_AKTIONS_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_AKTIONS_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* AKTIONSPARA */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* AKTIONSPARA:");
	status = CleanupBEZ((int)_AKTIONSPARA, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* AKTIONEN */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* AKTIONEN:");
	status = CleanupBEZ((int)_AKTIONEN, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_AKTIONEN);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* AKTIONSGRP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* AKTIONSGRP:");
	status = CleanupBEZ((int)_AKTIONSGRP, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* DIENST_ANGEBOT */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* DIENST_ANGEBOT:");
	status = CleanupBEZ((int)_DIENST_ANGEBOT, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_DIENST_ANGEBOT);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KUNDEN_TYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KUNDEN_TYP:");
	status = CleanupBEZ((int)_KUNDEN_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KUNDEN_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KUNDEN */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KUNDEN:");
	status = CleanupBEZ((int)_KUNDEN, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* DLG_PART */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* DLG_PART:");
	status = CleanupBEZ((int)_DLG_PART, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_DLG_PART);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* DIENSTLEISTUNG */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* DIENSTLEISTUNG:");
	status = CleanupBEZ((int)_DIENSTLEISTUNG, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_DIENSTLEISTUNG);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* DLG_DLG */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* DLG_DLG:");
	status = CleanupBEZ((int)_DLG_DLG, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* PROGRAMM */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* PROGRAMM:");
	status = CleanupBEZ((int)_PROGRAMM, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_PROGRAMM);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* ARRANGEMENT */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* ARRANGEMENT:");
	status = CleanupBEZ((int)_ARRANGEMENT, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_ARRANGEMENT);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* ARR_DLG */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* ARR_DLG:");
	status = CleanupBEZ((int)_ARR_DLG, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KOLLEKTIV_TYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KOLLEKTIV_TYP:");
	status = CleanupBEZ((int)_KOLLEKTIV_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KOLLEKTIV_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KOLLEKTIV */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KOLLEKTIV:");
	status = CleanupBEZ((int)_KOLLEKTIV, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KOLLEKTIV);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* BUCHUNG */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* BUCHUNG:");
	status = CleanupBEZ((int)_BUCHUNG, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* REISENDER_TYP */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* REISENDER_TYP:");
	status = CleanupBEZ((int)_REISENDER_TYP, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_REISENDER_TYP);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* REISENDER */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* REISENDER:");
	status = CleanupBEZ((int)_REISENDER, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* PERSADR */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* PERSADR:");
	status = CleanupBEZ((int)_PERSADR, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* PERSONEN */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* PERSONEN:");
	status = CleanupBEZ((int)_PERSONEN, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* AKT_DETAIL */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* AKT_DETAIL:");
	status = CleanupBEZ((int)_AKT_DETAIL, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KOSTEN_ART */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KOSTEN_ART:");
	status = CleanupBEZ((int)_KOSTEN_ART, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KOSTEN_ART);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KOMMISSION */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KOMMISSION:");
	status = CleanupBEZ((int)_KOMMISSION, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KOMMISSION);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KOMM_DETAIL */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KOMM_DETAIL:");
	status = CleanupBEZ((int)_KOMM_DETAIL, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KONTINGENT */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KONTINGENT:");
	status = CleanupBEZ((int)_KONTINGENT, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_KONTINGENT);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* KONT_DETAIL */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* KONT_DETAIL:");
	status = CleanupBEZ((int)_KONT_DETAIL, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* RESERVATION */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* RESERVATION:");
	status = CleanupBEZ((int)_RESERVATION, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* PREIS */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* PREIS:");
	status = CleanupBEZ((int)_PREIS, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* GRAPHIK */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* GRAFIK:");
	status = CleanupBEZ((int)_GRAPHIK, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_GRAPHIK);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* PCX_FILES */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* PCX_FILES:");
	status = CleanupBEZ((int)_PCX_FILES, (int)TRUE);
	if (status != MPOK)
		return(status);
	status = Selectallfrom((int)_PCX_FILES);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* REGIONS */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* REGIONS:");
	status = CleanupBEZ((int)_REGIONS, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();

	/* GRAFORM */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);
	AKTmsg(ACT_INFO, (int)_UNDEF, "\n\n* GRAFORM:");
	status = CleanupBEZ((int)_GRAFORM, (int)FALSE);
	if (status != MPOK)
		return(status);
	(void)MPAPIdb_committrx();


	return(status);
}


#define _SELECT_BEZEICHNUNG "SELECT DISTINCT TDBADMIN.BEZEICHNUNG.* \
	FROM TDBADMIN.BEZEICHNUNG WHERE BEZ_ID > 0 AND TYP = %d ORDER BY BEZ_ID;"

static int CleanupBEZ(int objtyp, int bezallowed)
{
	extern MEMOBJ sqlmem;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;
	extern char mailtext[]; /* defined as global in this action */

	int status = (int)MPOK;
	int anzahl;
	int i;
	int anzdelbez = 0;
	int countreturn;
	char query[_QUERYLEN];
	BEZEICHNUNG *tmpbez;

	(void)sprintf(query, _SELECT_BEZEICHNUNG, objtyp);
	status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == MPOK)
		{
		if (anzahl < 1)
			AKTmsg(ACT_INFO, (int)_UNDEF, "\n  keine Bezeichnung unter diesem Typ");
		else
			{
			tmpbez = (BEZEICHNUNG *)sqlmem.buffer;

			sprintf(mailtext, "\n  Total BEZ vor cleanup (sprachunabhaengig): %d", anzahl);
			AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);

			for (i=0; i<anzahl; i++)
				{
				bez.s_id=sprache;
				bez.typ=(int)objtyp;
				bez.bez_id=tmpbez[i].bez_id;
				if (bezallowed == (int)TRUE)
					countreturn = MPAPIid_count((int)_BEZEICHNUNG, objtyp, (char *)&bez);
				else
					countreturn = (int)EMPTY;
				if (countreturn == (int)EMPTY)
					{
					status = MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez);
					if (status == (int)MPOK)
						anzdelbez++;
					else
						{
						sprintf(mailtext, "\n  Fehler: Fehler beim loeschen von bezid %d vom typ ", bez.bez_id, objtyp);
						AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
						return(status);
						}
					}
				}

			sprintf(mailtext, "  Total BEZ nicht gebraucht und geloescht:   %d", anzdelbez);
			AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
         sprintf(mailtext, "  Total BEZ nach cleanup:                    %d", (anzahl - anzdelbez));
			AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
			}
		}
	else
		{
		sprintf(mailtext, "\n  Fehler: Fehler beim lesen auf BEZ mit Typ %d", objtyp);
		AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
		}

	return(status);
}

static int Selectallfrom(int objtyp)
{
	/* externals */
	extern MEMOBJ sqlmem;
	extern char mailtext[]; /* defined as global in this action */

	int anzahl;
	int i;
	int status = (int)MPOK;
	int countreturn;
	char query[_QUERYLEN];
	BEZEICHNUNG tstbez;

	/* pointers */
	SPRACHEN *sprptr;
	SAISON *saiptr;
	LAND *landptr;
	ORT *ortptr;
	WAEHRUNG *whrptr;
	TRAEGER_TYP *dlttptr;
	KATEGORIE *katptr;
	DIENST_TRAEGER *dltptr;
	ANGEBOTS_TYP *dlatptr;
	AKTIONS_TYP *akttptr;
	AKTIONEN *aktptr;
	DIENST_ANGEBOT *dlaptr;
	KUNDEN_TYP *kuntptr;
	DLG_PART *dlgptr;
	DIENSTLEISTUNG *dlptr;
	PROGRAMM *prgptr;
	ARRANGEMENT *arrptr;
	KOLLEKTIV_TYP *koltptr;
	KOLLEKTIV *kolptr;
	REISENDER_TYP *rkrptr;
	KOSTEN_ART *karptr;
	KOMMISSION *kommptr;
	KONTINGENT *kontptr;
	GRAPHIK *graptr;
	PCX_FILES *pcxptr;

	switch(objtyp)
		{
		case _SPRACHEN:
			strcpy(query, "SELECT * FROM TDBADMIN.SPRACHEN WHERE S_ID > 0;");
			break;
		case _SAISON:
			strcpy(query, "SELECT * FROM TDBADMIN.SAISON WHERE SAI_ID > 0;");
			break;
		case _LAND:
			strcpy(query, "SELECT * FROM TDBADMIN.LAND WHERE LAND_ID > 0;");
			break;
		case _ORT:
			strcpy(query, "SELECT * FROM TDBADMIN.ORT WHERE ORT_ID > 0;");
			break;
		case _WAEHRUNG:
			strcpy(query, "SELECT * FROM TDBADMIN.WAEHRUNG WHERE WHR_ID > 0;");
			break;
		case _TRAEGER_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.TRAEGER_TYP WHERE TYP_ID > 0;");
			break;
		case _KATEGORIE:
			strcpy(query, "SELECT * FROM TDBADMIN.KATEGORIE WHERE KAT_ID > 0;");
			break;
		case _DIENST_TRAEGER:
			strcpy(query, "SELECT * FROM TDBADMIN.DIENST_TRAEGER WHERE DLT_ID > 0;");
			break;
		case _ANGEBOTS_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.ANGEBOTS_TYP WHERE ART_ID > 0;");
			break;
		case _AKTIONS_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.AKTIONS_TYP WHERE A_TYP_ID > 0;");
			break;
		case _AKTIONEN:
			strcpy(query, "SELECT * FROM TDBADMIN.AKTIONEN WHERE AKT_ID > 0;");
			break;
		case _DIENST_ANGEBOT:
			strcpy(query, "SELECT * FROM TDBADMIN.DIENST_ANGEBOT WHERE DLA_ID > 0;");
			break;
		case _KUNDEN_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.KUNDEN_TYP WHERE K_TYP_ID > 0;");
			break;
		case _DLG_PART:
			strcpy(query, "SELECT * FROM TDBADMIN.DLG_PARTS WHERE DL_ID > 0;");
			break;
		case _DIENSTLEISTUNG:
			strcpy(query, "SELECT * FROM TDBADMIN.DIENSTLEISTUNG WHERE DLG_ID > 0;");
			break;
		case _PROGRAMM:
			strcpy(query, "SELECT * FROM TDBADMIN.PROGRAMM WHERE PRG_ID > 0;");
			break;
		case _ARRANGEMENT:
			strcpy(query, "SELECT * FROM TDBADMIN.ARRANGEMENT WHERE ARR_ID > 0;");
			break;
		case _KOLLEKTIV_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.KOLLEKTIV_TYP WHERE K_TYP_ID > 0;");
			break;
		case _KOLLEKTIV:
			strcpy(query, "SELECT * FROM TDBADMIN.KOLLEKTIV WHERE K_ID > 0;");
			break;
		case _REISENDER_TYP:
			strcpy(query, "SELECT * FROM TDBADMIN.REISENDER_TYP WHERE RKR_ID > 0;");
			break;
		case _KOSTEN_ART:
			strcpy(query, "SELECT * FROM TDBADMIN.KOSTEN_ART WHERE KAR_ID > 0;");
			break;
		case _KOMMISSION:
			strcpy(query, "SELECT * FROM TDBADMIN.KOMMISSION WHERE KOMM_ID > 0;");
			break;
		case _KONTINGENT:
			strcpy(query, "SELECT * FROM TDBADMIN.KONTINGENT WHERE KONT_ID > 0;");
			break;
		case _GRAPHIK:
			strcpy(query, "SELECT * FROM TDBADMIN.GRAPHIK WHERE GRA_ID > 0;");
			break;
		case _PCX_FILES:
			strcpy(query, "SELECT * FROM TDBADMIN.PCX_FILES WHERE PCX_ID > 0;");
			break;
		}

	status = MPAPIdb_sqlquery(objtyp, &sqlmem.buffer, query,
	                &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != MPOK)
		return(status);

	if (anzahl < 1)
		{
		AKTmsg(ACT_INFO, (int)_UNDEF, "  keine Eintraege in dieser Tabelle");
		return((int)MPOK);
		}

	switch(objtyp)
		{
		case _SPRACHEN:
			sprptr = (SPRACHEN *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_SPRACHEN;
				tstbez.bez_id =sprptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", sprptr[i].s_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _SAISON:
			saiptr = (SAISON *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_SAISON;
				tstbez.bez_id =saiptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", saiptr[i].sai_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _LAND:
			landptr = (LAND *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_LAND;
				tstbez.bez_id =landptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", landptr[i].land_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _ORT:
			ortptr = (ORT *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_ORT;
				tstbez.bez_id =ortptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", ortptr[i].ort_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _WAEHRUNG:
			whrptr = (WAEHRUNG *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_WAEHRUNG;
				tstbez.bez_id =whrptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", whrptr[i].whr_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _TRAEGER_TYP:
			dlttptr = (TRAEGER_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_TRAEGER_TYP;
				tstbez.bez_id =dlttptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dlttptr[i].typ_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KATEGORIE:
			katptr = (KATEGORIE *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KATEGORIE;
				tstbez.bez_id =katptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", katptr[i].kat_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _DIENST_TRAEGER:
			dltptr = (DIENST_TRAEGER *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_DIENST_TRAEGER;
				tstbez.bez_id =dltptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dltptr[i].dlt_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _ANGEBOTS_TYP:
			dlatptr = (ANGEBOTS_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_ANGEBOTS_TYP;
				tstbez.bez_id =dlatptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dlatptr[i].art_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _AKTIONS_TYP:
			akttptr = (AKTIONS_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_AKTIONS_TYP;
				tstbez.bez_id =akttptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", akttptr[i].a_typ_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _AKTIONEN:
			aktptr = (AKTIONEN *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_AKTIONEN;
				tstbez.bez_id =aktptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", aktptr[i].akt_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _DIENST_ANGEBOT:
			dlaptr = (DIENST_ANGEBOT *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_DIENST_ANGEBOT;
				tstbez.bez_id =dlaptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dlaptr[i].dla_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KUNDEN_TYP:
			kuntptr = (KUNDEN_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KUNDEN_TYP;
				tstbez.bez_id =kuntptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", kuntptr[i].k_typ_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _DLG_PART:
			dlgptr = (DLG_PART *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_DLG_PART;
				tstbez.bez_id =dlgptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dlgptr[i].dl_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _DIENSTLEISTUNG:
			dlptr = (DIENSTLEISTUNG *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_DIENSTLEISTUNG;
				tstbez.bez_id =dlptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", dlptr[i].dlg_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _PROGRAMM:
			prgptr = (PROGRAMM *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_PROGRAMM;
				tstbez.bez_id =prgptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", prgptr[i].prg_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _ARRANGEMENT:
			arrptr = (ARRANGEMENT *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_ARRANGEMENT;
				tstbez.bez_id =arrptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", arrptr[i].arr_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KOLLEKTIV_TYP:
			koltptr = (KOLLEKTIV_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KOLLEKTIV_TYP;
				tstbez.bez_id =koltptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", koltptr[i].k_typ_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KOLLEKTIV:
			kolptr = (KOLLEKTIV *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KOLLEKTIV;
				tstbez.bez_id =kolptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", kolptr[i].k_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _REISENDER_TYP:
			rkrptr = (REISENDER_TYP *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_REISENDER_TYP;
				tstbez.bez_id =rkrptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", rkrptr[i].rkr_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KOSTEN_ART:
			karptr = (KOSTEN_ART *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KOSTEN_ART;
				tstbez.bez_id =karptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", karptr[i].kar_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KOMMISSION:
			kommptr = (KOMMISSION *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KOMMISSION;
				tstbez.bez_id =kommptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", kommptr[i].komm_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _KONTINGENT:
			kontptr = (KONTINGENT *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_KONTINGENT;
				tstbez.bez_id =kontptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", kontptr[i].kont_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _GRAPHIK:
			graptr = (GRAPHIK *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_GRAPHIK;
				tstbez.bez_id =graptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", graptr[i].gra_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		case _PCX_FILES:
			pcxptr = (PCX_FILES *)sqlmem.buffer;
			for (i=0; i<anzahl; i++)
				{
				tstbez.s_id   =(int)_UNDEF;
				tstbez.typ    =(int)_PCX_FILES;
				tstbez.bez_id =pcxptr[i].bez_id;
				countreturn = MPAPIid_count((int)_BEZEICHNUNG, (int)_BEZEICHNUNG, (char *)&tstbez);
				if (countreturn == (int)EMPTY)
					{
					sprintf(mailtext, "  FATALERROR: Objekt %d hat keine g�ltige BEZ_ID", pcxptr[i].pcx_id);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailtext);
					}
				}
			break;
		}

	return(status);
}
