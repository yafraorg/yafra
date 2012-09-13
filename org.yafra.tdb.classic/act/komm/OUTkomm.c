/*D***********************************************************
 * Programm:     OUTkomm
 * Beschreibung: Print a list of all arrangements + details 
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/komm/OUTkomm.c,v 1.2 2008-11-02 19:55:53 mwn Exp $";
#include "version.h"

/* define the entry point of this function for the main() */
int OUTkomm( int, char *[]);
#define ACTIONFUNCTION OUTkomm

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standard main Funktion */


/*E--- ETERNALS ------------------------------------------------------------*/
extern 	int			DebugFlag;


/*P--- PROTOTYPES ----------------------------------------------------------*/
static int	OUTkommWrap					( int aPrgid, int aArrid );
static void OUTkommPageHeaderWrite 	();
static void	OUTkommTitleWrite			( int aPageNr );
static void	OUTkommColunmGetFormat 	();
static int	OUTkommHeaderPrint		( int aCruiseDlid);
static void OUTkommStatistics 		( );
static int OUTkommLoopItems			();



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
#define SIMPLELINE	"--------------------------------------------------------------------------"
#define SHORTLINE	   "-------------------------"

#define NEWPAGE			""


/*P--- GLOBALS -------------------------------------------------------------*/
int	formTextFlag = 0;          /* flag means: form texts already in mem */
int	NbKommis = 0;              /* nb total of arrangements  */
int	DlNb = 0;                  /* nb total of Dls   */

/*-- format for text output filled from DB texte --*/
char	fmt_sex[_CHAR80+1];
char	fmt_lastname[_CHAR80+1];
char	fmt_firstname[_CHAR80+1];
char	fmt_remark[_CHAR80+1];



/*F--------------------------------------------------------------------------
 *  Function:	OUTkomm()
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
int OUTkomm( int argc, char *argv[])
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

	/*--- Page layout stuff -------------------*/
	AKTlayoutInit( );
	AKTlayoutInitLinesMax( _STAMM_TYP, PAGE_LENGTH );
	AKTlayoutInitBottomMargin( _STAMM_TYP, BOTTOM_MARGIN );

	/*-----------------------------------------------------------------------*/
	/*     START  list output                                                */
	/*-----------------------------------------------------------------------*/
	/*--- General Title and Column identifiers -------*/
	OUTkommPageHeaderWrite ( );
	/*--- Build control list for stamm ------------*/
	status = OUTkommWrap( (int)_UNDEF, (int)_UNDEF );
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
 *  function:	OUTkommWrap
 *  				wrapper for stamm 
 *					call stamm detail functions 
 *  In:			-aProgramm
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int OUTkommWrap (int aPrgid, int aArrid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;

	int		i, status, id ;
	int		found ;

	/*--- init --------*/
	status	= (int)MPOK;
	/*--- init mem --------*/
	AKTcommisMemobjInit( );

	/*--- Get all commissions ------------------------------------*/
	status = AKTcommisFindAll((int)UNDEF, (int)UNDEF, (int)UNDEF, (int)UNDEF );
	TEST_STATUS(status)
		
	/*--- loop for parts of arrgt -------*/
	status = OUTkommLoopItems(  );
	TEST_STATUS(status)			

	/*--- print some statistics  -------*/
	OUTkommStatistics ( );
	AKTlayoutFormFeedPrint( FPout);

exit:	
	AKTcommisMemobjFree( );
	return(status);
}




