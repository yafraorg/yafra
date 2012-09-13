/*D***********************************************************
 * Modul:     DBI - database action
 *            Kurs
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLWinput.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int LWinput(int len, char *buffer)
{
	extern int sprache;
	extern LAND_WHR lw;
	extern LAND land;
	extern WAEHRUNG whr;
	extern STATUS_WERTE sta;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	struct tm DateTime;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		whr.whr_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		lw.land_id = (int)_UNDEF;
		lw.whr_id = (int)_UNDEF;
		lw.kurs_typ = (int)_UNDEF;
		}

	/* get LAND */
	lw.land_id = MPAPIselectEntry((int)_LAND, to_buffers[MLW_LAND],
	             (char *)&land, sizeof(land), sizeof(land.land_id));

	/* get WAEHRUNG */
	lw.whr_id = MPAPIselectEntry((int)_WAEHRUNG, to_buffers[MLW_WHR],
	             (char *)&whr, sizeof(whr), sizeof(whr.whr_id));

	/* get KURSTYP as STATUS_WERTE */
	if (*to_buffers[MLW_KURSTYP] != NULL)
		{
		sta.typ = (int)_KURSTYP;
		if (getAttribut((int)_KURSTYP, to_buffers[MLW_KURSTYP]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		lw.kurs_typ = sta.sta_id;
		}
	else
		lw.kurs_typ = (int)_UNDEF;

	/* get buy/sell change rates */
	if (readDouble(&lw.a_kurs, to_buffers[MLW_AKURS]) == (int)MPERROR)
		lw.a_kurs = (double)0.;
	if (readDouble(&lw.v_kurs, to_buffers[MLW_VKURS]) == (int)MPERROR)
		lw.v_kurs = (double)0.;


	/* DATE of currency exchange rate */
	(void)ReadDate(&DateTime, (time_t *)&lw.von_dat, to_buffers[MLW_VONDAT]);


	/* check needed fields */
	if (lw.whr_id == (int)_UNDEF || lw.land_id == (int)_UNDEF)
		{
/*!!! new msg */
		UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	if (ACTIONTYP != (unsigned char)MPDELETE && lw.kurs_typ == (int)_UNDEF)
		{
/*!!! new msg */
		UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* write entry */
	status = WriteEntry((int)_LAND_WHR, (char *)&lw, NULL);
	if (status == (int)MPERROR)
		UtilMsg(status, MSGTYP_ERROR, NULL);
	else
		WriteInfo((int)_LAND_WHR, (char *)&lw, buffer);

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
