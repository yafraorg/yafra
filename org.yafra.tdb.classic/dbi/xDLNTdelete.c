/*D***********************************************************
 * Modul:     DBI - database delete
 *            DL-Nehmertyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLNTdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $

 Log Information:
 $Log: xDLNTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:38  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:06  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:34:39  16:34:39  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/03/11  14:09:14  14:09:14  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNTdelete.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

#define MSG1	(int)165
#define MSG2	(int)166

int DLNTdelete(void)
{
	extern REISENDER_TYP reit;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	/* Falls dltt UNDEF */
	if (reit.rkr_id == (int)_UNDEF)
		{
		(void)find_text_nr((int)MPE_IDXISUNDEF, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_REISENDER_TYP, (int)_PREIS, (char *)&reit) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG1, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_REISENDER_TYP, (int)_REISENDER, (char *)&reit) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG2, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_REISENDER_TYP, (char *)&reit);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_REISENDER_TYP;
		bez.bez_id=reit.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_REISENDER_TYP, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				(void)find_text_nr((int)MPE_NOBEZDEL, message);
				xSqlMessage(message);
				status=(int)MPERROR;
				}
			}
		}
	else
		{
		(void)find_text_nr((int)MPE_NODEL, message);
		xSqlMessage(message);
		status=(int)MPERROR;
		}

	return(status);
}
