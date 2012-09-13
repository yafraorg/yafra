/*D***********************************************************
 * Modul:     DBI - database action
 *            Ort
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xORTinput.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int ORTinput(int len, char *buffer)
{
	extern int sprache;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern ORT ort;
	extern LAND land;
   extern STATUS_WERTE sta;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		ort.ort_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		ort.ort_id=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_ORT;
	(void)copyTextTo(bez.bez, to_buffers[MORT_BEZ], (int)_BEZLEN);
	if (*to_buffers[MORT_BEZ] != NULL)
		{
		if (*to_buffers[MORT_LAND] != NULL &&
			 (MPAPIselectEntry(_LAND, to_buffers[MORT_LAND], (char *)&land,
			  sizeof(land), sizeof(land.land_id)) != UNDEF))
			{
			ort.land_id = land.land_id;
			if (*to_buffers[MORT_KRZL] != NULL)
				(void)memcpy(ort.krzl, to_buffers[MORT_KRZL], _KRZLLEN);

			if (*to_buffers[MORT_ZEITVER] != NULL)
				ort.zeitver = atoi(to_buffers[MORT_ZEITVER]);
			else
				ort.zeitver = UNDEF;

			if (*to_buffers[MORT_KOORD1] != NULL)
				ort.koord1 = atoi(to_buffers[MORT_KOORD1]);
			else
				ort.koord1 = UNDEF;

			if (*to_buffers[MORT_KOORD2] != NULL)
				ort.koord2 = atoi(to_buffers[MORT_KOORD2]);
			else
				ort.koord2 = UNDEF;

			/* STATUS_WERTE  ORT_TYP */
			if (*to_buffers[MORT_TYP] != NULL)
				{
				sta.typ = (int)_STA_ORT;
				if (getAttribut((int)_STA_ORT, to_buffers[MORT_TYP]) != (int)MPOK)
					{
					UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				ort.ort_typ = sta.sta_id;
				}
			else
				ort.ort_typ = (int)_UNDEF;



			txt.typ=(int)_ORT;
			txt.s_id=(int)sprache;
			txt.textid=ort.textid;
			ort.textid=xTxtWrite(to_buffers[MORT_TXT]);

			status=WriteEntry((int)_ORT, (char *)&ort, &bez);
			if (status == (int)MPERROR)
				ort.ort_id=(int)_UNDEF;
			else
				(void)WriteInfo((int)_ORT, (char *)&ort, buffer);
			}
		else
			{
			/*??? MPE �ndern */
			UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
			ort.ort_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		ort.ort_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
