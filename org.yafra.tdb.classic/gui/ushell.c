/*D*************************************************************************
 * Modul:			GUI - Dialog				ushell.c   
 *            
 * 					Create diffents kind of shells  
 *						The list shell is a scrolled one with single selection
 *            		The text shell is a scrolled text for info, help, error...
 *            
 * Functions:	   xUIlistshell()			xUItextshell()
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ushell.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


/*F---------------------------------------------------------------------
 *	Function:	xUIlistshell 
 *					-creates a scrolled list within a dialog shell  
 *					-
 *	In:			-among others: shell and work widgets declared in main
 *					-
 *-----------------------------------------------------------------------
 */
void xUIlistshell( int typ, Widget parent, char *title, char *name, char *namt,
					Widget *shell, Widget *work)
{
	extern char		*xuiLabelTable[][XUILABMAXTEXTS];

	Widget		wform, button, searchrow;
	Widget		wexitframe;
	int			i, d, f;
	Arg			args[10];
	int			ac;
	char			bez[100];
	XmString 	xmStr;

	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE|MWM_DECOR_MAXIMIZE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE;
	ac=0;
	XtSetArg(args[ac], XmNallowShellResize, (XtArgVal)TRUE);  ac++;
	XtSetArg(args[ac], XmNtitle,            (XtArgVal)title); ac++;
	XtSetArg(args[ac], XmNmwmDecorations,   (XtArgVal)d);     ac++;
	XtSetArg(args[ac], XmNmwmFunctions,     (XtArgVal)f);     ac++;
	*shell = XtCreatePopupShell(name, topLevelShellWidgetClass, parent, args, ac); 

#ifdef COMPILE
	*shell = XmCreateDialogShell( parent, name, args, ac);
#endif

	/*--- Form ---------------------------*/
	sprintf(bez, "%sFRM", name);
	ac=0;
/*	XtSetArg(args[ac], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL); ac++; */
/*	XtSetArg(args[ac], XmNfractionBase,       8 ); ac++;	                     */
	wform = XmCreateForm( *shell, bez, args, ac);

	/*--- Scrolled list ------------------*/
	ac=0;
	XtSetArg(args[ac], XmNselectionPolicy,        XmSINGLE_SELECT); ac++;
	XtSetArg(args[ac], XmNlistSizePolicy,         XmVARIABLE); ac++;
	XtSetArg(args[ac], XmNscrollBarDisplayPolicy, XmSTATIC); ac++;
	*work = XmCreateScrolledList( wform, namt, args, ac);
	XtManageChild(*work);

	/*--- RowColumn with Textfield, Next and Last buttons for Search ------*/
	searchrow = xCOeClowCreateSearch(wform, *work);

	/*--- OK and Cancel buttons ----------*/
	wexitframe = xUIexitBar( wform, 
			LABEL_OK,     (XtCallbackProc)xUIchoosedown,   (XtPointer)0,
			LABEL_CANCEL, (XtCallbackProc)xUIchoosecancel, (XtPointer)0 );

	/*--- Constraints for scrolled-window resizability ---*/
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_NONE); ac++;
	XtSetValues( searchrow, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNtopWidget,          searchrow); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNbottomWidget,     wexitframe); ac++;
	XtSetValues(XtParent(*work), args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( wexitframe, args, ac);

	/*--- children management also is performed when the list size is known */
	/*--- xUItostrtable() will fill the table ------------------------------*/
	XtManageChild(wform);
}




/*F---------------------------------------------------------------------
 *	Function:	xUItextshell 
 *					-Check text size (width and length) 
 *					-Build a resizable scrolled text with ok button 
 *					-Properties of a dialog shell are usefull 
 *	In:			-widget-parent, type of text, the text
 *					-
 *-----------------------------------------------------------------------
 */
