/*D***********************************************************
 * Name:      AKTdatetime.c
 *
 * Modul:     AKT base moduls
 *            Handle date and time conversions and formatting
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdatetime.c,v 1.3 2008-11-23 15:44:39 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>


/*F************************************************************
 * Function:  AKTdatetimeday
 *            date and time formatting with language consideration
 *
 * in:        strings and language
 * out:
 * return:      _UNDEF if error else komm_id
 **************************************************************/
int AKTdatetimeday( int sek, char *date, char *zeit, char *day, char *lang )
{
	char *category;
	int NoOfCharacters;

	category = setlocale(LC_TIME, lang );

	if(sek > 0) {
		NoOfCharacters = strftime(date, _DATELEN, "%d.%m.%y", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(date, "%-8s", " ");
	} else {
		sprintf(date, "%-8s", " ");
	}

	if (sek > 0) {
		NoOfCharacters = strftime(zeit, _DATELEN, "%H:%M", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(zeit, "-----");
		NoOfCharacters = strftime(day, _DATELEN, "%a", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(day, "%-2s", " ");
	} else {
		sprintf(zeit, "-----");
		sprintf(day, "%-2s", " ");
	}
	return((int)MPOK);
}



/*F************************************************************
 * Function:  AKTdateTextLang
 *            date and time formatting with language consideration
 *
 * in:        seconds, string ptrs, language, flag for textform(1)
 * out:
 * return:
 **************************************************************/
void AKTdateTextLang( int sek, char *date, char *zeit, char *day, char *lang, int textform )
{
	char		*category;
	int		NoOfCharacters;
	time_t	clockValue;
	int		america;

	category = setlocale(LC_TIME, lang );
	if ( strcmp(lang, "american") == 0)
		america = 1;
	else
		america = 0;

	/*--- get current time if parameter "sek" is empty --------*/
	if (sek > 0)
		clockValue = (time_t)sek ;
	else
		(void)time( &clockValue );

	/*--- convert seconds -------------------------------------*/
	if (textform != 0)
		{
		/*--- month in letters ----*/
		if (america)
			NoOfCharacters = strftime(date, _DATELEN, "%b %d %y", localtime( (time_t *)&clockValue) );
		else
			NoOfCharacters = strftime(date, _DATELEN, "%d %b %y", localtime( (time_t *)&clockValue) );
		}
	else
		{
		/*--- month in digits ----*/
		if (america)
			NoOfCharacters = strftime(date, _DATELEN, "%m.%d.%y", localtime( (time_t *)&clockValue) );
		else
			NoOfCharacters = strftime(date, _DATELEN, "%d.%m.%y", localtime( (time_t *)&clockValue) );
		}
	if ( NoOfCharacters == 0 )
		sprintf(date, "%-8s", " ");

	/*--- convert to hour, minutes, day string ----------------*/
	NoOfCharacters = strftime(zeit, _DATELEN, "%H:%M", localtime( (time_t *)&clockValue ) );
	if ( NoOfCharacters == 0 )
		sprintf(zeit, "-----");
	NoOfCharacters = strftime(day, _DATELEN, "%a", localtime( (time_t *)&clockValue ) );
	if ( NoOfCharacters == 0 )
		sprintf(day, "%-2s", " ");
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTdateConvertToAge ()
 *					with the text of birth date, convert to age
 *  In:			-
 *  out:			-
 *  Return:		-age
 *---------------------------------------------------------------------------
 */
int AKTdateConvertToAge( char *dateStr )
{
	double	elapsed ;
	long		leap, nbdays ;
	char		ageTxt[_TEXTLEN];
	int		age, len, i ;
	struct	tm			date;
	time_t	now, seconds;

	/*-- check text for validity ----*/
	if (len = strlen(dateStr) <= 0 )
		return (-1);

	/*-- fill tm struct with DD.MM.YY -----------*/
	i = atoi(dateStr);
	if (i < 1)
		return(35); // TODO hardcoded default, check error handling of this func

	if (i > 31)
		{
		if (i > 1800) /* entered as 18xx or 19xx or 20xx */
			{
			age = (1998 - i); // TODO hardcoded current year - change !!!
			return(age);
			}
		else
			return(i); /* entered as real age */
		}
	date.tm_mday = i;

	i = atoi(strchr( dateStr, '.') + 1) - 1;
	if (i < 1)
		return(date.tm_mday); /* OK it was the age and not the day of the month */
	date.tm_mon  = i;

	i = atoi(strrchr(dateStr, '.') + 1);
	if (i < 1)
		return(35); // TODO hardcoded default, check error handling of this func
	date.tm_year = i;
	date.tm_hour = date.tm_min = date.tm_sec = 0;           /* midnight */

	/*-- get date integer -----------------------*/
	seconds = mktime(&date);
	now = time(NULL);

	/*-- compute in days then years -------------*/
	elapsed = difftime(now, seconds);
	leap = elapsed / (86400 * 365 * 4) ;
	nbdays = (elapsed / 86400) - leap;
	age = nbdays / 365;

	/*-- Check reasonnable limits of age ----*/
	if (age >= 150 )
		age = 150;

	return(age);
}



/*-------- old functions ----------------------------------------------------*/

char *convdate( time_t clock, char *format, char *lang, char *date )
{
	char *category;
	size_t NumberOfCharacters;

	/* if lang == "", LC_TIME environment value is used, or by default 'C' as language */
	category = setlocale( LC_TIME, lang );

	NumberOfCharacters = strftime( date, _DATELEN, format, localtime( &clock ) );

	if ( NumberOfCharacters == 0 )
		{
	   	*date = (char)NULL;
		}

	return( date );
}


int datetimeday( int sek, char *date, char *zeit, char *day, char *lang )
{
	char *category;
	int NoOfCharacters;

	category = setlocale(LC_TIME, lang );

	if(sek > 0) {
		NoOfCharacters = strftime(date, _DATELEN, "%d.%m.%y", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(date, "%-8s", " ");
	} else {
		sprintf(date, "%-8s", " ");
	}

	if (sek > 0) {
		NoOfCharacters = strftime(zeit, _DATELEN, "%H:%M", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(zeit, "-----");
		NoOfCharacters = strftime(day, _DATELEN, "%a", localtime( (time_t *)&sek ) );
		if ( NoOfCharacters == 0 ) sprintf(day, "%-2s", " ");
	} else {
		sprintf(zeit, "-----");
		sprintf(day, "%-2s", " ");
	}
	return((int)MPOK);
}