/*SF-------------------------------------------------------------------------
 *  function:	OUTkommLoopItems
 *					print all stuff for commission/reduction
 *  In:			-komm_id 
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int OUTkommLoopItems ( )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern 	KOMMISSION			kom ;
	extern 	DIENSTLEISTUNG		dl;
	extern 	DIENST_ANGEBOT		dla;
	extern 	STATUS_WERTE		sta;
	extern	KOSTEN_ART			kar;

	KOMMISSION	*pCom ;
	int		status, id, i ;
	int		oldKommtyp ;
	char		bezTxt[_BEZLEN+1];
	char		komTxt[_BEZLEN+1];
	char		SatzTxt[_BEZLEN+1];
	char		ValTxt[_BEZLEN+1];
	char		kommtypTxt[_BEZLEN+1];
	char	date[_CHAR80+1];                              
	char	time[_DATELEN];                               
	char	day[_DATELEN];                                

	/*--- init --------*/
	status	= (int)MPOK;
	*bezTxt		= NULL;
	*komTxt		= NULL;
	*SatzTxt		= NULL;
	*ValTxt		= NULL;
	*kommtypTxt	= NULL;
	*date		= NULL;
	*time		= NULL;
	*day		= NULL;


	/*--- loop for parts of arrgt -------*/
	oldKommtyp = (int)UNDEF;
	for (i=0;  i<anzCommis;   i++)
	{				
		pCom = &commis[i];

		/*--- get a struct -------------------------------------*/
		id = MPAPIselectOneId((int)_KOMMISSION, pCom->komm_id, (char *)&kom);
		if ( id == (int)UNDEF )
			return((int)MPERROR);

		/*-- Komm typ ------*/
		if (oldKommtyp != kom.komm_typ)
		{
			id = MPAPIselectOneId((int)_STATUS_WERTE, kom.komm_typ, (char *)&sta);
			(void)AKTobjbez((int)_KOMMTYP, sta.bez_id, bezTxt);
			(void)fprintf(FPout, "%s%-30.30s %s", _P_EOL_, bezTxt, _P_EOL_);
			(void)fprintf(FPout, "%s%s", SHORTLINE, _P_EOL_);
		}	
		oldKommtyp = kom.komm_typ;
	
		/*-- Kommissions_Id und Rangierung ----*/
		(void)fprintf(FPout, "%-5.5d ", kom.komm_id);
		(void)AKTobjtxt((int)_KOMMISSION, kom.textid, bezTxt, NOMARGIN);
		(void)fprintf(FPout, "%-5.5s ", bezTxt);
	
		/*-- Kommission / reduktion ----*/
		(void)AKTobjbez((int)_KOMMISSION, kom.bez_id, bezTxt);
		(void)fprintf(FPout, "%-25.25s ", bezTxt);
				
		/*-- Satz art ------*/
		id = MPAPIselectOneId((int)_STATUS_WERTE, kom.satz_art, (char *)&sta);
		(void)AKTobjbez((int)_SATZTYP, sta.bez_id, bezTxt);
		(void)fprintf(FPout, "%-20.20s ", bezTxt);
		/*-- Satz value ----*/
		cashint ( (int)kom.satz, "%d", ValTxt );
		(void)fprintf(FPout, "%8s ", ValTxt);
		
		/*-- Kosten art ------*/
		id = MPAPIselectOneId((int)_KOSTEN_ART, kom.kar_id, (char *)&kar);
		(void)AKTobjbez( (int)_KOSTEN_ART, kar.bez_id, bezTxt);
		(void)fprintf(FPout, "%-15.15s ", bezTxt);
		
		
		/*-- Angebot ----*/
		if (kom.dla_id != (int)UNDEF)
		{
			id = MPAPIselectOneId((int)_DIENST_ANGEBOT, kom.dla_id, (char *)&dla);
			(void)AKTobjbez( (int)_DIENST_ANGEBOT, dla.bez_id, bezTxt);
			(void)fprintf(FPout, "%-20.20s ", bezTxt);
		}
		else
			(void)fprintf(FPout, "%-20.20s ", "-");
		
		/*-- Dl ----*/
		if (kom.dl_id != (int)UNDEF)
		{
			id = MPAPIselectOneId((int)_DIENSTLEISTUNG, kom.dl_id, (char *)&dl);
			(void)AKTobjbez( (int)_DIENSTLEISTUNG, dl.bez_id, bezTxt);
			(void)fprintf(FPout, "%-20.20s ", bezTxt);
		}
		else
			(void)fprintf(FPout, "%-20.20s ", "-");
		
		
		/*-- von date ----*/
		if (kom.dl_vondat != (int)UNDEF)
		{
			AKTdateTextLang( kom.dl_vondat, date, time, day, EUROPEEN, DATE_DIGITFORM );
			(void)fprintf(FPout, "%8.8s ", date);
		}
		else
			(void)fprintf(FPout, "%8.8s ", "-");

		/*-- bis date ----*/
		if (kom.dl_vondat != (int)UNDEF)
		{
			AKTdateTextLang( kom.dl_bisdat, date, time, day, EUROPEEN, DATE_DIGITFORM );
			(void)fprintf(FPout, "%8.8s ", date);
		}
		else
			(void)fprintf(FPout, "%8.8s ", "-");
		
		(void)fprintf(FPout, "%s", _P_EOL_);
		
		NbKommis++;              
	}


exit:	
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:	OUTkommPageHeaderWrite
 * 				group all function composing the header of each new page 
 *  In:			-page number 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTkommPageHeaderWrite ()
{
	int	pageNr;

	pageNr = AKTlayoutGetPages(); 
	OUTkommTitleWrite ( pageNr );
	OUTkommColunmGetFormat ( );
}


/*F--------------------------------------------------------------------------
 * Function:	OUTkommTitleWrite
 * 				fetch the DB texts and prepare format, write texts 
 *  In:			-page number 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTkommTitleWrite ( int aPageNr )
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
 * Function:	OUTkommColunmGetFormat
 * 				fetch the DB texts and format later used in columns 
 *  In:			-
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTkommColunmGetFormat ()
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






/*F--------------------------------------------------------------------------
 * Function:	OUTkommStatistics
 * 				print statistics about stamm daten
 *  In:			- 
 *  out:			-
 *  Return:		-
 *--------------------------------------------------------------------------
 */
static void OUTkommStatistics ( )
{
	extern char language[];

	char	tmpBuf[_TEXTLEN+1];
	char	format[_TEXTLEN+1];
	int	i; 

	/*--- ints -----------*/
	*format		= NULL;
	*tmpBuf		= NULL;

	/*--- Nb total stamm ---------------------------------*/
	(void)AKTobjtxt((int)_STAMM_TYP, AKTTXT_NBPAX, format, NOMARGIN);
	(void)fprintf(FPout, format, " ", NbKommis );
	(void)fprintf(FPout, "%s", _P_EOL_);
	AKTlayoutLinesAdd( 1);
}

