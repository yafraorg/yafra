/*D************************************************************
 * Modul:		GRAPHIC						gckrect.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gckrect.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gckrect.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:16  ja
 general version

 * Revision 1.3  94/02/18  10:36:10  10:36:10  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:25  23:54:25  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gckrect.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



Boolean xGRcheck_rectangle(
)

{
	extern XPoint   punkt[];

	if (punkt[1].x < punkt[0].x) {
		return(False);
	}
	if (punkt[1].y < punkt[0].y) {
		return(False);
	}

	return(True);
}
