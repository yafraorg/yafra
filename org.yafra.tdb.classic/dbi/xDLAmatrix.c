/*D***********************************************************
 * Modul:     DBI - matrix
 *            Dienstleistungstraeger
 *            prepare DLT/DL matrix list
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>
#ifdef ps_unix
#include <sys/time.h>
#endif

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLAmatrix.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define _MX_DLA_NUMFIELDS  1
#define _MX_DLA_XMAX       5
#define _MX_DLA_MAXDAYS		10

static int DLAmatrixshowdb(DIENST_ANGEBOT *, MEMOBJ *, int *, time_t);
static int DLAmatrixshowkapa(DIENST_ANGEBOT *, MEMOBJ *, int *, time_t);
static int DLAmatrixbinary(int, char *, DIENST_ANGEBOT *, MEMOBJ *, int *, time_t);
static int GetNextDays( time_t, time_t *, int);
static int GetFirstDLAchild(DIENST_ANGEBOT *);

/*************************************************************
 * function:  DLAmatrix
 * typ:       public
 * desc:      check if DLT is free for booking
 * input:     DL / DLG_PART / KAT / KONT
 *************************************************************/
int DLAmatrix(int len, char *buffer)
{
	extern MEMOBJ tdl_mem;
	extern unsigned char selectfromtemp;

	static DIENST_ANGEBOT dla;
	static int tdlcnt;
	static time_t tdldate;

	int status = (int)MPOK;
	struct tm DateTime;
	char *to_buffers[MAX_MENU_ITEMS];

	if (COMMTYP == (unsigned char)MATRIXSELECT &&
	    ACTIONTYP == (unsigned char)MATRIXSHOW)
		{
		status = DLAmatrixbinary(len, buffer, &dla, &tdl_mem, &tdlcnt, tdldate);
		}
	else
		{
		/********************/
		/* KATEGORIE matrix */
		/********************/

		MPfree(tdl_mem.buffer);
		tdl_mem.buffer = NULL;
		tdl_mem.datalen = 0;
		tdl_mem.alloclen = 0;
		tdlcnt = 0;

		status = UtilSplitMenubuffer(buffer, to_buffers, '~');
		if (status != MPOK)
			{
			UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		if (*to_buffers[MBME_DAT] != NULL)
			{
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			ReadDate(&DateTime, &tdldate, to_buffers[MBME_DAT]);
			}
		else
			(void)time(&tdldate);
		/* DIENST_ANGEBOT  Teil-Dienstleistungsangebot */	
		if (MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MBME_DLA], (char *)&dla,
		    sizeof(dla), sizeof(dla.dla_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		UtilSplitFreeMenubuffer(to_buffers);

		/* if DLA is a HOST-DLA then try to get it's first child */
		if (dla.h_dla_id == (int)_UNDEF)
			(void)GetFirstDLAchild(&dla);

		if (selectfromtemp)
			status = DLAmatrixshowkapa(&dla, &tdl_mem, &tdlcnt, tdldate);
		else
			status = DLAmatrixshowdb(&dla, &tdl_mem, &tdlcnt, tdldate);
		}

	return(status);
}


/**************************** STATIC PART *************************************/


/*************************************************************
 * function:  DLAmatrixshowkapa
 * typ:       static
 * desc:      read all capacity from KAPA table not from query
 * input:     HOSTDLA
 *************************************************************/
static int DLAmatrixshowkapa(DIENST_ANGEBOT *dla, MEMOBJ *tdlmem,
                             int *tdlcnt, time_t tdldate)
{
	extern int sprache;
	extern PREIS pre;
	extern unsigned char selectfromtemp;

	MEMOBJ kapavmem;
	MPV_KAPA *Pkapav;
	DLG_PART *Ptdl = NULL;
	PREIS cntrlpre;
	struct tm DateTime;
	time_t datearray[10 * _MX_DLA_MAXDAYS]; /*!!! make this dynamic */
	register int i;
	register int j;
	int k, l, m;
	int status = (int)MPOK;
	int katcnt;
	int kapacnt;
	int buflen;
	int katfree;
	int kapatdl_id;
	int tdlelements = 0;
	int oldkatid;
	char query[_QUERYLEN];
	char bez[_RECORDLEN];
	char text[_RECORDLEN];
	char preistext[_RECORDLEN];
	char cdate[_DATLEN];
	char ctime[_DATLEN];
	char tdl_string[_RECORDLEN];
	char tmp_buffer[_RECORDLEN];
	unsigned long dlen, alen;

	/* COL -> DIENSTLEISTUNG */
	/* ROW -> KATEGORIE */

	/* init */
	kapavmem.buffer = NULL;
	kapavmem.datalen = 0;
	kapavmem.alloclen = 0;
	katcnt = 0;

	/* get all TDL for a DLA */
	(void)sprintf(query, _SEL_TDL_DLA, dla->dla_id);
	status=MPAPIdb_sqlquery((int)_DLG_PART, (char **)&tdlmem->buffer, query,
	                         tdlcnt, &tdlmem->datalen, &tdlmem->alloclen);
	if (status != (int)MPOK || *tdlcnt < 1)
		{
		UtilMsg((int)MPE_NOTDL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);		
		}
	Ptdl = (DLG_PART *)tdlmem->buffer;
	tdlelements = *tdlcnt;

	/* dynamic TDL can only be read directly from db */
	if (Ptdl[0].res_f == (int)_RES_DYNAMIC)
		{
		status = DLAmatrixshowdb(dla, tdlmem, tdlcnt, tdldate);
		return(status);
		}

	/* KAT are read below with cell entries */
	/* katcnt will be calculated there */

	/* get all cell entries via KAPA */
	for (i=0, *tdl_string=(char)NULL; i < tdlelements; i++)
		{
		if (Ptdl[i].h_dl_id > 0)
			kapatdl_id = Ptdl[i].h_dl_id;
		else
			kapatdl_id = Ptdl[i].dl_id;
		sprintf(tmp_buffer, "%d,", kapatdl_id);
		strcat(tdl_string, tmp_buffer);
		}
	tdl_string[strlen( tdl_string )-1] = NULL;
	(void)sprintf(query, _SEL_KAPAV_TDLS, tdl_string, sprache, sprache);
	status=MPAPIdb_sqlquery((int)_MPV_KAPA, (char **)&kapavmem.buffer, query,
	                         &kapacnt, &kapavmem.datalen, &kapavmem.alloclen);
	Pkapav = (MPV_KAPA *)kapavmem.buffer;
	if (status != (int)MPOK || kapacnt < 1)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		MPfreeobj(&kapavmem);
		return((int)MPERROR);		
		}

	/* count all KAT */
	oldkatid = -2;
	for (i=0; i<kapacnt; i++)
		{
		if (oldkatid != Pkapav[i].kat_id)
			{
			oldkatid = Pkapav[i].kat_id;
			katcnt++;
			}
		}

	/* init date array */
	for (i=0; i<tdlelements; i++)
		datearray[i] = (time_t)_UNDEF;

	/* header of MATRIXSHOW protocol */
	sprintf(comm.buffer, "%d\t%d\t%d\t\0", _MX_DLA_NUMFIELDS, tdlelements, katcnt);

	/* write COLS titel */
	for (i=0; i<*tdlcnt; i++)
		{
		if (Ptdl[0].a_zeit < 1 && *tdlcnt == 1)
			{
			status = GetNextDays(tdldate, (time_t *)&datearray, (int)_MX_DLA_MAXDAYS);
			for (j=0; j<tdlelements; j++)
				{
				/* DATUM  Endezeit der Dienstleistung */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&datearray[j], bez);
				sprintf(text, "%s\t%d\t", bez, Ptdl[0].dl_id);
				strcat(comm.buffer, text);
				}
			}
		else
			{
			if (Ptdl[i].a_zeit > 0)
				{
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Ptdl[i].a_zeit, bez);
				}
			else
				{
				MPdate_makecurrent(cdate, ctime);
				sprintf(bez, "%s", cdate);
				}
			sprintf(text, "%s\t%d\t", bez, Ptdl[i].dl_id);
			strcat(comm.buffer, text);
			}
		}

	/* write ROW titel */
	/* count all KAT */
	oldkatid = -2;
	for (i=0; i<kapacnt; i++)
		{
		if (oldkatid != Pkapav[i].kat_id)
			{
			oldkatid = Pkapav[i].kat_id;
			(void)copyTextTo(bez, (char *)Pkapav[i].katbez, (int)_BEZLEN);
			(void)sprintf(text, "%s\t%d\t", bez, Pkapav[i].kat_id);
			(void)strcat(comm.buffer, text);
			}
		}

	/* write CELL entries (KAT and all TDLs with this KAT, again and again) */
	/* the KAPAV is sorted to KAT but not to TDLs time */
	oldkatid = -2;
	l = 0;
	m = 0;
	for (i=0; i<kapacnt; )
		{
		if (oldkatid != Pkapav[i].kat_id)
			{
			oldkatid = Pkapav[i].kat_id;
			m = (m + *tdlcnt);
			for (j=0; j<*tdlcnt; j++)
				{
				for (k = l; k < m; k++)
					{
					if (Ptdl[j].dl_id == Pkapav[k].tdl_id)
						{
						(void)sprintf(preistext, "%8.2f", Pkapav[k].vpr);
						(void)sprintf(text, "%s | %4d %4d\t", preistext, Pkapav[k].anz, Pkapav[k].busy);
						(void)strcat(comm.buffer, text);
						i++;
						break;
						}
					}
				}
			l = m;
			}
		}
	buflen = strlen(comm.buffer);
	comm.buffer[buflen-1] = NULL;

	COMMTYP = (unsigned char)MATRIXSELECT;
	ACTIONTYP = (unsigned char)MATRIXSHOW;

	MPfreeobj(&kapavmem);

	return(MPOK);
}

