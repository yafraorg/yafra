/*D***********************************************************
 * Modul:     API - utilities                           
 *            filter for special characters
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/api/UtilConvertChar.c,v 1.2 2008-11-02 19:55:49 mwn Exp $

 Log Information:
 $Log: UtilConvertChar.c,v $
 Revision 1.2  2008-11-02 19:55:49  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 06:23:46  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/01 00:48:25  mw
 update for DB rel 2

 * Revision 1.2  94/02/16  15:46:53  15:46:53  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/08/05  23:35:59  23:35:59  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilConvertChar.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

#define MAKRO_1 '\''
#define MAKRO_2 '~'
#define MAKRO_3 '-'
#define MAKRO_4 '"'
#define MAKRO_5 '\\'
#define MAKRO_6 '/'
#define MAKRO_7 '*'
#define MAKRO_8 't'

char* ConvertSpecialChar( char *Buffer, char Seperator )
{
	char *ptr, *NewBuffer, *NewBufferPtr;

	NewBuffer = NewBufferPtr = (char *)calloc((strlen(Buffer) + 1),
	                                         sizeof( char ) );
	if (NewBuffer == (char *)NULL)
		return((char *)NULL);

	(void)memcpy((void *)NewBuffer, (void *)Buffer, (strlen(Buffer) + 1));

	ptr = Buffer;
	while ( *NewBufferPtr != NULL )
		{
		if ( *NewBufferPtr == Seperator )
			{
/*
 *			--------------------------------------
 *			Ist das Trennsymbol ein Char im Buffer
 *			dieses Zeichen �bergehen
 *			--------------------------------------
 */
			*ptr++ = *NewBufferPtr;
			}
		else if ( *NewBufferPtr == MAKRO_1 )
			{
/*
 *			-----------------------------------------------------
 *			Testet ob das Zeichen ' enthalten ist und schreibt ''
 *			-----------------------------------------------------
 */

			*ptr++ = *NewBufferPtr;
			*ptr++ = *NewBufferPtr;

			}
		else if ( *NewBufferPtr == MAKRO_2 )
			{
/*
 *			-----------------------------------------------------
 *			Testet ob das Zeichen ~ enthalten ist und ersetzt es mit -
 *			-----------------------------------------------------
 */

			*ptr++ = MAKRO_3;

			}
/*		else if ( *NewBufferPtr == MAKRO_4 )
			{ */
/*
 *			-----------------------------------------------------
 *			Testet ob das Zeichen " enthalten ist und schreibt \"
 *			-----------------------------------------------------
 */

/*			*ptr++ = MAKRO_5;
			*ptr++ = *NewBufferPtr;

			}
		else if ( *NewBufferPtr == MAKRO_5 && *(NewBufferPtr+1) != MAKRO_8 )
			{ */
/*
 *			-----------------------------------------------------
 *			Testet ob das Zeichen \ enthalten ist und schreibt \\
 *			-----------------------------------------------------
 */

/*			*ptr++ = *NewBufferPtr;
			*ptr++ = MAKRO_5;

			}
		else if ( *NewBufferPtr == MAKRO_6 && *(NewBufferPtr+1) == MAKRO_7 )
			{ */
/*
 *			-----------------------------------------------------
 *			Testet ob die Zeichenkombination /* enthalten ist und schreibt \/*
 *			-----------------------------------------------------
 */

/*			*ptr++ = MAKRO_5;
			*ptr++ = *NewBufferPtr;
			} */
		else
			*ptr++ = *NewBufferPtr;

		NewBufferPtr++;

	} /* Ende while Loop */

	*ptr = (char)NULL;

	free((void *)NewBuffer);

	return(Buffer);
}
