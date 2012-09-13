/*D***********************************************************
 * modul:     DBI - database action
 *            ins/upd/del a KONTINGENT
 *
 *            the KONTINGENT is a child of a HOST_KONT object
 *            the KONTINGENT is defined for a client (must !)
 *            and has an own detail section in KONT_DETAIL
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int KONinput(int len, char *buffer)
{
	extern int sprache;
	extern int WarningFlag;

	extern HOST_KONT hkon;
	extern KONTINGENT kon;
	extern KUNDEN kun;
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
		kon.kont_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* init */
   kon.kunden_id = (int)_UNDEF;
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		kon.kont_id	=	(int)_UNDEF;
		kon.textid	=	(int)_UNDEF;
		txt.textid	=	(int)_UNDEF;
		}

	bez.s_id	= sprache;
	bez.typ	= (int)_KONTINGENT;
	(void)copyTextTo( bez.bez, to_buffers[MKON_BEZ], (int)_BEZLEN);
	if (*bez.bez == NULL)
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		kon.kont_id = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

/***************
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		k_d.kont_id = kon.kont_id = MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKON_BEZ],
		     (char *)&kon, sizeof(KONTINGENT), sizeof(kon.kont_id));
		}
****************/

	/* HOST_KONT check FROM kontingent */
	if (*to_buffers[MKON_HKON] != NULL)
		{
		kon.hostkont_id = MPAPIselectEntry((int)_HOST_KONT, to_buffers[MKON_HKON],
		                  (char *)&hkon, sizeof(HOST_KONT), sizeof(kon.hostkont_id));
		}
	else
		{
/*!!! make new message */
		UtilMsg((int)MPE_NOKON, MSGTYP_ERROR, NULL);
		kon.kont_id = (int)_UNDEF;
		kon.hostkont_id=(int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KUNDEN Kontingent an-Kunde resp _UNDEF f�r FITs */
	if (*to_buffers[MKON_KUN] != NULL)
		{
		kon.kunden_id = MPAPIselectEntry((int)_KUNDEN, to_buffers[MKON_KUN],
		   (char *)&kun, sizeof(KUNDEN), sizeof(kon.kunden_id) );
	   if (kon.kunden_id == (int)_UNDEF)
		   {
		   UtilMsg((int)MPE_NOHOLDER, MSGTYP_ERROR, NULL);
		   kon.kunden_id = (int)_UNDEF;
		   UtilSplitFreeMenubuffer(to_buffers);
		   return((int)MPERROR);
		   }
		}


	/* reference for the KONTINGENT (same like in BUCHUNG) */
	if ( *to_buffers[MKON_REF] != NULL ) 
		(void)strcpy(kon.ref, to_buffers[MKON_REF]);
	else
		*kon.ref = (char)NULL;

	/* date till option on KONTINGENT is valid */
	if ( *to_buffers[MKON_OPTDAT] != NULL )
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		ReadDate(&DateTime,(time_t *)&kon.opt_dat,to_buffers[MKON_OPTDAT]);
		}
	else
		kon.opt_dat=(int)_UNDEF;

	/* SAISON from HOST_KONT */
	kon.sai_id = hkon.sai_id;

	txt.typ=(int)_KONTINGENT;
	txt.s_id=sprache;
	txt.textid=kon.textid;
	kon.textid=xTxtWrite(to_buffers[MKON_TXT]);

	status = WriteEntry( (int)_KONTINGENT, (char *)&kon, &bez);
	if (status == (int)MPERROR)
		kon.kont_id=(int)_UNDEF;

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
