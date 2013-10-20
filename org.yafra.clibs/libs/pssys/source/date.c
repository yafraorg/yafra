/**************************************************************
 * modul:     manage time/date read and write in/from
 *            strings in different languages
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/date.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/* piso includes */
#include <pssys.h>

/* global defines for date conversion */
#define _UNDEF -1
#define _NODATE 0
#define DEZIMAL 10

#define  MAX_TM   (int)5

/* static function prototypes */
static int PSSYSgerman_int2time(struct tm *, time_t *, char *, size_t);
static int PSSYSgerman_date2int(struct tm *, time_t *, char *);
static int PSSYSgerman_time2int(struct tm *, time_t *, char *);

/************************************************************
 * create a date and time string from an ANSI time_t value
 *
 * read time_t value and write it to date and time
 * string. If time_t is 0 then the current date/time is set.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSwriteDate(time_t aTimevalue, /* read time_t value */
                    char *aDate,       /* write date string */
                    char *aTime,       /* write time string */
                    size_t aLen,       /* string len of both strings */
                    int aFormat        /* country format    */)
{
	struct tm dat;
	time_t clock_value;
	time_t time_value;
	int status = PSOK;

	if (aTimevalue == (time_t)0)
		(void)time(&clock_value);
	else
		clock_value = aTimevalue;

	switch(aFormat)
		{
		case PSSYS_DAT_GERMAN:
		case PSSYS_TIME_GERMAN:
		default:
			status = PSSYSint2datetime(&dat, &clock_value, aDate, aLen, "%d.%m.%Y", PSSYS_DAT_GERMAN);
			status = PSSYSint2datetime(&dat, &clock_value, aTime, aLen, "%H:%M", PSSYS_DAT_GERMAN);
			break;
		}
}

/************************************************************
 * create a date and time string from an ANSI time_t value
 *
 * read time_t value and write it to date and time
 * string. If time_t is 0 then the current date/time is set.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI int PSSYSint2datetime(struct tm *aDateTime, /* control struct */
                      time_t    *aClock_value, /* INPUT time value */
                      char      *aRecord, /* OUTPUT string */
                      size_t    aRecordLen, /* OUTPUT string length */
                      char      *aLayout, /* how shall it look */
                      int       aFormat /* Date or Duration */)
{
	struct tm	*tv;
	size_t		len;
	int			value;
	char			value_char[16];
	int			status=PSOK;

	if (aRecordLen < 4)
		return(PSALLOC);

	if (*aClock_value == (time_t)0 || *aClock_value == (time_t)-1)
		return(PSNODATE);
	
	switch(aFormat)
		{
		case PSSYS_TIME_GERMAN:
			status = PSSYSgerman_int2time(aDateTime, aClock_value, aRecord, aRecordLen);
			break;
		case PSSYS_DAT_GERMAN:
		default:
			tv = localtime(aClock_value);
			*aRecord = (char)0;
			len = strftime(aRecord, aRecordLen, aLayout, tv);
			if (len == 0)
				return(PSNODATE);
			memcpy((void *)aDateTime, (void *)tv, sizeof(struct tm));
			break;
		}
	
	return(status);
}

/************************************************************
 * create a date and time string from an ANSI time_t value
 *
 * read time_t value and write it to date and time
 * string. If time_t is 0 then the current date/time is set.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI int PSSYSdatetime2int(struct tm *aDatecontrol,
                      time_t    *aDatevalue,
                      char      *aDatestring,
                      int       aFormat)
{
	extern int errno;

	int	status = PSOK;

	/* check if outputstring is not NULL */
	if (*aDatestring == (char)0)
		{
		*aDatevalue = (int)_NODATE;
		return(PSERROR);
		}

	/* check if it's a range or a date */
	if (*aDatestring == '-' || *aDatestring == '+')
		{
		*aDatevalue = atoi(aDatestring);
		return(status);
		}

	switch(aFormat) {
		case PSSYS_DAT_GERMAN:
			status = PSSYSgerman_date2int(aDatecontrol, aDatevalue, aDatestring);
			break;
		case PSSYS_TIME_GERMAN:
			status = PSSYSgerman_time2int(aDatecontrol, aDatevalue, aDatestring);
			break;
		default:
			status = PSSYSgerman_date2int(aDatecontrol, aDatevalue, aDatestring);
			break;
	}

	return(status);
}







/****************************************************************************/
/********************* STATIC FUNCTION SECTION ******************************/
/****************************************************************************/



/*SF**********************************************************
 * Function: PSSYSgerman_int2time
 * Format:   Input: time_t value Output: TAG STUNDEN:MINUTEN
 * Return:   MPOK or PSERROR
 *************************************************************/
static int PSSYSgerman_int2time(struct tm *aDateTime,
                                time_t    *aClock_value,
                                char      *aRecord,
                                size_t    aLen)
{
	int			status=PSOK;

	(void)memset((void *)aDateTime, (int)0, sizeof(aDateTime));

	aDateTime->tm_isdst = (int)-1;
    aDateTime->tm_sec  = *aClock_value % 60;
    aDateTime->tm_min  = ((*aClock_value-aDateTime->tm_sec)/60) % 60;
    aDateTime->tm_hour = ((*aClock_value-(aDateTime->tm_min*60)-aDateTime->tm_sec)/(60*60)) % 24;
    aDateTime->tm_mday = ((*aClock_value-(aDateTime->tm_hour*60*60)-(aDateTime->tm_min)-aDateTime->tm_sec)/(60*60*24));

	(void)sprintf(aRecord, "%02d %02d:%02d", aDateTime->tm_mday, aDateTime->tm_hour,aDateTime->tm_min);

	return(status);
}



