/*D***********************************************************
 * Name:      AKTbook.c
 *                                                            
 * Modul:     AKT base moduls
 *            Handle booking selection for several actions
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTbook.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/

/*--- SQL ------------------------------------------------------------------*/
#define	_SEL_BID_CRU	"SELECT DISTINCT AD.BID FROM TDBADMIN.AKT_DETAIL AD \
	WHERE AD.DL_ID = %d;"

#define	_SEL_BID_GRU	"SELECT DISTINCT AD.BID \
	FROM TDBADMIN.BUCHUNG B, TDBADMIN.AKT_DETAIL AD \
	WHERE AD.DL_ID = %d \
	AND B.K_ID = %d \
	AND B.BID = AD.BID;"

#define	_SEL_BCH_CRU	"SELECT * FROM TDBADMIN.BUCHUNG \
	WHERE BID IN (%s) \
	ORDER BY K_ID, KID, BID;"


#define	_SEL_BID_KOL	"SELECT B.BID FROM TDBADMIN.BUCHUNG B \
	WHERE B.K_ID = %d ;"

#define	_SEL_BID_KUN	"SELECT B.BID FROM TDBADMIN.BUCHUNG B \
	WHERE B.KID = %d ;"

#define	_SEL_BID_TDL_KUN	"SELECT DISTINCT AD.BID \
	FROM TDBADMIN.BUCHUNG B, TDBADMIN.AKT_DETAIL AD \
	WHERE AD.DL_ID = %d \
	AND B.KID = %d \
	AND B.BID = AD.BID;"

#define _SEL_ALL_DLN_BCH		"SELECT BD.* \
	FROM TDBADMIN.DLN_VIEW DLN, TDBADMIN.BCH_DLN BD  \
	WHERE BD.BID = %d AND DLN.DLN_ID = BD.DLN_ID \
	ORDER BY BD.DLN_ID ;"

#define _SEL_ALL_DLN_BCH_KOL	"SELECT BD.* \
	FROM TDBADMIN.DLN_VIEW DLN, TDBADMIN.BCH_DLN BD  \
	WHERE BD.BID IN (%s)  AND DLN.DLN_ID = BD.DLN_ID \
	ORDER BY BD.DLN_ID ;"

#define _SEL_KAT_DLT   "select * from root.kat_view \
   where kat_id in ( select distinct kat_id  \
                     from root.dienst_traeger \
                     where host_id = %d ) \
	and s_id = %d \
	order by bez;"

/*F--------------------------------------------------------------------------
 * Function:  AKTbchdlnMemobjectInit
 *            init memory for reservations operations 
 *---------------------------------------------------------------------------
 */
