/*D***********************************************************
 * Name:      AKTdln.c
 *                                                            
 * Modul:     AKT base moduls  
 *            Handle DLN reisenden functions
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdln.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/


/*--- LAYOUT ---------------------------------------------------------------*/


/*--- GLOBALS -------------------------------------------------------------*/





/*F--------------------------------------------------------------------------
 *  Function:	AKTdlnGetNames ()
 *					write single participant to travel 
 *  In:			-the current DLNid, where to write, format
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTdlnGetNames( int aDlnid, char* aTargetText, char* aFormat)
{
	extern DLN_VIEW		dlnv;

	char	vor[_CHAR30+1], name[_CHAR30+1];
	int	id;

	/*--- Get name from dlnview ---------*/
	id = MPAPIselectOneId((int)_DLN_VIEW, aDlnid, (char *)&dlnv);
	if (id != (int)MPOK)
	{ 
		copyTextTo( vor,  dlnv.vor, _CHAR30) ;
		copyTextTo( name, dlnv.name, _CHAR30) ;
		/*--- print out ---------------------*/
		sprintf( aTargetText, aFormat,  name,  vor );
	}
	else
		sprintf( aTargetText, aFormat, " ", " " );
}




/*SF-------------------------------------------------------------------------
 *  Function:  OUTdlnGetAgeAscii()
 *             - compute age stuff for ticket, faktura etc.... 
 *  In:        - 
 *  out:       - 
 *  Return:    - completion code
 *---------------------------------------------------------------------------
 */
static int OUTdlnGetAgeAscii( int aDlnid, int aAdultLimit, char *aAge, int *adultFlag )
{
	extern int	AgeAdult;            /* global */

	REISENDER		rei;
	int	age, len ;
	int	id;
	int	status;

	/*--- Init ----------------------------------*/
	status   = (int)MPOK;
	id			= (int)0;

	/*-- Reisender ----------------------*/
	id = MPAPIselectOneId( (int)_REISENDER, aDlnid, (char*)&rei );

	/*-- no date or no correct characters ---*/
	if ( ((len = strlen(rei.age)) == 0) || (isdigit(rei.age[0]) == 0) )
	{
		sprintf(aAge, "%s", "-" );
		*adultFlag = 1;
	}
	else
	{
		/*-- Age in digits ------------------*/
		age = AKTdateConvertToAge( rei.age );
		if ( age == -1  )
		{
			sprintf(aAge, "%s", "-" );               /* wrong string */
			*adultFlag = 1;
		}
		if ( age == 0  )
		{
			sprintf(aAge, "%s", "1" );
			*adultFlag = 0;
		}
		else if (age >= aAdultLimit)
		{
			(void)copyTextTo( aAge, "A", _CHAR4);
			*adultFlag = 1;
		}
		else
		{
			sprintf(aAge, "%3d", age );
			*adultFlag = 0;
		}
	}
	return (status);
}




/*SF-------------------------------------------------------------------------
 *  Function:  OUTdlnGetNextAdult()
 *             - Among all Dln, get the next: 2 Adults then other
 *  In:        -
 *  out:       -
 *  Return:    - completion code
 *---------------------------------------------------------------------------
 */
static int OUTticketGetNextDln( int aAlreadyBooked, int aTarifLimit )
{
	extern 	BCH_DLN	*bchdln	;
	extern	int		anzBd ;

	int   status, i, theDlnid ;
	int   adultFlag = 1 ;                         /* 1 means adult */
	char  ageTxt[_CHAR30+1];						/* age in ascii  */
	BCH_DLN			*pBchdln;

	/*-- Adults first ---------------------------*/
	if (aAlreadyBooked < aTarifLimit)
	{
		/*-- look for adults -----*/
		for ( i = 0;  i < anzBd ;  i++ )
		{
			pBchdln = &bchdln[i];
			theDlnid = pBchdln->dln_id;
			/*-- check if adult -----*/
			//status = OUTticketDlnAge( theDlnid, ageTxt, &adultFlag);
			if ( (theDlnid != (int)UNDEF) && (adultFlag == 1) )
			{
				/*-- this Dln has been treated --------------*/
				pBchdln->dln_id = (int)UNDEF;
				return ( theDlnid);                      /*>>>> exit */
			}
		}
	}

	/*-- Whatever Dln not selected -------------*/
	for ( i = 0;  i < anzBd ;  i++ )
	{
		pBchdln = &bchdln[i];
		theDlnid = pBchdln->dln_id;
		if (theDlnid != (int)UNDEF)
		{
			/*-- this Dln has been treated --*/
			pBchdln->dln_id = (int)UNDEF;
			return ( theDlnid);                      /*>>>> exit */
		}
	}

	return ((int)UNDEF);
}


