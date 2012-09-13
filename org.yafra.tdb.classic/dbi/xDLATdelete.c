/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungsangebotstyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLATdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $

 Log Information:
 $Log: xDLATdelete.c,v $
 Revision 1.2  2008-11-02 19:55:34  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:58  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  16:34:31  16:34:31  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  93/09/08  15:21:42  15:21:42  mw (Administrator)
 * new msg
 * 
 * Revision 1.1  93/09/08  15:10:30  15:10:30  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLATdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int DLATdelete(void)
{
	extern ANGEBOTS_TYP dlat;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if (dlat.art_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_ANGEBOTS_TYP, (int)_DIENST_ANGEBOT, (char *)&dlat) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLATDEL_DLA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_ANGEBOTS_TYP, (char *)&dlat);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_ANGEBOTS_TYP;
		bez.bez_id=dlat.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_ANGEBOTS_TYP, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
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
