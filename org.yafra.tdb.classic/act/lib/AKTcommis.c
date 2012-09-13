/*D***********************************************************
* Name:      AKTcommis.c
*                                                            
* Modul:     AKT base moduls
*            commision/reduction handling 
*                                                            
* Copyright: yafra.org, Basel, Switzerland     
**************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTcommis.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */



/*P--- EXTERNALS -----------------------------------------------------------*/

/*P--- PROTOTYPES ----------------------------------------------------------*/
static int AKTcommisBestDlDla  ( int low , int high );
static int AKTcommisBestDlid	( int lowix, int highix, int aDlid );
static int AKTcommisBestDlaid	( int lowix, int highix, int aDlaid );
static int AKTcommisBestKatidDlttid( int lowix, int highix, int aKatid, int aDlttid);
static int AKTcommisBestKatid  ( int lowix, int highix, int aKatid );
static int AKTcommisBestDlttid ( int lowix, int highix, int aDlttid );
static int AKTcommisBestRkrid  ( int lowix, int highix, int aKatid );
static int AKTcommisBestKontid ( int lowix, int highix, int aKontid );
static void AKTcommisBestDatum ( int aVondat );
static void AKTcommisResultAddOne( KOMMISSION *pCommis, double aValue );


#define COL_1			"%2.2s"
#define COL_2			"%29.29s"
#define COL_3			"%3.3s"
#define COL_TOT3		"%34.34s"                    /* COL_1+COL_2+COL_3     */
#define COL_4			"%8.8s"
#define COL_5			"%2.2s"
#define COL_TOT5		"%44.44s"                    /* COL_1+2+3+4+5         */
#define COL_6			"%8.8s"
#define VAL_6			"%4.1%%"
#define COL_7			"%2.2s"
#define COL_8			"%8.8s"
#define COL_9			"%2.2s"
#define COL_10			"%8.8s"
#define COL_11			"%2.2s"
#define COL_12			"%8.8s"
#define COL_KOM1		"%-4s"                   /* margin before com/reduction */
#define COL_KOM2		"%30.30s"                /* com/reduction text          */
#define COL_KOM3		"%-3.3s"                 /* gap                         */
#define COL_KOM4		"%+10.10s"               /* value                       */


/*--- SQL ------------------------------------------------------------------*/
#define	_SEL_COMMIS_ALL	"SELECT * FROM TDBADMIN.KOMMISSION \
	WHERE KOMM_ID >= 0 \
	ORDER BY KOMM_TYP, SATZ_ART ;"

#define	_SEL_COMMIS_BID_DLN	"SELECT KOMM_ID FROM TDBADMIN.KOMM_DETAIL \
	WHERE TDBADMIN.KOMM_DETAIL.BID    = %d 	AND  TDBADMIN.KOMM_DETAIL.DLN_ID = %d  ;"

#define	_SEL_COMMIS_KUN	"SELECT KOMM_ID FROM TDBADMIN.KOMM_DETAIL \
	WHERE (TDBADMIN.KOMM_DETAIL.KUN_ID = %d ) ;"

#define	_SEL_COMMIS_BID_DLN_KOL	"SELECT KOMM_ID FROM TDBADMIN.KOMM_DETAIL \
	WHERE (TDBADMIN.KOMM_DETAIL.BID   = %d AND  TDBADMIN.KOMM_DETAIL.DLN_ID = %d )\
	OR    (TDBADMIN.KOMM_DETAIL.KOL_ID = %d ) ;"


#define	_SEL_COMMIS_IN	         "SELECT * FROM TDBADMIN.KOMMISSION \
	WHERE KOMM_ID IN (%s) \
	ORDER  BY DLA_ID, DL_ID, DL_VONDAT, KAR_ID, KAT_ID, DLTT_ID, RKR_ID, KONT_ID ;"

#define _SEL_COMMIS_DLA		      "SELECT * FROM TDBADMIN.KOMMISSION \
	WHERE  DLA_ID = %d ;"

#define _SEL_COMMIS_MWST_DLA		   "SELECT * FROM TDBADMIN.KOMMISSION \
	WHERE  DLA_ID = %d AND KOMM_TYP = %d ;"
#define _SEL_COMMIS_MWST_ALL		   "SELECT * FROM TDBADMIN.KOMMISSION \
	WHERE  KOMM_TYP = %d ;"
	

/*--- DEFINES  -------------------------------------------------------------*/
#define COMMISMEMCHUNK		10          
#define _COMMIS_NOTFOUND 	3          
#define _COMMIS_ALL 			2          
#define _COMMIS_ONE			1          
#define _COMMIS_ERROR     	0          



/*F--------------------------------------------------------------------------
* Function:  AKTcommisMemobjInit
*            init memory for operations 
*---------------------------------------------------------------------------
*/
void AKTcommisMemobjInit( )
{
	extern	MEMOBJ		commismem;
	extern	KOMMISSION	*commis ;
	extern	MEMOBJ			comatrixmem;
	extern	COMMISRESULT	*commisMatrix;
	
	/*--- commission --------------*/
	commis  = (KOMMISSION *)NULL;
	commismem.buffer = NULL;       
	commismem.alloclen = 0;
	commismem.datalen = 0;	
	/*--- commission matrix -------*/
	commisMatrix  = (COMMISRESULT *)NULL;
	comatrixmem.alloclen = 0 ;
	comatrixmem.datalen  = 0 ;
	comatrixmem.buffer = NULL;       
}


