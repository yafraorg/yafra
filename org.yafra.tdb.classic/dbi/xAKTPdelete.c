/*D***********************************************************
 * Modul:     DBI - database delete
 *            Aktionstypparameter
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xAKTPdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $

 Log Information:
 $Log: xAKTPdelete.c,v $
 Revision 1.2  2008-11-02 19:55:35  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:35  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  16:14:05  16:14:05  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  94/01/21  10:34:42  10:34:42  mw (Administrator)
 * new setup
 * 
 * Revision 1.1  93/09/15  19:01:09  19:01:09  mw (Administrator)
 * Initial revision
 * 
 * Revision 1.1  93/01/10  00:38:55  00:38:55  mw ()
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTPdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int AKTPdelete(void)
{
	extern AKTIONSPARA para;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;

	if (para.a_typ_id == (int)_UNDEF ||
		 para.nr == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_AKTIONSPARA, (char *)&para);
	if (status == (int)MPOK)
		{
		if (para.textid != (int)_UNDEF)
			{
			txt.typ=(int)_AKTIONSPARA;
			txt.textid=para.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) != (int)MPERROR)
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
