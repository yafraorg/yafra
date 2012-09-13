/*D***********************************************************
 * Name:      AKTprice.c
 *
 * Modul:     AKT base moduls
 *            Price handling
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTprice.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */



/*P--- EXTERNALS -----------------------------------------------------------*/
extern 	int			DebugFlag;


/*P--- PROTOTYPES ----------------------------------------------------------*/
static int AKTpriceBestValidDatum  (  );
static int AKTpriceBestValidDatumForOneKar ( int low , int high );
static int AKTpriceBestDlDla       ( int low , int high );
static int AKTpriceBestDlDlaForOneKar ( int low , int high );
static int AKTpriceDynamicDate     ( int azeit, int ezeit );
static int AKTpriceBestKatidDlttid ( int lowix, int highix, int aKatid, int aDlttid );
static int AKTpriceBestKatid       ( int lowix, int highix, int aKatid );
static int AKTpriceBestDlttid      ( int lowix, int highix, int aTtypid );
static int AKTpriceBestRkrid       ( int lowix, int highix, int aKatid );
static int AKTpriceBestKontid      ( int lowix, int highix, int aKontid );
static int AKTpriceBestDatum       ( int lowix, int highix, int azeit, int ezeit );
static void AKTpriceElliminateKar  (void);
static void AKTpriceDebugPrintAll  (void);
static int AKTpriceCheckDebitor    ( PRICERESULT *pPrice, int *exists );
static int AKTpriceInsertDebitor   ( PRICERESULT *pPrice, BUCHUNG *pBch, int akt_nr, double reduktion, double kommission );
static int AKTpriceUpdateDebitor   ( PRICERESULT *pPrice, BUCHUNG *pBch, int akt_nr, double reduktion, double kommission );
static int ManageWhr(PREIS, PREIS *, LAND_WHR *);

int AKTpriceVerifyForOneKar        (int, int, RESERVATION *, int);
int AKTpricePrintAllValid          (void);

/*--- SQL ----------*/
#define _SEL_PRE_DLA_DLG		"SELECT * FROM TDBADMIN.PREIS \
	WHERE  (DLA_ID = %d   OR DL_ID = %d) AND GLT <= %d  \
	ORDER  BY KAR_ID, DLA_ID, DL_ID, GLT desc, DL_VONDAT, KAT_ID, DLTT_ID, RKR_ID, KONT_ID ;"


#ifdef DIETER_NEU
/*--- SQL ---------*/
#define _SEL_PRE_DLA_DLG		"SELECT * FROM TDBADMIN.PREIS \
	WHERE  (DLA_ID = %d   OR DL_ID = %d) AND GLT <= %d  \
	ORDER  BY GLT, DLA_ID, DL_ID, DL_VONDAT, KAR_ID, KAT_ID, DLTT_ID, RKR_ID, KONT_ID ;"
#endif


#define _SEL_DEBITOR_CHK		"SELECT count(*) FROM TDBADMIN.MP_DEBITOR \
	WHERE  BID = %d \
   AND    PERS_ID = %d \
   AND    TDL_ID = %d \
   AND    DLG_ID = %d \
   AND    TEIL = %d ;"

#define _UPD_DEBITOR          "UPDATE TDBADMIN.MP_DEBITOR \
SET  KBST = %d, \
     KID = %d, \
     ART_ID = %d, \
     KONT_ID = %d, \
     KOL_ID = %d, \
     KAT_ID = %d, \
     RKR_ID = %d, \
     KONTO = \'%s\', \
     AKT_NR = %d, \
     KAR_ID = %d, \
     APR = %f, \
     EPR = %f, \
     VPR = %f, \
     reduktion = %f, \
     kommission = %f, \
     FAKT_ZEIT = %d, \
     CRUE_ZEIT = %d \
   WHERE  BID = %d \
   AND    PERS_ID = %d \
   AND    TDL_ID = %d \
   AND    DLG_ID = %d \
   AND    TEIL = %d ;"

#define _INS_DEBITOR "INSERT INTO TDBADMIN.MP_DEBITOR VALUES( %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\'%s\',%d,%d,%f,%f,%f,%f,%f,%d,%d );"

/*--- DEFINES --------------------------------------------------------------*/
#define PRICEMEMCHUNK		20
#define _PRICE_NOTFOUND 	3
#define _PRICE_ALL 			2
#define _PRICE_ONE			1
#define _PRICE_ERROR      	0

#define _PRICE_KATID_DLTTID     1
#define _PRICE_ONLY_DLTTID      2
#define _PRICE_ONLY_KATID       3
#define _PRICE_NO_KATID_DLTTID  4

#define _PRICE_AKTTXT_KARGROUP  19

/*--- GLOBAL ---------------------------------------------------------------*/
PRICERESULT debitor;


/*F--------------------------------------------------------------------------
 * Function:  AKTpriceMemobjInit
 *            init memory for operations
 *---------------------------------------------------------------------------
 */
