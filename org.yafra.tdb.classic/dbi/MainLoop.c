/*D***********************************************************
 * Modul:     MarcoPolo DBI main loop
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */
#include "version.h"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MainLoop.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

void MainLoop(int fd)
{
	extern int FatalError;
	extern int WarningFlag;
	extern char messageBuffer[];
	extern unsigned char logging_mp;
	extern GLOBDATA glob_buffer;
	extern MP_GLOBALPROFIL globprof;
	extern int DebugFlag;
	extern FILE *MP_DBIDEBUGFILE;
	extern char *MPversiontext;

	char msgdat[_DATLEN], msgtime[_DATLEN];
	char msgformat[_RECORDLEN];
	static char *buffer;
	int len;
	int status;

	for(;;)
		{
		/* init */
		status     = MPOK;
		COMMTYP    = (char)NULL;
		ACTIONTYP  = (char)NULL;
		MENUNR     = (char)NULL;
		FELDNR     = (char)NULL;
		comm.datalen = 0;
		WarningFlag = (int)FALSE;

		(void)MPcomm(RECV, DEFMEMCHUNK);

		/* look if quit is send */
		if (COMMTYP == GLOBAL && ACTIONTYP == QUIT)
			break;

		/* check COMMSTAT send from GUI */
		// TODO implement the COMMSTAT check here

		/* init buffer and len */
		len = comm.datalen;
		buffer = comm.buffer;
		COMMSTAT = MESSAGEOK;

		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "got call from GUI with COMMTYP: %d", (int)COMMTYP);

		switch(COMMTYP)
			{
			/* Inits */
			case GLOBAL	:    /* action on the global datas */
				status = MenuGlobal(&glob_buffer);
				comm.datalen = strlen(comm.buffer);
				break;
			case DELETEFIELD:	/* loeschen eines Feldes  - Globale Variablen loeschen */
				InitField();
				comm.datalen = strlen(comm.buffer);
				break;
			case DELETEMENU:	/* Ausgew�hltes Menu alle Eintragungen l�schen */
				InitMenu();
				comm.datalen = strlen(comm.buffer);
				break;

			/* Select */
			case SELECT	:    /* a select button pressed - bring select window */
				status = MenuSelect(&len, buffer);
				if ( status == (int)MPOK && MENUNR != (unsigned char)_BMDLN &&
				    MENUNR != (unsigned char)_RESERVATION)
					comm.datalen = CleanPipeString(comm.buffer);
				else if (status == (int)MPOK)
					comm.datalen = strlen(comm.buffer);
				break;

			/* Choose */
			case CHOOSE:    /* mark the selected field */
				status = MenuChoose(&len, buffer);
				comm.datalen = strlen(comm.buffer);
				break;

			/* Commit */
			case ACTION	:    /* make action on a menu */
				status = MenuAktion(len, buffer);
				break;

			/* Information */
			case INFO:	/* Informationen �ber eine bestimmte Eintragung anfordern */
				status = MenuInfo(&len, buffer);
				break;

			/* Hilfetexte */
			case HELPCALL:
				status = MenuHelp(&len, buffer);
				break;

			case ONEITEM:	/* Ausf�hren einer Funktion und R�ckgabe eines Strings f�r das einzelne Widget */
				status = MenuOneitem(&len, buffer);
				comm.datalen = strlen(comm.buffer);
				break;

			/* Verwalte ver�nderung von Options von der GUI */
			case OPTIONTOGGLE:
				status = MenuOptiontoggles(len, buffer);
				break;

			/* matrix calls */
			case MATRIXSELECT:
			case MATRIXACTION:
				status = MenuMatrix(len, buffer);
				break;

			/* Grafik calls */
			case GRAINPUT:
			case GRASEND:
			case GRASELECT:
			case GRAREFRESH:
			case GRACHOOSE:
				status = MenuGraphics(len, buffer);
				break;

			/* booking mask calls */
			case BMOBJCHOOSE:
			case BMBOOK:
				status = MenuBM(len, buffer);
				break;

			default:	/* falscher COMMTYP - Fehler */
				UtilMsg((int)MPE_WRONGCOMMTYP, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				break;
			}

		/* Ueberpr�fe ob Fehler vorhanden oder nicht */
		if (FatalError == (int)TRUE || status != (int)MPOK || WarningFlag == (int)TRUE)
			{
			if ((status == (int)MPWARNING || WarningFlag == (int)TRUE) &&
			    (FatalError != (int)TRUE))
				{
				/* W A R N I N G  message */
				/* init for warning message */
				comm.buffer[0] = (char)NULL;
				COMMSTAT = MESSAGEWARNING;
				}
			else
				{
				/* E R R O R  message */
				/* message header */
				UtilMsgGet((int)MPS_ERRORHEADER, MSGTYP_SYSTEM, msgformat);
				MPdate_makecurrent(msgdat, msgtime);
				(void)sprintf(comm.buffer, msgformat,
				      msgdat, msgtime, globprof.user, globprof.database, MAINVERSION);
				(void)strcat(comm.buffer, MSGTRENNER);

				/* message footer */
				UtilMsg((int)MPS_SUPPORT, MSGTYP_SYSTEM, NULL);
				COMMSTAT = MESSAGEERROR;
				}

			/* set message for sending to GUI */
			(void)strcat(comm.buffer, messageBuffer);
			comm.datalen = CleanPipeString(comm.buffer);
			*messageBuffer = (char)NULL;
			}

		/* flush debug file */
		if (MP_DBIDEBUGFILE != NULL)
			(void)fflush(MP_DBIDEBUGFILE);

		/* Sende Daten an GUI */
		MPcomm(SEND, DEFMEMCHUNK);

		} /* End of for ever */

	return;
}
