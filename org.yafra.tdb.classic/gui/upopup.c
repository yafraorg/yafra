/*D************************************************************
 * Modul:     GUI - dialog        upopup.c 
 *            create a menu (popup)
 *            some optional fields can be absent                                                 
 *                                                            
 * Functions: upopup                                        
 * Callbacks: from a menu button:       xUImenubutton         
 *            from a toggle:            xUItoggle             
 *            from menu switch:         xUIchange_popup       
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/upopup.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

/*------------------------ PROTOTYPES -------------------------------------*/
static XtCallbackProc xUIchange_popup(Widget, XtPointer, XtPointer);
static void	xUIcreatetoggle(int, MENU *, Widget, Widget, int);
 

/*F--------------------------------------------------------------------------
 *  Function:	xUIpopup ()
 *					-create shell, bulletinboard, frames, titles, option 
 *					-create obligatory and optional pushbuttons and fields 
 *					-check if special variable output layout 
 *					-
 *					-
 *  In:			-nr the menu index   
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
Widget xUIpopup( int nr)
{
	extern Display *display;
	extern MENU   menu[];
	extern MENU   glob;
	extern unsigned char actiontoggle;
	extern Widget toplevel;
	extern XtTranslations fielddelete, edit, softkeytrans;
	extern ApplicationData app_data;
	extern unsigned char getcolor;		 /* TRUE: hole def. Farb FALSE: nop */
	extern OBJCOLORS orgcol;		       /* Original Colorset */
	extern OBJCOLORS keycol;		       /* Key Colorset */
	extern OBJCOLORS nextmenucol;			 /* Next Menu Colorset */
	extern OBJCOLORS gracol;		       /* Graphic Colorset */
	extern OBJCOLORS boardcol;		       /* Graphic Colorset */
   extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  


	Widget rowcolbuttonptr, rowcolfieldptr, optionalform;
	Widget popup;
	Widget rowcolmgr, rowcolmenu2, framemenu2;
	Widget framemenu1, rowcolmenu1;
	Widget framebutton1, rowcolbutton1, framefield1, rowcolfield1;
	Widget framebutton2, rowcolbutton2, framefield2, rowcolfield2;
	Widget rowcolmnu, framemnu;

	char			bez[_CHAR30+1], fez[_CHAR30+1], *defwert;
	char			nullString[2] = "\0";
	Arg			arglist[10];
	size_t		len;
	int			ac;
	int			i, j, optfields ;
	int			d, f;
	MENU			*a;
	Colormap		cmap;
	Pixel			bg, fg, top, bottom, select;
	Position		ypos1, ypos2, *yposptr;
	Dimension	marginheight, marginwidth;
	short			space;
	XmString		xmStr; 	
	Dimension		width, maxwidth;

	/*--- inits menu dimensions -------*/
	a  = &menu[nr];

	/*--- find if option field has items ---*/
	optfields = 0; 
	for (i=0; i<a->anz; i++)
		{
		if (a->inpfields[i] == FALSE)
			optfields++;
		} 

	/* LEVEL 0  Shell kreieren */ 
	d = MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU | MWM_DECOR_MINIMIZE;
	f = MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE;  
	ac = 0;
	(void)sprintf(bez, "%s%d", POPUP, nr);
	XtSetArg(arglist[ac], XmNtitle, a->titel); ac++;
	XtSetArg(arglist[ac], XmNallowShellResize, TRUE); ac++;
	XtSetArg(arglist[ac], XmNmwmDecorations,   d ); ac++;
	XtSetArg(arglist[ac], XmNmwmFunctions,     f ); ac++;
	popup = XtCreatePopupShell(bez, topLevelShellWidgetClass, toplevel,
	                           arglist, ac);

	/*--- LEVEL 1 Main manager  ---------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMGR, nr);
	rowcolmgr = XtCreateManagedWidget( bez, xmRowColumnWidgetClass, popup, 0, 0);


	/* LEVEL 3  Abschnitt obligatorische Felder kreieren */
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu1 = xUIframelabel( rowcolmgr, NULL, bez, LABEL_FRAMEOBLIG ); 
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu1 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemenu1, arglist, ac);

	/* LEVEL 3  Abschnitt optionale Felder kreieren */
	(void)sprintf(bez, "%s%d", FRAMEMENU, nr);
	framemenu2 = xUIframelabel(rowcolmgr, &optionalform, bez, LABEL_FRAMEOPTION );
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu2 = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, framemenu2, arglist, ac);


	/* LEVEL 4  [obligatorisch] Abschnitt Buttons kreieren */
	(void)sprintf(bez, "%s%d", FRAMEBUTTON, nr);
	framebutton1 = XtCreateManagedWidget(bez, xmFrameWidgetClass, rowcolmenu1, 0, 0);
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLBUTTON, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_NONE); ac++;
	rowcolbutton1 = XtCreateWidget(bez, xmRowColumnWidgetClass, framebutton1, arglist, ac);
	ac = 0;
	XtSetArg(arglist[ac], XmNspacing, &space); ac++;
	XtSetArg(arglist[ac], XmNmarginHeight, &marginheight); ac++;
	XtSetArg(arglist[ac], XmNmarginWidth, &marginwidth); ac++;
	XtGetValues(rowcolbutton1, arglist, ac);

	/* LEVEL 4  [optional] Abschnitt Buttons kreieren */
	(void)sprintf(bez, "%s%d", FRAMEBUTTON, nr);
	framebutton2 = XtCreateManagedWidget(bez, xmFrameWidgetClass, rowcolmenu2, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLBUTTON, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_NONE); ac++;
	rowcolbutton2 = XtCreateWidget(bez, xmRowColumnWidgetClass, framebutton2, arglist, ac);
	XtSetArg(arglist[0], XmNspacing, &space);
	XtSetArg(arglist[1], XmNmarginHeight, &marginheight);
	XtSetArg(arglist[2], XmNmarginWidth, &marginwidth);
	XtGetValues(rowcolbutton2, arglist, 3);

	/* LEVEL 4  [obligatorisch] Abschnitt Textfelder kreieren */
	(void)sprintf(bez, "%s%d", FRAMEFIELD, nr);
	framefield1 = XtCreateManagedWidget(bez, xmFrameWidgetClass, rowcolmenu1, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLFIELD, nr);
	XtSetArg(arglist[0], XmNpacking, XmPACK_NONE);
	rowcolfield1 = XtCreateWidget(bez, xmRowColumnWidgetClass, framefield1, arglist, 2);
	if (space <= 0)
		{
		space = 1;
		XtSetArg(arglist[0], XmNspacing, space);
		XtSetValues(rowcolbutton1, arglist, 1);
		XtSetValues(rowcolfield1,  arglist, 1);
		}

	/* LEVEL 4  [optional] Abschnitt Textfelder kreieren */
	(void)sprintf(bez, "%s%d", FRAMEFIELD, nr);
	framefield2 = XtCreateManagedWidget(bez, xmFrameWidgetClass, rowcolmenu2, 0, 0);
	(void)sprintf(bez, "%s%d", ROWCOLFIELD, nr);
	XtSetArg(arglist[0], XmNpacking, XmPACK_NONE);
	rowcolfield2 = XtCreateWidget(bez, xmRowColumnWidgetClass, framefield2, arglist, 2);
	if (space <= 0)
		{
		space = 1;
		XtSetArg(arglist[0], XmNspacing, space);
		XtSetValues(rowcolbutton2, arglist, 1);
		XtSetValues(rowcolfield2,  arglist, 1);
		}

	/* LEVEL 5  alle PushButtons und Fields kreieren */
	a->pushbutton = (Widget *)XtMalloc(a->anz * sizeof(Widget));
	a->field =      (Widget *)XtMalloc(a->anz * sizeof(Widget));
	ypos1 = marginheight;
	ypos2 = marginheight;
	maxwidth = 0;

	for (i=0; i<a->anz; i++)
		{
		/* Zuordnung checken zwischen DB und Menu */
		for (j=0; j<a->anz; j++)
			{
			if (a->zuobutton[j] == i)
				break;
			}

		/*--- Gruppiere Pushbuttons in obligatorisch und optional */
		(void)sprintf(bez, "%s%d%s%d", POPUP, nr, PUSHBUTTON, j);
		if (a->inpfields[j] == TRUE)
			{
			rowcolbuttonptr = rowcolbutton1;
			rowcolfieldptr  = rowcolfield1;
			yposptr = &ypos1;
			}
		else
			{
			rowcolbuttonptr = rowcolbutton2;
			rowcolfieldptr  = rowcolfield2;
			yposptr = &ypos2;
			}

		/*--- Pushbuttons --------------------------------*/
		ac = 0;
		xmStr = XmStringCreateLtoR(a->label[j], XmSTRING_DEFAULT_CHARSET );
		XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
		XtSetArg(arglist[ac], XmNy, *yposptr); ac++;
		XtSetArg(arglist[ac], XmNx, marginwidth); ac++;
		XtSetArg(arglist[ac], XmNrecomputeSize, False); ac++;
		a->pushbutton[j] = XmCreatePushButton(rowcolbuttonptr, bez, arglist, ac);
		XtManageChild(a->pushbutton[j]);
		XmStringFree( xmStr); 

		ac = 0;
		XtSetArg(arglist[ac], XmNwidth, &width ); ac++;
		XtGetValues(a->pushbutton[j], arglist, ac);
		if (width > maxwidth) maxwidth = width;

		/*--- Get default colorsettings ----------------*/
		xUIinitcolors (a->pushbutton[j]);

		/*--- Set special app-defaults Object color ----*/
		if (a->buttontype[j] == INPNEWLEVEL) 
			xUIsetwidgetcolor( a->pushbutton[j], &nextmenucol );
		else if (a->buttontype[j] == SELECTGRAFIELD ||
			      a->buttontype[j] == SHOWGRAFIELD   ||
			      a->buttontype[j] == INPUTGRAFIELD)
			xUIsetwidgetcolor( a->pushbutton[j], &gracol );
		else if (a->buttontype[j] == MATRIXSELFIELD    ||
			      a->buttontype[j] == MATRIXSELBINFIELD ||
			      a->buttontype[j] == MATRIXEDITFIELD)
			xUIsetwidgetcolor( a->pushbutton[j], &boardcol );
		else if ((actiontoggle != INSERT) && (a->suchfields[j] == TRUE))
			xUIsetwidgetcolor( a->pushbutton[j], &keycol );


		/*-- Setze den default Wert, falls er vorhanden ist im global ---*/
		if (a->vonglobal[j] != -1)
			{
			defwert = XmTextGetString(glob.field[a->vonglobal[j]]);
			len = strlen(defwert);
			if (len < 1)
				{
				XtFree( (void *)defwert);
				defwert = (char *)NULL;
				}
			}
		else
			defwert = (char *)NULL;

		/*-- create Text fields ------------------------------------*/
		(void)sprintf(fez, "%s%d%s%d", POPUP, nr, FIELD, j);
		a->field[j] = xUIeditor(fez, rowcolfieldptr, a->anzlines[j], a->anzcolumns[j],
		                        defwert, yposptr, space, edit);
		if (a->vonglobal[j] != -1 && defwert != (char *)NULL)
			XtFree( (void *)defwert); 

		/*--- set callback on pushbutton with field as parameter ---*/
		XtAddCallback(a->pushbutton[j], XmNactivateCallback,
		              (XtCallbackProc)xUImenubutton, (XtPointer)a->field[j]);
		}


	/*-- translations and visible fields -------------------------*/
	for (i=0; i<a->anz; i++)
		{
		ac = 0;
		XtSetArg(arglist[ac], XmNwidth, maxwidth ); ac++;
		XtSetValues(a->pushbutton[i], arglist, ac);
		XtOverrideTranslations(a->pushbutton[i], fielddelete);
		XtOverrideTranslations(a->pushbutton[i], softkeytrans);  
		XtOverrideTranslations(a->field[i],      softkeytrans);  
		if (a->buttontype[i] != INPNEWLEVEL)
			XtManageChild(a->field[i]);
		}

	/*-- Manage row columns after button and field creations -----*/
	XtManageChild( rowcolbutton1 );
	XtManageChild( rowcolfield1);
	XtManageChild( rowcolbutton2);
	XtManageChild( rowcolfield2);


	/* LEVEL 4 + 5  Action buttons kreieren ---------------------------*/
	xUIactionbar(a, rowcolmgr);

	/* LEVEL 4 + 5  Abschnitt  DB-Modus als RadioBox kreieren ---------*/
	if (a->typ != _OUTPUT)							/* Output has NO toggles */
		xUIcreatetoggle( nr, a, rowcolmgr, optionalform, optfields ); 


	XtRealizeWidget( popup);

   /*--- optional menu managed (default) ---*/
	if ((optfields > 0))
		{
		XtManageChild( optionalform);
		}
	else
		{
		XtUnmanageChild( optionalform);
		}

	return( popup);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIchange_popup ()
 *					-toggle between obligatory and optional
 *					-value is read from callback struct
 *  In:			-std callback params 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static XtCallbackProc xUIchange_popup(Widget w, XtPointer closure, XtPointer wdata)
{
	XmToggleButtonCallbackStruct	 *cb;
	Widget								 optionalform;

	cb = (XmToggleButtonCallbackStruct *)wdata;
	optionalform = (Widget)closure;

	if (cb->set)
		XtManageChild(optionalform);
	else
		XtUnmanageChild(optionalform);

}



