/*D***********************************************************
 * program:      OUTkapaupdate
 * descripton:   update and check of the KAPA table
 *
 * arguments:    standard arguments
 *               -t  must   action typ           (AKTIONS_TYP  akttid)
 *               -A  opt    DLA id               (DIENST_ANGEBOT id)
 *               -f  specificflag = 1            alles loeschen und alles neu
 *               -f  specificflag = 2            nur die dlg's neuer als today()
 *                                                            
 * copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/kapaupdate/OUTkapaupdate.c,v 1.2 2008-11-02 19:55:53 mwn Exp $";

/* version */
#include "version.h"

/* define the entry point of this function for the main() */
int OUTkapaupdate(int, char *[]);
#define ACTIONFUNCTION (OUTkapaupdate)

/*--- MarcoPolo API includes */
#include <mpact.h>
  
/*--- MarcoPolo API standard main function ! */
#include "AKTmain.h"

/*--- global SQL selects include ----*/
#include <mpsqlsel.h>

/*--- define text ids for language independent text */
#define PRINTCOMMAND1 1

/* margins for AKTobjtxt */
#define LEFTMARGIN	"       "

static int ManageKAPA(int, DLG_PART *);
static int MakeKAPAentry(KAPA *);
static int GetANZdlt(int, int, int *);
static int GetBUSYdlt(int, int, int, int *);

