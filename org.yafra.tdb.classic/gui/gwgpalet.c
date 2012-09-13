/*D*********************************************************
 * Modul:	GRAPHIC							gwgpalet.c
 *            
 *				Palette contains the tools, options and dialog
 *	
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgpalet.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

   Log Information:
   $Log:
 */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgpalet.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";

#include  <uinclude.h>
#include  <ginclude.h>


/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_palette ()
 *					-create a palette toplevel shell containing:
 *					-tools, options, regions, and a dialog area
 *  In:			-the parent
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_palette( Widget parent)		   
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAGLOB		graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;

	Widget	palette, board, rowcolmgr, frame1, frame2, rowcol ;
	Widget	header ;
	Arg		args[10];    
	int		n, d, f;
	Widget	helpform1, abtregion, regionlabel;

	/*--- Toplevelshell for palette ---------------*/
	d = MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU;
	f = MWM_FUNC_MOVE;
	n=0;
	XtSetArg(args[n], XmNallowShellResize, True); n++;
	XtSetArg(args[n], XmNtitle, LABEL_GRAPHIKPALETTE); n++;
	XtSetArg(args[n], XmNmwmFunctions,   f); n++;
	XtSetArg(args[n], XmNmwmDecorations, d); n++;
	palette = XtCreatePopupShell( GRAPHIshELL, topLevelShellWidgetClass, parent, args, n); 
/*	palette = XmCreateDialogShell( parent, GRAPHIshELL, args, n);  */

	/*--- Main managers ----------*/
	board = XmCreateBulletinBoard( palette, "board", 0, 0);
	XtManageChild( board);
	rowcolmgr = XmCreateRowColumn( board, "rowcol", 0, 0);
	XtManageChild( rowcolmgr);

	/*--- Widgets Pulldown  Workarea kreieren -----*/
	grawidgets.menubar = xGRwidget_menubar( rowcolmgr );
	XtManageChild(grawidgets.menubar);


	/*--- Filename header -----*/
	header = xGRwidget_palettehead( rowcolmgr );
	XtManageChild( header);


	/*--- Optionmenus | SelectRegion -----------*/                              
	n = 0;
	XtSetArg(args[n], XmNpacking, XmPACK_TIGHT); n++;  
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	rowcol = XmCreateRowColumn( rowcolmgr, "rowcol", args, n);
	XtManageChild( rowcol);

	grawidgets.optionmenu = xGRwidget_optionmenu( rowcol);
	XtManageChild( grawidgets.optionmenu);

	grawidgets.selectregion = xGRwidget_selectregion( rowcol);
	XtManageChild( grawidgets.selectregion);


	/*--- Dialog Textfeld -------*/
	grawidgets.textfeld = xGRwidget_textfeld( rowcolmgr);
	XtManageChild( grawidgets.textfeld);

	return( palette);
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_palettehead ()
 *					-file label + filename value creation
 *  In:			-the parent
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_palettehead( Widget parent )
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	Widget	wgpalettehead, wgmanager;
	Arg		args[6];
	int		n;
	XmString xmstr;
	char		filenameval[XGRFILENAMELEN+1] = " * ";


	/*---- main frame ---------------*/
	wgpalettehead = XmCreateFrame( parent, GRAPHIKSTATUSZEILE, 0, 0);
	n = 0;
	XtSetArg(args[n], XmNpacking,     XmPACK_TIGHT); n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	wgmanager = XtCreateManagedWidget( GRAPHIKROWCOL, xmRowColumnWidgetClass, wgpalettehead, args, n);

	/*--- File name label -----------*/
	xmstr = XmStringCreateSimple( LABEL_GRAPHIKDATEILABEL);
	XtSetArg(args[0], XmNlabelString,  xmstr);
	grawidgets.dateilabel = XmCreateLabelGadget(wgmanager, GRAPHIKDATEILABEL, args, 1);
	XtManageChild( grawidgets.dateilabel);
	XmStringFree( xmstr);

	/*--- File name Value -----------*/
	xGRstringpos( filenameval, XGRFILENAMELEN, XGRLEFT);
	xmstr = XmStringCreateSimple( filenameval);
	XtSetArg(args[0], XmNlabelString, xmstr);
	grawidgets.dateiname = XmCreateLabelGadget( wgmanager, GRAPHIKDATEINAME, args, 1);
	XtManageChild( grawidgets.dateiname);
	XmStringFree( xmstr);

	return( wgpalettehead);
}