void xUItextshell( Widget parent, int type, char * entries)
{
	extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  
	extern Widget	toplevel;
	extern MENU		menu[];
	extern int		aktmenuz;
	extern int		aktmenu[];
	extern unsigned char actiontoggle;

	MENU			*a;
	BOOKMENU		*b;	
	int		ac, d, f;
	Arg		args[10];
	Widget	shell, wform, scrolltext ;
	Widget	wexitframe;
	char		bez[100], beztitle[100], bezshell[100], beztext[100];
	XmString xmstr;
	int		totlines, lines, breite;
	unsigned char		dialogStyle; 
	XtCallbackProc		specialCall; 
	Boolean				editFlag, cursorFlag; 

	/*------ get text characteristics -------------------*/
	totlines = xUIlines( entries, &lines, &breite);
	if (totlines <= 0)
		return;											/* >>>>>> nothing to display */
	lines += 2 ;										/* better look */

	/*------ set type dependent options -----------------*/
	switch( type)
	{
		case _MSG_HELP:
				sprintf(beztitle, "%s", LABEL_HELPWINDOW );
				sprintf(bezshell, "%s", HELPSHELL );
				sprintf(beztext,  "%s", HELPTEXT );
				dialogStyle = XmDIALOG_MODELESS;
				specialCall = (XtCallbackProc)xUIhelpQuit;
				editFlag   = FALSE;
				cursorFlag = FALSE;
			break;

		case _MSG_INFO:
				sprintf(beztitle, "%s", LABEL_INFOWINDOW );
				sprintf(bezshell, "%s", INFOSHELL);
				sprintf(beztext,  "%s", INFOTEXT );
				dialogStyle = XmDIALOG_MODELESS;
				specialCall = (XtCallbackProc)xUIdestroy;
				editFlag   = FALSE;
				cursorFlag = FALSE;
				break;

		case _MSG_WARNING:
				sprintf(beztitle, "%s", LABEL_WARNINGWINDOW );
				sprintf(bezshell, "%s", WARNINGSHELL);
				sprintf(beztext,  "%s", WARNINGTEXT );
				dialogStyle = XmDIALOG_MODELESS;
				specialCall = (XtCallbackProc)xUIdestroy;
				editFlag   = FALSE;
				cursorFlag = FALSE;
				break;

		case _MSG_ERROR:
		default:
				sprintf(beztitle, "%s", LABEL_ERRORWINDOW );
				sprintf(bezshell, "%s", FAULTSHELL );
				sprintf(beztext,  "%s", FAULTTEXT );
				dialogStyle = XmDIALOG_MODELESS;
				specialCall = (XtCallbackProc)xUIdestroy;
				editFlag   = FALSE;
				cursorFlag = FALSE;
			break;
	}

	/*------ Build widgets -------------------------------*/
	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE|MWM_DECOR_MINIMIZE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE;
	ac = 0;
	XtSetArg(args[ac], XmNallowShellResize, TRUE);  ac++;
	XtSetArg(args[ac], XmNtitle,            beztitle); ac++;
	XtSetArg(args[ac], XmNmwmFunctions,     f);     ac++;
	XtSetArg(args[ac], XmNmwmDecorations,   d);     ac++;
	shell = XmCreateDialogShell( parent, bezshell, args, ac);

	sprintf(bez, "%sFRM", bezshell);
	ac = 0;
	XtSetArg(args[ac], XmNfractionBase,       7); ac++;	
	XtSetArg(args[ac], XmNdialogStyle,     dialogStyle); ac++;
	wform = XmCreateForm( shell, bez, args, ac);

	/*--- Scrolled text ----------*/
	ac = 0;
	XtSetArg(args[ac], XmNscrollingPolicy,        XmAUTOMATIC); ac++;	
	XtSetArg(args[ac], XmNscrollBarDisplayPolicy, XmAS_NEEDED); ac++;  
	XtSetArg(args[ac], XmNeditable,               editFlag);    ac++;
	XtSetArg(args[ac], XmNcursorPositionVisible,  cursorFlag);  ac++;
	XtSetArg(args[ac], XmNeditMode,              XmMULTI_LINE_EDIT); ac++;
	XtSetArg(args[ac], XmNvalue,        entries); ac++;
	XtSetArg(args[ac], XmNrows,    (short)lines); ac++;
	XtSetArg(args[ac], XmNcolumns, (short)breite); ac++;
	scrolltext = XmCreateScrolledText( wform, beztext, args, ac);
	XtManageChild( scrolltext);

	/*--- OK Pprint Pushbutton -------------*/
	wexitframe = xUIexitBar( wform, 
			LABEL_OK,    (XtCallbackProc)specialCall,  (XtPointer)shell,
			LABEL_PRINT, (XtCallbackProc)xUIprintText, (XtPointer)scrolltext );

	/*--- Constraints --------*/
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNbottomWidget, wexitframe); ac++;
	XtSetValues(XtParent(scrolltext), args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetValues( wexitframe, args, ac);

	/*----- when all is added, manage the form ----*/
	XtManageChild( wform);
	XtPopup(shell, XtGrabNone);
}


