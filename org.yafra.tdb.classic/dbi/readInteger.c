/*D***********************************************************
 * modul:     DBI - read a string and convert it to integer
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/readInteger.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

#define MSG1	69
#define MSG2	70

int readInteger(int *value, char *record)
{
	extern int errno;
	char *ptr;
	long lvalue, strtol();
	int base=(int)DEZIMAL, status=(int)MPOK;

	lvalue=strtol(record, &ptr, base);
	if (*ptr == NULL || errno == (int)EINVAL)
		{
		if (errno != (int)ERANGE)
			{
			*value=(int)lvalue;
			}
		else
			{
			*value=(int)0;
			UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else
		{
		*value=(int)0;
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
