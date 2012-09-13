/*D***********************************************************
 * Modul:     API - time/date conversion                           
 *            convert date to string
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/WriteDate.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int WriteDate(struct tm *DateTime, time_t *clock_value, char *record)
{
	int status=(int)MPOK;
	
	*record = (char)NULL;

	if (*clock_value == (time_t)0 || *clock_value == (time_t)_UNDEF)
		return(status);
	
	if (*clock_value < 1000 && *clock_value > -1000)
		{
		(void)sprintf(record, "%d", *clock_value);
		return(status);
		}

   if (DateTime->tm_mday == (int)_UNDEF && DateTime->tm_mon == (int)_UNDEF &&
       DateTime->tm_year == (int)_UNDEF && DateTime->tm_hour == (int)_UNDEF &&
       DateTime->tm_min == (int)_UNDEF )
		status = PSSYSint2datetime(DateTime, clock_value, record, 30, "%d.%m.%Y %H:%M", PSSYS_DAT_GERMAN);
	else
		status = PSSYSint2datetime(DateTime, clock_value, record, 30, "%d.%m.%Y", PSSYS_DAT_GERMAN);

	return(status);
}
