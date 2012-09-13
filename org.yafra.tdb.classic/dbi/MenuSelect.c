/*D************************************************************/
/* Modul:     DBI - database select                           */
/*            manage a select request on a field              */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuSelect.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int MenuSelect(int *len, char *buffer)
{
	extern int *NewLevel[];

	int (*selectfunc)();
	char message[RECLAENGE];
	char format[RECLAENGE];
	long bufferlen = 0;
	int anzahl=0;
	int status=(int)MPOK;
	int table;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return(MPERROR);
		}

	if (COMMTYP == GLOBAL && ACTIONTYP == (int)LABELINIT )
		table = (int)_GLOBALMENU;
	else
		table = NewLevel[MENUNR][FELDNR];

	bufferlen = (long)*len;

	switch(table)
		{
		/* BUCHUNG */
		case (int)_BUCHUNG:
			selectfunc = BCHselect;
			break;
		case (int)_KUNDEN:
			selectfunc = KUNselect;
			break;
		case (int)_REISENDER:
			selectfunc = DLNselect;
			break;
		case (int)_PERSADR:
			selectfunc = ADRselect;
			break;
		case (int)_KOLLEKTIV:
			selectfunc = KOLselect;
			break;
		case (int)_KOMMISSION:
			selectfunc = KOMselect;
			break;
		case (int)_KOMM_DETAIL:
			selectfunc = KOMDselect;
			break;


		/* ANGEBOT */
		case (int)_SAISON:
			selectfunc = SAIselect;
			break;
		case (int)_PROGRAMM:
			selectfunc = PRGselect;
			break;
		case (int)_ARRANGEMENT:
			selectfunc = ARRselect;
			break;
		case (int)_DIENSTLEISTUNG:
			selectfunc = DLselect;
			break;
		case (int)_DLG_PART:
			selectfunc = DLGselect;
			break;
		case (int)_DIENST_ANGEBOT:
			selectfunc = DLAselect;
			break;
		case (int)_ANGEBOTS_TYP:
			selectfunc = DLATselect;
			break;
		case (int)_AKTIONEN:
			selectfunc = AKTselect;
			break;
		case (int)_AKTIONSGRP:
			selectfunc = AKTGselect;
			break;
		case (int)_HOST_KONT:
			selectfunc = KONHselect;
			break;
		case (int)_KONTINGENT:
			selectfunc = KONselect;
			break;
		case (int)_KONT_DETAIL:
			selectfunc = KONDselect;
			break;
		case (int)_PREIS:
			selectfunc = PREselect;
			break;



		/* STAMM */
		case (int)_TRAEGER_TYP:
			selectfunc = DLTTselect;
			break;
		case (int)_DIENST_TRAEGER:
			selectfunc = DLTselect;
			break;
		case (int)_KATEGORIE:
			selectfunc = KATselect;
			break;
		case (int)_PCX_FILES:
			selectfunc = PCXselect;
			break;
		case (int)_GRAPHIK:
			selectfunc = GRAselect;
			break;
		case (int)_AKTIONS_TYP:
			selectfunc = AKTTselect;
			break;
		case (int)_KOSTEN_ART:
			selectfunc = KARselect;
			break;
		case (int)_KUNDEN_TYP:
			selectfunc = KUNTselect;
			break;
		case (int)_REISENDER_TYP:
			selectfunc = DLNTselect;
			break;
		case (int)_KOLLEKTIV_TYP:
			selectfunc = KOLTselect;
			break;
		case (int)_STATUS_WERTE:
			selectfunc = STAselect;
			break;


		/* GEOGRAFIE */
		case (int)_SPRACHEN:
			selectfunc = SPRselect;
			break;
		case (int)_WAEHRUNG:
			selectfunc = WHRselect;
			break;
		case (int)_LAND:
			selectfunc = LANDselect;
			break;
		case (int)_ORT:
			selectfunc = ORTselect;
			break;
		case (int)_LAND_WHR:
			selectfunc = LWselect;
			break;


		/* Administration */
		case (int)_BEZEICHNUNG:
			selectfunc = BEZselect;
			break;
		case (int)_MSG:
			selectfunc = MSGselect;
			break;


		/* Felder mit Typ _DATUM */
		case (int)_DATUM:
			selectfunc = DATUMselect;
			break;

		default:
			UtilMsgGet((int)MPE_NOSELECTTABLE, MSGTYP_ERROR, format);
			(void)sprintf( message, format, table );
			UtilMsgWrite(message);
			(void)MPAPIdb_committrx();
			return((int)MPERROR);
			break;
		}

	/* make select and choose calls */
	status = selectfunc(&bufferlen, buffer, &anzahl);
	(void)MPAPIdb_committrx();
	if (status != MPOK)
		return(status);
	*len = (int)bufferlen;

	/* in some cases we must go back immediately */
	if (COMMTYP == NEXTMENU || MENUNR == (unsigned char)_GLOBALMENU ||
	    COMMTYP == MATRIXSELECT)
		return(status);

	if (anzahl == 1)  /* 1 entrie found -> check it */
		{
		/* set the address of comm.buffer because we don't know */
		/* if there was a MPalloc in selectfunc	and the scope of */
	  	/* buffer is local !! */
		buffer = comm.buffer;
		status = MenuChoose(len, buffer);
		}
	else if (anzahl > 1)
		COMMTYP = SELECT;
	else
		{
		COMMSTAT = MESSAGEERROR;
		COMMTYP = SELECT;
		}

	return(status);
}
