/*D***********************************************************
 * program:      OUTrequest
 * descripton:   request for a free dlt-place from a DL
 *               give KAT if it's present
 *               execute it only on one BCH on one DL !
 *
 * arguments:    standard arguments
 *               -b  must   execution only on one BCH
 *               -s  must   DL for requesting a cabine/place in BCH
 *               -t  must   action typ
 *               -R  opt    reinitialize this action
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/request/OUTrequest.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/* define the entry point of this function for the main() */
int OUTrequest(int, char *[]);
#define ACTIONFUNCTION OUTrequest

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standart main Funktion */

#include "version.h"

/*P--- PROTOTYPES ----------------------------------------------------------*/
static int OUTrequestCheckMessage();
static int OUTrequestMessage();
static int OUTrequestAllotCover();
static int OUTrequestCatBerth();
static int OUTrequestText();
static int OUTrequestPax( int aDlnNumber);
static int OUTrequestDevice();
static int OUTrequestBirthdateToAge( char *birthDate );


/*--- SQL ------------------------------------------------------------------*/
#define _SEL_RESBCH "SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d \
	AND DLG_ID = %d ORDER BY PERS_ID, DL_ID, TEIL;"

#define _SEL_KONT_DETAIL_KID_KAT "SELECT * FROM TDBADMIN.KONT_DETAIL \
	WHERE KONT_ID = %d AND KAT_ID = %d ;"


/*--- define text ids for language independend text ------------------------*/
#define PRINTCOMMAND          1
#define PRINTCOMMAND2         2
#define PRINTCOMMAND3         3
#define PRINTCOMMAND4         4
#define AKTTXT_REQUEST        5
#define AKTTXT_MODIFICAT      6
#define AKTTXT_RECONFIRM      7
#define AKTTXT_CANCEL         8
#define AKTTXT_ALLOT          9
#define AKTTXT_ALLOT_GRP     10
#define AKTTXT_COVER_GRP     11
#define AKTTXT_BCHREF        12
#define AKTTXT_DLNKAT        13
#define AKTTXT_REQUESTS      14
#define AKTTXT_PAX           15
#define AKTTXT_REMARKS       16
#define AKTTXT_AN            17
#define AKTTXT_VON           18
#define AKTTXT_LB_GB         19
#define AKTTXT_SGL           20
#define AKTTXT_DBL           21
#define AKTTXT_TPL           22
#define AKTTXT_QD            23

/* margins for AKTobjtxt */
#define TOFROMMARGIN         "         "
#define LEFTMARGIN           "    "
#define COL_FREE	   "%-s"            /* free format             */
#define COL_0			"%4.4s"          /* margin                  */
#define COL_1			"%-5.5s"         /* Pax:                    */
#define VAL_2			"%-3d"           /* number                  */
#define COL_3			"%2.2s"          /* gap                     */
#define COL_TOT3		"%14.14s"        /* COL_1+2+3               */
#define COL_4			"%-20.20s"       /* Name                    */
#define COL_5			"%-15.15s"       /* Firstname               */
#define COL_6			"%-5.5s"         /* sex code                */
#define COL_7			"%-5.5s"         /* dlncode qualifier       */
#define VAL_8			"%-4d"           /* age  decimal            */
#define COL_8			"%-10.10s"       /* age ascii               */
/*-- remarks -----------------*/
#define COL_RMK0		"%16.16s"       /* COL_1+2+3+gap     */
#define COL_RMK1		"%-8.8s"         /* remarks:          */

#define SUB_REQUEST	    1
#define SUB_MODIF	       2
#define SUB_RECONF	    3
#define SUB_CANCEL	    4


/*P--- GLOBALS -------------------------------------------------------------*/
int	subject;                 /* request, modif., reconfirmation, cancel */
char	subjectTxt[_RECORDLEN];  /* explicit text from DEF_X_request.sql          */




