/*D***********************************************************
 * Modul:     DBI - database action
 *            Statuswerte
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSTAinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

#define MSG2	(int)26
#define MSG3	(int)120

int STAinput(int len, char *buffer)
{
	extern BEZEICHNUNG bez;
	extern STATUS_WERTE sta;
	extern TEXTE txt;
	extern int sprache;

	BEZEICHNUNG tmpbez;

	char *to_buffers[MAX_MENU_ITEMS];
	char message[RECLAENGE];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		sta.sta_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		sta.sta_id = (int)_UNDEF;

	if (*to_buffers[MSTA_BEZ] != NULL)
		{
		bez.s_id=(int)sprache;
		(void)copyTextTo(bez.bez, to_buffers[MSTA_BEZ], (int)_BEZLEN);
		if (*to_buffers[MSTA_KOND] == NULL)
			sta.kond = (double)_UNDEF;
		else
			{
			if(readDouble(&sta.kond, to_buffers[MSTA_KOND]) == (int)MPERROR) sta.kond = (double)_UNDEF;
			}

		if (*to_buffers[MSTA_ABK] == NULL)
			(void)strcpy(sta.abk, "");
		else
			(void)strcpy(sta.abk, to_buffers[MSTA_ABK]);

		if (*to_buffers[MSTA_WERT] == NULL)
			(void)strcpy(sta.sta, "");
		else
			(void)strcpy(sta.sta, to_buffers[MSTA_WERT]);

		tmpbez.s_id=(int)sprache;
		tmpbez.typ = (int)_NAMEN;
		(void)copyTextTo(tmpbez.bez, to_buffers[MSTA_TYP], (int)_BEZLEN);
		if (*to_buffers[MSTA_TYP] != NULL && MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MSTA_TYP],
				(char *)&tmpbez, sizeof(BEZEICHNUNG),
				sizeof(bez.bez_id)) != (int)_UNDEF)
			{
			sta.typ = tmpbez.typ;
			bez.typ = tmpbez.typ;
			status=WriteEntry((int)_STATUS_WERTE, (char *)&sta, &bez);
			if (status == (int)MPERROR)
				sta.sta_id=(int)_UNDEF;
			else
				(void)WriteInfo((int)_STATUS_WERTE, (char *)&sta, buffer);
			}
		else
			{
			UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
