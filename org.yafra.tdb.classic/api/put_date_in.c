/*D***********************************************************
 * Modul:     API - date/time
 *            Schreibt die Zeit und das Datum in einen String
 *            es wird die lokale Darstellung gem�ss LANG oder 
 *            LC_TIME verwendet.
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

#include <time.h>
#include <locale.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/put_date_in.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

time_t put_date_in(char *datum, char *zeit, char *lang, char *datum_format,
                   char *zeit_format) 
{
	time_t clock_value;
	char *category;
	int NoOfCharacters;

	/* look for the NLS-category defined by LC_TIME env. variable */
	category = setlocale( LC_TIME, lang );
	
	/* get the current system time */
	(void)time( &clock_value );
	
	if ( *datum_format != NULL )
	{
		/* if datum_format is set use it */
		NoOfCharacters = strftime( datum, _DATELEN, datum_format, localtime(&clock_value) );
	}
	else
	{
		/* otherwise we use the standard date format */
		NoOfCharacters = strftime(datum, _DATELEN, "%D", localtime(&clock_value) );
	}
	
	if ( *zeit_format != NULL )
	{
		/* if the zeit_format is set we use this string */
		NoOfCharacters = strftime( zeit, _DATELEN, zeit_format, localtime(&clock_value) );
	}
	else
	{
	 	/* otherwise we take a standard format */
		NoOfCharacters = strftime(zeit, _DATELEN, "%X", localtime(&clock_value) );
	}

	return( clock_value );
}
