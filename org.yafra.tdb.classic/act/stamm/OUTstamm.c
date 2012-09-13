/*D***********************************************************
 * Programm:     OUTstamm
 * Beschreibung: Print a list of all arrangements + details 
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/stamm/OUTstamm.c,v 1.2 2008-11-02 19:55:53 mwn Exp $";

/* define the entry point of this function for the main() */
int OUTstamm( int, char *[]);
#define ACTIONFUNCTION OUTstamm

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standard main Funktion */

#include "version.h"


/*E--- ETERNALS ------------------------------------------------------------*/
extern 	int			DebugFlag;


/*P--- PROTOTYPES ----------------------------------------------------------*/
static int	OUTstammWrap				( int aPrgid, int aArrid );
static void OUTstammPageHeaderWrite ();
static void	OUTstammTitleWrite		( int aPageNr );
static void	OUTstammColunmGetFormat ();
static int	OUTstammOneArrangement	(int aArrid );
static int	OUTstammHeaderPrint		( int aCruiseDlid);
static int	OUTstammForOneDl			( int aTdlid );
static void OUTstammStatistics 		( );



/*S--- SELECT'S ------------------------------------------------------------*/


/*--- TEXT ids for language independend text -------------------------------*/
#define PRINTCOMMAND				1
#define PRINTCOMMAND2			2
#define PRINTCOMMAND3			3
#define PRINTCOMMAND4			4
#define PAGE_LENGTH				5
#define BOTTOM_MARGIN			6
#define AKTTXT_DLATYP_TRANSF	7
#define AKTTXT_DLATYP_CRUISE	8
#define AKTTXT_TITLE				9
#define AKTTXT_PAGE				10
#define AKTTXT_VON				11
#define AKTTXT_AN					12
#define AKTTXT_ROUTE				13
#define AKTTXT_AB					14
#define AKTTXT_AN_END			15
#define AKTTXT_NACH				16
#define AKTTXT_TOTAL				17
#define AKTTXT_x					18
#define AKTTXT_FESTIVAL			19
#define AKTTXT_ANREDE			20
#define AKTTXT_LNAME				21
#define AKTTXT_FNAME				22
#define AKTTXT_REMARK			23
#define AKTTXT_xxx				24
#define AKTTXT_NBPAX				25

/*-- Common object texts -----------*/

/*-- Width of columns --------------*/
#define COL_H0			"%-10.10s  "                 /* Date                  */
#define COL_H1			"%-8.8s"                     /* Time                  */
#define COL_H2			"%-5.5s"                     /* gap                   */
#define COL_H3			"%-30.30s"                   /* Title PASS.LISTE      */
#define COL_H4			"%-5.5s"                     /* gap                   */
#define COL_H5			"%-10.10s"                   /* Page text             */
#define VAL_H6			"%-4d"                       /* Page nr               */

/*--- margins for AKTobjtxt --------*/
#define NOMARGIN		""
#define LEFTMARGIN	""
#define SIMPLELINE	"--------------------------------------------------------------------------"
#define SHORTLINE	   "------------------------------------------------------"
#define DOUBLELINE	"=========================================================================="

#define NEWPAGE			""

#define CRUISE_END 		0 
#define CRUISE_START		1 



/*P--- GLOBALS -------------------------------------------------------------*/
int	formTextFlag = 0;          /* flag means: form texts already in mem */
int	ArrangNb = 0;              /* nb total of arrangements  */
int	DlNb = 0;                  /* nb total of Dls   */

/*-- format for text output filled from DB texte --*/
char	fmt_sex[_CHAR80+1];
char	fmt_lastname[_CHAR80+1];
char	fmt_firstname[_CHAR80+1];
char	fmt_remark[_CHAR80+1];



