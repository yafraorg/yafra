/*D***********************************************************
 * Name:      AKTlayout.c
 * Modul:     AKT base moduls
 *            handling of layout, forms, lines... etc 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */


/*P--- PROTOTYPES ----------------------------------------------------------*/
static void printNewlines( FILE *aFPoutbuf, int aNumber);


/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutInit ()
 *					init the layout variables and structures 
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutInit(void)
{
	extern int		LayLines;                /* nb of current lines in page */
	extern int		LayPages;                /* nb of pages                 */
	extern int		LayLinesMax;

	/*--- general inits ------------*/
	LayLines	= 1;
	LayPages	= 1;
	LayLinesMax	= _NBLINES_NORMAL_ ;
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutInitLinesMax ()
 *					init the layout variable: nb of lines on a page
 *  In:			-actions typ and page length index  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutInitLinesMax( int aActionTyp, int aIndex )
{
	extern int		LayLinesMax;

	char		format[_TEXTLEN+1];

	/*--- Page length init -----------------*/
	(void)AKTobjtxt((int)aActionTyp, aIndex, format, NOMARGIN);
	LayLinesMax = atoi( format); 
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutInitBottomMargin ()
 *					init variable: nb of lines from bottom to jump on next
 *  In:			-actions typ and page length index  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutInitBottomMargin( int aActionTyp, int aIndex )
{
	extern int		LayBottomMargin;

	char		format[_TEXTLEN+1];

	/*--- Page length init -----------------*/
	(void)AKTobjtxt((int)aActionTyp, aIndex, format, NOMARGIN);
	LayBottomMargin = atoi( format); 
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutGetPages ()
 *					give back the nb of pages  
 *  In:			- 
 *  out:			-
 *  Return:		-nb of pages 0..n 
 *---------------------------------------------------------------------------
 */
int  AKTlayoutGetPages(void)
{
	extern int		LayPages;

	/*--- nb of used pages -----------*/
	return (LayPages);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutPageEndReached ()
 *					check if there is place for more lines on this page 
 *  In:			- 
 *  out:			-
 *  Return:		-1 means reached
 *---------------------------------------------------------------------------
 */
int AKTlayoutPageEndReached(void)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayLinesMax;
	extern int		LayBottomMargin;

	/*--- lines till bottom of page ------------*/
	if ( LayLines + LayBottomMargin  > LayLinesMax )
		return ( (int)1);
	else
		return ( (int)0);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutFormFeedPrint ()
 *					print a form feed symbol 
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutFormFeedPrint( FILE *aFPoutbuf)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayPages;                /* nb of pages                 */
	
	/*--- printout -----------------*/
	fprintf( aFPoutbuf, "%c", _MPSYMB_FF );
	/*--- counter tracing ----------*/
	LayLines = 1 ;
	LayPages++;
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutGetLines ()
 *					return the number of current lines 
 *  In:			- 
 *  out:			-
 *  Return:		-nb of used lines from top 
 *---------------------------------------------------------------------------
 */
int  AKTlayoutGetLines(void)
{
	extern int		LayLines;                /* nb of lines in current page */

	/*--- lines from top of page ------------*/
	return (LayLines);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutLinesAdd ()
 *					return the number of current lines 
 *  In:			-nb of lines to add  
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  AKTlayoutLinesAdd( int aNumber )
{
	extern int		LayLines;                /* nb of lines in current page */

	/*--- add lines ----------*/
	LayLines += aNumber;
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutGetFreeLines()
 *					init the layout variables and structures 
 *  In:			- 
 *  out:			-
 *  Return:		-nb of free lines till bottom  
 *---------------------------------------------------------------------------
 */
int AKTlayoutGetFreeLines(void)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayLinesMax;

	/*--- lines till bottom of page ------------*/
	return (LayLinesMax - LayLines);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutNewLinePrint ()
 *					trace the nb of lines and print out 
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutNewLinePrint( FILE *aFPoutbuf)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayPages;                /* nb of pages                 */
	extern int		LayLinesMax;
	
	/*--- printout -----------------*/
	fprintf( aFPoutbuf, "%s", _P_EOL_ );
	/*--- counter tracing ----------*/
	LayLines++ ;
	if (LayLines > LayLinesMax )
	{	
		LayLines = 1 ;
		LayPages++;
		fprintf( aFPoutbuf, "%c", _MPSYMB_FF );   
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutNewLine ()
 *					count only do not print 
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutNewLine(void)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayPages;                /* nb of pages                 */
	extern int		LayLinesMax;
	
	/*--- counter tracing ----------*/
	LayLines++ ;
	if (LayLines > LayLinesMax ) ;
	{	
		LayLines = 1 ;
		LayPages++;
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlayoutPrintManyNewLines ()
 *					init the layout variables and structures 
 *  In:			-a file descriptor, aLineNumber 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlayoutPrintManyNewLines( FILE *aFPoutbuf, int aNumber)
{
	extern int		LayLines;                /* nb of lines in current page */
	extern int		LayPages;                /* nb of pages                 */
	extern int		LayLinesMax;

	int		k, tillBottom;

	/*--- inits --------*/
	
	/*--- Check if aNumber is greater than LayLinesMax --------*/

	/*--- check nb of free lines till page bottom ------------*/
	tillBottom = LayLinesMax - LayLines;
	if (aNumber <= tillBottom)
	{
		printNewlines( aFPoutbuf, aNumber);
	}
	else 
	/*--- nb of lines is more than tillbottom ----------------*/
	{
		/*--- first part of lines  ---------------*/
		printNewlines( aFPoutbuf, tillBottom);              
		fprintf( aFPoutbuf, "%c", _MPSYMB_FF );           /* form feed */

		/*--- second part of lines on next page --*/
		printNewlines( aFPoutbuf, aNumber - tillBottom);

		/*--- counter tracing --------------------*/
		LayLines = aNumber - tillBottom ;
		LayPages++;
	}
}


/****************************************************************************/
/*F--------------------------------------------------------------------------
 *  Function:	printNewlines ()
 *					print a number of newlines  
 *  In:			-aLineNumber 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static void printNewlines( FILE *aFPoutbuf, int aNumber)
{
	int		k;
	char	format[_NBLINES_COMPRESSED_+1];
	
	/*--- inits --------*/
	*format = (char)NULL;
	
	/*--- limit check ------------------------------------------*/
	if (aNumber <= _NBLINES_COMPRESSED_)
	{	
		for (k=0;  k < aNumber;  k++)
			strcat(format, _P_EOL_ );

		fprintf( aFPoutbuf, format );   
	}
}
