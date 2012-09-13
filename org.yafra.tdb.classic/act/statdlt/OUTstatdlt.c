/*D***********************************************************
 * program:      OUTstatdlt
 * description:  
 *
 * arguments:    standard arguments
 *               -s  opt    DIENSTLEISTUNG (cruise) Kreuzfahrt
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/statdlt/OUTstatdlt.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/* define the entry point of this function for the main() */
int OUTstatdlt(int, char *[]);
#define ACTIONFUNCTION OUTstatdlt

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standard main Funktion */

#include "version.h"

static int DLTstatistic(int, int, int, MEMOBJ *, int *, int *);
static void DLTcheckReservations(DLT_VIEW *, int, char *);
static void DLTnum_of_dln(int, int *);

/*P--- GLOBALS -------------------------------------------------------------*/

/*--- define text ids for language independend text */
#define PRINTCOMMAND    	1
#define PRINTCOMMAND2		2
#define PRINTCOMMAND3		3
#define PRINTCOMMAND4		4
#define AKTTXT_FMT_ZEILE_1 5
#define AKTTXT_FMT_ZEILE_2	6
#define AKTTXT_FMT_ZEILE_3	7
#define AKTTXT_FMT_ZEILE_4	8
#define AKTTXT_FMT_ZEILE_5	9

#define _SEL_KATVIEW "SELECT DISTINCT K.* \
	FROM TDBADMIN.KAT_VIEW K, TDBADMIN.DIENST_TRAEGER D WHERE D.HOST_ID = %d \
	AND K.S_ID = %d AND K.KAT_ID > 0 AND K.KAT_ID = D.KAT_ID ORDER BY K.BEZ;"
#define _SEL_KATVIEW_KAT "SELECT * FROM TDBADMIN.KAT_VIEW \
	WHERE KAT_ID = %d AND S_ID = %d;"

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatdlt
 *---------------------------------------------------------------------------
 */
int OUTstatdlt(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern STATUS_WERTE	sta;
	extern int dialogsprache;
	extern int outputsprache;
	extern int DebugFlag;
	extern char sqlquery[];
	extern MEMOBJ sqlmem;

	extern DIENST_TRAEGER dlt;
	extern KATEGORIE kat;
	extern TTYP_VIEW ttyp;

	int	status, id, state;
	int   i, anzahl, count;
	int	katcount, katdltcount;
	int	totkatcount, totkatdltcount;
	int	oldkat;
	int	dlt_id;
	struct tm DateTime;
	char	bezeichnung[_BEZLEN+5];
	char	tmpbuf[_RECORDLEN];
	char	tmp_buffer[RECLAENGE];
	char	tmp_buffer2[RECLAENGE];
	char	cdate[_DATELEN];		/* Current Date */
	char	ctime[_DATELEN];		/* Current Time */
	char  format[_RECORDLEN];
	char	typbez[_BEZLEN+1];
	char	dltbez[_BEZLEN+1];
	char	katbez[_BEZLEN+1];
	char	dlgbez[_RECORDLEN];
	AKT_DETAIL	adcntrl;
	DEVICE_PORT	*pDev;
	DIENST_TRAEGER *Pdlt;
	KAT_VIEW *Pkatv;
	MEMOBJ dltmem;
	DIENSTLEISTUNG MPdl;

	char	fmt_zeile_1[_CHAR80+1];
	char	fmt_zeile_2[_CHAR80+1];
	char	fmt_zeile_3[_CHAR80+1];
	char	fmt_zeile_4[_CHAR80+1];
	char	fmt_zeile_5[_CHAR80+1];

	/*--- init ------*/
	pDev = &devicePort;
	oldkat = (int)_UNDEF;
	katcount = 0;
	katdltcount = 0;
	totkatcount = 0;
	totkatdltcount = 0;
	dltmem.buffer = NULL;
	dltmem.alloclen = 0;
	dltmem.datalen = 0;

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	/*--- Get the Format string from DBMS -------------------*/
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)AKTTXT_FMT_ZEILE_1,  fmt_zeile_1,  NOMARGIN);   
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)AKTTXT_FMT_ZEILE_2,  fmt_zeile_2,  NOMARGIN);   
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)AKTTXT_FMT_ZEILE_3,  fmt_zeile_3,  NOMARGIN);
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)AKTTXT_FMT_ZEILE_4,  fmt_zeile_4,  NOMARGIN);   
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)AKTTXT_FMT_ZEILE_5,  fmt_zeile_5,  NOMARGIN);

	/*--- set right language ----------------------------------------------*/
	if (outputsprache == (int)_UNDEF)
		aktuellesprache = dialogsprache;
	else
		aktuellesprache = outputsprache;

	/*--- mailing header --------------------------------------------------*/
	status = AKTmailHeader() ;
	if (status != (int)MPOK)
		return(status);

	/*--- check if all needed arguments are set (-h) ----------------*/
	if (dltid == (int)_UNDEF)
		{
		AKTmsg(ACT_ERROR, MPA_INVALIDARGS, NULL);
		TEST_STATUS(MPERROR);
		}



	/******** B O D Y ****************/

	/* get host dlt */
	(void)MPAPIselectOneId((int)_DIENST_TRAEGER, (int)dltid, (char *)&dlt);
	(void)SelectBez((int)_DIENST_TRAEGER, sprache, dlt.bez_id, dltbez);

	if (dlid != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_min  = (int)_UNDEF;
		DateTime.tm_hour = (int)_UNDEF;
		DateTime.tm_mday = (int)_UNDEF;
		DateTime.tm_mon  = (int)_UNDEF;
		DateTime.tm_year = (int)_UNDEF;
		(void)MPAPIselectOneId((int)_DIENSTLEISTUNG, (int)dlid, (char *)&MPdl);
		(void)WriteDate(&DateTime, (time_t *)&MPdl.a_zeit, tmpbuf);
		(void)SelectBez((int)_DIENSTLEISTUNG, sprache, MPdl.bez_id, dlgbez);
		(void)strcat(dlgbez, " => ");
		(void)strcat(dlgbez, tmpbuf);
		}

	/* update mailing with dlt info */
	AKTmsgget(MPA_OBJECTDLT, format);
	(void)sprintf(mailstring, format, dltid, dltbez, " ");
	AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);

