/*D*************************************************************************
 * Modul:			GUI - Dialog				ucselect.c   
 *            
 * 					Methods for SELECT widget (create, add, select, ...)
 *						A Select is here a shell+scrolled list to select One item.
 * Functions:		.	   
 * 
 * Used:				.
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ucselect.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


#define SELECTROW			"selectrow"
#define SELECTNEXT		"selectnext"
#define SELECTLAST		"selectlast"
#define SELECTTEXT		"selecttext"


/*E------------------------ EXTERNALS ---------------------------------------*/
extern char				*xuiLabelTable[][XUILABMAXTEXTS];		/* ui */  

/*P------------------------ PROTOTYPES --------------------------------------*/
void				xUICselectCreate( Widget parent, char *entries, SELECTLIST *aList); 
void				xUICselectUpdate( char *text, SELECTLIST *aList);
XtCallbackProc xUICselectChoose( Widget w, XtPointer closure, XtPointer call_data);
XtCallbackProc xUICselectQuit( Widget w, XtPointer closure, XtPointer call_data);
XtCallbackProc xUICselectButtonCancel( Widget w, XtPointer closure, XtPointer call_data);
XtActionProc	xUICselectCancel( Widget w, XEvent* event, String* s, Cardinal* m);
XtActionProc	xUICselectNewMenu( Widget w, XEvent* event, String* s, Cardinal* m);
XtActionProc	xUICselectkey( Widget w, XEvent* event, String* s, Cardinal* n);
void				xUICselectPositionTo( SELECTLIST	*aList, char search);
Widget			xCOeClowCreateSearch(Widget, Widget);
void				xCOiAlowSearch( Widget, Widget, int);
XtCallbackProc xCOiAlowSearchBackward( Widget, XtPointer, XtPointer);
XtCallbackProc xCOiAlowSearchForward( Widget, XtPointer, XtPointer);


