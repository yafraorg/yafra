/*D***********************************************************
 * Modul:     DBI - database delete
 *            Kostenarten
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xKARdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $

 Log Information:
 $Log: xKARdelete.c,v $
 Revision 1.2  2008-11-02 19:55:37  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:59  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  18:20:23  18:20:23  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/03/30  19:48:46  19:48:46  mw (Administrator)
 * "maintenance"
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKARdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#define MSG1	(int)202
#define MSG2	(int)260

int KARdelete(void)
{
	extern KOSTEN_ART kar;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	/* Falls kar UNDEF */
	if (kar.kar_id == (int)_UNDEF)
		{
		(void)find_text_nr((int)MPE_IDXISUNDEF, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KOSTEN_ART, (int)_PREIS, (char *)&kar) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG1, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KOSTEN_ART, (int)_KOMM_DETAIL, (char *)&kar) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG2, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_KOSTEN_ART, (char *)&kar);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_KOSTEN_ART;
		bez.bez_id=kar.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_KOSTEN_ART, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) != MPOK)
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
