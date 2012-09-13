/*D*********************************************************
 * Modul:	GRAPHIC						gwgselec.c
 *            
 *				Create region selection scrolled list             
 *				
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgselec.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

   Log Information:
   $Log:
 */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgselec.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


#include <uinclude.h>
#include <ginclude.h>


Widget xGRwidget_selectregion( Widget parent)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	static ACTCALLBACK defcallback = {BUTTONSELECT, BUTTONSELECT_DEFINE};

	Widget	selectregion, frameLabel;			  /* Scrolled Selectlist */
	Arg		args[6];
	int		n;

	/*--- Returned manager widget -------*/
	selectregion = XmCreateRowColumn( parent, GRAPHIKROWCOL, 0, 0);
	XtManageChild( selectregion);
	
	/*--- Select frame label ------*/
	frameLabel = xUIframelabel( selectregion, NULL, GRAPHIKFRAME, LABEL_GRAPHIKSELECT );

	/*--- scrolled list -----*/
	n=0;
	XtSetArg(args[n], XmNscrollingPolicy,        XmAUTOMATIC);      n++;	
	XtSetArg(args[n], XmNselectionPolicy,        XmMULTIPLE_SELECT); n++;
	XtSetArg(args[n], XmNlistSizePolicy,         XmRESIZE_IF_POSSIBLE); n++;
	XtSetArg(args[n], XmNvisibleItemCount,       17 );               n++;
	XtSetArg(args[n], XmNwidth,                  300 );               n++;
	grawidgets.select = XmCreateScrolledList( frameLabel, GRAPHIKSELECT, args, n);
	XtManageChild( grawidgets.select);

	XtAddCallback(	grawidgets.select, XmNmultipleSelectionCallback,
									(XtCallbackProc)xGRaction, (XtPointer)&defcallback);

	return( selectregion);
}
