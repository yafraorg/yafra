/*D************************************************************
 * Modul:		GRAPHIC							gigerund.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gigerund.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gigerund.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:53  ja
 general version

 * Revision 1.3  94/02/18  10:38:15  10:38:15  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:48  00:25:48  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gigerund.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


int xGRint_gerundet(
WCVALUE wert
)

{
	if(wert-(int)wert>0.5)return((int)wert+1);
	else                  return((int)wert);
}


