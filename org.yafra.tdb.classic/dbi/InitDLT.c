/*D***********************************************************
 * Modul:     DBI - database select                           
 *            initialisiert die globalen Strukturen auf UNDEF
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/InitDLT.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int InitDLT(void)
{
	extern MEMOBJ sqlmem;
	extern MEMOBJ globDLT_MEM;
	extern DLT_VIEW *globDLT_VIEW;
	extern int AnzglobDLT;
	extern int sprache;

	DLT_VIEW *tmp_ptr;
	char query[RECLAENGE];
	int loop, maximum, newindex;
	int status = (int)MPOK;

	/* init */
	AnzglobDLT = 0;

	/* Die DLT_VIEW lesen um eine bessere Performance zu erreichen */
	/***************************************************************/
	(void)sprintf(query, _SEL_ALL_DLT_VIEW, (int)sprache);
	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	status=MPAPIdb_sqlquery((int)_DLT_VIEW, &sqlmem.buffer, query,
	                         &AnzglobDLT, &sqlmem.datalen, &sqlmem.alloclen);
	(void)MPAPIdb_committrx();
	if (status == (int)MPOK && AnzglobDLT > (int)0)
		{
		tmp_ptr = (DLT_VIEW *)sqlmem.buffer;
		for (loop=0, maximum=(int)_UNDEF; loop < AnzglobDLT; loop++)
			maximum = (maximum > tmp_ptr[loop].dlt_id) ? maximum : tmp_ptr[loop].dlt_id;

		if (maximum != (int)_UNDEF)
			{
			globDLT_MEM.datalen = ((sizeof(DLT_VIEW)) * (maximum + 1));
			globDLT_MEM.buffer = MPalloc((void *)globDLT_MEM.buffer,
			      &globDLT_MEM.alloclen, DEFMEMCHUNK, globDLT_MEM.datalen,
			      sizeof(char));
			(void)memset((void *)globDLT_MEM.buffer, NULL, globDLT_MEM.alloclen);
			if (tmp_ptr != NULL && globDLT_MEM.buffer != NULL)
				{
				globDLT_VIEW = (DLT_VIEW *)globDLT_MEM.buffer;
				for (loop = (int)0; loop < AnzglobDLT; loop++)
					{
					newindex = tmp_ptr[loop].dlt_id;
					if (newindex == (int)_UNDEF)
						newindex = (int)0;
					(void)memcpy( (void *)&(globDLT_VIEW[newindex]), (void *)&tmp_ptr[loop], sizeof(DLT_VIEW) );
					}
				AnzglobDLT = maximum+1;
				}
			else
				AnzglobDLT = (int)0;
			}
		else
			AnzglobDLT = (int)0;
		}
	return(status);
}
