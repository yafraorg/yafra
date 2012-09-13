/*D************************************************************
 * Modul:		GUI - BM dialog                      bmenubtn.c
 *
 *					Pushbutton action wrapper 
 *					selection callbacks for booking menus 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bmenubtn.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/


/*P------------------------ PROTOTYPES --------------------------------------*/
static int xBMfieldMove( int diff, BOOKMENU *b);


/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMmenubutton ()
 *					-A DLN button has been pressed, attitude depends on actiontoggle
 *						* popup a selection
 *						* execute function correspondent to field type
 *  In:			-std callback params: closure = current Wgfields[] 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMmenubutton ( Widget w, XtPointer field, XtPointer wdata )
{
	extern unsigned char	actiontoggle;
	extern int     		bm_aktfield;

	XtCallbackProc  (*funcptr)();
	int			j;
	int			xfeld;
	BOOKMENU		*b;	

	/*--- init and check field index ------*/
	b = xBMmenuActive();
	if (b)
	{
		xfeld = xBMfeldnr( b, (Widget)field);
		if (xfeld == -1)
			return ; 
		bm_aktfield = xfeld;
	} 
	else 
		return ;                                      /* >>>>>>>> exit >>>>>>*/


	/*---- check Search mode (UPDATE+DELETE) -------------------------------*/
	if ((b->suchfields[xfeld] == TRUE) && (actiontoggle != INSERT))
	{
		/*--- build selection popup and talk to db to get choices -----*/
		xBMselpopup(w, field, wdata);
	}
	else
	{
		/*----- Normalfall INSERT ------------*/
		switch (b->fieldtype[xfeld])
			{
			case SEDITFIELD:
			case MEDITFIELD:
				funcptr = xBMreadtowrite;
				break;
			case ONEITEMFIELD:
				funcptr = xBMseltowrite;
				break;
			case SELECTFIELD:
			case SELNOFIELD:
			case TWINSELFIELD:
				funcptr = xBMselpopup;
				break;
			case SELECTGRAFIELD:
				funcptr = xBMselgrafic;
				break;
			case INPNEWLEVEL:
				funcptr = xBMnewlevel;
				break;
			case SELMENUFIELD:
				funcptr = xBMselmenu;
				break;
			case READONLYFIELD:
				funcptr = xUIbeeping;
				break;
			default:
				funcptr = xUImenuButtonError;
				break;
			}
		funcptr(w, field, wdata);		 /* je nach Feldtyp handeln */
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMselpopup ()
 *					-request DB data for select popup  
 *					-
 *  In:			-std callback params: closure = Wgfields[x] 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMselpopup(Widget w, XtPointer closure, XtPointer data)
{
	extern unsigned char	actiontoggle;
	extern char		*outcomm;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	long			len;
	int			xfeld;
	BOOKMENU		*b;	

	/*--- init field index -----------*/
	b = &bm_menu[bm_ix];
	xfeld = xBMfeldnr( b, (Widget)closure);

	/*--- Results --------------------*/
	len = xBMmenustr(b);

	/*--- Menu specific --------------*/
	if (bm_ix == _BMCATIX)
		MENUNR  = (unsigned char) _RESERVATION  ;
	else if (bm_ix == _BMDLNIX)
		MENUNR  = (unsigned char) _BMDLN  ;
 
	ACTIONTYP = actiontoggle;
	COMMTYP   = SELECT;
	FELDNR    = (unsigned char) xfeld ;
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMselmenu ()
 *					-call next menu, output only is allowed in field
 *					-
 *  In:			-std callback params
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMselmenu( Widget w, XtPointer closure, XtPointer data)
{
	extern unsigned char	actiontoggle;
	extern char		*outcomm;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	long			len;
	int			xfeld;
	BOOKMENU		*b;	

	/*--- init field index ------*/
	b = &bm_menu[bm_ix];
	xfeld = xBMfeldnr( b, (Widget)closure);
 
	/*--- Results --------------------*/
	len = xBMmenustr(b);

	/*--- Menu specific --------------*/
	if (bm_ix == _BMCATIX)
		MENUNR  = (unsigned char) _RESERVATION  ;
	else if (bm_ix == _BMDLNIX)
		MENUNR  = (unsigned char) _BMDLN  ;

	COMMTYP   = SELECT;
	ACTIONTYP = actiontoggle;
	FELDNR    = (unsigned char) xfeld ;
	(void)xUItalkto(SEND, outcomm, len);
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMnewlevel ()
 *					-Go ahead for a new menu level  
 *					-
 *  In:			-std callback params
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMnewlevel(Widget w, XtPointer closure, XtPointer data)
{
	extern int		aktmenuobj[];
	extern unsigned char	actiontoggle;
	extern char		*outcomm;
	extern int     		bm_aktmenuz;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	long			len;
	int			xfeld;
	BOOKMENU		*b;	

	/*--- init field index ------*/
	b = &bm_menu[bm_ix];
	xfeld = xBMfeldnr(b, (Widget)closure);
 
	/*--- Results --------------------*/
	len = xBMmenustr(b);

/*	COMMTYP   = NEWLEVEL;    */
	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[bm_aktmenuz];
	FELDNR    = (unsigned char) xfeld ;
	(void)xUItalkto(SEND, outcomm, len);
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMreadtowrite ()
 *					-set a field editable 
 *					-set sensitivity of pushbuttons and action bar	
 *	
 *	
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMreadtowrite(Widget w, XtPointer closure, XtPointer wdata)
{
	extern XtTranslations	BMtransedit, BMtransnoedit, BMedit, BMfielddelete ;
	extern int     		bm_aktfield;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	Arg		wargs[2];
	int		i, akt;
	Widget	editwidget;
	BOOKMENU	*b;	

	/*------ init work ------*/
	b = &bm_menu[bm_ix];
	editwidget = (Widget)closure;

	if (b->editfeld && !b->alreadywrite)
	{
		b->alreadywrite = TRUE;
		b->enter = FALSE;
		xBMmenufeld(b, editwidget, FALSE, TRUE, TRUE, FALSE);

		XtSetArg(wargs[0], XmNeditable, TRUE);
		XtSetArg(wargs[1], XmNcursorPositionVisible, TRUE);
		XtSetValues(editwidget, wargs, 2);
		XtOverrideTranslations(editwidget, BMtransedit);
		XtSetKeyboardFocus(b->Wgpopup, editwidget);

		i = xBMfeldnr(b, editwidget);
		bm_aktfield = i;
	}
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMseltowrite
 *					-only one item, it is automatically selected
 *					-
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMseltowrite(Widget w, XtPointer closure, XtPointer data)
{
	extern unsigned char	actiontoggle;
	extern char		*outcomm;
	extern int				aktmenuobj[];
	extern int     		bm_aktmenuz;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	MENU		*a;
	int		len;
	int		xfeld;
	BOOKMENU	*b;	

	/*------ init work ------*/
	b = &bm_menu[bm_ix];
	xfeld = xBMfeldnr(b, (Widget)closure);

	/*--- Results --------------------*/
	len = xBMmenustr(b);

	COMMTYP   = ONEITEM;
	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)aktmenuobj[bm_aktmenuz];
	FELDNR    = (unsigned char) xfeld ;
	(void)xUItalkto(SEND, outcomm, len);
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMfieldDeleteAll ()
 *					-user whishes to delete ALL menu fields
 *					-send/talk selected text to DBI
 *	
 *  In:			-Standard callback parameters, closure = bm menu
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMfieldDeleteAll(Widget w, XtPointer closure, XtPointer wdata)
{
	extern unsigned char	actiontoggle;
	extern int     		bm_ix;
	extern TWINLIST	*twinList;

	int		i;
	char		*ptr;
	BOOKMENU	*b;	

	/*--- init work ------*/
	b = (BOOKMENU *)closure;

	/*--- clear fields strings ------*/
	for ( i = 0; i < b->nbitems; i++ )
	{
		if ((b->fieldtype[i] != INPNEWLEVEL) && (b->fieldtype[i] != READONLYFIELD))
			XmTextSetString( b->Wgfields[i], "" );
	}

	/*--- Menu specific --------------*/
	if (bm_ix == _BMCATIX)
		xBMcatSelectionReset();
	else if (bm_ix == _BMDLNIX)
		xBMdlnSelectionReset();		

	COMMTYP   = DELETEMENU;
	ACTIONTYP = actiontoggle;
	MENUNR    = NULL;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, 0, 0);

	/*--- Clear the lists after sending to DataBank -------------*/
	xUICtwinDeleteItems( twinList);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMselgrafic
 *					-akd for graphic data
 *					-
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMselgrafic( Widget w, XtPointer closure, XtPointer data)
{
	extern unsigned char	actiontoggle;
	extern long			grajobflag;
	extern Boolean		graphikflag;
	extern char		*outcomm;
	extern BOOKMENU		bm_menu[];
	extern int     		bm_ix;

	long			len;
	int			xfeld;
	BOOKMENU		*b;	

	/*--- init field index ------*/
	b = &bm_menu[bm_ix];
	xfeld = xBMfeldnr( b, (Widget)closure);

	/*--- Results --------------------*/
	len = xBMmenustr(b);

	/*--- Ask for graphik data ------------*/
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

	ACTIONTYP = actiontoggle;
	MENUNR    = (unsigned char)_RESERVATION;
	FELDNR    = (unsigned char)xfeld;
	(void)xUItalkto(SEND, outcomm, len);
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMmenufeld
 *					-set sensitivity of pushbuttons and actionbar 
 *					-reverse color of a field 
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMmenufeld( BOOKMENU *b, Widget aWfield, Boolean sensedit, Boolean sensnextlast,
					 									 Boolean sensendedit, Boolean sensactquit)
{
	Pixel		fg, bg;
	int		i;
	Arg		wargs[2];

	/*---- menu must have pushbuttons -----*/
	if (b->Wgbuttons)
	{
		for (i=0; i < b->nbitems; i++)
		{
			XtSetSensitive(b->Wgbuttons[i], sensedit);
		}
		/*---- Action Bar -----*/
		if (b->Wgbuttonmenu)
			XtSetSensitive(b->Wgbuttonmenu, sensactquit);
		if (b->Wgbuttonact)
			XtSetSensitive(b->Wgbuttonact, sensactquit);
		if (b->Wgbuttonquit)
			XtSetSensitive(b->Wgbuttonquit, sensactquit);
	}

	/*--- Button sensitive means field in normal color ------ */
	if (aWfield)
	{
		if (sensedit)
			xUIcolorNormal( aWfield); 
		else
			xUIcolorInverse( aWfield); 
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMfeldnr
 *					-find index of field in Wgfields array
 *					-
 *  In:			-a menu , a field 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int xBMfeldnr( BOOKMENU *b, Widget field)
{
	int     i;

	for (i=0; i < b->nbitems; i++)
	{
		if (b->Wgfields[i] == field)  return(i);
	}
	return(-1);
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMmenustr ()
 *					-get menu strings out of fields from active BOOKMENU 
 *
 *  In:			-the menu
 *  out:			-
 *  Return:		-length of string 
 *---------------------------------------------------------------------------
 */
long xBMmenustr( BOOKMENU *b)
{
	extern int     		bm_ix;

	int			len;

	/*--- General results getting ----------------------*/
	if (bm_ix == _BMCATIX)
		len = xBMcatGetResults(); 
	else
		len = xBMdlnGetResults(b);

	return( len );
}






/*F--------------------------------------------------------------------------
 *  Function:	xBMeditend ()
 *					end an edition session on a menu field 
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMeditend( Widget w, XtPointer closure, XtPointer wdata)
{
	extern int     		bm_aktfield;
	extern unsigned char	actiontoggle;

	BOOKMENU		*b;	
	int		feld;
	int		type, akt;
	Boolean	alrwr;

	/*-- get menu and check if it is already in edit ------*/
	b = xBMmenuActive();
	alrwr = b->alreadywrite;
	if (alrwr)
	{
		/*-- get current field type ------*/
		feld = bm_aktfield;
		type = b->fieldtype[feld];

		/*--- in UPDATE/DELETE popdown the select if any ------*/
		if ((b->suchfields[feld] == TRUE) && (actiontoggle != INSERT))
			xUICselectQuit( 0, 0, 0);

		/*-- work depends on type --------*/
		switch (type)
		{
			case SEDITFIELD:
			case MEDITFIELD:
				xBMwritetoread( b->Wgfields[feld], 0, 0, 0);
				break;
			case ONEITEMFIELD:
				break;
			case SELECTFIELD:
			case SELNOFIELD:
				xUICselectQuit( 0, 0, 0);
				break;
			case TWINSELFIELD:
				xUICtwinButtonOk( 0, 0, 0);
				break;
		}
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMeditnext ()
 *					Get next editfield  
 *  In:			-a menu, int  
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMeditnext(  Widget w, BOOKMENU *b, int j)
{
	Widget		wfield, wbutton ;

	/*-- find widget with index ----------------*/
	wfield = b->Wgfields[j];
	wbutton = b->Wgbuttons[j];

	/*-- call as if this button was pressed ----*/
	xBMmenubutton ( wbutton, (XtPointer)wfield, (XtPointer)0 );
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMfieldnext ()
 *					go to the next field of the menu (direct or shift Return)
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMfieldnext( Widget w, XtPointer closure, XtPointer wdata)
{
	extern int     		bm_aktfield;

	BOOKMENU		*b;	
	int   		newfeld;
	Widget		wbutton ;

	/*-- find menu and end editing-----------------*/
	b = (BOOKMENU *)closure;
	wbutton = b->Wgbuttons[bm_aktfield];   /* to avoid pb since no nextbutton exist */
	xBMeditend( wbutton, closure, 0);

	/*-- move to new field ------------------------*/
	newfeld = xBMfieldMove( 1, b);

	/*-- new field action -------------------------*/
	xBMeditnext( w, b, newfeld);
}




/*S************************ STATIC FUNCTIONS *********************************/

/*F--------------------------------------------------------------------------
 *  Function:	xBMfieldMove ()
 *					Find next edit field in the menu 
 *  In:			-diff forward+1 or backward-1 , b menu
 *  out:			-
 *  Return:		-field number
 *---------------------------------------------------------------------------
 */
static int xBMfieldMove( int diff, BOOKMENU *b)
{
	extern int     		bm_aktfield;

	int                feld;

	/*-- get current field --------------------*/
	feld = bm_aktfield;

	/*-- move to next, rotate if last field ---*/
	feld += diff;
	if (feld < 0) 
		feld = b->nbitems-1;
	else if (feld >= b->nbitems) 
		feld = 0;
	
	return(feld);
}


