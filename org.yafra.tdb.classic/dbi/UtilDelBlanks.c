/*D***********************************************************
 * Modul:     API - utilities                           
 *            delete trailing blanks
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/UtilDelBlanks.c,v 1.2 2008-11-02 19:55:40 mwn Exp $

 Log Information:
 $Log: UtilDelBlanks.c,v $
 Revision 1.2  2008-11-02 19:55:40  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:07  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:12:15  16:12:15  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/04/02  17:33:33  17:33:33  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilDelBlanks.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

void UtilDelBlanks(char *buffer)
{
	int i, len;

	len = strlen(buffer);

	for(i=(len - 1); (i > (int)-1); i--)
		{
		if (buffer[i] == ' ')
			buffer[i] = NULL;
		else if (buffer[i] == NULL)
			continue;
		else
			break;
		}
}