/*DEBUG*****************/
	if (DebugFlag)
		printf("%sdebug: START statistic of dlt %d - %s now !%s",
				 _P_EOL_, dltid, dltbez, _P_EOL_);
/*DEBUG*****************/

	/* get dltt of host dlt */
	id = MPAPIselectOneId((int)_TTYP_VIEW, (int)dlt.typ_id, (char *)&ttyp);
	if (id != (int)_UNDEF)
		(void)copyTextTo(typbez, ttyp.bez, (int)_BEZLEN);

	fprintf(FPout, "%s", _P_EOL_);
	fprintf(FPout, "%s", _P_EOL_);
	/* !!! dv (void)fprintf(FPout, "%s%sBenutzungsgrad fuer %s: %s%s%s",
		_P_EOL_, _P_EOL_, typbez, dltbez, _P_EOL_, _P_EOL_); */
	(void)fprintf(FPout, fmt_zeile_1, typbez, dltbez);
	fprintf(FPout, "%s", _P_EOL_);
	fprintf(FPout, "%s", _P_EOL_);
	if (dlid != (int)_UNDEF)
	{
		fprintf(FPout, "%s", _P_EOL_);
		fprintf(FPout, "%s", _P_EOL_);
		/* !!! dv (void)fprintf(FPout, "%s%sfuer Dienstleistung: %s%s%s",
			_P_EOL_, _P_EOL_, dlgbez, _P_EOL_, _P_EOL_); */
		(void)fprintf(FPout, fmt_zeile_2, dlgbez);
		fprintf(FPout, "%s", _P_EOL_);
		fprintf(FPout, "%s", _P_EOL_);
	}

	/*--- get all needed KATEGORIEs ---------------*/
	if (katid != (int)_UNDEF)
		(void)sprintf(sqlquery, _SEL_KATVIEW_KAT, katid, aktuellesprache);
	else
		(void)sprintf(sqlquery, _SEL_KATVIEW, dltid, aktuellesprache);
	status = MPAPIdb_sqlquery((int)_KAT_VIEW, (char **)&sqlmem.buffer,
	                sqlquery, &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != MPOK || anzahl < 1)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}
	Pkatv = (KAT_VIEW *)sqlmem.buffer;
	for (i=0;i<anzahl;i++)
	{
		/* write header line */
		(void)copyTextTo(katbez, Pkatv[i].bez, (int)_BEZLEN);
		(void)fprintf(FPout, "%s%s%s:%s%s",
						  _P_EOL_, _P_EOL_, katbez, _P_EOL_, _P_EOL_);
		katcount = 0;
		katdltcount = 0;
		
		/* write detail kategorie */
		status = DLTstatistic(Pkatv[i].kat_id, dltid, dlid, &dltmem,
                            &katcount, &katdltcount);
		
		/* write total line */
		totkatcount += katcount;
		totkatdltcount += katdltcount;
		if (katcount != 0)
		{
			fprintf(FPout, "%s", _P_EOL_);
			/* fprintf(FPout, "%sTOTAL Einheiten in dieser KATEGORIE: %d (%d)",
				_P_EOL_, katcount, katdltcount); */
			fprintf(FPout, fmt_zeile_3, katcount, katdltcount);
			fprintf(FPout, "%s", _P_EOL_);
		}
		
		if (anzahl != (i+1))
			fprintf(FPout, "%s", _P_EOL_);
		else
		{
			fprintf(FPout, "%s", _P_EOL_);
			fprintf(FPout, "%s", _P_EOL_);
			/* fprintf(FPout, "%s%sTOTAL Einheiten: %d (%d) %s",
				_P_EOL_, _P_EOL_, totkatcount, totkatdltcount, _P_EOL_); */
			fprintf(FPout, fmt_zeile_4, totkatcount, totkatdltcount);
			fprintf(FPout, "%s", _P_EOL_);
			fprintf(FPout, "%s", _P_EOL_);
		}
	}

	MPfree(dltmem.buffer);

	/*--- Device start output ---------------------------------------------*/
	/*--- Device --------------------------------*/
	pDev->callnumber[0] = '\0';
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)PRINTCOMMAND, format, NOMARGIN);
	(void)sprintf(pDev->command, "%s", format);
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)PRINTCOMMAND2, format, NOMARGIN);
	(void)sprintf(pDev->command2, "%s", format);
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)PRINTCOMMAND3, format, NOMARGIN);
	(void)sprintf(pDev->command3, "%s", format);
	(void)AKTobjtxt( (int)_STATDLT_TYP, (int)PRINTCOMMAND4, format, NOMARGIN);
	(void)sprintf(pDev->command4, "%s", format);

	/*--- Device process ------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");

	MPAPIdb_committrx();

/*DEBUG*****************/
	if (DebugFlag)
		printf("%s%sdebug: EXIT with status: %d, mailingadr: %s%s%s",
				 _P_EOL_, _P_EOL_, status, userid, _P_EOL_, _P_EOL_);
