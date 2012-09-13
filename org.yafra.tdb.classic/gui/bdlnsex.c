/*D************************************************************
 * Modul:		GUI - BM dialog		bdlnsex.c
 *					create widgets used for DLN (Dienstleistungsnehmer)
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bdlnsex.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/
XtCallbackProc  xBMdlnSexSelect (Widget w, XtPointer closure, XtPointer call_data);

/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexSize ()
 *					-at init allocate mem, later check if mem is sufficent 
 *					-
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int xBMdlnSexSize (int nb, MENUAREA *anArea )
{
	/*--- Create with a default selected ----*/
	xBMradioSize( nb, anArea, False);                /* no initial select */
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexCreate ()
 *					-create radio row column
 *					-
 *  In:			-parent widget, area to work on    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMdlnSexCreate (Widget parent, MENUAREA *anArea)
{
	/*--- call class radio methods ----*/
	xBMradioCreate ( parent, anArea, _BMDLNNR, True);    /* one sel only */
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexUpdate ()
 *					-create radio toggle buttons, for all update labels
 *					-
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMdlnSexUpdate (MENUAREA *anArea)
{
	/*---- use class methods  ----------------*/
	xBMradioUpdate (anArea, _BMDLNNR, xBMdlnSexSelect ); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexReset ()
 *					-reset all selection in toggle buttons
 *					-
 *  In:			-area where to reset values    
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMdlnSexReset (MENUAREA *anArea)
{
	/*---- use class methods  ----------------*/
	xBMradioReset (anArea ); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexSelect ()
 *					-set the selection of radio toggles  
 *					-
 *  In:			-Standard callback parameters, closure = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdlnSexSelect(Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern MENUAREA sexArea; 
	int				state;
 
	/*----- get toggle state ----------*/
	state = ((XmToggleButtonCallbackStruct *)wdata)->set;

	/*---- are state and my selection identical? ------*/
	if ((sexArea.select[(int)toggleIndex] == state) && (wdata != NULL))
		return;

	else if (wdata == NULL)
		/*---- undefined state, set one ----------------*/
		XtVaSetValues(w, XmNset, True, NULL);

	else
		/*---- update state in my selection ------------*/
		sexArea.select[(int)toggleIndex] = state ;
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMdlnSexDestroy ()
 *					-remove all constructed stuff of radio areas
 *
 *  In:			-an area
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xBMdlnSexDestroy (MENUAREA *anArea )
{
	/*---- free area stuff ---------------*/ 
	xBMradioDestroy( anArea );
}



