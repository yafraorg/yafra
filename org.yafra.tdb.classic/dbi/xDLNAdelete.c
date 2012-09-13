/*D***********************************************************
 * Modul:     DBI - database delete
 *            DLNA Dienstleistungsnehmer Attribute
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNAdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int DLNAdelete(void)
{
	extern PERSADR adr[];

	int status=(int)MPOK;

	if (adr[0].pers_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = MPAPIdeleteEntry((int)_PERSADR, (char *)&adr[0]);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	
	return( status );
}
