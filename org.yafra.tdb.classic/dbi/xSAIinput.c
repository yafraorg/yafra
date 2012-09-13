/*D***********************************************************
 * Modul:     DBI - database action
 *            Saison
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSAIinput.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int SAIinput(int len, char *buffer)
{
	extern BEZEICHNUNG bez;
	extern SAISON sai;
	extern TEXTE txt;
	extern int sprache;

	struct tm DateTime;
	int status=(int)MPOK;
	char *to_buffers[MAX_MENU_ITEMS];

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		sai.sai_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		sai.sai_id=(int)_UNDEF;
		sai.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_SAISON;
	(void)copyTextTo(bez.bez, to_buffers[MSAI_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
     	(void)copyTextTo(sai.code, to_buffers[MSAI_CODE], (int)_KRZLLEN);
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&sai.von, to_buffers[MSAI_VON]);
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&sai.bis, to_buffers[MSAI_BIS]);
		if ((sai.von != (int)_UNDEF && sai.bis != (int)_UNDEF) &&
		     sai.bis > sai.von)
			{
			txt.typ=(int)_SAISON;
			txt.s_id=(int)sprache;
			txt.textid=sai.textid;
			sai.textid=xTxtWrite(to_buffers[MSAI_TXT]);

			status=WriteEntry((int)_SAISON, (char *)&sai, &bez);
			if (status == (int)MPERROR)
				sai.sai_id=(int)_UNDEF;
			else
				(void)WriteInfo((int)_SAISON, (char *)&sai, buffer);
			}
		else
			{
			UtilMsg((int)MPE_DATEFROMTO, MSGTYP_ERROR, NULL);
			sai.sai_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		sai.sai_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
