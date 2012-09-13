/*D***********************************************************
 * Name:      AKTdienst.c
 *                                                            
 * Modul:     AKT base moduls
 *            Handle DL and TDL  
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdienst.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/



/*P--- PROTOTYPES ----------------------------------------------------------*/


/*P--- LAYOUT --------------------------------------------------------------*/


/*P--- GLOBALS  -----------------------------------------------------------*/


/*--- SQL ------------------------------------------------------------------*/
#define _SEL_DLG_DLG		"SELECT * FROM TDBADMIN.DLG_DLG \
								WHERE DLG_ID = %d  ORDER BY ORD ;"
                               


/*F--------------------------------------------------------------------------
 * Function:  AKTdlgdlgMemobjInit
 *            init memory for  dl  operations 
 *---------------------------------------------------------------------------
 */
void AKTdlgdlgMemobjInit( )
{
	extern 	MEMOBJ		dlgdlgmem; 
	extern 	DLG_DLG		*dlgdlg ;

	/*--- reservation --------------*/
	dlgdlg  = (DLG_DLG *)NULL;
	dlgdlgmem.buffer = NULL;       
	dlgdlgmem.alloclen = 0;
	dlgdlgmem.datalen = 0;
}


/*F--------------------------------------------------------------------------
 * Function:  AKTdlgdlgMemobjFree
 *            free memory of dlgdlg objects  
 *---------------------------------------------------------------------------
 */
void AKTdlgdlgMemobjFree( )
{
	extern 	MEMOBJ		dlgdlgmem; 
	extern 	DLG_DLG		*dlgdlg ;

	/*--- free mem --------------*/
	MPfreeobj(&dlgdlgmem);
	/*--- prepare for next usage ---*/
	AKTdlgdlgMemobjInit();
}


/*F--------------------------------------------------------------------------
 * Function:  AKTdlgdlgFindAll
 *            look for all dlgdlg structures  
 * 
 * in:        arr id 
 * out:       array of arr dl views 
 * return:    success code
 *---------------------------------------------------------------------------
 */
int AKTdlgdlgFindAll( int aDlid )
{
	extern 	MEMOBJ		dlgdlgmem; 
	extern 	DLG_DLG		*dlgdlg ;
	extern 	int			anzDlgdlg;

	int		status;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

	/*--- query reservations -------*/
	if (aDlid != (int)_UNDEF) 
	{
		(void)sprintf(query, _SEL_DLG_DLG, aDlid);
		status = MPAPIdb_sqlquery((int)_DLG_DLG, (char **)(&dlgdlgmem.buffer),
										  query, &anzDlgdlg, &dlgdlgmem.datalen, &dlgdlgmem.alloclen );
	}		
	else 
		status = (int)MPERROR;

	dlgdlg = (DLG_DLG *)dlgdlgmem.buffer;
	return(status);
}





