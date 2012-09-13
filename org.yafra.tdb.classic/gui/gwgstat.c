/*D*********************************************************
 * Modul:	GRAPHIC							gwgstat.c
 *            
 *				Create graphic status line containing:             
 *				-active-region, coordinates
 *				Clear status line function
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgstat.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

   Log Information:
   $Log:
 */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgstat.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


#include <uinclude.h>
#include <ginclude.h>


Widget xGRwidget_status( Widget parent )
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	Widget	wgStatus, wgmanager, aktregionlabel;	
	Arg		args[6];
	int		n;
	XmString xmstr;
	char		coordval[XGRCOORDLEN+1];
	char		regionval[XGRREGIONLEN+1] = "*";


	/*---- main frame ------*/
	wgStatus = XmCreateFrame( parent, GRAPHIKSTATUSZEILE, 0, 0);
	n=0;
	XtSetArg(args[n], XmNresizable, True);  n++;
	wgmanager = XmCreateForm( wgStatus, GRAPHIKSTATUSZEILE, args, n);
	XtManageChild( wgmanager);

	/*--- Active region label -----------*/
	xmstr = XmStringCreateSimple( LABEL_GRAPHIKAKTREGION);
	XtSetArg(args[0], XmNlabelString,  xmstr);
	aktregionlabel = XmCreateLabelGadget(wgmanager, GRAPHIKAKTREGIONLABEL, args, 1);
	XtManageChild( aktregionlabel);
	XmStringFree( xmstr);

	/*--- Active region value-----------*/
	xGRstringpos( regionval, XGRREGIONLEN, XGRLEFT);  
	xmstr = XmStringCreateSimple( regionval);
	XtSetArg(args[0], XmNlabelString,  xmstr);
	grawidgets.aktregion = XmCreateLabelGadget( wgmanager, GRAPHIKAKTREGION, args, 1);
	XtManageChild( grawidgets.aktregion);
	XmStringFree( xmstr);

	/*--- Coordinates -------------*/
	coordval[0] = 0;
	xGRstringpos( coordval, XGRCOORDLEN, XGRRIGHT);  
	xmstr = XmStringCreateSimple( coordval);
	XtSetArg(args[0], XmNlabelString, xmstr);
	grawidgets.koord = XmCreateLabelGadget( wgmanager, GRAPHIKKOORD, args, 1);
	XtManageChild( grawidgets.koord);
	XmStringFree( xmstr);


	/******************************************************************
	* Constraints: the external windows remain constant
	* the middle window grow and shrink with main window 
	*/
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_FORM); n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_NONE);   n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);   n++;
	XtSetValues( aktregionlabel, args, n);               
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNleftWidget,       aktregionlabel);  n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_WIDGET); n++;
	XtSetArg(args[n], XmNrightWidget,      grawidgets.koord); n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);   n++;
	XtSetValues(grawidgets.aktregion, args, n);               
	n=0;
	XtSetArg(args[n], XmNtopAttachment,    XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNleftAttachment,   XmATTACH_NONE);   n++;
	XtSetArg(args[n], XmNrightAttachment,  XmATTACH_FORM);   n++;
	XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);   n++;
	XtSetValues(grawidgets.koord, args, n);               

	return( wgStatus);
}


/*F-------------------------------------------------------------------------
 *  Function:	xGRwidget_status_init ()
 *					-Clear status line 
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xGRwidget_status_clear()
{
	extern GRAWIDGETS grawidgets;

	XmString		leer2, leer3;
	char			strleer2[XGRREGIONLEN+1], strleer3[XGRCOORDLEN+1];
	Arg			args[2];


	/*--- Active region value clear -----*/
	strleer3[0] = 0;
	xGRstringpos( strleer3, XGRREGIONLEN, XGRLEFT);
	leer3 = XmStringCreateSimple(strleer3);
	XtSetArg(args[0], XmNlabelString, leer3);
	XtSetValues( grawidgets.aktregion, args, 1);
	XmStringFree(leer3);

	/*--- Coord value clear -------------*/
	strleer2[0] = 0;
	xGRstringpos( strleer2, XGRCOORDLEN, XGRLEFT);
	leer2 = XmStringCreateSimple(strleer2);
	XtSetArg(args[0], XmNlabelString, leer2);
	XtSetValues( grawidgets.koord, args, 1);
	XmStringFree(leer2);

}


