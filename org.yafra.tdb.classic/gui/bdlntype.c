/*D************************************************************
 * Modul:		GUI - BM dialog		bdlntype.c
 *					create a service user menu (Dienstleistungsnehmer)
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bdlntype.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/
XtCallbackProc xBMdlnTypeSelect(Widget w, XtPointer toggleIndex, XtPointer wdata);


/*G------------------------ GLOBAL VARIABLES --------------------------------*/





/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeSize ()
 *					-at init allocate mem, later check if mem is sufficent 
 *					-
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int xBMdlnTypeSize (int nb, MENUAREA *anArea )
{
	/*--- call class radio methods ----*/
	xBMradioSize(nb, anArea, False);                  /* no initial select */  
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeCreate ()
 *					-create radio row column for dln-type
 *					-
 *  In:			-parent widget, an area, an Area to work    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMdlnTypeCreate (Widget parent, MENUAREA *anArea)
{
	/*--- call class radio methods ----*/
	xBMradioCreate ( parent, anArea, _BMDLNNR, True);  /* one sel only */
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeUpdate ()
 *					-create radio toggle buttons if not enough
 *					-update all labels
 *					-
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMdlnTypeUpdate (MENUAREA *anArea)
{
	/*---- use class methods  ----------------*/
	xBMradioUpdate (anArea, _BMDLNNR, xBMdlnTypeSelect ); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeReset ()
 *					-reset radio toggle buttons 
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMdlnTypeReset (MENUAREA *anArea)
{
	/*---- use class methods  ----------------*/
	xBMradioReset (anArea ); 
}




/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeSelect ()
 *					-set the selection of radio toggles  
 *					-
 *  In:			-Standard callback parameters, closure = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdlnTypeSelect(Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern MENUAREA typeArea; 
	int				state;
 
	/*----- get toggle state ----------*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;

	/*---- are state and my selection identical? ------*/
	if ((typeArea.select[(int)toggleIndex] == state) && (wdata != NULL))
		return;

	else if (wdata == NULL)
		/*---- undefined state, set one ----------------*/
		XtVaSetValues(w, XmNset, True, NULL);

	else
		/*---- update state in my selection ------------*/
		typeArea.select[(int)toggleIndex] = state ;
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnTypeDestroy ()
 *					-remove all constructed stuff of type area
 *  In:			-an area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnTypeDestroy (MENUAREA *anArea )
{
	/*---- free area stuff ---------------*/ 
	xBMradioDestroy( anArea );
}



