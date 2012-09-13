/*D***********************************************************
 * Modul:     DBI - PCX utility
 *            search database if there is a pixel image for
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPCXsearch.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define _SEARCH_PCXIMAGE "SELECT * FROM TDBADMIN.PCX_FILES \
	WHERE TYP = %d AND TYPCODE = %d;"

/*F***********************************************************
 * Function:  PCXsearch
 * Returns:   _UNDEF if no image found or error
 *            id of pcx image if one or more are found
 **************************************************************/
int PCXsearch(int typ, int bezid, char *filename)
{
	extern int sprache;
	extern MEMOBJ sqlmem;

	int status=(int)MPOK;
	int anzahl;
	char query[_RECORDLEN];
	PCX_FILES *Ppcx;

	(void)sprintf(query, _SEARCH_PCXIMAGE, typ, bezid);
	status = MPAPIdb_sqlquery((int)_PCX_FILES, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK || anzahl < 1)
		return((int)_UNDEF);

	Ppcx = (PCX_FILES *)sqlmem.buffer;
	(void)copyTextTo(filename, Ppcx[0].filename, _FILELEN);

	return((int)Ppcx[0].pcx_id);
}
