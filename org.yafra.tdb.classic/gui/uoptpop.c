/*D************************************************************
 * Modul:		GUI - dialog        uoptpop.c
 *
 *					Create an option popup menu
 *
 * Functions:	xUIoptionCreatePopup()
 * Callbacks:	from a menu button:		xUIoption 
 *					from exit:					xUIoptionPopdown
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uoptpop.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


/*E------------------------ EXTERNAL  --------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/
static Widget	xUIoptionCreate(void);
static Widget	xUIoptionCreateActionbar(Widget);
static XtCallbackProc xUIoptionGlob(Widget, XtPointer, XtPointer);
static XtCallbackProc xUIoptionMail(Widget, XtPointer, XtPointer);
static XtCallbackProc xUIoptionLabelFile(Widget, XtPointer, XtPointer);
static XtCallbackProc xUIoptionSelect(Widget, XtPointer, XtPointer);
static void xUIoptionSendOne(int, int);
static void xUIoptionSetOneValue(int, int);


/*P------------------------ PUBLIC VARIABLES --------------------------------*/

extern Widget	Woption ;                   /* main option widget            */ 
extern Boolean	openedoption;               /* true when mapped              */
extern int		optionSelect[];             /* option toggle selections      */
extern Widget	WoptionButtonQuit;          /* button Quit, used in softkey  */ 
extern Widget	WoptionButtonHelp;          /* button Help, used in softkey  */ 



/*F--------------------------------------------------------------------------
 *  Function:	xUIoptionCreatePopup ()
 *					-called by main to fill .button member of option menus
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xUIoptionCreatePopup(void)
{
	if ( ! Woption)
		{
		Woption = xUIoptionCreate();
		}	 
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIoption ()
 *					-popup the option menu 
 *					-
 *  In:			-Standard callback parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc  xUIoption( Widget w, XtPointer closure, XtPointer call_data)
{
	/*----- popup existent widget ----------*/
	XtPopup( Woption, XtGrabNone);
	openedoption = True;

	/*--- Disable other menus ------*/
	xUIpulldownSensitive( False );
	xUIglobmenuSensitive( False); 
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIoptionSendAll ()
 *					-prepare buffer then send all the options to DBI 
 *					-format is:  optionNumber \t value \n .....\0
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIoptionSendAll(void)
{
	extern int DebugFlag;
	extern int		optionSelect[];             /* option toggle selections */
	extern char			*outcomm;
	extern long			maxoutcomm;
	extern ApplicationData	app_data;
	extern unsigned char		actiontoggle;

	long		totlen;
	int		i, len = 0;      /* needed for xUItalkto */
 	char		*pBuf ;


	/*--- Allocate memory ---------------------*/
	totlen = _MAXBUTTONS_ +1 * 4 ;
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
											app_data.maxdataout, totlen, sizeof(char));
   pBuf = outcomm ; 

	/*-- Prepare buffer------------------------*/
	for (i=0;  i<_MAXBUTTONS_;  i++)
	{
		/*-- option number -------------*/
		len = sprintf(pBuf, "%d", i);
		pBuf += len; 
		*pBuf++ = _MPSYMB_TAB ;
		/*-- Value ---------------------*/
		len = sprintf(pBuf, "%d", optionSelect[i] );
		pBuf += len; 
		*pBuf++ = _MPSYMB_CR ;
	}
	*pBuf++ = _MPSYMB_NULL ;
	len = strlen(outcomm);

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "sending all options to DBI now");

	/*--- Communication with DB process -----*/
	COMMSTAT	 = MESSAGEOK; 
	COMMTYP   = OPTIONTOGGLE;
	ACTIONTYP = actiontoggle;
	MENUNR    = NULL;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, len);
	xUItalkto(RECV, 0, 0);                  /* since DBI sends nothing */
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIoptionSetDefaults ()
 *					-set the default selections for all options  
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIoptionSetDefaults(void)
{
	extern int		optionSelect[];            /* option toggle selections        */

	/*----- get toggle state ----------*/
	optionSelect[_TOGDBLOG]     = FALSE ;     /* Data Bank log                   */ 
	optionSelect[_TOGUSERLOG]   = FALSE ;     /* user  log                       */
	optionSelect[_TOGAUTOINFO]  = FALSE ;     /* Info window is automatic        */
	optionSelect[_TOGGRAPHIC]   = FALSE ;     /* Graphic                         */
	optionSelect[_TOGDLN]       = TRUE ;      /* Reisende nacheinander, denn RES */
	optionSelect[_TOGGLOBAL]    = FALSE ;     /* Global window presence          */
	optionSelect[_TOGDATORDER]  = TRUE ;      /* Data order Date=1/Alphanum=0    */
	optionSelect[_TOGAUDIO]     = FALSE ;     /* Audio facility                  */
	optionSelect[_TOGDEBUG]     = FALSE ;     /* Debugging tracing is on         */
	optionSelect[_TOGSELFROMTMP] = TRUE ;     /* read from DB or temp tables     */
}

