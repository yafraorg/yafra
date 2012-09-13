/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungstr�gertyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLTTdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $

 Log Information:
 $Log: xDLTTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:35  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:16  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:34:47  16:34:47  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/07/12  22:24:53  22:24:53  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTTdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

static int DLTTdeleteOneEntry(TRAEGER_TYP);

int DLTTdelete(void)
{
	extern int sprache;
	extern TRAEGER_TYP dltt;

	char message[RECLAENGE];
	int status=(int)MPOK;

	/* Falls dltt UNDEF */
	if (dltt.typ_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist in RESERVATION noch etwas drauf ? */
	if (MPAPIid_count((int)_TRAEGER_TYP, (int)_RESERVATION, (char *)&dltt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTTDEL_RES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Gibt es noch Kategorien darauf ? */
	if (MPAPIid_count((int)_TRAEGER_TYP, (int)_KATEGORIE, (char *)&dltt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTTDEL_KAT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Sind noch DLTs definiert ? */
	if (MPAPIid_count((int)_TRAEGER_TYP, (int)_DIENST_TRAEGER, (char *)&dltt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTTDEL_DLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Gibt es noch Parent Eintr�ge ? */
	if (MPAPIid_count((int)_TRAEGER_TYP, (int)_TRAEGER_TYP, (char *)&dltt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTTDEL_DLTT, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else
		status = DLTTdeleteOneEntry(dltt);

	return(status);
}


/*************************************************************
 * Function:  DLTTdeleteOneEntry
 * Typ:       private for DLTTdelete
 * Desc:      delete one DLTT with TXT and BEZ
 *************************************************************/
static int DLTTdeleteOneEntry(TRAEGER_TYP localdltt)
{
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	char message[RECLAENGE];
	int status = MPOK;

	/* L�sche nun DLTT */
	status = MPAPIdeleteEntry((int)_TRAEGER_TYP, (char *)&localdltt);
	if (status == (int)MPOK)
		{
		/* L�sche Bezeichnung und Texte */
		bez.bez_id=localdltt.bez_id;
		status = MPAPIid_count((int)_BEZEICHNUNG, (int)_TRAEGER_TYP, (char *)&bez);
		if (status == EMPTY && localdltt.bez_id != _UNDEF)
			{
			bez.typ=(int)_TRAEGER_TYP;
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (localdltt.textid != _UNDEF)
			{
			txt.typ=(int)_TRAEGER_TYP;
			txt.textid=localdltt.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else /* konnte Objekt nicht l�schen */
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
