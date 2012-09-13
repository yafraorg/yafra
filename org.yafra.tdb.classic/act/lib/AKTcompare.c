/*D***********************************************************
 * Name:      AKTcompare.c
 *                                                            
 * Modul:     AKT base moduls
 *            Comparison algorithms for various objects 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTcompare.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/
/*--- reservation --------*/
extern	MEMOBJ	resmem, *pResmem;                      /* memory for work */
extern	RESERVATION	*reservation ;
extern	int		anzRes;


/*-------------------- PROTOTYPES -----------------------------------------*/
unsigned char AKTcompareMakeCs( unsigned char *element, int nbelements );



/*F************************************************************
 * Function:  AKTcompareDlnRes
 *            Compare the DLN's reservations 
 * 
 * in:        array of dlnviews, number of views
 * out:       value 1=identical
 * return:    success code 
 **************************************************************/
int AKTcompareDlnRes( int aBid, BCH_DLN *bd, int anzBd, int *compstat )
{
	int		status, j, k;
	int		anzBid, *bid, tmpPersid;
	MEMOBJ	csmem,  *pCsmem;                       /* memory for checksum */
	int		*pChecksum;
	unsigned char		aChecksum;
	int		equal; 
	RESERVATION		*pRes;

	/*--- Init memory objects ------*/
	csmem.buffer	= NULL;     /* checksums */
	csmem.alloclen	= 0;
	csmem.datalen  = 0;
	pCsmem = &csmem;

	status = MPOK;

	/*--- allocate array of Checksums -------*/
	csmem.datalen = anzBd * (sizeof(int *)) ;
	pChecksum = (int *)MPallocobj( &csmem, LITTELMEMCHUNK);

	/*--- Loop for all DLN in bd Buffer -------------------------------*/
	/*----------------------------------------------------------------------*/
	for (j = 0;  j < anzBd;  j++)
	{
		/*--- select all Reservations for current DLN person ----------------*/
		status = AKTreservatFindAll( aBid, bd[j].dln_id );
		if (status != (int)MPOK)
			return(status);                                      /*>>>>> exit */

		/*--- Compute CS for all RESERVATIONs but without pers_id  ----*/
		aChecksum = 0;
		for (k=0;  k < anzRes;  k++)
		{
			pRes = &reservation[k] ;
			/*-- remove since it is different and restore later ---*/
			tmpPersid = pRes->pers_id;
			pRes->pers_id = -1 ;
			/*--- compute checksum of reservation ---*/
			aChecksum = aChecksum ^ AKTcompareMakeCs((unsigned char *) (pRes),
											sizeof(reservation[k])/sizeof(unsigned char) ); 
			pRes->pers_id = tmpPersid ;
		}

		/*--- store checksum of one dln ----*/
		pChecksum[j] = aChecksum; 
	}

	/*--- compare checksums and set status --------------------------------*/
	aChecksum = pChecksum[0];
	for (j = 0, equal = 1;  (j < anzBd) && (equal == 1);  j++)
	{
		if (aChecksum != pChecksum[j])                     /* fail if ONE diff */
			equal = 0 ;
	}
	if (equal) 
		*compstat = 1;
	else
		*compstat = 0;

	/*--- conclusion ----------------*/
	MPfree((void *)csmem.buffer);

	return(status);
}



/*F************************************************************
 * Function:  AKTcompareMakeCs
 *            Compare the DLN's reservations 
 * 
 * in:        array of elements, number of elements
 * out:       
 * return:    success code 
 **************************************************************/
unsigned char AKTcompareMakeCs( unsigned char *element, int nbelements )
{
	int				i; 
	unsigned char	checksum;

	/*--- compute for all elements ---------*/
	checksum = 0; 
	for (i=0;  i < nbelements;  i++)
	{
		/*--- compute checksum of reservation ---*/
		checksum = checksum ^ element[i] ; 
	}
	return(checksum); 
}



/*F************************************************************
 * Function:  AKTcompareResDate
 *            Compare the Reservation's date/times (a_zeit) 
 * 
 * in:        two resevations
 * out:       
 * return:    result (lt:-1, eq:0, gt:1) 
 **************************************************************/
int AKTcompareResDate( RESERVATION *resA, RESERVATION *resB )
{
	int				result; 

	/*--- compare a_zeit ---------*/
	if (resA->teil == resB->teil && resA->a_zeit == resB->a_zeit)
		return(0);
 
	if (resA->teil > resB->teil && resA->a_zeit > resB->a_zeit)
		return(1);
	if (resA->teil == resB->teil && resA->a_zeit > resB->a_zeit)
		return(1);
	if (resA->teil > resB->teil && resA->a_zeit == resB->a_zeit)
		return(1);
	if (resA->teil > resB->teil && resA->a_zeit < resB->a_zeit)
		return(1); 
 
	if (resA->teil < resB->teil && resA->a_zeit < resB->a_zeit)
		return(-1);
	if (resA->teil == resB->teil && resA->a_zeit < resB->a_zeit)
		return(-1);
	if (resA->teil < resB->teil && resA->a_zeit == resB->a_zeit)
		return(-1);
	if (resA->teil < resB->teil && resA->a_zeit > resB->a_zeit)
		return(-1);
}