/*F--------------------------------------------------------------------------
 *  Function:	OUTrequest ()
 *					get "Kunden" infos (KID) and build filename
 *					find device (fax or tlx)
 *					the radix: "FAX" or "TLX" are also used in cronfax script!
 *					get text which is requested to destination (BID)
 *					Request specified action
 *
 *  In:			-argc, argv as action was invoked
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
int OUTrequest(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern int dialogsprache;
	extern int aktuellesprache;
	extern int outputsprache;
	extern char language[];
	extern FILE *FPout;
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern int DebugFlag;

	extern BUCHUNG			bch;
	extern DLG_PART		dlg;
	extern DIENST_ANGEBOT dla;
	extern KUN_VIEW		kunv;

	int		status, mesflag ;
	char     format[_RECORDLEN];
	int		subtitle;

	AKT_DETAIL		adcntrl;
	DEVICE_PORT		*pDev;

	/*--- inits -----------*/
	pDev = &devicePort;
	*language = (char)NULL;
	*format   = (char)NULL;
	AKTreservatMemobjInit();

	if (DebugFlag)
		(void)printf("\n\ndebug: Version %s\n\n", MAINVERSION);

	/*--- begin RU section ---------------------------------------------RU-*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS(status)                                   /* >>> exit */

	/*--- set the right language, default is dialogsprache ----------------*/
	AKTlanguage((int)_UNDEF, (int)_UNDEF, (int)_UNDEF, (int)_UNDEF);

	/*--- General switch for action type ---------*/
	switch (specificflag)
		{
		case 1:
			subject = (int)SUB_REQUEST;
			subtitle = (int)AKTTXT_REQUEST;
			break;
		case 2:
			subject = (int)SUB_MODIF;
			subtitle = (int)AKTTXT_MODIFICAT;
			break;
		case 3:
			subject = (int)SUB_RECONF;
			subtitle = (int)AKTTXT_RECONFIRM;
			break;
		case 4:
			subject = (int)SUB_CANCEL;
			subtitle = (int)AKTTXT_CANCEL;
			break;
		default:
			/*----- no -f flag set ----*/
			if (DebugFlag)
				(void)printf("debug: no -f flag is give (should be 1-4)\n");
			subject = (int)SUB_REQUEST;
			subtitle = (int)_UNDEF;
			break;
		}
	(void)AKTobjtxt((int)_REQUEST_TYP, subtitle, subjectTxt, LEFTMARGIN);


	/*--- mailing header -------------*/
	status = AKTmailHeader();
	TEST_STATUS_COMMIT(status)                                  /*>>>> exit */

	/*--- check if all needed arguments are set ---*/
	if (bchid == (int)_UNDEF || akttid == (int)_UNDEF || dlid == (int)_UNDEF)
		{
		AKTmsg(ACT_ERROR, MPA_INVALIDARGS, NULL);
		EXIT_COMMIT_WITH_STATUS(MPERROR)                           /*>>>> exit */
		}
	/*--- End RU section -------------*/
	(void)MPAPIdb_committrx();


	/*--- Control state but not for Modification ---------------*/
	/*--- start db transaction and check if it's ok to run this action ----*/
	status = MPAPIdb_begintrx(SQLISOLATION_RC, SQLPRIO_NORMAL);
	TEST_STATUS(status)                                   /* >>> exit */

	/*--- Modification has multiple executions ----*/
	if (subject == (int)SUB_MODIF)
		adcntrl.z_flag = _AKT_READYTOSTART ;    /* force to be ready */
	else
		adcntrl.z_flag = (int)_UNDEF ;          /* execute once */
	adcntrl.bid = bchid;
	adcntrl.a_typ_id = akttid;
	adcntrl.dlg_id = dlid;
	if (reinitflag == (int)TRUE)
		{
		status = AKTcntrl(_AKTCNTRL_REINIT, &adcntrl, (int)_UNDEF);
		TEST_STATUS_COMMIT( status)
		}
	else
		{
		status = AKTcntrl(_AKTCNTRL_CHECK, &adcntrl, (int)_UNDEF);
		TEST_STATUS_COMMIT( status)
		}
	/*--- End RR section -------------*/
	(void)MPAPIdb_committrx();


	/*-----------------------------------------------------------------------*/
	/*    MESSAGE                                                            */
	/*-----------------------------------------------------------------------*/
	/*--- begin RU section -------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS(status)                                   /* >>> exit */

	/*--- Get reservations --------------------*/
	status = AKTreservatBidDlgid( bchid, dlid);
	if (status != MPOK || anzRes < 1)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_COMMIT_WITH_STATUS(MPERROR)
		}

	/*--- Check if we need a message ----------*/
	mesflag = OUTrequestCheckMessage( );
	if ( mesflag == 1)
		{
		/*--- Build a message ------------------*/
		status = OUTrequestMessage( );
		TEST_STATUS_COMMIT(status)                                  /*>>>> exit */

		/*--- Device output --------------------*/
		status = OUTrequestDevice();
		if (status != MPOK)
			{
			AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");
			EXIT_COMMIT_WITH_STATUS(MPERROR)
			}
		}

	/*--- End RU section ---------------------------------------------------*/
	(void)MPAPIdb_committrx();


	/*-----------------------------------------------------------------------*/
	/*    Conclusion  CONFIRM                                                */
	/*-----------------------------------------------------------------------*/
	/*--- start db transaction and confirm this action state -------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RC, SQLPRIO_NORMAL);
	TEST_STATUS(status)                                   /* >>> exit */

	adcntrl.bid = bchid;
	adcntrl.a_typ_id = akttid;
	adcntrl.dlg_id = dlid;
	status = AKTcntrl(_AKTCNTRL_CONFIRM, &adcntrl, targetsta);
	TEST_STATUS_MSG_COMMIT(status, MPA_NOSTART)

	(void)MPAPIdb_committrx();  /*-- End RR section --*/


	/*-----------------------------------------------------------------------*/
	/*    EXIT                                                               */
	/*-----------------------------------------------------------------------*/