/*F--------------------------------------------------------------------------
 *  Function:	OUTstamm()
 *             perform all inits 
 *             check pre-conditions 
 *					get arrangement or dl id for work 
 *					device (fax or tlx)
 *
 *  In:			-argc, argv as action was invoked
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int OUTstamm( int argc, char *argv[])
{
	extern int aktuellesprache;
	extern int dialogsprache;
	extern int outputsprache;
	extern char language[];
	extern FILE *FPout;
	extern STATUS_WERTE sta;
	extern DEVICE_PORT	devicePort;

	int		status, id1, id2;
	char		format[_RECORDLEN];
	DEVICE_PORT		*pDev;

	/*-----------------------------------------------------------------------*/
	/*     INITIALIZATIONS                                                   */
	/*-----------------------------------------------------------------------*/
	pDev = &devicePort;

	/*--- Switch for Specific flag if any --*/

	/*--- DB begin RU section ------------------------------------------RU-*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS(status)

	/*--- set the right language, normal is language of KUNDE ----*/
	AKTlanguage((int)_UNDEF, (int)_UNDEF, (int)_UNDEF, (int)_UNDEF);

	/*--- mailing header ------------------*/
	status = AKTmailHeader();
	TEST_STATUS_COMMIT(status);

	/*--- PRE-CONDITIONS check if all needed arguments are set ------------*/
	if (akttid == (int)_UNDEF ) 
	{
		AKTmsg(ACT_ERROR, MPA_INVALIDARGS, NULL);
		EXIT_COMMIT_WITH_STATUS(MPERROR);
	}
	/*--- update mailing with details -----*/
	(void)AKTmailArrangement( arrid ); 
	/*--- Page layout stuff -------------------*/
	AKTlayoutInit( );
	AKTlayoutInitLinesMax( _STAMM_TYP, PAGE_LENGTH );
	AKTlayoutInitBottomMargin( _STAMM_TYP, BOTTOM_MARGIN );

	/*-----------------------------------------------------------------------*/
	/*     START STAMM list output                                           */
	/*-----------------------------------------------------------------------*/
	/*--- General Title and Column identifiers -------*/
	OUTstammPageHeaderWrite ( );
	/*--- Build control list for stamm ------------*/
status = OUTstammWrap( (int)_UNDEF, arrid );        /*???? no progid ?????*/
	TEST_STATUS_COMMIT(status);

	/*--- End RU section -----*/
	MPAPIdb_committrx();

	/*-----------------------------------------------------------------------*/
	/*    DEVICE                                                             */
	/*-----------------------------------------------------------------------*/
	/*--- begin RU section -----------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS(status)                                   /* >>> exit */
	/*--- Device start output --------*/
	pDev->callnumber[0] = '\0';
	(void)AKTobjtxt((int)_STAMM_TYP,  (int)PRINTCOMMAND, format, NOMARGIN);
	(void)sprintf(pDev->command, "%s", format);
	(void)AKTobjtxt( (int)_STAMM_TYP, (int)PRINTCOMMAND2, format, NOMARGIN);
	(void)sprintf(pDev->command2, "%s", format);
	(void)AKTobjtxt( (int)_STAMM_TYP, (int)PRINTCOMMAND3, format, NOMARGIN);
	(void)sprintf(pDev->command3, "%s", format);
	(void)AKTobjtxt( (int)_STAMM_TYP, (int)PRINTCOMMAND4, format, NOMARGIN);
	(void)sprintf(pDev->command4, "%s", format);

	/*--- Device process -------------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");

	/*--- End RU section -------------*/
	(void)MPAPIdb_committrx();

	/*........ DEBUG .......*/
	if (DebugFlag) 
		printf("%s%sdebug: EXIT with status: %d, mailingadr: %s%s%s",
				 _P_EOL_, _P_EOL_, status, userid, _P_EOL_, _P_EOL_);


	/*-----------------------------------------------------------------------*/
	/*    CONCLUSION                                                         */
	/*-----------------------------------------------------------------------*/
	/*--- Mailing foot --------------------------*/
	AKTmailFoot(status);

exit:
	/*--- free memory ---------------------------*/

	return(status);
}