/*************************************************************
 * function:  DLAmatrixshowdb
 * typ:       static
 * desc:      read all capacity directly from the DB with queries
 * input:     HOST DLA
 *************************************************************/
static int DLAmatrixshowdb(DIENST_ANGEBOT *dla, MEMOBJ *tdlmem,
                           int *tdlcnt, time_t tdldate)
{
	extern int sprache;
	extern PREIS pre;

	PREIS cntrlpre;
	KAT_VIEW *kv = NULL;
	DLG_PART *tdl = NULL;
	struct tm DateTime;
	time_t datearray[10 * _MX_DLA_MAXDAYS]; /*!!! make this dynamic */
	register int i;
	register int j;
	int status = (int)MPOK;
	int katcnt;
	int buflen;
	int kattotal;
	int katfree;
	int katbusy;
	int tdlelements = 0;
	int tdlid;
	char query[_QUERYLEN];
	char bez[_RECORDLEN];
	char text[_RECORDLEN];
	char preistext[_RECORDLEN];
	char cdate[_DATLEN];
	char ctime[_DATLEN];
	unsigned long dlen, alen;

	/* COL -> DIENSTLEISTUNG */
	/* ROW -> KATEGORIE */

	/* init */
	kattotal = 0;
	katbusy = 0;
	katfree = 0;

	/* if not yet got, then get now the host DLA */
/**** out for testing without host dla
	if (dla->h_dla_id != (int)_UNDEF)
		(void)MPAPIselectOneId((int)_DIENST_ANGEBOT, dla->h_dla_id, (char *)dla);
*****/

	/* get all TDL for a DLA */
	alen = dlen = 0;
	(void)sprintf(query, _SEL_TDL_DLA, dla->dla_id);
	status=MPAPIdb_sqlquery((int)_DLG_PART, (char **)&tdlmem->buffer, query,
	                         tdlcnt, &tdlmem->datalen, &tdlmem->alloclen);
	tdl = (DLG_PART *)tdlmem->buffer;
	if (status == (int)MPOK && *tdlcnt > 0)
		{
		if (tdl[0].res_f == (int)_RES_DYNAMIC)
			tdlelements = (int)_MX_DLA_MAXDAYS;
		else
			{
			if (*tdlcnt > (int)_MX_DLA_XMAX)
				*tdlcnt = (int)_MX_DLA_XMAX;
			tdlelements = *tdlcnt;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOTDL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);		
		}

	/* get all KAT for DLA.DLT */
	alen = dlen = 0;
	(void)sprintf(query, _SEL_KATVIEW_DLT, dla->dlt_id, sprache);
	status=MPAPIdb_sqlquery((int)_KAT_VIEW, (char **)&kv, query, &katcnt,
		                      &dlen, &alen);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);		
		}
	if (katcnt < 1)
		{
		UtilMsg((int)MPE_NOKAT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);		
		}

	/* init date array */
	for (i=0; i<tdlelements; i++)
		datearray[i] = (time_t)_UNDEF;

	/* header of MATRIXSHOW protocol */
	sprintf(comm.buffer, "%d\t%d\t%d\t\0", _MX_DLA_NUMFIELDS, tdlelements, katcnt);

	/* write COLS titel */
	for (i=0; i<*tdlcnt; i++)
		{
		if (tdl[0].res_f == (int)_RES_DYNAMIC)
			{
			status = GetNextDays(tdldate, (time_t *)&datearray, (int)_MX_DLA_MAXDAYS);
			for (j=0; j<tdlelements; j++)
				{
				/* DATUM  Endezeit der Dienstleistung */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&datearray[j], bez);
				sprintf(text, "%s\t%d\t", bez, tdl[0].dl_id);
				strcat(comm.buffer, text);
				}
			}
		else
			{
			if (tdl[i].a_zeit > 0)
				{
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&tdl[i].a_zeit, bez);
				}
			else
				{
				MPdate_makecurrent(cdate, ctime);
				sprintf(bez, "%s", cdate);
				}
			sprintf(text, "%s\t%d\t", bez, tdl[i].dl_id);
			strcat(comm.buffer, text);
			}
		}

	/* write ROW titel */
	for (i=0; i<katcnt; i++)
		{
		(void)copyTextTo(bez, (char *)kv[i].bez, (int)_BEZLEN);
		sprintf(text, "%s\t%d\t", bez, kv[i].kat_id);
		strcat(comm.buffer, text);
		}

	/* write CELL titel */
	for (i=0; i<katcnt; i++)
		{
		kattotal = 0;
		for (j=0; j<tdlelements; j++)
			{
			if (dla->h_dla_id == (int)_UNDEF)
				cntrlpre.dla_id = dla->dla_id;
			else
				cntrlpre.dla_id = dla->h_dla_id;
			cntrlpre.dl_id = (int)_UNDEF;
			cntrlpre.rkr_id = (int)_UNDEF;
			cntrlpre.kar_id = (int)_UNDEF;
			status = MPAPIpre_getprice((int)_KATEGORIE, kv[i].kat_id,
			         &cntrlpre, &pre, preistext);
			if (*tdlcnt == 1)
				tdlid = tdl[0].dl_id;
			else
				tdlid = tdl[j].dl_id;
			status = KATfree(&kattotal, &katbusy, (int)_UNDEF, tdlid, kv[i].kat_id,
			                 (int)_UNDEF, kv[i].typ_id, datearray[j]);
			sprintf(text, "%s | %4d %4d\t", preistext, kattotal, katbusy);
			strcat(comm.buffer, text);
			}
		}
	buflen = strlen(comm.buffer);
	comm.buffer[buflen-1] = NULL;

	COMMTYP = (unsigned char)MATRIXSELECT;
	ACTIONTYP = (unsigned char)MATRIXSHOW;

	MPfree((void *)kv);

	return(MPOK);
}