exit:
	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

	/*--- free memory -----------------*/
	AKTreservatMemobjFree();

	return(status);
}




/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestCheckMessage ()
 *					check if a message is really necessary
 *					- not if allotment is requested
 *  In:			-
 *  out:			-
 *  Return:		-value 1 requests a message
 *---------------------------------------------------------------------------
 */
static int OUTrequestCheckMessage()
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	/*--- when cabine nr is known do not request ------*/
	if ((reservation[0].dlt_id != (int)_UNDEF) && (subject == SUB_REQUEST ))
		/*--- return(0); --- dv always make a request ---*/
		return(1);
	else
		return(1);
}



/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestDlnNumber ()
 *					count nb of dlns
 *
 *  In:			-
 *  out:			-
 *  Return:		-nb of dln
 *---------------------------------------------------------------------------
 */
static int OUTrequestDlnNumber()
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int		i, nbDln, grpuid ;
	RESERVATION	*pRes;

	/*-- count all DLN's in this booking -----------------------------------*/
	grpuid = (int)-2;
	nbDln = 0;
	for (i=0;  i < anzRes;  i++)
	{
		pRes = &reservation[i];
		if (grpuid != pRes->pers_id)
		{
			nbDln++;
			grpuid = pRes->pers_id;
		}
	}
	return(nbDln);
}




