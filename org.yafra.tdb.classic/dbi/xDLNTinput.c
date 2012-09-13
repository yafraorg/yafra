/*D***********************************************************
 * Modul:     DBI - database action
 *            DL-Nehmertyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNTinput.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#define MSG1	(int)15
#define MSG2	(int)26

int DLNTinput(int len, char *buffer)
{
	extern REISENDER_TYP reit;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		reit.rkr_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (int)INSERT)
		{
		reit.rkr_id=(int)_UNDEF;
		reit.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		reit.vonalter = (int)_UNDEF;
		reit.bisalter = (int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_REISENDER_TYP;
	(void)copyTextTo(bez.bez, to_buffers[MDLNT_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		(void)copyTextTo(reit.dlncode, to_buffers[MDLNT_CODE], (int)_CHAR10);

		status = readInteger(&reit.vonalter, to_buffers[MDLNT_VONALTER]);
		if (status == (int)MPERROR)
			reit.vonalter = (int)_UNDEF;

		status = readInteger(&reit.bisalter, to_buffers[MDLNT_BISALTER]);
		if (status == (int)MPERROR)
			reit.bisalter = (int)_UNDEF;

		txt.typ=(int)_REISENDER_TYP;
		txt.s_id=sprache;
		txt.textid=reit.textid;
		reit.textid=xTxtWrite(to_buffers[MDLNT_TXT]);

		status=WriteEntry((int)_REISENDER_TYP, (char *)&reit, &bez);
		if (status == (int)MPERROR)
			reit.rkr_id=(int)_UNDEF;
		/*!!! WriteInfo hier */
		}
	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