/***************************** STATIC FUNCTIONS *****************************/

/*F--------------------------------------------------------------------------
 *  Function:	xUIcreatetoggle ()
 *					-create DB operation toggles  
 *					-create Optional field ONLY if there are fields 
 *					-
 *  In:			-the current menu, the parent widget
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static void xUIcreatetoggle( int nr, MENU *a, Widget parent, Widget optionalform,
										int optfields )
{
	extern OBJCOLORS boardcol;		            /* matrix Colorset for example */
	extern MENU   menu[];
	extern unsigned char actiontoggle;
   extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  
	extern XtTranslations  softkeytrans;

	Widget		frameradiobox, radiobox, framechange;
	Widget		framemod, rowcolmod, manager ;
	Widget		child[3], optional;
	char			bez[_CHAR30+1] ;
	Arg 			arglist[10];
	int			ac, i;
	Boolean		state;
	XmString		xmStr; 	


	/* LEVEL 3  Abschnitt Toggles kreieren */
	(void)sprintf(bez, "%s%d", FRAMEMOD, nr);
	framemod = xUIframelabel(parent, NULL, bez, LABEL_FRAMETOGGLE );

	/*--- Form is prefered */
	(void)sprintf(bez, "%s%d", ROWCOLMOD, nr);
	manager  = XmCreateForm( framemod, bez, 0, 0);
	XtManageChild( manager);

	/* LEVEL 4  [Toggles] DB-Modus als RadioBox kreieren */
	(void)sprintf(bez, "%s%d", FRAMERADIOBOX, nr);
	frameradiobox = XtCreateManagedWidget(bez, xmFrameWidgetClass, manager, NULL, 0);
	(void)sprintf(bez, "%s%d", RADIOBOX, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	radiobox = XmCreateRadioBox( frameradiobox, RADIOBOX, arglist, ac);	

	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEINSERT, nr);
	xmStr = XmStringCreateSimple(LABEL_INSERTMODE) ;
	XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
	state = (actiontoggle == INSERT)? True : False ;	 /* Default state  */
	XtSetArg(arglist[ac], XmNset, state); ac++;
	XtSetArg(arglist[ac], XmNselectColor, boardcol.select ); ac++;
	a->toggleinsert = XmCreateToggleButton( radiobox, bez, arglist, ac);
	child[0] = a->toggleinsert;
	XmStringFree( xmStr); 
	XtAddCallback( child[0], XmNvalueChangedCallback, (XtCallbackProc)xUItoggle,
													             (XtPointer)INSERT);
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEUPDATE, nr);
	xmStr = XmStringCreateSimple(LABEL_UPDATEMODE) ;
	XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
	state = (actiontoggle == UPDATE)? True : False ;	 /* Default state  */
	XtSetArg(arglist[ac], XmNset, state); ac++;
	XtSetArg(arglist[ac], XmNselectColor, boardcol.select ); ac++;
	a->toggleupdate = XmCreateToggleButton( radiobox, bez, arglist, ac);
	child[1] = a->toggleupdate;
	XmStringFree( xmStr); 
	XtAddCallback(child[1], XmNvalueChangedCallback, (XtCallbackProc)xUItoggle,
	          												    (XtPointer)UPDATE);
	ac = 0;
	(void)sprintf(bez, "%s%d", TOGGLEDELETE, nr);
	xmStr = XmStringCreateSimple(LABEL_DELETEMODE) ;
	XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
	state = (actiontoggle == MPDELETE)? True : False ; /* Default state  */
	XtSetArg(arglist[ac], XmNset, state); ac++;
	XtSetArg(arglist[ac], XmNselectColor, boardcol.select ); ac++;
	a->toggledelete = XmCreateToggleButton( radiobox, bez, arglist, ac);
	child[2] = a->toggledelete;
	XmStringFree( xmStr); 
	XtAddCallback(child[2], XmNvalueChangedCallback, (XtCallbackProc)xUItoggle,
	            												 (XtPointer)MPDELETE);
	for (i=0; i<3; i++)
		XtOverrideTranslations(child[i], softkeytrans);

	/*--- constraints ---------*/
	ac = 0;
	XtSetArg(arglist[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
	XtSetArg(arglist[ac], XmNleftAttachment,   XmATTACH_FORM); ac++;
	XtSetArg(arglist[ac], XmNrightAttachment,  XmATTACH_NONE); ac++;
	XtSetArg(arglist[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
	XtSetValues( frameradiobox, arglist, ac);
	XtManageChild(radiobox);
	XtManageChildren(child, 3);

	/*--------- LEVEL 4  [Optional]  change between obli and optional fields */
	if (optfields > 0)
	{ 
		ac = 0;
		(void)sprintf(bez, "%s%d", FRAMERADIOBOX, nr);
		framechange = XtCreateManagedWidget(bez, xmFrameWidgetClass, manager, 0, 0);

		ac = 0;
		(void)sprintf(bez, "%s%d", ROWCOLMOD, nr);
		XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
		XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
		rowcolmod = XtCreateManagedWidget( bez, xmRowColumnWidgetClass, framechange, arglist, ac);

		ac = 0;
		(void)sprintf(bez, "%s%d", TOGGLECHANGE, nr);
		xmStr = XmStringCreateSimple(LABEL_CHANGEMODE) ;
		XtSetArg(arglist[ac], XmNlabelString, xmStr ); ac++;
		XtSetArg(arglist[ac], XmNset, True); ac++;				/* default is optional */
		XtSetArg(arglist[ac], XmNvisibleWhenOff, True); ac++;
		XtSetArg(arglist[ac], XmNindicatorType, XmN_OF_MANY); ac++;
		optional = XmCreateToggleButton( rowcolmod, bez, arglist, ac);
		a->optional = optional; 
		XmStringFree( xmStr); 
		/*---- callback needs to know the form to toggle -----------------*/
		XtAddCallback( optional, XmNvalueChangedCallback, (XtCallbackProc)xUIchange_popup,
														              (XtPointer)optionalform);
		XtOverrideTranslations( optional, softkeytrans); 

		/*--- constraints -----*/
		ac = 0;
		XtSetArg(arglist[ac], XmNtopAttachment,    XmATTACH_FORM); ac++;
		XtSetArg(arglist[ac], XmNleftAttachment,   XmATTACH_WIDGET); ac++;
		XtSetArg(arglist[ac], XmNleftWidget,       frameradiobox); ac++;
		XtSetArg(arglist[ac], XmNrightAttachment,  XmATTACH_FORM); ac++;
		XtSetArg(arglist[ac], XmNbottomAttachment, XmATTACH_FORM); ac++;
		XtSetValues( framechange, arglist, ac);
		XtManageChild( optional);
	}
}
