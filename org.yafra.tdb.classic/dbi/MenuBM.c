/*D***********************************************************
 * Modul:     DBI - booking
 *            manage booking mask calls
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuBM.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int MenuBM(int len, char *buffer)
{
	extern int save_point;
	int status=(int)MPOK;

	/* start transaction */
	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	switch (COMMTYP)
		{
		case BMOBJCHOOSE: /* sende Auswahl Buchungsobjekt */
			status = BMobjChoose(len, buffer);
			break;
		case BMBOOK:      /* sende Reservationsmaske (Kategorieauswahl) */
			status = BMRESsend(len, buffer);
			break;
		}

	/* end transaction */
	if (status != MPOK)
		MPAPIdb_rollbacktrx();
	else
		MPAPIdb_committrx();

	if (status == (int)MPOK)
		comm.datalen = strlen(comm.buffer);

	return(status);
}
