/*D***********************************************************
 * Modul:     DBI - database action
 *            Dienstleistungstr�gertyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTTinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int DLTTinput(int len, char *buffer)
{
	extern BEZEICHNUNG bez;
	extern TRAEGER_TYP dltt;
	extern TEXTE txt;
	extern int sprache;

	TRAEGER_TYP hdltt;

	char *to_buffers[MAX_MENU_ITEMS];
	char message[RECLAENGE];
	char buffer1[RECLAENGE];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dltt.typ_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	switch (ACTIONTYP)
		{
		case MPDELETE:
			if (*to_buffers[MDLTT_BEZ] == NULL)
				{
				UtilMsg((int)MPE_NODLTT, MSGTYP_ERROR, NULL);
				dltt.typ_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			else
				{
				if (*to_buffers[MDLTT_HDLTT] != NULL)
					{
					(void)strcpy(buffer1, to_buffers[MDLTT_BEZ]);
					(void)strcat(buffer1, TRENNER);
					(void)strcat(buffer1, to_buffers[MDLTT_HDLTT]);
					}
				else
					{
					UtilMsg((int)MPE_NODLTT, MSGTYP_ERROR, NULL);
					dltt.typ_id = (int)_UNDEF;
					status = (int)MPERROR;
					}
				if (MPAPIselectEntry((int)_TRAEGER_TYP, buffer1, (char *)&dltt,
					     sizeof(dltt), sizeof(dltt.typ_id)) == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				}
			break;

		case INSERT:
		case UPDATE:
			if (ACTIONTYP == (int)INSERT)
				{
				dltt.typ_id=(int)_UNDEF;
				dltt.textid=(int)_UNDEF;
				txt.textid=(int)_UNDEF;
				}
			bez.s_id=(int)sprache;
			bez.typ=(int)_TRAEGER_TYP;
			(void)copyTextTo(bez.bez, to_buffers[MDLTT_BEZ], (int)_BEZLEN);
			if (*to_buffers[MDLTT_BEZ] != NULL)
				{
				if (*to_buffers[MDLTT_HDLTT] != NULL)
					dltt.h_typ_id=(int)MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLTT_HDLTT], (char *)&hdltt,
									sizeof(TRAEGER_TYP), sizeof(dltt.typ_id));
				else
					dltt.h_typ_id=(int)_UNDEF;

				if (dltt.h_typ_id == (int)_UNDEF)
					dltt.host_typ=(int)_UNDEF;
				else
					dltt.host_typ=hdltt.host_typ;

				txt.typ=(int)_TRAEGER_TYP;
				txt.s_id=(int)sprache;
				txt.textid=dltt.textid;
				dltt.textid=xTxtWrite(to_buffers[MDLTT_TXT]);
				}
			else
				{
				UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
				dltt.typ_id=(int)_UNDEF;
				status=(int)MPERROR;
				}
			break;
		}


	/* F�hre Aktion aus */
	if (status == MPOK)
		{
		status=WriteEntry((int)_TRAEGER_TYP, (char *)&dltt, &bez);
		if (status == (int)MPERROR)
			dltt.typ_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_TRAEGER_TYP, (char *)&dltt, buffer);
		}
	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
