/*D***********************************************************
 * Modul:     API - time/date conversion                           
 *            convert string to time
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/ReadDate.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

int ReadDate(struct tm *aDatecontrol, time_t *aDatevalue, char *aDatestring)
{
	int status = MPOK;
	size_t len;

	/* check if outputstring is not NULL */
	len = strlen(aDatestring);
	if (*aDatestring == NULL || (len == (int)1 && *aDatestring == ' ') )
		{
		*aDatevalue = (int)_MP_NODATE;
		return(MPERROR);
		}

	/* check if it's a range or a date */
	if (*aDatestring == '-' || *aDatestring == '+')
		{
		*aDatevalue = atoi(aDatestring);
		return(status);
		}

	status = PSSYSdatetime2int(aDatecontrol, aDatevalue, aDatestring, PSSYS_DAT_GERMAN);

	return(status);
}
