/*D***********************************************************
 * Name:      AKTarrang.c
 *                                                            
 * Modul:     AKT base modules
 *            Handle arrangements 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTarrang.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/



/*P--- PROTOTYPES ----------------------------------------------------------*/


/*P--- LAYOUT --------------------------------------------------------------*/


/*P--- GLOBALS  -----------------------------------------------------------*/


/*--- SQL ------------------------------------------------------------------*/
#define _SEL_ARRDLVIEW		"SELECT * FROM TDBADMIN.ARR_DL_VIEW \
	WHERE ARR_ID = %d AND S_ID = 1 \
	ORDER BY TEIL, DLG_ID ;"

#define _SEL_DLG_DLG		"SELECT * FROM TDBADMIN.DLG_DLG \
	WHERE DL_ID IN (SELECT DL_ID FROM TDBADMIN.DLG_DLG \
                   WHERE DLG_ID = %d ) \
	ORDER BY DLG_ID, ORD;"
                               
#define _SEL_ARR_PRG		"SELECT * FROM TDBADMIN.ARRANGEMENT \
	WHERE PRG_ID = %d  \
	ORDER BY A_DAT ;"

#define _SEL_ARR_ALL		"SELECT * FROM TDBADMIN.ARRANGEMENT \
	WHERE ARR_ID >= 0  \
	ORDER BY A_DAT ;"

/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlViewMemobjInit
 *            init memory for arrangement operations 
 *---------------------------------------------------------------------------
 */
void AKTarrgtMemobjInit( )
{
	extern 	MEMOBJ		arrgtmem; 
	extern 	ARRANGEMENT	*arrangement ;
	extern 	int			anzArrgt;

	/*--- reservation --------------*/
	arrangement  = (ARRANGEMENT *)NULL;
	arrgtmem.buffer = NULL;       
	arrgtmem.alloclen = 0;
	arrgtmem.datalen = 0;
	anzArrgt = 0;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTarrgtMemobjFree
 *            free memory containing array of structs 
 *---------------------------------------------------------------------------
 */
void AKTarrgtMemobjFree( )
{
	extern 	MEMOBJ		arrgtmem; 
	extern 	ARRANGEMENT	*arrangement ;

	/*--- reservation --------------*/
	MPfreeobj( &arrgtmem);
	/*--- prepare for next usage ---*/
	AKTarrDlViewMemobjInit();
}


/*F--------------------------------------------------------------------------
 * Function:  AKTarrgtGetAll
 *            look for all arrangements 
 * 
 * in:        a Programm  id 
 * out:       array of arr 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTarrgtGetAll( int aProgid )
{
	extern 	MEMOBJ		arrgtmem; 
	extern 	ARRANGEMENT	*arrangement ;
	extern 	int			anzArrgt;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aProgid != (int)_UNDEF) 
		(void)sprintf(query, _SEL_ARR_PRG, aProgid);
	else 
		(void)sprintf(query, _SEL_ARR_ALL );

	status = MPAPIdb_sqlquery((int)_ARRANGEMENT, (char **)(&arrgtmem.buffer),
										  query, &anzArrgt, &arrgtmem.datalen, &arrgtmem.alloclen );

	arrangement = (ARRANGEMENT *)arrgtmem.buffer;
	return(status);
}



/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlViewMemobjInit
 *            init memory for arrangement dl view operations 
 *---------------------------------------------------------------------------
 */
void AKTarrDlViewMemobjInit( )
{
	extern 	MEMOBJ		arrdlvmem, *pArrdlvmem; 
	extern 	ARRDL_VIEW	*arrdlview ;

	/*--- reservation --------------*/
	arrdlview  = (ARRDL_VIEW *)NULL;
	arrdlvmem.buffer = NULL;       
	arrdlvmem.alloclen = 0;
	arrdlvmem.datalen = 0;
	pArrdlvmem    = &arrdlvmem;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlViewMemobjFree
 *            free memory containing array of structs 
 *---------------------------------------------------------------------------
 */
void AKTarrDlViewMemobjFree( )
{
	extern 	MEMOBJ		arrdlvmem, *pArrdlvmem; 
	extern 	ARRDL_VIEW	*arrdlview ;

	/*--- reservation --------------*/
	MPfreeobj(&arrdlvmem);
	/*--- prepare for next usage ---*/
	AKTarrDlViewMemobjInit();
}



/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlView
 *            look for all arrangements 
 * 
 * in:        arr id 
 * out:       array of arr dl views 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTarrDlView( int aArrid )
{
	extern 	MEMOBJ		arrdlvmem, *pArrdlvmem; 
	extern 	ARRDL_VIEW	*arrdlview ;
	extern 	int			anzArrdl;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aArrid != (int)_UNDEF) 
	{
		(void)sprintf(query, _SEL_ARRDLVIEW, aArrid);
		status = MPAPIdb_sqlquery((int)_ARRDL_VIEW, (char **)(&arrdlvmem.buffer),
										  query, &anzArrdl, &arrdlvmem.datalen, &arrdlvmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	arrdlview = (ARRDL_VIEW *)arrdlvmem.buffer;
	return(status);
}

/*F--------------------------------------------------------------------------
 * Function:  AKTarrGiveAllDlgFor
 *            look for all dlg's that includes parts of aDlgid 
 * 
 * in:        arr id 
 * out:       array of arr dl views 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTarrGiveAllDlgFor( int aDlgid )
{
	extern 	MEMOBJ		dlgdlgmem, *pDlgdlgmem; 
	extern 	DLG_DLG		*dlgdlg;
	extern 	int			anzDlgdlg;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aDlgid != (int)_UNDEF) 
	{
		(void)sprintf(query, _SEL_DLG_DLG, aDlgid);
		status = MPAPIdb_sqlquery((int)_DLG_DLG, (char **)(&dlgdlgmem.buffer),
										  query, &anzDlgdlg, &dlgdlgmem.datalen, &dlgdlgmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	dlgdlg = (DLG_DLG *)dlgdlgmem.buffer;
	return(status);
}


/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlgdlgMemobjInit
 *            init memory for dlg_dlg operations 
 *---------------------------------------------------------------------------
 */
void AKTarrDlgdlgMemobjInit( )
{
	extern 	MEMOBJ		dlgdlgmem; 
	extern 	DLG_DLG		*dlgdlg ;
	extern 	int			anzDlgdlg;

	/*--- reservation --------------*/
	dlgdlg  = (DLG_DLG *)NULL;
	dlgdlgmem.buffer = NULL;       
	dlgdlgmem.alloclen = 0;
	dlgdlgmem.datalen = 0;
	anzDlgdlg = 0;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTarrDlgdlgMemobjFree
 *            free memory containing array of structs 
 *---------------------------------------------------------------------------
 */
void AKTarrDlgdlgMemobjFree( )
{
	extern 	MEMOBJ	dlgdlgmem, *pDlgdlgmem; 
	extern 	DLG_DLG	*dlgdlg ;

	/*--- reservation --------------*/
	MPfreeobj(&dlgdlgmem);
	/*--- prepare for next usage ---*/
	AKTarrDlgdlgMemobjInit();
}
