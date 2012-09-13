/*D***********************************************************
 * Modul:     DBI - database action
 *            Kollektivtyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOLTinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

#define MSG1	(int)15
#define MSG2	(int)26

int KOLTinput(int len, char *buffer)
{
	extern KOLLEKTIV_TYP kolt;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kolt.k_typ_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		kolt.k_typ_id=(int)_UNDEF;
		kolt.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_KOLLEKTIV_TYP;
	(void)copyTextTo(bez.bez, to_buffers[MKOLT_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		(void)copyTextTo(kolt.kolcode, to_buffers[MKOLT_CODE], (int)_CHAR10);

		txt.typ=(int)_KOLLEKTIV_TYP;
		txt.s_id=sprache;
		txt.textid=kolt.textid;
		kolt.textid=xTxtWrite(to_buffers[MKOLT_TXT]);

		status=WriteEntry((int)_KOLLEKTIV_TYP, (char *)&kolt, &bez);
		if (status == (int)MPERROR)
			kolt.k_typ_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_KOLLEKTIV_TYP, (char *)&kolt, buffer);

		}
	else
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		kolt.k_typ_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
