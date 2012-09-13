/*D***********************************************************
 * Modul:     DBI - database action
 *            Kategorie
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKATinput.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

#define MSG3	(int)109

int KATinput(int len, char *buffer)
{
	extern KATEGORIE kat;
	extern BEZEICHNUNG bez;
	extern TRAEGER_TYP dltt;
	extern TEXTE txt;
	extern STATUS_WERTE sta;
	extern int sprache;

	KATEGORIE hkat;
	char *to_buffers[MAX_MENU_ITEMS];
	char buffer1[RECLAENGE];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kat.kat_id = (int)_UNDEF;
		return((int)MPERROR);
		}


	switch (ACTIONTYP)
		{
		case MPDELETE:
			if (*to_buffers[MKAT_BEZ] == NULL)
				{
				UtilMsg((int)MPE_NOKAT, MSGTYP_ERROR, NULL);
				kat.kat_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			else
				{
				if (MPAPIselectEntry((int)_KATEGORIE, to_buffers[MKAT_BEZ], (char *)&kat,
					     sizeof(kat), sizeof(kat.kat_id)) == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				}
			break;

		case INSERT:
		case UPDATE:
			if (ACTIONTYP == (unsigned char)INSERT)
				{
				kat.kat_id=(int)_UNDEF;
				kat.textid=(int)_UNDEF;
				txt.textid=(int)_UNDEF;
				}
			bez.s_id=(int)sprache;
			bez.typ=(int)_KATEGORIE;
			(void)copyTextTo(bez.bez, to_buffers[MKAT_BEZ], (int)_BEZLEN);
			if (*bez.bez != NULL)
				{
				if (*to_buffers[MKAT_DLTT] != NULL && (kat.typ_id=(int)MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MKAT_DLTT],
					 (char *)&dltt, sizeof(TRAEGER_TYP), sizeof(dltt.typ_id))) != (int)_UNDEF)
					{
					if (*to_buffers[MKAT_HKAT] != NULL)
						kat.h_kat_id=(int)MPAPIselectEntry((int)_KATEGORIE, to_buffers[MKAT_HKAT],
							(char *)&hkat,	sizeof(KATEGORIE), sizeof(kat.kat_id));
					else
						kat.h_kat_id=(int)_UNDEF;

					sta.typ=(int)_GA;
					(void)getAttribut((int)_GA, to_buffers[MKAT_GA]);
					kat.ga=sta.sta_id;

					txt.typ=(int)_KATEGORIE;
					txt.s_id=(int)sprache;
					txt.textid=kat.textid;
					kat.textid=xTxtWrite(to_buffers[MKAT_TXT]);
					}
				else
					{
					UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
					kat.kat_id=(int)_UNDEF;
					status=(int)MPERROR;
					}
				}
			else
				{
				UtilMsg((int)MPE_NOKAT, MSGTYP_ERROR, NULL);
				kat.kat_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			break;
		}

	if (status == MPOK)
		{
		status=WriteEntry((int)_KATEGORIE, (char *)&kat, &bez);
		if (status == (int)MPERROR)
			kat.kat_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_KATEGORIE, (char *)&kat, buffer);
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
