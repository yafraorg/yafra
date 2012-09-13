/*D************************************************************
 * Modul:       GUI - BM dialog                        bradio.c
 *
 *					Methods for class radio (one-of-many) selection
 *					Size, creation, update, destroy
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bradio.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/
	extern XtTranslations	softkeytrans;

/*P------------------------ PROTOTYPES --------------------------------------*/

/*G------------------------ GLOBAL VARIABLES --------------------------------*/




/*F--------------------------------------------------------------------------
 *  Function:	xBMradioSize ()
 *					-at allocate or re-alloc mem for a radio oneof selection
 *					-
 *  In:			-nb of items, area to work, flag to set a default
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int xBMradioSize (int nb, MENUAREA *anArea, Boolean oneFlag )
{
	int	i, nbItems ;

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

	/*---- reset previous selections, set first as default one ------ */
	if (oneFlag)
	{
		for (i=0; i< nbItems; i++ )
		{ 
			if (i==0)
				anArea->select[i] = 1;
			else	
				anArea->select[i] = 0;
		}
	}

	anArea->nbitems = nbItems;
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMradioCreate ()
 *					-create radio row column
 *					-
 *  In:			-parent widget, ressource numbering    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void	xBMradioCreate( Widget parent, MENUAREA *anArea, int nr, Boolean oneFlag)
{
	Widget		radiobox ;
	char			bez[_CHAR30+1] ;
	Arg			arglist[10];
	int			ac;

	/*---- inits -------*/
	(void)sprintf(bez, "%s%d", RADIOBOX, nr);
	ac = 0;
	XtSetArg(arglist[ac], XmNradioAlwaysOne, oneFlag ); ac++; 
	XtSetArg(arglist[ac], XmNpacking, XmPACK_COLUMN); ac++;
	XtSetArg(arglist[ac], XmNnumColumns, 1); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	radiobox = XmCreateRadioBox( parent, bez, arglist, ac);	
	anArea->Wglink = radiobox;			/*link for manage/unmanage if no items */
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMradioUpdate ()
 *					-create radio toggle buttons
 *					-
 *  In:			-area where to find values, ressource numbering, callback func     
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMradioUpdate (MENUAREA *anArea, int nr,
							XtCallbackProc (*cbFunc)(Widget, XtPointer, XtPointer))
{
	extern OBJCOLORS boardcol;		       /* Board matrix Colorset */

	Widget		radiobox ;
	char			bez[_CHAR30+1] ;
	Arg			arglist[10];
	int			ac;
	int			i,  state, nbItems, col ;
	XmString		xmStr; 	

	/*--- inits -----------------------------------*/
	radiobox = anArea->Wglink; 
	nbItems = anArea->nbitems;

	/*--- Presence test ---------------------------*/
	if (nbItems <= 0)
	{
		XtUnmanageChild(anArea->Wglink);
		return;                                        /* >>>>>> exit >> */
	} 
	else 
		XtManageChild(anArea->Wglink);

	/*--- Nb of columns/lines in radiobox ---------*/
	col = (nbItems / _DLN_COLUMNSIZE) +1 ; 
	ac = 0;
	XtSetArg(arglist[ac], XmNnumColumns, col); ac++;
	XtSetValues (radiobox, arglist, ac);	


	/*--- unmanage oldies -------------------------*/
	XtUnmanageChildren(anArea->Wgbuttons, anArea->olditems);
	/*--- enough existent widgets -----------------*/
	if ( anArea->olditems < nbItems)
	{
		for (i=anArea->olditems; i < nbItems; i++ )
		{
			/*--- create missing toggles ------------*/
			(void)sprintf(bez, "%s%d", RADIOTOGGLE, nr);
			anArea->Wgbuttons[i] = XmCreateToggleButton( radiobox, bez, arglist, ac);
			XtAddCallback(anArea->Wgbuttons[i], XmNvalueChangedCallback, 
													(XtCallbackProc)cbFunc, (XtPointer)i);
			XtOverrideTranslations( anArea->Wgbuttons[i], softkeytrans);  
		}
	}

	/*--- for all items, set new values  ----------*/
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

	/*--- run for new values  ---------------------*/
	XtManageChildren(anArea->Wgbuttons, nbItems);

	/*--- keep maximum of values ------------------*/
	if (anArea->olditems < nbItems )
	 	anArea->olditems = nbItems;
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMradioReset ()
 *					-reset all values in the area 
 *					-
 *  In:			-ptr to area     
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void	xBMradioReset( MENUAREA *anArea )
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
 *  Function:	xBMradioDestroy ()
 *					-remove all allocations for an Area class
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMradioDestroy ( MENUAREA *anArea )
{
	int		i; 

	/*--- free memory --------*/
	if (anArea) 
	{ 
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
}
