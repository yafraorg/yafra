/*D***********************************************************
 * Modul:     DBI - database action
 *            Dienstleistungstr�gertyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKARinput.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

#define MSG1	(int)15

int KARinput(int len, char *buffer)
{
	extern KOSTEN_ART kar;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kar.kar_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (int)INSERT)
		{
		kar.kar_id=(int)_UNDEF;
		kar.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_KOSTEN_ART;
	(void)copyTextTo(bez.bez, to_buffers[MKAR_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		txt.typ=(int)_KOSTEN_ART;
		txt.s_id=(int)sprache;
		txt.textid=kar.textid;
		kar.textid=xTxtWrite(to_buffers[MKAR_TXT]);

		status=WriteEntry((int)_KOSTEN_ART, (char *)&kar, &bez);
		if (status == (int)MPERROR)
			kar.kar_id=(int)_UNDEF;
		/*!!! WriteInfo hier */
		}
	else
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		kar.kar_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