/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestMessage ()
 *					get "Kunden" infos (KID) and build filename
 *					get text which is requested to destination (BID)
 *					Request specified action
 *
 *  In:			-
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
static int OUTrequestMessage()
{
	extern int dialogsprache;
	extern int aktuellesprache;
	extern int outputsprache;
	extern char language[];
	extern FILE *FPout;
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	extern BUCHUNG				bch;
	extern DLG_PART			dlg;
	extern DIENST_ANGEBOT 	dla;
	extern KUN_VIEW			kunv;
	extern DIENST_TRAEGER	dlt;

	int		status, id;
	char		bez1[_RECORDLEN];
	char		bez2[_RECORDLEN];
	char		bez3[_RECORDLEN];
	char		tmp_buffer[_RECORDLEN];
	char     format[_RECORDLEN];
	int		 nbDln;

	DIENST_TRAEGER	diensttraeger;
	RESERVATION		*pRes;
	DIENSTLEISTUNG dl;
	KUN_VIEW			kbst;


	/*--- inits -----------*/
	pRes = &reservation[0] ;
	status = (int)MPOK ;

	/*-- DL: Dienstleistung die zu bearbeiten ist -----*/
	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, dlid, (char *)&dl);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*-- BCH: current booking -------------------------*/
	id = MPAPIselectOneId((int)_BUCHUNG, bchid, (char *)&bch);
	if (bch.bid == (int)UNDEF)              /* DO NOT TEST id, function bug */
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*--- DLG_PARTS: Teildienstleistungen mit Anbieter als Kunde */
	status = MPAPIselectTDL(dlid, &dlg);
	if (status != (int)MPOK)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*-- DLA: Dienstleistungsangebot mit Haupttr�ger ---*/
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dlg.dla_id, (char *)&dla);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*-- DLT: Dienstleistungstr�ger --------------------*/
	id = MPAPIselectOneId((int)_DIENST_TRAEGER, dla.dlt_id, (char *)&diensttraeger);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*-- KUNDEN: Anbieter der Dienstleistung -----------*/
	id = MPAPIselectOneId((int)_KUN_VIEW, dlg.kid, (char *)&kunv);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}

	/*-- PROFIL: get owner profil for BCH STELLE BST -----------------*/
	id = MPAPIselectOneId((int)_MP_PROFIL, bch.anw, (char *)&prof);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}
	/*-- KUNDEN: name of sender of FAX -----------------*/
	id = MPAPIselectOneId((int)_KUN_VIEW, prof.bchst, (char *)&kbst);
	if (id == (int)UNDEF)
	{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		EXIT_WITH_STATUS(MPERROR)
	}


	/*-- Mailing with details ------------------------------------*/
	(void)AKTmailDetail(bchid, dlid, (int)_UNDEF, (int)_UNDEF, dla.dlt_id);

	/*-- count the dlns --------------------------------*/
	nbDln = OUTrequestDlnNumber();

	/***********************************************************************/
	/* PRINT A REQUEST FORM                                                */
	/***********************************************************************/

	/*--- set right language, KUNDE Anbieter -------------------*/
	AKTlanguage((int)_UNDEF, (int)_UNDEF, (int)_UNDEF, kunv.kun_id);

	/*-- To recipients -----------------------------------------*/
	(void)copyTextTo(bez1, kunv.name, _CHAR512);
	(void)copyTextTo(bez2, kunv.ort, _CHAR256);
	(void)copyTextTo(bez3, kunv.fax, _CHAR256);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_AN, format, TOFROMMARGIN);
	(void)fprintf(FPout, "%s  %s, %s, %s%s", format, bez1, bez2, bez3, _P_EOL_);

	/*-- Mailing: recipient + call number ----*/
	AKTmailDevice(	bez1, bez3);

	/*-- From emitter ------------------------*/
	(void)copyTextTo(bez1, kbst.name, _CHAR512);
	(void)copyTextTo(bez2, kbst.ort, _CHAR256);
	(void)copyTextTo(bez3, kbst.fax, _CHAR256);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_VON, format, TOFROMMARGIN);
	(void)fprintf(FPout, "%s %s, %s, %s%s", format, bez1, bez2, bez3, _P_EOL_);
	(void)fprintf(FPout, "%s", _P_EOL_);


	/*--- Subject title header -------------------------------------------*/
	(void)fprintf(FPout, "%s%s", subjectTxt, _P_EOL_);   /*  dieter datum   */
	(void)fprintf(FPout, "%s", _P_EOL_ );

	/*-- Allot/Allot GRP/ Cover grp --------------------------------------*/
	status = OUTrequestAllotCover( );
	TEST_STATUS(status)                                     /*>>>> exit */


	/*-- booking ref -----------------------------*/
	(void)fprintf(FPout, "%s", _P_EOL_ );         /* dieter new linefeed */
	(void)copyTextTo(bez1, bch.ref, _CHAR256);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_BCHREF, format, LEFTMARGIN);
	(void)fprintf(FPout, "%s %s%s", format, bez1, _P_EOL_);

	/*--- Traeger + DL ----------------------------------------------------*/
	(void)AKTobjbez((int)_DIENST_TRAEGER, diensttraeger.bez_id, bez2);
	(void)AKTobjbez((int)_DIENSTLEISTUNG, dl.bez_id, bez1);
	(void)convdate((time_t)dl.a_zeit, "%b %d %y", language, tmp_buffer);
	(void)fprintf(FPout, "%s%s   %s   %s%s", LEFTMARGIN, bez2, tmp_buffer,
	              bez1, _P_EOL_ );

	/*???????? show here any DLG_PART if needed (if res.dl_id != -1) */


	/*-- Category, berth, cabine --------------------------*/
	status = OUTrequestCatBerth( nbDln );
	TEST_STATUS(status)                                     /*>>>> exit */

	/*-- Request text--------------------------------------*/
	status = OUTrequestText( );
	TEST_STATUS(status)                                     /*>>>> exit */

	/*-- Pax list and berth codes and texts if any --------*/
	status = OUTrequestPax( nbDln );
	TEST_STATUS(status)                                     /*>>>> exit */

	(void)fprintf(FPout, "%s%s%s%s", _P_EOL_, _P_EOL_, _P_EOL_, _P_EOL_);

