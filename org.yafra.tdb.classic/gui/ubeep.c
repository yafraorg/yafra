/*D*************************************************************************
 * Modul:			GUI - Dialog		   ubeep.c 
 *            
 * Description:	Generates a beep tone
 *						
 *
 * Functions:		Callback and Action procedures
 * 
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/ubeep.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

   Log Information:
   $Log: ubeep.c,v $
   Revision 1.2  2008-11-02 19:55:47  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:03:33  ja
   general version

 * Revision 1.4  94/02/24  14:14:59  14:14:59  ja (Jean-Marc Adam)
 * Function header
 * 
 * Revision 1.3  94/02/18  10:40:09  10:40:09  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/06/09  10:46:18  10:46:18  ja (Jean-Marc Adam)
 * "Header"
 * 

			 Erstellt am 25.05.90 rh
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ubeep.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIbeep 
 *					emit a beep 
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtActionProc xUIbeep( Widget w, XEvent* event, String* s, Cardinal* n)
{
	XBell(XtDisplay(w), 100);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIbeeping 
 *					emit a beep 
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIbeeping( Widget w, XtPointer closure, XtPointer call_data)
{
   XBell(XtDisplay(w), 100);
}