/*F--------------------------------------------------------------------------
 * Function:  AKTcommisMemobjFree
 *            release memory for operations 
 *---------------------------------------------------------------------------
 */
void AKTcommisMemobjFree( )
{
	extern	MEMOBJ		commismem;
	extern	MEMOBJ		comatrixmem;

	/*--- Commission --------------*/
	MPfreeobj(&commismem);
	MPfreeobj(&comatrixmem);
	/*--- re-init for next --------*/
	AKTcommisMemobjInit();
}



/*F************************************************************
 * Function:  AKTcommisFindAll
 *            look for all commission/reduktion  
 * in:        
 * out:       
 * return:    success code
 **************************************************************/
int AKTcommisFindAll( int aBid, int aDlnid, int aKunid, int aKolid )
{
	extern	MEMOBJ		commismem ;
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	int		i, id, status ;
	int		anzCommid, *commid;
	unsigned long datalength, alloclength;
	char		query[2*RECLAENGE];
	char		bufid[2*RECLAENGE];
	char		tmpid[_CHAR10];
	
	/*--- general inits ------------*/
	status = (int)MPOK ;
	anzCommis = 0 ;

	/*--- General get all commissions -------------------------------------*/
	if (  (aBid   == (int)UNDEF) && (aDlnid == (int)UNDEF)
		&&	(aKunid == (int)UNDEF) && (aKolid == (int)UNDEF) ) 
	{
		(void)sprintf(query, _SEL_COMMIS_ALL );
		status = MPAPIdb_sqlquery((int)_KOMMISSION, (char **)(&commismem.buffer), query,
										  &anzCommis, &commismem.datalen, &commismem.alloclen );
		if (status == (int)MPOK )
			commis = (KOMMISSION *)commismem.buffer;
		else
			status = (int)MPERROR;
return(status);                                          /* >>> exit */
	}

	
	/*--- KOL -------------------------------------------*/
	if ((aKolid != (int)UNDEF)&&(aBid != (int)UNDEF)&&(aDlnid != (int)UNDEF))
	{
		anzCommid = (int)0;
		(void)sprintf(query, _SEL_COMMIS_BID_DLN_KOL, aBid, aDlnid, aKolid);
		commid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&commid, query, &anzCommid,
										  &datalength, &alloclength );
		/*--- prepare commids ---------*/
		for(i=0, *bufid=NULL;  i<anzCommid;  i++)
		{
			(void)sprintf(tmpid, "%d,", commid[i]);
			(void)strcat(bufid, tmpid);
		}
		if ( anzCommid > 0)
			bufid[strlen(bufid)-1] = NULL;
	}
	/*--- KUNID --------------------------------------------*/
	else if (aKunid != (int)UNDEF) 
	{
		anzCommid = (int)0;
		(void)sprintf(query, _SEL_COMMIS_KUN, aKunid );
		commid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&commid, query, &anzCommid,
										  &datalength, &alloclength );
		/*--- prepare commids ---------*/
		for(i=0, *bufid=NULL;  i<anzCommid;  i++)
		{
			(void)sprintf(tmpid, "%d,", commid[i]);
			(void)strcat(bufid, tmpid);
		}
		if ( anzCommid > 0)
			bufid[strlen(bufid)-1] = NULL;
	}
	/*--- BID and DLN ------------------------------------*/
	else if ((aBid != (int)UNDEF) && (aDlnid != (int)UNDEF)) 
	{
		anzCommid = (int)0;
		(void)sprintf(query, _SEL_COMMIS_BID_DLN, aBid, aDlnid);
		commid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&commid, query, &anzCommid,
										  &datalength, &alloclength );
		/*--- prepare commids ---------*/
		for(i=0, *bufid=NULL;  i<anzCommid;  i++)
		{
			(void)sprintf(tmpid, "%d,", commid[i]);
			(void)strcat(bufid, tmpid);
		}
		if ( anzCommid > 0)
			bufid[strlen(bufid)-1] = NULL;
	}
	/*--- Free allocated mem --------------*/
	MPfree((void *)commid);

	/*--- best commissions available ---------------------------------------*/
	if (anzCommid > 0)
	{	
		/*--- get a large set of possible commissions ---*/
		if (status == (int)MPOK)
		{
			(void)sprintf(query, _SEL_COMMIS_IN, bufid );
			status = MPAPIdb_sqlquery((int)_KOMMISSION, (char **)(&commismem.buffer), query,
											  &anzCommis, &commismem.datalen, &commismem.alloclen );
			if (status == (int)MPOK )
				commis = (KOMMISSION *)commismem.buffer;
			else
				status = (int)MPERROR;
		}		
		else
			status = (int)MPERROR;
	}
	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisPrepare ()
 *					Get commissions and verify if they are applicable 
 *  In:			-price result structure, Kund, Kollektif
 *  out:			-
 *  Return:		-success code 
 *---------------------------------------------------------------------------
 */