exit:
	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestAllotCover ()
 *					test kind of request with allotment or not
 *
 *  In:			-
 *  out:			-
 *  Return:		-status
 *---------------------------------------------------------------------------
 */
static int OUTrequestAllotCover()
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern 	KONTINGENT	kon;

	char		query[2*RECLAENGE];
	char		dbText[_CHAR80+1];
	char     refText[_BEZLEN];
	char		bez1[_BEZLEN];
	int		status, id;
	int		anzKond, usedKon;
	MEMOBJ		kondmem;
	KONT_DETAIL	*kond, *pKond;
	RESERVATION	*pRes;

	/*-- inits -----------*/
	status = (int)MPOK ;
	/*-- memory ----------*/
	kond   = (KONT_DETAIL *)NULL;
	kondmem.buffer   = NULL;
	kondmem.alloclen = 0;
	kondmem.datalen  = 0;

	/*-- no cat  or  a cat but no contingent ----------------------------*/
	pRes = &reservation[0];
	if (  (pRes->kat_id <= 0) ||
		  ((pRes->kat_id > 0 ) && (pRes->kont_id == (int)_UNDEF)) )
	{
		/*--- Allot ------------------------------------------*/
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_ALLOT, dbText, LEFTMARGIN);
		(void)fprintf(FPout, "%s%s", dbText, _P_EOL_);
	}

	/*-- contingent defined but not for that category   or  there is no place */
	if ((pRes->kat_id > 0 ) && (pRes->kont_id != (int)_UNDEF))
	{
		/*--- Kont Bez and reference -------------------------*/
		id = MPAPIselectOneId((int)_KONTINGENT, pRes->kont_id, (char *)&kon);
		if (id == (int)UNDEF)
		{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			EXIT_WITH_STATUS(MPERROR)
		}
		(void)AKTobjbez((int)_KONTINGENT, kon.bez_id, bez1);
		(void)copyTextTo(refText, kon.ref, _CHAR256);


		/*--- Kont_detail ------------------------------------*/
		(void)sprintf(query, _SEL_KONT_DETAIL_KID_KAT, pRes->kont_id, pRes->kat_id );
		status = MPAPIdb_sqlquery((int)_KONT_DETAIL, (char **)(&kondmem.buffer), query,
										&anzKond, &kondmem.datalen, &kondmem.alloclen );
		if (status == (int)MPOK )
			kond = (KONT_DETAIL *)kondmem.buffer;
		else
			EXIT_WITH_STATUS(MPERROR)

		/*--- check if there is place ------------------------*/
		pKond = &kond[0];
		if (anzKond > 0)
		{
			/*-- count all reservations for that category --------*/
			usedKon = MPAPIid_count((int)_KONTINGENT, (int)_RESERVATION, (char *)&kon);
			if (usedKon <= pKond->anz)
			{
				/*--- Cover Grp ----------*/
				(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_COVER_GRP, dbText, LEFTMARGIN);
				(void)fprintf(FPout, "%s GRP %s %s", dbText, bez1, refText );
			}
			else  /*-- no more place -*/
			{
				/*--- Allot Grp ------*/
				(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_ALLOT_GRP, dbText, LEFTMARGIN);
				(void)fprintf(FPout, "%s GRP %s %s", dbText, bez1, refText );
			}

		}
		else  /*-- no cat in this allot --------------*/
		{
			/*--- Allot Grp ------*/
			(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_ALLOT_GRP, dbText, LEFTMARGIN);
			(void)fprintf(FPout, "%s GRP %s %s", dbText, bez1, refText );
		}
	}

exit:
	/*--- Free from heap ------*/
	MPfreeobj(&kondmem);

	return(status);
}




