/*D***********************************************************
 * Modul:     process the "commit" button
 *            go to detail functions (it's depending on the menu)
 *            if error occured make rollback of the commit
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuAktion.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int MenuAktion(int len, char *buffer)
{
	extern MP_PROFIL prof;

	int (*inputfunc)();
	char message[_RECORDLEN];
	char format[_RECORDLEN];
	int status=(int)MPOK;

	/* init inputfunc */
	inputfunc = NULL;

	/* SECURITY: check if user has permission to ins/upd/del data */
	if (prof.seclevel == _SECLEVEL_READONLY || prof.seclevel == _SECLEVEL_NOP)
		{
		UtilMsg((int)MPE_NOPERMISSION, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* start transaction in read uncomitted mode */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		return(MPERROR);
		}

	switch (MENUNR)
		{
		case (unsigned char)_BUCHUNG:
			inputfunc = BMBCHinput;
			break;
		case (unsigned char)_KUNDEN:
			inputfunc = KUNinput;
			break;
		case (unsigned char)_RESERVATION:
			inputfunc = BMRESinput;
			break;
		case (unsigned char)_REISENDER:
			inputfunc = DLNinput;
			break;
		case (unsigned char)_BMDLN:
			inputfunc = BMDLNinput;
			break;
		case (unsigned char)_KOLLEKTIV:
			inputfunc = KOLinput;
			break;
		case (unsigned char)_PERSADR:
			inputfunc = ADRinput;
			break;
		case (unsigned char)_OUTPUT:
			inputfunc = OUTexec;
			break;
		case (unsigned char)_KOMMISSION:
			inputfunc = KOMinput;
			break;
		case (unsigned char)_KOMM_DETAIL:
			inputfunc = KOMDinput;
			break;


		case (unsigned char)_SAISON:
			inputfunc = SAIinput;
			break;
		case (unsigned char)_PROGRAMM:
			inputfunc = PRGinput;
			break;
		case (unsigned char)_ARRANGEMENT:
			inputfunc = ARRinput;
			break;
		case (unsigned char)_DIENSTLEISTUNG:
			inputfunc = DLinput;
			break;
		case (unsigned char)_DLG_PART:
			inputfunc = DLGinput;
			break;
		case (unsigned char)_DIENST_ANGEBOT:
			inputfunc = DLAinput;
			break;
		case (unsigned char)_AKTIONEN:
			inputfunc = AKTinput;
			break;
		case (unsigned char)_AKTIONSGRP:
			inputfunc = AKTGinput;
			break;
		case (unsigned char)_HOST_KONT:
			inputfunc = KONHinput;
			break;
		case (unsigned char)_KONTINGENT:
			inputfunc = KONinput;
			break;
		case (unsigned char)_KONT_DETAIL:
			inputfunc = KONDinput;
			break;
		case (unsigned char)_PREIS:
			inputfunc = PREinput;
			break;


		case (unsigned char)_TRAEGER_TYP:
			inputfunc = DLTTinput;
			break;
		case (unsigned char)_DIENST_TRAEGER:
			inputfunc = DLTinput;
			break;
		case (unsigned char)_KATEGORIE:
			inputfunc = KATinput;
			break;
		case (unsigned char)_PCX_FILES:
			inputfunc = PCXinput;
			break;
		case (unsigned char)_GRAPHIK:
			inputfunc = GRAinput;
			break;
		case (unsigned char)_ANGEBOTS_TYP:
			inputfunc = DLATinput;
			break;
		case (unsigned char)_AKTIONS_TYP:
			inputfunc = AKTTinput;
			break;
		case (unsigned char)_KUNDEN_TYP:
			inputfunc = KUNTinput;
			break;
		case (unsigned char)_REISENDER_TYP:
			inputfunc = DLNTinput;
			break;
		case (unsigned char)_KOSTEN_ART:
			inputfunc = KARinput;
			break;
		case (unsigned char)_KOLLEKTIV_TYP:
			inputfunc = KOLTinput;
			break;
		case (unsigned char)_STATUS_WERTE:
			inputfunc = STAinput;
			break;


		case (unsigned char)_SPRACHEN:
			inputfunc = SPRinput;
			break;
		case (unsigned char)_WAEHRUNG:
			inputfunc = WHRinput;
			break;
		case (unsigned char)_LAND:
			inputfunc = LANDinput;
			break;
		case (unsigned char)_ORT:
			inputfunc = ORTinput;
			break;
		case (unsigned char)_LAND_WHR:
			inputfunc = LWinput;
			break;


		case (unsigned char)_BEZEICHNUNG:
			inputfunc = BEZinput;
			break;
		case (unsigned char)_MSG:
			inputfunc = MSGinput;
			break;
		case (unsigned char)_BACKUP:
			inputfunc = UtilBackup;
			break;
		case (unsigned char)_RESTORE:
			inputfunc = UtilRestore;
			break;

		default:
			UtilMsgGet((int)MPE_NOSELECTTABLE, MSGTYP_ERROR, format);
			(void)sprintf(message, format, (int)MENUNR);
			UtilMsgWrite(message);
			status = (int)MPERROR;
			break;
		}

	/* call delete function */
	if (inputfunc != NULL)
		status = inputfunc(len, buffer);

	/* end transaction */
	if (status != (int)MPOK)
		MPAPIdb_rollbacktrx();
	else
		MPAPIdb_committrx();

	/* empty protocol for ACTION call in GUI */
	if (COMMTYP == (unsigned char)ACTION)
		comm.datalen = 0;
	else
		comm.datalen = strlen(comm.buffer);

	return(status);
}
