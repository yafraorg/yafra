/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Kursinformationen
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLWinfo.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

#define _SEL_LW_KURSE "SELECT * FROM TDBADMIN.LAND_WHR WHERE LAND_ID = %d \
	ORDER BY KURS_TYP, WHR_ID;"

int LWinfo(char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern WAEHRUNG whr;
	extern LAND land;
	extern LAND_WHR lw;
	extern char sqlquery[];

	LAND_WHR *lwptr;
	char whrbez[_BEZLEN];
	char tmp_buffer[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int anzahl;
	int i;

	ACTIONTYP = INFOTXT;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* get LAND */
	lw.land_id = MPAPIselectEntry((int)_LAND, to_buffers[MLW_LAND],
	             (char *)&land, sizeof(land), sizeof(land.land_id));
	(void)sprintf(buffer, "\nFolgende Kurse sind fuer das Land %s gueltig:\n\n",
	        to_buffers[MLW_LAND]);

	/* make loop over all WHR in LAND *****/
	(void)sprintf(sqlquery, _SEL_LW_KURSE, land.land_id);
	status = MPAPIdb_sqlquery((int)_LAND_WHR, &sqlmem.buffer, sqlquery,
                          &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	lwptr = (LAND_WHR *)sqlmem.buffer;
	if (status != (int)MPOK || anzahl == (int)0)
		{
/*!!! new msg */
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}
	for (i=0; i<anzahl; i++)
		{
		whr.whr_id = MPAPIselectOneId((int)_WAEHRUNG, lwptr[i].whr_id, (char *)&whr);
		(void)copyTextTo(whrbez, (char *)whr.krzl, (int)_CHAR10);
		(void)sprintf(tmp_buffer, "\n%5.5s :  %4.4f    %4.4f", whrbez,
		              lwptr[i].a_kurs, lwptr[i].v_kurs);
		(void)strcat(buffer, tmp_buffer);
		}

	return(status);
}
