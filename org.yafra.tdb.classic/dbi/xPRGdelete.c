/*D***********************************************************
 * Modul:     DBI - database delete
 *            Programm
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xPRGdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $

 Log Information:
 $Log: xPRGdelete.c,v $
 Revision 1.2  2008-11-02 19:55:34  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:59  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  18:20:57  18:20:57  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  93/03/30  20:25:05  20:25:05  mw (Administrator)
 * "maintenance"
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPRGdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

#define MSG1	(int)143
#define MSG2	(int)20
#define MSG3	(int)128
#define MSG4	(int)130

int PRGdelete(void)
{
	extern PROGRAMM prg;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if (prg.prg_id == (int)_UNDEF)
		{
		(void)find_text_nr((int)MPE_IDXISUNDEF, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_PROGRAMM, (int)_ARRANGEMENT, (char *)&prg) != (int)EMPTY)
		{
		(void)find_text_nr((int)MSG1, message);
		xSqlMessage(message);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_PROGRAMM, (char *)&prg);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_PROGRAMM;
		bez.bez_id=prg.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_PROGRAMM, (char *)&bez) == (int)EMPTY)
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