/*DEBUG*****************/

	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

exit:
	return(status);
}




#define _SEL_DLT_HOST_KAT "SELECT DLT.* FROM TDBADMIN.DLT_VIEW DLT  \
	WHERE DLT.HOST_ID = %d AND DLT.KAT_ID = %d AND DLT.S_ID = %d ORDER BY DLT.BEZ;"
/*************************************************************
 * function:  DLTstatistic
 * typ:       private local
 * desc:      
 * input:     KAT_VIEW object and DLG_PARTS id
 * output:    all DLTs
 *************************************************************/
static int DLTstatistic(int Akatid, int Ahostid, int Adlid, MEMOBJ *dltmem,
                        int *Akatcnt, int *Akatdltcnt)
{
	extern char sqlquery[];
	extern TTYP_VIEW ttyp;
	extern int aktuellesprache;

	DLT_VIEW *Pdltv;
	int status = (int)MPOK;
	int i, id;
	int anzahl, count;
	int katcnt = 0;
	int kattotcnt = 0;
	char usedbez[_RECORDLEN];
	char typbez[_BEZLEN+1];
	char dltbez[_BEZLEN+1];

	/*--- get all needed DLTs ---------------*/
	(void)sprintf(sqlquery, _SEL_DLT_HOST_KAT, Ahostid, Akatid, aktuellesprache);
	status = MPAPIdb_sqlquery((int)_DLT_VIEW, (char **)&dltmem->buffer,
	                sqlquery, &anzahl, &dltmem->datalen, &dltmem->alloclen);
	if (status != MPOK || anzahl < 1)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}
	Pdltv = (DLT_VIEW *)dltmem->buffer;
	for (i=0;i<anzahl;i++)
		{
		id = MPAPIselectOneId((int)_TTYP_VIEW, (int)Pdltv[i].typ_id, (char *)&ttyp);
		(void)copyTextTo(typbez, ttyp.bez, (int)_BEZLEN);
		(void)copyTextTo(dltbez, Pdltv[i].bez, (int)_BEZLEN);
		DLTnum_of_dln(Pdltv[i].dlt_id, &count);
		DLTcheckReservations(&Pdltv[i], Adlid, usedbez);
		(void)fprintf(FPout, "* %s: %s  ->  %3d  | %s%s",
		              typbez, dltbez, count, usedbez, _P_EOL_);
		katcnt++;
		kattotcnt = kattotcnt + count;
		}
	*Akatcnt = katcnt;
	*Akatdltcnt = kattotcnt;

	return(status);
}





