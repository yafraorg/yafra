/*D**********************************************************
 * Modul:     GUI - dialog				utoggle.c              
 *                                                           
 *            Toggle between the DB modes types:             
 *            INSERT, UPDATE, DELETE                         
 *                                                           
 *                                                           
 * Copyright: yafra.org, Basel, Switzerland    
 ************************************************************/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/utoggle.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


/*---------------------- PROTOTYPES -------------------------------------*/
void xUItoggleButtonColor( MENU *a );
void xUItoggleRadioPosition( MENU *a );




XtCallbackProc xUItoggle(Widget w, XtPointer whichtoggle, XtPointer wdata)
{
	extern MENU  menu[];
	extern int   aktmenu[];
	extern int   aktmenuz;
	extern int   holdfield;
	extern unsigned char actiontoggle;
	extern OBJCOLORS orgcol, keycol;

	MENU          *a;
	int				akt;
	register int  i, j;
	Arg	        arglist[6];
	Position      ypos;
	Dimension     marginheight, marginwidth;
	short         space;
	XmToggleButtonCallbackStruct *state = (XmToggleButtonCallbackStruct *)wdata;

	static MENU  *lastmenu = 0;

	a = &menu[aktmenu[aktmenuz]];

	holdfield = -1;
	if ((actiontoggle == (unsigned char)whichtoggle) && (wdata != NULL))
		return;
	else if (wdata == NULL)
	{
		actiontoggle = (unsigned char)whichtoggle;
		/*--- change menu look toggles ------*/
		xUItoggleRadioPosition( a );
	}
	else
		actiontoggle = (unsigned char)whichtoggle;

	/*--- Color update ---------------------------------*/
	xUItoggleButtonColor( a );

	/*--- Update other menus if popped-up ---------------------*/
	for (i=0; i < aktmenuz; i++) 
	{
		akt = aktmenu[i];
		a = &menu[akt];
		xUItoggleButtonColor( a );
		xUItoggleRadioPosition( a );
	}

}




/*F--------------------------------------------------------------------------
 *  Function:	xUItoggleButtonColor ()
 *					after a toggle change update/modify-delete change color
 *
 *  In:			-menu 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUItoggleButtonColor( MENU *a )
{
	extern unsigned char actiontoggle;
	extern OBJCOLORS orgcol, keycol;

	int	  i;

	/*--- Color update ---------------------------------*/
	switch (actiontoggle)
		{
		case INSERT:
			for (i = 0; i<a->anz; i++)
				if (a->suchfields[i] == TRUE)
					xUIsetwidgetcolor( a->pushbutton[i], &orgcol );
			break;
		case UPDATE:
		case MPDELETE:
			for (i = 0; i<a->anz; i++)
				if (a->suchfields[i] == TRUE)
					xUIsetwidgetcolor( a->pushbutton[i], &keycol );
			break;
		}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUItoggleRadioPosition ()
 *					after a toggle change toggle radio button position
 *
 *  In:			-menu 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUItoggleRadioPosition( MENU *a )
{
	extern unsigned char actiontoggle;

	/*--- Color update ---------------------------------*/
	switch (actiontoggle)
		{
		case INSERT:
			XtVaSetValues(a->toggleinsert, XmNset, True,  NULL);
			XtVaSetValues(a->toggleupdate, XmNset, False, NULL);
			XtVaSetValues(a->toggledelete, XmNset, False, NULL);
			break;
		case UPDATE:
			XtVaSetValues(a->toggleinsert, XmNset, False, NULL);
			XtVaSetValues(a->toggleupdate, XmNset, True,  NULL);
			XtVaSetValues(a->toggledelete, XmNset, False, NULL);
			break;
		case MPDELETE:
			XtVaSetValues(a->toggleinsert, XmNset, False, NULL);
			XtVaSetValues(a->toggleupdate, XmNset, False, NULL);
			XtVaSetValues(a->toggledelete, XmNset, True,  NULL);
			break;
		}
}