/*F--------------------------------------------------------------------------
 *  Function:	OUTkapaupdate ()
 *					update check kapa table
 *  In:			-
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int OUTkapaupdate(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern STATUS_WERTE	sta;	/*--- get BM menu --------------------------*/
	extern int	dialogsprache;
	extern int	aktuellesprache;
	extern int	outputsprache;    
	extern int	globalflag;
	extern int	DebugFlag;
	extern STATUS_WERTE sta;

	DEVICE_PORT	*pDev;
	int		status, id, state, currentBch;
	int		i, j, anzahl, count;
	time_t	clock_value;
	char     format[_RECORDLEN];
	char     tmp_buffer[_RECORDLEN];
	AKT_DETAIL	adcntrl;
	DLG_PART *Ptdl;

	/*--- init ----------------------------------*/
	pDev = &devicePort;
	*language = (char)NULL;
	*format   = (char)NULL;
	currentBch = 0;

	/*--- action specific language ----------------*/
	aktuellesprache = dialogsprache;

	if (DebugFlag)
		(void)printf("\n\ndebug: Version %s\n\n", MAINVERSION);

	/*--- begin RU section ------------------------------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)           /*>>>> exit */

	/*--- mailing header --------------------------*/
	status = AKTmailHeader();
	if (status != (int)MPOK)
		EXIT_WITH_STATUS(status)                                /*>>>> exit */

	/*--- check if obligatory arguments are set ---*/
	if (akttid == (int)_UNDEF)
		{
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		EXIT_WITH_STATUS(MPERROR)                                 /*>>>> exit */
		}
	(void)MPAPIdb_committrx();


	if (dlaid > 0)
		{
		/* read all HOST-TDL from a DIENST_ANGEBOT */
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			return(status);
		(void)sprintf(tmp_buffer, _SEL_TDL_HOST_DLA, dlaid);
		status = MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer, tmp_buffer,
			                       &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		(void)MPAPIdb_committrx();
		if (status != MPOK || anzahl < 1)
			{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			(void)MPAPIdb_committrx();
			return(MPERROR);
			}

		status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			return(status);
		Ptdl = (DLG_PART *)sqlmem.buffer;
		for (i=0; i < anzahl && status == (int)MPOK; i++)
			{
			/* delete all KAPA entries for one TDL */
			(void)sprintf(tmp_buffer, "DELETE FROM TDBADMIN.KAPA WHERE TDL_ID = %d;", Ptdl[i].dl_id);
			status = MPAPIdb_sqlcommand(tmp_buffer, &count);
			}
		(void)MPAPIdb_committrx();
		if (DebugFlag)
			(void)fprintf(stderr, "debug: deleted KAPA entries for DLA %d%s", dlaid, _P_EOL_);
		}
	else
	{
		if ( specificflag == 1 )
		{
			/* delete all KAPA entries now and make new one's later */
			status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
			if (status != (int)MPOK)
				return(status);
			(void)sprintf(tmp_buffer, "DELETE FROM TDBADMIN.KAPA;");
			status = MPAPIdb_sqlcommand(tmp_buffer, &count);
			(void)MPAPIdb_committrx();
			if (DebugFlag)
				(void)fprintf(stderr, "debug: deleted all (%d) KAPA entries%s", count, _P_EOL_);
		}
		else
		{
			/* delete all KAPA entries now and make new one's later */
			if (DebugFlag)
				(void)fprintf(stderr, "debug: nothing deleted specific flag = 2 is set%s", count, _P_EOL_);
		}

		/* read all HOST-TDL (dlg_parts) */
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			return(status);
		(void)sprintf(tmp_buffer, _SEL_TDL_HOST);
		status = MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer, tmp_buffer,
										  &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		(void)MPAPIdb_committrx();
		if (status != MPOK || anzahl < 1)
		{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			(void)MPAPIdb_committrx();
			return(MPERROR);
		}

	}

	Ptdl = (DLG_PART *)sqlmem.buffer;
	for (i=0; i < anzahl && status == (int)MPOK; i++)
		{
		/* get DLT of TDL */
		(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		status = MPAPIselectDLT((int)_UNDEF, Ptdl[i].dl_id, (int)_UNDEF, &dlt);
		(void)MPAPIdb_committrx();

		/* make KAPA entries */
		if (DebugFlag)
			(void)fprintf(stderr, "debug: manage KAPA for host dlt: %d with tdl: %d%s",
			              dlt.dlt_id, Ptdl[i].dl_id, _P_EOL_);

		/* compare current system time with ttdl time */
		(void)time(&clock_value);

		if ( Ptdl[i].a_zeit >= clock_value || specificflag == 1 )
			{
			if ( specificflag == 2 )
				{
				/* delete all KAPA entries for one TDL */
				(void)sprintf(tmp_buffer, "DELETE FROM TDBADMIN.KAPA WHERE TDL_ID = %d;", Ptdl[i].dl_id);
				status = MPAPIdb_sqlcommand(tmp_buffer, &count);
				
				(void)MPAPIdb_committrx();
				}
			
			if (status == MPOK)
				{
				if (DebugFlag)
					(void)fprintf(stderr, "debug: deleted KAPA entries for TDL %d%s", Ptdl[i].dl_id, _P_EOL_);
				
				status = ManageKAPA(dlt.dlt_id, &Ptdl[i]);
				}
			/* make status clean: do not break the process */
			status = MPOK;
			}
		else
			{
			if (DebugFlag)
				(void)fprintf(stderr, "debug: nothing deleted for DLA %d%s", dlaid, _P_EOL_);
			}
		}
	fprintf(FPout, "%s%s%s KAPA UPDATED !! ", _P_EOL_, _P_EOL_, _P_EOL_);


	/*--- Device -------------------------------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)        /*>>>> exit */
	/*--- Get print command -------------------*/
	(void)sprintf(pDev->command, "lp");
	pDev->callnumber[0] = '\0';
	/*--- Device process ----------------------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Status Change: Device error ");
	(void)MPAPIdb_committrx();

exit:
	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

	return(status);	
}

static int ManageKAPA(int dlt_id, DLG_PART *tdl)
{
	MEMOBJ katmem;
	KATEGORIE *Pkat;
	KAPA kapa;
	PREIS cntrlpre;
	PREIS pre;
	int status = (int)MPOK;
	int anzahl = 0;
	int anzdlt = 0;
	int busydlt = 0;
	int i;
	char sqlquery[_QUERYLEN];
	char preistext[_RECORDLEN];

	/* init */
	katmem.buffer = NULL;
	katmem.alloclen = 0;
	katmem.datalen = 0;
	pre.vpr = (float)0;

	/* hole alle KATEGORIEN auf DLA.DLT_ID */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	(void)sprintf(sqlquery, _SEL_KAT_DLT, dlt_id);
	status=MPAPIdb_sqlquery((int)_KATEGORIE, &katmem.buffer, sqlquery, &anzahl,
		                      &katmem.datalen, &katmem.alloclen);
	(void)MPAPIdb_committrx();
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}
	if (anzahl < 1)
		{
		/* there's no KAT on this DLT - skip this entry */
		if (DebugFlag)
			(void)fprintf(stderr, "debug: skip this KAPA entry cause of no KAT: tdl %d dlt %d%s",
			              tdl->dl_id, dlt_id, _P_EOL_);
		return(MPOK);
		}

	/* pro KATEGORIE mache Eintrag in KAPA */
	Pkat = (KATEGORIE *)katmem.buffer;
	for (i=0; i < anzahl && status == (int)MPOK; i++)
		{
		anzdlt = 0;
		busydlt = 0;

		/* hole ANZ DLT pro KAT */
		status = GetANZdlt(Pkat[i].kat_id, dlt_id, &anzdlt);
		if (status != (int)MPOK)
			break;

		/* hole gebuchte ANZ DLT pro KAT */
		status = GetBUSYdlt(Pkat[i].kat_id, tdl->dl_id, tdl->res_f, &busydlt);
		if (status != (int)MPOK)
			break;

		/* get PREIS for the KATEGORIE */
		cntrlpre.kar_id = (int)_UNDEF;
		cntrlpre.rkr_id = (int)_UNDEF;
		cntrlpre.dla_id = tdl->dla_id;
		cntrlpre.dl_id = (int)_UNDEF;
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			return(status);
		status = MPAPIpre_getprice((int)_KATEGORIE, Pkat[i].kat_id,
		         &cntrlpre, &pre, preistext);
		(void)MPAPIdb_committrx();

		/* make new KAPA entry */
		kapa.kat_id = Pkat[i].kat_id;
		kapa.katbez_id = Pkat[i].bez_id;
		kapa.tdl_id = tdl->dl_id;
		kapa.tdlbez_id = tdl->bez_id;
		kapa.pre_id = pre.pre_id;
		kapa.anz = anzdlt;
		kapa.busy = busydlt;
		kapa.vpr = pre.vpr;
		kapa.von_dat = tdl->a_zeit;
		kapa.bis_dat = tdl->e_zeit;
		status = MakeKAPAentry(&kapa);
		if (status != (int)MPOK)
			break;

		if (DebugFlag)
			(void)fprintf(stderr, "debug: wrote KAPA: tdl %d, kat %d, %d, %d, %f%s",
			              tdl->dl_id, Pkat[i].kat_id, anzdlt, busydlt, pre.vpr, _P_EOL_);
		}

	MPfreeobj(&katmem);

	return(status);
}