void AKTpriceMemobjInit( )
{
	extern	MEMOBJ		preismem;
	extern	PREIS			*preis ;
	extern	MEMOBJ		matrixmem;
	extern	PRICERESULT	*priceMatrix;

	/*--- Preis --------------*/
	preis  = (PREIS *)NULL;
	preismem.buffer = NULL;
	preismem.alloclen = 0;
	preismem.datalen = 0;

	/*--- Price matrix -------*/
	priceMatrix  = (PRICERESULT *)NULL;
	matrixmem.alloclen = 0 ;
	matrixmem.datalen  = 0 ;
	matrixmem.buffer = NULL;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTpriceMemobjFree
 *            release memory for operations
 *---------------------------------------------------------------------------
 */
void AKTpriceMemobjFree( )
{
	extern	MEMOBJ		preismem;
	extern	MEMOBJ		matrixmem;

	/*--- Preis --------------*/
	MPfreeobj(&preismem);
	MPfreeobj(&matrixmem);
	/*--- re-init for next ---*/
	AKTpriceMemobjInit();
}



/*F************************************************************
 * Function:  AKTpriceFindAll
 *            look for all prices for a Dla or a Dln
 * in:        category, reisendertyp, dlangebot
 * out:
 * return:    success code
 **************************************************************/
int AKTpriceFindAll( int aDlaid, int aDlid )
{
	extern	DIENST_ANGEBOT	dla;
	extern	DIENST_TRAEGER dlt;
	extern	MEMOBJ		preismem ;
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		status;
	char		query[2*RECLAENGE];
	time_t	today;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- get current time ---------*/
	(void)time( &today );

	/*--- get a large set of possible prices -------------------------------*/
	if ((aDlaid != (int)_UNDEF) || (aDlid != (int)_UNDEF))
	{
		(void)sprintf(query, _SEL_PRE_DLA_DLG, aDlaid, aDlid, today );
		status = MPAPIdb_sqlquery((int)_PREIS, (char **)(&preismem.buffer), query,
										  &anzPreis, &preismem.datalen, &preismem.alloclen );
		if (status == (int)MPOK )
			preis = (PREIS *)preismem.buffer;
		else
			status = (int)MPERROR;
	}
	else
		status = (int)MPERROR;

	return(status);
}


/*F************************************************************
 * Function:  AKTpriceVerify
 *            verify if all criteria are filled, otherwise
 *            eliminate that price
 * in:
 * out:
 * return:    status  (== MPOK, MPERROR, NO
 **************************************************************/
int AKTpriceVerify( RESERVATION	*pRes, int aRkrid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, old_kar_id,  status;
	int		lowix, highix;
	PREIS		*pPreis, *pNextPreis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- Test if one price minimum -------------*/
	if (anzPreis <= 0 )
		return ((int)MPERROR )	;                              /* >>>>> exit */

#ifdef _DIETER_NEU
	/*--- find start of most recent "Gultig ab Datum" -----------*/
	start = AKTpriceBestValidDatum();

	/*--- Check DL or DLA price ----------------------------------*/
	end = AKTpriceBestDlDla( start, anzPreis );
#endif

	/*--- Special case if one preis -----------------------------*/
	if (anzPreis == 1 )
	{
		lowix  = 0 ;
		highix = anzPreis ;
		/*-- verify for that kostenart -------*/
		status = AKTpriceVerifyForOneKar( lowix, highix, pRes, aRkrid );

		if (status == (int)_PRICE_ERROR )
			return ((int)MPERROR )	;                           /* >>>>> exit */
	}
	else
	{
		/*--- more than one price -----------------------------------*/
		/*--- find KAR_ID boundary limits low and high --------------*/
		for (k=0;  k < anzPreis;  k++)
		{
			pPreis = &preis[k];
			/*--- first loop --------------*/
			if ( k == 0 )
			{
				lowix = k;
				old_kar_id = pPreis->kar_id;
				continue;
			}
			/*--- kar change or end of loop --------------------------*/
			if (k < anzPreis-1 )
			{
				/*--- look ahead is possible to find kar-id change ---*/
				pNextPreis = &preis[k+1];
				if (pNextPreis->kar_id != old_kar_id)
				{
					highix = k + 1;
					/*..... Debug ........*/
						if (DebugFlag)
						{
						fprintf( stderr, "%s Verify for kar_id boundary: low-high: %d   %d-%d %s", _P_EOL_ ,
						pPreis->kar_id, lowix, highix, _P_EOL_ );
						}
						/*-- verify for that kostenart -------*/
					status = AKTpriceVerifyForOneKar( lowix, highix, pRes, aRkrid );

					if (status == (int)_PRICE_ERROR )
						return ((int)MPERROR )	;                           /* >>>>> exit */

					lowix = highix;
					old_kar_id = pNextPreis->kar_id;
				}
			}
			else
			{
				/*-- it is the last ------*/
				highix = k + 1;

				/*-- verify for that kostenart -------*/
				status = AKTpriceVerifyForOneKar( lowix, highix, pRes, aRkrid );

				if (status == (int)_PRICE_ERROR )
					return ((int)MPERROR )	;                           /* >>>>> exit */

			}
		}
	}

	return( (int)MPOK );

#ifdef _DIETER_NEU
	/*--- there must be a price otherwise return MPERROR */
   if ( AKTpriceCountValid( ) > 0 )
	{
		return( (int)MPOK );
	}
	else
	{
		return ((int)MPERROR);
	}
#endif

}


/*F--------------------------------------------------------------------------
 * Function:  AKTpriceVerifyForOneKar
 *            verify if all criteria are filled, for one kosten art
 *            Most functions have low and high limits indexes to search
 * in:
 * out:
 * return:    status
 *---------------------------------------------------------------------------
 */
int AKTpriceVerifyForOneKar( int lowix, int highix, RESERVATION *pRes, int aRkrid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		status;

	/*--- general inits ------------*/
	status = (int)_PRICE_NOTFOUND ;

	/*--- Start / End date check ------------------------------------------*/
	status = AKTpriceDynamicDate( pRes->a_zeit, pRes->e_zeit);
	if (DebugFlag)
		AKTpriceDebugPrintAll( );
	if (status == (int)_PRICE_ERROR )
		return (status);                                /* >>>>> exit */

	/*--- Qualify Kategorie + Traegertyp ----------------------------------*/
	status = AKTpriceBestKatidDlttid ( lowix, highix, pRes->kat_id, pRes->typ_id);
	if (status == (int)_PRICE_ERROR )
		return (status);

	/*--- Traegertyp, before Kategorie ------------------------------------*/
	status = AKTpriceBestDlttid( lowix, highix, pRes->typ_id );
	if (DebugFlag)
		AKTpriceDebugPrintAll( );

	if (status == (int)_PRICE_ERROR )
		return (status);                                /* >>>>> exit */

	/*--- Kategorie --------------------------------------*/
	status = AKTpriceBestKatid ( lowix, highix, pRes->kat_id);
	if (DebugFlag)
		AKTpriceDebugPrintAll( );
	if (status == (int)_PRICE_ERROR )
		return (status);                                /* >>>>> exit */

	/*--- Reisender Typ check ---------------------------------------------*/
	status = AKTpriceBestRkrid( lowix, highix, aRkrid);
	if (DebugFlag)
		AKTpriceDebugPrintAll( );
	if (status == (int)_PRICE_ERROR )
		return (status);                                /* >>>>> exit */

	/*--- Kontigent check -------------------------------------------------*/
	status = AKTpriceBestKontid( lowix, highix, pRes->kont_id);

	/*--- Check DL or DLA price ----------------------------------*/
	status = AKTpriceBestDlDlaForOneKar( lowix, highix );
	if (DebugFlag)
		AKTpriceDebugPrintAll( );
	if (status == (int)_PRICE_ERROR )
		return (status);

	/*--- find start of most recent "Gultig ab Datum" -----------*/
	status = AKTpriceBestValidDatumForOneKar( lowix, highix );
	if (DebugFlag)
		AKTpriceDebugPrintAll( );
	if (status == (int)_PRICE_ERROR )
		return (status);                                /* >>>>> exit */

	return( (int)_PRICE_ALL );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceMatrixPrepare ()
 *					get DLA and get prices
 *  In:			-reisender typ
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int AKTpriceMatrixPrepare( int aDlnid, int aRkrid, int aDlid )
{
	extern DLN_VIEW			dlnv;
	extern KOSTEN_ART		kar;
	extern DIENST_TRAEGER dlt;
	extern DIENST_ANGEBOT	dla;
	extern RESERVATION	*reservation ;
	extern int			anzRes;
	extern PREIS			*preis ;
	extern int			anzPreis;
	extern PRICERESULT		*priceMatrix;
	extern MEMOBJ		matrixmem;
	extern int			anzMatrix;
	extern int LWwhrid;
	extern int LWlandid;

	PREIS newpre;
	LAND_WHR usedlw;
	DLG_PART			dlg_part;
	PREIS				*pPreis;
	RESERVATION		*pRes;
	PRICERESULT		*pPrMat;
	int		m, k, id, status;
	int		theDlaid ;

	/*--- inits ------------------*/
	status = (int)MPOK ;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	anzMatrix = 0;
	for (k=0;  k < anzRes;  k++)
		{
		pRes = &reservation[k];

		/*--- valid Dl for operation ------------------------------------*/
		if (pRes->dlg_id != (int)_UNDEF )
			{
			/*--- Dl restriction check ------------------------------------*/
			if ((aDlid != (int)_UNDEF) && (pRes->dlg_id != aDlid))
				{
				continue;                     /* it is not the target DL */
				}

			/*--- find dla  !! mw special trick !!! through dlt ----------------*/
			status = MPAPIselectDLT( (int)_UNDEF, (int)_UNDEF, pRes->dlg_id, &dlt);
			if (status != (int)MPOK)
				{
				AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
				return( (int)MPERROR );                           /* >>>> exit */
				}
			else
				theDlaid = dla.dla_id;

			/*--- get prices --------------------------------------------*/
 			status = AKTpriceFindAll( theDlaid, pRes->dlg_id);
			if (status != (int)MPOK)
				{
				AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
				return ( (int)MPERROR );                             /* >>>> exit */
				}

			/*--- there must be a price otherwise smthg is wrong --------*/
			status =  AKTpriceVerify( pRes, aRkrid );
			if ( status == (int)MPERROR )
				{
				if (DebugFlag)
					{
					AKTmailPriceProblem( pRes->bid, pRes->dlg_id);
					AKTpricePrintAllValid( );
					}
				}

#ifdef _KOSTENARTEN
			/*--- Auswaehlen von Kosenarten ---*/
			AKTpriceElliminateKar( );
#endif

			/*--- Dl_part bez for res_flag --------*/
			id = MPAPIselectTDL( pRes->dlg_id, &dlg_part);

			/*--- Build price matrix ------------------------------------------*/
			for (m=0;  m < anzPreis;  m++)
				{
				pPreis = &preis[m];
				/*--- Kosten art  -------------*/
				if (( pPreis->pre_id != (int)_UNDEF) && (pPreis->kar_id != (int)_UNDEF) )
					{
					/*--- Price matrix -----------------------*/
					matrixmem.datalen = (anzMatrix+1)* sizeof(PRICERESULT);
					matrixmem.buffer = (char *)MPallocobj( &matrixmem,
												  PRICEMEMCHUNK * sizeof(PRICERESULT) );
					priceMatrix = (PRICERESULT *)matrixmem.buffer;
					pPrMat = &priceMatrix[anzMatrix];
					pPrMat->preid    = pPreis->pre_id ;
					pPrMat->bid      = pRes->bid ;
					pPrMat->dlnid    = aDlnid ;
					pPrMat->karid    = pPreis->kar_id ;
					pPrMat->dlttid   = pPreis->dltt_id ;
					pPrMat->katid    = pRes->kat_id ;
					pPrMat->rkrid    = aRkrid ;
					pPrMat->dlaid    = theDlaid ;
					pPrMat->tdlid    = dlg_part.dl_id ;
					pPrMat->dlgid    = pRes->dlg_id ;
					pPrMat->teil     = pRes->teil ;
					pPrMat->kontid   = pRes->kont_id ;
					pPrMat->resflag  = dlg_part.res_f;
					pPrMat->azeit    = pRes->a_zeit;
					pPrMat->ezeit    = pRes->e_zeit;
					pPrMat->ankaufVal   = pPreis->apr;
					pPrMat->einstandVal = pPreis->epr;
					pPrMat->verkaufVal  = pPreis->vpr;
					if (pPreis->whr_id != LWwhrid)
						{
						usedlw.land_id = LWlandid;
						usedlw.whr_id = pPreis->whr_id;
						usedlw.kurs_typ = _KURS_CREDIT;
						status = ManageWhr(*pPreis, &newpre, &usedlw);
						if (status == MPOK)
							{
							pPrMat->ankaufVal   = newpre.apr;
							pPrMat->einstandVal = newpre.epr;
							pPrMat->verkaufVal  = newpre.vpr;
							pPreis->whr_id  = usedlw.whr_id;
							}
						else
							{
							status = MPOK;
							if (DebugFlag)
								(void)fprintf(stderr, "debug: exchange rate not in DB for LAND %d and WHR %d%s", usedlw.land_id, usedlw.whr_id, _P_EOL_);
							}
						}
					anzMatrix++ ;
					}
				}
			}
		}

	return ( (int)MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceMatrixGetSum ()
 *					get all prices and give back the sum
 *  In:			-
 *  out:			-price value
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void AKTpriceMatrixGetSum( double *preisVal, int aKarid )
{
	extern	PRICERESULT		*priceMatrix;
	extern	int				anzMatrix;

	PRICERESULT	*pMat;
	int			k;
	double		totalVal;

	/*--- inits -------*/
	totalVal = 0.0;

	/*--- Sum all prices -----------*/
	for (k=0;  k < anzMatrix;  k++)
		{
		pMat = &priceMatrix[k];
		if (aKarid != (int)UNDEF)
			{
			if (pMat->karid == aKarid)
				totalVal += pMat->verkaufVal;        /* sum for same karid */
			}
		else
			totalVal += pMat->verkaufVal;           /* sum all */
		}

	/*--- give back the total -------*/
	*preisVal = totalVal;
}

/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceMatrixGetAESum ()
 *					get all einstand/ankauf prices and give back the sum
 *  In:			-
 *  out:			-price value
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void AKTpriceMatrixGetAESum( double *aAval, double *aEval, int aKarid )
{
	extern	PRICERESULT		*priceMatrix;
	extern	int				anzMatrix;

	PRICERESULT	*pMat;
	int			k;
	double		totalAval;
	double		totalEval;

	/*--- inits -------*/
	totalAval = 0.0;
	totalEval = 0.0;

	/*--- Sum all prices -----------*/
	for (k=0;  k < anzMatrix;  k++)
		{
		pMat = &priceMatrix[k];
		if (aKarid != (int)UNDEF) /* only prices for same KOSTENART */
			{
			if (pMat->karid == aKarid)
				{
				totalAval += pMat->ankaufVal;        /* sum for same karid */
				totalEval += pMat->einstandVal;        /* sum for same karid */
				}
			}
		else /* prices for all KOSTENART */
			{
			totalAval += pMat->ankaufVal;
			totalEval += pMat->einstandVal;
			}
		}

	/*--- give back the total -------*/
	*aAval = totalAval;
	*aEval = totalEval;
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceGetAll ()
 *					get all prices and give back the sum
 *  In:			-
 *  out:			-price value
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void AKTpriceGetAll( double *preisVal)
{
	extern	KOSTEN_ART		kar;
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int	k;
	PREIS		*pPreis;
	double	unitVal, totalVal;                              /* unit prices             */

	/*--- inits --------------*/
	totalVal = 0.0;

	/*--- Sum all valid prices -----------------*/
	for (k=0;  k < anzPreis;  k++)
		{
		pPreis = &preis[k];
		/*--- valid price? ----*/
		if ( pPreis->pre_id != (int)_UNDEF )
			{
			unitVal = pPreis->vpr ;
			totalVal += unitVal;
			}
		}

	/*--- give back the value of total preis array -------*/
	*preisVal = totalVal;
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceCountValid ()
 *					scan all prices and count valid one
 *  In:			-
 *  out:			-
 *  Return:		-count
 *---------------------------------------------------------------------------
 */
int AKTpriceCountValid( )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, count;
	PREIS		*pPreis;

	/*--- count valid prices ----------*/
	count = 0;
	for (k=0;  k < anzPreis;  k++)
		{
		pPreis = &preis[k];
		if ( pPreis->pre_id != (int)_UNDEF )
			count++;
		}
	return (count);
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpricePrintAllValid ()
 *					scan all prices and count valid one
 *  In:			-
 *  out:			-
 *  Return:		-count
 *---------------------------------------------------------------------------
 */
int AKTpricePrintAllValid(void)
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;
	extern   char		   mailstring[];

	char	   format[_RECORDLEN];
	int		k, count;
	PREIS		*pPreis;

	AKTmsgget( MPA_PRICEDESCRIPT, format);

	/*--- Print valid prices ----------*/
	for (k=0, count=0;  k < anzPreis;  k++)
		{
		pPreis = &preis[k];
		if ( pPreis->pre_id != (int)_UNDEF )
			{
			count++;
			(void)sprintf(mailstring, format, pPreis->pre_id, pPreis->dltt_id, pPreis->kat_id,
							  pPreis->rkr_id, pPreis->dla_id, pPreis->dl_id );
			AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

			}
		}

	AKTmsg( ACT_INFO, (int)_UNDEF, _P_EOL_ );
	AKTmsgget( MPA_PRICECOUNTER, format);
	(void)sprintf( mailstring, format, count );
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

	return ( (int)MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceTrialDebitor ( )
 *					check if the debitor Flag is set
 *  In:			- pRes RESERVATION
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int AKTpriceTrialDebitor( void )
{
	extern int debitorflag; /* -J flag */

	PRICERESULT aPrice;
	int exists;
	int status = (int)MPOK;

	if ( debitorflag == (int)FALSE )
		return ( status );

	/*-- check existance of MP_DEBITOR table ---*/
	aPrice.bid = (int)_UNDEF;
	aPrice.dlnid = (int)_UNDEF;
	aPrice.tdlid = (int)_UNDEF;
	aPrice.dlgid = (int)_UNDEF;
	aPrice.teil = (int)_UNDEF;

	status = AKTpriceCheckDebitor( &aPrice, &exists );

	if ( status != (int)MPOK )
		debitorflag = (int)FALSE;

	/*-- return MPOK or MPERROR ---*/
	return (status);
}

/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceWriteDebitor ( )
 *					put the Debitor entry into the database
 *  In:			- pRes RESERVATION
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int AKTpriceWriteDebitor  ( PRICERESULT *pPrice,
									 BUCHUNG *pBch,
									 int akt_nr,
									 double reduktion, double kommission )
{
	int exists;
	int status = (int)MPOK;

	status = AKTpriceCheckDebitor( pPrice, &exists );
	if( status != (int)MPOK )
		return( status );

	if ( exists == (int)FALSE )
		{
		status = AKTpriceInsertDebitor(pPrice, pBch, akt_nr, reduktion, kommission );
		if( status != (int)MPOK )
			{
			AKTmsg( ACT_ERROR, MPA_DBERROR, NULL);
			return( (int)MPERROR );
			}
		}
	else
		{
		status = AKTpriceUpdateDebitor( pPrice, pBch, akt_nr, reduktion, kommission );
		if( status != (int)MPOK )
			{
			AKTmsg( ACT_ERROR, MPA_DBERROR, NULL);
			return( (int)MPERROR );
			}
		}
}

/************************ STATIC FUNCTIONS ***********************************/
/*****************************************************************************/


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestValidDatum ()
 *					scan all prices and keep only the most recent "Gultig ab"
 *  In:			-
 *  out:			-
 *  Return:		- the start index
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestValidDatum( )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		old_glt, lowindex ;
	PREIS		*pPreis;


	/*--- special case of One price ---------------------*/
	if ( anzPreis == 1  )
	{
		return (0);                                     /*>>>>>>> exit >>*/
	}

	/*--- loop INVERSE to find best gultigab ------------*/
	for (k=anzPreis-1;  k >= 0;  k--)
	{
		pPreis = &preis[k];
		if (k == anzPreis-1 )
		{
			old_glt = pPreis->glt ;
			continue;
		}
		/*-- gultig changes or this is the last price -*/
		if ((pPreis->glt != old_glt) || (k == 0))
		{
			if (k == 0)
				lowindex = 0;
			else
				lowindex = k + 1;
			break;
		}
	}

	/*--- eliminate bad gultigab -------------------------*/
	for (k=0;  k < lowindex;  k++)
	{
		pPreis = &preis[k];
		pPreis->pre_id = (int)_UNDEF;
	}

	/*--- results ------------*/
	return (lowindex);
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestValidDatumForOneKar( int low , int high )
 *					scan all prices of one KAR and keep
 *             only the most recent "Gultig ab"
 *  In:			-
 *  out:			-
 *  Return:		- status : _PRICE_ONE _PRICE_ALL
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestValidDatumForOneKar( int low , int high )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, PriceFound, status ;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_ALL ;
	PriceFound = (int)_PRICE_NOTFOUND;

	/*--- special case of One price ---------------------*/
	if ( anzPreis == 1  )
	{
		return ( (int)_PRICE_ONE );               /*>>>>>>> exit >>*/
	}

	/*--- loop to find best gultigab ------------*/
	for (k = low;  k < high;  k++)
	{
		pPreis = &preis[k];
		if ( pPreis->pre_id != (int)_UNDEF )
		{
			if ( PriceFound == (int)_PRICE_NOTFOUND )
			{
				/*--- This is the best gultigAb --------*/
				/*--- because of order by (GLT desc) ---*/
				PriceFound = (int)_PRICE_ONE;
			}
			else
			{
				/*--- This prices are no longer valid -------*/
				pPreis->pre_id = (int)_UNDEF;
			}
		}
	}

	/*--- results ------------*/
	return ( status );
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestDlDla ( int low , int high )
 *					scan all prices and find if prices are for DL or DLA
 *  In:			-
 *  out:			-
 *  Return:		-new high index
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestDlDla( int low , int high )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, highindex, DLfound ;
	PREIS		*pPreis;

	/*--- default ----------------*/
	highindex = high ;

	/*--- loop to find DL prices -----------------------------------*/
	DLfound = 0;
	for (k=low;  k < high;  k++)
	{
		pPreis = &preis[k];
		/*--- DL prices ? -------*/
		if (pPreis->dl_id != (int)_UNDEF)
		{
			DLfound = 1;
			highindex = k + 1;
		}
		else
			break;   /* DLA prices strech till end -*/
	}

	/*--- remove DLA prices if there are DL prices -----------------*/
	if (DLfound == 1)
	{
		for (k=highindex;  k < high;  k++)
		{
			pPreis = &preis[k];
			pPreis->pre_id = (int)_UNDEF;
		}
	}

	/*-- give new high limit -----*/
	return( highindex);
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestDlDlaForOneKar ( int low , int high )
 *					scan all prices of one KAR and find if prices are for DL or DLA
 *  In:			-
 *  out:			-
 *  Return:		-new high index
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestDlDlaForOneKar( int low , int high )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, highindex, DLfound, status ;
	PREIS		*pPreis;

	/*--- default ----------------*/
	highindex = high ;
	status = (int)_PRICE_ALL;

	/*--- loop to find DL prices -----------------------------------*/
	DLfound = 0;
	for (k=low;  k < high;  k++)
	{
		pPreis = &preis[k];
		/*--- DL prices ? -------*/
		if ( pPreis->pre_id != (int)_UNDEF && pPreis->dl_id != (int)_UNDEF)
		{
			DLfound = 1;
			highindex = k + 1;
		}
		else
			break;   /* DLA prices strech till end -*/
	}

	/*--- remove DLA prices if there are DL prices -----------------*/
	if (DLfound == 1)
	{
		for (k=highindex;  k < high;  k++)
		{
			pPreis = &preis[k];
			pPreis->pre_id = (int)_UNDEF;
		}
	}

	return( status );
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceDynamicDate ()
 *					scan all prices and look for DL prices
 *					if a price is available in the date gap keep it
 *
 *  In:			- a kontingent
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static int AKTpriceDynamicDate( int azeit, int ezeit )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, found, status;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_ALL ;

	/*--- check if there are prices for DL -----------*/
	found = 0;
	for (k=0;  k < anzPreis;  k++)
	{
		pPreis = &preis[k];
		if (pPreis->dl_id != (int)_UNDEF)
		{
			found = 1;
			break;
		}
	}
	return ( status );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestKatidDlttid ()
 *					scan all prices and try to find prices matching either a
 *					a category or a dlttype but not the two
 *					No price at all is not ok
 *  In:			-limits for loop, a category, a dlttid
 *  out:			-
 *  Return:		- special codes
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestKatidDlttid( int lowix, int highix, int aKatid, int aDlttid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		priceTest  ;
	int		status;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_NOTFOUND;
	priceTest = (int)_PRICE_ERROR;

	/*--- look if prices exist with a kat_id ----*/
	for (k=lowix;  k < highix;  k++)
	{
		pPreis = &preis[k];
		if (pPreis->pre_id != (int)_UNDEF)
		{
			if ((pPreis->kat_id == aKatid) && (pPreis->dltt_id == aDlttid))
			{
				priceTest = (int)_PRICE_KATID_DLTTID ;
				break;
			}
			if ((pPreis->kat_id == (int)_UNDEF) && (pPreis->dltt_id == aDlttid))
			{
				priceTest = (int)_PRICE_ONLY_DLTTID ;
				break;
			}
			if ((pPreis->kat_id == aKatid) && (pPreis->dltt_id == (int)_UNDEF))
			{
				priceTest = (int)_PRICE_ONLY_KATID ;
				break;
			}
			if ((pPreis->kat_id == (int)_UNDEF) && (pPreis->dltt_id == (int)_UNDEF))
			{
				priceTest = (int)_PRICE_NO_KATID_DLTTID ;
				break;
			}
		}
	}

	switch (priceTest)
	{
		case (int)_PRICE_KATID_DLTTID:     /*--- both have prices handle as one with priority */
		case (int)_PRICE_ONLY_DLTTID:      /*--- take price of dltt      */
		case (int)_PRICE_ONLY_KATID:       /*--- take price of category   */
			status = (int)_PRICE_ONE ;
			break;

		case (int)_PRICE_NO_KATID_DLTTID:  /*--- No cat or dltt price critria found ---*/
			status = (int)_PRICE_ALL ;
			break;
	}

	return ( status );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestDlttid ()
 *					scan all prices to find one with Traegertyp
 *					in this case if a Traegertyp is defined take this one
 *					if NO Traegertyp is defined eliminate these without
 *  In:			-limits for loop, a Traegertyp
 *  out:			-
 *  Return:		- special codes
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestDlttid( int lowix, int highix, int aDlttid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		found, minusone, status;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_NOTFOUND ;

	/*--- look if prices exist with a Traegertyp ----*/
	found = 0;
	for (k=lowix;  k < highix;  k++)
	{
		pPreis = &preis[k];
		/* if (( pPreis->dltt_id != (int)_UNDEF) && (pPreis->pre_id != (int)_UNDEF)) */
		if ( pPreis->dltt_id == aDlttid && (pPreis->pre_id != (int)_UNDEF))
		{
			found = 1;
			break;
		}
	}

	/*--- There are prices and a Traegertyp is defined ? -------------------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( (pPreis->dltt_id != aDlttid) && (pPreis->pre_id != (int)_UNDEF))
			{
				pPreis->pre_id = (int)_UNDEF;
			}
		}
		/*-- one price has been found ------*/
		status = (int)_PRICE_ONE ;
	}
	else
	/*--- no price with Traegertyp or aDlttid is not defined -------------*/
	{
		/*--- look for a price with traegertyp -1 --*/
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( pPreis->dltt_id == (int)_UNDEF )
			{
				minusone = 1;
				break;
			}
		}
		if ( minusone )
		{
			/*--- eliminate these with dltt_id since there is one without  */
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ((pPreis->dltt_id != (int)_UNDEF) && (pPreis->pre_id != (int)_UNDEF))
					pPreis->pre_id = (int)_UNDEF;
			}
			/*-- a price for all (-1) has been found ---*/
			status = (int)_PRICE_ALL ;
		}
		else
		{
			/*--- eliminate other no price found for dltt ------------*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ( (pPreis->dltt_id != aDlttid) && (pPreis->pre_id != (int)_UNDEF))
				{
					pPreis->pre_id = (int)_UNDEF;
				}
			}
			/*-- no price has been found all are deleted ---*/
			status = (int)_PRICE_NOTFOUND ;
		}
	}
	return ( status );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestKatid ()
 *					scan all prices and try to find prices with a category
 *					in this case and if a Kategorie is defined take this one
 *					if NO Kategorie is defined eliminate these without
 *  In:			-limits for loop, a category
 *  out:			-
 *  Return:		- special codes
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestKatid( int lowix, int highix, int aKatid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		found, minusone, status;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_NOTFOUND ;

	/*--- look if prices exist with a kat_id ----*/
	found = 0;
	if (aKatid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ((pPreis->kat_id == aKatid) && (pPreis->pre_id != (int)_UNDEF))
			{
				found = 1;
				break;
			}
		}
	}
	/*--- There are prices for Categories and aKatid is defined ----------*/
	if ( found )
	{
		/*--- eliminate other categories --*/
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( (pPreis->kat_id != aKatid) && (pPreis->pre_id != (int)_UNDEF))
			{
				pPreis->pre_id = (int)_UNDEF;
			}
		}
		/*-- one price has been found ------*/
		status = (int)_PRICE_ONE ;
	}
	else
	/*--- there are no prices with Categorie or aKatid is not defined -------*/
	{
		/*--- look for a price without category otherwise something is wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( pPreis->kat_id == (int)_UNDEF )
			{
				minusone = 1;
				break;
			}
		}
		if ( minusone )
		{
			/*--- eliminate these with kategories since there is one without  */
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ((pPreis->kat_id != (int)_UNDEF) && (pPreis->pre_id != (int)_UNDEF))
					pPreis->pre_id = (int)_UNDEF;
			}
			/*-- a price for all (-1) has been found ---*/
			status = (int)_PRICE_ALL ;
		}
		else
		{
			/*--- eliminate other categories --*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ( (pPreis->kat_id != aKatid) && (pPreis->pre_id != (int)_UNDEF))
				{
					pPreis->pre_id = (int)_UNDEF;
				}
			}
			/*-- no price has been found all are deleted ---*/
			status = (int)_PRICE_NOTFOUND ;
		}
	}
	return ( status );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestRkrid ()
 *					scan all prices and try to find prices with a rkr-id
 *					in this case and if a rkr is defined take this one
 *					if NO rkr is defined eliminate these without
 *  In:			-limits for loop, a reisender-typ
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestRkrid( int lowix, int highix, int aRkrid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		found, minusone, status ;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)_PRICE_NOTFOUND ;

	/*--- look if rkr is a criteria of selection and if there is a price --*/
	found = 0;
	if (aRkrid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ((pPreis->rkr_id == aRkrid) && (pPreis->pre_id != (int)_UNDEF))
			{
				found = 1;
				break;
			}
		}
	}

	/*--- a price is found so eliminate non matching Reisender-typ ---*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if (  (pPreis->rkr_id != aRkrid) && (pPreis->pre_id != (int)_UNDEF) )
			{
				pPreis->pre_id = (int)_UNDEF;
			}
		}
		/*-- one price has been found ------*/
		status = (int)_PRICE_ONE ;
	}
	else
	{
		/*--- look for a price without Reisender-typ otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( pPreis->rkr_id == (int)_UNDEF )
			{
				minusone = 1;
				break;
			}
		}
		/*--- is there a price without Reisender-typ (-1) ? ---------*/
		if ( minusone )
		{
			/*--- eliminate these with Reisender-typ --*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ((pPreis->rkr_id != (int)_UNDEF) && (pPreis->pre_id != (int)_UNDEF))
					pPreis->pre_id = (int)_UNDEF;
			}
			/*-- a price for all (-1) has been found ---*/
			status = (int)_PRICE_ALL ;
		}
		else
		{
			/*--- eliminate other ------------*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if (  (pPreis->rkr_id != aRkrid) && (pPreis->pre_id != (int)_UNDEF) )
				{
					pPreis->pre_id = (int)_UNDEF;
				}
			}
			/*-- no price has been found all are deleted ---*/
			status = (int)_PRICE_NOTFOUND ;
		}
	}
	return (status);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestKontid ()
 *					scan all prices and eliminate bad candidates
 *					if a kontigent is defined take this one
 *					if NO kontigent is defined eliminate these with
 *  In:			-limits for loop, a kontingent
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestKontid( int lowix, int highix, int aKontid )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k ;
	int		found, minusone, status ;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- look if there are prices with a kont_id ----*/
	found = 0;
	if (aKontid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ((pPreis->kont_id == aKontid) && (pPreis->pre_id != (int)_UNDEF))
			{
				found = 1;
				break;
			}
		}
	}

	/*--- There are prices for Kontingent and aKontid is defined -----------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( (pPreis->kont_id != aKontid) && (pPreis->pre_id  != (int)_UNDEF) )
			{
				pPreis->pre_id = (int)_UNDEF;
			}
		}
		/*-- a price for all (-1) has been found ---*/
		status = (int)_PRICE_ONE ;
	}
	else
	{
		/*--- look for a price without kont_id otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pPreis = &preis[k];
			if ( pPreis->kont_id == (int)_UNDEF )
			{
				minusone = 1;
				break;
			}
		}
		/*--- is there a price without Kontingent (-1) ----------*/
		if ( minusone )
		{
			/*--- eliminate these with kont_id --*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ((pPreis->kont_id != (int)_UNDEF) && (pPreis->pre_id != (int)_UNDEF))
					pPreis->pre_id = (int)_UNDEF;
			}
			/*-- a price for all (-1) has been found ---*/
			status = (int)_PRICE_ALL ;
		}
		else
		{
			/*--- eliminate other ------------*/
			for (k=lowix;  k < highix;  k++)
			{
				pPreis = &preis[k];
				if ( (pPreis->kont_id != aKontid) && (pPreis->pre_id  != (int)_UNDEF) )
				{
					pPreis->pre_id = (int)_UNDEF;
				}
			}
			/*-- no price has been found all are deleted ---*/
			status = (int)_PRICE_NOTFOUND ;
		}
	}
	return ( status );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceBestDatum ()
 *					scan all prices and eliminate bad candidates
 *					if a price is available in the date gap keep it
 *
 *  In:			-limits for loop, start, end dates
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTpriceBestDatum( int lowix, int highix, int azeit, int ezeit )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k, found, status ;
	PREIS		*pPreis;

	/*--- general inits ------------*/
	status = (int)MPOK ;


	/*--- check if preis is limited -----------------------------------*/
	found = 0;
	for (k=0;  k < anzPreis;  k++)
	{
		pPreis = &preis[k];
		if ((pPreis->dl_vondat != (int)_UNDEF) || (pPreis->dl_bisdat != (int)_UNDEF))
		{
			found = 1;
			break;
		}
	}

	/*--- dl (d) start date (<) must come after preis(p) start and before end */
	if ( found )
	{
		for (k=0;  k < anzPreis;  k++)
		{
			pPreis = &preis[k];
			/*--- eliminate if price gap is out of dl gap -----*/
			if ((azeit > pPreis->dl_vondat ) || (azeit < pPreis->dl_bisdat))
				pPreis->pre_id = (int)_UNDEF;
		}
	}
	return ( status );
}

