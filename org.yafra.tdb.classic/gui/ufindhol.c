/*D*************************************************************************
 * Modul:			GUI - Dialog		   ufindhol.c 
 *            
 * 				Find holdfield (int. fieldnumber)
 *						
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/ufindhol.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

   Log Information:
   $Log: ufindhol.c,v $
   Revision 1.2  2008-11-02 19:55:44  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:03:56  ja
   general version

 * Revision 1.3  94/02/18  10:44:11  10:44:11  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.2  93/06/09  10:48:02  10:48:02  ja (Jean-Marc Adam)
 * "Header"
 * 
 * 
	erstellt am 04.10.91 pi
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ufindhol.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


int xUIfindhold(MENU *a, int feldnr)
{
	int   i;

	for (i=0; i<a->anz; i++) {
		if (a->zuobutton[i] == feldnr)
			return(i);
	}
	return(-1);
}
