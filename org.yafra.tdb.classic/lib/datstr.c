/*D************************************************************/
/* Modul:     make date and time string                       */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <pssys.h>
#include <mpobjdef.h>
#include <mpdef.h>
#include <mpprolib.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/datstr.c,v 1.2 2008-11-02 19:55:33 mwn Exp $";

void MPdate_makecurrent(char *aDate, char *aTime)
{
	PSSYSwriteDate(0, aDate, aTime, sizeof(aTime), PSSYS_DAT_GERMAN);
}

void MPdate_makefromint(int aClock, char *aDatestring, int aDatestrlen)
{
	int cret;
	struct tm dat;
	time_t clock_value;

	(void)memset((void *)&dat, (int)NULL, sizeof(dat));
	dat.tm_hour=(int)_UNDEF;
	dat.tm_min=(int)_UNDEF;
	dat.tm_mday=(int)_UNDEF;
	dat.tm_mon =(int)_UNDEF;
	dat.tm_year=(int)_UNDEF;
	clock_value = (time_t)aClock;
	cret = PSSYSint2datetime(&dat, &clock_value, aDatestring, (size_t)aDatestrlen, "%d.%m.%Y %H:%M", PSSYS_DAT_GERMAN);
	if (cret != PSOK)
		(void)strcpy(aDatestring, "-");
}



void MPdate_puttoint(int *aClock, char *aDatestring)
{
	int cret;
	struct tm dat;
	time_t clock_value;

	(void)memset((void *)&dat, (int)NULL, sizeof(dat));
	dat.tm_hour=(int)_UNDEF;
	dat.tm_min=(int)_UNDEF;
	dat.tm_mday=(int)_UNDEF;
	dat.tm_mon =(int)_UNDEF;
	dat.tm_year=(int)_UNDEF;
	clock_value = (time_t)*aClock;
	cret = PSSYSdatetime2int(&dat, &clock_value, aDatestring, PSSYS_DAT_GERMAN);
	if (cret != PSOK)
		(void)strcpy(aDatestring, "-");
	*aClock = (int)clock_value;
}
