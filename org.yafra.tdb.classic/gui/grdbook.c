/*D************************************************************
 * Modul:		GRAPHIC							grdbook.c
 *
 *					Update the time display, ask for DB update	
 *					Set the nex rendez-vous
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/grdbook.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: grdbook.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.2  1997/08/11 09:42:20  pi
 add handling of appcontext

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:00  ja
 general version

 * Revision 1.4  94/02/18  10:38:21  10:38:21  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/10/23  11:02:37  11:02:37  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.2  93/08/21  00:25:57  00:25:57  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/grdbook.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



XtTimerCallbackProc xGRread_booking(
XtPointer Input
)

{
	extern GRAGLOB		graglob;
	extern ApplicationData app_data;
	extern XtAppContext	mpx_appcontext;

	/*--- read the time and display it ---------*/
	if (graglob.openedbookmain == True)                   
		xGRtime();

	/*--- ask and wait for DB booking status ---*/
	if (graglob.mode != XGRINPGRAFIC) {
		xGRwait_for_zustand();
	}

	/*--- set next rendez-vous -----------------*/
	graglob.timer = XtAppAddTimeOut(mpx_appcontext, app_data.updateBookingTime*1000,
											(XtTimerCallbackProc)xGRread_booking, 0);
}
