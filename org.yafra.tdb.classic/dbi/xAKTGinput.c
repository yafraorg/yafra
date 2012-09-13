/*D***********************************************************
 * Modul:     DBI - database input                           
 *            Aktionsgruppe
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTGinput.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int AKTGinput(int len, char *buffer)
{
	extern AKTIONEN akt;
	extern AKTIONSGRP aktgrp;
	extern int sprache;

	AKTIONEN hakt;
	char *to_buffers[MAX_MENU_ITEMS];
	char message[RECLAENGE];
	char tmp_buffer[RECLAENGE];
	char *buffer_ptr;
	int status=(int)MPOK;
	int buffersize;
	int ord;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		aktgrp.parentakt = (int)_UNDEF;
		aktgrp.childakt  = (int)_UNDEF;
		ord              = (int)_UNDEF;
		}

	/* PARENT Aktion */
	hakt.akt_id = _UNDEF;
	hakt.a_typ_id = _UNDEF;
	hakt.akt_id=MPAPIselectEntry((int)_AKTIONEN, to_buffers[MAKTG_HAKT],
	             (char *)&hakt, sizeof(AKTIONEN), sizeof(hakt.akt_id));
	if (hakt.akt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		hakt.akt_id=(int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* CHILD Aktion */
	akt.akt_id=MPAPIselectEntry((int)_AKTIONEN, to_buffers[MAKTG_AKT],
	             (char *)&akt, sizeof(AKTIONEN), sizeof(akt.akt_id));
	if (akt.akt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* ORD - Number of AKTION in a group */
	if (*to_buffers[MAKTG_ORD] == NULL)
		ord=MPAPIid_max((int)_AKTIONSGRP, (int)_ORD, (char *)&hakt) + (int)1;
	else
		{
		status=readInteger(&ord, to_buffers[MAKTG_ORD]);
		if (status == (int)MPERROR)
			ord=MPAPIid_max((int)_AKTIONSGRP, (int)_ORD, (char *)&hakt) + (int)1;
		else
			{
			if (ord < (int)1)
				ord=MPAPIid_max((int)_AKTIONSGRP, (int)_ORD,
										(char *)&hakt) + (int)1;
			}
		}

	aktgrp.parentakt = hakt.akt_id;
	aktgrp.childakt = akt.akt_id;
	aktgrp.ord = ord;
	aktgrp.h_akt_id = (int)_UNDEF; /*!!! noch ausprogrammieren */

	status=WriteEntry((int)_AKTIONSGRP, (char *)&aktgrp, NULL);
	if (status == (int)MPERROR)
		aktgrp.childakt=(int)_UNDEF;

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