/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestCatBerth ()
 *					print category, berth code and cabine number
 *
 *  In:			-
 *  out:			-
 *  Return:		-status
 *---------------------------------------------------------------------------
 */
static int OUTrequestCatBerth( int aDlnNumber)
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern DIENST_TRAEGER	dlt;
	extern REISENDER_TYP		dlnt;
	extern DLN_VIEW			dlnv;
	extern KATEGORIE			kat;

	int		status, id;
	char		tmp_buffer[_RECORDLEN];
	char     dlncodeTxt[_TEXTLEN];
	char     dbText[_TEXTLEN];
	char     defaultText[_TEXTLEN];
	char		bez1[_BEZLEN];
	char		*str ;

	/*--- inits -----------*/
	status = (int)MPOK ;

	/*-- Category ---------------------------------------------------------*/
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_DLNKAT, dbText, LEFTMARGIN);
	(void)fprintf(FPout, "%s", dbText);
	/*---- print KAT if present --------*/
	if (reservation[0].kat_id > 0)
	{
		id = MPAPIselectOneId((int)_KATEGORIE, reservation[0].kat_id, (char *)&kat);
		if (id == (int)UNDEF)
		{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			EXIT_WITH_STATUS(MPERROR)
		}
		(void)AKTobjbez((int)_KATEGORIE, kat.bez_id, bez1);
		(void)fprintf(FPout, " %s / ", bez1);
	}
	else
		(void)fprintf(FPout, " %s / ", "gtee");

	/*-- Berth code --------------------------------------------------------*/
	if (aDlnNumber == 1 )
	{
		/*-- Default text unless modified --------*/
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_SGL, defaultText, NOMARGIN);

		/*-- get dlncode -------------------------*/
		id = MPAPIselectOneId((int)_DLN_VIEW, reservation[0].pers_id, (char *)&dlnv);
		if (id == (int)UNDEF)
		{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			EXIT_WITH_STATUS(MPERROR)
		}
		if (dlnv.rkr_id > 0)
		{
			id = MPAPIselectOneId((int)_REISENDER_TYP, dlnv.rkr_id, (char *)&dlnt);
			if (id == (int)UNDEF)
			{
				AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
				EXIT_WITH_STATUS(MPERROR)
			}
			(void)copyTextTo(dlncodeTxt, dlnt.dlncode, _NUMLEN);

			/*-- check if dlncode is a berth code --*/
			(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_LB_GB, dbText, NOMARGIN);
			if ( (str = strstr( dbText, dlncodeTxt))  != NULL )
				(void)fprintf(FPout, "%s", dlncodeTxt);  /*--- alte Variante mit ReisenderTyp ---*/
			else
			{
				if ( reservation[0].typ_id != (int)_UNDEF && kat.typ_id != reservation[0].typ_id )
				{
					/*--- ein Bett wurde gewaehlt ---*/
					if (dlnv.sex == _FRAU )
					{
						/*--- LB ---*/
						str = strstr( dbText, ",");
						*str = (char)NULL;
						fprintf( FPout, "%s", dbText );
					}
					else
					{
						/*--- GB ---*/
						str = strstr( dbText, ",");
						str++;
						fprintf( FPout, "%s", str );
					}
				}
				else
					(void)fprintf(FPout, "%s", defaultText);   /*--- SGL ---*/
			}
		}
		else 	/*-- SGL ----------------------------*/
		{
			(void)fprintf(FPout, "%s", defaultText);
		}
	}

	/*-- Berth code for > 1 ----------------------*/
	if (aDlnNumber == 2 )
	{
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_DBL, dbText, NOMARGIN);
		(void)fprintf(FPout, "%s", dbText );
	}
	if (aDlnNumber == 3 )
	{
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_TPL, dbText, NOMARGIN);
		(void)fprintf(FPout, "%s", dbText );
	}
	if (aDlnNumber == 4 )
	{
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_QD, dbText, NOMARGIN);
		(void)fprintf(FPout, "%s", dbText );
	}

	/*-- Kabine Nr (DLT) ---------------------------------------------------*/
	if (reservation[0].dlt_id != (int)_UNDEF)
	{
		id = MPAPIselectOneId( (int)_DIENST_TRAEGER, reservation[0].dlt_id, (char *)&dlt);
		if (id != (int)_UNDEF )
		{
			(void)AKTobjbez( (int)_DIENST_TRAEGER, dlt.bez_id, tmp_buffer);
			(void)fprintf(FPout, "  %s%s", tmp_buffer, _P_EOL_);
		}
	}
	else
		(void)fprintf(FPout, "%s", _P_EOL_);

