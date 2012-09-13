/*D***********************************************************
 * Modul:     DBI - database action
 *            DLAT - Dienstleistungsangebotstyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLATinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int DLATinput(int len, char *buffer)
{
	extern ANGEBOTS_TYP dlat;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dlat.art_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		dlat.art_id=(int)_UNDEF;
		dlat.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_ANGEBOTS_TYP;
	(void)copyTextTo(bez.bez, to_buffers[MDLAT_BEZ], (int)_CHAR30);
	if (*bez.bez != NULL)
		{
		txt.typ=(int)_ANGEBOTS_TYP;
		txt.s_id=(int)sprache;
		txt.textid=dlat.textid;
		dlat.textid=xTxtWrite(to_buffers[MDLAT_TXT]);

		status=WriteEntry((int)_ANGEBOTS_TYP, (char *)&dlat, &bez);
		if (status == (int)MPERROR)
			dlat.art_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_ANGEBOTS_TYP, (char *)&dlat, buffer);
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		dlat.art_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
