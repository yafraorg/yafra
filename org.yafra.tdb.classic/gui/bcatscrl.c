/*D************************************************************
 * Modul:		GUI - BM dialog		bcatscrl.c
 *
 *					Create header label for categories 
 *					Create scrollable window with categories 
 *					Init routines
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bcatscrl.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/

/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*M------------------------ MACROS ------------------------------------------*/
/* macros converting string values to form required by widgets */
#define	MA_RES_CONVERT( res_name, res_value) \
	XtVaTypedArg, (res_name), XmRString, (res_value), strlen(res_value) + 1

#define	MA_SET_RES_VALUE( wgt, res_name, res_value ) \
	XtVaSetValues( wgt, MA_RES_CONVERT( res_name, res_value ), NULL )



/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerSize ()
 *					-at init allocate mem, later check if mem is sufficent 
 *					-
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int xBMscrollerSize (int nb, SCROLLAREA *anArea )
{
	int	i, nbItems ;

	/*--- inits -----------------*/
	nbItems = nb;												 		/* no limit */ 
	/*--- check existant max number of items -----------------*/
	if (anArea->olditems < nbItems)
	{
		anArea->Wgbuttons = (Widget *)XtRealloc((char *)anArea->Wgbuttons, nbItems * sizeof(Widget));
		anArea->select = (int *)XtRealloc((char *)anArea->select, nbItems * sizeof(int));

		anArea->labels = (char **)XtRealloc((char *)anArea->labels, nbItems * sizeof(char *));
		for (i=anArea->nbitems; i< nbItems; i++ ) 
			anArea->labels[i] = (char *)XtMalloc(_BMLABELLEN+1);

		anArea->colors = (char **)XtRealloc((char *)anArea->colors, nbItems * sizeof(char *));
		for (i=anArea->nbitems; i< nbItems; i++ ) 
			anArea->colors[i] = (char *)XtMalloc(_LABELLEN+1);

		anArea->catid = (char **)XtRealloc((char *)anArea->catid, nbItems * sizeof(char *));
		for (i=anArea->nbitems; i< nbItems; i++ ) 
			anArea->catid[i] = (char *)XtMalloc(_LABELLEN+1);
	}

	anArea->nbitems = nbItems;
	return (_OK); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerCreate
 *					-create row/col for header and scrolled window
 *					-scrolled row/col will be parent Wglink for futur operations
 *					-label header is copied from labeltable as default string
 *  In:			-parent widget, an area    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMscrollerCreate (Widget parent, SCROLLAREA *anArea, Boolean headerFlag)
{
	extern XtTranslations	softkeytrans;

	Widget		rowcolmenu;
	Widget		rowcolbutton ;
	Widget		scrollwin;
	char			bez[_CHAR30+1] ;
	Arg			arglist[10];
	int			ac;
	int			i, nr, nbItems;
	XmString		xmStr; 	

	/*---- inits ----------------*/
	nr = _BMCATNR ; 

	/*---- create row/column ------------------------------------------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmVERTICAL); ac++;
	rowcolmenu = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, parent, arglist, ac);
	anArea->Wgarea = rowcolmenu;

	/*--- Header label widget ----*/
	anArea->headlabel = (char *)XtMalloc(_BMLABELLEN+1);
	strcpy (anArea->headlabel, _SCROLL_HEADER); 
	(void)sprintf(bez, "%s%d", LABEL, nr);
	ac = 0;
	xmStr = XmStringCreateLtoR( anArea->headlabel, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
	anArea->Wghead = XmCreateLabel(rowcolmenu, bez, arglist, ac);
	XmStringFree(xmStr); 
	/*--- display if whished ----*/
	if (headerFlag)
	{
	 	XtManageChild(anArea->Wghead); 
	}

	/*--- create scrolled window ---------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", SCROLLEDWINDOW, nr);
	XtSetArg(arglist[ac], XmNscrollingPolicy, XmAUTOMATIC); ac++;	
	scrollwin = XtCreateManagedWidget(bez, xmScrolledWindowWidgetClass, rowcolmenu, arglist, ac);
	anArea->Wgscroll = scrollwin;

	/*---- create row/column in scroll, manage later ---------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT);		ac++;
	XtSetArg(arglist[ac], XmNorientation, XmVERTICAL);		ac++;
	XtSetArg(arglist[ac], XmNspacing, _SCROLL_SPACE);	ac++;	
	XtSetArg(arglist[ac], XmNrowColumnType, XmWORK_AREA); ac++;
	rowcolbutton = XtCreateWidget(bez, xmRowColumnWidgetClass, scrollwin, arglist, ac);
	anArea->Wglink = rowcolbutton;
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerUpdate ()
 *					-update scroll buttons
 *					-
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMscrollerUpdate( SCROLLAREA *anArea)
{
	extern XtTranslations	softkeytrans;

	char			bez[_CHAR30+1] ;
	Arg			arglist[10];
	int			ac;
	int			i, nr, nbItems, nbVisibleItems ;
	Dimension	b, h, scrollHeight; 
	XmString		xmStr; 	
	AREACALLBACK	*pAreaCb;

	/*---- inits ----------------*/
	nr = _BMDLNNR ; 
	nbItems = anArea->nbitems;

	if (nbItems <=0)  {
		XtUnmanageChild(anArea->Wgarea);
/*		anArea->olditems = nbItems;  */
		return;                            /* >>>>>>>exit>>>>>> */
	} 
	else 
		XtManageChild(anArea->Wgarea);

	/*--- update header label ------------------------------------------------*/
	xmStr = XmStringCreateLtoR( anArea->headlabel, XmSTRING_DEFAULT_CHARSET);
	XtVaSetValues(anArea->Wghead, XmNlabelString, xmStr, NULL);
	XmStringFree(xmStr); 

	/*--- unmanage oldies ----------------------------------------------------*/
	XtUnmanageChildren(anArea->Wgbuttons, anArea->olditems);
	(void)sprintf(bez, "%s%d", SCROLLEDBUTTON, nr);

	/*--- enough existent widgets? -------------*/
	if ( anArea->olditems < nbItems)
	{
		for (i=anArea->olditems; i < nbItems; i++ )			/* from old up to new */
		{
			/*--- Create Pushbutton ---*/
			anArea->Wgbuttons[i] = XtCreateWidget( bez, xmPushButtonWidgetClass,
																		anArea->Wglink, 0, 0 );
			XtOverrideTranslations( anArea->Wgbuttons[i], softkeytrans);
			/*--- Store CB struct -----*/
			pAreaCb = (AREACALLBACK *)XtMalloc(sizeof(AREACALLBACK));
			pAreaCb->index = i;
			pAreaCb->pArea = anArea;
			XtAddCallback( anArea->Wgbuttons[i], XmNactivateCallback,
		             	 (XtCallbackProc)xBMscrollerSelect, (XtPointer)pAreaCb );
		}
	}
	/*----- update labels and color of ALL buttons --------------*/
	for (i=0;  i < nbItems;  i++ )
	{
		MA_SET_RES_VALUE( anArea->Wgbuttons[i], XmNlabelString, anArea->labels[i] );
		MA_SET_RES_VALUE( anArea->Wgbuttons[i], XmNbackground,  anArea->colors[i] ); 
		xUIsetBestForeground ( anArea->Wgbuttons[i]);
		if (anArea->select[i] == 1)
			xUIsetSelectColor(anArea->Wgbuttons[i]);		
	}
	/*--- adjust scrolled window size to nb items ----------------*/
	if (anArea->Wgbuttons[0])
		XtVaGetValues(anArea->Wgbuttons[0], XmNheight, &h, NULL);
	nbVisibleItems = (anArea->nbitems > _SCROLL_NBVISIBLE)? _SCROLL_NBVISIBLE: anArea->nbitems;
	scrollHeight = (nbVisibleItems+1) * (h + _SCROLL_SPACE) ;
	XtVaSetValues(anArea->Wgscroll, XmNheight, scrollHeight, NULL);

	/*--- keep maximum of values ---------------------------------*/
	if (anArea->olditems < nbItems )
	 	anArea->olditems = nbItems;

	/*--- Manage when all buttons present ------------------------*/
	XtManageChildren(anArea->Wgbuttons, nbItems);
	XtManageChild(anArea->Wglink);
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerSelect ()
 *					-set the selection of radio-behaviored scroll buttons  
 *					-
 *  In:			-Standard callback parameters, closure = index
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMscrollerSelect(Widget w, XtPointer pAreaCb, XtPointer wdata)
{
	extern SCROLLAREA scrollArea; 

	int				i, k, state, ix ;
	SCROLLAREA			*anArea;

	/*--- inits  ------------*/
	anArea = ((AREACALLBACK *)pAreaCb)->pArea ; 
	ix     = ((AREACALLBACK *)pAreaCb)->index;

	/*--- get toggle state --*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;	

	/*--- find old index --------------*/
	k = -1 ;												/* default if nothing set */ 
	for (i= 0; i< anArea->nbitems; i++ )
	{
		if (anArea->select[i] == 1)
		{
			k = i;
			break;										/* break loop to keep index */
		} 
	}
	
	/*---- What to do -----------------------------------*/
	if ( ix == k ) 
	{
		/*---- twice press, reset for unselect ---*/
		anArea->select[k] = 0 ;
		xUIsetUnselectColor(anArea->Wgbuttons[k]);		
	}
	else if (k == -1)
	{
		/*---- nothing set, set one --------------*/
		anArea->select[ix] = 1 ;
		xUIsetSelectColor(anArea->Wgbuttons[ix]);		
	}
	else
	{
		/*--- reset OLD state and color ----------*/
		anArea->select[k] = 0 ;
		xUIsetUnselectColor(anArea->Wgbuttons[k]);		

		/*--- update state in current selection --*/
		scrollArea.select[ix] = 1 ;
		xUIsetSelectColor(anArea->Wgbuttons[ix]);		
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerReset ()
 *					-reset the selection of radio-behaviored scroll buttons  
 *					-
 *  In:			-a scroll area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMscrollerReset( SCROLLAREA *anArea)
{
	int				i, k, state, ix ;

	/*--- find old index --------------*/
	k = -1 ;												/* default if nothing set */ 
	for (i= 0; i< anArea->nbitems; i++ )
	{
		if (anArea->select[i] == 1)
		{
			k = i;
			break;										/* break loop to keep index */
		} 
	}

	/*--- reset for unselect ---*/
	if (k != -1 )
	{
		anArea->select[k] = 0 ;
		xUIsetUnselectColor(anArea->Wgbuttons[k]);
	}		
}





/*F--------------------------------------------------------------------------
 *  Function:	xBMscrollerDestroy ()
 *					-remove all allocations for a scrolled Area
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMscrollerDestroy ( SCROLLAREA *anArea )
{
	int		i; 

	/*--- free memory --------*/
	XtFree((void *)anArea->Wgbuttons); 
	XtFree((void *)anArea->select);
	XtFree((void *)anArea->headlabel);
	/*---- reset labels allocations ------ */
	for (i=0; i< anArea->nbitems; i++ )
	{ 
		XtFree((void *)anArea->catid[i]);
		XtFree((void *)anArea->labels[i]);
	}
	XtFree((void *)anArea->catid);
	XtFree((void *)anArea->labels);
	anArea->Wgscroll = 0;
	anArea->Wglink = 0;
	anArea->nbitems = 0;
	anArea->olditems = 0;
}