int AKTcommisPrepare( PRICERESULT *pPr, int aKunid, int aKolid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	extern	COMMISRESULT	*commisMatrix;
	extern	MEMOBJ			comatrixmem;
	
	KOMMISSION	*pCommis;
	int			m, k, status, nbCommis; 
	
	/*--- inits ------------------*/
	status = (int)MPOK ;
	CommisTyp = (int)_ACT_COMMIS_REISENDER;
	
	/*--- get commission -----------------------------------------------*/
 	status = AKTcommisFindAll( pPr->bid, pPr->dlnid, aKunid, aKolid );   
	if (status != (int)MPOK)
	{
		AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
		return ( (int)MPERROR );                               /* >>>> exit */
	}

	/*--- verify all criteria and get best commissions -----------------*/
	status = AKTcommisVerify( pPr);
	
	return( status );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisKunPrepare ()
 *					Get commissions and verify if they are applicable 
 *  In:			-Kund
 *  out:			-
 *  Return:		-success code 
 *---------------------------------------------------------------------------
 */
int AKTcommisKunPrepare( int aKunid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	
	KOMMISSION	*pCommis;
	int			m, k, status, nbCommis; 
	
	/*--- inits ------------------*/
	status = (int)MPOK ;
	CommisTyp = (int)_ACT_COMMIS_KUNDE;
	
	/*--- get commission -----------------------------------------------*/
 	status = AKTcommisFindAll( (int)_UNDEF, (int)_UNDEF, aKunid, (int)_UNDEF );   
	if (status != (int)MPOK)
	{
		AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
		return ( (int)MPERROR );                               /* >>>> exit */
	}

	return( status );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisMWStPrepare ()
 *					Get MWSt commissionsfrom the DlId 
 *  In:			-aDlgid
 *  out:			-
 *  Return:		-success code 
 *---------------------------------------------------------------------------
 */
int AKTcommisMWStPrepare( int aDlid )
{
	extern	MEMOBJ		commismem ;
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;

   DLG_PART             aTdl;
	char		            query[2*RECLAENGE];
	int			         status;
	int                  aDlaid;
	
	/*--- inits ------------------*/
	status = (int)MPOK ;


	/*---  get the dla from the dlg_part -------------------*/
	if ( aDlid != (int)_UNDEF )
	{
		aDlaid = MPAPIselectOneId((int)_DLG_PART, aDlid, (char *)&aTdl);
		(void)sprintf(query, _SEL_COMMIS_MWST_DLA, aDlaid, _KOMM_MWST );
	}
	else
	{
		(void)sprintf(query, _SEL_COMMIS_MWST_ALL, (int)_KOMM_MWST );
	}

	/*--- get commission -----------------------------------------------*/
	status = MPAPIdb_sqlquery((int)_KOMMISSION, (char **)(&commismem.buffer), query,
									  &anzCommis, &commismem.datalen, &commismem.alloclen );

	if (status == (int)MPOK )
		commis = (KOMMISSION *)commismem.buffer;
	else
		status = (int)MPERROR;
	
	return( status );
}




/*F************************************************************
 * Function:  AKTcommisVerify
 *            verify if all criteria are filled, otherwise 
 *            eliminate that commis/reduk
 * in:        
 * out:       
 * return:    nb of valid commis/reduk 
 **************************************************************/
int AKTcommisVerify( PRICERESULT *pPr )
{
	extern 	int			DebugFlag;
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;

	int		nbvalid ;
	int		k, old_kar_id,  status;
	int		lowix, highix, start, end ;
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- Test if one item minimum -------------*/
	if (anzCommis <= 0 )
		return (status);                                    /* >>>>> exit */	

	/*--- Check DL or DLA commission -----------------------------------*/
	start = 0;
	end = AKTcommisBestDlDla( start, anzCommis );   


	/*--- Eliminate bad karid commissions ------------*/
	for (k=start;  k < end;  k++)
	{
		pCommis = &commis[k];
		/*--- not same karid -------------*/
		if ( pCommis->kar_id != pPr->karid )  
		{
			pCommis->komm_id = (int)_UNDEF;
		}		
	}
	lowix  = start ;
	highix = end ;

	/*--- Verify all details -------------------------*/
	status = AKTcommisVerifyForOneKar( lowix, highix, pPr ); 
	if (status != (int)MPOK )
		return ((int)MPERROR )	;                           /* >>>>> exit */	


	return( (int)MPOK );
}



/*F************************************************************
 * Function:  AKTcommisVerifyForOneKar
 *            verify if all criteria are filled, for one kosten art 
 *            Most functions have low and high limits indexes to search
 * in:        
 * out:       
 * return:    status 
 **************************************************************/
int AKTcommisVerifyForOneKar( int lowix, int highix,  PRICERESULT *pPr )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;

	int			k, old_kar_id, status, result1, result2 ;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- DL check -------------------------------------------------------*/
	status = AKTcommisBestDlid( lowix, highix, pPr->dlgid);
	if (status != (int)MPOK )
		return ((int)MPERROR )	;                                /* >>>>> exit */	

	/*--- DLA check -------------------------------------------------------*/
	status = AKTcommisBestDlaid( lowix, highix, pPr->dlaid);
	if (status != (int)MPOK )
		return ((int)MPERROR )	;                                /* >>>>> exit */	

	/*--- Kategorie / Traegertyp --------------------------------------*/
	status = AKTcommisBestKatidDlttid( lowix, highix, pPr->katid, pPr->dlttid);

	/*--- Traegertyp --------------------------------------*/
	status = AKTcommisBestDlttid( lowix, highix, pPr->dlttid );
	if (status == (int)_COMMIS_ERROR)
		return ((int)MPERROR )	;
                                                            /* >>>>> exit */	
	/*--- Kategorie --------------------------------------*/
	status = AKTcommisBestKatid ( lowix, highix, pPr->katid  );
	if (status == (int)_COMMIS_ERROR)
		return ((int)MPERROR )	;                                /* >>>>> exit */	

	/*--- Reisender Typ check ---------------------------------------------*/
	status = AKTcommisBestRkrid( lowix, highix, pPr->rkrid);
	if (status != (int)MPOK )
		return ((int)MPERROR )	;                                /* >>>>> exit */	

	/*--- Kontigent check -------------------------------------------------*/
	status = AKTcommisBestKontid( lowix, highix, pPr->kontid);
	if (status != (int)MPOK )
		return ((int)MPERROR )	;                                /* >>>>> exit */	

	return( (int)MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisComputeResult ()
 *					compute 3 commissions and find texts  
 *					Order is given by program  
 *  In:			-nb allowed discounts, value to compute with
 *  out:			-where to write texts and value 
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int	AKTcommisComputeResult( int aNbKom, double brutVal, double *comVal )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			anzComatrix;
	
	KOMMISSION	*pCommis;
	int			k; 
	int			curOrder ; 
	int			number ; 
	char		bezKomm[_CHAR30+1];
	char		unitTxt[_CHAR30+1];
	char		*ptr;
	char		*pText;
	double		localBaseVal;                 /* for internal summing */
	double		minorVal, localMinorVal;      /* for internal summing */
	
	/*--- init -----*/
	number		= 0; 
	minorVal		= 0.0; 
	localBaseVal = brutVal;        /* is the base to compute */

	/*--- build a NEW commis result matrix -----*/
	anzComatrix		= 0; 

	/*--- look for all _SATZ_ABSOLUT ---------------------------*/
	for (k=0;  (k < anzCommis) && (number < aNbKom);  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( (pCommis->komm_id != (int)_UNDEF) && (pCommis->satz_art == _SATZ_ABSOLUT))
		{
			/*--- overwrite value --------*/
			localBaseVal  = pCommis->satz;
			minorVal = pCommis->satz ;

			/*--- save these values ---*/
			AKTcommisResultAddOne( pCommis, minorVal );
			pCommis->komm_id = (int)_UNDEF;               /* do not reuse */
			/*--- exit since we overwrite all rest ---*/
			*comVal  = minorVal ;
		return((int)MPOK) ;                      /* >>>>> exit >>>>*/ 
		}
	}

	/*--- look for all SATZ_NORMAL -----------------------------*/
	for (k=0;  (k < anzCommis) && (number < aNbKom);  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis?  ------------------*/
		if ( (pCommis->komm_id != (int)_UNDEF) && (pCommis->satz_art == _SATZ_NORMAL))
		{
			/*--- substract minoration value --------*/
			minorVal = minorVal + pCommis->satz ;         /* sum all minorations*/

			/*--- save these values ---*/
			AKTcommisResultAddOne( pCommis, pCommis->satz );
			pCommis->komm_id = (int)_UNDEF;               /* do not reuse */
			number++; 
		}		
	}
	localBaseVal = localBaseVal + minorVal;

	/*--- look for all SATZ_PROZENT  > 10% ----------------------------*/
	for (k=0;  (k < anzCommis) && (number < aNbKom);  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis?   ------------------*/
		if ( (pCommis->komm_id != (int)_UNDEF) && (pCommis->satz_art == _SATZ_PROZENT))
		{
			if (pCommis->satz > 10.0) 
			{
				/*--- sum all % minorations based on localBaseVal -------*/
				localMinorVal = (localBaseVal * pCommis->satz) / 100.0 ; 
				minorVal    += localMinorVal ;
				localBaseVal += localMinorVal ;     				 /* kumuliert */

				/*--- save these values ---*/
				AKTcommisResultAddOne( pCommis, localMinorVal );
				pCommis->komm_id = (int)_UNDEF;               /* do not reuse */
				number++;
			}
		}		
	}

	/*--- look for reset of SATZ_PROZENT ----------------------------*/
	for (k=0;  (k < anzCommis) && (number < aNbKom);  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis?  ------------------*/
		if ( (pCommis->komm_id != (int)_UNDEF) && (pCommis->satz_art == _SATZ_PROZENT))
		{
			/*--- sum all % minorations based on localBaseVal -------*/
			localMinorVal = (localBaseVal * pCommis->satz) / 100.0 ; 
			minorVal    += localMinorVal ;
			localBaseVal += localMinorVal ;     				 /* kumuliert */

			/*--- save these values ---*/
			AKTcommisResultAddOne( pCommis, localMinorVal );
			pCommis->komm_id = (int)_UNDEF;               /* do not reuse */
			number++;
		}		
	}

	/*--- final ----------*/
	*comVal  = minorVal ;
	return ( (int)MPOK );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisDeleteItemWhen ()
 *					kill commissions which do not contain the string in Bez
 *					
 *  In:			-parameter for matching or not, string to look for
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int	AKTcommisDeleteItemWhen ( int matchingOrNot, char *aString )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	KOMMISSION	*pCommis;
	int			k ; 
	char		bezKomm[_CHAR30+1];
	char		*ptr;

	/*--- init -----*/

	/*--- look for all commission containing "aString" -----------------*/
	for (k=0;  k < anzCommis ;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis?  ------------------*/
		if (pCommis->komm_id != (int)_UNDEF)
		{
			/*--- is string contained in Bez ? --------*/
			(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
			ptr = strstr( bezKomm, aString ) ;
			if ( matchingOrNot == MP_NOT_MATCHING)
			{
				/*--- delete when NOT matching/not found -----*/
				if (ptr == 0)
					pCommis->komm_id = (int)_UNDEF;
			}
			else
			{
				/*--- delete when MATCHING/found --------------*/
				if (ptr != 0)
					pCommis->komm_id = (int)_UNDEF;
			}
		}		
	}
	return ( (int)MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisGetIndexWhen ()
 *					get index of commission which contains the string in Bez
 *					
 *  In:			-parameter for matching or not, string to look for
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int	AKTcommisGetIndexWhen ( char *aString )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	KOMMISSION	*pCommis;
	int			k ; 
	char		bezKomm[_CHAR30+1];
	char		*ptr;

	/*--- init -----*/
	*bezKomm = 0;

	/*--- look for all commission containing "aString" -----------------*/
	for (k=0;  k < anzCommis ;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis?  ------------------*/
		if (pCommis->komm_id != (int)_UNDEF)
		{
			/*--- is string contained in Bez ? --------*/
			(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
			ptr = strstr( bezKomm, aString ) ;
			if (ptr != 0)
				return(k);                           /*>>>> exit */
		}		
	}
	return ( (int)-1 );
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisCompute ()
 *					compute all commissions for that price result in that order
 *					Absolute value is priority and no other computing is done
 *					then all fixed values are removed 
 *					then all rates are removed 
 *  In:			- 
 *  out:			-ptr to price result structure
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int	AKTcommisCompute( PRICERESULT *pPr, double *brutVal, double *minorVal, double *netVal )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	KOMMISSION	*pCommis;
	int			k, absolutFlag; 
	double		localBaseVal, localMinorVal;         /* for internal summing */
	
	/*--- look for all _SATZ_ABSOLUT ---------------------------*/
	absolutFlag = 0; 
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- Uebersteuerungs-Wert ---------------*/
			if ( pCommis->satz_art == _SATZ_ABSOLUT )
			{
				*brutVal  = pCommis->satz;
				*netVal   = *brutVal;
				absolutFlag = 1 ; 
			}
		}
	}
	if (absolutFlag == 1)
		return((int)MPOK) ;                            /* >>>>> exit */ 
	
	/*--- look for all SATZ_NORMAL -----------------------------*/
	localBaseVal = 0.0;
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- normaler Wert ----------------------*/
			if ( pCommis->satz_art == _SATZ_NORMAL ) 
			{
				*minorVal = *minorVal + pCommis->satz ;    /* sum all minorations*/
			}
		}		
	}
	/*--- substract sum of minorations -------------------------*/
	localBaseVal = *brutVal + *minorVal;
	
	/*--- look for all SATZ_PROZENT ----------------------------*/
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- Prozentualer Wert % ----------------*/
			if ( pCommis->satz_art == _SATZ_PROZENT )  
			{
				localMinorVal = (localBaseVal * pCommis->satz) / 100.0 ; 
				*minorVal    += localMinorVal ;
				localBaseVal += localMinorVal ;     /* kumuliert ? */
			}
		}		
	}
	/*--- final computing: remove all minorations ---------------*/
	*netVal   = *brutVal + *minorVal;
	return ( (int)MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisPrint ()
 *					pritout the text and value for commission/reduktion
 *  				1.Absolut  2.Values  3.Procent 
 *  In:			- 
 *  out:			-ptr to price result structure
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int	AKTcommisPrint( PRICERESULT *pPr, double brutVal)
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	FILE			*FPout;

	KOMMISSION	*pCommis;
	int			k, absolutFlag; 
	char	format[_CHAR80+1];
	char	bezKomm[_CHAR80+1];
	char	unitTxt[_CHAR30+1];
	char	*ptr;
	double		localBaseVal, localMinorVal;         /* for internal summing */
	double		minorVal;

	/*--- init for intern calculations --------*/
	minorVal      = 0.0 ;                            /* sum all minorations   */
	localBaseVal  = 0.0 ;                            /* intermediate new base */
	localMinorVal = 0.0 ;                            /* temp value of %       */

	/*--- 1. look for all ABSOLUT Satz ---------------------------------*/
	absolutFlag = 0; 
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- Uebersteuerungs-Wert ---------------*/
			if ( pCommis->satz_art == _SATZ_ABSOLUT )
			{
				(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
				cashint( (int)pCommis->satz, "%d", unitTxt);
				sprintf(format, "%s%s%s", COL_1, COL_2, _P_EOL_ );
				fprintf(FPout, format, " ", bezKomm  ); 
				absolutFlag = 1 ; 
			}
		}
	}
	/*--- Rest is not necessary if absolut ----------------------------*/
	if (absolutFlag == 1)
		return((int)MPOK) ;                            /* >>>>> exit */ 

	/*--- 2. look for all SATZ_NORMAL ---------------------------------*/
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- normaler Wert ----------------------*/
			if ( pCommis->satz_art == _SATZ_NORMAL ) 
			{
				minorVal = minorVal + pCommis->satz ;    /* sum all minorations*/
				
				(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
				cashint( (int)pCommis->satz, "%d", unitTxt);
				sprintf(format, "%s%s%s%s%s%s%s%s%s", COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, _P_EOL_ );
				fprintf(FPout, format, " ", bezKomm, " ", " ", " ", " ", " ", unitTxt ); 
			}
		}
	}
		
	/*--- substract sum of minorations -------------------------*/
	localBaseVal = brutVal + minorVal;

	/*--- 3.look for all SATZ_PROZENT % ---------------------------------*/
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		/*--- valid commis? -------------------*/
		if ( pCommis->komm_id != (int)_UNDEF )  
		{
			/*--- Prozentualer Wert % ----------------*/
			if ( pCommis->satz_art == _SATZ_PROZENT )  
			{
				localMinorVal = (localBaseVal * pCommis->satz) / 100.0 ; 

				(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
/*--- replace % which makes formatting problems ---*/
				while ((ptr = strchr(bezKomm, '%')) != NULL)
				   *ptr = 'p';
				cashint( (int)localMinorVal, "%d", unitTxt);
				sprintf(format, "%s%s%s%s%s%s%s%s%s", COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, _P_EOL_ );
				fprintf(FPout, format, " ", bezKomm, " ", " ", " ", " ", " ", unitTxt ); 
			}
		}		
	}
	return((int)MPOK) ;                            /* >>>>> exit */ 
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisCountValid ()
 *					scan all commission and count valid one
 *  In:			- 
 *  out:			-
 *  Return:		-count 
 *---------------------------------------------------------------------------
 */
