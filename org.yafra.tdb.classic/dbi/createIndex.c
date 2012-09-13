/*D***********************************************************
 * modul:  DB create an index in an RDBMS with SQL
 *
 * desc:   Erkennt aus den SYSTEM.TABELLEN die verwendeten
 *			  Indices auf einer Tabelle, l�scht sie und
 *			  schreibt den CREATE-string in einen Buffer.
 *
 * return: UNDEF wenn ein Fehler vorhanden ist
 *         anzahl wenn alles in Ordnung
 *
 * (c):    yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/createIndex.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int createIndex(char *table, char **ptr, int *anzahl)
{
	int status=(int)MPOK;
	int i;
	int count;

	for(i=0; i<*anzahl; i++)
		status = MPAPIdb_sqlcommand(ptr[i], &count);

	return(status);
}
