/*D***********************************************************
 * Modul:     DBI - graphic modul
 *            update book info for graphic
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRrefresh.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int GRrefresh(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern DIENST_TRAEGER dlt;
	extern RESERVATION res;
	extern DIENSTLEISTUNG dtg;
	extern int sprache;
	extern char sqlquery[];
	extern char glob_dat_bch[];
	extern unsigned char bm_obj;
	
	DLG_PART dlg;
	DIENST_ANGEBOT dla;
	
	DLG_DLG *Pdl_tdl;
	RESERVATION *Pres;
	DLT_VIEW *Pdltv;

	char tmp_buffer[RECLAENGE];
	char dl_string[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char dlbez[_BEZLEN*3];

	int status = (int)MPOK;
	int xdtg, xdlg;
	int anzres, anzdlt, anzdlg, offset;
	int resindex, dltindex;
	int anzahl;
	int id;
	int found;
	int *tdlids;
	int tdlcnt;
	register int i, j;
	unsigned long dlen = 0;
	unsigned long alen = 0;
   struct tm DateTime;
	time_t dldate;

	/* set DL */
	switch(MENUNR)
		{
		case (unsigned char)_BUCHUNG:
			status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
			if (status != MPOK)
				{
				UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			(void)strcpy(dlbez, to_buffers[MBCH_DL]);
			if (*to_buffers[MBCH_DAT] != NULL)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				ReadDate(&DateTime, &dldate, to_buffers[MBME_DAT]);
				}
			else
				(void)time(&dldate);
			UtilSplitFreeMenubuffer(to_buffers);
			id = MPAPIselectEntry((int)_DIENSTLEISTUNG, dlbez, (char *)&dtg,
			                  sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
			if (id == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			break;

		case _RESERVATION:
			if (dtg.dlg_id < 1)
				{
				UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}

			/* read menu string and set it to RES */
			tdlids = NULL;
			tdlcnt = 0;
			status = BMRESreadprotocol(buffer, &res, &tdlids, &tdlcnt);
			if (status != (int)MPOK)
				{
				UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			if (res.a_zeit > 0)
				dldate = (time_t)res.a_zeit;
			else
				(void)time(&dldate);
			MPfree((void *)tdlids);
			break;

		default:
			UtilMsg((int)MPE_NOGRA, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
		}

	/* get all DLT to HOST_DLT entry in DLA */
	(void)sprintf(sqlquery, _SEL_DLTVIEW_HOST, (int)sprache, dlt.dlt_id);
	status=MPAPIdb_sqlquery((int)_DLT_VIEW, &sqlmem.buffer, sqlquery, &anzdlt,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	Pdltv = (DLT_VIEW *)sqlmem.buffer;
	if (status != (int)MPOK || anzdlt < 1)
		{
		UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (dtg.a_zeit > 0)
		dldate = (int)_UNDEF;

	/* get all RES on DL_PARTS */
	Pres = NULL;
	alen = dlen = 0;
	if (dldate == (time_t)_UNDEF)
		(void)sprintf(sqlquery, _SEL_RES_DL, dtg.dlg_id);
	else
		(void)sprintf(sqlquery, _SEL_RES_DL_DAT, dtg.dlg_id, (int)dldate, (int)dldate);
	status=MPAPIdb_sqlquery((int)_RESERVATION, (char **)&Pres,
									 sqlquery, &anzres, &dlen, &alen);
	if (status != (int)MPOK)
		{
		MPfree((void *)Pres);
		UtilMsg((int)MPE_NORES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* match DLT with RES */
	for (i=0; i<anzdlt; i++)
		{
		found = (int)_UNDEF;
		for (j=0; j<anzres; j++)
			{
			if (Pdltv[i].dlt_id == Pres[j].dlt_id)
				{
				found = 0;
				break;
				}
			}
		/*!!! we must count the num of DLN in DLT */
		if (found == (int)_UNDEF)
			comm.buffer[i] = (unsigned char)0;
		else
			comm.buffer[i] = (unsigned char)10;
		}

	comm.buffer[anzdlt] = (char)NULL;
	comm.datalen = anzdlt;
			
	MPfree((void *)Pres);
				
	return(status);
}
