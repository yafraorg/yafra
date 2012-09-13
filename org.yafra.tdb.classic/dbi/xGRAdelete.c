/*D***********************************************************
 * Modul:     DBI - database delete
 *            Graphik
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xGRAdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: xGRAdelete.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:35  mw
 update to new DB release 2.0

 * Revision 1.5  94/02/16  18:20:19  18:20:19  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.4  93/07/19  15:10:19  15:10:19  mw (Administrator)
 * "delete order"
 * 
 * Revision 1.3  93/03/30  19:43:29  19:43:29  mw (Administrator)
 * "maintenance"
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xGRAdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int GRAdelete(void)
{
	extern GRAPHIK gra;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	/* a graphic must be activ */
	if (gra.gra_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* delete the graphic format data */
	status = MPAPIdeleteEntry((int)_GRAFORM, (char *)&gra);
	if (status == (int)MPERROR)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* delete all regions for this object */
	status = MPAPIdeleteEntry((int)_REGIONS, (char *)&gra);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* delete the graphic object */
	status = MPAPIdeleteEntry((int)_GRAPHIK, (char *)&gra);
	if (status == (int)MPERROR)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	
	return(status);
}