void AKTbchdlnMemobjectInit( )
{
	extern 	MEMOBJ	bchmem, *pBchmem; 
	extern 	BUCHUNG	*buchung	;
	extern	int		anzBch ;
	extern 	MEMOBJ	dlnmem, *pDlnmem; 
	extern 	BCH_DLN	*bchdln	;
	extern	int		anzBd ;

	/*--- Buchung -----------*/
	buchung   = (BUCHUNG *)NULL;
	bchmem.buffer   = NULL;      
	bchmem.alloclen = 0;
	bchmem.datalen  = 0;
	pBchmem   = &bchmem;
	anzBch    = 0;

	/*-- dln ----------------*/
	bchdln   = (BCH_DLN *)NULL;
	dlnmem.buffer   = NULL;       
	dlnmem.alloclen = 0;
	dlnmem.datalen  = 0;
	pDlnmem  = &dlnmem;
	anzBd   	= 0;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTbchdlnMemobjectFree
 *            free the memory and init for next use 
 *---------------------------------------------------------------------------
 */
void AKTbchdlnMemobjectFree( )
{
	extern 	MEMOBJ	bchmem, *pBchmem; 
	extern 	BUCHUNG	*buchung	;
	extern 	MEMOBJ	dlnmem, *pDlnmem; 
	extern 	BCH_DLN	*bchdln	;

	/*--- Free from heap ------*/
	MPfreeobj(&bchmem);
	MPfreeobj(&dlnmem);

	/*--- re-init structure ---*/
	AKTbchdlnMemobjectInit();
}



/*F--------------------------------------------------------------------------
 * Function:  AKTbchFindAll
 *            look for all booking with correct selection 
 * in:        
 * out:
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTbchFindAll( MEMOBJ *pBchmem, int *anzBch, int bchid, int kolid, int tdlid, int kunid)
{
	int		status, i, id;
	unsigned long datalength, alloclength;
	int		anzBid, *bid;
	char		query[4*RECLAENGE]; 
	char		c_bid[4*RECLAENGE];
	char		c_id[_CHAR10];
	
	/*--- general inits ------------*/
	status = (int)MPOK ;
	
	/*--- test for priorities -----------*/
	if ((kolid != (int)UNDEF) && (tdlid != (int)_UNDEF))   /*-- kollectiv ---*/
	{
		anzBid = (int)0;
		(void)sprintf(query, _SEL_BID_GRU, tdlid, kolid);
		bid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&bid, query, &anzBid,
										  &datalength, &alloclength );
		/*--- prepare dl parts ---------*/
		for(i=0, *c_bid=NULL;  i<anzBid;  i++)
		{
			(void)sprintf(c_id, "%d,", bid[i]);
			(void)strcat(c_bid, c_id);
		}
		if ( anzBid > 0)
			c_bid[strlen(c_bid)-1] = NULL;

		/*--- Free allocated mem --------------*/
		MPfree((void *)bid);

	}
	else if ((kunid != (int)UNDEF) && (tdlid != (int)_UNDEF))   /*-- kunde ---*/
	{
		anzBid = (int)0;
		(void)sprintf(query, _SEL_BID_TDL_KUN, tdlid, kunid);
		bid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&bid, query, &anzBid,
										  &datalength, &alloclength );
		/*--- prepare dl parts ---------*/
		for(i=0, *c_bid=NULL;  i<anzBid;  i++)
		{
			(void)sprintf(c_id, "%d,", bid[i]);
			(void)strcat(c_bid, c_id);
		}
		if ( anzBid > 0)
			c_bid[strlen(c_bid)-1] = NULL;

		/*--- Free allocated mem --------------*/
		MPfree((void *)bid);

	}
	else if (bchid != (int)_UNDEF)         /*--- buchung ----------*/
	{
		anzBid = (int)1;
		(void)sprintf(c_bid, "%d", bchid);
	}
	else if (kunid != (int)_UNDEF)         /*--- Bch eines Kunden ---------*/
	{
		anzBid = (int)0;
		(void)sprintf(query, _SEL_BID_KUN, kunid);
		bid = (int *)NULL;
		alloclength = (unsigned long)0;  
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&bid, query, &anzBid,
										  &datalength, &alloclength );
		for(i=0, *c_bid=NULL;  i<anzBid;  i++)
		{
			(void)sprintf(c_id, "%d,", bid[i]);
			(void)strcat(c_bid, c_id);
		}
		if ( anzBid > 0)
			c_bid[strlen(c_bid)-1] = NULL;                   /*suppress comma */

		/*--- Free allocated mem --------------*/
		MPfree((void *)bid);

	}
	else if (tdlid != (int)_UNDEF)         /*--- dl parts ---------*/
	{
		anzBid = (int)0;
		(void)sprintf(query, _SEL_BID_CRU, tdlid);
		bid = (int *)NULL;
		alloclength = (unsigned long)0;  
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&bid, query, &anzBid,
										  &datalength, &alloclength );
		for(i=0, *c_bid=NULL;  i<anzBid;  i++)
		{
			(void)sprintf(c_id, "%d,", bid[i]);
			(void)strcat(c_bid, c_id);
		}
		if ( anzBid > 0)
			c_bid[strlen(c_bid)-1] = NULL;                   /*suppress comma */

		/*--- Free allocated mem --------------*/
		MPfree((void *)bid);

	}
	
	/*--- Find all of bookings -------------------------------------------*/
	if ((status == (int)MPOK) && (anzBid > 0))
	{
		(void)sprintf(query, _SEL_BCH_CRU, c_bid);
		status = MPAPIdb_sqlquery((int)_BUCHUNG, (char **)(&pBchmem->buffer), query,
										  anzBch, &pBchmem->datalen, &pBchmem->alloclen );
	}		
	else 
		status = MPERROR;
	
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTdlnFindAll
 *            look for all DLN views with correct selection 
 * 
 * in:        buchung id 
 * out:       array of DLNs ptrs to fill, numbers 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTdlnFindAll( MEMOBJ *pDlnmem, int *anzBd, int bchid, int kolid )
{
	int		status, i, id;
	char		query[2*RECLAENGE];
	unsigned long datalength, alloclength;
	int		anzBid, *bid;
	char		c_bid[2*RECLAENGE];
	char		c_id[_CHAR10];
	
	/*--- general inits ------------*/
	status = (int)MPOK ;
	
	/*--- query bch dln ------------*/
	if (kolid != (int)UNDEF)          /*--- group kollectiv booking --*/
	{
		anzBid = (int)0;
		(void)sprintf(query, _SEL_BID_KOL, kolid);
		bid = (int *)NULL;
		alloclength = (unsigned long)0;
		status = MPAPIdb_sqlquery((int)_INTEGER, (char **)&bid, query, &anzBid,
										  &datalength, &alloclength );
		/*--- prepare bid list ---------*/
		for(i=0, *c_bid=NULL;  i<anzBid;  i++)
		{
			(void)sprintf(c_id, "%d,", bid[i]);                 /* comma separeted list */
			(void)strcat(c_bid, c_id);                          /* add to list */
		}
		if ((status == (int)MPOK) && (anzBid > 0))
		{
			c_bid[strlen(c_bid)-1] = NULL;                    /* suppress comma */
			/*--- get all dlnv for the prepared bids -----*/
			(void)sprintf(query, _SEL_ALL_DLN_BCH_KOL, c_bid);
			status = MPAPIdb_sqlquery((int)_BCH_DLN, (char **)(&pDlnmem->buffer), query,
											  anzBd, &pDlnmem->datalen, &pDlnmem->alloclen );
		}
		else
		{
			status = MPERROR;
		}
	}
	else if (bchid != (int)_UNDEF)    /*--- single booking --------*/
	{
		(void)sprintf(query, _SEL_ALL_DLN_BCH, bchid);
		status = MPAPIdb_sqlquery((int)_BCH_DLN, (char **)(&pDlnmem->buffer), query,
										  anzBd, &pDlnmem->datalen, &pDlnmem->alloclen );
	}		
	
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTbchOrderByDltKat
 *            order the buchung array by the Cruise Category 
 * 
 * in:        aTdlid
 * out:       . 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTbchOrderByDltKat( int aTdlid, int OrderByFlag )
{
	extern BUCHUNG *buchung;
	extern int     anzBch;
	extern int     sprache;

	extern 	RESERVATION	*reservation ;
	extern 	int			anzRes;

	/*--- bchdln -------------*/
	extern 	MEMOBJ		dlnmem, *pDlnmem; 
	extern 	BCH_DLN		*bchdln	;
	extern	int			anzBd;
	/*--- kat_view -------------*/
	MEMOBJ		   katvmem, *pKatvmem;
	KAT_VIEW	      *kat_view ;
	KAT_VIEW	      *pkatv ;
	int			   anzKatv;

	DIENST_TRAEGER	hostDlt;
	BUCHUNG        *tmpbchBuffer;
	int		      status, i, j, k, id, ires;
	int            l, start, end, old_kolid;
	unsigned long  alloclen;
	char		      query[2*RECLAENGE]; 
	
	/*--- general inits ------------*/
	status           = (int)MPOK ;
	alloclen         = (unsigned long)0;
	tmpbchBuffer     = (BUCHUNG *)NULL;
	/*--- Kat_view -----------*/
	kat_view         = (KAT_VIEW *)NULL;
	katvmem.buffer   = NULL;      
	katvmem.alloclen = 0;
	katvmem.datalen  = 0;
	pKatvmem         = &katvmem;
	anzKatv          = 0;
	
	id = MPAPIselectDLT ( _UNDEF, aTdlid, _UNDEF, &hostDlt );

	/* Kein DLT zu aTdlid gefunden kein Problem */
	if ( id == (int)_UNDEF )
		return(status);

	/* alle Kategorien des DLT's lesen */
	(void)sprintf( query, _SEL_KAT_DLT, hostDlt.dlt_id, sprache );
	status = MPAPIdb_sqlquery((int)_KAT_VIEW, (char **)(&pKatvmem->buffer), query,
									  &anzKatv, &pKatvmem->datalen, &pKatvmem->alloclen );
	kat_view = (KAT_VIEW *)pKatvmem->buffer;
	
	/*--- check all kat_views -------------------------------------------*/
	if ((status == (int)MPOK) && (anzKatv > 0))
	{
		/* allocate memory for the temp BchBuffer */
		tmpbchBuffer = (BUCHUNG *)MPalloc((void *)NULL, &alloclen,
									  anzBch*sizeof(BUCHUNG), anzBch, sizeof(BUCHUNG));

		/* assign the kat_id to each bid using the dbid field in tmpbchBuffer */
		memcpy( (void *)tmpbchBuffer, (void *)buchung,
				 (size_t)(anzBch*sizeof(BUCHUNG)) );

		for ( i=0; i < anzBch; i++ )
		{
			/*--- Get all DLNs Reisender of current booking -----------------------*/
			status = AKTdlnFindAll( pDlnmem, &anzBd, buchung[i].bid, (int)_UNDEF  );
			if (status != (int)MPOK)
			{
				AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
				return ((int)MPERROR) ;                          			 /*>>>>> exit */
			}
			bchdln = (BCH_DLN *)dlnmem.buffer;

			if ( anzBd > 0 )
			{
				/*--- get all Reservations ----------------*/
				status = AKTreservatFindAll( bchdln[0].bid, bchdln[0].dln_id );
				if (status != (int)MPOK)
				{
					AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
					return (status) ;                          			 /*>>>>> exit */
				}
				AKTreservatReplaceDl();

				tmpbchBuffer[i].d_bid = (int)_UNDEF;
				for ( ires=0; ires < anzRes; ires++ )
				{
					if ( reservation[ires].dl_id == aTdlid )
					{
						tmpbchBuffer[i].d_bid = reservation[ires].kat_id;
						break;
					}
				}
			}
		} /* Ende for ( i=0; i < anzBch; i++ ) */

		if ( OrderByFlag == BCH_ORDER_BY_KAT_ALL )
		{
			/* build a buffer with new order */
			for ( k=0, j=0; k < anzKatv; k++ )
			{
				pkatv = &kat_view[k];
				/* check each buchung if the kat_id is related */
				for ( i=0; i < anzBch; i++ )
				{
					if ( tmpbchBuffer[i].bid != (int)_UNDEF &&
						 tmpbchBuffer[i].d_bid == pkatv->kat_id )
					{
						tmpbchBuffer[i].d_bid = (int)_UNDEF;
						memcpy( (void *)&(buchung[j]), 
								 (void *)&(tmpbchBuffer[i]), sizeof(BUCHUNG) );
						tmpbchBuffer[i].bid = (int)_UNDEF;
						j++;
					}
				} /* Ende i-Loop */ 
			} /* Ende k-Loop */
		}
		else if ( OrderByFlag == BCH_ORDER_BY_KAT_KOL )
		{
			old_kolid = tmpbchBuffer[0].k_id;
			start = 0;

			/* build a buffer with new order */
			for ( l=0, j=0; l <= anzBch; l++ )
			{
				if ( old_kolid != tmpbchBuffer[l].k_id || l >= anzBch )
				{
					end = l;
					for ( k=0; k < anzKatv; k++ )
					{
						pkatv = &kat_view[k];
						/* check each buchung if the kat_id is related */
						for ( i=start; i < end; i++ )
						{
							if ( tmpbchBuffer[i].bid != (int)_UNDEF &&
								 tmpbchBuffer[i].d_bid == pkatv->kat_id )
							{
								tmpbchBuffer[i].d_bid = (int)_UNDEF;
								memcpy( (void *)&(buchung[j]), 
										 (void *)&(tmpbchBuffer[i]), sizeof(BUCHUNG) );
								tmpbchBuffer[i].bid = (int)_UNDEF;
								j++;
							}
						} /* Ende i-Loop */ 
					} /* Ende k-Loop */
					start = end;
				}
				if ( l < anzBch )
					old_kolid = tmpbchBuffer[l].k_id;
			} /* Ende l-Loop */
		}
	}		
 
	/*--- Free allocated mem --------------*/
	MPfreeobj(&katvmem);
	MPfreeobj(&tmpbchBuffer);
		
	return(status);
}