/*************************************************************
 * function:  DLAmatrixbinary
 * typ:       static
 * desc:      show all DLTs from a KAT and a TDL
 * input:     KAT / TDL written in buffer and HOST DLA
 *************************************************************/
static int DLAmatrixbinary(int len, char *buffer, DIENST_ANGEBOT *dla,
                           MEMOBJ *tdlmem, int *tdlcnt, time_t tdldate)
{
	extern int sprache;
	extern KATEGORIE kat;

	MEMOBJ dltfree_mem;
	DLG_PART *Ptdl;
	DLG_PART tdl;
	DIENST_TRAEGER *dlt;

	struct tm DateTime;
	time_t datearray[10 * _MX_DLA_MAXDAYS]; /*!!! make this dynamic */
	register int i;
	register int j;
	int status = (int)MPOK;
	int id;
	char query[_QUERYLEN];
	char bez[_RECORDLEN];
	char text[_RECORDLEN];
	char tmpdate[_DATLEN];
	char tmptime[_DATLEN];
	char *ptr;
	unsigned long dlen, alen;

	int kat_id, tdl_id, typ_id;
	int dltcnt;
	int buflen;
	int tdlelements;
	int tmp_tdlid;
	int dltbchid;
	int dltkontid;
	int countdln;

	/* init */
	dltfree_mem.buffer = NULL;
	dltfree_mem.datalen = 0;
	dltfree_mem.alloclen = 0;
	dlt = NULL;
	Ptdl = NULL;

	/* COL -> DIENSTLEISTUNG */
	/* ROW -> DIENST_TRAEGER */

	/* read col and row id's from comm.buffer */
	ptr = buffer;
	tdl_id = MPgetSection(ptr, &len, (char)_MPSYMB_TAB);
	ptr = ptr + (len+_MPSYMBLEN);
	kat_id = MPgetSection(ptr, &len, (char)_MPSYMB_TAB);
	ptr = ptr + (len+_MPSYMBLEN);

	(void)MPAPIselectOneId((int)_KATEGORIE, kat_id, (char *)&kat);
	(void)MPAPIselectOneId((int)_DLG_PART, tdl_id, (char *)&tdl);
	if (kat.kat_id == (int)_UNDEF || tdl.dl_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOTDL, MSGTYP_ERROR, NULL);
		UtilMsg((int)MPE_NOKAT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);		
		}

	typ_id = kat.typ_id;
	Ptdl = (DLG_PART *)tdlmem->buffer;

	/* check tdlres_f, I support only detail on static and on dynamic DL's */
	if (tdl.res_f != (int)_RES_STATIC && tdl.res_f != (int)_RES_DYNAMIC)
		{
		*comm.buffer = NULL;
		comm.datalen = 0;
		return(MPOK);
		}

	/* get all DLT for KAT */
	alen = dlen = 0;
	(void)sprintf(query, _SEL_DLT_HOSTDLT_KAT, dla->dlt_id, kat.kat_id);
	status=MPAPIdb_sqlquery((int)_DIENST_TRAEGER, (char **)&dlt, query, &dltcnt,
		                      &dlen, &alen);
	if (status != (int)MPOK || dltcnt < 1)
		{
		UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);		
		}

	/* init date array */
	if (*tdlcnt == 1 && Ptdl[0].a_zeit < 1)
		tdlelements = (int)_MX_DLA_MAXDAYS;
	else
		{
		/* tdlelements = *tdlcnt; */
		tdlelements = 1;
		}
	for (i=0; i<tdlelements; i++)
		datearray[i] = (time_t)_UNDEF;

	sprintf(comm.buffer, "%d\t%d\t%d\t\0", _MX_DLA_NUMFIELDS, tdlelements, dltcnt);

	/* write COLS titel */
	if (tdl.res_f == (int)_RES_DYNAMIC)
		{
		status = GetNextDays(tdldate, (time_t *)&datearray, (int)_MX_DLA_MAXDAYS);
		for (i=0; i<tdlelements; i++)
			{
			/* DATUM  Endezeit der Dienstleistung */
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)0;
			DateTime.tm_min =(int)0;
			(void)WriteDate(&DateTime, (time_t *)&datearray[i], bez);
			(void)sprintf(text, "%s\t%d\t", bez, Ptdl[0].dl_id);
			(void)strcat(comm.buffer, text);
			}
		}
	else if (tdl.res_f == (int)_RES_STATIC)
		{
		if (tdl.a_zeit > 0)
			{
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)_UNDEF;
			DateTime.tm_min =(int)_UNDEF;
			(void)WriteDate(&DateTime, (time_t *)&tdl.a_zeit, bez);
			}
		else
			{
			MPdate_makecurrent(tmpdate, tmptime);
			(void)sprintf(bez, "%s", tmpdate);
			}
		(void)sprintf(text, "%s\t%d\t", bez, tdl.dl_id);
		(void)strcat(comm.buffer, text);
		}
	else /* impossible */
		{
		}

	/* write ROW titel */
	for (i=0; i<dltcnt; i++)
		{
		id = SelectBez((int)_DIENST_TRAEGER, sprache, dlt[i].bez_id, bez);
		(void)sprintf(text, "%s\t%d\t", bez, dlt[i].dlt_id);
		(void)strcat(comm.buffer, text);
		}

	/* write CELL titel */
	for (i=0; i<dltcnt; i++)
		{
		for (j=0; j<tdlelements; j++)
			{
			tmp_tdlid = (int)_UNDEF;
			if (tdl.res_f == (int)_RES_DYNAMIC)
				tmp_tdlid = Ptdl[0].dl_id;
			else if (tdl.res_f == (int)_RES_STATIC)
				tmp_tdlid = tdl.dl_id;
			else
				tmp_tdlid = tdl.dl_id;
			status = DLTfree(dlt[i].dlt_id, (int)_UNDEF, tmp_tdlid,
             (int)_UNDEF, datearray[j], &countdln, &dltbchid, &dltkontid);

			/*!!! check out here the right colors */
			if (countdln < 1)
				(void)strcpy(text, "\n\n\t");
			else
				{
				if (dltkontid != (int)_UNDEF)
					(void)sprintf(text, "%d | %d\n%s\n\t", dltbchid, dltkontid, "blue");
				else
					(void)sprintf(text, "%d\n%s\n\t", dltbchid, "red");
				}
			(void)strcat(comm.buffer, text);
			}
		}

	if (dltfree_mem.alloclen > 0)
		MPfree((void *)dltfree_mem.buffer);

	MPfree((void *)dlt);

	buflen = strlen(comm.buffer);
	comm.buffer[buflen] = NULL;

	COMMTYP = (unsigned char)MATRIXSELECT;
	ACTIONTYP = (unsigned char)MATRIXBINARY;

	return((int)MPOK);
}