/*SF-------------------------------------------------------------------------
 *  function:	OUTstammWrap
 *  				wrapper for stamm 
 *					call stamm detail functions 
 *  In:			-aProgramm
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int OUTstammWrap (int aPrgid, int aArrid )
{
	extern 	MEMOBJ		arrgtmem, *pArrgtmem; 
	extern 	ARRANGEMENT	*arrangement ;
	extern 	int			anzArrgt;
	extern 	PROGRAMM		prg ;

	int		i, status, id ;
	int		found ;
	char		bezPrg[_BEZLEN+1];

	/*--- init --------*/
	status	= (int)MPOK;
	/*--- init mem --------*/
	AKTarrgtMemobjInit( );

	/*--- Pogramm title -------------------------------------*/
	if (aPrgid != (int)UNDEF)
	{
		id = MPAPIselectOneId((int)_PROGRAMM, aPrgid, (char *)&prg);
		if ( id != (int)UNDEF )
			(void)AKTobjbez((int)_PROGRAMM, prg.bez_id, bezPrg);
		(void)fprintf(FPout, "%-30.30s %s", bezPrg, _P_EOL_ );
	}


	/*-- Specific only that arrangt --------------------------------------*/
	if (aArrid != (int)_UNDEF)
	{ 
		status = OUTstammOneArrangement( aArrid );
		TEST_STATUS(status)
		ArrangNb = 1;              
	}
	else 
	{
		/*--- Arrangement with all parts -------------------------------------*/
		status = AKTarrgtGetAll( aPrgid );
		TEST_STATUS(status)

		/*--- loop for parts of arrgt -------*/
		for (i=0;  i<anzArrgt;   i++)
		{
			status = OUTstammOneArrangement( arrangement[i].arr_id );
			TEST_STATUS(status)			
			ArrangNb++;              
		}
	}

	/*--- print some statistics  -------*/
	OUTstammStatistics ( );
	AKTlayoutFormFeedPrint( FPout);

exit:	
	AKTarrgtMemobjFree( );
	return(status);
}




/*SF-------------------------------------------------------------------------
 *  function:	OUTstammOneArrangement
 *  				find parts of arrangement  
 *					call then sub parts functions to handle details 
 *  In:			-Arrangement
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int OUTstammOneArrangement (int aArrid )
{
	extern 	MEMOBJ		arrdlvmem, *pArrdlvmem; 
	extern 	ARRDL_VIEW	*arrdlview ;
	extern 	int			anzArrdl;
	extern 	ARRANGEMENT	arr ;
	extern 	DIENST_TRAEGER		dlt;

	int		i, status, okFlag, id ;
	int		found ;
	char		bezArr[_BEZLEN+1];
	char	date[_CHAR80+1];                              
	char	time[_DATELEN];                               
	char	day[_DATELEN];                                

	/*--- init --------*/
	status	= (int)MPOK;
	*date		= NULL;
	*time		= NULL;

	formTextFlag = 0;
	/*--- init mem --------*/
	AKTarrDlViewMemobjInit( );

	/*--- Arrangement title -------------------------------------*/
	id = MPAPIselectOneId((int)_ARRANGEMENT, aArrid, (char *)&arr);
	if ( id != (int)UNDEF )
		(void)AKTobjbez((int)_ARRANGEMENT, arr.bez_id, bezArr);
	AKTdateTextLang( arr.a_dat, date, time, day, EUROPEEN, DATE_DIGITFORM );
	(void)fprintf(FPout, "%-30.30s    %8.8s %5.5s %s",
					  bezArr, date, time, _P_EOL_);
	(void)fprintf(FPout, "%s%s", SHORTLINE, _P_EOL_);


	/*--- Arrangement with all parts -------------------------------------*/
	status = AKTarrDlView( aArrid );
	TEST_STATUS(status)

	/*--- loop for parts of arrgt -------------------------------------------*/
	for (i=0, okFlag=0;  i<anzArrdl;   i++)
	{
 		/*--- is Traeger parameter defined, when yes is it the same --*/
		if ( dltid != (int)_UNDEF)
		{
			id = MPAPIselectDLT ( _UNDEF, _UNDEF, arrdlview[i].dlg_id, &dlt );
			if ( dltid == dlt.dlt_id)
				okFlag = 1 ;
			else
				okFlag = 0 ;
		}
		else
			okFlag = 1 ;

 
		if (okFlag == 1)
		{
			/*--- Print header ----------------------------*/
			status =	OUTstammHeaderPrint( arrdlview[i].dlg_id );
			TEST_STATUS(status)
 			/*-- print all parts of transfer ---------------*/
			status = OUTstammForOneDl( arrdlview[i].dlg_id );
			TEST_STATUS(status)
		}
	}

