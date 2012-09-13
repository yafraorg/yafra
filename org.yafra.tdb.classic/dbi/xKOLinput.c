/*D***********************************************************
 * Modul:     DBI - database action
 *            KOLLEKTIV
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOLinput.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int KOLinput(int len, char *buffer )
{
	extern KOLLEKTIV kol;
	extern REISENDER rei;
	extern BEZEICHNUNG bez;
	extern KOLLEKTIV_TYP kolt;
	extern TEXTE txt;
	extern KOMMISSION kom;
	extern int sprache;
	
	REISENDER tmprei;
	KUNDEN rechnungsadr;
	KUNDEN buchungsstelle;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	/* init */
	kol.kid    = (int)_UNDEF;
	kol.k_id   = (int)_UNDEF;
	kol.textid = (int)_UNDEF;
	kol.k_sta  = (int)_UNDEF;	/* Nicht gesetzt */
	bez.s_id   = sprache;
	bez.typ    = (int)_KOLLEKTIV;
	txt.textid = (int)_UNDEF;
	txt.typ    = (int)_KOLLEKTIV;
	txt.s_id   = sprache;
	
	/* get menu fields */
	status = UtilSplitMenubuffer(buffer, to_buffers, NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kol.k_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* check MUST fields */
	if (*to_buffers[MKOL_BEZ] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}
	if (*to_buffers[MKOL_KOLT] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOKOLT, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}
	if (*to_buffers[MKOL_KUNBCH] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOBCHST, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	if (ACTIONTYP == UPDATE || ACTIONTYP == MPDELETE)
		{
		kol.k_id = MPAPIselectEntry((int)_KOLLEKTIV, to_buffers[MKOL_BEZ],
		     (char *)&kol, sizeof(KOLLEKTIV), sizeof(kol.k_id));
		}

	/* make action */
	switch (ACTIONTYP)
		{
		case MPDELETE:
			break;

		case UPDATE:
		case INSERT:
			/* BEZEICHNUNG only for INSERT */
			(void)copyTextTo(bez.bez, to_buffers[MKOL_BEZ], (int)_BEZLEN);

			/* KOLLEKTIV-TYP */
			kol.k_typ_id = MPAPIselectEntry((int)_KOLLEKTIV_TYP,
			        to_buffers[MKOL_KOLT], (char *)&kolt, sizeof(KOLLEKTIV_TYP),
			        sizeof(kol.k_typ_id));

			/* KUN BUCHUNGSSTELLE */
			kol.kbst = MPAPIselectEntry((int)_KUNDEN, to_buffers[MKOL_KUNBCH],
				(char *)&buchungsstelle, sizeof(KUNDEN), sizeof(kol.kbst));

			/* DLN as responsible */
			if ( *to_buffers[MKOL_VERANT] != NULL )
				{
				kol.hauptpers = MPAPIselectEntry( (int)_REISENDER, to_buffers[MKOL_VERANT], (char *)&tmprei,
											 sizeof( REISENDER ), sizeof( tmprei.pers_id ) );
				}
			else
				kol.hauptpers = (int)_UNDEF;
				
			/* KUN RECHNUNGSSTELLE */
			if (*to_buffers[MKOL_KUNRECH] != NULL)
				kol.kid = MPAPIselectEntry( (int)_KUNDEN, to_buffers[MKOL_KUNRECH],
				 (char *)&rechnungsadr, sizeof(KUNDEN), sizeof(kol.kid));

			/* KOL reference */
			if (*to_buffers[MKOL_REF] != NULL)
				(void)strcpy(kol.ref, to_buffers[MKOL_REF]);
			else
				*kol.ref = NULL;

			/* TEXTE */
			txt.textid = kol.textid;
			kol.textid = xTxtWrite(to_buffers[MKOL_TXT]);
			break;
		}

	/* ... and action */
	status = WriteEntry((int)_KOLLEKTIV, (char *)&kol, &bez);
	if (status != (int)MPOK)
		{
		kol.k_id = (int)_UNDEF;
		status   = (int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
