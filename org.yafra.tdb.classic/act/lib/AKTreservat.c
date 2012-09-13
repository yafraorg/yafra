/*D***********************************************************
 * Name:      AKTreservat.c
 *                                                            
 * Modul:     AKT base moduls
 *            Handle reservation long and short print forms 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTreservat.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/



/*P--- PROTOTYPES ----------------------------------------------------------*/


/*P--- LAYOUT --------------------------------------------------------------*/
#define TEXTID7       7

#define COL_DL1			"%-2s"                       /* DL margin        */
#define COL_DL2			"%-30.30s"                     /* DL bezeichnung   */
#define COL_DL3			"%-s"                          /* DL anfang day    */
#define COL_DL4			"%-2.2s"                       /* DL gap           */
#define COL_DL5			"%-s"                          /* DL anfang date   */
#define NOTIME				"-------"                      /* no time          */


/*P--- GLOBALS  -----------------------------------------------------------*/

/*-- Common object texts -----------*/
#define AKTCOM_KAT_ZUSATZ			20

/*--- SQL ------------------------------------------------------------------*/
#define _SEL_ALL_RES_PERS		"SELECT * FROM TDBADMIN.RESERVATION \
	WHERE BID = %d \
	AND   PERS_ID = %d  ORDER BY DLG_ID ;"
                               
#define _SEL_ALL_AKT_DETAIL	"SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE BID = %d     AND PERS_ID = %d  \
	AND   DLG_ID = %d  AND A_TYP_ID = %d ;"

#define _SEL_DLG_DLG				"SELECT * FROM TDBADMIN.DLG_DLG \
	WHERE DLG_ID = %d  ORDER BY ORD ;"

/*-- Res with status -----------*/
#define _SEL_RES_STA		"SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE R_STA >= %d AND R_STA <= %d \
	ORDER BY  BID, PERS_ID, DLG_ID;"                    /*????? */

#define _SEL_RESBCH_STA	"SELECT * FROM TDBADMIN.RESERVATION \
	WHERE BID = %d \
	AND R_STA >= %d AND R_STA <= %d \
	ORDER BY  BID, PERS_ID;"

#define _SEL_RESDL_STA		"SELECT * FROM TDBADMIN.RESERVATION \
	WHERE DLG_ID = %d \
	AND R_STA >= %d AND R_STA <= %d \
	ORDER BY  BID, PERS_ID;"

#define _SEL_RES_DL		"SELECT * FROM TDBADMIN.RESERVATION \
	WHERE DLG_ID = %d \
	ORDER BY  PERS_ID;"


/*-- Res view with status ------*/
#define _SEL_RESV_ST			"SELECT * FROM TDBADMIN.RES_DL_VIEW R \
	WHERE R.R_STA >= %d AND R.R_STA <= %d \
	ORDER BY  R.R_STA, R.RESAZEIT, R.DLAZEIT, R.BID, R.PERS_ID;"

#define _SEL_RESV_BCH_ST	"SELECT * FROM TDBADMIN.RES_DL_VIEW R \
   WHERE R.BID = %d \
	AND R.R_STA >= %d AND R.R_STA <= %d \
	ORDER BY  R.R_STA, R.RESAZEIT, R.DLAZEIT, R.BID, R.PERS_ID;"

#define _SEL_RESV_DL_ST		"SELECT  * FROM TDBADMIN.RES_DL_VIEW R \
   WHERE R.DL_ID = %d \
	AND R.R_STA >= %d AND R.R_STA <= %d \
	ORDER BY  R.R_STA, R.RESAZEIT, R.DLAZEIT, R.BID, R.PERS_ID;"


/*-- Res Buchung DL  -----------*/
#define _SEL_RESBCH_DLG		"SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d \
	AND DLG_ID = %d ORDER BY PERS_ID, DL_ID, TEIL;"


/*-- Res view for PAX Cruise ---*/
#ifdef ps_unix
#define _SEL_RESV_DL			"SELECT  * FROM TDBADMIN.RES_DL_VIEW  \
   WHERE DL_ID = %d  AND S_ID = %d \
	GROUP BY  KAT_ID, KATBEZ, DLT_ID, DLTBEZ, BID, PERS_ID, NAME, DL_ID, \
	BID, DLAZEIT, TDL_ID, TDLAZEIT, TDLEZEIT,\
	RESAZEIT, RESEZEIT, TYP_ID, KONT_ID, R_STA, S_ID \
	ORDER BY  KATBEZ, DLTBEZ, BID, PERS_ID;"
#endif

#ifdef ps_win
#define _SEL_RESV_DL			"SELECT  * FROM TDBADMIN.RES_DL_VIEW  \
   WHERE DL_ID = %d  AND S_ID = %d \
	ORDER BY  KATBEZ, DLTBEZ, PERS_ID;"
#endif


/*-- Res view for PAX Bus ------*/
#define _SEL_RESV_DL_1			"SELECT  * FROM TDBADMIN.RES_DL_VIEW  \
   WHERE DL_ID = %d  AND S_ID = %d \
	ORDER BY NAME, PERS_ID, DL_ID, TDLEZEIT ;"

