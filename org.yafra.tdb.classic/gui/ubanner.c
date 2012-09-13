/**************************************************************
 * Modul:		GUI - dialog                            ubanner.c
 *
 *					Create the banner in top of global menu 
 *					
 * 
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ubanner.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xUIbannerCreate ()
 *					create the banner on top of global menu
 *					(label: a text,  a pushbutton)
 *  In:			-the parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xUIbannerCreate( Widget mainwindow)
{
   extern	char *	 xuiLabelTable[][XUILABMAXTEXTS];  
	extern  MENU           glob;
	extern  GLOBDATA       globdata;
	extern  XtTranslations fielddelete, edit;
	extern  Widget	bannertext ;

	Widget	board;
	Widget	framemgr, rowcolmgr, bannerbutton;
	Arg		arglist[10];
	int		ac, i;
	XmString	xmStr; 	

	/*--- Bulletinboard kreiieren LEVEL 1 ----------*/
/*	board = XtCreateManagedWidget(BOARD, xmBulletinBoardWidgetClass, mainwindow, 0, 0);
*/

	/*--- RowColWidget kreiieren LEVEL 2 -----------*/
	framemgr  = XtCreateManagedWidget(FRAMEMGR, xmFrameWidgetClass, mainwindow, 0, 0);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT);      ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL);  ac++;
	rowcolmgr = XtCreateManagedWidget(ROWCOLMGR, xmRowColumnWidgetClass, framemgr, arglist, ac);

	/*--- Pushbutton -------------------------------*/
	ac = 0;
	xmStr = XmStringCreateLtoR( LABEL_BANNER, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
	bannerbutton = XmCreatePushButton(rowcolmgr, BANNERBUTTON, arglist, ac);
	XmStringFree( xmStr); 
	XtOverrideTranslations(bannerbutton, fielddelete);
	XtAddCallback(bannerbutton, XmNactivateCallback,
											(XtCallbackProc)xUIselBanner, (XtPointer)0);
	XtManageChild( bannerbutton);

	/*--- Label ----------------------------------*/
	bannertext = XmCreateLabel( rowcolmgr, BANNERLABEL, 0, 0);
	XtManageChild( bannertext);

	return( framemgr );
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIbannerDisplay 
 *					display the text on the banner 
 *
 *  In:			-true means display
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIbannerDisplay( char *text)
{
	extern	Widget	bannertext;
	Arg			arglist[10];
	int			ac;
	XmString		xmStr; 	

	/*--- Sensitivity -----------------------------*/
	if (bannertext)
	{
		ac = 0;
		xmStr = XmStringCreateSimple(text);
		XtSetArg(arglist[ac], XmNlabelString,   xmStr ); ac++;
		XtSetValues( bannertext, arglist, ac);	
		XmStringFree( xmStr);
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIbannerClear 
 *					display the text on the banner 
 *
 *  In:			-true means display
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIbannerClear()
{
	extern	Widget	bannertext;

	/*--- Sensitivity -----------------------------*/
	if (bannertext)
	{
		xUIbannerDisplay( "" );
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIbannerPresence 
 *					display or not the banner
 *
 *  In:			-true means display
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIbannerPresence( Boolean presenceflag)
{
	extern	Widget	bannerboard;

	/*--- Sensitivity -----------------------------*/
	if (presenceflag == TRUE)
		XtManageChild( bannerboard);
	else
		XtUnmanageChild( bannerboard);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIselBanner ()
 *					user has pressed banner pushbutton 
 *									
 *  In:			std callback parameters (closure = menu) 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIselBanner(Widget w, XtPointer closure, XtPointer data)
{
	/*--- clear banner text -----------*/
	xUIbannerDisplay( "" );
}

