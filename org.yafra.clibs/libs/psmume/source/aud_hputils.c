#ifdef ps_hpux
/*
 * autils - audio utilities for audio examples 
 *   Pat McElhatton   Sep. 6 1991
 */

#include <stdlib.h>
#include <stdio.h>
#include <Alib.h>
#include <psmume.h>
#include "aud_hp.h"

/*
 * To add new file format types to name2format, you must:
 *  1. create a new user defined format code (in autils.h
 *  2. add the new extension/format_switch to formatNames
 *  3. add the new format code to formatCodes
 * The above steps are marked in the code below with the string "STEP"
 *
 *  We have added one user-defined type, "spl", which is just another name
 * for linear offset 8-bit, as a simple example.
 *
 */

static char *formatNames[] = {
    "al",               /* raw ALaw */
    "au",               /* Sun file format */
    "l16",              /* raw linear 16-bit */
    "lo8",              /* raw linear offset 8-bit */
    "l8",               /* raw linear 8-bit */
    "u",                /* raw MuLaw */
    "wav",              /* Riff file */
    "snd",              /* Next file format */
/* STEP 2. ADD USER-DEFINED FORMAT NAMES HERE: */
    "spl",              /* sound-pressure-level (Atari format?) same as lo8 */
/* END OF USER-DEFINED FORMATS */
    ""                  /* *** NULL STRING ENDS THE LIST - DO NOT REMOVE */
};

static long formatCodes[] = {
    AFFRawALaw,
    AFFSun,
    AFFRawLin16,
    AFFRawLin8Offset,
    AFFRawLin8,
    AFFRawMuLaw,
    AFFRiffWave,
    AFFSun,
/* STEP 3. ADD USER-DEFINED FORMAT CODES HERE: */
    USER_FORMAT_spl,
/* END OF USER-DEFINED FORMATS */
    -1                  /* END OF THE LIST - DO NOT REMOVE */
};

static char *DataFormatNames[] = {
    "u",                /* MuLaw */
    "al",               /* ALaw */
    "l16",              /* linear 16-bit */
    "lo8",              /* linear offset 8-bit */
    "l8",               /* linear 8-bit */
    ""                  /* *** NULL STRING ENDS THE LIST - DO NOT REMOVE */
};

static long DataFormatCodes[] = {
    ADFMuLaw,
    ADFALaw,
    ADFLin16,
    ADFLin8Offset,
    ADFLin8,
    -1                  /* END OF THE LIST - DO NOT REMOVE */
};


/****************************************************************************
 *
 *   searchNameTable - search a table for a match with given string
 *	return -1 for no match, else return match index
 *	assumes that last+1 entry in table is empty string
 *     (search is case insensitive)
 */
#ifdef __STDC__
int
searchNameTable(
    char *pName,
    char *pTable[]
    )
#else
int
searchNameTable( pName, pTable )
    char *pName;
    char *pTable[];
#endif
{
    int i;
    char *pString;

    /* first, create a lowercase only version of pName in pString */
    pString = malloc( strlen(pName) + 1 );
    pString[ strlen(pName) ] = 0;
    i = 0;
    while ( pName[i] != 0 ) {
        pString[i] = tolower( pName[i] );
        i++;
    }

    /* scan name table for match with pString */
    i = 0;
    while ( *(pTable[i]) ) {
        if ( strcmp(pString, pTable[i]) == 0 ) {
	    free( pString );
            return i;
        }
        i++;
    }
    free( pString );
    return -1;

}   /* end searchNameTable */


/****************************************************************************
 *
 *   findFormat - convert file format string to file format code
 */
#ifdef __STDC__
AFileFormat
findFormat(
    char *pString
    )
#else
AFileFormat
findFormat( pString )
    char *pString;
#endif
{
    int file_format;

    /* look for a format name that matches pString */
    file_format = searchNameTable( pString, formatNames );

    /* if format name was found, convert it to a file format code */
    if ( file_format < 0 ) {
        file_format = AFFUnknown;
    } else {
        file_format = formatCodes[ file_format ];
    }

    return file_format;

}   /* end findFormat */