exit:	
	AKTarrDlViewMemobjFree( );
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:	OUTstammPageHeaderWrite
 * 				group all function composing the header of each new page 
 *  In:			-page number 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTstammPageHeaderWrite ()
{
	int	pageNr;

	pageNr = AKTlayoutGetPages(); 
	OUTstammTitleWrite ( pageNr );
	OUTstammColunmGetFormat ( );
}


/*F--------------------------------------------------------------------------
 * Function:	OUTstammTitleWrite
 * 				fetch the DB texts and prepare format, write texts 
 *  In:			-page number 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTstammTitleWrite ( int aPageNr )
{
	extern char language[];

	static char	format[_CHAR80+1];
	static char	formtitel[_CHAR80+1];
	static char	formseite[_CHAR80+1];
	static	char	date[_CHAR80+1];                              
	static	char	time[_DATELEN];                               
	static	char	day[_DATELEN];                                

	/*--- get formats only first time --------------------------------------*/
	if ( formTextFlag == 0)
	{
		*formtitel	= NULL;
		*formseite	= NULL;
		*date		= NULL;
		*time		= NULL;
		/*--- print out header ----------------------------------------------*/
		(void)AKTobjtxt((int)_STAMM_TYP, AKTTXT_TITLE, formtitel, NOMARGIN);
		(void)AKTobjtxt((int)_STAMM_TYP, AKTTXT_PAGE, formseite, NOMARGIN);
		AKTdateTextLang( TODAY_VALUE, date, time, day, language, DATE_TEXTFORM );   
		/*--- format ---*/
		sprintf(format, "%s%s%s%s%s%s%s%s",
				  COL_H0, COL_H1, COL_H2, COL_H3, COL_H4, COL_H5, VAL_H6, _P_EOL_ );

		formTextFlag = 1;
	}
	/*--- write ---------------*/
	(void)fprintf(FPout, "%s", _P_EOL_);
	(void)fprintf(FPout, format, date, time, " ", formtitel, " ", formseite, aPageNr );
	(void)fprintf(FPout, "%s%s%s", SIMPLELINE, _P_EOL_, _P_EOL_);
	AKTlayoutLinesAdd( 3 );
}



/*F--------------------------------------------------------------------------
 * Function:	OUTstammColunmGetFormat
 * 				fetch the DB texts and format later used in columns 
 *  In:			-
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTstammColunmGetFormat ()
{
	char actText[_TEXTLEN+1];
	int	len;

	/*-- Header columns ---------------*/
	(void)AKTobjtxtFormat((int)_STAMM_TYP, (int)AKTTXT_ANREDE, actText, fmt_sex );
/*	(void)fprintf(FPout, fmt_sex, actText);        */
	(void)AKTobjtxtFormat((int)_STAMM_TYP, (int)AKTTXT_LNAME, actText, fmt_lastname );
/*	(void)fprintf(FPout, fmt_lastname, actText);   */
	(void)AKTobjtxtFormat((int)_STAMM_TYP, (int)AKTTXT_FNAME, actText, fmt_firstname );
