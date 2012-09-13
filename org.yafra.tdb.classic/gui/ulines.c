/*D***********************************************************
 * Modul:		GUI - Dialog	   ulines.c
 *                                                            
 *					Count lines and columns of buffer                                                
 *             This can be used for texts and lists                                               
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/ulines.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: ulines.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:07  ja
 general version

 * Revision 1.6  94/02/18  10:44:23  10:44:23  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.5  93/11/10  08:29:57  08:29:57  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.4  93/05/11  11:07:16  11:07:16  ja (Jean-Marc Adam)
 * "Trial"
 * 
 * Revision 1.3  93/05/04  18:11:45  18:11:45  ja ()
 * "rev"
 * 
 * Revision 1.2  93/01/07  11:33:13  11:33:13  ja ()
 * "Default value for columns is 1 (0 triggers an Xt warning)"
 * 
 * 
			 Erstellt am 09.07.90 dv
			 ge�ndert am 09.07.90 dv
			 ge�ndert am 03.10.91 pi
*/


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ulines.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIlines ()
 *					-count the number of lines and columns of a text 
 *					-the results are checked against application max values 
 *					-
 *					-
 *  In:			-ref to a text   
 *  out:			-lines and width to modify 
 *  Return:		-total number of lines
 *---------------------------------------------------------------------------
 */
int xUIlines (char *text, int *lines, int *breite )
{
	extern ApplicationData app_data;

	char	 *ptr;
	int	 b, totlines;

	/*------set default values -------------*/ 
	*lines = 0;
	*breite = 1;		/* 1 avoids warning of Xt, 0 columns not allowed */
	b = 0;

	if (!text)
	   return(0);

	ptr = text;
	while (*ptr != 0) {
		if (*ptr == '\n') {
			*breite = *breite > b ? *breite : b;
			(*lines)++;
			b = 0;
		} else if (*ptr == '\t') {
			*ptr = '\n';
		}
		b++;
		ptr++;
	}
	if (*(ptr-1) != '\n') {
		*breite = *breite > b ? *breite : b;
		(*lines)++;
	}

	totlines = *lines;
	/*------- check limits ----------------------------------*/
	*breite = *breite > app_data.scroll_maxbreite ?
								app_data.scroll_maxbreite : *breite;
	*lines  = *lines  > app_data.scroll_maxlines  ?
								app_data.scroll_maxlines  : *lines;

	return(totlines);
}
