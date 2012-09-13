/*D***********************************************************
 * modul:     DBI - read a string and convert it to double
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/readDouble.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

#define MSG1	71
#define MSG2	70

int readDouble(double *value, char *record)
{
	extern int errno;
	char *ptr;
	double dvalue;
	int status=(int)MPOK;

	dvalue=strtod(record, &ptr);
	if (*ptr == NULL)
		{
		if (errno != (int)ERANGE)
			{
			*value=(double)dvalue;
			}
		else
			{
			*value=(double)0.;
			UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else
		{
		*value=(double)0.;
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