/*F--------------------------------------------------------------------------
 *  Function:	xUIoptionPopdown ()
 *					-shut down the options-menu window
 *					-
 *  In:			-Standard callback parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIoptionPopdown(Widget w, XtPointer closure, XtPointer wdata )
{
	/*--- keep in memory ----------*/
	XtPopdown( Woption);
	openedoption = False;

	/*--- Enable UI pulldown menus ------*/
	xUIpulldownSensitive( True );
	xUIglobmenuSensitive( True); 
}



/*************************** STATIC FUNCTIONS *******************************/

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionSelect ()
 *					-set the selection choices of toggles  
 *					-send to DB toggle-index \t value ...
 *					-
 *  In:			-Standard callback parameters, wdata = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIoptionSelect(Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern int		optionSelect[];             /* option toggle selections      */

	int				state;
	unsigned char	whichToggle;
	long				totlen;
	int            len = 0;      /* needed for xUItalkto */
 
	/*----- get toggle state ----------*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;

	if (wdata == NULL)
		/*---- undefined state, set one ----------------*/
		XtVaSetValues(w, XmNset, True, NULL);
	else
		/*---- update state in my selection ------------*/
		optionSelect[(int)toggleIndex] = (int)state ;

	/*--- set indexes and transmit to DBI -------------*/
	xUIoptionSetOneValue( (int)toggleIndex, (int)state);
	xUIoptionSendOne( (int)toggleIndex, (int)state);
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionSetOneValue ()
 *					-perform action for this option 
 *					-send to DB toggle-index \t value ...
 *					-
 *  In:			-value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void xUIoptionSetOneValue(int toggleIndex, int state)
{
	extern ApplicationData	app_data;
	extern char			graphikallowed;				/* PS modul graphic ok */
	extern Boolean		graphikflag;
	extern Boolean		audioflag;

	unsigned char	whichToggle;
	long				totlen;
	int            len = 0;      /* needed for xUItalkto */
 
	/*--- Set option choice  ------------------*/
	optionSelect[toggleIndex] = state;
	
	/*--- Do specific actions -----------------*/
	switch(toggleIndex)
		{
		case 0: 
			whichToggle = _TOGDBLOG ; 
			break; 
		case 1: 
			whichToggle = _TOGUSERLOG ; 
			break; 
		case 2: 
			whichToggle = _TOGAUTOINFO ; 
			break; 
		case 3: 
			whichToggle = _TOGGRAPHIC ; 
			if (graphikallowed)
				if (state == TRUE)
				{
					graphikflag = True;            /* Graphic already initialized */
					xGRinit_graphic();
				}
				else
					graphikflag = False;   				 
			break; 
		case 4: 
			whichToggle = _TOGDLN ; 
			break; 
		case 5: 
			whichToggle = _TOGGLOBAL ; 
			xUIglobmenuPresence( (Boolean)state );
			break; 
		case 6: 
			whichToggle = _TOGDATORDER ; 
			break; 
		case 7:                                 /* audio */
			whichToggle = _TOGAUDIO ; 
			if (state == True)
				{
				audioflag = True;            
				xUIaudioPlay( app_data.audioToggle);  
				}
			else
				audioflag = False;   				 
			break; 
		default: 
			break; 
		}

}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionSendOne ()
 *					-perform action for this option 
 *					-send to DB toggle-index \t value ...
 *					-
 *  In:			-value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void xUIoptionSendOne(int toggleIndex, int state)
{
	extern char			*outcomm;
	extern long			maxoutcomm;
	extern ApplicationData	app_data;
	extern unsigned char		actiontoggle;

	unsigned char	whichToggle;
	long				totlen;
	int            len = 0;      /* needed for xUItalkto */
 	char		*pBuf ;

	/*--- Send to DBI -------------------------*/
	totlen = 10;
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm,
											app_data.maxdataout, totlen, sizeof(char));
   pBuf = outcomm ; 

	/*-- option number -------------*/
	len = sprintf(pBuf, "%d", toggleIndex);
	pBuf += len; 
	*pBuf++ = _MPSYMB_TAB ;
	/*-- Value ---------------------*/
	len = sprintf(pBuf, "%d", state );
	pBuf += len; 
	*pBuf++ = _MPSYMB_CR ;
	*pBuf++ = _MPSYMB_NULL ;

	len = strlen(outcomm);

	/*--- Communication with DB process -----*/
	COMMSTAT	 = MESSAGEOK; 
	COMMTYP   = OPTIONTOGGLE;
	ACTIONTYP = actiontoggle;
	MENUNR    = NULL;
	FELDNR    = NULL;  
	(void)xUItalkto(SEND, outcomm, len);
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionGlob ()
 *					Send global init order to DBI
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIoptionGlob(Widget w, XtPointer x, XtPointer y)
{
	extern char			*outcomm;
	extern XtPointer	para;

	/* set para to NULL because of the check in xUIinput 
	   I hope I'll understand this thing in the near future */
	para = NULL;

	/*--- Communication with DB */
	COMMTYP   = GLOBAL;
	ACTIONTYP = GLOBINIT;
	MENUNR    = NULL;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, 0);
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionLabelFile ()
 *					Send global init order to DBI
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIoptionLabelFile( Widget w, XtPointer x, XtPointer y)
{
	extern char			*outcomm;
	extern XtPointer	para;

	para = NULL;

	/*--- Communication with DB */
	COMMTYP   = GLOBAL;
	ACTIONTYP = MAKELABELFILE;
	MENUNR    = NULL;
	FELDNR    = NULL;
	(void)xUItalkto(SEND, outcomm, 0);
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionMail ()
 *					Display mail if any
 *
 *  In:			standard callback parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIoptionMail( Widget w, XtPointer x, XtPointer y)
{
	extern MP_GLOBALPROFIL globprof;

	PSSYSmail(globprof.user, NULL, PSSYS_WWWTYPNS, 0);

	return;
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionCreate ()
 *					-create shell, bulletinboard, frames, titles, option 
 *					-create pushbuttons and fields 
 *					-
 *  In:			-nr the menu index   
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
static Widget xUIoptionCreate()
{
	extern MENU			menu[];
	extern Widget		toplevel;
	extern XtTranslations	softkeytrans;
	extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  
	extern Boolean		graphikflag;
	extern Boolean		audioflag;
	extern OBJCOLORS boardcol;	/* Board matrix Colorset for ex */
 
	Widget	toggles[_MAXBUTTONS_] ;
	Widget	popup;									/* main widget */
	Widget	board, framemgr, rowcolmgr;
	Widget	framechange, rowcolmod, frametest ;
	Widget	framebutton1, rowcolbutton1 ;
	Widget	framebutton2, rowcolbutton2 ;
	Widget	framemenu1,  framemenu2,  framemenu3,  framemenu4,  framemenu5 ;
	Widget	rowcolmenu1, rowcolmenu2, rowcolmenu3, rowcolmenu4, rowcolmenu5 ;
	Widget	pb_glob, pb_labelfile, pb_mail;
	Widget	*buttons;								/* option pushbuttons        */
	Widget	rowcolptr;								/* used to split in columns */
	char		bez[_CHAR30+1], fez[_CHAR30+1] ;
	Arg		arglist[10];
	int		ac;
	int		i, j, g, nr, state;
	XmString	xmStr; 	
	MENU		*a;

	/*----- used for widget class ident. */
	nr = _OPTIONNR;

/* LEVEL 0 create a Shell -------------------------------------------------- */ 
	ac = 0;
	XtSetArg(arglist[ac], XmNtitle, LABEL_OPTIONTITLE ); ac++;
	XtSetArg(arglist[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(arglist[ac], XmNmwmFunctions, MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE); ac++;
	XtSetArg(arglist[ac], XmNmwmDecorations,
	  MWM_DECOR_BORDER|MWM_DECOR_TITLE|MWM_DECOR_MENU|MWM_DECOR_MINIMIZE); ac++;
	popup = XtCreatePopupShell(OPTIONSHELL, topLevelShellWidgetClass, toplevel,
	                           arglist, ac);

/* LEVEL 1 create a Bulletinboard ------------------------------------------ */
	(void)sprintf(bez, "%s%d", BOARD, nr);
	board = XtCreateManagedWidget(bez, xmBulletinBoardWidgetClass, popup, 0, 0);

/* LEVEL 2 create general Frame with parts ------------------------------- */
	(void)sprintf(bez, "%s%d", FRAMEMGR, nr);
	framemgr = XtCreateManagedWidget(bez, xmFrameWidgetClass, board, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLMGR, nr);
	rowcolmgr = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemgr, 0, 0);


             /***************** PREFERENCES *************** */

/* LEVEL 3 create framed part --------------------------------*/
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu3 = xUIframelabel(rowcolmgr, NULL, bez, LABEL_OPTIONFRAME_3 );
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu3 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemenu3, arglist, ac);
	XtOverrideTranslations(rowcolmenu3, softkeytrans);		/* -- toggles ---*/		

/* LEVEL 4  [Preferences] create toggle buttons --------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMOD, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	rowcolmod = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, rowcolmenu3, arglist, ac);

	/*-- _TOGDBLOG -----------------*/
	/*-- _TOGUSERLOG ---------------*/
	/*-- _TOGAUTOINFO --------------*/
	/*-- Graphic -------------------*/
	/*-- TOGDLN --------------------*/
	/*-- TOGGLOBAL -----------------*/
	/*-- Sorting mode Date or other */
	/*-- Audio ---------------------*/
	/*-- Debugging -----------------*/
	/*-- Select from temp or DB ----*/

	/*--- LEVEL 5  <Preference> toggles --------------------------------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLECHANGE, nr);
	XtSetArg(arglist[ac], XmNvisibleWhenOff, True); ac++;
	XtSetArg(arglist[ac], XmNindicatorType, XmN_OF_MANY); ac++;
	XtSetArg(arglist[ac], XmNselectColor, boardcol.select ); ac++;

/*--- LEVEL 5  <Preference> toggles --------------------------------------*/
	for (i=0;  i<_MAXBUTTONS_;  i++)
	{
		/*--- _TOGDBLOG -----*/
		xmStr = XmStringCreateSimple(xuiLabelTable[_OPTIONTOGGLE][i]);
		XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++; 
		state = (optionSelect[i])? True : False ; 
		XtSetArg(arglist[ac], XmNset, state); ac++;
		toggles[i] = XmCreateToggleButton(rowcolmod, bez, arglist, ac);
		XmStringFree( xmStr);
		XtAddCallback( toggles[i], XmNvalueChangedCallback, (XtCallbackProc)xUIoptionSelect,
						 (XtPointer)i );
		XtManageChild( toggles[i]);
		XtOverrideTranslations( toggles[i], softkeytrans);
		ac = ac - 2;
	}

#ifdef COMPILE
	/***************** SOFTWARE TESTS *************** */
	frametest = xUIoptionTest(rowcolmgr );
#endif 

	/***************** PUSHBUTTONS *************** */
	/* LEVEL 3 create framed part  -------------------------- */
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu4 = xUIframelabel(rowcolmgr, NULL, bez, LABEL_OPTIONFRAME_5 );
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT);     ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu4 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemenu4, arglist, ac);
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT);    ac++;
	rowcolmenu5 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, rowcolmenu4, arglist, ac);

	/*--- LEVEL 4  [Erase Global Values] create pushbutton pb_glob ----*/
	ac = 0;
	(void)sprintf(bez, "%s%d", PUSHBUTTON, nr);
	xmStr = XmStringCreateSimple((LABEL_OPTIONERASE));
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
	pb_glob = XmCreatePushButton(rowcolmenu5, bez, arglist, ac);
	XmStringFree( xmStr);
	XtAddCallback(pb_glob, XmNactivateCallback, (XtCallbackProc)xUIoptionGlob, (XtPointer)NULL );
	XtManageChild(pb_glob);
	XtOverrideTranslations( pb_glob, softkeytrans);

	/*--- LEVEL 4  [Make Label file] create pushbutton pb_makelabel ----*/
	ac = 0;
	(void)sprintf(bez, "%s%d", PUSHBUTTON, nr);
	xmStr = XmStringCreateSimple((LABEL_OPTIONLABELFILE));
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
	pb_labelfile = XmCreatePushButton(rowcolmenu5, bez, arglist, ac);
	XmStringFree( xmStr);
	XtAddCallback(pb_labelfile, XmNactivateCallback, (XtCallbackProc)xUIoptionLabelFile, (XtPointer)NULL );
	XtManageChild(pb_labelfile);
	XtOverrideTranslations( pb_labelfile, softkeytrans);

	/*--- LEVEL 4  [mail] create pushbutton pb_mail ----*/
	ac = 0;
	(void)sprintf(bez, "%s%d", PUSHBUTTON, nr);
	xmStr = XmStringCreateSimple(("Mail"));
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
	pb_mail = XmCreatePushButton(rowcolmenu5, bez, arglist, ac);
	XmStringFree( xmStr);
	XtAddCallback( pb_mail, XmNactivateCallback, (XtCallbackProc)xUIoptionMail, (XtPointer)NULL );
	XtManageChild( pb_mail);
	XtOverrideTranslations( pb_mail, softkeytrans);


	/***************** ACTION BAR *************** */
	/* LEVEL 3 create framed part  -------------------------- */
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu5 = xUIframelabel(rowcolmgr, NULL, bez, LABEL_OPTIONFRAME_6 );

	/*--- Action bar for softkeys ----- */
   xUIoptionCreateActionbar( framemenu5);


	return(popup);
}

