/*D***********************************************************
 * Modul:     DBI - database delete
 *            Aktionsgruppe
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTGdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int AKTGdelete(void)
{
	extern AKTIONSGRP aktgrp;

	int status=(int)MPOK;

	if (aktgrp.parentakt == (int)_UNDEF || aktgrp.childakt == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_AKTIONSGRP, (char *)&aktgrp);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
