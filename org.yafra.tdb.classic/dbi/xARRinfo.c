/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Arrangement Info
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xARRinfo.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

#define _SEL_ARRDL_VIEW "SELECT * FROM TDBADMIN.ARR_DL_VIEW \
	WHERE ARR_ID = %d AND S_ID = %d \
	ORDER BY TEIL, PRIO;"

int ARRinfo(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern int DebugFlag;

	struct tm DateTime;
	ARRANGEMENT arr;
	ARRDL_VIEW *arrdl;
	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[4*_RECORDLEN];
	char arrbez[_RECORDLEN];
	char *ptr;
	int status=(int)MPOK;
	int i, anzahl, anzchar;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* get ARR bez */
	if (*to_buffers[MARR_BEZ] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}
	(void)sprintf(arrbez, "%s %s %s", to_buffers[MARR_BEZ], TRENNER,
	       to_buffers[MARR_DAT]);
	UtilSplitFreeMenubuffer(to_buffers); /* free up menu strings */
	arr.arr_id = MPAPIselectEntry((int)_ARRANGEMENT, arrbez, (char *)&arr,
	            sizeof(ARRANGEMENT), sizeof(arr.arr_id));
	if (arr.arr_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOARR, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Kopfzeile mit ARR */
	(void)SelectBez((int)_ARRANGEMENT, sprache, 0, tmp_buffer);
	(void)sprintf(comm.buffer, "\n %s \n\n %s \n ", tmp_buffer, arrbez);
	anzchar = (int)strlen(arrbez);
	ptr = &comm.buffer[anzchar + (int)9 + (strlen(tmp_buffer))]; /* 9 f�r [\n \n ...] */
	for (i=0; i<anzchar; i++)
		*ptr++ = '=';
	*ptr++ = '\n';
	*ptr++ = '\n';
	*ptr = NULL;
	if (DebugFlag)
		{
		(void)sprintf(tmp_buffer, "(ARR DEBUG-ID: %d) \n\n", arr.arr_id);
		(void)strcat(comm.buffer, tmp_buffer);
		}

	/* Zusammensetzung ARR - DL */
	(void)sprintf(sqlquery, _SEL_ARRDL_VIEW, arr.arr_id, sprache);
	status = MPAPIdb_sqlquery((int)_ARRDL_VIEW, &sqlmem.buffer, sqlquery,
	                &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	arrdl = (ARRDL_VIEW *)sqlmem.buffer;
	if (anzahl > (int)0 && status == (int)MPOK)
		{
		for (i=0; i<anzahl; i++)
			{
			if (DebugFlag)
				{
				(void)sprintf(tmp_buffer, "(DEBUG-ID: %d) ", arrdl[i].dlg_id);
				(void)strcat(comm.buffer, tmp_buffer);
				}
			(void)sprintf(tmp_buffer, "%-4d", arrdl[i].teil);
			(void)strcat(comm.buffer, tmp_buffer);
			(void)sprintf(tmp_buffer, "%-4d : ", arrdl[i].prio);
			(void)strcat(comm.buffer, tmp_buffer);
			arrdl[i].bez[_BEZLEN] = (char)NULL;
			(void)strcat(comm.buffer, arrdl[i].bez);
			if (arrdl[i].a_zeit != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&arrdl[i].a_zeit, tmp_buffer);
				(void)strcat(comm.buffer, TRENNER);
				(void)strcat(comm.buffer, tmp_buffer);
				}
			(void)strcat(comm.buffer, "\n");
			}
		}
	else
		UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);

	/* only text info */
	ACTIONTYP = INFOTXT;

	return(status);
}
