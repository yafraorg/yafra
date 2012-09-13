/*D***********************************************************
 * program:      OUTchange
 * descripton:   Aendert der status Wert
 *
 * arguments:    standard arguments
 *               -t  must   action typ           (AKTIONS_TYP  akttid)
 *               -b  opt    focus on BCH         (BUCHUNG)
 *               -d  opt    focus on BCH         (dlid)
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/change/OUTchange.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";


/*--- define the entry point of this function for the main() */
int OUTchange( void);
#define ACTIONFUNCTION	(OUTchange)

/*--- MarcoPolo API includes */
#include <mpact.h>    
  
/*--- MarcoPolo API standard main function ! */
#include "AKTmain.h"

#include "version.h"

/*--- define text ids for language independent text */
#define PRINTCOMMAND1 1

#define TOTULINE		"------------------------------------------------------------------------"

/*-- Width of columns ---------*/
#define COL_0			"%s"
#define COL_0L			"%-s"                        /* COL_1       Left just */
#define COL_1			"%2.2s"


/*F--------------------------------------------------------------------------
 *  Function:	OUTchange ()
 *					Change the status when action executes
 *  In:			-
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int OUTchange()
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
	int		i, j, oldGroupId;
	char     format[_RECORDLEN];
	AKT_DETAIL	adcntrl;


	/*--- init ----------------------------------*/
	pDev = &devicePort;
	*language = (char)NULL;
	*format   = (char)NULL;
	currentBch = 0;

	/*--- action specific language ----------------*/
	aktuellesprache = dialogsprache;

	/*--- begin RU section ------------------------------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)           /*>>>> exit */

	/*--- mailing header --------------------------*/
	status = AKTmailHeader() ;
	if (status != (int)MPOK)
		EXIT_WITH_STATUS(status)                                /*>>>> exit */

	/*--- check if obligatory arguments are set ---*/
	if (akttid == (int)_UNDEF || dlid == (int)_UNDEF || bchid == (int)_UNDEF)  
		{
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		EXIT_WITH_STATUS(MPERROR)                                 /*>>>> exit */
		}

	/*--- End RU section -----*/
	(void)MPAPIdb_committrx();


	/*--- Start db transaction and check if it's ok to run this action ---*/
	status = MPAPIdb_begintrx(SQLISOLATION_RC, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	adcntrl.bid      = bchid;
	adcntrl.a_typ_id = akttid;
	adcntrl.dlg_id   = dlid;                   /* specific for that DL in BID */
	adcntrl.dl_id    = (int)_UNDEF;            
	if (reinitflag == (int)TRUE)
		{
		status = AKTcntrl(_AKTCNTRL_REINIT, &adcntrl, (int)_UNDEF);
		(void)MPAPIdb_committrx();
		}
	else
		{
		status = AKTcntrl(_AKTCNTRL_CHECK, &adcntrl, (int)_UNDEF);
		(void)MPAPIdb_committrx();
		if (status != (int)MPOK)
			{
			/*--- if Aktion auf dieser Buchung fehlerhaft, Meldung + naechste */
			status = (int)MPOK;
			}
		}

	/*--- start db transaction and check if it's ok to run this action --*/
	status = MPAPIdb_begintrx(SQLISOLATION_RC, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	status = AKTcntrl(_AKTCNTRL_CONFIRM, &adcntrl, targetsta);
	(void)MPAPIdb_committrx();
	if (status != (int)MPOK)
		{
		AKTmsg(ACT_ERROR, MPA_NOSTART, NULL);
		status = (int)MPOK;
		}


	/*-------------------------------------------------------------------*/
	/*    END - make output if necessary                                 */
	/*-------------------------------------------------------------------*/
	if (targetsta == (int)_UNDEF)
		(void)fprintf(FPout, "%s%sSTATUS VALUE IS CHANGED FOR BOOKING %d WITH SERVICE %d", _P_EOL_, _P_EOL_, adcntrl.bid, adcntrl.dlg_id);
	else
		(void)fprintf(FPout, "%s%sSTATUS VALUE IS CHANGED TO %d FOR BOOKING %d WITH SERVICE %d", _P_EOL_, _P_EOL_, targetsta, adcntrl.bid, adcntrl.dlg_id);

	/*--- Device -------------------------------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)
	(void)AKTobjtxt( _COMMON_TYP, (int)PRINTCOMMAND1, format, NOMARGIN);   
	(void)sprintf(pDev->command, "%s", format);
	pDev->callnumber[0] = '\0';
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Status Change: Device error ");
	(void)MPAPIdb_committrx();

exit:
	/*--- mail current booking id -------------------------------*/
	if ((status != MPOK) && (currentBch >= 0))
		{
		AKTmsgget( MPA_FATALERRORSTATE, format);
		(void)sprintf( mailstring, format, currentBch);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		}

	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

	return(status);	
}


