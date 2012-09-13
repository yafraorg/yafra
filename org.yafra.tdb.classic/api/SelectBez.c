/*D***********************************************************
 * Modul:     DBI - database select                           
 *            select a BEZEICHNUNG.BEZ from an object
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlbez.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectBez.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int SelectBez(int table , int spr, int bez_id , char *bezeichnung )
{
	extern MEMOBJ apimem;

	BEZEICHNUNG *bez_ptr;
	char query[_QUERYLEN];
	char *ptr;
	int anzahl, id;
	int status=(int)MPOK;

	(void)sprintf( query, _SELECT_BEZ, bez_id, spr, table );
	status = MPAPIdb_sqlquery( (int)_BEZEICHNUNG, &apimem.buffer, query,
	                           &anzahl, &apimem.datalen, &apimem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( anzahl == (int)1 )
			{
			bez_ptr = (BEZEICHNUNG *)apimem.buffer;
			(void)copyTextTo(bezeichnung, bez_ptr->bez, (int)_BEZLEN);
			id = bez_ptr->bez_id;
			}
		else
			id = (int)_UNDEF;
		}
	else
		id = (int)_UNDEF;

	return(id);
}
