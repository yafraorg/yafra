/*D***********************************************************
 * Modul:     DBI - database action
 *            Kundentyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKUNTinput.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define MSG1	(int)15
#define MSG2	(int)26

int KUNTinput(int len, char *buffer)
{
	extern KUNDEN_TYP kunt;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kunt.k_typ_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		kunt.k_typ_id=(int)_UNDEF;
		kunt.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_KUNDEN_TYP;
	(void)copyTextTo(bez.bez, to_buffers[MKUNT_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		(void)copyTextTo(kunt.kuncode, to_buffers[MKUNT_CODE], (int)_CHAR10);

		txt.typ=(int)_KUNDEN_TYP;
		txt.s_id=sprache;
		txt.textid=kunt.textid;
		kunt.textid=xTxtWrite(to_buffers[MKUNT_TXT]);

		status=WriteEntry((int)_KUNDEN_TYP, (char *)&kunt, &bez);
		if (status == (int)MPERROR)
			kunt.k_typ_id=(int)_UNDEF;
		/*!!! WriteInfo hier */
		}
	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
