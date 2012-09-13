/*D***********************************************************
 * Modul:     API - time/date conversion                           
 *            convert time to string
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/WriteTime.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

int WriteTime(struct tm *DateTime, time_t *clock_value, char *record)
{
	int status=(int)MPOK;

	status = PSSYSint2datetime(DateTime, clock_value, record, 30, NULL, PSSYS_TIME_GERMAN);

	return(status);
}