exit:
	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestText ()
 *					print the request text: whishes and special request
 *
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static int OUTrequestText()
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	char		tmp_buffer[_RECORDLEN];
	char		dbText[_CHAR80+1];
	int		status, len;

	/*--- inits -----------*/
	status = (int)MPOK ;

	/*-- request text if any -----------------------------*/
	(void)AKTobjtxt((int)_RESERVATION, reservation[0].textid, tmp_buffer, LEFTMARGIN);
	if ( len = strlen(tmp_buffer) > 0 )
	{
		(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_REQUESTS, dbText, LEFTMARGIN);
		(void)fprintf(FPout, "%s   %s%s", dbText, tmp_buffer, _P_EOL_);
	}
	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestPax ()
 *					print passenger names and stuff such as berth code...
 *					get text belonging to the passengers
 *
 *  In:			-
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
static int OUTrequestPax( int aDlnNumber)
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern 	REISENDER_TYP	dlnt;

	RESERVATION		*pRes;
	int		status, id;
	char		format[_CHAR80+1];
	char		sexTxt[_CHAR80+1];
	char		qualTxt[_CHAR80+1];
	char		ageTxt[_CHAR80+1];
	char		remarTxt[_RECORDLEN];
	char		tmp_buffer[_RECORDLEN];
	int		len,  grpuid, i, age;
	char		*ptr, *bufptr;

	/*--- inits -----------*/
	status = (int)MPOK ;

	/*--- all DLN's in this booking ----------------------------------------*/
	grpuid = (int)-2;
	for (i=0; i < anzRes && status == MPOK; i++)
	{
		pRes = &reservation[i];
		if (grpuid != pRes->pers_id)
		{
			/*-- Name and first name -------------------------*/
			id = MPAPIselectOneId((int)_DLN_VIEW, pRes->pers_id, (char *)&dlnv);
			if (id == (int)UNDEF)
			{
				AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
				EXIT_WITH_STATUS(MPERROR)
			}

			/*-- Birth date to Age conversion ----------------*/
			(void)copyTextTo(tmp_buffer, dlnv.age, _NUMLEN);
			age = AKTdateConvertToAge( tmp_buffer );
			if ( age == -1  )
				sprintf(ageTxt, "%s", "--" );
			if ( age == 0  )
				sprintf(ageTxt, "%s", " 1" );
			else if ((age > 0) && (age < 150))
				sprintf(ageTxt, "%d", age );
			else
				sprintf(ageTxt, "%s", "--" );


			/*-- Sex Mr-Ms -----------------------------------*/
			if (dlnv.sex == _FRAU )
				sprintf(sexTxt, "%s", "Mrs" );
			else
				sprintf(sexTxt, "%s", "Mr" );

			/*-- DLN type ------------------------------------*/
			if (dlnv.rkr_id > 0)
			{
				id = MPAPIselectOneId((int)_REISENDER_TYP, dlnv.rkr_id, (char *)&dlnt);
				if (id == (int)UNDEF)
				{
					AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
					EXIT_WITH_STATUS(MPERROR)
				}
				(void)copyTextTo(qualTxt, dlnt.dlncode, _NUMLEN);
			}
			else
				sprintf(qualTxt, "%s", " ");


			/*-- Write Dln texts --------------------------------------------*/
			if (i == 0)
			{
				/*-- number of pax ----------------*/
				(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_PAX, tmp_buffer, NOMARGIN);
				(void)sprintf(format, "%s%s%s", COL_0, COL_1, VAL_2 );
				(void)fprintf(FPout, format, " ", tmp_buffer, aDlnNumber);

				/*-- Name first name --------------*/
				(void)sprintf(format, "%s%s %s %s %s %s%s", COL_3, COL_4, COL_5,
				        COL_6, COL_7, COL_8, _P_EOL_);
				(void)fprintf(FPout, format, " ",
								  dlnv.name, dlnv.vor, sexTxt, qualTxt, ageTxt );
			}
			else
			{
				/*--No pax info only  Name first name etc --------------*/
				(void)sprintf(format, "%s%s %s %s %s %s%s", COL_TOT3, COL_4,
				              COL_5, COL_6, COL_7, COL_8, _P_EOL_);
				(void)fprintf(FPout, format, " ",
								  dlnv.name, dlnv.vor, sexTxt, qualTxt, ageTxt );
			}

			/*-- TEXTE intern ------------------------------------------------*/
			(void)AKTobjtxt((int)_PERSONEN, dlnv.textid, tmp_buffer, NOMARGIN);
			if ( len = strlen(tmp_buffer) > 0 )
			{
				(void)AKTobjtxt((int)_REQUEST_TYP, (int)AKTTXT_REMARKS, remarTxt, NOMARGIN);
				(void)sprintf(format, "%s%s%s%s",
								  COL_RMK0, COL_RMK1, COL_FREE, _P_EOL_ );
				bufptr = tmp_buffer;
				/*-- check how many lines of text ----------*/
				if ((ptr = strchr(tmp_buffer, '\n')) != NULL)
				{
					*ptr = '\0';
					bufptr = ++ptr;                     /* begin of next string */
					/*-- print line 1 --------*/
					(void)fprintf(FPout, format, " ", remarTxt, tmp_buffer);
					/*-- get next lines ------*/
					while ((ptr = strchr(bufptr, '\n')) != NULL)
					{
						*ptr = '\0';
						(void)fprintf(FPout, format,  " ",  " ", bufptr);
						bufptr = ++ptr;
					}
					/*-- last line  --------*/
					(void)fprintf(FPout, format,  " ",  " ", bufptr);
				}
				else   /*-- only 1 line of text -----------*/
					(void)fprintf(FPout, format, " ", remarTxt, tmp_buffer);

			}
			grpuid = pRes->pers_id;
		}
	}