/*	(void)fprintf(FPout, fmt_firstname, actText);  */
	(void)AKTobjtxtFormat((int)_STAMM_TYP, (int)AKTTXT_REMARK, actText, fmt_remark );
/*	(void)fprintf(FPout, fmt_remark, actText);     */
}


/*SF-------------------------------------------------------------------------
 *  function:	OUTstammHeaderPrint 
 *  				Anbieter, from: to: Cruise, Bus data
 *					Print Date of departure or arrival 
 *					Set language of anbieter 
 *  In:			-id
 *  out:			- 
 *  Return:		-success code
 *---------------------------------------------------------------------------
 */
static int	OUTstammHeaderPrint( aDlid )
{
	extern 	DIENSTLEISTUNG		dl;

	int	status, id, i, found ;
	char	tmpBuf[_TEXTLEN+1];
	char	bezDl[_RECORDLEN];
	char	date[_CHAR80+1];                              
	char	time[_DATELEN];                               
	char	day[_DATELEN];                                

	/*--- init ------------------*/
	status = (int)MPOK;
	*tmpBuf	 = NULL;
	*bezDl	 = NULL;
	*date		= NULL;
	*time		= NULL;
	*day		= NULL;

	/*--- Dl ------------------------*/
	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, aDlid, (char *)&dl);
	if ( id != (int)UNDEF )
		(void)AKTobjbez((int)_DIENSTLEISTUNG, dl.bez_id, bezDl);

	/*--- Dates ---------------------*/
	if (dl.a_zeit == 0 || dl.a_zeit == -1)
		{
		(void)strcpy(date, "-");
		(void)strcpy(time, "-");
		(void)strcpy(day, "-");
		}
	else
		AKTdateTextLang( dl.a_zeit, date, time, day, EUROPEEN, DATE_DIGITFORM );
	(void)fprintf(FPout, "%5.5s  %-30.30s %8.8s %5.5s%s", " ", bezDl, date, time, _P_EOL_); 
	AKTlayoutLinesAdd( 2);

exit:
	return(status);
}



