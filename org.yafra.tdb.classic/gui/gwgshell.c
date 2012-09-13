/*D*********************************************************
 * Modul:	GRAPHIC							gwgshell.c
 *            
 *				Main Graphic widget for MARCO POLO             
 *				Building functions for components          
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgshell.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

   Log Information:
   $Log:
 */


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgshell.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


#include  <uinclude.h>
#include  <ginclude.h>



Widget xGRwidget_shell( Widget parent)		   
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAGLOB		graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern ApplicationData app_data;
	extern Display		*display;

	Widget	shell, minimenu;
	Arg		args[7];    
	int		n, d, f;
	XmString xmstr;
	Atom		wm_delete_window;


	/********************************************************************/
	/* Toplevelshell fuer Graphik Anwendung                             */
	/********************************************************************/
	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE|MWM_DECOR_MENU
		|MWM_DECOR_MINIMIZE|MWM_DECOR_MAXIMIZE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE;

	n=0;
/*	XtSetArg(args[n], XmNallowShellResize, True); n++;   */
	XtSetArg(args[n], XmNallowShellResize, False); n++;  
	XtSetArg(args[n], XmNtitle, LABEL_GRAPHIshELL); n++;
	XtSetArg(args[n], XmNiconName, LABEL_GRAPHIKICON); n++;
	XtSetArg(args[n], XmNmwmFunctions, f); n++;
	XtSetArg(args[n], XmNmwmDecorations, d); n++;
	XtSetArg(args[n], XmNsaveUnder, True); n++;
	shell = XtCreatePopupShell(GRAPHIshELL, topLevelShellWidgetClass,
																			parent, args, n);

	/*--- Iconpixmap  fuer Toplevelshell  aufbauen -------*/
	xUIiconpixmap(shell, app_data.iconbitmapgraphik);
	/*--- Mainwindow kreieren   --------------------------*/
	grawidgets.main = XmCreateMainWindow(shell, GRAPHIKMAIN, 0, 0);
	XtManageChild(grawidgets.main);

	/*--- Minimenu area --------------*/
	minimenu = xGRwidget_menubar_mini( grawidgets.main);
	XtManageChild( minimenu );

	/*--- Work area --------------*/
	grawidgets.form = XmCreateForm(grawidgets.main, GRAPHIKFORM, 0, 0);
	XtManageChild(grawidgets.form);

	XmMainWindowSetAreas( grawidgets.main, minimenu, 0, 0, 0, grawidgets.form);

	/* Status ----------------*/
	grawidgets.status = xGRwidget_status( grawidgets.form);
	XtManageChild(grawidgets.status);

	/* Graphik ---------------*/
	grawidgets.scrolledgraphik = xGRwidget_graphik(grawidgets.form);
	XtManageChild(grawidgets.scrolledgraphik);


	/*--- Constraints in form --------------------*/
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_NONE);   n++;
	XtSetValues( grawidgets.status, args, n);
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_WIDGET);   n++;
	XtSetArg(args[n], XmNtopWidget,        grawidgets.status); n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM);     n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);     n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);     n++;
	XtSetValues( grawidgets.scrolledgraphik, args, n);


	/*********************************************************************/
	/*--- Cursorsymbole festlegen ---------------------------------------*/
	graglob.wait = XCreateFontCursor(display, XC_watch);
	graglob.work = XCreateFontCursor(display, XC_tcross);

	/*---- FileSelectionBox ---------------------------------------------*/
	grawidgets.filebox = xUIdialog(XUIDIALOG_SELECTION, shell,
						(char *)LABEL_GRAPHIKFILESELECTION, FILESELECTIONBOX,
						(XtCallbackProc)xGRgetfilename, (XtPointer)True,
						(XtCallbackProc)xGRgetfilename, (XtPointer)False);

	return(shell);
}



/*F-------------------------------------------------------------------------
 *  Function:	xGRtest ()
 *					-toggle graphic modes
 *					-
 *  In:			-std CB parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xGRtest( Widget w, XtPointer b, XtPointer wdata)
{
	extern char *entries;
	static int			graphicUsage = 0;			/* current function of graphic */

	/*--- Test rotate index ---------*/
	strcpy(entries, "\0");

	xGRchangetyp( XGRSELGRAFIC);  
}




