/*D***********************************************************
 * Modul:	GUI - dialog			uquestio.c
 * 	                                       
 *				Popup a question dialog                                                             
 * 	                                       
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uquestio.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: uquestio.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:27  ja
 general version

 * Revision 1.4  94/02/18  10:44:44  10:44:44  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.3  93/11/10  08:31:12  08:31:12  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.2  93/06/09  10:53:01  10:53:01  ja (Jean-Marc Adam)
 * "Header"
 * 
 *
		Erstellt am 25.05.90 rh
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uquestio.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



XtCallbackProc xUIquestion( Widget w, XtPointer closure, XtPointer wdata)
{
	extern XtCallbackProc (*funcquestion)();
	extern XtPointer adrptr;
	extern MENU menu[];
	extern int   aktmenu[];
	extern int   aktmenuz;
	extern Widget questionshell;
	extern Widget questionbox;

	MENU *a;
	int   n;

	if (closure) {
		(*funcquestion)(w, adrptr, 0);
	}
	XtDestroyWidget(XtParent(w));
}