int AKTcommisCountValid( )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	int			k, count ; 
	KOMMISSION	*pCommis;
	
	/*--- look if kont_id is a criteria of selection --------------*/
	count = 0;
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		if ( pCommis->komm_id != (int)_UNDEF )
			count++;
	}
	return (count);
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisPrintAllValid ()
 *					print all Commissions that are valid in free format
 *  In:			- 
 *  out:			-
 *  Return:		-count 
 *---------------------------------------------------------------------------
 */
int AKTcommisPrintAllValid( )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern   char		   mailstring[];
	
	int			k; 
	KOMMISSION	*pCommis;
	char	bezKomm[_CHAR80+1];
	
	/*--- look if kont_id is valid --------------*/
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		if ( pCommis->komm_id != (int)_UNDEF )
		{
			(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
			(void)sprintf(mailstring, "%s", bezKomm);
			AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		}
	}
	return ( (int)MPOK );
}


/************************ STATIC FUNCTIONS ***********************************/
/*****************************************************************************/

/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestDlDla ()
 *					scan from low to high and find if there are commissions 
 *					for DL (set new high index) or DLA (default is high). 
 *					Piiority is for DL commissions. 
 *  In:			- 
 *  out:			-
 *  Return:		-new high index  
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestDlDla( int low , int high )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	
	int		k, highindex, dl_found ; 
	KOMMISSION	*pCommis;

	/*--- default ----------------*/
	highindex = high ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*-- give new high limit -----*/
		return( highindex );
	}

	/*--- loop to find DL commissions for kunden --------------------*/
	dl_found = 0; 
	for (k=low;  k < high;  k++)
	{
		pCommis = &commis[k];
		/*--- DL items ? -------*/
		if (pCommis->dl_id != (int)_UNDEF)
		{ 
			dl_found = 1;
			highindex = k + 1;
		}
		else		
			break;   /* DLA commissions strech till end -*/
	}
	/*--- remove DLA commissions if there are DL commisions ---------*/
	if (dl_found == 1)
	{ 
		for (k=highindex;  k < high;  k++)
		{
			pCommis = &commis[k];
			pCommis->komm_id = (int)_UNDEF;
		}  
	}
	/*-- give new high limit -----*/
	return( highindex);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestDlid ()
 *					scan all commissions and try to find some with a dl-id 
 *					in this case and if one is defined take this one 
 *					if NO one is defined eliminate these without 
 *  In:			-limits for loop, an id 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestDlid( int lowix, int highix, int aDlid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	
	int		k; 
	int		found, minusone, status ; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dl_id != aDlid) && ( pCommis->dl_id != (int)_UNDEF ) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( status );
	}
	
	/*--- look if aDlid is a criteria of selection -----*/
	found = 0;
	if (aDlid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dl_id == aDlid) && (pCommis->komm_id != (int)_UNDEF))
			{ 
				found = 1;
				break;
			}
		}
	}

	/*--- it is a criteria, so look for matching ------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dl_id != aDlid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
	}
	else 
	{
		/*--- look for a comm without otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->dl_id == (int)_UNDEF )
			{ 
				minusone = 1;
				break;
			}
		}
		/*--- is there a commission without dl_id (-1) ? ---------*/
		if ( minusone )
		{
			/*--- eliminate these with one --*/
			for (k=lowix;  k < highix;  k++)
			{
				pCommis = &commis[k];
				if ((pCommis->dl_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
		}
		else 
		{
			/*--- there is a problem with selection -----------------------*/
			status = (int)MPERROR ; 
		}
	}
	return (status); 
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestDlaid ()
 *					scan all commissions and try to find some with a dla-id 
 *					in this case and if one is defined take this one 
 *					if NO one is defined eliminate these without 
 *  In:			-limits for loop, an id 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestDlaid( int lowix, int highix, int aDlaid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	
	int		k; 
	int		found, minusone, status ; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( (pCommis->dla_id != aDlaid) && (pCommis->dla_id != (int)_UNDEF) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( status );
	}
	
	/*--- look if aDlaid is a criteria of selection -----*/
	found = 0;
	if (aDlaid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dla_id == aDlaid) && (pCommis->komm_id != (int)_UNDEF))
			{ 
				found = 1;
				break;
			}
		}
	}

	/*--- it is a criteria, so look for matching ------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dla_id != aDlaid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
	}
	else 
	{
		/*--- look for a comm without id, otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->dla_id == (int)_UNDEF )
			{ 
				minusone = 1;
				break;
			}
		}
		/*--- is there a commission without dla_id (-1) ? ---------*/
		if ( minusone )
		{
			/*--- eliminate these with one --*/
			for (k=lowix;  k < highix;  k++)
			{
				pCommis = &commis[k];
				if ((pCommis->dla_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
		}
		else 
		{
			/*--- there is a problem with selection -----------------------*/
			status = (int)MPERROR ; 
		}
	}
	return (status); 
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestKatidDlttid ()
 *					scan all items and try to find items matching either a 
 *					a category or a dlttype but not the two 
 *					No commission at all is not ok 
 *  In:			-limits for loop, a category, a dlttid
 *  out:			-
 *  Return:		- special codes 
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestKatidDlttid( int lowix, int highix, int aKatid, int aDlttid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;

	int		k ; 
	int		situation  ; 
	int		status; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)_COMMIS_NOTFOUND ;

	/*--- look if prices exist with a kat_id ----*/
	for (k=lowix;  k < highix;  k++)
	{
		pCommis = &commis[k];
		if (pCommis->komm_id != (int)_UNDEF)
		{ 
			if ((pCommis->kat_id == aKatid) && (pCommis->dltt_id == aDlttid))
			{ 
				situation = 1 ;
				break;
			}
			if ((pCommis->kat_id == (int)_UNDEF) && (pCommis->dltt_id == aDlttid))
			{ 
				situation = 2 ;
				break;
			}
			if ((pCommis->kat_id == aKatid) && (pCommis->dltt_id == (int)_UNDEF))
			{ 
				situation = 3 ;
				break;
			}
			if ((pCommis->kat_id == (int)_UNDEF) && (pCommis->dltt_id == (int)_UNDEF))
			{ 
				situation = 4 ;
				break;
			}
		}
	}

	switch (situation)
	{
		case 1:           /*--- both have items handle as one with priority */
		case 2:           /*--- take commission of dltt      */
		case 3:           /*--- take commission of category  */
			status = (int)_COMMIS_ONE ;
			break;

		case 4:           /*-- No commission found           */
			status = (int)_COMMIS_ALL ;
			break;
	}

	return ( status );
}





/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestDlttid ()
 *					scan all commis to find one with Traegertyp 
 *					in this case if a Traegertyp is defined take this one 
 *					if NO Traegertyp is defined eliminate these without 
 *  In:			-limits for loop, a Traegertyp
 *  out:			-
 *  Return:		- special codes 
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestDlttid( int lowix, int highix, int aDlttid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;

	int		k ; 
	int		found, minusone, status; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)_COMMIS_NOTFOUND ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dltt_id != aDlttid) && (pCommis->dltt_id != (int)_UNDEF) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( (int)_COMMIS_ALL );
	}

	/*--- look if commissions exist with a Traegertyp ----*/
	found = 0;
	for (k=lowix;  k < highix;  k++)
	{
		pCommis = &commis[k];
		if (( pCommis->dltt_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
		{ 
			found = 1;
			break;
		}
	}

	/*--- There are commissions and a Traegertyp is defined ? -------------------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->dltt_id != aDlttid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
		/*-- one commission has been found ---*/
		status = (int)_COMMIS_ONE ;
	}
	else 
	/*--- no commission with Traegertyp or aDlttid is not defined -------------*/
	{
		/*--- look for a commission with traegertyp -1 --*/
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->dltt_id == (int)_UNDEF )
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
				pCommis = &commis[k];
				if ((pCommis->dltt_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
			/*-- a commission for all (-1) has been found ---*/
			status = (int)_COMMIS_ALL ;
		}
		else 
		{
			/*--- there is a problem with commissions selection -----------*/
			status = (int)_COMMIS_ERROR ;
		}
	}
	return ( status );
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestKatid ()
 *					scan all commissions and try to find some with a category 
 *					in this case and if a Kategorie is defined take this one 
 *					if NO Kategorie is defined eliminate these without 
 *  In:			-limits for loop, a category
 *  out:			-
 *  Return:		- special codes 
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestKatid( int lowix, int highix, int aKatid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;

	int		k ; 
	int		found, minusone, status; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)_COMMIS_NOTFOUND ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other categories --*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kat_id != aKatid) && (pCommis->kat_id != (int)_UNDEF) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( (int)_COMMIS_ALL );
	}

	/*--- look if commission exist with a kat_id ----*/
	found = 0;
	if (aKatid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kat_id == aKatid) && (pCommis->komm_id != (int)_UNDEF))
			{ 
				found = 1;
				break;
			}
		}
	}

	/*--- There are commissions for Categories and aKatid is defined -------*/
	if ( found )
	{
		/*--- eliminate other categories --*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kat_id != aKatid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
		/*-- one commission has been found ---*/
		status = (int)_COMMIS_ONE ;
	}
	else
	/*--- there are no commission with Categorie or aKatid is not defined ---*/
	{
		/*--- look for one without category otherwise something is wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->kat_id == (int)_UNDEF )
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
				pCommis = &commis[k];
				if ((pCommis->kat_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
			/*-- a commission for all (-1) has been found ----*/
			status = (int)_COMMIS_ALL ;
		}
		else 
		{
			/*--- there is a problem with selection  -------------------------*/
			status = (int)_COMMIS_ERROR ;
		}
	}
	return ( status );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestRkrid ()
 *					scan all commissions and try to find some with a rkr-id 
 *					in this case and if a rkr is defined take this one 
 *					if NO rkr is defined eliminate these without 
 *  In:			-limits for loop, a reisender-typ
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestRkrid( int lowix, int highix, int aRkrid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;
	
	int		k; 
	int		found, minusone, status ; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->rkr_id != aRkrid) && (pCommis->rkr_id != (int)_UNDEF) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( (int)_COMMIS_ALL );
	}
	
	/*--- look if rkr is a criteria of selection --*/
	found = 0;
	if (aRkrid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->rkr_id == aRkrid) && (pCommis->komm_id != (int)_UNDEF))
			{ 
				found = 1;
				break;
			}
		}
	}

	/*--- rkr is a criteria, so look for matching Reisender-typ ---*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->rkr_id != aRkrid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
	}
	else 
	{
		/*--- look for a price without Reisender-typ otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->rkr_id == (int)_UNDEF )
			{ 
				minusone = 1;
				break;
			}
		}
		/*--- is there a commission without Reisender-typ (-1) ? ---------*/
		if ( minusone )
		{
			/*--- eliminate these with Reisender-typ --*/
			for (k=lowix;  k < highix;  k++)
			{
				pCommis = &commis[k];
				if ((pCommis->rkr_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
		}
		else 
		{
			/*--- there is a problem with selection -----------------------*/
			status = (int)MPERROR ; 
		}
	}
	return (status); 
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestKontid ()
 *					scan all commissions and eliminate bad candidates 
 *					if a kontigent is defined take this one 
 *					if NO kontigent is defined eliminate these with 
 *  In:			-limits for loop, a kontingent
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
static int AKTcommisBestKontid( int lowix, int highix, int aKontid )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	extern	int			CommisTyp;

	int		k ; 
	int		found, minusone, status ; 
	KOMMISSION	*pCommis;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- if there is a reisender Commission all are valid ---*/
	if ( CommisTyp == (int)_ACT_COMMIS_REISENDER )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kont_id != aKontid) && (pCommis->kont_id != (int)_UNDEF) &&
				 (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}

		return( (int)_COMMIS_ALL );
	}

	/*--- look if there are commissions with a kont_id ----*/
	found = 0;
	if (aKontid != (int)_UNDEF)
	{
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kont_id == aKontid) && (pCommis->komm_id != (int)_UNDEF))
			{ 
				found = 1;
				break;
			}
		}
	}

	/*--- There are commissions for Kontingent and aKontid is defined ------*/
	if ( found )
	{
		/*--- eliminate other ------------*/
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ((pCommis->kont_id != aKontid) && (pCommis->komm_id != (int)_UNDEF))
				pCommis->komm_id = (int)_UNDEF;		
		}
	}
	else
	{
		/*--- look for a commission without kont_id otherwise wrong */
		minusone = 0;
		for (k=lowix;  k < highix;  k++)
		{
			pCommis = &commis[k];
			if ( pCommis->kont_id == (int)_UNDEF )
			{ 
				minusone = 1;
				break;
			}
		}
		/*--- is there a commission without Kontingent (-1) ----------*/
		if ( minusone )
		{
			/*--- eliminate these with kont_id --*/
			for (k=lowix;  k < highix;  k++)
			{
				pCommis = &commis[k];
				if ((pCommis->kont_id != (int)_UNDEF) && (pCommis->komm_id != (int)_UNDEF))
					pCommis->komm_id = (int)_UNDEF;		
			}
		}
		else 
		{
			/*--- there is a problem with selection  -------------------*/
			status = (int)MPERROR ; 
		}
	}
	return ( status );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisBestDatum ()
 *					control if the start date is within the gap 
 *  In:			- a start datum
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static void AKTcommisBestDatum( int aVondat )
{
	extern	KOMMISSION	*commis ;
	extern	int			anzCommis;
	
	int			k, found ; 
	KOMMISSION	*pCommis;
	
	/*--- look if datum is a criteria of selection --------------*/
	found = 0;
	for (k=0;  k < anzCommis;  k++)
	{
		pCommis = &commis[k];
		if ( pCommis->dl_vondat != (int)_UNDEF )
		{ 
			found = 1;
			break;
		}
	}
	/*--- start date must be in gap to valid ---------------------*/
	if ( found )
	{
		for (k=0;  k < anzCommis;  k++)
		{
			pCommis = &commis[k];
			/*--- eliminate other non matching Reisender-typ --*/
			if ((pCommis->dl_vondat >= aVondat) || (pCommis->dl_bisdat <= aVondat))
				pCommis->komm_id = (int)_UNDEF;		
		}
	}
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTcommisResultAddOne ()
 *					add a commission to the result array 
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static void AKTcommisResultAddOne( KOMMISSION *pCommis, double aValue )
{
	extern	MEMOBJ		commismem;
	extern	KOMMISSION	*commis ;
	extern	MEMOBJ			comatrixmem;
	extern	COMMISRESULT	*commisMatrix;
	extern	int				anzComatrix;
	
	int			k, found ; 
	char		bezKomm[_CHAR30+1];
	char		unitTxt[_CHAR30+1];
	COMMISRESULT	*pComx;
	
	/*--- get a new item reference ---------------------*/
	comatrixmem.datalen = (anzComatrix+1)* sizeof(COMMISRESULT);
	comatrixmem.buffer = (char *)MPallocobj( &comatrixmem,
													 COMMISMEMCHUNK * sizeof(COMMISRESULT) );
	commisMatrix = (COMMISRESULT *)comatrixmem.buffer;
	pComx = &commisMatrix[anzComatrix];
 
	/*--- Write a new result ---------------------------*/
	pComx->komid	= pCommis->komm_id ;
	(void)AKTobjbez( (int)_KOMMISSION, pCommis->bez_id, bezKomm);
	sprintf( pComx->bez, "%s", bezKomm);
	pComx->satzart	= pCommis->satz_art;
	pComx->satzVal	= pCommis->satz;
	pComx->commVal	= aValue;

	anzComatrix++ ;
}

