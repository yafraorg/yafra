/*D*************************************************************************
 * Modul:			GUI - dialog           ulizdial.c
 *            
 * Description: 	create licence information dialog 
 *						set callbacks to continue application or stop it  
 *						error messages appear after 'ok' answer
 * 
 * Functions:	   ulizdial xUIstartapp xUIstopapp
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */
#include <uinclude.h>
#include <mplizenz.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ulizdial.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";

static XtCallbackProc xUIstartapp (Widget w, XtPointer closure, XtPointer data);
static XtCallbackProc xUIstopapp  (Widget w, XtPointer closure, XtPointer data);


/*F--------------------------------------------------------------------------
 *  Function:	xUIlicenceDisplay ()
 *					User has chosen "About..." in pull down menu 
 *					display the licence text 
 *  In:			std callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIlicenceDisplay(Widget w, XtPointer closure, XtPointer data)
{
	extern Widget	   licence ;

	/*--- display if exist ------*/
	if (licence)
		XtManageChild(licence);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIlicenceCreatePopup ()
 *					Create an information dialog, with a modality
 *					The texts are hardcoded in MPlizenz.h, no labels necessary
 *
 *
 *  In:			the licence message,  the parent Widget
 *  out:			-
 *  Return:		-the created widget
 *---------------------------------------------------------------------------
 */
void  xUIlicenceCreatePopup( Widget aktparent)
{
	extern Widget licence;
	extern char mp_verinfo[];
	extern char mp_guivers[];

	Arg			wargs[4];
	int			ac;
	Widget	   messagewidget, work ;
	XmString		xmStr; 	
	char        tmpbuf[_RECORDLEN];

	/*--- delete old widget --------------*/
	if (licence)
		XtManageChild(licence);
	else
		{
		/*-- dialog licence shell ----------------------------*/
		(void)sprintf(tmpbuf, "%s%s\n%s\n", LIZMESS, mp_guivers, mp_verinfo);
		ac = 0;
		xmStr = XmStringCreateLtoR(tmpbuf, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(wargs[ac], XmNmessageString, xmStr); ac++;
		XtSetArg(wargs[ac], XmNtitle, (XtArgVal) LIZWINDOW);	ac++;
		XtSetArg(wargs[ac], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL); ac++;
/*		XtSetArg(wargs[ac], XmNdialogStyle, XmDIALOG_MODELESS);	ac++;	 */
		work = XmCreateInformationDialog(aktparent, LIZENZTEXT, wargs, ac);
		XmStringFree( xmStr);

		/*--- remove undesirable buttons, create ok button */
		XtUnmanageChild(XmMessageBoxGetChild(work, XmDIALOG_HELP_BUTTON));
		XtUnmanageChild(XmMessageBoxGetChild(work, XmDIALOG_CANCEL_BUTTON));
		XtAddCallback(work, XmNokCallback, (XtCallbackProc)xUIstartapp, (XtPointer)work );

		licence = work;
		XtManageChild(work);
		}
}


 

/*F--------------------------------------------------------------------------
 *  Function:	xUIstartapp ()
 *					remove license dialog 
 *					start the application only after acknowledgment (ok)           
 *
 *  In:			std callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIstartapp (Widget w, XtPointer closure, XtPointer data)
{
	extern	ApplicationData   app_data;                /* xUIappdefaults.h */
	extern	GLOBDATA		globdata;
	extern	Widget		toplevel, mainwindow ; 
	extern	Boolean		databasenotok ; 
	extern	MENU			glob ; 
	extern	Boolean		audioflag;

	/*-- Play whelcome audio file ----------*/
	xUIaudioPlay( app_data.audioWelcome);  

	/*--- start if not already present -----*/
	if (glob.openedmenu != True)                       
	{	
		/*-- destroy liz dialog -------------*/
		XtUnmanageChild((Widget)closure);

		/*-- Start application --------------*/
		XtRealizeWidget(toplevel); 
		XtMapWidget(toplevel); 
		glob.openedmenu = True;                        /* no widget present */

		/*-- report init errors if any ------*/
		if (databasenotok)
			xUIfehler(databasenotok, 0);
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIstopapp ()
 *					User has chosen "Cancel", meaning exit the application         
 *
 *  In:			std callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIstopapp (Widget w, XtPointer closure, XtPointer data)
{
	XtDestroyWidget((Widget)closure);

	xUImainStop(_OK);
}
