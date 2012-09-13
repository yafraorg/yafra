/*D***********************************************************
 * Modul:     DBI - database mutation on an object
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/WriteEntry.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int WriteEntry(int table , char *datastring , BEZEICHNUNG *bez )
{
	int status = (int)MPOK;

	switch (ACTIONTYP)
		{
		case (unsigned char)UPDATE:
			status = MPAPIupdateEntry(table, datastring, bez);
			break;
		case (unsigned char)INSERT:
			status = MPAPIinsertEntry(table, datastring, bez);
			break;
		case (unsigned char)MPDELETE:
			status = MenuDelete(table);
			break;
		default:
			status = MPE_WRONGACTIONTYP;
			MPlog(_LOGMP, MSGTYP_ERROR, "Falscher ACTIONTYP", __FILE__);
		}

	/* send messages for errors other than the standard error code */
	if (status != (int)MPOK && status != (int)MPERROR)
		UtilMsg(status, MSGTYP_ERROR, NULL);

	return(status);
}
