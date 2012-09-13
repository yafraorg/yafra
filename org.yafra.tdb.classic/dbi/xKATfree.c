/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Kategorie
 *            prepare free KAT select list
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKATfree.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";
static int DayRange(time_t, time_t *, time_t *);
static int old_katid = 0;
static int anzdlt;
static char dlt_string[10*_RECORDLEN];

/*************************************************************
 * function:  KATfree
 * typ:       public
 * desc:      get free DLT's in a KAT from DB
 * input:     DL / DLG_PART / KAT / KONT / opt. count of free DLT
 * output:    number of free DLT in KAT
 * return:    state of function
 *************************************************************/
int KATfree(int *cnttotal, int *cntbusy,
            int dl_id, int tdl_id, int kat_id,
            int kont_id, int typ_id, time_t dldate)
{
	extern MEMOBJ sqlmem;
	extern int sprache;

	MEMOBJ intmem;
	DLG_DLG *Pdd;
	DIENSTLEISTUNG dl;
	DLG_PART tdl;
	DIENST_ANGEBOT dla;

	int status = (int)MPOK;
	int anzdlg, anzres, anztdl;
	int id;
	int *intptr;
	register int i, j;
	time_t vondat, bisdat;

	char query[_QUERYLEN];
	char tmp_buffer[_RECORDLEN];
	char dl_string[_RECORDLEN];

	/* if cnttotal is > 0 then we don't need to count the DLT's !! */
	/* I made this for faster processing. But attention: init to zero */
	/* must be done before calling this function ! */

	/* init */
	*cntbusy = 0;
	intmem.buffer = NULL;
	intmem.datalen = 0;
	intmem.alloclen = 0;

	/* get DLG_PARTS for searching in RES */
	if (tdl_id == (int)_UNDEF)
		{
		status = MPAPIselectTDL(dl_id, &tdl);
		/* Ist eine g�ltige aktive Dienstleistung vorhanden */
		sprintf(dl_string, "%d", dl_id);
		}
	else
		{
		id = MPAPIselectOneId((int)_DLG_PART, tdl_id, (char *)&tdl);
		if (id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		(void)sprintf(query, _SEL_TDLDLG, tdl_id);
		status=MPAPIdb_sqlquery((int)_DLG_DLG, &sqlmem.buffer, query,
		                  &anzdlg, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		Pdd = (DLG_DLG *)sqlmem.buffer;
		for (i=0, *dl_string=(char)NULL; i < anzdlg; i++)
			{
			sprintf(tmp_buffer, "%d,", Pdd[i].dlg_id);
			strcat(dl_string, tmp_buffer);
			}
		dl_string[strlen( dl_string )-1] = NULL;
		}

	/* get current date if nec. */
	if (tdl.res_f == (int)_RES_DYNAMIC)
		{
		if (dldate == (time_t)_UNDEF)
			(void)time(&dldate);
		}
	else
		dldate = (time_t)_UNDEF;

	/* Das Angebot der ersten Teildienstleistung aus der datenbank lesen */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, tdl.dla_id, (char *)&dla);
	if (id == (int)_UNDEF)
		{
		/*	Kein Dienstleistungsangebot ist g�ltig */
		UtilMsg( (int)MPE_NODLA, MSGTYP_ERROR, NULL );
		status = (int)MPERROR;
		return( status );
		}
	else
		{
		if ( dla.dlt_id == (int)_UNDEF)
			{
			UtilMsg( (int)MPE_NODLTINDLA, MSGTYP_ERROR, NULL );
			return((int)MPERROR);
			}
		}

	/* set total count of DLT's on this KAT */
	if (*cnttotal == 0)
		{
		(void)sprintf(query, _SEL_COUNTDLT, kat_id, dla.dlt_id);
		status = MPAPIdb_sqlquery((int)_INTEGER, &intmem.buffer, query,
		                           &anzdlt, &intmem.datalen, &intmem.alloclen);
		if (status == MPOK && anzdlt > 0)
			{
			intptr = (int *)intmem.buffer;
			*cnttotal = *intptr;
			}
		}

	/* get all RES on these DLT's */
	if (tdl.res_f == (int)_RES_DYNAMIC)
		(void)sprintf(query, _SEL_COUNT_RES_BUSYDLT_DAT, kat_id, dl_string,
		              (int)dldate, (int)dldate);
	else if (tdl.res_f == (int)_RES_BOOLEAN)
		(void)sprintf(query, _SEL_COUNT_RES_BUSYDL, dl_string);
	else
		(void)sprintf(query, _SEL_COUNT_RES_BUSYDLT, kat_id, dl_string);
	status = MPAPIdb_sqlquery((int)_INTEGER, &intmem.buffer, query,
	                           &anzres, &intmem.datalen, &intmem.alloclen);
	if (status == (int)MPOK && anzres > 0)
		{
		if (tdl.res_f == (int)_RES_BOOLEAN)
			{
			intptr = (int *)intmem.buffer;
			*cntbusy = *intptr;
			}
		else
			*cntbusy = anzres;
		}

	MPfreeobj(&intmem);
	return(status);
}

static int DayRange(time_t Starttime, time_t *Von, time_t *Bis)
{
	struct tm *dat;
	struct tm tmptr;
	time_t ti;
	int status, i;

	status = (int)0;

	dat = localtime(&Starttime);

	tmptr.tm_sec = 0;
	tmptr.tm_min = 0;
	tmptr.tm_hour = 0;
	tmptr.tm_mday = dat->tm_mday;
	tmptr.tm_mon = (dat->tm_mon);
	tmptr.tm_year = dat->tm_year;
	tmptr.tm_wday = 0;
	tmptr.tm_yday = 0;
	tmptr.tm_isdst = dat->tm_isdst;

	*Von = mktime ( &tmptr );

	tmptr.tm_sec = 0;
	tmptr.tm_min = 0;
	tmptr.tm_hour = 0;
	tmptr.tm_mday = dat->tm_mday+1;
	tmptr.tm_mon = (dat->tm_mon);
	tmptr.tm_year = dat->tm_year;
	tmptr.tm_wday = 0;
	tmptr.tm_yday = 0;
	tmptr.tm_isdst = dat->tm_isdst;

	*Bis = mktime ( &tmptr );

	return (status);
}
