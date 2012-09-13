/*D***********************************************************
 * program:      OUTkapaupdate
 * descripton:   update and check of the KAPA table
 *
 * arguments:    standard arguments
 *               -t  must   action typ           (AKTIONS_TYP  akttid)
 *               -a  opt    arrangement id       (ARRANGEMENT  arrid)
 *                                                            
 * copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/arrkom/OUTarrkom.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/* version */
#include "version.h"

/* define the entry point of this function for the main() */
int OUTarrkom(int, char *[]);
#define ACTIONFUNCTION (OUTarrkom)

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

MEMOBJ kommem;

static int ManageARRKOM(int);

/*F--------------------------------------------------------------------------
 *  Function:	OUTarrkom()
 *					update arrangement kommission join table
 *  In:			-
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int OUTarrkom(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern STATUS_WERTE	sta;	/*--- get BM menu --------------------------*/
	extern int	dialogsprache;
	extern int	aktuellesprache;
	extern int	outputsprache;    
	extern int	globalflag;
	extern STATUS_WERTE sta;

	DEVICE_PORT	*pDev;
	int		status, id, state, currentBch;
	int		i, j, anzahl;
	char     format[_RECORDLEN];
	char     tmp_buffer[_RECORDLEN];
	AKT_DETAIL	adcntrl;
	DLG_PART *Ptdl;
	ARRANGEMENT *Parr;

	/*--- init ----------------------------------*/
	pDev = &devicePort;
	*language = (char)NULL;
	*format   = (char)NULL;
	currentBch = 0;
	kommem.buffer = NULL;
	kommem.alloclen = 0;
	kommem.datalen = 0;

	/*--- action specific language ----------------*/
	aktuellesprache = dialogsprache;

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

	if (arrid > 0 && DebugFlag)
	{
		(void)fprintf(stderr, "debug: arrid is %d", arrid);
		fprintf(stderr, "%s", _P_EOL_);
	}

	/* delete all KAPA entries now and make new one's later */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	if (arrid > 0)
		(void)sprintf(tmp_buffer, "DELETE FROM TDBADMIN.MP_ARRKOM WHERE ARR_ID = %d;", arrid);
	else
		(void)sprintf(tmp_buffer, "DELETE FROM TDBADMIN.MP_ARRKOM;");
	status = MPAPIdb_sqlcommand(tmp_buffer, &anzahl);
	(void)MPAPIdb_committrx();
	if (status != (int)MPOK)
		return(status);
	if (DebugFlag)
		{
		(void)fprintf(stderr, "debug: deleted %d ARRKOM entries", anzahl);
		fprintf(stderr, "%s", _P_EOL_);
		}

	/* check if only one arrangement update or all */
	if (arrid > 0)
		{
		/* make ARRKOM entries */
		status = ManageARRKOM(arrid);
		}
	else
		{
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			{
			MPfreeobj(&kommem);
			return(status);
			}
		(void)sprintf(tmp_buffer, "SELECT * FROM TDBADMIN.ARRANGEMENT WHERE ARR_ID > 0 ORDER BY ARR_ID;");
		status = MPAPIdb_sqlquery((int)_ARRANGEMENT, &sqlmem.buffer, tmp_buffer,
			                       &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		(void)MPAPIdb_committrx();
		if (status != MPOK || anzahl < 1)
			{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			MPfreeobj(&kommem);
			return(MPERROR);
			}
		Parr = (ARRANGEMENT *)sqlmem.buffer;
		for (i=0; i < anzahl && status == (int)MPOK; i++)
			{
			/* make ARRKOM entries */
			status = ManageARRKOM(Parr[i].arr_id);
			}
		}

	MPfreeobj(&kommem);

	(void)fprintf(FPout, "%s%s%s ARR-KOMM UPDATED !! ", _P_EOL_, _P_EOL_, _P_EOL_);

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

static int ManageARRKOM(int arr_id)
{
	extern MEMOBJ kommem;
	extern MP_ARRKOM arrkom;

	KOMMISSION *Pkom;
	int status = (int)MPOK;
	int anzahl;
	int i;
	char sqlquery[_QUERYLEN];

	if (DebugFlag)
		(void)fprintf(stderr, "debug: manage ARRKOM for arr: %d%s", arr_id, _P_EOL_);

	/* hole alle KATEGORIEN auf DLA.DLT_ID */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	(void)sprintf(sqlquery, _SEL_KOM_KOMTYP_ARR, (int)_KOMM_DLN,
	              arr_id, arr_id, arr_id);
	status=MPAPIdb_sqlquery((int)_KOMMISSION, &kommem.buffer, sqlquery, &anzahl,
		                      &kommem.datalen, &kommem.alloclen);
	if (status != MPOK || anzahl < 1)
		{
		if (anzahl < 1)
			{
			(void)MPAPIdb_committrx();
			if (DebugFlag)
				(void)fprintf(stderr, "debug: no kommission for arr id %d%s", arr_id, _P_EOL_);
			return(MPOK);
			}
		else
			{
			if (DebugFlag)
				(void)fprintf(stderr, "debug: Error with SQL Statement for arrid %d%s%s%s", arr_id, _P_EOL_, sqlquery, _P_EOL_);
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			(void)MPAPIdb_committrx();
			return(MPERROR);
			}
		}

	/* for one KOMMISSION make entry in ARRKOM table */
	Pkom = (KOMMISSION *)kommem.buffer;
	for (i=0; i < anzahl && status == (int)MPOK; i++)
		{
		arrkom.arr_id = arr_id;
		arrkom.komm_id = Pkom[i].komm_id;
		arrkom.komm_bezid = Pkom[i].bez_id;
		status = MPAPIinsertEntry((int)_MP_ARRKOM, (char *)&arrkom, (BEZEICHNUNG *)NULL);
		
		if (DebugFlag)
			{
			(void)fprintf(stderr, "debug: wrote ARRKOM: arrid %d, kommid %d",
			              arrkom.arr_id, arrkom.komm_id);
			fprintf(stderr, "%s", _P_EOL_);
			}
		}

	(void)MPAPIdb_committrx();


	return(status);
}
