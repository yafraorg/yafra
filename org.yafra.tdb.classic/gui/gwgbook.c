/*D*********************************************************
 * Modul:	GRAPHIC							gwgbook.c
 *            
 *				This widget contains the elements necessary 
 *				to perform booking operations:
 *				Time scheduled update, force update, region list            
 *            
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgbook.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

   Log Information:
   $Log:
 */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgbook.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";

#include  <uinclude.h>
#include  <ginclude.h>


/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_booking ()
 *					-create a interface for booking
 *					-
 *  In:			-the parent
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_booking( Widget parent)		   
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAGLOB		graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;

	Widget	retwidget, board, rowcolmgr, frame1, frame2, rowcol ;
	Widget	header ;
	Arg		args[10];    
	int		n, d, f;

	/*--- Toplevelshell for palette ---------------*/
	d = MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU;
	f = MWM_FUNC_MOVE | MWM_FUNC_RESIZE;
	n=0;
	XtSetArg(args[n], XmNallowShellResize, True); n++;
	XtSetArg(args[n], XmNtitle, LABEL_GRAPHIKBOOKING); n++;
	XtSetArg(args[n], XmNmwmFunctions,   f); n++;
	XtSetArg(args[n], XmNmwmDecorations, d); n++;
	retwidget = XtCreatePopupShell( GRAPHIshELL, topLevelShellWidgetClass, parent, args, n); 
/*	retwidget = XmCreateDialogShell( parent, GRAPHIshELL, args, n);  */

#ifdef COMPILE
	/*--- Main managers ----------*/
	board = XmCreateBulletinBoard( retwidget, "board", 0, 0);
	XtManageChild( board);
	rowcolmgr = XmCreateRowColumn( board, "rowcol", 0, 0);
	XtManageChild( rowcolmgr);
#endif

	/*--- List region  -----*/
	grawidgets.listregion = xGRwidget_listregion( retwidget);
	XtManageChild( grawidgets.listregion);


	return( retwidget);
}


