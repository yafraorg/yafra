/*D***********************************************************
 * Modul:     DBI - database delete
 *            KOMM_DETAIL
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMDdelete.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int KOMDdelete(void)
{
	extern KOMM_DETAIL komd;

	int status=(int)MPOK;

	/* pruefe ob irgendwas auch aktiv ist */
	if (komd.komm_id == (int)_UNDEF && komd.bid == (int)_UNDEF &&
	    komd.dln_id == (int)_UNDEF && komd.kun_id == (int)_UNDEF &&
	    komd.kol_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* delete */
	status = MPAPIdeleteEntry((int)_KOMM_DETAIL, (char *)&komd);
	if (status != MPOK && status != MPE_NOINSUPDDEL)
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
	
	return(status);
}
