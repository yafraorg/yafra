/*D***********************************************************
 * Module:		telfax.c
 * 				telex, telefax transmission
 *                                                            
 * Functions:	ACTtelfax()                                                            
 *                                                            
 *                                                            
 * Copyright: Yafra.org     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/fax_hylafax.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>

/*--- Public interface with library -------------*/
#include <pssercom.h>

/*F**************************************************************************
 *  Function:	faxUniplex ()
 *					fax utility program for Boll + Reich Uniplex soft
 *					build fax command
 *					send file to queue and delete it					
 *					
 *  In:			-filename, fax/tlxNr, device, delay , debug
 *  out:			-
 *  Return:		-completion code 
 ***************************************************************************-
 */
int fax_Hylafax(char *filename, char *phoneNr, int device, int delay, int debug)
{
	int		status;

	status = 0;

	return(status);
}
