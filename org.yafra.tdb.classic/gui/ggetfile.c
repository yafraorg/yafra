/*D************************************************************
 * Modul:		GRAPHIC							ggetfile.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/ggetfile.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: ggetfile.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:49  ja
 general version

 * Revision 1.3  94/02/18  10:38:11  10:38:11  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:42  00:25:42  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ggetfile.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/* UP save_as wird vom okCallback der 2.FileSelection Box aufgerufen. */
/* Zeichnung unter anderem Namen abspeichern.                         */

XtCallbackProc xGRgetfilename(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern GRAGLOB graglob;
	extern XtPointer adrptr;
	extern XtCallbackProc (*funcquestion)();
	XmFileSelectionBoxCallbackStruct *call_data;


	if (Input) {
		call_data = (XmFileSelectionBoxCallbackStruct *)Output;
		if (graglob.fileselected) {
			XtFree((void *)graglob.fileselected);
		}
		XmStringGetLtoR(call_data->value, XmSTRING_DEFAULT_CHARSET,
		&graglob.fileselected);
		(*funcquestion)(w, adrptr, 0);
	}
	XtUnmanageChild(w);
}
