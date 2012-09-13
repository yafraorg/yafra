/*D*************************************************************************
 * Modul:			GUI - Dialog				uctwin.c   
 *            
 * 					Twin-list widget for parameters selection with priority.
 *						Source list for selection, destination list for deletion
 * 					Twin is designed for use with UI or BM menus (but Glob)
 *
 * Functions:		.	   
 * 
 * Used:				.
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uctwin.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

/*E------------------------ EXTERNALS ---------------------------------------*/
extern char				*xuiLabelTable[][XUILABMAXTEXTS];


/*P------------------------ PROTOTYPES --------------------------------------*/
TWINLIST*		xUICtwinCreate( Widget parent); 
void				xUICtwinUpdate( char *text, TWINLIST	*aList); 
XtCallbackProc xUICsourceChoose(Widget w, XtPointer closure, XtPointer call_data);
XtCallbackProc xUICdestChoose(Widget w, XtPointer closure, XtPointer call_data);
XtCallbackProc xUICtwinButtonOk( Widget w, XtPointer closure, XtPointer call_data);
XtCallbackProc xUICtwinButtonCancel( Widget w, XtPointer closure, XtPointer call_data);
void				xUICgetListResults( char *buffer, TWINLIST *aList);
long				xUICtwinGetChoice( TWINLIST *aList);
XtActionProc	xUICtwinCancel(Widget w, XEvent* event, String* s, Cardinal* m);


/*G------------------------ GLOBAL VARIABLES --------------------------------*/
TWINLIST	*twinList = 0;





