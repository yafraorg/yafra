/*D***********************************************************
 * modul:     DBI - database action
 *            ins/upd/del a HOST_KONT
 *
 *            the HOST_KONT is the root definition of KONTINGENT
 *            there are two typs of HOST_KONT:
 *            - a internal allotment  (FROM_PERS = UNDEF)
 *            - a external allotment from a client to us (FROM_PERS != UNDEF)
 *
 *            it's depending on:
 *            - DIENST_ANGEBOT
 *            - DIENSTLEISTUNG
 *            - DIENSTLEISTUNG from/to date
 *
 *            the giving to client definition is saved in KONTINGENT
 *            (see KONTINGENT)
 *
 *            the detail relations are in KONT_DETAIL  (see KONT_DETAIL)
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONHinput.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int KONHinput(int len, char *buffer)
{
	extern int sprache;

	extern HOST_KONT hkon;
	extern KUNDEN kun;
	extern DIENSTLEISTUNG dl;
	extern DIENST_ANGEBOT dla;
	extern SAISON sai;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	struct tm DateTime;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int id;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~' );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		hkon.hostkont_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* init */
	hkon.dla_id	= (int)_UNDEF;
	hkon.dl_id	= (int)_UNDEF;
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		hkon.hostkont_id =	(int)_UNDEF;
		hkon.history =			(int)_UNDEF;
		hkon.dl_vondat =		(int)_UNDEF;
		hkon.dl_bisdat	=		(int)_UNDEF;
		hkon.textid	=			(int)_UNDEF;
		txt.textid	=			(int)_UNDEF;
		}

	bez.s_id	= sprache;
	bez.typ	= (int)_HOST_KONT;
	(void)copyTextTo( bez.bez, to_buffers[MHKON_BEZ], (int)_BEZLEN);
	if (*bez.bez == NULL)
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		hkon.hostkont_id = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

/***********
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		hkon.hostkont_id = MPAPIselectEntry((int)_HOST_KONT, to_buffers[MHKON_BEZ],
		     (char *)&hkon, sizeof(HOST_KONT), sizeof(hkon.hostkont_id));
		}
**************/
	
	/* KUNDEN Buchungsstelle */
	if (*to_buffers[MHKON_BST] != NULL && 
	   (hkon.kbst = MPAPIselectEntry((int)_KUNDEN, to_buffers[MHKON_BST],
		(char *)&kun, sizeof(KUNDEN), sizeof(hkon.kbst))) != (int)_UNDEF)
		{
		if ( *to_buffers[MHKON_DLA] != NULL )
			{
			if ( *to_buffers[MHKON_DL] != NULL )
				{
				UtilMsg((int)MPE_ONLYDLORDLA, MSGTYP_ERROR, NULL);
				hkon.hostkont_id	= (int)_UNDEF;
				UtilSplitFreeMenubuffer(to_buffers);
				return((int)MPERROR);
				}
			else
				{
				hkon.dla_id=MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MHKON_DLA],
				    (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(hkon.dla_id));
				hkon.sai_id=(int)_UNDEF;
				hkon.dl_id=(int)_UNDEF;
				}		
			}
		else
			{
			if (*to_buffers[MHKON_DL] != NULL &&
			   (hkon.dl_id=MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MHKON_DL],
				(char *)&dl, sizeof(DIENSTLEISTUNG), sizeof(dl.dlg_id))) != (int)_UNDEF)
				{
				hkon.sai_id = dl.sai_id;
				hkon.dla_id=(int)_UNDEF;
				}
			else
				{
				hkon.sai_id=(int)_UNDEF;
				hkon.dla_id=(int)_UNDEF;
				hkon.dl_id=(int)_UNDEF;
				}
			}		

		/* KUNDEN Kontingent von-Kunde */
		if (*to_buffers[MHKON_KUN] != NULL)
			{
			hkon.from_pers = MPAPIselectEntry((int)_KUNDEN, to_buffers[MHKON_KUN],
			                 (char *)&kun, sizeof(KUNDEN), sizeof(hkon.from_pers));
			}
		else
			hkon.from_pers = (int)_UNDEF;

		/* Dienstleistung oder Dienstleistungsangebot */
		/* m�ssen vorhanden sein */
		if (hkon.dla_id != (int)_UNDEF || hkon.dl_id != (int)_UNDEF)
			{
			/* reference for the KONTINGENT (same like in BUCHUNG) */
			if ( *to_buffers[MHKON_REF] != NULL ) 
				(void)strcpy(hkon.ref, to_buffers[MHKON_REF]);
			else
				*hkon.ref = (char)NULL;

			/* date till option on KONTINGENT is valid */
			if ( *to_buffers[MHKON_OPTDAT] != NULL )
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				ReadDate(&DateTime,(time_t *)&hkon.opt_dat,to_buffers[MHKON_OPTDAT]);
				}
			else
				hkon.opt_dat=(int)_UNDEF;

			txt.typ=(int)_HOST_KONT;
			txt.s_id=sprache;
			txt.textid=hkon.textid;
			hkon.textid=xTxtWrite(to_buffers[MKON_TXT]);

			status=WriteEntry((int)_HOST_KONT, (char *)&hkon, &bez);
			if ( status == (int)MPERROR )
				hkon.hostkont_id=(int)_UNDEF;
			}
		else
			{
			UtilMsg((int)MPE_MUSTONDLORDLA, MSGTYP_ERROR, NULL);
			hkon.hostkont_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOHOLDER, MSGTYP_ERROR, NULL);
		hkon.hostkont_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
