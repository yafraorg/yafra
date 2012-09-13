/*D*************************************************************************
 * Modul: 	    GUI - Dialog			uimecall.c	
 *  	          manage immediate call
 *            
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/uimecall.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

   Log Information:
   $Log: uimecall.c,v $
   Revision 1.2  2008-11-02 19:55:45  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:04:01  ja
   general version

 * Revision 1.6  94/02/18  10:44:17  10:44:17  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.5  93/04/08  14:26:31  14:26:31  ja (Jean-Marc Adam)
 * "Free after XtSetValue"
 * 
 * Revision 1.4  93/04/08  13:08:17  13:08:17  ja ()
 * "Deallocate XmStringCreate... stuff"
 * 
 * Revision 1.3  93/01/18  13:45:57  13:45:57  ja ()
 * "Label"
 * 
 * Revision 1.2  93/01/03  20:47:21  20:47:21  mw ()
 * "new callback handling"
 * 
 * Revision 1.1  92/12/31  11:17:21  11:17:21  mw ()
 * Initial revision
 * 
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uimecall.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";

/* local callback prototypes */
static XtCallbackProc xUIicCB(Widget, XtPointer, XtPointer);


void xUIimmediatCall(char *text, Widget aktwidget)
{
   extern char *xuiLabelTable[][XUILABMAXTEXTS];  
	Widget       ICquestionbox;
	Arg          wargs[3];
	XmString     xmStr1, xmStr2, xmStr3;

	ICquestionbox = xUIdialog (XmDIALOG_QUESTION,
							aktwidget,
							LABEL_QUESTIONWINDOW,
                     QUESTIONBOX,
							(XtCallbackProc)xUIicCB,
							(XtPointer)TRUE,
							(XtCallbackProc)xUIicCB,
							(XtPointer)FALSE);
	xmStr1 = XmStringCreateLtoR( text, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(wargs[0], XmNmessageString,     xmStr1);
	xmStr2 = XmStringCreateSimple( LABEL_NO);
	XtSetArg(wargs[1], XmNcancelLabelString, xmStr2);
	xmStr3 = XmStringCreateSimple( LABEL_YES);
	XtSetArg(wargs[2], XmNokLabelString,     xmStr3);
	XtSetValues(ICquestionbox, wargs, 3);
	XtManageChild(ICquestionbox);
	XmStringFree( xmStr1);
	XmStringFree( xmStr2);
	XmStringFree( xmStr3);
}


static XtCallbackProc xUIicCB(Widget w, XtPointer status, XtPointer wdata)
{
	char putstate;

	putstate = (char)status;

	COMMTYP   = IMMEDIATCALL;
	ACTIONTYP = NULL;
	MENUNR    = NULL;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, &putstate, (long)sizeof(putstate));

	XtDestroyWidget(XtParent(w));
}
