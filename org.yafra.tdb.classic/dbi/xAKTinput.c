/*D***********************************************************
 * Modul:     DBI - database input
 *            Aktionen
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int AKTinput(int len, char *buffer)
{
	extern AKTIONEN akt;
	extern AKTIONSGRP aktgrp;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern AKTIONS_TYP aktt;
	extern STATUS_WERTE sta;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[RECLAENGE];
	char *buffer_ptr;
	int status=(int)MPOK;
	int buffersize;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		akt.akt_id=(int)_UNDEF;
		akt.b_flag=(int)_UNDEF;
		akt.b2_flag=(int)_UNDEF;
		akt.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	/* AKTION */
	if (ACTIONTYP != INSERT && ACTIONTYP != UPDATE)
		{
		akt.akt_id=MPAPIselectEntry((int)_AKTIONEN, to_buffers[MAKT_BEZ],
		             (char *)&akt, sizeof(AKTIONEN), sizeof(akt.akt_id));
		if (akt.akt_id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			akt.akt_id=(int)_UNDEF;
			return((int)MPERROR);
			}
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_AKTIONEN;
	(void)copyTextTo(bez.bez, to_buffers[MAKT_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		if (*to_buffers[MAKT_AKTT] == NULL)
			akt.a_typ_id = (int)_UNDEF;
		else
			{
			akt.a_typ_id=(int)MPAPIselectEntry((int)_AKTIONS_TYP, to_buffers[MAKT_AKTT],
			          (char *)&aktt, sizeof(AKTIONS_TYP), sizeof(akt.a_typ_id));
			}

		if (*to_buffers[MAKT_STAAUS] == NULL)
			akt.a_flag = (int)_UNDEF;
		else
			{
			sta.typ = (int)_A_FLG;
			status = getAttribut((int)_A_FLG, to_buffers[MAKT_STAAUS]);
			if (status != (int)MPERROR)
				akt.a_flag=sta.sta_id;
			else
				{
				UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
				akt.akt_id=(int)_UNDEF;
				UtilSplitFreeMenubuffer(to_buffers);
				return((int)MPERROR);
				}
			}

		if (*to_buffers[MAKT_STAINRES] == NULL)
			akt.b_flag = (int)_UNDEF;
		else
			{
			sta.typ = (int)_R_STA;
			status = getAttribut((int)_R_STA, to_buffers[MAKT_STAINRES]);
			if (status != (int)MPERROR)
				akt.b_flag=sta.sta_id;
			else
				{
				UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
				akt.akt_id=(int)_UNDEF;
				UtilSplitFreeMenubuffer(to_buffers);
				return((int)MPERROR);
				}
			}

		if (*to_buffers[MAKT_STAOUTRES] == NULL)
			akt.b2_flag = (int)_UNDEF;
		else
			{
			sta.typ = (int)_R_STA;
			status = getAttribut((int)_R_STA, to_buffers[MAKT_STAOUTRES]);
			if (status != (int)MPERROR)
				akt.b2_flag=sta.sta_id;
			else
				{
				UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
				akt.akt_id=(int)_UNDEF;
				UtilSplitFreeMenubuffer(to_buffers);
				return((int)MPERROR);
				}
			}

		if (*to_buffers[MAKT_STADEV] == NULL)
			akt.m_flag = (int)_UNDEF;
		else
			{
			sta.typ = (int)_DEVICE;
			status = getAttribut((int)_DEVICE, to_buffers[MAKT_STADEV]);
			if (status != (int)MPERROR)
				akt.m_flag=sta.sta_id;
			else
				{
				UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
				akt.akt_id=(int)_UNDEF;
				UtilSplitFreeMenubuffer(to_buffers);
				return((int)MPERROR);
				}
			}

		txt.typ=(int)_AKTIONEN;
		txt.s_id=(int)sprache;
		txt.textid=akt.textid;
		akt.textid=xTxtWrite(to_buffers[MAKT_TXT]);

		status=WriteEntry((int)_AKTIONEN, (char *)&akt, &bez);
		if (status == (int)MPERROR)
			akt.akt_id=(int)_UNDEF;
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
