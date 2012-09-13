/*D***********************************************************
 * Modul:     API - time/date conversion                           
 *            convert string to time
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/ReadTime.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

int ReadTime(struct tm *DateTime, time_t *clock_value, char *record)
{
	int status=(int)MPOK;

	if (*record == NULL)
		{
		*clock_value=(time_t)_MP_NODATE;
		return(status);
		}

	status = PSSYSdatetime2int(DateTime, clock_value, record, PSSYS_TIME_GERMAN);
	
	return(status);
}