#define ONE_DAY 86400
static int GetNextDays( time_t Starttime, time_t *Array, int Arraylen )
{
	struct tm *dat;
	struct tm tmptr;
	int status, i;

	status = (int)0;

	Array[0] = Starttime;
	for ( i = 1; i < Arraylen; i++ )
	{
		Array[i] = Starttime;
		Array[i] += (time_t)(i*ONE_DAY);

		dat = localtime(&Array[i]);

		tmptr.tm_sec = 0;
		tmptr.tm_min = 0;
		tmptr.tm_hour = 12;
		tmptr.tm_mday = dat->tm_mday;
		tmptr.tm_mon = (dat->tm_mon);
		tmptr.tm_year = dat->tm_year;
		tmptr.tm_wday = 0;
		tmptr.tm_yday = 0;
		tmptr.tm_isdst = dat->tm_isdst;

		Array[i] = mktime ( &tmptr );
	}
	
	return (status);
}

static int GetFirstDLAchild(DIENST_ANGEBOT *dla)
{
	unsigned long dlen, alen;
	int status;
	int dlacnt;
	DIENST_ANGEBOT *dlamem;
	char query[_QUERYLEN];

	status = (int)MPOK;
	alen = dlen = 0;
	dlamem = NULL;

	(void)sprintf(query, _SEL_DLA_ALLFROMHOST, dla->dla_id);
	status=MPAPIdb_sqlquery((int)_DIENST_ANGEBOT, (char **)&dlamem, query,
	       &dlacnt, &dlen, &alen);
	if (status == (int)MPOK && dlacnt > 0)
		{
		/* overwrite existing host dla entry with first found child ! */
		(void)memcpy((void *)dla, (void *)&dlamem[0], sizeof(DIENST_ANGEBOT));
		}

	MPfree((void *)dlamem);

	return(status);
}






















