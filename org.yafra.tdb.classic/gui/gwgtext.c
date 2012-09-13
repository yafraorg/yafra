/*D************************************************************
 * Modul:		GRAPHIC							gwgtext.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gwgtext.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gwgtext.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:23  ja
 general version

 * Revision 1.3  94/02/18  10:40:02  10:40:02  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:27:02  00:27:02  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgtext.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



#define MAXROWS  4


/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_textfeld ()
 *					-create a labelled frame and a form as child
 *					-insert a pushbutton, a text and an input field 
 *  In:			-the parent
 *  out:			-
 *  Return:		-the form of the labelled frame
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_textfeld( Widget parent)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	static ACTCALLBACK antwort = {BUTTONTEXTFELDANTWORT, 0};
	static ACTCALLBACK quit    = {BUTTONTEXTFELDQUIT,    0};

	Widget	textfeld, autoform, labelledFrame;   
	Arg		args[8];
	int		n;

	/*--- Labelled Frame and child ------*/
	labelledFrame = xUIframelabel( parent, &autoform, GRAPHIKTEXTFELD, LABEL_GRAPHIKTEXTFELD );
	textfeld = XmCreateForm( labelledFrame, GRAPHIKFORM, 0, 0);
	XtManageChild( textfeld);

	/*--- Button End ---------*/
	n=0;
	XtSetArg(args[n], XmNlabelString,
	XmStringCreateSimple(LABEL_GRAPHIKTEXTFELDQUIT));  n++;
	grawidgets.textfeldquit =
							XmCreatePushButton(textfeld, GRAPHIKTEXTFELDQUIT, args, n);
	XtManageChild(grawidgets.textfeldquit);
	
	/*--- Text ---------------*/
	n=0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);  n++;
	XtSetArg(args[n], XmNeditable, False);              n++;
	XtSetArg(args[n], XmNrows, MAXROWS);                n++;
	XtSetArg(args[n], XmNcolumns, _CHAR30);             n++;
	XtSetArg(args[n], XmNmaxLength, MAXROWS*_CHAR30);   n++;
	XtSetArg(args[n], XmNwordWrap, True);               n++;
	XtSetArg(args[n], XmNcursorPositionVisible, False); n++;
	grawidgets.frage = XmCreateText(textfeld, GRAPHIKFRAGE, args, n);
	XtManageChild(grawidgets.frage);

	/*--- Response field -----*/
	n=0;
	XtSetArg(args[n], XmNcolumns, _CHAR30);             n++;
	XtSetArg(args[n], XmNmaxLength, _CHAR30);           n++;
	grawidgets.antwort = (Widget)XmCreateTextField( textfeld, GRAPHIKANTWORT,
								args, (Cardinal)n);
	XtManageChild(grawidgets.antwort);

	/*--- Constraints for all widgets -------*/
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_NONE);    n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);    n++;
	XtSetValues(grawidgets.antwort, args, n);
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_NONE);    n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_WIDGET);  n++;
	XtSetArg(args[n], XmNbottomWidget, grawidgets.antwort);   n++;
	XtSetValues(grawidgets.frage, args, n);
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);    n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_WIDGET);  n++;
	XtSetArg(args[n], XmNbottomWidget, grawidgets.frage);     n++;
	XtSetValues(grawidgets.textfeldquit, args, n);

	/*--- Callbacks -------*/
	XtAddCallback( grawidgets.antwort, XmNactivateCallback,
										(XtCallbackProc)xGRaction, (XtPointer)&antwort);
	XtAddCallback( grawidgets.textfeldquit, XmNactivateCallback,
										(XtCallbackProc)xGRaction, (XtPointer)&quit);

	return( autoform);
}
