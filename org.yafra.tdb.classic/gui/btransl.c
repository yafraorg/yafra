/*D************************************************************
 * Modul:		GUI - BM dialog		btransl.c
 *
 *					Translations for BM menus 
 *
 * Functions:		
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/btransl.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*P------------------------ PROTOTYPES --------------------------------------*/
XtActionProc xBMreadwrite(Widget, XEvent*, String*, Cardinal*);
XtActionProc xBMwritetoread(Widget, XEvent*, String*, Cardinal*);
XtActionProc xBMbeep(Widget, XEvent*, String*, Cardinal*);
XtActionProc xBMdelfield(Widget, XEvent*, String*, Cardinal*);

/*G------------------------ GLOBAL VARIABLES --------------------------------*/
/*----- Our Actions look-up table used in Translations -----*/
static XtActionsRec newactions[] = {
	{"BMeditstart",(XtActionProc)xBMreadwrite},
	{"BMeditquit", (XtActionProc)xBMwritetoread},
	{"BMbeep",     (XtActionProc)xBMbeep},
	{"BMdelfield", (XtActionProc)xBMdelfield} };

/*--- translations tables (Event sequence: action proc call) ----*/
static String edittrans =
							"<Btn3Up>: BMeditquit()";
static String noedittrans =
							"<Btn3Up>: BMbeep()";
static String deletefield =
							"<Btn3Up>: BMdelfield()";
static String fieldtrans =
							"<Btn1Up>:      BMeditstart()\n\
							 <LeaveWindow>: BMeditquit()";



/*F--------------------------------------------------------------------------
 *  Function:	xBMinitTranslations ()
 *					-add new actions for BM  
 *					-parse translation table 
 *					-
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMinitTranslations( )
{
	extern XtAppContext mpx_appcontext;
	extern XtTranslations	BMtransedit, BMtransnoedit, BMedit, BMfielddelete ;

	/*----- Actions --------------------------------------------*/
	XtAppAddActions(mpx_appcontext, newactions, XtNumber(newactions));
	BMtransedit			= XtParseTranslationTable( edittrans);
	BMtransnoedit		= XtParseTranslationTable( noedittrans);
	BMfielddelete		= XtParseTranslationTable( deletefield);
	BMedit				= XtParseTranslationTable( fieldtrans);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMbeep ()
 *					-same function as xUIbeep
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xBMbeep(Widget w, XEvent* event, String* s, Cardinal* n)
{
	XBell(XtDisplay(w), 100);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMreadwrite ()
 *					-turn field into an editable one
 *					-call a callback routine performing same action
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xBMreadwrite(Widget w, XEvent* event, String* s, Cardinal* m)
{
	xBMreadtowrite(0, (XtPointer)w, 0);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMwritetoread ()
 *					-quit an edition session
 *					-make the field non editable
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xBMwritetoread(Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern XtTranslations	BMtransedit, BMtransnoedit, BMedit, BMfielddelete ;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_aktfield;
	extern int     		bm_ix;

	Arg		wargs[2];
	BOOKMENU	*b;	
	int		f, n;

	/*------ init work ------*/
	if ( bm_ix == -1 )
		return;

	b = &bm_menu[bm_ix]; 
	f = bm_aktfield;

	if ( bm_aktfield == -1 )
		return;


	if (b->Wgfields == NULL)
		return;
	if (b->Wgfields[f] == NULL)
		return;

	if (b->editfeld && b->alreadywrite && b->Wgfields[f] == w)
		{
		/*-- update sensitivity and field color, no editable ---*/
		b->alreadywrite = FALSE;
		xBMmenufeld(b, w, TRUE, TRUE, FALSE, TRUE);

		XtSetArg(wargs[0], XmNeditable, FALSE);
		XtSetArg(wargs[1], XmNcursorPositionVisible, FALSE);
		XtSetValues(w, wargs, 2);
		XtOverrideTranslations(w, BMtransnoedit);
		}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdelfield ()
 *					-user whishes to delete a field content
 *					-find field and delete string 
 *					-send/talk selected text to DBI
 *	
 *---------------------------------------------------------------------------
 */
XtActionProc xBMdelfield(Widget w, XEvent* event, String* s, Cardinal* n)
{
	extern unsigned char	actiontoggle;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	BOOKMENU	*b;	
	int		i;
	int		feldnr;

	/*--- init work ------*/
	b = &bm_menu[bm_ix]; 
	/*---- find the field peered with button -------*/
	for ( i=0;  i < b->nbitems;  i++ )
	{
		if ( w == b->Wgbuttons[i] )
			feldnr = i;
	}
	/*----- clear field string and talk to DB ------*/
	if ((b->fieldtype[feldnr] != INPNEWLEVEL) && (b->fieldtype[feldnr] != READONLYFIELD))  
	{
		XmTextSetString( b->Wgfields[feldnr], "" );
		COMMTYP   = DELETEFIELD;
		ACTIONTYP = actiontoggle;
		MENUNR    = (unsigned char)0;
		FELDNR    = (unsigned char)feldnr;
		(void)xUItalkto(SEND, 0, 0);
	}
	else
		xBMbeep( w, 0, 0, 0 );
}




