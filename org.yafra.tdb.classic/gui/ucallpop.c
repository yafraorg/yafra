/*D***********************************************************
 * Modul:	GUI - Dialog                            ucallpop.c
 *				Make all ready and popup a MENU                          
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ucallpop.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

/*F--------------------------------------------------------------------------
 *  Function:	xUIcallpopup 
 *					handle NON special menus
 *					check if allowd, then prepare to popup a menu
 *					handle conflicts with other menus, update menu pointers
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIcallpopup(Widget w, XtPointer closure, XtPointer call_data)
{
	extern MENU    menu[];
	extern int     aktmenuz;
	extern int     aktmenu[];
	extern int     aktmenuobj[];
	extern int     holdfield;
	extern Boolean allmenuflag;
	extern unsigned char actiontoggle;
	extern Widget  bookingMask;
	extern OBJCOLORS	keycol;

	int		i, nr;
	MENU		*a;

	a = (MENU *)closure;

	/*---- check if already popuped -------*/
	if (a->openedmenu)
		return ;                                             /* >>>>>> return */

	/*--- Is menu allowed ? ---------------*/
	if (a->flags)
		{
		nr = a-menu;
		/*--- Must menu be created ? Output always new --------*/
		if (( !allmenuflag) || (a->typ == _OUTPUT))
	 		a->popup = xUIpopup(nr);

		/*--- first time, set main menu buttons insensitive ---*/
		xUIpulldownSensitive( False );
		xUIglobmenuSensitive( False );

		/*---- setze aktuelles MENU und MENU-Objekt -----------*/
		aktmenu[++aktmenuz] = nr;
		aktmenuobj[aktmenuz] = menu[nr].typ;

		/*--- Udate DB mode toggle ----------------------------*/
		if (a->typ == _OUTPUT)
		{
			actiontoggle = UPDATE ;                 /* No toggle, force DB mode */
			/*--- update mode has blue buttons ----*/
			for (i = 0; i<a->anz; i++)
				if (a->suchfields[i] == TRUE)
					xUIsetwidgetcolor( a->pushbutton[i], &keycol );
		}
		else
			xUItoggle(w, (XtPointer)actiontoggle, NULL);

		holdfield = -1;
		a->openedmenu = TRUE;
		XtPopup(a->popup, XtGrabNone);
		}
}
