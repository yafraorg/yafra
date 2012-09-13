/*D***********************************************************
 * Modul:     DBI - menu
 *            manage matrix calls
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuMX.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int MenuMatrix(int len , char *buffer)
{
	int status=(int)MPOK;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	switch (COMMTYP)
		{
		case MATRIXSELECT:
			status = MXbinarysend(len, buffer);
			break;
		case MATRIXACTION:
			status = MXaction(len, buffer);
			break;
		}

	(void)MPAPIdb_committrx();

	if (status == (int)MPOK)
		comm.datalen = strlen(comm.buffer);
	else
		comm.datalen = 0;

	return(status);
}