/*************************************************************
 * function:  DLTnum_of_dln
 * typ:       public
 * desc:      get number of space for dln's on a dlt and
 *            their direct sub-dlt's
 * input:     dlt-id
 * output:    count of dln's 
 *************************************************************/
static void DLTnum_of_dln(int Adltid, int *countofplaces)
{
	extern DIENST_TRAEGER dlt;

	int count, id;

	id = MPAPIselectOneId((int)_DIENST_TRAEGER, Adltid, (char *)&dlt);

	count = MPAPIid_count((int)_DIENST_TRAEGER, (int)_DIENST_TRAEGER,
	                (char *)&dlt);
	if (count < 1)
		count = 1;

	*countofplaces = count;

	return;
}


#define _SEL_RES_DLT_TDL "SELECT RES.* \
	FROM TDBADMIN.RESERVATION RES \
	WHERE RES.DLG_ID = %d AND RES.DLT_ID = %d \
	ORDER BY RES.BID, RES.PERS_ID;"

/*************************************************************
 * function:  DLTcheckReservations
 * typ:       local privat
 * desc:      get number of space for dln's on a dlt and
 *            their direct sub-dlt's
 * input:     dlt-id
 * output:    count of dln's 
 *************************************************************/
static void DLTcheckReservations(DLT_VIEW *Adltv, int Adlid, char *Abez)
{
	char bidstring[_RECORDLEN];
	char querystring[_QUERYLEN];
	int anzahl, i, status = MPOK;
	int oldbid;
	MEMOBJ resmem;
	RESERVATION *Pres;

	resmem.buffer = NULL;
	resmem.datalen = 0;
	resmem.alloclen = 0;
	strcpy(Abez, " ");
	oldbid = -2;
	bidstring[0] = NULL;

	if (Adlid == (int)_UNDEF)
		return;
	else
		{
		(void)sprintf(querystring, _SEL_RES_DLT_TDL, Adlid, Adltv->dlt_id);
		status = MPAPIdb_sqlquery((int)_RESERVATION, (char **)&resmem.buffer,
		                querystring, &anzahl, &resmem.datalen, &resmem.alloclen);
		if (status != MPOK || anzahl < 0)
			{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			MPfree(resmem.buffer);
			return;
			}

		if (anzahl == 0)
			strcpy(Abez, "frei"); /*!!! hardcoded msg */
		else
			{
			Pres = (RESERVATION *)resmem.buffer;
			for (i=0;i<anzahl;i++)
				{
				if (Pres[i].bid != oldbid)
					{
					sprintf(bidstring, "%d ", Pres[i].bid);
					oldbid = Pres[i].bid;
					}
				}
			/*!!! hardcoded msg */
			(void)sprintf(Abez, "besetzt durch Buchung(en) %s", bidstring);
			}
		}
	MPfree(resmem.buffer);

	return;
}
