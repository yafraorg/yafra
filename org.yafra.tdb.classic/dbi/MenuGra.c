/*D***********************************************************
 * Modul:     DBI - database select                           
 *            steuert die Infoausgabe
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuGra.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int MenuGraphics(int len , char *buffer)
{
	extern int save_point;

	int status=(int)MPOK;

	status=MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	switch(COMMTYP)
		{
		case GRAINPUT:	/* Anfrage f�r die Daten einer neuen oder bestehenden Graphik */
			status = GRinput(len, buffer );
			break;
		case GRASEND:	/* Die neuen Graphikdaten ( Regions ) in die Datenbank schreiben */
			(void)MPAPIdb_setsavepoint( &save_point );
			status = GRwrite(len, buffer );
			/* rollback work if an error occured */
			if (status != (int)MPOK)
				(void)MPAPIdb_rollbacksavepoint(&save_point);
			break;
		case GRASELECT: /* Anfrage f�r die Graphikdaten einer bestehenden Graphik */
			status = GRselect(len, buffer);
			break;
		case GRAREFRESH: /* Buchungsaufforderung aus der Graphik */
			status = GRrefresh(len, buffer );
			break;
		case GRACHOOSE: /* COMMIT der ausgew�hlten DLT's beim graphischen Buchen */
			status = GRchoose(len, buffer );
			break;
		}

	(void)MPAPIdb_committrx();
	return(status);
}