/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceElliminateKar ()
 *					elliminate Katalogpreis if Nettopreis exists
 *  In:			-
 *  out:			-price value
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void AKTpriceElliminateKar( )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	PREIS    *pPreis;
	char	   tmpBuf[_TEXTLEN+1];
	char	   *ptr, *bufptr;
	int		k, type;
	int      toDelete;
	int      KarGroupFound;

	/*--- initialisation -------------------*/
	KarGroupFound = (int)FALSE;
	(void)AKTobjtxt((int)_COMMON_TYP, (int)_PRICE_AKTTXT_KARGROUP, tmpBuf, NOMARGIN);

	/*--- Elliminate Prices of same KarGroup ----------*/
	for (k=0;  k < anzPreis;  k++)
	{
		pPreis = &preis[k];
		if (( pPreis->pre_id != (int)_UNDEF) && (pPreis->kar_id != (int)_UNDEF) )
		{
			type = (int)_UNDEF;
			if ( KarGroupFound == (int)FALSE )
			{
				bufptr = tmpBuf;
				while ((ptr = strchr(bufptr, '$')) != NULL)
				{
					ptr++ ;
					type = atoi(ptr);
					bufptr = ptr;
					if ( pPreis->kar_id == type )
					{
						KarGroupFound = (int)TRUE;
						toDelete = k;
						break;
					}
				}
				KarGroupFound = (int)TRUE;
			}
			if ( KarGroupFound == (int)TRUE && type == (int)_UNDEF )
			{
				bufptr = tmpBuf;
				while ((ptr = strchr(bufptr, '$')) != NULL)
				{
					ptr++ ;
					type = atoi(ptr);
					bufptr = ptr;
					if ( pPreis->kar_id == type )
					{
						preis[toDelete].kar_id = (int)UNDEF;
						preis[toDelete].pre_id = (int)UNDEF;
						break;
					}
				}
			}
		}
	}

	return;
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceDebugPrintAll ( )
 *					print debug formatted prices
 *  In:			-
 *  out:			-
 *  Return:		-count
 *---------------------------------------------------------------------------
 */