/*SF**********************************************************
 * Function: PSSYSgerman_date2int
 * Format:   Input: TAG:MONAT:JAHR STUNDEN:MINUTEN Output: time_t value
 * Return:   MPOK or PSERROR
 *************************************************************/
static int PSSYSgerman_date2int(struct tm *aDatecontrol,
                                time_t    *aDatevalue,
                                char      *aDatestring)
{
	int	value;
	char	*ptr_src;
	char	*ptr_orig;
	int	status = PSOK;
	int	index;
	time_t currtime;
	struct tm	*tv;

	/* format date string ! incomming format is now german TT.MM.JJ SS.MM\0 */
	/* 15 bytes (incl. NULL termination. Only parse if element is set to UNDEF */
	ptr_orig = aDatestring;
	if ( (isdigit(*ptr_orig) == 0) )
		ptr_orig++;


	/* day */
	if (aDatecontrol->tm_mday == _UNDEF)
		{
		ptr_src = ptr_orig;
		ptr_src[2] = NULL;
		value = atoi(ptr_src);
		aDatecontrol->tm_mday = value;
		}

	/* month */
	if (aDatecontrol->tm_mon == _UNDEF)
		{
		index = 3;
		ptr_src = &ptr_orig[index];
		ptr_src[2] = NULL;
		value = atoi(ptr_src);
		aDatecontrol->tm_mon = (value - 1);
		}

	/* year */
	if (aDatecontrol->tm_year == _UNDEF)
		{
		index = 6;
		ptr_src = &ptr_orig[index];
		ptr_src[4] = NULL;

		/* hat jahr 2 oder 4 Stellen */
		/* falls 2 Stellen, dann das aktuelle century dazu tun (1900, 2000, ...)
         dies ist noch zu tun spaeter */
		if (strlen(ptr_src) == 2) {
			currtime = time(NULL);
			tv = localtime(&currtime);
			ptr_src[2] = NULL;
			value = atoi(ptr_src);
			value += ((int)(tv->tm_year / 100)*100);
			index = 9;
		} else {
			value = (atoi(ptr_src) - 1900);
			index = 11;
		}
		aDatecontrol->tm_year = value;
		}

	/* hour */
	if (aDatecontrol->tm_hour == _UNDEF)
		{
		ptr_src = &ptr_orig[index];
		ptr_src[2] = NULL;
		value = atoi(ptr_src);
		aDatecontrol->tm_hour = value;
		}

	/* minute */
	if (aDatecontrol->tm_min == _UNDEF)
		{
		index += 3;
		ptr_src = &ptr_orig[index];
		ptr_src[2] = NULL;
		value = atoi(ptr_src);
		aDatecontrol->tm_min = value;
		}
	aDatecontrol->tm_sec = 0;

	/* daylight saving flag (<0 means don't know, 0 is not and 1 is in effect) */
	aDatecontrol->tm_isdst = (int)-1;

	/* make time_t value */
	*aDatevalue = (time_t)mktime(aDatecontrol);
	if (errno == ERANGE)
		{
		*aDatevalue=(int)_NODATE;
		errno=(int)0;
		status=(int)PSNODATE;
		}

	return(status);
}



/*SF**********************************************************
 * Function: PSSYSgerman_time2int
 * Format:   Input: TAGE STUNDEN:MINUTEN Output: time_t value
 * Return:   MPOK or PSERROR
 *************************************************************/
static int PSSYSgerman_time2int(struct tm *aDateTime,
                                time_t    *aClock_value,
                                char      *aDatestring)
{
	int status=PSOK;

	char **ptr, *str;
	int gemacht = (int)0;
	int time_value[MAX_TM], alle = (int)0;

	if (*aDatestring == NULL)
		{
		*aClock_value = (time_t)_NODATE;
		return(status);
		}

	ptr = (char **)calloc((unsigned)1, sizeof(char *));

	(void)memset((void *)time_value, NULL, (size_t)(sizeof(int) * (size_t)MAX_TM));

	*ptr = aDatestring;
	str = aDatestring;

	do
		{
		if (isdigit((int)*str) != FALSE)
			{
			time_value[alle++] = (int)strtol(str, ptr, (int)DEZIMAL);
			str = (char *)*ptr;
			}
		else
			str++;
		} while(*str != NULL);

	if (alle > (int)0)
		{
		if (aDateTime->tm_mday == (int)_UNDEF)
			aDateTime->tm_mday = time_value[gemacht++];

		if (aDateTime->tm_hour == (int)_UNDEF)
			aDateTime->tm_hour = time_value[gemacht++];

		if (aDateTime->tm_min == (int)_UNDEF)
			aDateTime->tm_min = time_value[gemacht++];

		if (aDateTime->tm_sec == (int)_UNDEF)
			aDateTime->tm_sec = time_value[gemacht++];

		*aClock_value = (time_t)0;

		*aClock_value += aDateTime->tm_sec;
		*aClock_value += (aDateTime->tm_min*(int)60);
		*aClock_value += (aDateTime->tm_hour*(int)60*(int)60);
		*aClock_value += (aDateTime->tm_mday*(int)60*(int)60*(int)24);
		}
	else
		{
		*aClock_value = (time_t)_NODATE;
		status = (int)PSNODATE;
		}

	return(status);
}
