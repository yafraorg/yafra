/*D************************************************************
 * Modul:		GUI - BM dialog		bcatextr.c
 *					Handle extra beds toggles
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/bcatextr.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: bcatextr.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:01:54  ja
 general version

 * Revision 1.4  94/02/18  10:34:30  10:34:30  ja (Jean-Marc Adam)
 * Name conversion to DOS
 * 
 * Revision 1.3  93/05/11  09:36:48  09:36:48  ja (Jean-Marc Adam)
 * "Default settings for radiotoggles"
 * 
 * Revision 1.2  93/05/04  18:02:13  18:02:13  ja ()
 * "rev"
 * 
 * Revision 1.1  93/03/22  16:06:50  16:06:50  ja ()
 * Initial revision
 * 
 * 
*/

#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bcatextr.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


/*E------------------------ EXTERNALS ---------------------------------------*/

/*P------------------------ PROTOTYPES --------------------------------------*/
XtCallbackProc  xBMcatExtraSelect (Widget w, XtPointer closure, XtPointer call_data);

/*G------------------------ GLOBAL VARIABLES --------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatExtraSize ()
 *					-at parsing, alloc or re-alloc memory  
 *					-
 *  In:			-nb of items as parsed from DB buffer, area to work on 
 *  out:			-
 *  Return:		- status
 *---------------------------------------------------------------------------
 */
int xBMcatExtraSize (int nb, MENUAREA *anArea )
{
	/*--- call Radio class methods ----*/
	xBMradioSize(nb, anArea, True);  
	return (_OK); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatExtraCreate ()
 *					-create radio row column
 *					-
 *  In:			-parent widget    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMcatExtraCreate (Widget parent, MENUAREA *anArea )
{
	/*--- call class radio methods ----*/
	xBMradioCreate ( parent, anArea, _BMCATNR, True);
}


/*F--------------------------------------------------------------------------
 *  Function:	xBMcatExtraUpdate ()
 *					-create extra beds radio toggle buttons
 *					-
 *  In:			-area where to find values    
 *  out:			-
 *  Return:		-a widget 
 *---------------------------------------------------------------------------
 */
void xBMcatExtraUpdate (MENUAREA *anArea)
{
	/*---- use class methods  ----------------*/
	xBMradioUpdate (anArea, _BMCATNR, xBMcatExtraSelect ); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xBMcatExtraSelect ()
 *					-set the selection of radio toggles  
 *					-
 *  In:			-Standard callback parameters, closure = value
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMcatExtraSelect(Widget w, XtPointer toggleIndex, XtPointer wdata)
{
	extern MENUAREA extraArea; 
	int			state;
	MENUAREA		*pA;
	
	pA = &extraArea ; 
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
 *  Function:	xBMcatExtraDestroy ()
 *					-remove all allocations for an Area
 *					-
 *  In:			-area to delete
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xBMcatExtraDestroy ( MENUAREA *anArea )
{
	/*---- free area stuff ---------------*/ 
	xBMradioDestroy( anArea );
}




