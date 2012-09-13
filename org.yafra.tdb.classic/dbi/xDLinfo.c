/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Liste aller Teildienstleistung einer
 *            Dienstleistung
 *            -> Was macht der Reisende/DLN Uebersicht
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLinfo.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int DLinfo(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern unsigned char alphaordering;
	extern int DebugFlag;

	struct tm DateTime;

	ARR_DETAIL *dienstleistung;
	DIENSTLEISTUNG dtg;
	DLDLG_VIEW *dldlg;
	ARR_VIEW *arrv;

	char tmp_buffer[_RECORDLEN];
	char dlbez[_RECORDLEN];
	char *ptr;
	char *Poutput;
	char *to_buffers[MAX_MENU_ITEMS];
	char sqlordering[_QUERYLEN];

	int status=(int)MPOK;
	int i, anzahl, anzchar, id;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Check auf glob_bez_dtg ob vorhanden */
	if (*to_buffers[MDL_BEZ] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	/* read dl entry */
	(void)sprintf(dlbez, "%s %s %s", to_buffers[MDL_BEZ], TRENNER,
	       to_buffers[MDL_DAT]);
	UtilSplitFreeMenubuffer(to_buffers); /* free up menu strings */
	dtg.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, dlbez, (char *)&dtg,
		sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
	if (dtg.dlg_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	Poutput = comm.buffer;
	id = PCXsearch((int)_DIENSTLEISTUNG, dtg.bez_id, comm.buffer);
	if (id != (int)_UNDEF)
		{
		ACTIONTYP = (unsigned char)INFOTXTANDPCX;
		Poutput += strlen(comm.buffer);
		*Poutput = '\n';
		Poutput++;
		}
	else
		ACTIONTYP = (unsigned char)INFOTXT;

	/* Kopfzeile  mit DL */
	(void)SelectBez((int)_DIENSTLEISTUNG, sprache, 0, tmp_buffer);
	(void)sprintf(Poutput, "\n %s \n\n %s \n ", tmp_buffer, dlbez);
	anzchar = (int)strlen(dlbez);
	ptr = &Poutput[anzchar + (int)9 + (strlen(tmp_buffer))]; /* 9 f�r [\n \n ...] */
	for (i=0; i<anzchar; i++)
		*ptr++ = '=';
	*ptr++ = '\n';
	*ptr++ = '\n';
	*ptr = NULL;
	if (DebugFlag)
		{
		(void)sprintf(tmp_buffer, "(DL DEBUG-ID: %d) \n\n", dtg.dlg_id);
		(void)strcat(comm.buffer, tmp_buffer);
		}

	/* Aufbau der DL */
	(void)sprintf(sqlquery, _SEL_DLDLG_VIEW, dtg.dlg_id, sprache);
	status=MPAPIdb_sqlquery((int)_DLDLG_VIEW, &sqlmem.buffer, sqlquery,
	                &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	dldlg = (DLDLG_VIEW *)sqlmem.buffer;
	if (status == (int)MPOK)
		{
		if (anzahl > (int)0)
			{
			for (i=0; i<anzahl; i++)
				{
				if (DebugFlag)
					{
					(void)sprintf(tmp_buffer, "(DEBUG-ID: %d) ", dldlg[i].dl_id);
					(void)strcat(comm.buffer, tmp_buffer);
					}
				(void)sprintf(tmp_buffer, "%-4d : ", dldlg[i].ord);
				(void)strcat(Poutput, tmp_buffer);
				dldlg[i].bez[_BEZLEN] = (char)NULL;
				(void)strcat(Poutput, dldlg[i].bez);
				if (dldlg[i].a_zeit != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&dldlg[i].a_zeit, tmp_buffer);
					(void)strcat(Poutput, " | ");
					(void)strcat(Poutput, tmp_buffer);
					}
				if (dldlg[i].e_zeit != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&dldlg[i].e_zeit, tmp_buffer);
					(void)strcat(Poutput, " | ");
					(void)strcat(Poutput, tmp_buffer);
					}
				(void)strcat(Poutput, "\n");
				}
			}
		else
			{
			(void)strcat(Poutput, "keine Verknuepfungen mit Teildienstleistungen vorhanden\n");
			}
		}
	else
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	/* Referenzierung vom Arrangement - In welchem ARR kommnt DL vor ? */
	(void)strcat(Poutput, "\n\n");
	(void)strcat(Poutput, " Verknuepfungen zu Arrangements:\n\n");

	/* set ordering string for SQL query */
	if (alphaordering == (unsigned char)TRUE)
		(void)strcpy(sqlordering, _ORDER_ARR_DAT);
	else
		(void)strcpy(sqlordering, _ORDER_ARR_BEZ);

	(void)sprintf(sqlquery, _SEL_ARRVIEW_DL, dtg.dlg_id, sprache, sqlordering);
	status=MPAPIdb_sqlquery((int)_ARR_VIEW, &sqlmem.buffer, sqlquery,
	                &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	arrv = (ARR_VIEW *)sqlmem.buffer;
	if (status == (int)MPOK)
		{
		if (anzahl > (int)0)
			{
			for (i=0; i<anzahl; i++)
				{
				if (DebugFlag)
					{
					(void)sprintf(tmp_buffer, "(DEBUG-ID: %d) ", arrv[i].arr_id);
					(void)strcat(Poutput, tmp_buffer);
					}
				arrv[i].bez[_BEZLEN] = (char)NULL;
				(void)sprintf(tmp_buffer, "%s ", arrv[i].bez);
				(void)strcat(Poutput, tmp_buffer);
				if (arrv[i].a_dat != (int)_UNDEF)
					{
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_mon =(int)_UNDEF;
					DateTime.tm_year=(int)_UNDEF;
					(void)WriteDate(&DateTime, (time_t *)&arrv[i].a_dat, tmp_buffer);
					(void)strcat(Poutput, tmp_buffer);
					}
				(void)strcat(Poutput, "\n");
				}
			}
		else
			{
			(void)strcat(Poutput, "keine Verknuepfungen mit Arrangements vorhanden\n");
			}
		}
	else
		{
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	return(status);
}
