/*D***********************************************************
 * Modul:     DBI - database action
 *            Land
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLANDinput.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int LANDinput(int len, char *buffer)
{
	extern int sprache;
	extern SPRACHEN spr;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern LAND land;
	extern ORT ort;
	extern WAEHRUNG whr;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		land.land_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		land.land_id=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	/* SPRACHEN */
	if (*to_buffers[MLAND_SPR] != NULL &&
		 (MPAPIselectEntry(_SPRACHEN, to_buffers[MLAND_SPR], (char *)&spr,
		  sizeof(spr), sizeof(spr.s_id)) != UNDEF))
		land.haupt_spr = spr.s_id;
	else
		land.haupt_spr = sprache;

	/* ORT Hauptstadt */
	if (*to_buffers[MLAND_ORT] != NULL &&
		 (MPAPIselectEntry(_ORT, to_buffers[MLAND_ORT], (char *)&ort,
		  sizeof(ort), sizeof(ort.ort_id)) != UNDEF))
		land.haupt_ort = ort.ort_id;
	else
		land.haupt_ort = _UNDEF;

	/* WAEHRUNG  Landesw�hrung */
	if (*to_buffers[MLAND_WHR] != NULL &&
		 (MPAPIselectEntry(_WAEHRUNG, to_buffers[MLAND_WHR], (char *)&whr,
		  sizeof(whr), sizeof(whr.whr_id)) != UNDEF))
		land.haupt_whr = whr.whr_id;
	else
		land.haupt_whr = _UNDEF;

	bez.s_id=(int)sprache;
	bez.typ=(int)_LAND;
	(void)copyTextTo(bez.bez, to_buffers[MLAND_BEZ], (int)_BEZLEN);
	if (*to_buffers[MLAND_BEZ] != NULL)
		{
		if (*to_buffers[MLAND_KRZL] != NULL)
			(void)memcpy(land.krzl, to_buffers[MLAND_KRZL], _KRZLLEN);

		if (readDouble(&land.vat, to_buffers[MLAND_VAT]) == (int)MPERROR)
			land.vat = (double)0.;

		if (*to_buffers[MLAND_DATEFORMAT] != NULL)
			(void)memcpy(land.krzl, to_buffers[MLAND_DATEFORMAT], _CHAR20);


		txt.typ=(int)_LAND;
		txt.s_id=(int)sprache;
		txt.textid=land.textid;
		land.textid=xTxtWrite(to_buffers[MLAND_TXT]);

		status=WriteEntry((int)_LAND, (char *)&land, &bez);
		if (status == (int)MPERROR)
			land.land_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_LAND, (char *)&land, buffer);
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		land.land_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