/*-- Get first part of a Hostdlid ---*/
#define _SEL_FIRST_DLG_PART   "SELECT * FROM TDBADMIN.DLG_PARTS \
   WHERE H_DL_ID = %d \
   AND     ORD = (SELECT MIN(ORD) FROM TDBADMIN.DLG_PARTS \
                  WHERE  H_DL_ID = %d);"

/*-- Get all dlg_id from one bid ---*/
#define _SEL_BID_DLG   "SELECT DISTINCT(DLG_ID) FROM TDBADMIN.RESERVATION \
   WHERE BID = %d;"


/*F--------------------------------------------------------------------------
 * Function:  AKTreservatMemobjectInit
 *            init memory for reservations operations 
 *---------------------------------------------------------------------------
 */
void AKTreservatMemobjInit( )
{
	extern 	MEMOBJ		resmem, *pResmem; 
	extern 	RESERVATION	*reservation ;
	extern 	MEMOBJ		aktdetmem, *pAktdetmem;  
	extern 	AKT_DETAIL	*aktdetail ;

	/*--- reservation --------------*/
	reservation  = (RESERVATION *)NULL;
	resmem.buffer = NULL;       
	resmem.alloclen = 0;
	resmem.datalen = 0;
	pResmem    = &resmem;
	/*--- aktion detail ------------*/
	aktdetail = (AKT_DETAIL *)NULL;
	aktdetmem.buffer = NULL;    
	aktdetmem.alloclen = 0;
	aktdetmem.datalen = 0;
	pAktdetmem = &aktdetmem;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTresViewMemobjInit
 *            init memory for reservations view operations 
 *---------------------------------------------------------------------------
 */
void AKTresViewMemobjInit( )
{
	extern 	MEMOBJ		resvmem, *pResvmem; 
	extern 	RES_DL_VIEW	*resview ;

	/*--- reservation --------------*/
	resview  = (RES_DL_VIEW *)NULL;
	resvmem.buffer = NULL;       
	resvmem.alloclen = 0;
	resvmem.datalen = 0;
	pResvmem    = &resvmem;
}



/*F--------------------------------------------------------------------------
 * Function:  AKTreservatMemobjectFree
 *            free memory of reservations 
 *---------------------------------------------------------------------------
 */
void AKTreservatMemobjFree( )
{
	extern 	MEMOBJ		resmem; 
	extern 	MEMOBJ		aktdetmem;  

	/*--- reservation --------------*/
	MPfreeobj(&resmem);
	/*--- action detail ------------*/
	MPfreeobj(&aktdetmem);

	/*--- prepare for next usage ---*/
	AKTreservatMemobjInit();
}


/*F--------------------------------------------------------------------------
 * Function:  AKTresViewMemobjFree
 *            free memory of reservations view 
 *---------------------------------------------------------------------------
 */
void AKTresViewMemobjFree( )
{
	extern 	MEMOBJ		resvmem, *pResvmem; 
	extern 	RES_DL_VIEW	*resview ;

	/*--- reservation --------------*/
	MPfreeobj(&resvmem);

	/*--- prepare for next usage ---*/
	AKTresViewMemobjInit();
}




/*F--------------------------------------------------------------------------
 * Function:  AKTreservatFindDl
 *            look for all reservation with a Dl 
 * 
 * in:        dl id 
 * out:       array of RESs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatFindDl( int aDlid )
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aDlid != (int)_UNDEF) 
		{
		(void)sprintf(query, _SEL_RES_DL, aDlid );
		status = MPAPIdb_sqlquery((int)_RESERVATION, (char **)(&resmem.buffer),
									 query, &anzRes, &resmem.datalen, &resmem.alloclen );
		}		
	else 
		status = (int)MPERROR;

	reservation = (RESERVATION *)resmem.buffer;
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTreservatFindAll
 *            look for all reservation for a dln 
 * 
 * in:        dln id 
 * out:       array of RESs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatFindAll( int aBid, int aPersid )
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aPersid != (int)_UNDEF) 
	{
		(void)sprintf(query, _SEL_ALL_RES_PERS, aBid, aPersid);
		status = MPAPIdb_sqlquery((int)_RESERVATION, (char **)(&resmem.buffer),
										  query, &anzRes, &resmem.datalen, &resmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	reservation = (RESERVATION *)resmem.buffer;
	return(status);
}


/*F--------------------------------------------------------------------------
 * Function:  AKTreservatFindCat
 *            look for category in all reservation for a dln 
 * 
 * in:        dlg id 
 * out:       string with the Category Bez 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatFindCat( int aDlgid, int aDlnid, char *CatTxt )
{ 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int		id, ires, status;
   KAT_VIEW kat_view;

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- reservation loop -------*/
	if (aDlgid != (int)_UNDEF && aDlnid != (int)_UNDEF ) 
	{
	   for ( ires=0; ires < anzRes; ires++ )
      {
         if ( ( reservation[ires].dlg_id == aDlgid ) &&
              ( reservation[ires].pers_id == aDlnid ) )
         {
            if ( reservation[ires].kat_id != (int)_UNDEF )
               {
                  id = MPAPIselectOneId((int)_KAT_VIEW, reservation[ires].kat_id,
                                  (char *)&kat_view);
                  if ( id != (int)_UNDEF )
                  {
                     copyTextTo( CatTxt, kat_view.bez, _CHAR30 );
                  }
                   else
                  {
                     strcpy( CatTxt, "?" );
                  }
               }
            else
               {
                  strcpy( CatTxt, " " );
               }
         }
      }
	}	
	
	return(status);
}


