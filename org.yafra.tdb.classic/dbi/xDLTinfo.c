/*D***********************************************************
 * Modul:     DBI - database info                           
 *            show only PCX images if possible
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int DLTinfo(int len, char *buffer )
{
	extern int sprache;
	extern DIENST_TRAEGER dlt;

	int id;

	if (dlt.dlt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	id = PCXsearch((int)_DIENST_TRAEGER, dlt.bez_id, comm.buffer);
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	ACTIONTYP = (unsigned char)INFOPCX;

	return((int)MPOK);
}
