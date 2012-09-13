/*D***********************************************************
 * Modul:     DBI - database select                           
 *            steuert die Infoausgabe
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuInfo.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int MenuInfo(int *len, char *buffer)
{
	int status=(int)MPOK;
	unsigned char msgtyp = MESSAGEINFO;
	int tmplen = 0;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	switch(MENUNR)
		{
		case (unsigned char)_BMDLN:
		case (unsigned char)_BUCHUNG:
		case (unsigned char)_RESERVATION:
			status = RESinfo(tmplen, buffer);
			break;
		case (unsigned char)_REISENDER:
			status = DLNinfo(tmplen, buffer);
			break;
		case (unsigned char)_DIENSTLEISTUNG:
			status = DLinfo(tmplen, buffer);
			break;
		case	(unsigned char)_ARRANGEMENT:
			status = ARRinfo(tmplen, buffer);
			break;
		case	(unsigned char)_DLG_PART:
			status = DLGinfo(buffer);
			ACTIONTYP = INFOTXT;
			break;
		case	(unsigned char)_AKTIONS_TYP:
			status = AKTTinfo(buffer);
			ACTIONTYP = INFOTXT;
			break;
		case (unsigned char)_AKTIONSGRP:
			status = AKTGinfo(buffer);
			ACTIONTYP = INFOTXT;
			break;
		case	(unsigned char)_KOMMISSION:
			status = KOMinfo(buffer);
			break;
		case	(unsigned char)_KOMM_DETAIL:
			status = KOMDinfo(buffer);
			break;
		case	(unsigned char)_DIENST_ANGEBOT:
			status = DLAinfo(buffer);
			ACTIONTYP = INFOTXT;
			break;
		case (unsigned char)_PREIS:
			status = PREinfo(buffer);
			break;
		case (unsigned char)_HOST_KONT:
		case (unsigned char)_KONTINGENT:
			status = KONinfo(buffer);
			break;
		case (unsigned char)_KONT_DETAIL:
			status = KONDinfo(buffer);
			break;
		case (unsigned char)_KOLLEKTIV:
			status = KOLinfo(buffer);
			break;
		case (unsigned char)_PERSADR:
			status = ADRinfo(buffer);
			break;

		case (unsigned char)_DIENST_TRAEGER:
			status = DLTinfo(tmplen, buffer);
			break;
		case (unsigned char)_KATEGORIE:
			status = KATinfo(tmplen, buffer);
			break;
		case (unsigned char)_PCX_FILES:
			status = PCXinfo(tmplen, buffer);
			break;

		case (unsigned char)_LAND_WHR:
			status = LWinfo(buffer);
			break;
		case (unsigned char)_WAEHRUNG:
			status = WHRinfo(buffer);
			break;
		case (unsigned char)_LAND:
			status = LANDinfo(buffer);
			break;
		case (unsigned char)_ORT:
			status = ORTinfo(buffer);
			break;

		default:
			UtilMsg((int)MPE_NOINFOPCX, MSGTYP_ERROR, NULL);
			status = (int)MPERROR;
			break;
		}

	/* set length of output buffer */
	comm.datalen = strlen(comm.buffer);

	(void)MPAPIdb_committrx();

	return(status);
}
