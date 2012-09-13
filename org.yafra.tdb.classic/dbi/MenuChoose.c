/*D************************************************************/
/* Modul:     DBI - database select                           */
/*            manage one item                                 */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuChoose.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

static void CheckBuffer(char *);

int MenuChoose(int *len, char *buffer)
{
	int (*choosefunc)();
	char format[RECLAENGE];
	char message[RECLAENGE];
	int status=(int)MPOK;

	/* init the choosefunc */
	choosefunc = NULL;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return(MPERROR);
		}

	/* buffer pr�fen, damit bei TWINSELECT nur ein Eintrag durchgeht */
	CheckBuffer(buffer);

	switch(MENUNR)
		{
		/* BUCHUNG */
		case (unsigned char)_BUCHUNG:
			choosefunc = BMBCHchoose;
			break;
		case (unsigned char)_REISENDER:
			choosefunc = DLNchoose;
			break;
		case (unsigned char)_BMDLN:
			choosefunc = BMDLNchoose;
			break;
		case (unsigned char)_RESERVATION:
			choosefunc = BMRESchoose;
			break;
		case (unsigned char)_KUNDEN:
			choosefunc = KUNchoose;
			break;
		case (unsigned char)_KOLLEKTIV:
			choosefunc = KOLchoose;
			break;
		case (unsigned char)_PERSADR:
			choosefunc = ADRchoose;
			break;
		case (unsigned char)_OUTPUT:
			choosefunc = OUTchoose;
			break;
		case (unsigned char)_KOMMISSION:
			choosefunc = KOMchoose;
			break;
		case (unsigned char)_KOMM_DETAIL:
			choosefunc = KOMDchoose;
			break;


		/* ANGEBOT */
		case	(unsigned char)_SAISON:
			choosefunc = SAIchoose;
			break;
		case (unsigned char)_PROGRAMM:
			choosefunc = PRGchoose;
			break;
		case	(unsigned char)_ARRANGEMENT:
			choosefunc = ARRchoose;
			break;
		case	(unsigned char)_DIENSTLEISTUNG:
			choosefunc = DLchoose;
			break;
		case	(unsigned char)_DLG_PART:
			choosefunc = DLGchoose;
			break;
		case	(unsigned char)_DIENST_ANGEBOT:
			choosefunc = DLAchoose;
			break;
		case (unsigned char)_AKTIONEN:
			choosefunc = AKTchoose;
			break;
		case (unsigned char)_AKTIONSGRP:
			choosefunc = AKTGchoose;
			break;
		case	(unsigned char)_HOST_KONT:
			choosefunc = KONHchoose;
			break;
		case	(unsigned char)_KONTINGENT:
			choosefunc = KONchoose;
			break;
		case	(unsigned char)_KONT_DETAIL:
			choosefunc = KONDchoose;
			break;
		case	(unsigned char)_PREIS:
			choosefunc = PREchoose;
			break;


		/* STAMM */
		case (unsigned char)_TRAEGER_TYP:
			choosefunc = DLTTchoose;
			break;
		case (unsigned char)_DIENST_TRAEGER:
			choosefunc = DLTchoose;
			break;
		case (unsigned char)_KATEGORIE:
			choosefunc = KATchoose;
			break;
		case (unsigned char)_PCX_FILES:
			choosefunc = PCXchoose;
			break;
		case (unsigned char)_GRAPHIK:
			choosefunc = GRAchoose;
			break;
		case (unsigned char)_ANGEBOTS_TYP:
			choosefunc = DLATchoose;
			break;
		case (unsigned char)_AKTIONS_TYP:
			choosefunc = AKTTchoose;
			break;
		case (unsigned char)_KOSTEN_ART:
			choosefunc = KARchoose;
			break;
		case	(unsigned char)_KUNDEN_TYP:
			choosefunc = KUNTchoose;
			break;
		case (unsigned char)_REISENDER_TYP:
			choosefunc = DLNTchoose;
			break;
		case (unsigned char)_KOLLEKTIV_TYP:
			choosefunc = KOLTchoose;
			break;
		case	(unsigned char)_STATUS_WERTE:
			choosefunc = STAchoose;
			break;


		/* GEO */
		case (unsigned char)_SPRACHEN:
			choosefunc = SPRchoose;
			break;
		case (unsigned char)_WAEHRUNG:
			choosefunc = WHRchoose;
			break;
		case (unsigned char)_LAND:
			choosefunc = LANDchoose;
			break;
		case (unsigned char)_ORT:
			choosefunc = ORTchoose;
			break;
		case (unsigned char)_LAND_WHR:
			choosefunc = LWchoose;
			break;


		/* Administration */
		case	(unsigned char)_BEZEICHNUNG:
			choosefunc = BEZchoose;
			break;
		case (unsigned char)_MSG:
			choosefunc = MSGchoose;
			break;

		default:
			UtilMsgGet((int)MPE_NOSELECTTABLE, MSGTYP_ERROR, format);
			(void)sprintf(message, format, (int)MENUNR);
			UtilMsgWrite(message);
			(void)MPAPIdb_committrx();
			return((int)MPERROR);
			break;
		}

	/* call choose function */
	if (choosefunc != NULL)
		status = choosefunc(MENUNR, buffer);
	(void)MPAPIdb_committrx();
	return(status);
}

static void CheckBuffer(char *buffer)
{
	int i;
	int len;

	len = strlen(buffer);

	for (i=0; i < len; i++)
		if (buffer[i] == '\n')
			{
			buffer[i] = NULL;
			break;
			}
}