/*SF--------------------------------------------------------------------------
 *  Function:	xUIoptionCreateActionbar ()
 *					-create option action bar with some functions
 *  In:			-the parent widget   
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
static Widget xUIoptionCreateActionbar( Widget parent)
{
	extern XtTranslations	softkeytrans;
   extern	char *	 xuiLabelTable[][XUILABMAXTEXTS];

	Widget	rowcol, separator; 
	Widget	child[8];
	char		bez[_CHAR30+1], fez[_CHAR30+1] ;
	char		bezdummy[_LABELLEN+1], fezdummy[_LABELLEN+1];
	Arg		arglist[10];
	int		ac;
	int		i;
	XmString		xmStr, xmStrDum ; 	


	/*--- Framed part -------------------------------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMOD, _OPTIONNR);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_COLUMN); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcol = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, parent, arglist, ac);

	/*--- preparation for dummies -------------------------*/
	(void)sprintf(bezdummy, "%s", BUTTONDUMMY);
	(void)sprintf(fezdummy, "%s",	"  ");
	xmStrDum = XmStringCreateLtoR( fezdummy, XmSTRING_DEFAULT_CHARSET);


	/*--- HELP/Info ACTION --------*/
	(void)sprintf(bez, "%s%d", BUTTONHELP, _BMDLNNR);
	(void)sprintf(fez, "%s\n%s",	LABEL_HELP_1, LABEL_HELP_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	child[0] = XmCreatePushButton(rowcol, bez, arglist, 1);
	WoptionButtonHelp = child[0];
	XmStringFree( xmStr); 
	XtAddCallback(child[0], XmNactivateCallback, (XtCallbackProc)xUIinfo, (XtPointer)NULL);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[1] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[2] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[3] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Separator --------------------------------------------------------*/
	(void)sprintf(bez, "%s%d", SEPAR, _BMDLNNR);
	XtSetArg(arglist[0], XmNseparatorType, XmNO_LINE ); 
	XtSetArg(arglist[1], XmNorientation,   XmVERTICAL    ); 
	XtSetArg(arglist[2], XmNwidth,   25    ); 
	separator = XmCreateSeparator( rowcol, bez, arglist, 3);
	XtManageChild(separator);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[4] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[5] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[6] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- [Exit] create pushbutton exit ---------------------*/
	ac = 0;
	(void)sprintf(bez, "%s", BUTTONQUIT );
	(void)sprintf(fez, "%s\n%s",	LABEL_QUITMENU_1, LABEL_QUITMENU_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
	child[7] = XmCreatePushButton( rowcol, bez, arglist, ac);
	XmStringFree( xmStr);
	XtAddCallback(child[7], XmNactivateCallback, (XtCallbackProc)xUIoptionPopdown, (XtPointer)NULL );
	WoptionButtonQuit = child[7];                       /* used in softkey() */

	/*--- common stuff -----*/
	for (i=0; i<8; i++)
		XtOverrideTranslations(child[i], softkeytrans);
	XtManageChildren(child, 8);
	XmStringFree( xmStrDum); 

	return (rowcol); 
}
