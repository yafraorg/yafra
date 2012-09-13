/*D************************************************************
 * Modul:		GUI - BM dialog		bnofmany.c
 *
 *					Methods for class n-of-many selection 
 *					default selection is the first
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bnofmany.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/
	extern XtTranslations	softkeytrans;

/*P------------------------ PROTOTYPES --------------------------------------*/

/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMnofmanySize ()
 *					-at init allocate mem, later check if mem is sufficent 
 *					-default selection is first one
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int xBMnofmanySize (int nb, MENUAREA *anArea )
{
	int	i, nbItems ;
	int	more;

	/*--- Limit by construction -----------------*/
	nbItems = nb;												 		/* no limit */ 
	/*--- check number of items -----------------*/
	if (anArea->nbitems < nbItems)
	{
		anArea->Wgbuttons = (Widget *)XtRealloc((char *)anArea->Wgbuttons, nbItems * sizeof(Widget));
		anArea->select = (int *)XtRealloc((char *)anArea->select, nbItems * sizeof(int));
		anArea->labels = (char **)XtRealloc((char *)anArea->labels, nbItems * sizeof(char *));
		for (i=anArea->nbitems; i< nbItems; i++ ) 
			anArea->labels[i] = (char *)XtMalloc(_LABELLEN+1);
	}
	anArea->nbitems = nbItems;
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMnofmanyCreate()
 *					-create reduction rowcolumn
 *					-
 *  In:			-the parent widget
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMnofmanyCreate (Widget parent, MENUAREA *anArea, int nr )
{
	Widget	rowcolmenu;
	char		bez[_CHAR30+1] ;
	Arg		arglist[10];
	int		ac;

	/*---- inits ----------------*/
	(void)sprintf(bez, "%s%d", ROWCOLMENU, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_COLUMN); ac++;
	XtSetArg(arglist[ac], XmNnumColumns, 1); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolmenu = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, parent, arglist, ac);
	anArea->Wglink = rowcolmenu; 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMnofmanyUpdate ()
 *					-create or add toggles, the CALLBACK is a parameter
 *					-
 *  In:			-anArea where to find values, the callback   
 *  					function attached with that area   
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMnofmanyUpdate (MENUAREA *anArea, int nr,
							XtCallbackProc (*cbFunc)(Widget, XtPointer, XtPointer))
{
	extern OBJCOLORS boardcol;		       /* Board matrix Colorset for ex */

	Widget		link;
	char			bez[_CHAR30+1] ;
	Arg			arglist[10];
	int			ac;
	int			i, nbItems, col ;
	XmString		xmStr; 	
	Boolean		state; 

	/*---- inits -------------------------------*/
	link = anArea->Wglink; 
	nbItems = anArea->nbitems; 	

	/*---- Presence test -----------------------*/
	if (nbItems <= 0)
	{
		XtUnmanageChild(anArea->Wglink);
		return;                            /* >>>>>>>exit>>>>>> */
	} 
	else 
		XtManageChild(anArea->Wglink);

	/*--- Nb of columns/lines in parent link ---*/
	col = (nbItems / _DLN_COLUMNSIZE) +1 ; 
	ac = 0;
	XtSetArg(arglist[ac], XmNnumColumns, col); ac++;
	XtSetValues (link, arglist, ac);	

	/*--- unmanage oldies ----------------------*/
	XtUnmanageChildren(anArea->Wgbuttons, anArea->olditems);
	/*--- enough existent widgets --------------*/
	if ( anArea->olditems < nbItems)
	{
		for (i=anArea->olditems; i < nbItems; i++ )
		{
			/*--- create missing toggles -----------*/
			(void)sprintf(bez, "%s%d", TOGGLECHANGE, nr);
			ac = 0;
			XtSetArg(arglist[ac], XmNvisibleWhenOff, True); ac++;
			XtSetArg(arglist[ac], XmNindicatorType, XmN_OF_MANY); ac++;
			anArea->Wgbuttons[i] = XmCreateToggleButton( link, bez, arglist, ac);
			XtAddCallback(anArea->Wgbuttons[i], XmNvalueChangedCallback,
										 (XtCallbackProc)cbFunc, (XtPointer)i);
			XtOverrideTranslations(anArea->Wgbuttons[i], softkeytrans);
		}
	}
	/*--- for all items, set new values  ------------------*/
	for (i= 0; i<nbItems; i++ )
	{
		ac = 0;
		xmStr = XmStringCreateSimple(anArea->labels[i]);
		XtSetArg(arglist[ac], XmNlabelString, xmStr); ac++;
		state = (anArea->select[i] == 1)? True : False ; 
		XtSetArg(arglist[ac], XmNset, state); ac++;
		XtSetArg(arglist[ac], XmNselectColor, boardcol.select ); ac++;
		XtSetValues (anArea->Wgbuttons[i], arglist, ac);	
		XmStringFree( xmStr);
	}
	/*--- run for new values  -----------------------------*/
	XtManageChildren(anArea->Wgbuttons, nbItems);

	/*--- keep maximum of values --------------------------*/
	if (anArea->olditems < nbItems )
	 	anArea->olditems = nbItems;
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMnofmanyReset ()
 *					-reset all values in the area 
 *					-
 *  In:			-ptr to area     
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void	xBMnofmanyReset( MENUAREA *anArea )
{
	Arg			arglist[10];
	int			ac, i;
	Boolean		state; 

	/*--- for all items, set new values  ----------*/
	for (i= 0;  i<anArea->nbitems ;  i++ )
	{
		ac = 0;
		anArea->select[i] = 0 ; 
		state =  False ; 
		XtSetArg(arglist[ac], XmNset, state); ac++;
		XtSetValues (anArea->Wgbuttons[i], arglist, ac);	
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMnofmanyDestroy ()
 *					-remove all constructed stuff of reduc areas
 *
 *  In:			-an area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMnofmanyDestroy (MENUAREA *anArea )
{
	int		i; 

	/*--- free memory --------*/
	XtFree((void *)anArea->Wgbuttons); 
	XtFree((void *)anArea->select);
	/*---- reset labels allocations ------ */
	for (i=0; i< anArea->nbitems; i++ )
	{ 
		XtFree((void *)anArea->labels[i]);
	}
	XtFree((void *)anArea->labels);		/*after pointed-to stuff is free */
	anArea->Wglink = 0; 
	anArea->nbitems = 0;
	anArea->olditems = 0;
}


