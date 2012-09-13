/*D***********************************************************
 * Modul:     DBI - database delete
 *            KONT_DETAIL
 *            if kat_id or dlt_id are UNDEF then delete
 *            everything of this KONTINGENT or HOST_KONT
 *            else delete only specified KAT or DLT
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONDdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int KONDdelete(void)
{
	extern KONT_DETAIL k_d;

	int status=(int)MPOK;

	if (k_d.kont_id == (int)_UNDEF && k_d.hostkont_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_KONT_DETAIL, (char *)&k_d);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