exit:
	return(status);
}




/*F--------------------------------------------------------------------------
 *  Function:	OUTrequestDevice ()
 *					with "Kunden" infos, check if call number is present
 *					for device (fax or tlx)
 *					get recipient text for mail
 *					Start device action
 *  In:			-
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
static int OUTrequestDevice()
{
	extern DEVICE_PORT	devicePort;
	extern KUN_VIEW		kunv;

	int		status;
	char		faxNr[_TEXTLEN];
	char		tlxNr[_TEXTLEN];
	char		recip[_RECORDLEN];
	char     format[_RECORDLEN];
	int		faxl, tlxl, recipl ;
	DEVICE_PORT		*pDev;

	/*--- inits -----------*/
	pDev = &devicePort;
	status = (int)MPOK ;

	/*--- copy fax number ----------------------*/
	faxl = strlen (copyTextTo(faxNr, kunv.fax, (int)_CHAR256));
	if (faxl > 0)
		strcpy( pDev->faxnumber,  faxNr);
	/*--- copy telex number --------------------*/
	tlxl = strlen (copyTextTo(tlxNr, kunv.tlx, (int)_CHAR256));
	if (tlxl > 0)
		strcpy( pDev->callnumber, tlxNr);

	/*--- copy recipient -----------------------*/
	recipl = strlen (copyTextTo(recip, kunv.name, (int)_CHAR512));
	if (recipl > 0)
		strcpy( pDev->recipient, recip);

	/*--- Get printer command -------------------*/
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)PRINTCOMMAND, format, NOMARGIN);
	(void)sprintf(pDev->command, "%s", format);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)PRINTCOMMAND2, format, NOMARGIN);
	(void)sprintf(pDev->command2, "%s", format);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)PRINTCOMMAND3, format, NOMARGIN);
	(void)sprintf(pDev->command3, "%s", format);
	(void)AKTobjtxt((int)_REQUEST_TYP, (int)PRINTCOMMAND4, format, NOMARGIN);
	(void)sprintf(pDev->command4, "%s", format);

	/*--- Device start output -----------------------------------------------*/
	status = AKTdeviceOutput();
	if (status != MPOK)
	{
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");
		return(MPERROR);
	}

	return(status);
}


