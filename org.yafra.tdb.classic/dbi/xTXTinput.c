/*D***********************************************************
 * Modul:     DBI - database action
 *            Text (wird vermutlich nicht mehr ben�tigt)
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTXTinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

#define MSG1	(int)24
#define MSG2	(int)105

int TXTinput(int len, char *buffer )
{
	extern TEXTE txt;
	extern SPRACHEN spr;
	extern int sprache;

	int status=(int)MPOK;
	char *to_buffers[MAX_MENU_ITEMS];

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		txt.s_id=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		txt.textid = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (*to_buffers[MTXT_SPR] != NULL)
		txt.s_id=MPAPIselectEntry((int)_SPRACHEN, to_buffers[MTXT_SPR], (char *)&spr, sizeof(SPRACHEN), sizeof(txt.s_id));
	else
		txt.s_id=(int)_UNDEF;

	if (txt.s_id == (int)_UNDEF)
		txt.s_id=sprache;

	if (txt.s_id != (int)_UNDEF)
		{
		if (*to_buffers[MTXT_TXT] != NULL)
			{

			status=WriteEntry((int)_TEXTE, (char *)&txt, (BEZEICHNUNG *)NULL);

			if (status == (int)MPERROR)
				{
				txt.textid=(int)_UNDEF;
				}
			}
		else
			{
			UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
			txt.textid=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		txt.textid=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
