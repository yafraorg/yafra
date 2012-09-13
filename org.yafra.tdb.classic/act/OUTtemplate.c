/*D***********************************************************
 * program:      OUTtemplate
 * descripton:   template nor new actions 
 *
 * arguments:    standard arguments
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/*--- RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/OUTtemplate.c,v 1.2 2008-11-02 19:55:53 mwn Exp $";
char ident[]="@(#)MarcoPolo - Action template$";


/*--- define the entry point of this function for the main() */
int OUTtemplate( void);
#define ACTIONFUNCTION	(OUTtemplate)

/*--- MarcoPolo API includes */
#include <mpact.h>    
  
/*--- MarcoPolo API standard main function ! */
#include "AKTmain.h"



/*P--- PROTOTYPES --------------------------------------------------------*/



/*--- define text ids for language independend text */
#define TEST_PRINT_COMMAND    "lp -od -oc -olpi8 -otl85 -olm6" 



/*F--------------------------------------------------------------------------
 *  Function:	OUTtemplate ()
 *					template is used to test device functionalities 
 *
 *  In:			-
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int OUTtemplate( void)
{
	extern DEVICE_PORT	devicePort;

	DEVICE_PORT	*pDev;
	int		status;


	/*--- init ----------------------------------*/
	status = MPOK;
	pDev = &devicePort;

	/*--- Device init ---------------------------*/
	(void)sprintf(pDev->callnumber, "%s", "0123456789");
	(void)sprintf(pDev->command,    "%s", TEST_PRINT_COMMAND);


	/*--- mailing header ------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS(status)

	status = AKTmailHeader() ;
	TEST_STATUS_COMMIT(status)


	/*-----------------------------------------------------------------------*/
	/*--- Dummy text for action test 
	/*-----------------------------------------------------------------------*/
	fprintf(FPout, "\n\n\n\n\n");
	fprintf(FPout, "\n-------------------------------------------------------");
	fprintf(FPout, "\n                  ACTION TEST                          ");
	fprintf(FPout, "\n-------------------------------------------------------");
	fprintf(FPout, "\n");
	fprintf(FPout, "\nDevice parameters");
	fprintf(FPout, "\n-----------------");
	fprintf(FPout, "\n  type:       %d",  pDev->type       );
	fprintf(FPout, "\n  direction:  %d",  pDev->direction  );
	fprintf(FPout, "\n  delay:      %d",  pDev->delay      );
	fprintf(FPout, "\n  callnumber: %s",  pDev->callnumber );
	fprintf(FPout, "\n  filename:   %s",  pDev->filename   );
	fprintf(FPout, "\n  command:    %s",  pDev->command    );




	/*--- update mailing -----------------------------------------*/
	(void)sprintf( mailstring, "%s", "Mailing message test" );
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);




	/*--- Device processing --------------------------------------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");


	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);
	MPAPIdb_committrx();

exit:
	/*--- free memory ---------------------------*/
	;

	return(status);
}
