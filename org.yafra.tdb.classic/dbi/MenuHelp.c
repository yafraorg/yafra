/*D***********************************************************
 * Modul:     DBI - database select                           
 *            steuert die Helpausgabe
 *
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuHelp.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int MenuHelp(int *len, char *buffer)
{
	extern int sprache;
	char format[_RECORDLEN];
	int status=(int)MPOK;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	if (sprache == (int)1)
		(void)sprintf(comm.buffer, "index.html");
	else
		(void)sprintf(comm.buffer, "index.html");


	/* set length of output buffer */
	comm.datalen = strlen(comm.buffer);

	(void)MPAPIdb_committrx();
	return(status);
}