/*G------------------------ GLOBAL VARIABLES --------------------------------*/
SELECTLIST	*selectList ; 



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectPopup ()
 *					-main function to use a Select Object 
 *  In:			-the parent, item-entries buffer
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xUICselectPopup( Widget parent, char * entries )
{
	/*--- Create selection ------*/ 
	xUICselectCreate( parent, entries, selectList );

	/*--- Reset selection -----------------------------*/ 
	selectList->selectRec[0] = 0;

	XtPopup( selectList->Wgpopup, XtGrabNone);
	XtSetKeyboardFocus( selectList->Wgpopup, selectList->Wglist);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectCreate ()
 *					-create a select ( scrolled list) 
 *					-
 *  In:			-parent widget, ressource numbering    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xUICselectCreate( Widget parent, char *entries, SELECTLIST *aList) 
{
	extern XtAppContext mpx_appcontext;
	Widget		wform, wlist;
	Widget		searchrow; 
	Widget		wexitframe ; 
	char			bez[100];
	Arg			args[10];
	int			ac;
	int			d, f;
	char			actionName1[] = "APCselectquit";
	char			actionName2[] = "APCselectnew";
	char			actionName3[] = "APCselectkey";
	XmString		xmStr; 

/*!!! deleted cause of mem leaks mw 18.8.95
	XtTranslations		TR_selectquit, TR_selectnew, TR_selectkey;
****/

	/*--- action table (name, func) !Caution: XtAddActions removes the name ---*/
	static XtActionsRec selectActionsTable[] = {
								{"APCselectquit",  (XtActionProc)xUICselectCancel},  
								{"APCselectnew",  (XtActionProc)xUICselectNewMenu},  
								{"APCselectkey",  (XtActionProc)xUICselectkey    }  
							};

	/*--- translations table (Event sequence: action-proc-call) ----*/
/*!!! deleted cause of mem leaks mw 18.8.95
	static String quitTransTable = 	"<Btn3Up>: APCselectquit()";
	static String newTransTable  = 	"<Btn2Up>: APCselectnew()";
	static String keyTransTable  = 	"<Key>: APCselectkey()";
***/

	/*--- add and compile new actions ------------*/
	selectActionsTable[0].string = actionName1 ;
	selectActionsTable[1].string = actionName2 ;
	selectActionsTable[2].string = actionName3 ;
	XtAppAddActions(mpx_appcontext, selectActionsTable, XtNumber(selectActionsTable));
/*!!! deleted cause of mem leaks mw 18.8.95
	TR_selectquit = XtParseTranslationTable( quitTransTable);
	TR_selectnew  = XtParseTranslationTable( newTransTable);
	TR_selectkey  = XtParseTranslationTable( keyTransTable);
******/

	/*----- create Select list and init ----------*/
	aList = (SELECTLIST *)XtMalloc( sizeof(SELECTLIST));
	selectList = aList; 
 
	/*--- Shell create ---------------------------*/
	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE;
	ac=0;
	XtSetArg(args[ac], XmNallowShellResize,  TRUE);  ac++;
	XtSetArg(args[ac], XmNtitle,             LABEL_SELECTLISTWINDOW); ac++;
	XtSetArg(args[ac], XmNmwmFunctions,      f);     ac++;
	XtSetArg(args[ac], XmNmwmDecorations,    d);     ac++;
	aList->Wgpopup = XmCreateDialogShell( parent, SELECTSHELL, args, ac);

	/*--- Form ---------------*/
	sprintf(bez, "%sFRM", SELECTSHELL);
	ac = 0;
	XtSetArg(args[ac], XmNfractionBase,       8 ); ac++;	
	wform = XmCreateForm( aList->Wgpopup, bez, args, ac);

	/*--- Scrolled list ------*/
	ac=0;
	XtSetArg(args[ac],XmNselectionPolicy,  XmSINGLE_SELECT);ac++;
	XtSetArg(args[ac],XmNlistSizePolicy,   XmVARIABLE);     ac++;
	XtSetArg(args[ac], XmNscrollBarDisplayPolicy,  XmAS_NEEDED); ac++;
	wlist = XmCreateScrolledList( wform, CSELECTLIST, args, ac);
	aList->Wglist = wlist ;
	XtAddCallback(wlist, XmNsingleSelectionCallback, (XtCallbackProc)xUICselectChoose, (XtPointer)aList );
	XtAddCallback(wlist, XmNdefaultActionCallback, (XtCallbackProc)xUICselectQuit, (XtPointer)aList );

	/*--- RowColumn with Textfield, next and last Button for Search ------*/
	searchrow = xCOeClowCreateSearch(wform, wlist);

/*--- Resource file does! -------------------------*/
/*!!! this was deleted by ja */
/*	XtOverrideTranslations( wlist, TR_selectquit);  */
/*	XtOverrideTranslations( wlist, TR_selectnew);   */

	/*--- add items in list --------------------------------*/
	xUICselectUpdate( entries, selectList); 

	/*--- OK and Cancel buttons ---------*/
	wexitframe = xUIexitBar( wform, 
			LABEL_OK,     (XtCallbackProc)xUICselectQuit,         (XtPointer)0,
			LABEL_CANCEL, (XtCallbackProc)xUICselectButtonCancel, (XtPointer)0  );

	/*--- Resize constraints -------------------------*/
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_NONE); ac++;
	XtSetValues( searchrow, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNtopWidget,        searchrow); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_WIDGET); ac++;
	XtSetArg(args[ac], XmNbottomWidget,     wexitframe); ac++;
	XtSetValues( XtParent(wlist), args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNtopAttachment,    XmATTACH_NONE); ac++;
	XtSetArg(args[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
	XtSetArg(args[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( wexitframe, args, ac);

	XtManageChild(wlist);
	XtManageChild(wform);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICselectUpdate ()
 *					-Update and fill items in list  with PROPER table 
 *					-
 *  In:			-list of items, a select     
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xUICselectUpdate( char *text, SELECTLIST *aList) 
{
	extern long			maxtablist;
	extern ApplicationData app_data;

	int		totlines, i, lines, breite;
	char		*ptr, *anf;
	Arg		args[10];
	long		currentlines = 0;

	/*--- get text dimension and alloc space ------*/
	totlines = xUIlines( text, &lines, &breite);
	aList->tab = (XmString *)XtMalloc( totlines * sizeof(XmString));

	/*--- separate with NULL-terminated units -----*/
	for (i=0, ptr= text; i<totlines; i++)
	{
		anf = ptr;
		while (*ptr != '\n' && *ptr != 0) 
			ptr++;
		if (*ptr == '\n')
		{
			*ptr = 0;
			ptr++;
		}
		aList->tab[i] = XmStringCreateSimple(anf);
	}

	/*--- update scrolled list parameters ---------*/
	XtSetArg(args[0], XmNvisibleItemCount, (XtArgVal)lines );
	XtSetArg(args[1], XmNitems, (XtArgVal)aList->tab );
	XtSetArg(args[2], XmNitemCount, (XtArgVal)totlines );
	XtSetValues(aList->Wglist, args, 3);

	/*---- free all compound strings ------------*/
	for (i=0; i<totlines; i++)
		XmStringFree( aList->tab[i]);
	XtFree( (void *)aList->tab ); 

}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectChoose ()
 *					-get user selection-Choice from list
 *  In:			-cb params    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICselectChoose(Widget w, XtPointer closure, XtPointer call_data)
{
	char			*str;
	XmListCallbackStruct *cb = (XmListCallbackStruct *)call_data;
	SELECTLIST	*aList; 
	BOOKMENU		*b;

	aList = (SELECTLIST	*)closure;

	/*--- single selection ---------------------*/
	XmStringGetLtoR(cb->item, XmSTRING_DEFAULT_CHARSET, &str);
	if (strlen(str) < RECLAENGE)
		(void)sprintf(aList->selectRec, "%s", str);
	else
		aList->selectRec[0] = 0;
	XtFree((void *)str);

}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectQuit ()
 *					-Action procedure call to get selection and close select popup
 *					Caution! the select list can have been triggered by DBI, in this	
 *								case there is no menu field responsible.
 *	
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICselectQuit( Widget w, XtPointer closure, XtPointer call_data)
{
	extern ApplicationData app_data;
	extern long		maxoutcomm;
	extern char		*outcomm;
	extern unsigned char	actiontoggle;
	extern int		bm_aktfield;
	extern int		bm_ix;

	int			len, totlen ;
	int			f, n;
	char			*text;
	SELECTLIST	*aList; 
	BOOKMENU		*b;

	/*--- inits -------------*/
	b = xBMmenuActive();
	aList =	selectList;									/*???? callback struct later */

	/*--- check if present ---------------*/
	if ((!aList) || (!aList->Wgpopup))
	{
		return;                                  /*>>>>>> exit >>>>>>*/
	}


	/*--- Something chosen? --------------*/
 	if (strlen(aList->selectRec) > 0)
	{
		/*---- check for buffer size ------*/
		totlen = RECLAENGE ;
		outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm, app_data.maxdataout, totlen, sizeof(char) );
		strcpy( outcomm, aList->selectRec ); 
		if (COMMTYP == BMOBJCHOOSE)
		{
			/*---  send chosen item to DBI ----*/
			COMMTYP   = BMBOOK;
			ACTIONTYP = actiontoggle;
			MENUNR    = (unsigned char) 0 ;
			FELDNR    = (unsigned char) 0 ;
			(void)xUItalkto( SEND, outcomm, strlen(outcomm));
		}
		else
		{
			if (b)
			{
				COMMTYP   = CHOOSE;
				ACTIONTYP = actiontoggle;
				/*	MENUNR and FELDNR  already set by xBMselpopup */
				(void)xUItalkto( SEND, outcomm, strlen(outcomm));
			}
		}
	}

	if (b)
	{
		/*--- Enable edition in menu -----------*/
		b->editfeld = TRUE;
		b->alreadywrite = FALSE;
		if (bm_aktfield != -1)
			xBMmenufeld( b, b->Wgfields[bm_aktfield], TRUE, TRUE, FALSE, TRUE);
		else
			xBMmenufeld( b, 0, TRUE, TRUE, FALSE, TRUE);  /*when triggered by DBI*/
	}

	/*--- kill Select widget ---------------*/
	XtPopdown(aList->Wgpopup);
	xUICselectDestroy( aList);
	selectList = 0;					/* origin ptr must be cleared */
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICselectButtonCancel ()
 *					-Cancel the selection: idem as Action procedure cancel
 *	
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICselectButtonCancel( Widget w, XtPointer closure, XtPointer call_data)
{
		xUICselectCancel(w, 0, 0, 0); 	
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICselectCancel ()
 *					-Quit and close forgetting any choice
 *					-
 *  In:			-APC parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtActionProc xUICselectCancel( Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern int		bm_aktfield;
	extern int	bm_ix ;

	SELECTLIST	*aList; 
	BOOKMENU		*b;

	/*--- there must be an item selection in BMRes menu --------*/
	if (bm_ix == _BMCATIX )
	{
		xUIbeep( w, 0, 0, 0);
		return;                                           /* >>>>>>>>> exit */ 
	}

	/*--- Clear any selection ---*/
	b = xBMmenuActive();
	aList = selectList;						/*?? find a struct later */
	aList->selectRec[0] = 0;

	/*--- Enable edition and menu sensitivity ----*/
	if (b)
	{
		b->editfeld = TRUE;
		b->alreadywrite = FALSE;
		if (bm_aktfield != -1)
			xBMmenufeld( b, b->Wgfields[bm_aktfield], TRUE, TRUE, FALSE, TRUE);
		else
			xBMmenufeld( b, 0, TRUE, TRUE, FALSE, TRUE);  /*when triggered by DBI*/
	}

	/*--- Close Cselect ----*/
	XtPopdown(aList->Wgpopup);
	xUICselectDestroy( aList);
	selectList = 0;					/* origin ptr must be cleared */
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectNewMenu ()
 *					-close select window and start new menu
 *					-
 *  In:			-APC parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtActionProc xUICselectNewMenu( Widget w, XEvent* event, String* s, Cardinal* m)
{
	xUIbeep( w, 0, 0, 0); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectDestroy ()
 *					-remove all allocations for an Select class
 *					-Warning: original ptr must be nulled, not only the copy!
 *  In:			-a ptr to a Select instance
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUICselectDestroy( SELECTLIST *aList)
{
	/*--- cleaning --------*/
	if (aList) 
	{ 
		if (aList->Wgpopup) 
		{ 
			XtDestroyWidget(aList->Wgpopup); 
			XtFree ((void *)aList); 
			/* aList = 0;     !Caution: it must be done in calling prog */
		}
	} 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUICselectkey ()
 *					-check pressed key
 *					-get key equivalent to start search in list 
 *					
 *---------------------------------------------------------------------------
 */
XtActionProc xUICselectkey( Widget w, XEvent* event, String* s, Cardinal* n)
{
	extern Display *display;
	extern Widget	toplevel; 

	int				f, len; 
	Window			selwindow;
	KeySym			keysym;
	XComposeStatus	compose; 
	char				buffer[10];
	int				bufsize = 10; 
	SELECTLIST		*aList; 

	/*--- inits ---*/
	aList = selectList;

	/*--- Select must be up ---------*/
	if (!aList->Wgpopup)
	{
		xUIbeep( toplevel, 0, 0, 0);		
		return;
	}

	/*--- find active windows -----*/
	selwindow = XtWindow( aList->Wglist );
	if (event->xany.window != selwindow) 
	{
		xUIbeep( toplevel, 0, 0, 0);		/* no widget >>>>exit */
		return;
	}

	/*------ check pressed fkey -----------------------------*/
	len = XLookupString( (XKeyEvent*)event, buffer, bufsize, &keysym, &compose);  

	if ( (keysym == XK_Shift_L) || (keysym == XK_Shift_R))	/*shift no beep*/
		return; 

	/*--- Alphanum key? --------------*/
	if (   ((keysym >= XK_KP_Space) && (keysym <= XK_KP_9))		/*keypad*/
		 || ((keysym >= XK_space) && (keysym <= XK_asciitilde))	/*a-z,A-Z,0-9*/
		)
	{
		/*--- Position the list --------------*/
		buffer[len] = '\0';
/*		xUICselectPositionTo( aList, buffer[0]);    */
	}
	else
	{
		xUIbeep( toplevel, 0, 0, 0);		/* key not interesting >>>>exit */
		return;
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUICselectPositionTo ()
 *					-set list to position whished by user
 *  In:			-a list, the search character
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUICselectPositionTo( SELECTLIST	*aList, char search)
{
	char			*str;
	Arg			wargs[5];
	int			ac;
	int			i, pos, nbitems, top, visible;
	Boolean		found; 
	XmString		*tab;									/* table of items */

	/*--- Get nb of total items ------------------*/
	XtVaGetValues(aList->Wglist,	XmNitemCount,        &nbitems, 
											XmNitems,            &tab,
											XmNtopItemPosition,  &top,
											XmNvisibleItemCount, &visible,
						NULL);

	/*--- find position of item -------------*/
	found = False;  
	for (i=0; (i <= nbitems) && (!found) ;  i++)
	{
		/*--- pos is the last match of search -------*/
		XmStringGetLtoR( tab[i], XmSTRING_DEFAULT_CHARSET, &str);
		if (*str == search)
		{
			pos = (i+1) % nbitems ;  /*0 reject at end*/
			found = True;  
		}
		XtFree((void *)str);
	}

	/*--- set item into visible position ----*/
	if (found)
	{ 
		if ((pos >= top+visible) || (pos == 0))
			XmListSetBottomPos( aList->Wglist, pos);
		else if (pos < top) 
			XmListSetPos( aList->Wglist, pos); 
	} 
}




/*************************** TEST ***************************************/
/*FT-----------------------------------------------------------------TEST----
 *  Function:	xUICselectTest ()
 *					-test dln features 
 *					-cb function can be called from test menu if existent
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUICselectTest( Widget w, XtPointer b, XtPointer wdata)
{
	char selectTestBuffer[] ="\
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

	/*------ create select-list ------------------ */
	xUICselectPopup( w, selectTestBuffer );
}


XtCallbackProc xCOiAlowSearchForward(
	Widget w,		/* calling widget */
	XtPointer closure,	/* widget specific data */
	XtPointer data		/* callback specific data */
)
{
	Arg args[1];
	Widget list;
	Widget text = (Widget)closure;

	XtSetArg(args[0], XmNuserData, &list);
	XtGetValues(w, args, 1);

	xCOiAlowSearch(list, text, 1);
}

XtCallbackProc xCOiAlowSearchBackward(
	Widget w,		/* calling widget */
	XtPointer closure,	/* widget specific data */
	XtPointer data		/* callback specific data */
)
{
	Arg args[1];
	Widget list;
	Widget text = (Widget)closure;

	XtSetArg(args[0], XmNuserData, &list);
	XtGetValues(w, args, 1);

	xCOiAlowSearch(list, text, -1);
}

void xCOiAlowSearch(
	Widget list,		/* list widget to look for */
	Widget text,		/* text widget for search string */
	int incr 		/* increment for search */
)
{
	Arg args[3];
	char *searchstring, *act, *found, *ptr, *atr, *convsearch;
	XmString *xm;
	int anz, pos, i, j;

	XtSetArg(args[0], XmNvalue, &searchstring);
	XtGetValues(text, args, 1);
	if (searchstring && *searchstring) {
		convsearch = (char *)XtMalloc((strlen(searchstring)+1)*sizeof(char));
		for (ptr=searchstring, atr=convsearch; *ptr; ptr++, atr++) {
			*atr = toupper(*ptr);
		}
		*atr = (char)0;

		XtSetArg(args[0], XmNitems, &xm);
		XtSetArg(args[1], XmNitemCount, &anz);
		XtSetArg(args[2], XmNtopItemPosition, &pos);
		XtGetValues(list, args, 3);
		if (pos == 0) {
			pos = anz;
		}
		pos--;

		/* set j to 0 if we do XmListSelectPos() */
		found = (char *)0;
		for (j=1; j<anz; j++) {
			i = pos+j*incr;
			if (i<0) i=anz+i;
			if (i>=anz) i=i-anz;
			XmStringGetLtoR(xm[i], XmSTRING_DEFAULT_CHARSET, &act);
			for (ptr=act; *ptr; ptr++) {
				*ptr = toupper(*ptr);
			}
			found = strstr(act, convsearch);
			XtFree((void *)act);
			if (found) {
				break;
			}
		}

		if (found) {
			XmListSetPos(list, i+1);

			/* don't do this in twin select */
			XmListSelectPos(list, i+1, True);
		}

		XtFree((void *)convsearch);
	}
}

Widget xCOeClowCreateSearch(
	Widget wform,		/* parent */
	Widget wlist		/* list   */
)

{
	Widget searchrow;
	Widget searchtext;
	Widget searchnext;
	Widget searchlast;
	XmString label;
	int ac;
	Arg args[2];

	ac = 0;
	XtSetArg(args[ac], XmNpacking,     XmPACK_TIGHT); ac++;
	XtSetArg(args[ac], XmNorientation, XmHORIZONTAL); ac++;
	searchrow = XmCreateRowColumn(wform, SELECTROW, args, ac);
	ac = 0;
	XtSetArg(args[ac], XmNuserData, (XtPointer)wlist); ac++;
	searchtext = XmCreateTextField(searchrow, SELECTTEXT, args, ac);
	XtAddCallback(searchtext, XmNactivateCallback, (XtCallbackProc)xCOiAlowSearchForward, (XtPointer)searchtext);

	label = XmStringCreateSimple(LABEL_SEARCHNEXT);
	XtSetArg(args[ac], XmNlabelString, label); ac++;
	searchnext = XmCreatePushButton(searchrow, SELECTNEXT, args, ac);
	XtAddCallback(searchnext, XmNactivateCallback, (XtCallbackProc)xCOiAlowSearchForward, (XtPointer)searchtext);

	ac--;
	label = XmStringCreateSimple(LABEL_SEARCHPREVIOUS);
	XtSetArg(args[ac], XmNlabelString, label); ac++;
	searchlast = XmCreatePushButton(searchrow, SELECTLAST, args, ac);
	XtAddCallback(searchlast, XmNactivateCallback, (XtCallbackProc)xCOiAlowSearchBackward, (XtPointer)searchtext);

	XtManageChild(searchtext);
	XtManageChild(searchnext);
	XtManageChild(searchlast);
	XtManageChild(searchrow);
	return(searchrow);
}