static void AKTpriceDebugPrintAll( )
{
	extern	PREIS			*preis ;
	extern	int			anzPreis;

	int		k;

	/*--- Print valid prices ----------*/
	for (k=0;  k < anzPreis;  k++)
	{
		fprintf( stderr, "Preis Nr= %d: KarId=%d; Preis=%f%s" ,
				  preis[k].pre_id, preis[k].kar_id, preis[k].vpr, _P_EOL_ );
	}

	return;
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceCheckDebitor ( )
 *					check if the Debitor entry already exists
 *  In:			- pPrice PRICERESULT
 *  out:			- int status
 *  Return:		- count
 *---------------------------------------------------------------------------
 */
static int AKTpriceCheckDebitor( PRICERESULT *pPrice, int *exists )
{
	MEMOBJ intmem;

	int        status;
	int        anzint, intval;
	int        *intptr;

	char query[_QUERYLEN];

	/* init */
	intmem.buffer = NULL;
	intmem.datalen = 0;
	intmem.alloclen = 0;

	(void)sprintf(query, _SEL_DEBITOR_CHK, pPrice->bid, pPrice->dlnid,
					  pPrice->tdlid, pPrice->dlgid, pPrice->teil);

	status = MPAPIdb_sqlquery((int)_INTEGER, &intmem.buffer, query,
									  &anzint, &intmem.datalen, &intmem.alloclen);

	if (status == MPOK && anzint > 0)
	{
		/* count in integer umwandeln */
		intptr = (int *)intmem.buffer;
		intval = *intptr;

		status = (int)MPOK;

		if ( pPrice->bid == (int)_UNDEF && intval == 0 )
		{
			/*-- Init check if Table exists --*/
			*exists = (int)FALSE;
		}
		else if ( pPrice->bid != (int)_UNDEF && intval != 0 )
		{
			/*-- Table and entry exists --*/
			*exists = (int)TRUE;
		}
		else
		{
			/*-- Table exists but no entry found --*/
			*exists = (int)FALSE;
		}
	}
	else
	{
		*exists = (int)FALSE;
		status = (int)MPERROR;
	}

	MPfreeobj(&intmem);

	return(status);
}

/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceUpdateDebitor ( )
 *					update the Debitor entry
 *  In:			- pRes RESERVATION
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTpriceUpdateDebitor   ( PRICERESULT *pPrice,
												BUCHUNG *pBch,
												int akt_nr,
												double reduktion, double kommission )
{
	KUN_VIEW		      kunv;
	DIENST_ANGEBOT	   aDla;
	DIENSTLEISTUNG    aDlg;
	char              command[RECLAENGE];
	char              tmpBuf[_TEXTLEN+1];

	int status = (int)MPOK;
	int count, id;
	time_t	todayClock;

	/*----- get the delay of bill -----------*/
	(void)time( &todayClock );

	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, pPrice->dlgid, (char *)&aDlg);
	if (id == (int)_UNDEF)
	{
		AKTmsg( ACT_ERROR, MPA_OBJECTDLID, NULL);
		return( (int)MPERROR );
	}

	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, pPrice->dlaid, (char *)&aDla );
	if (id == (int)_UNDEF)
	{
		AKTmsg( ACT_ERROR, MPA_OBJECTDLA, NULL);
		return( (int)MPERROR );
	}

	/*-- KUNDEN: Anbieter der Dienstleistung -----------*/
	id = MPAPIselectOneId((int)_KUN_VIEW, pBch->kid, (char *)&kunv);
	if (id != (int)UNDEF)
		(void)copyTextTo(tmpBuf, kunv.konto, (int)_CHAR256);
	else
		*tmpBuf = NULL;

