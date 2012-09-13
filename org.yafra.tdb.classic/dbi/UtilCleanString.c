/*D***********************************************************
 * Modul:     API - utilities                           
 *            mache buffer GUI-Konform
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilCleanString.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int CleanPipeString ( char *buffer )
{
	int i, len;
	int status=(int)MPOK;

	len = strlen(buffer);
	for ( i=strlen(buffer); i > 0; i-- )
		{
		if ( buffer[i] == '\n' )
			{
			buffer[i] = '\0';
			len --;
			if ( buffer[i-1] == '\n' )
				{
				buffer[i-1] = '\0';
				len --;
				if ( buffer[i-2] == '\n' )
					{
					buffer[i-2] = '\0';
					len --;
					}
				}
			i = 0;
			}
		}
	return(len);
}
