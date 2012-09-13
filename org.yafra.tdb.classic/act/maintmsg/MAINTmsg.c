/*D***********************************************************
 * Programm:     MAINTmsg.c
 * Beschreibung: Gibt die Programm-Fehlermeldungen aus
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/maintmsg/MAINTmsg.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/* define the entry point of this function for the main() */
int MAINTmsg(int, char *[]);
#define ACTIONFUNCTION MAINTmsg

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"    /* Standart main Funktion */

#include "version.h"    /* Standart main Funktion */

#define _SELECT_ALL_MSG "SELECT * FROM TDBADMIN.MSG ORDER BY MSG_TYP, MSG_ID;"

int MAINTmsg(int argc, char *argv[])
{
	extern MEMOBJ sqlmem;
	extern int aktuellesprache;
	extern FILE *FPout;

	MP_MSG *msgs;
	char query[RECLAENGE];
	int nextid;
	int previd;
	int status;
	int anzahl;
	int i;

	if (outputsprache == (int)UNDEF) {
		aktuellesprache = dialogsprache;
	} else {
		aktuellesprache = outputsprache;
	}
	/* F�r dynamisches Select aus */
	status = begin_transaction(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	(void)sprintf(query, _SELECT_ALL_MSG, (short)aktuellesprache);
	status = dynamic_sql_query((int)_MSG, &sqlmem.buffer, query, &anzahl,
          &sqlmem.datalen, &sqlmem.alloclen);
	(void)end_transaction();

	/* Pr�fe Status und Anzahl */
	if (status != (int)MPOK)
		return(status);
	if (anzahl < 1)
		return(status);

	/* Setzte MSG pointer */
	msgs=(MP_MSG *)sqlmem.buffer;

	/* Titel */
	fprintf(FPout, "\n\n");
	fprintf(FPout, "Typ ID      TextNr Text\n");
	fprintf(FPout, "=====================================================\n\n");

	/* alle Eintr�ge */
	i = 0;
	fprintf(FPout, "%3d %7d %6d %s\n", msgs[i].msg_typ, msgs[i].msg_id,
		                                msgs[i].textnr, msgs[i].text);
	for(i=1; i<anzahl; i++)
		{
		previd = msgs[(i-1)].msg_id;
		nextid = msgs[i].msg_id;
		if (previd != nextid)
			fprintf(FPout, "------------------------------------------------------\n\n");
			
		fprintf(FPout, "%3d %7d %6d %s\n", msgs[i].msg_typ, msgs[i].msg_id,
		                                   msgs[i].textnr, msgs[i].text);

		}
	return(status);
}
