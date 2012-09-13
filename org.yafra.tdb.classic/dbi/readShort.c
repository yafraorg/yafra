/*D***********************************************************
 * modul:     DBI - read a string and convert it to int
 *
 * copyright: yafra.org, Switzerland, www.pisoag.com
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes for ANSI-C */

#ifdef ps_cygwin
#undef ps_unix
#define ps_win
#endif

#ifdef ps_unix
#include <values.h>
#endif

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/readShort.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

#define MSG1	69
#define MSG2	70

int readShort(short *value, char *record)
{
	extern int errno;
	char *ptr;
	long lvalue;
	long maxval;
	int base=(int)DEZIMAL, status=(int)MPOK;

#ifdef ps_win
	maxval = (long)sizeof(short);
#else
	maxval = (long)MAXSHORT;
#endif
	lvalue=strtol(record, &ptr, base);
	if (*ptr == (char *)NULL || errno == (int)EINVAL)
		{
		if (errno != (int)ERANGE &&
		   (lvalue >= (maxval*(long)-1) && lvalue <= maxval))
			{
			*value=(short)lvalue;
			}
		else
			{
			*value=(short)0;
			UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else
		{
		*value=(short)0;
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
