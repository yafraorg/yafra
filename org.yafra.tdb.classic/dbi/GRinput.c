/*D***********************************************************
 * Modul:     DBI - graphic modul
 *            start up graphic in input mode
 *
 * Desc:      Schreibt die RegionsDaten in die Datenbank
 *				  Wenn im INPUTGRA-Fall die Daten verlangt werden,
 *				  m�ssen die Regionsdaten geschrieben werden wenn
 *				  sie da sind, ansonsten wird der Buffer mit 0
 *				  Regions Punkten geschrieben.
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRinput.c,v 1.3 2008-11-29 21:56:38 mwn Exp $";

int GRinput(int len, char *buffer)
{
	extern GRAPHIK gra;

	DIENST_TRAEGER dlt;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int anzahl;
	long laenge;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		gra.gra_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* start graphical input */
	dlt.stufe = (int)1;
	if ( *to_buffers[MGRA_DLT] != NULL  &&
		(gra.dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MGRA_DLT],
		 (char *)&dlt, sizeof(DIENST_TRAEGER),
		 sizeof(gra.dlt_id))) != (int)_UNDEF)
		{
		if (gra.gra_id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOGRA, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		laenge = (long)GRgetRegionsFromDB((GRAPHIK *)&gra);
		comm.datalen = laenge;
		if (comm.datalen == (int)0)
			status = (int)MPERROR;
		}
	else
		{
		COMMSTAT = MESSAGEOK;
		COMMTYP = SELECT;
		MENUNR  = (unsigned char)_GRAPHIK;
		FELDNR  = (unsigned char)MGRA_DLT;
		status = DLTselect(&laenge, buffer, &anzahl);
		if (status != (int)MPOK )
			status = (int)MPERROR;
		comm.datalen = laenge;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
