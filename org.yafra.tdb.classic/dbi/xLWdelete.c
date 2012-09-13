/*D***********************************************************
 * Modul:     DBI - database delete
 *            Kurse
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLWdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int LWdelete(void)
{
	extern LAND_WHR lw;

	int status = MPOK;

	if (lw.whr_id == (int)_UNDEF || lw.land_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_LAND_WHR, (char *)&lw);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
