/*D***********************************************************
 * Modul:     DBI - database info                           
 *            show only PCX images if possible
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKATinfo.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int KATinfo(int len, char *buffer )
{
	extern int sprache;
	extern KATEGORIE kat;

	int id;

	if (kat.kat_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	id = PCXsearch((int)_KATEGORIE, kat.bez_id, comm.buffer);
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	ACTIONTYP = (unsigned char)INFOPCX;

	return((int)MPOK);
}
