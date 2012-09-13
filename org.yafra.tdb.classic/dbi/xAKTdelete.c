/*D***********************************************************
 * Modul:     DBI - database delete
 *            delete an action
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xAKTdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $

 Log Information:
 $Log: xAKTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:38  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:39  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  16:14:08  16:14:08  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  94/02/10  09:28:31  09:28:31  mw (Administrator)
 * update group handling
 * 
 * Revision 1.1  93/05/02  16:59:43  16:59:43  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

#define MSG1	(int)159
#define MSG2	(int)160
#define MSG3	(int)161

int AKTdelete(void)
{
	extern AKTIONEN akt;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;

	if (akt.akt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_AKTIONEN, (int)_DIENST_ANGEBOT, (char *)&akt) != (int)EMPTY)
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_AKTIONEN, (int)_DIENSTLEISTUNG, (char *)&akt) != (int)EMPTY)
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_AKTIONEN, (int)_AKT_DETAIL, (char *)&akt) != (int)EMPTY)
		{
		UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_AKTIONEN, (int)_AKTIONSGRP, (char *)&akt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOAKTDEL_AKTG, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_AKTIONEN, (char *)&akt);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_AKTIONEN;
		bez.bez_id=akt.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_AKTIONEN, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (akt.textid != (int)_UNDEF)
			{
			txt.typ=(int)_AKTIONEN;
			txt.textid=akt.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
