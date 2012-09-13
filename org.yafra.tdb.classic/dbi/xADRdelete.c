/*D***********************************************************
 * Modul:     DBI - database delete
 *            PERSADR
 *            delete an address of a person (privat or firm)
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xADRdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int ADRdelete(void)
{
	extern PERSADR adr;

	int status=(int)MPOK;

	if (adr.pers_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_PERSADR, (char *)&adr);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
