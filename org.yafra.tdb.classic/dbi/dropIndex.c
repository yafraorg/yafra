/*D***********************************************************
 * Modul:     DBI - database select                           
	           Erkennt aus den SYSTEM.TABELLEN die verwendeten
			     Indices auf einer Tabelle, l�scht sie und
			     schreibt den CREATE-string in einen Buffer.
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsql.h>
#include <mpsqlsel.h>
#include <mpdb.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/dropIndex.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int dropIndex(char *table, char **ptr, int *anzahl)
{
	extern MEMOBJ sqlmem;

	char tableString[_CHAR20+1];
	char indexString[_CHAR20+1];
	char dummy[_CHAR20+1];
	char colnames[(RECLAENGE*10)];
	char query[RECLAENGE];
	char command[RECLAENGE];
	char message[RECLAENGE];

	SYS_COLUMN *sys_column;
	SYS_INDEX *sys_index = NULL;

	int status=(int)MPOK;
	int anzcolumns, i, j, inum;
	int count;
	unsigned long dlen = 0;
	unsigned long alen = 0;

	(void)sprintf(query, __SYS_COLUMN, table);
	status=MPAPIdb_sqlquery(_SYS_COLUMN, &sqlmem.buffer, query,
	                         &anzcolumns, &sqlmem.datalen, &sqlmem.alloclen);
	sys_column = (SYS_COLUMN *)sqlmem.buffer;

	(void)sprintf(query, __SYS_INDEX, table);
	status=MPAPIdb_sqlquery(_SYS_INDEX, (char **)&sys_index, query,
	                         anzahl, &dlen, &alen);

	*ptr = calloc((size_t)*anzahl, sizeof(char *));

	for(i=0; i < *anzahl; i++)
		{
		(void)copyTextTo(indexString, sys_index[i].indexname, (int)_CHAR20);
		(void)copyTextTo(tableString, sys_index[i].tablename, (int)_CHAR20);
		
		for(j=0, *colnames = NULL; j < sys_index[i].numc; j++)
			{
			inum = (int)(sys_index[i].columns[j] - (int)1);
			(void)copyTextTo(dummy, sys_column[inum].colname, (int)_CHAR20);
			strcat(colnames, dummy);
			if (sys_index[i].coldirs[j] == _DESC)
				strcat(colnames, " DESC");
			if (j < (sys_index[i].numc - 1))
				strcat(colnames, ", ");
			}

		if (sys_index[i].unique == _UNIQUE && sys_index[i].cluster == _CLUSTER)
			(void)sprintf(command, _CREATE_UC_INDEX, indexString, tableString, colnames);
		else if(sys_index[i].unique == _UNIQUE)
			(void)sprintf(command, _CREATE_U_INDEX, indexString, tableString, colnames);
		else if(sys_index[i].cluster == _CLUSTER)
			(void)sprintf(command, _CREATE_C_INDEX, indexString, tableString, colnames);
		else
			(void)sprintf(command, _CREATE_INDEX, indexString, tableString, colnames);

		ptr[i] = calloc((size_t)(sizeof(command) + (size_t)1), sizeof(char));
		(void)sprintf(ptr[i], "%s", command);

		(void)sprintf(command, _DROP_INDEX, indexString, tableString);
		status=MPAPIdb_sqlcommand(command, &count);
		}

	MPfree((char *)sys_index);
	return(status);
}