/****************************************************************************
 *
 *   findDataFormat- convert data format string to data format code
 */
#ifdef __STDC__
ADataFormat
findDataFormat(
    char *pString
    )
#else
ADataFormat
findDataFormat( pString )
    char *pString;
#endif
{
    int data_format;

    /* look for a format name that matches pString */
    data_format = searchNameTable( pString, DataFormatNames );

    /* if format name was found, convert it to a data format code */
    if ( data_format < 0 ) {
        data_format = ADFUnknown;
    } 
    else {
        data_format = DataFormatCodes[ data_format ];
    }

    return data_format;

}   /* end findDataFormat */


/****************************************************************************
 *
 *   name2format - get sample rate & data format from filename
 *   returns:
 *      0   if neither data format or sample rate is found
 *      1   if data format is found but no sample rate
 *      2   if data format and sample rate are found
 *    does not modify *pFormat or *pSampleRate if not found in filename
 */
#ifdef __STDC__
int
name2format(
    char          *afile,
    AFileFormat   *pFormat,
    unsigned long *pSampleRate
    )
#else
int
name2format( afile, pFormat, pSampleRate )
    char          *afile;
    AFileFormat   *pFormat;
    unsigned long *pSampleRate;
#endif
{
    int n, numFound, lastIndex;
    unsigned long sum;
    AFileFormat fFormat;
    char *str;

    /*
     * first strip off any leading directory names
     */
    str = afile;
    while ( *str ) {
      if ( *str == '/' ) {
	afile = str;
      }
      str++;
    }

    /*
     * next try to find the data format from the extension tail
     */
    n = strlen( afile );
    while ( (afile[n] != '.') && (n != 0) ) { /* find the extension tail */
        n--;
    }
    fFormat = findFormat( &(afile[n + 1]) );
    numFound = ( fFormat != AFFUnknown ) ? 1 : 0;

    /*
     * if we found the data format, try to find the sample rate
     */
    if ( (fFormat != AFFUnknown) && (n != 0) ) {
        /*
	 * find the sample rate
	 */
        n--;
	lastIndex = n;
        while ( (afile[n] != '.') && (n != 0) ) {
	    n--;
	}
        if ( afile[n] == '.' ) {
	    /*
	     * found another period, see if string is valid sample rate
	     *  n is index of '.' at start of sample rate string
	     *  lastIndex is index of last char in sample rate string
	     */
	    n++;
	    sum = 0;
	    while ( n <= lastIndex ) {
	        /*
	         * A valid sample rate string is a series of digits, with an optional
	         * last character of 'k' or 'K', which indicates that the sample rate
	         * is in kilohertz ( Ex: "11k" means sample rate of 11000 )
	         */
	        sum *= 10;
	        if ( isdigit( afile[n] ) ) {
		    sum += (afile[n] - '0');
		} else {
		    /*
		     * the last char in a sample rate can be 'k' or 'K'
		     * anything else (other than a digit) is not valid
		     */
		    if ( (n == lastIndex) && 
		        ((afile[lastIndex] == 'k') || (afile[lastIndex] == 'K')) ) {
		        sum *= 100;        /* already multiplied by 10 above */
		    } else {
		        /* string is not a valid sample rate, exit */
		        return numFound;
		    }
		}
	        n++;
	    }  /* end while n <= lastIndex */

	    if ( sum ) {
	        /*
		 * sample rate is valid, return it to user
		 */
	        *pSampleRate = sum;
		numFound = 2;
	    }

        }      /* end if found beginning of sample rate string */

    }       /* end if found data format string */
    if ( fFormat != AFFUnknown ) {
      *pFormat = fFormat;
    }
    return numFound;
}


/*
 * printAudioError - print audio error text given error code
 */
#ifdef __STDC__
void
printAudioError(
    Audio    *audio,
    char     *message,
    int      errorCode
    )
#else
void
printAudioError( audio, message, errorCode )
    Audio    *audio;
    char     *message;
    int      errorCode;
#endif
{
    char    errorbuff[132];

    AGetErrorText(audio, errorCode, errorbuff, 131);
    fprintf ( stderr, "%s: %s\n", message, errorbuff);
}

#endif
