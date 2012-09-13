/*D************************************************************
 * Modul:		GUI - BM dialog		bdlnredu.c
 *
 *					Reduction-Kommission creation for DLN
 *
 * Functions:	xBMdlnReduc1() 	xBMdlnReduc2()
 *
 * Callbacks:	xBMreduc1Select() xBMreduc2Select()
 *					each area must have its own callback, 
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bdlnredu.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/

/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReducSize ()
 *					-Allocate mem for a number of items 
 *					-
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int xBMdlnReducSize( int nb, MENUAREA *anArea )
{
	int	status; 

	/*---- create with no selection ---*/
	status = xBMnofmanySize ( nb, anArea );
	return (status); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReducCreate()
 *					-create reduction rowcolumn
 *					-
 *  In:			-the parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReducCreate( Widget parent, MENUAREA *anArea )
{
	/*---- inits ----------------*/
	xBMnofmanyCreate( parent, anArea, _BMDLNNR ); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc1Update ()
 *					-create reduction toggles for dln 
 *					-
 *  In:			-anArea where to find values   
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc1Update( MENUAREA *anArea)
{
	/*---- build widget with proper callback  ----------------*/
	xBMnofmanyUpdate ( anArea, _BMDLNNR, xBMdlnReduc1Select );
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc1Reset ()
 *					-reset the reduction toggles for dln 
 *					-
 *  In:			-anArea where to find values   
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc1Reset( MENUAREA *anArea)
{
	/*---- build widget with proper callback  ----------------*/
	xBMnofmanyReset ( anArea );
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc1Select ()
 *					-set the selection of radio toggles  
 *					-
 *  In:			-Standard callback parameters, closure = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdlnReduc1Select( Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern MENUAREA reduc1Area;
	int				state;
	MENUAREA			*pA ; 
 
	pA = &reduc1Area;
	/*----- get toggle state ----------*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;
	/*---- are state and my selection identical? ------*/
	if ((pA->select[(int)toggleIndex] == state) && (wdata != NULL))
		return;
	else if (wdata == NULL)
		/*---- undefined state, set one ----------------*/
		XtVaSetValues(w, XmNset, True, NULL);
	else
		/*---- update state in my selection ------------*/
		pA->select[(int)toggleIndex] = state ;
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc1Destroy ()
 *					-remove all constructed stuff of reduc1 area 
 *
 *  In:			-an area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc1Destroy( MENUAREA *anArea )
{
	/*---- reduc1 is of class area ---------------*/ 
	xBMnofmanyDestroy( anArea );
}



#ifdef ONE_REDUC

/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc2Update ()
 *					-create reduction toggles for dln 
 *					-
 *  In:			-anArea where to find values   
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc2Update( MENUAREA *anArea)
{
	/*---- build widget with proper callback  ----------------*/
	xBMradioUpdate ( anArea, _BMDLNNR, xBMdlnReduc2Select );
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc2Reset ()
 *					-reset the reduction toggles for dln 
 *					-
 *  In:			-anArea where to find values   
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc2Reset( MENUAREA *anArea)
{
	/*---- build widget with proper callback  ----------------*/
	xBMnofmanyReset ( anArea );
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc2Select ()
 *					-set the selection of radio toggles  
 *					-
 *  In:			-Standard callback parameters, closure = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdlnReduc2Select( Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern MENUAREA reduc2Area;
	int				state;
	MENUAREA			*pA ; 
 
	pA = &reduc2Area;
	/*----- get toggle state ----------*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;
	/*---- are state and my selection identical? ------*/
	if ((pA->select[(int)toggleIndex] == state) && (wdata != NULL))
		return;
	else if (wdata == NULL)
		/*---- undefined state, set one ----------------*/
		XtVaSetValues(w, XmNset, True, NULL);
	else
		/*---- update state in my selection ------------*/
		pA->select[(int)toggleIndex] = state ;
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnReduc2Destroy ()
 *					-remove all constructed stuff of reduc2 area 
 *
 *  In:			-an area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnReduc2Destroy( MENUAREA *anArea )
{
	/*---- reduc2 is of class area ---------------*/ 
	xBMradioDestroy( anArea );
}

#endif
