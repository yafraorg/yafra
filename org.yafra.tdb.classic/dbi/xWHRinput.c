/*D***********************************************************
 * Modul:     DBI - database action
 *            W�hrung
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xWHRinput.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int WHRinput(int len, char *buffer)
{
	extern int sprache;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern WAEHRUNG whr;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		whr.whr_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		whr.whr_id=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_WAEHRUNG;
	(void)copyTextTo(bez.bez, to_buffers[MWHR_BEZ], (int)_BEZLEN);
	if (*to_buffers[MWHR_BEZ] != NULL)
		{
		if (*to_buffers[MWHR_KRZL] != NULL)
			(void)copyTextTo(whr.krzl, to_buffers[MWHR_KRZL], (int)_KRZLLEN);
		else
			whr.krzl[0] = NULL;
		txt.typ=(int)_WAEHRUNG;
		txt.s_id=(int)sprache;
		txt.textid=whr.textid;
		whr.textid=xTxtWrite(to_buffers[MWHR_TXT]);

		status=WriteEntry((int)_WAEHRUNG, (char *)&whr, &bez);
		if (status == (int)MPERROR)
			whr.whr_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_WAEHRUNG, (char *)&whr, buffer);
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		whr.whr_id=(int)_UNDEF;
		status=(int)MPERROR;
		}


	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
