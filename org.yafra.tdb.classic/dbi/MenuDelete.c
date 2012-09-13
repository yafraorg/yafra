/*D***********************************************************
 * modul:     DBI - menu
 *            delete functions
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuDelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int MenuDelete(int table)
{
	extern unsigned char logging_user;

	int (*deletefunc)();
	char logmsg[_RECORDLEN];
	int status = MPOK;

	/* init the deletefunc */
	deletefunc = NULL;

	switch(table)
		{
		case (int)_BUCHUNG:
			deletefunc = BCHdelete;
			break;
		case (int)_REISENDER:
			deletefunc = DLNdelete;
			break;
		case (int)_RESERVATION:
			deletefunc = RESdelete;
			break;
		case (int)_KOLLEKTIV:
			deletefunc = KOLdelete;
			break;
		case (int)_KUNDEN:
			deletefunc = KUNdelete;
			break;
		case (int)_KOMMISSION	:
			deletefunc = KOMdelete;
			break;
		case (int)_KOMM_DETAIL:
			deletefunc = KOMDdelete;
			break;


		case (int)_SAISON:
			deletefunc = SAIdelete;
			break;
		case (int)_PROGRAMM:
			deletefunc = PRGdelete;
			break;
		case (int)_ARRANGEMENT	:
			deletefunc = ARRdelete;
			break;
		case (int)_DIENSTLEISTUNG	:
			deletefunc = DLdelete;
			break;
		case (int)_DLG_PART	:
			deletefunc = DLGdelete;
			break;
		case (int)_DIENST_ANGEBOT	:
			deletefunc = DLAdelete;
			break;
		case (int)_AKTIONEN		:
			deletefunc = AKTdelete;
			break;
		case (int)_AKTIONSGRP:
			deletefunc = AKTGdelete;
			break;
		case (int)_HOST_KONT:
			deletefunc = KONHdelete;
			break;
		case (int)_KONTINGENT:
			deletefunc = KONdelete;
			break;
		case (int)_KONT_DETAIL:
			deletefunc = KONDdelete;
			break;
		case (int)_PREIS:
			deletefunc = PREdelete;
			break;


		case (int)_TRAEGER_TYP	:
			deletefunc = DLTTdelete;
			break;
		case (int)_KATEGORIE:
			deletefunc = KATdelete;
			break;
		case (int)_DIENST_TRAEGER	:
			deletefunc = DLTdelete;
			break;
		case (int)_GRAPHIK:
			deletefunc = GRAdelete;
			break;
		case (int)_PCX_FILES:
			deletefunc = PCXdelete;
			break;
		case (int)_ANGEBOTS_TYP	:
			deletefunc = DLATdelete;
			break;
		case (int)_AKTIONS_TYP	:
			deletefunc = AKTTdelete;
			break;
		case (int)_AKTIONSPARA:
			deletefunc = AKTPdelete;
			break;
		case (int)_KUNDEN_TYP:
			deletefunc = KUNTdelete;
			break;
		case (int)_REISENDER_TYP	:
			deletefunc = DLNTdelete;
			break;
		case (int)_KOSTEN_ART	:
			deletefunc = KARdelete;
			break;
		case (int)_KOLLEKTIV_TYP	:
			deletefunc = KOLTdelete;
			break;
		case (int)_STATUS_WERTE	:
			deletefunc = STAdelete;
			break;


		case (int)_SPRACHEN:
			deletefunc = SPRdelete;
			break;
		case (int)_WAEHRUNG:
			deletefunc = WHRdelete;
			break;
		case (int)_LAND:
			deletefunc = LANDdelete;
			break;
		case (int)_ORT:
			deletefunc = ORTdelete;
			break;
		case (int)_LAND_WHR:
			deletefunc = LWdelete;
			break;


		case (int)_BEZEICHNUNG	:
			deletefunc = BEZdelete;
			break;
		case (int)_MSG:
			deletefunc = MSGdelete;
			break;

		default:
			UtilMsg((int)MPE_NOSELECTTABLE, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			break;
		}

	/* call delete function */
	if (deletefunc != NULL)
		status = deletefunc();

	/* execution time logging */
	if (logging_user)
		{
		(void)sprintf(logmsg, "Etwas aus Tabelle-Nr %d geloescht mit Status %d",
		              table, status);
		MPlog(_LOGUSER, status, logmsg, __FILE__);
		}

	return(status);
}
