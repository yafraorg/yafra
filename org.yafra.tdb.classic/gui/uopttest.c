/*D************************************************************
 * Modul:		GUI - dialog        uopttest.c
 *
 *					Create a test part of option menu
 *
 * Functions:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uopttest.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: uopttest.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:19  ja
 general version

 * Revision 1.3  94/02/18  10:44:34  10:44:34  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.2  93/08/21  00:28:20  00:28:20  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.1  93/05/04  18:13:10  18:13:10  ja ()
 * Initial revision
 * 
 * 
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uopttest.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


/*E------------------------ EXTERNAL  (remove when test finished )-----------*/
extern XtCallbackProc xUICtwinTest( Widget w, XtPointer b, XtPointer wdata);
extern XtCallbackProc xUICselectTest( Widget w, XtPointer b, XtPointer wdata);
extern XtCallbackProc xUItalkTest( Widget w, XtPointer b, XtPointer wdata);
extern XtCallbackProc xGRtest( Widget w, XtPointer b, XtPointer wdata);
extern XtCallbackProc xUIoutputtest( Widget w, XtPointer b, XtPointer wdata);


/*P------------------------ PROTOTYPES --------------------------------------*/


/*P------------------------ PUBLIC VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xUIoptionTest ()
 *					-create test toggles 
 *					-
 *  In:			-the parent
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
Widget xUIoptionTest (Widget parent)
{
   extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  

	Widget	rowcolmod;
	Widget	framemenu3,  framemenu4,  framemenu5 ;
	Widget	rowcolmenu3, rowcolmenu4, rowcolmenu5 ;
	Widget	toggles[10] ;
	char		bez[_CHAR30+1] ;
	Arg		arglist[10];
	int		ac;							/* arg counter */
	int		i, j, g, nr;
	XmString	xmStr; 	

	nr = ANZ_MENU+1;		/* used for widget ident. */


             /***************** PREFERENCES *************** */

/* LEVEL 3 create framed part --------------------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu3 = xUIframelabel(parent, NULL, bez, LABEL_OPTIONFRAME_4 );
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu3 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemenu3, arglist, ac);


/* LEVEL 4  [Preferences] create toggle buttons --------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMOD, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
/*	XtSetArg(arglist[ac], XmNnavigationType, XmEXCLUSIVE_TAB_GROUP); ac++; */
	rowcolmod = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, rowcolmenu3, arglist, ac);

/* LEVEL 5  <Preference> toggles --------------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLECHANGE, nr);
	XtSetArg(arglist[ac], XmNset, True); ac++;
	XtSetArg(arglist[ac], XmNvisibleWhenOff, True); ac++;
	XtSetArg(arglist[ac], XmNindicatorType, XmN_OF_MANY); ac++;


	/*---------- Possible Tests ----------*/
	/*   xBMdlnTest                       */
	/*   xBMcatTest                       */
	/*   xBMdltTest                       */
	/*   xUICtwinTest                     */
	/*   xUICselectTest                   */
	/*   xUItalkTest                      */
	/*   xGRtest                          */
	/*   xUIoutputtest                    */
	/*------------------------------------*/
	ac--;
	xmStr = XmStringCreateSimple("Graphic Test");
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++; 
	toggles[0] = XmCreateToggleButton(rowcolmod, bez, arglist, ac);
	XmStringFree( xmStr);
	XtAddCallback(toggles[0], XmNvalueChangedCallback,
										 (XtCallbackProc)xUIoutputtest, (XtPointer)NULL );
	XtManageChild(toggles[0]);

	return( framemenu3);
}



