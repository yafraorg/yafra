/*D***********************************************************
 * Modul:     DBI - database delete
 *            Kollektivtyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xKOLTdelete.c,v 1.2 2008-11-02 19:55:39 mwn Exp $

 Log Information:
 $Log: xKOLTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:39  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:08  mw
 update to new DB release 2.0

 * Revision 1.4  94/02/16  18:20:28  18:20:28  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.3  93/03/30  19:56:52  19:56:52  mw (Administrator)
 * "maintenance"
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOLTdelete.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

#define MSG1	(int)167
#define MSG2	(int)20
#define MSG3	(int)128
#define MSG4	(int)130

int KOLTdelete(void)
{
	extern KOLLEKTIV_TYP kolt;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if (kolt.k_typ_id == (int)_UNDEF)
		{
		(void)find_text_nr((int)MPE_IDXISUNDEF, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KOLLEKTIV_TYP, (int)_KOLLEKTIV, (char *)&kolt) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG1, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_KOLLEKTIV_TYP, (char *)&kolt);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_KOLLEKTIV_TYP;
		bez.bez_id=kolt.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_KOLLEKTIV_TYP, (char *)&bez) == (int)EMPTY)
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