/*SF-------------------------------------------------------------------------
 *  function:	OUTstammForOneDl
 *  				print for one Dienstleistung 
 *					Title + stuff 
 *  In:			-
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int OUTstammForOneDl( int aDlid )
{
	extern 	RES_DL_VIEW	*resview ;
	extern 	int			anzResv;
	extern 	DLG_DLG		*dlgdlg ;
	extern 	int			anzDlgdlg;
	extern 	DIENSTLEISTUNG		dl;
	extern 	DIENST_ANGEBOT		dla;
	extern 	DLG_PART				tdl;
	extern	ORT					ort;
	extern	int	BottomMargin ;

	int	status, id, idd, subtotal, quitbus ;
	int	i, j, k, curTdlid, curPersid ;
	int	nextPers, nextPart ;
	char	bezTxt[_RECORDLEN];
	char	abTxt[_RECORDLEN];
	char	anTxt[_RECORDLEN];
	char	nachTxt[_RECORDLEN];
	char	subtotForm[_RECORDLEN] = "%30.30s Subtotal: %d" ;
	char	routeTxt[_RECORDLEN];
	char	treffTxt[_RECORDLEN];
	char	date[_CHAR80+1];                              
	char	time[_DATELEN];                               
	char	day[_DATELEN];                                
	RES_DL_VIEW			*pResv, *pResv2, pResvnext;                                
	DLG_DLG				*pDlg;                                

	/*--- init --------*/
	status	= (int)MPOK;
	*bezTxt	= NULL;
	*routeTxt	= NULL;
	*treffTxt	= NULL;
	*date		= NULL;
	*time		= NULL;
	*day		= NULL;

	/*--- dlgdlg memobject --------*/
	AKTdlgdlgMemobjInit( );

	/*--- texts used many times ---*/
	/*-- Subtotal ----*/
	(void)AKTobjtxt((int)_STAMM_TYP, AKTTXT_TOTAL, subtotForm, NOMARGIN);

	/*--- Query all Bus Parts of Dl ----------------------------------------*/
	status = AKTdlgdlgFindAll( aDlid );
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)        /*>>>> exit */


	/*--- Loop for all parts ----------------------------------*/
	for (k=0;  k<anzDlgdlg;  k++)
	{
		/*--- get current Tdlid and look for Dlns ----*/
		pDlg = &dlgdlg[k]; 
		curTdlid = pDlg->dl_id;

		/*--- Dl_part  ---------------*/
		idd = MPAPIselectOneId((int)_DLG_PART, curTdlid, (char *)&tdl);
		(void)AKTobjbez((int)_DLG_PART, tdl.bez_id, bezTxt);
		(void)fprintf(FPout, "%10.10s%2d  %-30.30s", " ", tdl.ord, bezTxt );
		if (tdl.a_zeit == 0 || tdl.a_zeit == -1)
			{
			(void)strcpy(date, "-");
			(void)strcpy(time, "-");
			(void)strcpy(day, "-");
			}
		else
			AKTdateTextLang( tdl.a_zeit, date, time, day, EUROPEEN, DATE_DIGITFORM );
		(void)fprintf(FPout, "%8.8s %5.5s", date, time);
		if (tdl.e_zeit == 0 || tdl.e_zeit == -1)
			{
			(void)strcpy(date, "-");
			(void)strcpy(time, "-");
			(void)strcpy(day, "-");
			}
		else
			AKTdateTextLang( tdl.e_zeit, date, time, day, EUROPEEN, DATE_DIGITFORM );
		(void)fprintf(FPout, "    %8.8s %5.5s %s", date, time, _P_EOL_);


		/*--- Dla --------------------*/
		idd = MPAPIselectOneId((int)_DIENST_ANGEBOT, tdl.dla_id, (char *)&dla);
		(void)copyTextTo( treffTxt, dla.ort, _CHAR30 );
		/*--- von Ort ----------------*/
		idd = MPAPIselectOneId((int)_ORT, dla.von, (char *)&ort);
		(void)AKTobjbez((int)_ORT, ort.bez_id, bezTxt);
		(void)fprintf(FPout, "%12.12s%s (%s)     ", " ", bezTxt, treffTxt);
		/*--- nach Ort ----------------*/
		idd = MPAPIselectOneId((int)_ORT, dla.nach, (char *)&ort);
		(void)AKTobjbez((int)_ORT, ort.bez_id, bezTxt);
		(void)fprintf(FPout, "%s (%s) %s", bezTxt, treffTxt, _P_EOL_);

		AKTlayoutLinesAdd( 1);

		/*--- Detect end of page and go to new and print header --------*/
		if ( LayLines + LayBottomMargin  > LayLinesMax )
		{
			AKTlayoutFormFeedPrint( FPout);
			OUTstammPageHeaderWrite ( );
		}
	}

	/*--- separator --------------------------*/
	(void)fprintf(FPout, "%s%s", _P_EOL_, _P_EOL_);
	AKTlayoutLinesAdd( 2);

exit:
	AKTdlgdlgMemobjFree( );
	return(status);
}







/*F--------------------------------------------------------------------------
 * Function:	OUTstammStatistics
 * 				print statistics about stamm daten
 *  In:			- 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTstammStatistics ( )
{
	extern char language[];
	extern SPRACHEN			spr;

	char	tmpBuf[_TEXTLEN+1];
	char	format[_TEXTLEN+1];
	int	i; 

	/*--- ints -----------*/
	*format		= NULL;
	*tmpBuf		= NULL;

	/*--- Nb total stamm ---------------------------------*/
	(void)AKTobjtxt((int)_STAMM_TYP, AKTTXT_NBPAX, format, NOMARGIN);
	(void)fprintf(FPout, format, " ", ArrangNb );
	(void)fprintf(FPout, "%s", _P_EOL_);
	AKTlayoutLinesAdd( 1);
}