/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinPopup 
 *					Main function to use a Twin Object
 *					Check if already existent before creating 
 *  In:			-parent widget, entries are DBI string of items 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xUICtwinPopup( Widget parent, char * entries )
{
	/*--- create if not existent -------------*/
	if ( ! twinList )
	{
		/*--- first create one ----------*/
		twinList = xUICtwinCreate( parent);
		/*---- update DBI parameters ----*/
		xUICtwinUpdate( entries, twinList); 
	} else 
	{	 
		/*--- update with new values ----*/
		xUICtwinUpdate( entries, twinList); 
	}
	/*--- popup existent menu ----------*/
	XtPopup( twinList->Wgpopup, XtGrabNone);
	/*--- set for test in popdown -----*/
	twinList->chosenFlag = FALSE;
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinCreate 
 *					-create a twin list selector (source + dest scrolled lists)
 *					-
 *  In:			-parent widget    
 *  out:			-
 *  Return:		-the created TWINLIST 
 *---------------------------------------------------------------------------
 */
TWINLIST	* xUICtwinCreate( Widget parent) 
{
	extern XtAppContext mpx_appcontext;
	Widget		wrowcol, wform, wsource, wdest ; 
	Widget		wexitframe; 
	Widget		wsourceframe, wdestframe ; 
	Widget		whelpsource, whelpdest;
	Widget		searchrowsource, searchrowdest;
	Widget		wsourceform, wdestform ; 
	char			bez[_CHAR30+1] ;
	Arg			args[10];
	int			ac;
	int			d, f;
	char			actionName[] = "APCtwinCancel";
	XtTranslations		TR_twincancel;
	TWINLIST		*aList;
	XmString		xmStr;

	/*--- action table (name, func) !Caution: XtAddActions removes the name --*/
	static XtActionsRec twinActionsTable[] = {
								{"APCtwinCancel",  (XtActionProc)xUICtwinCancel }  };
	/*--- translations table (Event sequence: action proc call) ----*/
	static String twinTransTable = 	"<Btn3Up>: APCtwinCancel()";


	/*--- add new actions -----------*/
	twinActionsTable[0].string = actionName ;
	XtAppAddActions(mpx_appcontext, twinActionsTable, XtNumber(twinActionsTable));
	TR_twincancel = XtParseTranslationTable( twinTransTable);		/*compile*/

	aList = (TWINLIST *)XtMalloc( sizeof(TWINLIST));

	/*----- create shell ----------------------------*/
	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE;
	ac=0;
	XtSetArg(args[ac], XmNallowShellResize,  TRUE);  ac++;
	XtSetArg(args[ac], XmNtitle,             LABEL_SELECTLISTWINDOW); ac++;
	XtSetArg(args[ac], XmNmwmFunctions,      f);     ac++;
	XtSetArg(args[ac], XmNmwmDecorations,    d);     ac++;
	aList->Wgpopup = XmCreateDialogShell( parent, SELECTSHELL, args, ac);

	/*----- Form + 2 (form and frame) ---------------*/
	sprintf(bez, "%sFRM", SELECTSHELL);
	ac = 0;
	XtSetArg(args[ac], XmNfractionBase,       8 ); ac++;	
	wform = XmCreateForm( aList->Wgpopup, bez, args, ac);
	aList->Wgform = wform; 

	(void)sprintf(bez, "%s", FRAMEMENU );
	wsourceframe = xUIframelabel( wform, &wsourceform, bez, LABEL_FRAMESOURCETWIN);	
	whelpsource = XmCreateForm(wsourceframe, "form", args, 0);
	XtManageChild(whelpsource);
	wdestframe = xUIframelabel( wform, &wdestform, bez, LABEL_FRAMEDESTTWIN);
	whelpdest = XmCreateForm(wdestframe, "form", args, 0);
	XtManageChild(whelpdest);

	/*--- Scrolled list SOURCE --------------------*/
	ac=0;
	XtSetArg(args[ac], XmNselectionPolicy,  XmEXTENDED_SELECT);ac++;
	XtSetArg(args[ac], XmNlistSizePolicy,   XmVARIABLE);     ac++;
	XtSetArg(args[ac], XmNscrollBarDisplayPolicy,  XmAS_NEEDED); ac++;
	wsource = XmCreateScrolledList( whelpsource, CTWINSOURCELIST, args, ac);
	aList->Wgsource = wsource ;
	XtAddCallback( wsource, XmNextendedSelectionCallback,
									(XtCallbackProc)xUICsourceChoose, (XtPointer)aList);
	XtAddCallback( wsource, XmNdefaultActionCallback, 
									(XtCallbackProc)xUICsourceChoose, (XtPointer)aList);

	searchrowsource = xCOeClowCreateSearch(whelpsource, wsource);

	/*--- Scrolled list DESTINATION same args -----*/
	wdest = XmCreateScrolledList( whelpdest, CTWINDESTLIST, args, ac);
	aList->Wgdest = wdest ;
	XtAddCallback( wdest, XmNextendedSelectionCallback,
									(XtCallbackProc)xUICdestChoose, (XtPointer)aList);

/*--- Resource file does! ----------------------------*/
/*	XtOverrideTranslations( wsource, TR_twincancel);   */
/*	XtOverrideTranslations( wdest, TR_twincancel);     */

	searchrowdest = xCOeClowCreateSearch(whelpdest, wdest);


	/*--- OK and Cancel buttons ---------*/
	wexitframe = xUIexitBar( wform, 
			LABEL_OK,     (XtCallbackProc)xUICtwinButtonOk,     (XtPointer)0,
			LABEL_CANCEL, (XtCallbackProc)xUICtwinButtonCancel, (XtPointer)0  );

	/*--- Constraints for resizability --------------*/
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_NONE); ac++;
	XtSetValues( searchrowsource, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNtopWidget,        searchrowsource); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( XtParent(wsource), args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_NONE); ac++;
	XtSetValues( searchrowdest, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNtopWidget,        searchrowdest); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( XtParent(wdest), args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_POSITION); ac++;
	XtSetArg(args[ac], XmNrightPosition,    4); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNbottomWidget,     wexitframe); ac++;
	XtSetValues( wsourceform, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_POSITION); ac++;
	XtSetArg(args[ac], XmNleftPosition,     4); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNbottomWidget,     wexitframe); ac++;
	XtSetValues( wdestform, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( wexitframe, args, ac);

	return( aList);  
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinUpdate 
 *					-Update and fill source list, set dimensions of dest list 
 *					-
 *  In:			-list of items, a list     
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xUICtwinUpdate( char *text, TWINLIST	*aList) 
{
	Arg			args[10];
	int			ac;
	Dimension	width; 

	/*--- fill source list -------------------*/
	xUItostrtable( text, aList->Wgsource );  
	/*--- remove destination items -----------*/
	XmListDeleteAllItems( aList->Wgdest );
	/*--- Manage ---------------------------*/
	XtManageChild( aList->Wgdest);
	XtManageChild( aList->Wgsource); 
	XtManageChild( aList->Wgform);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICsourceChoose 
 *					-get selection choice from source list, add to dest list  
 *					-
 *  In:			-cb params (closure is a twin-list)   
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICsourceChoose(Widget w, XtPointer closure, XtPointer call_data)
{
	int		i;
	XmListCallbackStruct *cb = (XmListCallbackStruct *)call_data;
	TWINLIST	*aList; 

	aList = (TWINLIST	*)closure;
	XtUnmapWidget(aList->Wgdest);

	/*--- extended multi selection ---------------------------*/
	if (cb->reason == XmCR_EXTENDED_SELECT)
	{
		for (i=0; i < cb->selected_item_count; i++ )
		{
			/*---- add to dest list if not already existent ---*/
			if ( !XmListItemExists(aList->Wgdest, cb->selected_items[i] ))
				XmListAddItemUnselected ( aList->Wgdest, cb->selected_items[i], 0); 
		}
	}
	else
	{
		/*---- add to dest list if not already existent ---*/
		if ( !XmListItemExists(aList->Wgdest, cb->item ))
			XmListAddItemUnselected ( aList->Wgdest, cb->item, 0); 
	}
	XtMapWidget(aList->Wgdest);
	/*--- set for test in popdown -----*/
	aList->chosenFlag = TRUE;
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICdestChoose 
 *					-get selection choice from a dest list
 *					-delete from list is possible
 *  In:			-cb params    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICdestChoose(Widget w, XtPointer closure, XtPointer call_data)
{
	XmListCallbackStruct *cb = (XmListCallbackStruct *)call_data;
	TWINLIST	*aList; 

	aList = (TWINLIST	*)closure;

	/*----- delete all selected items in ONE shot ----------*/
	if (cb->reason == XmCR_EXTENDED_SELECT)
		XmListDeleteItems(w, cb->selected_items, cb->selected_item_count );

	/*--- set for test in popdown -----*/
	aList->chosenFlag = TRUE;
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinButtonOk  
 *					-OK button has been pressed, send choices to DBI 
 *					-Popdown but do NOT destroy immediately
 *  In:			-cb params    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICtwinButtonOk( Widget w, XtPointer closure, XtPointer call_data)
{
	extern char			*outcomm;
	extern XtPointer  para;
	extern GLOBDATA   globdata;
	extern MENU       menu[];
	extern MENU       glob;
	extern int        aktmenuz;
	extern int        aktmenu[];
	extern int        aktmenuobj[];
	extern int        aktfield[];
	extern int        globfield;
	extern unsigned char actiontoggle;
	extern int        bm_aktfield;

	MENU			*a;
	int			f, n;
	char			*ptr;
	long			len ;
	TWINLIST		*aList; 
	BOOKMENU		*b;

	/*--- inits ------*/
	aList = twinList; 
	b = xBMmenuActive();

	/*--- copy choice to DBI buffer ----*/
	len = xUICtwinGetChoice( aList);

	if (b)
	{
		/*--- Enable edition in menu -----------*/
		b->editfeld = TRUE;
		b->alreadywrite = FALSE;
		xBMmenufeld( b, b->Wgfields[bm_aktfield], TRUE, TRUE, FALSE, TRUE);

		if ((aList->chosenFlag) && (len >0) )
		{
			COMMTYP   = CHOOSE;
			ACTIONTYP = actiontoggle;
			/*-- MENUNR and FELDNR inchanged ----*/
			(void)xUItalkto(SEND, outcomm, strlen(outcomm));
		}
	}
	else if (globfield == -1)    /* popdown on the normal MENU */
	{
		n = aktmenu[aktmenuz];
		f = aktfield[aktmenuz];
		a = &menu[n];
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		xUImenufeld(a, a->field[f], TRUE, TRUE, FALSE, TRUE);
		globfield = -1;

		/*--- sende den gewaehlten Eintrag an Datenbankprozess */
		if ((aList->chosenFlag) && (len >0) )
		{
			COMMTYP   = CHOOSE;
			ACTIONTYP = actiontoggle;
			MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
			FELDNR    = (unsigned char)f;
			(void)xUItalkto(SEND, outcomm, strlen(outcomm));
		}
	}

	/*--- close Twin -----*/
	XtPopdown( aList->Wgpopup );
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinButtonCancel  
 *					-Cancel select operations 
 *					-Popdown but do NOT destroy immediately
 *  In:			-cb params    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICtwinButtonCancel( Widget w, XtPointer closure, XtPointer call_data)
{
	xUICtwinCancel( w, 0, 0, 0); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinGetItemsLength 
 *					-count length of twin items in dest list 
 *					-
 *  In:			-
 *  Return:		-length of all choosen items in nb of chars    
 *---------------------------------------------------------------------------
 */
long xUICtwinGetItemsLength( )
{
	int			nbItem;
	long			totlen ;
	TWINLIST		*aList;
	
	/*--- only one instance exist for the moment ------*/
	aList = twinList;
 
	/*--- check existence ------*/
	if ((aList) && (aList->Wgpopup))
	{
		/*--- get max -------*/
		XtVaGetValues( aList->Wgdest, XmNitemCount, &nbItem, NULL );
		totlen = _TEXTLEN * nbItem ;
	}
	else
		totlen = 1; 			/* one for tab */
	return (totlen); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinItemsNumber 
 *					-count number of twin items in dest list 
 *					-
 *  In:			-
 *  Return:		-number of all choosen items    
 *---------------------------------------------------------------------------
 */
int xUICtwinItemsNumber( )
{
	int			nbItem;
	TWINLIST		*aList;
	
	/*--- only one instance exist for the moment ------*/
	aList = twinList;
	nbItem = 0;
 
	/*--- check existence ------*/
	if ((aList) && (aList->Wgpopup))
		XtVaGetValues( aList->Wgdest, XmNitemCount, &nbItem, NULL );

	return (nbItem); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinGetItems 
 *					-get and copy choosen-items in buffer
 *					 each line ends with \n, the LAST ends with \0
 *  In:			-a Twin-list instance, the buffer where to write   
 *  Return:		-len of written chars
 *---------------------------------------------------------------------------
 */
long xUICtwinGetItems( char *pBuf)
{
	int			i, nbItem;
	char			rec[_TEXTLEN];
	char			*str;
	XmString		*xmstring; 
	TWINLIST		*aList;
	long			totlen; 			/* how many was copied */
	
	/*-- inits -----*/
	aList = twinList; 
	totlen = 0;

	/*--- check if twin exists -----------------*/
	if ((aList) && (aList->Wgpopup))
	{
		/*--- get nb of items  -----------------*/
		XtVaGetValues( aList->Wgdest, XmNitemCount, &nbItem, NULL );
		XtVaGetValues( aList->Wgdest, XmNitems, &xmstring, NULL );

		/*---- copy items ----------------------*/
		for (i=0; i < nbItem; i++ )
		{
			rec[0] = 0;
			/*----- extract a string ---------*/
			XmStringGetLtoR(xmstring[i], XmSTRING_DEFAULT_CHARSET, &str);
			if ( strlen(str) > _TEXTLEN)
				str[_TEXTLEN-1] = '\0';							/* limitation */
			(void)sprintf( rec, "%s", str);
			XtFree( (void *)str);
			/*---- add to DBI string ---------*/
			strncpy( pBuf, rec, strlen(rec));
			pBuf += strlen( rec);
			*pBuf++ = '\n';
			totlen += strlen( rec) +1 ; 
		}
		/* bug fix mw: delete here last \n */
		if (nbItem > 0)
		{
			pBuf-- ;                                /* replace \n  with  \0 */
			*pBuf = '\0';                           
			totlen--;                               /* up to \0             */
		}
	}
	return (totlen);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinGetChoice 
 *					-procedure to allocate memory and get selection if one or more
 *	             items have been chosen
 *  In:			-a Twin-list instance    
 *---------------------------------------------------------------------------
 */
long xUICtwinGetChoice( TWINLIST *aList)
{
	extern ApplicationData app_data;
	extern long		maxoutcomm;
	extern char		*outcomm;

	int			nbItem;
	char		   *pBuf ;
	long			totlen, len ;

	/*--- get nb of items  ---------------*/
	XtVaGetValues( aList->Wgdest, XmNitemCount, &nbItem, NULL );
	if ( nbItem > 0) 
	{
		totlen = nbItem * _TEXTLEN ;
		outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
										app_data.maxdataout, totlen, sizeof(char) );
		/*--- get and copy items -------------*/	
 	 	pBuf = outcomm ; 
		len = xUICtwinGetItems( pBuf);                      /* delimiter is \0 */
		pBuf += len ; 
	}
	else
	{
		return(0);
	} 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinDeleteItems 
 *					-procedure to clear the selections 
 *	
 *  In:			-    
 *---------------------------------------------------------------------------
 */
void xUICtwinDeleteItems( TWINLIST *aList)
{
	/*--- Check if a list exists before doing -----*/
	if (aList) 
	{ 
		/*--- remove choices ----------------------*/
		XmListDeleteAllItems( aList->Wgsource );
		XmListDeleteAllItems( aList->Wgdest );
		aList->chosenFlag = False; 
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinCancel 
 *					-Action-procedure-call to cancel selection and popdown twin 
 *	
 *  In:			-XtAction params    
 *---------------------------------------------------------------------------
 */
XtActionProc xUICtwinCancel( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern char			*outcomm;
	extern XtPointer  para;
	extern GLOBDATA   globdata;
	extern MENU       menu[];
	extern MENU       glob;
	extern int        aktmenuz;
	extern int        aktmenu[];
	extern int        aktmenuobj[];
	extern int        aktfield[];
	extern int        globfield;
	extern unsigned char actiontoggle;
	extern int        bm_aktfield;

	MENU			*a;
	int			f, n;
	char			*ptr;
	long			len ;
	TWINLIST		*aList; 
	BOOKMENU		*b;

	/*--- inits ------*/
	aList = twinList; 
	b = xBMmenuActive();

	/*--- remove choices ----------------------*/
	xUICtwinDeleteItems( aList);

	/*--- restore menu abilities --------*/
	if (b)
	{
		/*--- Enable edition in menu --*/
		b->editfeld = TRUE;
		b->alreadywrite = FALSE;
		xBMmenufeld( b, b->Wgfields[bm_aktfield], TRUE, TRUE, FALSE, TRUE);
	}
	else
	if (globfield == -1)  /* popdown on the MENU */
	{
		n = aktmenu[aktmenuz];
		f = aktfield[aktmenuz];
		a = &menu[n];
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		xUImenufeld(a, a->field[f], TRUE, TRUE, FALSE, TRUE);
	}

	XtPopdown( aList->Wgpopup );
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICtwinDestroy 
 *					-remove all allocations for an Twin-list class
 *					-Warning: original ptr must be nulled, not only the copy!
 *					-
 *  In:			-ptr to Twin to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUICtwinDestroy( TWINLIST *aList)
{
	/*--- clear ------*/
	if (aList) 
	{ 
		if (aList->Wgpopup) 
		{ 
			XtDestroyWidget(aList->Wgpopup); 
			XtFree ((void *)aList); 
			aList = 0;
		}
	}
}


/*************************** TEST ***************************************/
/*FT-----------------------------------------------------------------TEST----
 *  Function:	xUICtwinTest 
 *					-test dln features 
 *					-cb function can be called from test menu if existent
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICtwinTest( Widget w, XtPointer b, XtPointer wdata)
{
	extern Widget	toplevel; 

char listTestBuffer[] ="\
1-First-item\n\
2-Second\n\
3-Third\n\
4-Fourth\n\
5-Fith\n\
6-Sixth\n\
7-Seven\n\
8-Eight\n\
9-Item\n\
10-Item\n\
11-Item\n\
12-Item\n\
13-Item\n\
14-Item\n\
\0" ;

	/*------ create twin-list ------------------ */
	twinList = xUICtwinCreate( toplevel);

	/*------ fill with items ------------------ */
	xUICtwinUpdate( listTestBuffer, twinList); 
	XtPopup( twinList->Wgpopup, XtGrabNone);
}