/*F--------------------------------------------------------------------------
 * Function:  AKTreservatBidDlgid
 *            look for all reservation for a dl
 * 
 * in:        dln id 
 * out:       array of RESs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatBidDlgid( int aBid, int aDlid )
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if ((aBid != (int)_UNDEF) && (aDlid != (int)_UNDEF))
	{
		(void)sprintf(query, _SEL_RESBCH_DLG, aBid, aDlid);
		status = MPAPIdb_sqlquery((int)_RESERVATION, (char **)(&resmem.buffer),
										  query, &anzRes, &resmem.datalen, &resmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	reservation = (RESERVATION *)resmem.buffer;
	return(status);
}




/*F--------------------------------------------------------------------------
 * Function:  AKTreservatStatus
 *            look for all reservation which are < tartget status 
 * 
 * in:        dln id 
 * out:       array of RESs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatStatus( int aBid, int aDlid, int aSourcesta, int aTargetsta )
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern 	int			DebugFlag;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- get all needed RESERVATION ---------------*/
	if (aBid != (int)_UNDEF)
		(void)sprintf( query, _SEL_RESBCH_STA, aBid, aSourcesta, aTargetsta);
	else if (aDlid != (int)_UNDEF)
		(void)sprintf( query, _SEL_RESDL_STA, aDlid, aSourcesta, aTargetsta);
	else
		(void)sprintf( query, _SEL_RES_STA, aSourcesta, aTargetsta);

	/*.... DEBUG .......*/
	if (DebugFlag)
		printf("%sAKTreservatStatus: sql-query %s%s", _P_EOL_, query, _P_EOL_ );

	status = MPAPIdb_sqlquery((int)_RESERVATION, (char **)(&resmem.buffer),
									 query, &anzRes, &resmem.datalen, &resmem.alloclen );

	reservation = (RESERVATION *)resmem.buffer;
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTresViewStatus
 *            look for all reservation views which are in status range
 * 
 * in:        a bchid, a dlid , source and target status 
 * out:       array of resview ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTresViewStatus( int aBid, int aDlid, int aSourcesta, int aTargetsta )
{
	extern 	MEMOBJ		resvmem, *pResvmem; 
	extern 	RES_DL_VIEW	*resview ;
	extern 	int			anzResv;
	extern 	int			DebugFlag;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- get all needed RES_DL_VIEW ---------------*/
	if (aBid != (int)_UNDEF)
		(void)sprintf( query, _SEL_RESV_BCH_ST, aBid, aSourcesta, aTargetsta);
	else if (aDlid != (int)_UNDEF)
		(void)sprintf( query, _SEL_RESV_DL_ST, aDlid, aSourcesta, aTargetsta);
	else
		(void)sprintf( query, _SEL_RESV_ST, aSourcesta, aTargetsta);

/*DEBUG*****************/
	if (DebugFlag)
		printf("%sAKTresViewStatus: sql-query %s%s", _P_EOL_, query, _P_EOL_ );

	/*--- query reservations views -----------------------*/
	if ((aSourcesta != (int)_UNDEF)&&(aTargetsta != (int)_UNDEF))
	{
		status = MPAPIdb_sqlquery((int)_RES_DL_VIEW, (char **)(&resvmem.buffer),
									 query, &anzResv, &resvmem.datalen, &resvmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	resview = (RES_DL_VIEW *)resvmem.buffer;
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTresViewDl
 *            look for all reservation views with Dl id 
 * 
 * in:        a dlid
 * out:       array of resview ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTresViewDl( int aDlid )
{
	extern 	MEMOBJ		resvmem, *pResvmem; 
	extern 	RES_DL_VIEW	*resview ;
	extern 	int			anzResv;
	extern 	int			DebugFlag;
	extern	int outputsprache;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;
	*query = (char)NULL ;

/*?????!!!! hardcoded sprache 1 in query *********/

	/*--- get all needed RES_DL_VIEW ---------------*/
	if (aDlid != (int)_UNDEF)
	{
		(void)sprintf( query, _SEL_RESV_DL, aDlid, 1);  /*???! hardcoded sprache 1 */
	}

	/*..... DEBUG ......../
	if (DebugFlag)
		printf("%sAKTresViewDl: sql-query %s%s", _P_EOL_, query, _P_EOL_ );

	/*--- query reservations views -----------------------*/
	if ( strlen(query) > 0)
		status = MPAPIdb_sqlquery((int)_RES_DL_VIEW, (char **)(&resvmem.buffer),
								query, &anzResv, &resvmem.datalen, &resvmem.alloclen );
	else 
		status = (int)MPERROR;

	resview = (RES_DL_VIEW *)resvmem.buffer;
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:	AKTresViewDl_variant
 *					look for all reservation views with Dl id 
 * 				Order by is variable 
 * in:			a dlid
 * out:			array of resview ptrs to fill, numbers 
 * return:		success code
 *---------------------------------------------------------------------------
 */
int AKTresViewDl_variant( int aDlid, int aVariant)
{
	extern 	MEMOBJ		resvmem, *pResvmem; 
	extern 	RES_DL_VIEW	*resview ;
	extern 	int			anzResv;
	extern 	int			DebugFlag;
	extern	int outputsprache;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;
	*query = (char)NULL ;

	/*--- pre-conditions --------------------*/
	if (aDlid == (int)_UNDEF)
		return((int)MPERROR);                                 /*>>>>>> exit >>>>*/

/*?????!!!! hardcoded sprache 1 in query *********/
	/*--- get all needed RES_DL_VIEW ---------------*/
	if (aVariant == VARIANT_0)
		(void)sprintf( query, _SEL_RESV_DL, aDlid, 1);   
	if (aVariant == VARIANT_1)
		(void)sprintf( query, _SEL_RESV_DL_1, aDlid, 1); 

	/*..... DEBUG ......../
	if (DebugFlag)
		printf("%sAKTresViewDl: sql-query %s%s", _P_EOL_, query, _P_EOL_ );

	/*--- query reservations views -----------------------*/
	if ( strlen(query) > 0)
		status = MPAPIdb_sqlquery((int)_RES_DL_VIEW, (char **)(&resvmem.buffer),
								query, &anzResv, &resvmem.datalen, &resvmem.alloclen );
	else 
		status = (int)MPERROR;

	resview = (RES_DL_VIEW *)resvmem.buffer;
	return(status);
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatCopyDate()
 *					collect all date/time in same res structure 
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatCopyDate()
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	DLG_PART				dlg_part;
	DIENSTLEISTUNG		dl;
	int				k, idd; 
	RESERVATION		*pRes;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	for (k=0;  k < anzRes;  k++)
	{
		pRes = &reservation[k];

		/*--- check complete DL ----------------------*/
		if (pRes->dl_id == -1) 
		{
			if ( pRes->a_zeit <= (int)0 )
			{
				idd = MPAPIselectOneId((int)_DIENSTLEISTUNG, pRes->dlg_id, (char *)&dl);
				pRes->a_zeit = dl.a_zeit;
				pRes->e_zeit = dl.a_zeit;        /* force with a_zeit ! */
			}
		}
		else
		{
			/*--- Dl_part -----------------------------*/
			idd = MPAPIselectOneId((int)_DLG_PART, pRes->dl_id, (char *)&dlg_part);
			/*--- Normalize date/time in RES struct ---*/
			if (dlg_part.res_f != _RES_DYNAMIC) 
			{
				pRes->a_zeit = dlg_part.a_zeit;
				pRes->e_zeit = dlg_part.e_zeit;
			}
		}
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatCopySortDate()
 *					collect all date/time in same res structure, order by date 
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatCopySortDate()
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int			(*comparefunc)(void *, void *);

	/*--- copy date from parts so that we are ready to sort -----*/
	AKTreservatCopyDate(); 

	/*--- Order by date/time -------------------------------------------*/
	if (anzRes > 1 )
	{
		comparefunc = AKTcompareResDate;
		qsort((void*)reservation, (size_t)anzRes, (size_t)sizeof(RESERVATION),
			 comparefunc );
	}

#ifdef DEBUG_GING
	for (k=0;  k < anzRes;  k++)
	{
		pRes = &reservation[k];
		fprintf(stderr, "persid:%d, dlg_id:%d, dl_id: %d, teil:%d %s",
						 pRes->pers_id, pRes->dlg_id, pRes->dl_id, pRes->teil, _P_EOL_ );
	}
#endif
}





/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatReplaceDl()
 *					replace the -1 parameter in a reservation with host dl_id
 *  In:			-
 *  out:			-
 *  Return:		-status
 *---------------------------------------------------------------------------
 */
int AKTreservatReplaceDl()
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	DLG_PART			dlg_part;
	int				status, k, idd; 
	RESERVATION		*pRes;

	status = (int)MPOK;
	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	for (k=0;  k < anzRes;  k++)
	{
		pRes = &reservation[k];
		/*--- get complete host DL -------------------*/
		if (pRes->dl_id == -1) 
		{
			idd = MPAPIselectTDL( pRes->dlg_id, &dlg_part);
			pRes->dl_id = dlg_part.dl_id;
		}
	}
	return (status);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatPartsExpand()
 *					check if there are DL with -1 to be expanded 
 *					save the old to ex-reservation array 
 *					expand the DLs with all parts to reservation array 
 *  In:			-
 *  out:			-
 *  Return:		-status 
 *---------------------------------------------------------------------------
 */
int AKTreservatPartsExpand()
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	char		query[2*RECLAENGE];
	int				status, k, n, idd, totalRes; 
	DLG_PART			dlg_part, *pDlg_part;
	RESERVATION		*pRes, *pExres ;
	DLG_DLG			*dlgdlg, *pDlgdlg;
	MEMOBJ			dlgdlgmem,  *pDlgdlgmem;            /* memory for dlg_dlg*/
	int				anzDlgdlg; 
 	MEMOBJ			exresmem; 
	RESERVATION		*exreservation;

	/*--- Init memory objects ------*/
	dlgdlgmem.buffer	 = NULL;     
	dlgdlgmem.alloclen = 0;
	dlgdlgmem.datalen  = 0;
	pDlgdlgmem = &dlgdlgmem;

	/*--- expanded reservation -----*/
	exreservation  = (RESERVATION *)NULL;
	exresmem.buffer = NULL;       
	exresmem.alloclen = 0;
	exresmem.datalen = 0;

	status = (int)MPOK;
	totalRes = 0;

	/*--- Allocate mem and copy compressed ex-reservation --------------*/
	exresmem.datalen =  anzRes * (sizeof(RESERVATION)) ;
	exreservation = (RESERVATION *)MPallocobj( &exresmem, LITTELMEMCHUNK);
	exresmem.buffer = (char *)exreservation;
	(void)memcpy( (void *)(exreservation), (void *)reservation, exresmem.datalen);

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	for (k=0;  k < anzRes;  k++)
	{
		pExres = &exreservation[k];

		/*--- check complete DL -------------------*/
		if (pExres->dl_id == -1) 
		{
			/*---- Get all dlg_dlg's --------*/
			(void)sprintf(query, _SEL_DLG_DLG, pExres->dlg_id);
			status = MPAPIdb_sqlquery((int)_DLG_DLG, (char **)(&dlgdlgmem.buffer),
							query, &anzDlgdlg, &dlgdlgmem.datalen, &dlgdlgmem.alloclen );
			if (status != (int)MPOK)
				return ( status);                           /*>>>> exit >>>>>>>>>*/
			dlgdlg = (DLG_DLG *)dlgdlgmem.buffer;

			/*--- Allocate memory for new reservation struct ------------*/
			resmem.datalen = (totalRes + anzDlgdlg) * (sizeof(RESERVATION)) ;
			reservation = (RESERVATION *)MPallocobj( &resmem, LITTELMEMCHUNK);
			resmem.buffer = (char *)reservation;

			/*-- next free struct -----------------*/
			pRes = &reservation[totalRes] ;

			/*-- Copy parts stuff if more than ONE ----------*/
			for (n=0;  n < anzDlgdlg;  n++)
			{
				/*-- Get DL id and selct TDL --------*/
				pDlgdlg = &dlgdlg[n];
				idd = MPAPIselectOneId((int)_DLG_PART, pDlgdlg->dl_id, (char *)&dlg_part);
				if (idd == (int)_UNDEF)
					return ((int)MPERROR );                 /* >>>>>>>>> exit >>>*/
				
				/*-- copy default DL struct ---------*/
				*pRes = *pExres; 
				
				/*-- Fill with specific part --------*/
				pDlg_part = &dlg_part;
				pRes->dl_id   = pDlg_part->dl_id ; 
				pRes->teil    = pDlg_part->ord ;     

				if (dlg_part.res_f != _RES_DYNAMIC) 
				{
					pRes->a_zeit  = pDlg_part->a_zeit ; 
					pRes->e_zeit  = pDlg_part->e_zeit ; 
				}

				pRes++;           /* next struct */
			}
			/*-- forward subscript ------------*/
			totalRes += anzDlgdlg  ;
		}
		else
		{
			/*--- Allocate memory for new reservation struct ------------*/
			resmem.datalen = (totalRes + 1) * (sizeof(RESERVATION)) ;
			reservation = (RESERVATION *)MPallocobj( &resmem, LITTELMEMCHUNK);
			resmem.buffer = (char *)reservation;

			/*-- next free struct -----------------*/
			pRes = &reservation[totalRes] ;

			/*-- copy ex reservation -------*/
			*pRes = *pExres; 
			pRes++;                                /* next struct */	
			/*-- forward subscript ------------*/
			totalRes += 1  ;
		}
	}
	anzRes = totalRes;

	/*--- conclusion ----------------*/
	MPfree((void *)dlgdlgmem.buffer);
	MPfree((void *)exresmem.buffer);
	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatSortService ()
 *					sort and eliminate duplicate  teil dl in same booking
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatSortService()
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int	k; 
	int 	oldBid, oldDlgId, oldPersid;
	RESERVATION		*pRes;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	oldDlgId  = (int)_UNDEF;
	oldBid  = (int)_UNDEF;
	oldPersid  = (int)_UNDEF;
	for (k=0;  k < anzRes;  k++)
	{
		pRes = &reservation[k];
		/*--- eliminate duplicates keep only new Dl ---*/
		if ((pRes->dlg_id == oldDlgId) && (pRes->bid == oldBid) && (pRes->pers_id == oldPersid))
			pRes->dlg_id = (int)_UNDEF;
      else
         oldDlgId = pRes->dlg_id;
		/*--- rotations -------------------------------*/
		/* oldDlgId = pRes->dlg_id; */
		oldBid = pRes->bid; 
		oldPersid = pRes->pers_id; 
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatSortLeader ()
 *					enable only the leader entries in same booking
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatSortLeader()
{
	extern	RESERVATION	*reservation ;
	extern	int			anzRes;

	int	k; 
	int	oldBid, oldPersid;
	RESERVATION	*pRes;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	oldBid  = (int)_UNDEF;
	oldPersid  = (int)_UNDEF;
	for (k=0;  k < anzRes;  k++)
	{
      pRes = &reservation[k];

      if ( pRes->bid != oldBid )
         oldPersid = pRes->pers_id;

		/*--- eliminate duplicates keep only new Dl ---*/
		if ((pRes->bid == oldBid) && (pRes->pers_id != oldPersid))  
			pRes->dlg_id = (int)_UNDEF;

		/*--- rotations -------------------------------*/ 
		oldBid = pRes->bid; 
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatGetStartDate ()
 *					look for the first date available: Precondition must be sorted! 
 *  In:			-ptr to startDate 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatGetStartDate( time_t *startDate)
{
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	int			k; 
	RESERVATION		*pRes;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	*startDate = 0;
	for (k=0;  k < anzRes;  k++)
	{
		pRes = &reservation[k];
		if (pRes->dlg_id != (int)_UNDEF )
		{
			/*--- get the earliest date of all since ordered --*/
			if ((pRes->a_zeit != 0) && (*startDate == 0))
				*startDate = pRes->a_zeit; 
		}
	}
}



/*F--------------------------------------------------------------------------
 * Function:  AKTactionDetailFind
 *            look for all reservations responding to action type
 * 
 * in:        memory ptr, anzahl, buchung id, personen id, Dlg id, 
 *            aktionstype id 
 * out:       array of AKT_DETAILs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTactionDetailFind( int aBchid, int aPersid, int aDlgid, int anAkttid )
{
	extern 	MEMOBJ		aktdetmem, *pAktdetmem;  
	extern 	AKT_DETAIL	*aktdetail ;
	extern 	int			anzAktdet;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query aktion_detail tables -------*/
	if ((aBchid != (int)_UNDEF) && (aPersid != (int)_UNDEF) &&
		(aDlgid != (int)_UNDEF) && (anAkttid != (int)_UNDEF)    )
		{
		(void)sprintf(query, _SEL_ALL_AKT_DETAIL, aBchid, aPersid, aDlgid, anAkttid);
		status = MPAPIdb_sqlquery((int)_AKT_DETAIL, (char **)(&aktdetmem.buffer),
							query, &anzAktdet, &aktdetmem.datalen, &aktdetmem.alloclen );
		}		
	else 
		status = MPERROR;

	return(status);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatCheckActionType ()
 *					check if all reservations are ok for that action
 *  In:			-res array, number, buchung id, personen id
 *  out:			-changes startDate
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservatCheckActionType( )
{
	extern 	int		akttid;                         /* interface parameter  */
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern 	MEMOBJ		aktdetmem;   
	extern 	int			anzAktdet;

	int	k, status; 
	RESERVATION		*pRes;

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	for (k=0;  k < anzRes;  k++)
		{
		pRes = &reservation[k];
		/*--- Valid Dl ? --------------*/
		if (pRes->dlg_id != (int)_UNDEF )
			{
			/*--- Check if ok for that aktion typ ----------*/
			status = AKTactionDetailFind( pRes->bid, pRes->pers_id, pRes->dlg_id,
                                       akttid);
			if (status != (int)MPOK)
				{
				AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
				continue;
				}
#ifdef DEBUG_GING
	fprintf(stderr, "bid:%d, persid:%d, dlg_id:%d,   anzAktdet: %d %s",
						 pRes->bid, pRes->pers_id, pRes->dlg_id, anzAktdet, _P_EOL_ );
#endif
			/*--- eliminate Dl if not in aktdetail -----*/
			if (anzAktdet <= 0)
				pRes->dlg_id = (int)_UNDEF ;         
			}
		}
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTreservationMini ()
 *					print out reservation text in short form 
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTreservationMini()
{
	extern	FILE			*FPout;
	extern 	MEMOBJ		resmem; 
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	extern 	char 			language[];

	DIENSTLEISTUNG		dl;
	int	k, idd; 
	char	format[_CHAR80+1];
	char	titleTxt[_CHAR80+1];
	char	bezDl[_CHAR80+1];
	char	adate[_DATELEN], azeit[_DATELEN], aday[_DATELEN];      /* anfang */
	RESERVATION		*pRes;

	/*--- inits --------------*/
	*bezDl		= (char)NULL;
	sprintf(format, "%s%s%s%s%s%s", _P_EOL_, COL_DL1, COL_DL2, COL_DL3, COL_DL4, COL_DL5);

	/*--- Services title -----*/
	fprintf(FPout, "%s", _P_EOL_ );
   AKTlayoutLinesAdd( 1 );

	(void)AKTobjtxt( (int)_COMMON_TYP, (int)TEXTID7, titleTxt, NOMARGIN);   
	fprintf(FPout, "%s",  titleTxt);
	AKTlayoutLinesAdd( 1 );                      

	/*--- Loop for all RESERVATIONs  -----------------------------------*/
	for (k=0;  k < anzRes;  k++)
		{
		pRes = &reservation[k];
		/*--- valid dl ? ------------------------------------------*/
		if (pRes->dlg_id != (int)_UNDEF )
			{
			/*--- Dl bez in actual or default language ------*/
			idd = MPAPIselectOneId((int)_DIENSTLEISTUNG, pRes->dlg_id, (char *)&dl);
			(void)AKTobjbez( (int)_DIENSTLEISTUNG, dl.bez_id, bezDl);
			/*--- Date and time -----------------------------*/
			AKTdatetimeday( pRes->a_zeit, adate, azeit, aday, language);
			/*--- Compute/Print out -------------------------------*/
			fprintf(FPout, format, " ", bezDl, aday, " ", adate );
			AKTlayoutLinesAdd( 1 );
			}
		}
	fprintf(FPout, "%s", _P_EOL_);
	AKTlayoutLinesAdd( 1 );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatCheckFirstLeg( int aBid, int aTdlid )
 *					check if the given aTdlid is on the first leg or not
 *  In:			- BuchungsId und HostTeildienstleistung
 *  out:			-
 *  Return:		- status MP_NOT_MATCHING == reservation nicht auf erstem Leg
 *                      MP_MATCHING     == reservation auf dem ersten Leg
 *                      MP_ERROR        == Datanbankfehler
 *---------------------------------------------------------------------------
 */

int AKTreservatCheckFirstLeg( int aBid, int aTdlid )
{
	extern   MEMOBJ		dlgdlgmem; 
	extern   DLG_DLG		*dlgdlg ;
	extern   int			anzDlgdlg;
	extern   int         DebugFlag;

	DLG_PART             *dlg_part;
	DLG_DLG              *aDlgdlg;

	unsigned long  datalength, alloclength;
	int            *Dlgid;
	int				status, i, k;
	int            First_Tdlid;
	int            anzDlg, anzDl;	
	char		      query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MP_NOT_MATCHING;

	/*--- query the first dlg_parts of the host dlid -------*/
	if ( aTdlid != (int)_UNDEF )
	{
		/*--- get first Part of the Hostdlid -------------------*/
		(void)sprintf(query, _SEL_FIRST_DLG_PART, aTdlid, aTdlid );

		anzDl = (int)0;
		alloclength = (unsigned long)0;
      dlg_part = (DLG_PART *)NULL;
		status = MPAPIdb_sqlquery((int)_DLG_PART, (char **)&dlg_part,
										  query, &anzDl, &datalength, &alloclength );
		
		if ( status != (int)MPOK )   /*--- SQL error occurred ---*/
		{
			/*--- Free allocated mem --------------*/
			MPfree((void *)dlg_part);
			return( MP_NOT_MATCHING );
		}
		else
		{
			if ( anzDl > (int)1 )        /*--- not a single record has been found ---*/
			{
				/*--- Free allocated mem --------------*/
				MPfree((void *)dlg_part);
				return( (int)MP_NOT_MATCHING );
			}
			else if ( anzDl == (int)0 )        /*--- there is no detail entry ---*/
			{
				MPfree((void *)dlg_part);
				return( (int)MP_MATCHING );
			}
			else
			{
				First_Tdlid = dlg_part[0].dl_id;
				/*--- Free allocated mem --------------*/
				MPfree((void *)dlg_part);
			}
		}
	}		
	else
		return( (int)MP_NOT_MATCHING );

	anzDlg = (int)0;
	(void)sprintf(query, _SEL_BID_DLG, aBid);
	Dlgid = (int *)NULL;
	alloclength = (unsigned long)0;
	status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&Dlgid, query, &anzDlg,
									  &datalength, &alloclength );

	/*--- Loop over all dlg's -----------------------------------*/
	for (k=0;  k < anzDlg;  k++)
	{
		if ( Dlgid[k] != (int)UNDEF )
		{
			/*--- get all dlg_parts of the reserved dlg ---*/
			status = AKTdlgdlgFindAll( Dlgid[k] );

			if ( status == (int)MPOK )
			{
				/*--- loop over all dlg_dlg entries of the dlg ---*/
				for ( i = 0; i < anzDlgdlg; i++ )
				{
					aDlgdlg = &dlgdlg[i];
					if ( aDlgdlg->dl_id == First_Tdlid )
					{
						if (DebugFlag)
							fprintf(stderr, "Bid %d : First Part matches %d%s", aBid, First_Tdlid, _P_EOL_ );
						/*--- Free allocated mem --------------*/
						MPfree((void *)Dlgid);						
						return( (int)MP_MATCHING );
					}
				}
			}
		}
	}
	
	if (DebugFlag)
		fprintf(stderr, "Bid %d : First Part NOT found %d%s", aBid, First_Tdlid, _P_EOL_ );

	/*--- Free allocated mem --------------*/
	MPfree((void *)Dlgid);
	return ( (int)MP_NOT_MATCHING );
}




/*F--------------------------------------------------------------------------
 *  Function:	AKTreservatChangeZusatzbett( int aDlgId, int aZusatzid )
 *					Change to Zusatzbett 
 *  In:			- Zusatzbett TypId
 *  out:			-
 *  Return:		- return:    success code
 *---------------------------------------------------------------------------
 */

void AKTreservatChangeZusatzbett( int aDlgId, int aZusatzid )
{
	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;
	
	RESERVATION				*pRes ;
	int                  found, type;
	char	               tmpBuf[_TEXTLEN+1];
	char	               *ptr, *bufptr;
	
	int		j;
	

	/*--- check presence in DB types -------------------*/
	(void)AKTobjtxt((int)_COMMON_TYP, (int)AKTCOM_KAT_ZUSATZ, tmpBuf, NOMARGIN);

	for (j=0;  j < anzRes;  j++)     /* force zusatzbett */
	{
		pRes = &reservation[j];
		if ( aDlgId == pRes->dlg_id )      /* only for this dlg */
		{	
			bufptr = tmpBuf;
			found = 0;
			while ((ptr = strchr(bufptr, '$')) != NULL)
			{
				ptr++ ;
				type = atoi(ptr);
				bufptr = ptr;
				if ( pRes->kat_id == type )
				{ 
					found = 1 ;
					break;
				} 
			}
			
			if ( ! found )
			{
				pRes->typ_id = aZusatzid ;
			}				
		}
	}
}


/*SF-------------------------------------------------------------------------
 *  function:	AKTreservatGetStrechFrom
 *  				Create the From To Strech of a Teil
 *					
 *  In:			- a PersId, a Part, 
 *  out:			- a Strech
 *  Return:		- return:    success code
 *---------------------------------------------------------------------------
 */
int AKTreservatGetStrechFrom ( int aPersId, int aTeil, char *aFrom, char *aTo )
{
	extern 	DLG_PART			tdl;
	extern 	DIENST_ANGEBOT	dla;
	extern 	RESERVATION	   *reservation ;
	extern 	int			   anzRes;

	RESERVATION	            *pRes;
	DLG_PART			         aTdl;
	DIENST_ANGEBOT	         aDla;
	ORT				         aOrt;

	int	                  i, status, id;
	int                     firstpart, lastpart;

	/*--- init --------*/
	status = (int)MPOK;

	*aFrom = '\0';
	*aTo   = '\0';

	firstpart = (int)TRUE;
	lastpart = (int)FALSE;

	for ( i=0; i<anzRes; i++ )
	{
		pRes = &reservation[i];

		/* skip entries that do not belong to arguments */
		if ( pRes->teil != aTeil || pRes->pers_id != aPersId )
			continue;

		/*--- DLA_TYP suchen ----------------------*/
		id = MPAPIselectOneId((int)_DLG_PART, pRes->dl_id, (char *)&aTdl );
		if (id == (int)_UNDEF)
			return ( (int)MPERROR );                             /* >>>> exit >>>*/

		id = MPAPIselectOneId((int)_DIENST_ANGEBOT, aTdl.dla_id, (char *)&aDla );
		if (id == (int)_UNDEF)
			return ( (int)MPERROR );                             /* >>>> exit >>>*/
			
		/*--- Erster Teil der Strecke ---*/
		if ( firstpart == (int)TRUE )
		{
			/*--- Von Ort der Strecke ----*/
			id = MPAPIselectOneId ( (int)_ORT, aDla.von, (char*)&aOrt );
			if ( id != (int)_UNDEF )
			{
				(void)copyTextTo( aFrom, aOrt.krzl, 3 );
			}
			else
				(void)strcpy ( aFrom, "-" );
			
			firstpart = (int)FALSE;
			lastpart = (int)TRUE;
		}
			
		/*--- Last part of the individual route ---*/
		if ( lastpart == (int)TRUE )
		{
			/*--- Von Ort der Strecke ----*/
			id = MPAPIselectOneId ( (int)_ORT, aDla.nach, (char*)&aOrt );
			if ( id != (int)_UNDEF )
				(void)copyTextTo( aTo, aOrt.krzl, 3 );
			else
				(void)strcpy ( aTo, "-" );
		}
	}

	return(status);
}