/*#4 get kbst from current user, now I put -1 init */
	(void)sprintf(command, _UPD_DEBITOR,
					  -1, pBch->kid, aDla.art_id, pPrice->kontid, pBch->k_id,
					  pPrice->katid, pPrice->rkrid, tmpBuf, akt_nr, pPrice->karid,
					  pPrice->ankaufVal, pPrice->einstandVal, pPrice->verkaufVal, reduktion,
					  kommission, (int)todayClock, aDlg.a_zeit, pPrice->bid, pPrice->dlnid,
					  pPrice->tdlid, pPrice->dlgid, pPrice->teil);

	status=MPAPIdb_sqlcommand(command, &count);

	return (status);
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTpriceInsertDebitor ( )
 *					insert the Debitor entry
 *  In:			- pRes RESERVATION
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTpriceInsertDebitor   ( PRICERESULT *pPrice,
												BUCHUNG *pBch,
												int akt_nr,
												double reduktion, double kommission )
{
	KUN_VIEW		      kunv;
	DIENST_ANGEBOT	   aDla;
	DIENSTLEISTUNG    aDlg;
	char              command[RECLAENGE];
	char              tmpBuf[_TEXTLEN+1];

	int status = (int)MPOK;
	int count, id;
	time_t	todayClock;

	/*----- get the delay of bill -----------*/
	(void)time( &todayClock );

	id = MPAPIselectOneId((int)_DIENSTLEISTUNG, pPrice->dlgid, (char *)&aDlg);
	if (id == (int)_UNDEF)
	{
		AKTmsg( ACT_ERROR, MPA_OBJECTDLID, NULL);
		return( (int)MPERROR );
	}

	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, pPrice->dlaid, (char *)&aDla );
	if (id == (int)_UNDEF)
	{
		AKTmsg( ACT_ERROR, MPA_OBJECTDLA, NULL);
		return( (int)MPERROR );
	}

	/*-- KUNDEN: Anbieter der Dienstleistung -----------*/
	id = MPAPIselectOneId((int)_KUN_VIEW, pBch->kid, (char *)&kunv);
	if (id != (int)UNDEF)
		(void)copyTextTo(tmpBuf, kunv.konto, (int)_CHAR256);
	else
		*tmpBuf = NULL;

