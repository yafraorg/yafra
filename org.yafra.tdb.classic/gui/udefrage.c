/*D*************************************************************************
 * Modul:			GUI - Dialog			udefrage.c
 *            
 * Description:	Prepare Question dialog, and show it 
 *
 * Functions:		xUIdialog()	xUIquestion()
 *											
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/udefrage.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

   Log Information:
   $Log: udefrage.c,v $
   Revision 1.2  2008-11-02 19:55:44  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:03:49  ja
   general version

 * Revision 1.7  94/02/18  10:40:19  10:40:19  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.6  93/11/10  08:28:53  08:28:53  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.5  93/04/08  14:26:40  14:26:40  ja (Jean-Marc Adam)
 * "Free after XtSetValue"
 * 
 * Revision 1.4  93/04/08  12:44:36  12:44:36  ja ()
 * "Deallocate XmStringGreateSimple stuff"
 * 
 * Revision 1.3  93/01/18  13:42:57  13:42:57  ja ()
 * "Label"
 * 
 * Revision 1.2  93/01/18  11:22:27  11:22:27  ja ()
 * "Header"
 * 
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/udefrage.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIdeffrage ()
 *					prepare question dialog and show 
 *
 *  In:			-yes, no, question strings,  callaback, closure, widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIdeffrage ( char *yes, char *no, char *frage, XtCallbackProc func,
							XtPointer closure, Widget aktwidget )
{
	extern XtPointer		 adrptr;
	extern XtCallbackProc funcquestion;
	extern Widget			 questionshell, questionbox;
   extern char *			 xuiLabelTable[][XUILABMAXTEXTS];  

	Arg			wargs[3];
	XmString     xmStr1, xmStr2, xmStr3;

	questionbox = xUIdialog (XmDIALOG_QUESTION,
							aktwidget,
							LABEL_QUESTIONWINDOW,
                     QUESTIONBOX,
							(XtCallbackProc)xUIquestion,
							(XtPointer)True,
							(XtCallbackProc)xUIquestion,
							(XtPointer)False);
	xmStr1 = XmStringCreateSimple( no);
	XtSetArg(wargs[0], XmNcancelLabelString, xmStr1);
	xmStr2 = XmStringCreateSimple( yes);
	XtSetArg(wargs[1], XmNokLabelString,     xmStr2);
	xmStr3 = XmStringCreateSimple( frage);
	XtSetArg(wargs[2], XmNmessageString,     xmStr3);
	XtSetValues(questionbox, wargs, 3);
	XmStringFree( xmStr1);
	XmStringFree( xmStr2);
	XmStringFree( xmStr3);
	funcquestion = func;
	adrptr = closure;
	XtManageChild(questionbox);
}
