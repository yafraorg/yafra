/************************************************************** 
 * Modul:     GUI - dialog                          umenubtn.c
 *                                                         
 *            Callback for buttons from a menu 
 *            Function for pressed button depends on button type                                             
 *                                                         
 *                                                           
 * Copyright: yafra.org, Basel, Switzerland   
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umenubtn.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



/*F---------------------------------------------------------------------
 *	Function:	xUImenubutton 
 *					a menu push button has been pressed 
 *					look for menu and do action corresponding to field type
 *					
 *	In:			-std CB parameters 
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUImenubutton( Widget w, XtPointer pressed_field, XtPointer data)
{
	extern int aktmenuz;
	extern int aktmenu[];
	extern int aktfield[];
	extern MENU menu[];
	extern unsigned char actiontoggle;

	Arg wargs[5];
	int ac;
	MENU *a;
	int akt;
	XtCallbackProc  (*funcptr)();
	int j;

	/*--- aktuelles Menu mit ausl�sendem Button bestimmen */
	akt = aktmenu[aktmenuz];
	a = &menu[akt];
	j = aktfield[aktmenuz] = xUIfieldnr(a, (Widget)pressed_field);

	/*--- Sind wir im Suchmodus (UPDATE+DELETE) */
	if ((a->suchfields[j] == TRUE) && (actiontoggle != INSERT))
	{
		xUIselpopup(w, pressed_field, data);
	}
	else
	{
		/*--- Normalfall ------------------------------------*/
		switch (a->buttontype[j])
		{
			case SEDITFIELD:
			case MEDITFIELD:
				funcptr = xUIreadtowrite;
				break;
			case ONEITEMFIELD:
				funcptr = xUIseltowrite;
				break;
			case SELECTFIELD:
			case SELNOFIELD:
			case TWINSELFIELD:
			case INPNEWLEVEL:
			case MATRIXSELFIELD:
				funcptr = xUIselpopup;
				break;
			case SELECTGRAFIELD:
				funcptr = xUIselgrafic;
				break;
			case SHOWGRAFIELD:
				funcptr = xUIshowgrafic;
				break;
			case INPUTGRAFIELD:
				funcptr = xUIinpgrafic;
				break;
			case READONLYFIELD:
			case TOGGLEFIELD:
				funcptr = xUIbeeping;
				break;
			default:
				funcptr = xUImenuButtonError;
				break;
			}
		funcptr(w, pressed_field, data); /* je nach Feldtyp handeln */
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUImenuButtonError ()
 *					-missing field type 
 *  In:			-std callback params 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc  xUImenuButtonError( Widget w, XtPointer pressed_field, XtPointer data)
{
	/*---- write error message ------*/ 
	perror ("mpgui menubutton: Missing or unknown field type for button \n");
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIreadwrite ()
 *					-user has clicked in field, Turn edit field to write enable
 *  In:			-std action proc params 
 *---------------------------------------------------------------------------
 */
XtActionProc xUIreadwrite(Widget w, XEvent* event, String* s, Cardinal* m)
{
	xUIreadtowrite(0, (XtPointer)w, 0);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIreadtowrite ()
 *					Turn edit field to write
 *  In:			-std CB parameters 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIreadtowrite( Widget w, XtPointer closure, XtPointer wdata)
{
	extern Widget	toplevel;
	extern int		holdfield;
	extern int		aktmenuz;
	extern int		aktmenu[];
	extern int		aktfield[];
	extern MENU		menu[];
	extern XtTranslations transedit;

	Arg	wargs[2];
	MENU    *a;
	int     f, akt;
	Widget  editwidget;

	/*--- get active menu ----------------------------------*/
	akt = aktmenu[aktmenuz];
	a = &menu[akt];

	/*--- eliminate fantasy fields and readonly ------------*/
	editwidget = (Widget)closure;
	f = xUIfieldnr( a, editwidget);
	if ( (f < 0) || (a->buttontype[f] == READONLYFIELD))
	{
		xUIbeep(toplevel, 0, 0, 0);
		return; 
	}

	/*--- must be editable and not already in write state ---*/
	if ( (a->editfeld) && (!a->alreadywrite) )
	{
		a->alreadywrite = TRUE;
		a->enter = FALSE;
		xUImenufeld(a, editwidget, FALSE, TRUE, TRUE, FALSE);

		XtSetArg(wargs[0], XmNeditable, TRUE);
		XtSetArg(wargs[1], XmNcursorPositionVisible, TRUE);
		XtSetValues(editwidget, wargs, 2);
		XtOverrideTranslations(editwidget, transedit);
		XtSetKeyboardFocus(a->popup, editwidget);
		holdfield = a->zuobutton[f];
		aktfield[aktmenuz] = f;
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIseltowrite ()
 *					Make select and then go to editor mode
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIseltowrite(Widget w, XtPointer closure, XtPointer data)
{
	extern MENU	    menu[];
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktmenuobj[];
	extern int      holdfield;
	extern char     *outcomm;
	extern unsigned char actiontoggle;

	MENU	*a;
	int	len;
	int  	xfeld;

	a = &menu[aktmenu[aktmenuz]];
	len = xUImenustr(a);
	xfeld = xUIfieldnr( a, (Widget)closure);
	holdfield = a->zuobutton[xfeld];

	COMMTYP   = ONEITEM;
	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	FELDNR    = (unsigned char)xfeld;
	(void)xUItalkto(SEND, outcomm, len);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIselpopup ()
 *					Ask DBI process to bring items for user choice
 *  In:			-std CB parameters 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIselpopup(Widget w, XtPointer closure, XtPointer data)
{
	extern MENU	menu[];
	extern int  aktmenuz;
	extern int  aktmenu[];
	extern int  aktmenuobj[];
	extern int  holdfield;
	extern char *outcomm;
	extern unsigned char actiontoggle;

	MENU  *a;
	long	len;
	int   xfeld;

	/*--- Auswahl von bereits vorhandenen Items verlangen */
	a = &menu[aktmenu[aktmenuz]];
	xfeld = (int)xUIfieldnr( a, (Widget)closure);
	holdfield = a->zuobutton[xfeld];
	len = xUImenustr(a);

	COMMTYP   = SELECT;
	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	FELDNR    = (unsigned char)xfeld;
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIselgrafic ()
 *					Start graphic in SELECT/BOOKING mode
 *  In:			-std CB parameters 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIselgrafic(Widget w, XtPointer closure, XtPointer data)
{
	extern long     grajobflag;
	extern MENU	    menu[];
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktmenuobj[];
	extern int      holdfield;
	extern char     *outcomm;
	extern Boolean  graphikflag;
	extern unsigned char actiontoggle;

	MENU *a;
	long len;
	int  xfeld;

	/* Auswahl von bereits vorhandenen Items verlangen */

	if (graphikflag)
		{
		grajobflag = XGRSELGRAFIC;  
		COMMTYP = GRASELECT;
		}
	else
		{
		grajobflag = UNDEF;    
		COMMTYP = SELECT;
		}
	a = &menu[aktmenu[aktmenuz]];
	xfeld  = xUIfieldnr(a, (Widget)closure);
	holdfield = a->zuobutton[xfeld];
	len = xUImenustr(a);

	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	FELDNR    = (unsigned char)xfeld;
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIshowgrafic ()
 *					Start graphic in SHOW mode
 *  In:			-std CB parameters 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIshowgrafic(Widget w, XtPointer closure, XtPointer data)
{
	extern long     grajobflag;
	extern MENU	menu[];
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktmenuobj[];
	extern int      holdfield;
	extern char     *outcomm;
	extern Boolean  graphikflag;
	extern unsigned char actiontoggle;

	MENU *a;
	long len;
	int  xfeld;

	/*--- Auswahl von bereits vorhandenen Items verlangen */
	if (graphikflag)
		{
		grajobflag = XGRSHOWGRAFIC;     
		COMMTYP = GRASELECT;
		}
	else
		{
		grajobflag = UNDEF;       
		COMMTYP = SELECT;
		}
	a = &menu[aktmenu[aktmenuz]];
	xfeld = xUIfieldnr(a, (Widget)closure);
	holdfield = a->zuobutton[xfeld];
	len = xUImenustr(a);

	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
	FELDNR    = (unsigned char)xfeld;
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIinpgrafic ()
 *					Start grafik in INPUT mode
 *  In:			-std CB parameters 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIinpgrafic( Widget w, XtPointer closure, XtPointer data)
{
	extern long     grajobflag;
	extern MENU	    menu[];
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktmenuobj[];
	extern int      holdfield;
	extern char     *outcomm;
	extern Boolean  graphikflag;
	extern unsigned char actiontoggle;

	MENU *a;
	long len;
	int  xfeld;

	/*--- Auswahl von bereits vorhandenen Items verlangen */
	if (graphikflag)
		{
		grajobflag = XGRINPGRAFIC;      

		a = &menu[aktmenu[aktmenuz]];
		xfeld  = xUIfieldnr(a, (Widget)closure);
		holdfield = a->zuobutton[xfeld];
		len = xUImenustr(a);

		COMMTYP   = GRAINPUT;
		ACTIONTYP = actiontoggle;
		MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
		FELDNR    = (unsigned char)xfeld;
		(void)xUItalkto(SEND, outcomm, len);
		}
	else
		xUIfehler( XUINOGRAPHIK, 0);
}