/*#4 get kbst not form buchung, get it from current user profile. Put it to -1 for now */
	(void)sprintf(command, _INS_DEBITOR,
					  -1, pBch->kid, aDla.art_id, pPrice->kontid, pBch->k_id,
					  pBch->bid, pPrice->dlnid, pPrice->tdlid, pPrice->dlgid, pPrice->teil,
					  pPrice->katid, pPrice->rkrid, tmpBuf, akt_nr, pPrice->karid,
					  pPrice->ankaufVal, pPrice->einstandVal, pPrice->verkaufVal, reduktion,
					  kommission, (int)todayClock, aDlg.a_zeit);

	status=MPAPIdb_sqlcommand(command, &count);

	return (status);
}


static int ManageWhr(PREIS actpre, PREIS *newpre, LAND_WHR *usedlw)
{
	LAND_WHR currlw;
	int id;
	double tmppre;
	int abspre;

	(void)memcpy((void *)newpre, (void *)&actpre, sizeof(PREIS));

	currlw.land_id = usedlw->land_id;
	currlw.whr_id = usedlw->whr_id;
	currlw.kurs_typ = usedlw->kurs_typ;

	id = MPAPIselectOneId((int)_LAND_WHR, (int)currlw.land_id, (char *)&currlw);
	if (id == (int)_UNDEF)
		return(MPERROR);
	usedlw->a_kurs = currlw.a_kurs;
	usedlw->v_kurs = currlw.v_kurs;

	newpre->vpr = actpre.vpr * currlw.v_kurs;
	if (newpre->vpr != (double)0)
		{
		tmppre = actpre.vpr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->vpr = (double)abspre / (double)10.0;
			}
		}
	newpre->epr = actpre.epr * currlw.v_kurs;
	if (newpre->epr != (double)0)
		{
		tmppre = actpre.epr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->epr = (double)abspre / (double)10.0;
			}
		}
	newpre->apr = actpre.apr * currlw.v_kurs;
	if (newpre->apr != (double)0)
		{
		tmppre = actpre.apr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->apr = (double)abspre / (double)10.0;
			}
		}

	if (DebugFlag)
		(void)fprintf(stderr, "debug: WHR %d calculated with EXCHANGE RATE of %3.6f%s", actpre.whr_id, currlw.v_kurs, _P_EOL_);
	return(MPOK);
}
