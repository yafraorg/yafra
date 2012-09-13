/*D***********************************************************
 * Modul:		GUI - Dialog                           uedit.c                         
 *                                                            
 *					Edit-field session functions (end, next, purge)                        
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uedit.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIeditend ()
 *					end an edition session on a menu field 
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIeditend( Widget w, XtPointer closure, XtPointer wdata)
{
	extern unsigned char	actiontoggle;
	extern MENU menu[];
	extern MENU glob;
	extern int  aktfield[];
	extern int  aktmenu[];
	extern int  aktmenuz;

	MENU		*a, *m;
	int		feld;
	int		type, akt;
	Boolean	alrwr;

	m = (MENU *)closure;
	akt = aktmenu[aktmenuz];
	a = &menu[akt];
	alrwr = a->alreadywrite;
	if (alrwr)
		{
		feld = aktfield[aktmenuz];
		type = a->buttontype[feld];

		/*--- in UPDATE/DELETE popdown the select if any ------*/
		if ((a->suchfields[feld] == TRUE) && (actiontoggle != INSERT))
			xUIselectpopdown( 0, 0, 0, 0);

		/*-- work depends on type --------*/
		switch (type)
			{
			case SEDITFIELD:
			case MEDITFIELD:
				xUIwritetoread( a->field[feld], 0, 0, 0);
				break;
			case ONEITEMFIELD:
				break;
			case SELECTFIELD:
			case SELNOFIELD:
				xUIselectpopdown( 0, 0, 0, 0);
				break;
			case TWINSELFIELD:
				xUICtwinButtonOk( 0, 0, 0);
				break;
			}
		}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIeditnext ()
 *					Get next editfield  
 *  In:			-a menu, int  
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIeditnext( MENU *a, int j)
{
	int   type, i;
	XtCallbackProc (*func)();
	Widget field;

	i = xUIfindhold(a, j);
	field = a->field[i];

	type = a->buttontype[i];
	switch (type) {
		case SEDITFIELD:
		case MEDITFIELD:
				func = xUIreadtowrite;
				break;
		case ONEITEMFIELD:
				func = xUIseltowrite;
				break;
		case SELECTFIELD:
		case SELNOFIELD:
		case TWINSELFIELD:
				func = xUIselpopup;
				break;
		default:
				func = xUIselpopup;
				break;
	}
	(*func)(a->pushbutton[j], (XtPointer)field, 0);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIeditpurge ()
 *					purge an edit field 
 *  In:			-std CB parameters 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIeditpurge( Widget w, XtPointer closure, XtPointer wdata)
{
	extern MENU menu[];
	extern MENU glob;
	extern int  aktfield[];
	extern int  aktmenuz;

	MENU *a;
	int   feld;

	a = (MENU *)closure;

	if (a == &glob)
		xUIbeep(w, 0, 0, 0);
	else
		{
		feld = aktfield[aktmenuz];
		if (a->alreadywrite)
			xUIfielddel(a->pushbutton[feld], 0, 0, 0);
		else
			xUIbeep(w, 0, 0, 0);
		}
}
