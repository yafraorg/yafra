/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Ortinformationen
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xORTinfo.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int ORTinfo(char *buffer )
{
	extern int sprache;
	extern MEMOBJ sqlmem;
	extern ORT ort;
	extern char sqlquery[];

	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[RECLAENGE];
	char tmp_bez[_RECORDLEN];
	int status=(int)MPOK;
	int i, id, anzahl, anzchar, last_id=(int)_UNDEF;

	/* init */
	ort.ort_id = (int)_UNDEF;
	ACTIONTYP = INFOTXT;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		ort.ort_id = (int)_UNDEF;
		return((int)MPERROR);
		}
	(void)copyTextTo(tmp_bez, to_buffers[MORT_BEZ], _BEZLEN);
	UtilSplitFreeMenubuffer(to_buffers);

	/* get ORT object */
	if (MPAPIselectEntry((int)_ORT, tmp_bez, (char *)&ort,
	    sizeof(ort), sizeof(ort.ort_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	/* now search for graphics */
	id = PCXsearch((int)_ORT, ort.bez_id, comm.buffer);
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}
	ACTIONTYP = (unsigned char)INFOPCX;

	return(MPOK);
}