static int GetANZdlt(int kat_id, int dlt_id, int *anzdlt)
{
	MEMOBJ intmem;
	int status = (int)MPOK;
	int anzahl = 0;
	char sqlquery[_QUERYLEN];
	int *intptr;

	/* init */
	intmem.buffer = NULL;
	intmem.alloclen = 0;
	intmem.datalen = 0;

	/* hole alle KATEGORIEN auf DLA.DLT_ID */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	(void)sprintf(sqlquery, _SEL_COUNTDLT, kat_id, dlt_id);
	status=MPAPIdb_sqlquery((int)_INTEGER, &intmem.buffer, sqlquery, &anzahl,
		                      &intmem.datalen, &intmem.alloclen);
	(void)MPAPIdb_committrx();
	if (status != MPOK || anzahl < 1)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}

	/* pro KATEGORIE mache Eintrag in KAPA */
	intptr = (int *)intmem.buffer;

	*anzdlt = *intptr;

	MPfreeobj(&intmem);

	return(status);
}

static int GetBUSYdlt(int kat_id, int tdl_id, int tdl_resf, int *busydlt)
{
	MEMOBJ intmem;
	MEMOBJ dlmem;
	MEMOBJ tdlmem;
	int status = (int)MPOK;
	int cntdlt = 0;
	int cntdl = 0;
	int cnttdl = 0;
	int i;
	char sqlquery[_QUERYLEN];
	char dl_string[_QUERYLEN];
	char tmp_buffer[_RECORDLEN];
	int tdlflag;
	int *ptr;
	int cntres;
	DLG_DLG *Pdl;
	DLG_PART *Ptdl;

	/* init */
	intmem.buffer = NULL;
	intmem.alloclen = 0;
	intmem.datalen = 0;
	dlmem.buffer = NULL;
	dlmem.alloclen = 0;
	dlmem.datalen = 0;
	tdlmem.buffer = NULL;
	tdlmem.alloclen = 0;
	tdlmem.datalen = 0;
	tdlflag = (int)_RES_STATIC;

	if (tdl_resf == (int)_RES_BOOLEAN)
		tdlflag = (int)_RES_BOOLEAN;

	/* hole alle KATEGORIEN auf DLA.DLT_ID */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);

	/* get all TDL's from a HOST TDL */
	(void)sprintf(sqlquery, _SEL_DLG_ALLFROMHOST, tdl_id);
	status=MPAPIdb_sqlquery((int)_DLG_PART, &tdlmem.buffer, sqlquery,
	                        &cnttdl, &tdlmem.datalen, &tdlmem.alloclen);
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		MPfreeobj(&dlmem);
		return(MPERROR);
		(void)MPAPIdb_committrx();
		}

	/* make IN (...) buffer for next select */
	Ptdl = (DLG_PART *)tdlmem.buffer;
	*dl_string=(NULL);
	if (cnttdl > 0)
		{
		for (i=0; i < cnttdl; i++)
			{
			(void)sprintf(tmp_buffer, "%d,", Ptdl[i].dl_id);
			(void)strcat(dl_string, tmp_buffer);
			}
		}
	else
		(void)sprintf(dl_string, "%d,", tdl_id);
	dl_string[strlen( dl_string )-1] = NULL;
	MPfreeobj(&tdlmem);

	(void)sprintf(sqlquery, _SEL_DD_TDL, dl_string);
	status=MPAPIdb_sqlquery((int)_DLG_DLG, &dlmem.buffer, sqlquery,
	                        &cntdl, &dlmem.datalen, &dlmem.alloclen);
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		MPfreeobj(&dlmem);
		(void)MPAPIdb_committrx();
		return(MPERROR);
		}

	/* if no dl's found return with zero busy indicator */
	if (cntdl < 1)
		{
		*busydlt = 0;
		MPfreeobj(&dlmem);
		(void)MPAPIdb_committrx();
		return(MPOK);
		}

	/* make IN (...) buffer for next select */
	Pdl = (DLG_DLG *)dlmem.buffer;
	for (i=0, *dl_string=(char)NULL; i < cntdl; i++)
		{
		sprintf(tmp_buffer, "%d,", Pdl[i].dlg_id);
		strcat(dl_string, tmp_buffer);
		}
	dl_string[strlen( dl_string )-1] = NULL;
	MPfreeobj(&dlmem);

	/* get count of busy DLT_ID's. intmem holds each DLT_ID with */
	/* the count of DLN's in it */
	if (tdlflag == (int)_RES_BOOLEAN)
		(void)sprintf(sqlquery, _SEL_COUNT_RES_BUSYDL, dl_string);
	else
		(void)sprintf(sqlquery, _SEL_COUNT_RES_BUSYDLT, kat_id, dl_string);
	status=MPAPIdb_sqlquery((int)_INTEGER, &intmem.buffer, sqlquery, &cntdlt,
		                      &intmem.datalen, &intmem.alloclen);
	(void)MPAPIdb_committrx();
	if (tdlflag == (int)_RES_BOOLEAN)
		{
		ptr = (int *)intmem.buffer;
		cntres = ptr[0];
		}
	else
		cntres = cntdlt;

	MPfreeobj(&intmem);
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}

	/* if count is less than one, set to zero and exit, else set busy count */
	if (cntdlt < 1)
		{
		*busydlt = 0;
		return(MPOK);
		}
	else
		{
		if (tdlflag == (int)_RES_BOOLEAN)
			*busydlt = cntres;
		else
			*busydlt = cntdlt;
		}

	return(status);
}


/* insert KAPA values */
static int MakeKAPAentry(KAPA *kapa)
{
	int status = (int)MPOK;

	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	status = MPAPIinsertEntry((int)_KAPA, (char *)kapa, (BEZEICHNUNG *)NULL);
	(void)MPAPIdb_committrx();

	return(status);
}
