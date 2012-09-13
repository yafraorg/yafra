/*D***********************************************************
 * Programm:     MAINTdlt
 * Beschreibung: wartet den Dienstleistungstr�ger
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/maintdlt/MAINTdlt.c,v 1.2 2008-11-02 19:55:53 mwn Exp $";

/* define the entry point of this function for the main() */
int MAINTdlt(int, char *[]);
#define ACTIONFUNCTION MAINTdlt

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"    /* Standart main Funktion */

#define _MWALLDLT "SELECT TDBADMIN.DIENST_TRAEGER.* \
	FROM TDBADMIN.DIENST_TRAEGER;"

#define _MWUPDLT "UPDATE TDBADMIN.DIENST_TRAEGER \
	SET H_BEZ_ID=%d WHERE DLT_ID=%d;"

int MAINTdlt(int argc, char *argv[])
{
	extern MEMOBJ sqlmem;
	char query[RECLAENGE];
	int Savepoint;
	int anzahl;
	int i;
	int id;
	int status = (int)MPOK;
	int count;
	DIENST_TRAEGER *dlts;
	DIENST_TRAEGER hdlt;

	/* begin trx */
	status = begin_transaction(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != MPOK)
		return(status);

	/* lese alle DLTs */
	(void)sprintf(query, _MWALLDLT);
	status = dynamic_sql_query((int)_DIENST_TRAEGER, &sqlmem.buffer, query,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == MPOK && anzahl > (int)0)
		{
		/* setze h_bez_id von jedem DLT */
		status = set_savepoint(&Savepoint);
		if (status != MPOK)
			return(status);
		dlts = (DIENST_TRAEGER *)sqlmem.buffer;
		for (i = 0; i < anzahl; i++)
			{
			if (dlts[i].h_dlt_id == UNDEF)
				continue;
			id = SelectOneId((int)_DIENST_TRAEGER, dlts[i].h_dlt_id, (char *)&hdlt);
			if (id == UNDEF)
				return(MPERROR);
			(void)sprintf(query, _MWUPDLT, hdlt.bez_id, dlts[i].dlt_id);
			status=dynamic_sql_command(query, &count);
			if (status != MPOK)
				return(status);
			}
		}

	/* Falls Fehler zur�ck zum savepoint sonst commit */
	if (status != MPOK)
		(void)roll_back_work(&Savepoint);
	else
		(void)end_transaction();

	return(status);
}
