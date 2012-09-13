/*D***********************************************************
 * Modul:     GUI - dialog					unewlevl.c                                   
 *                                                            
 *            Start a menu to enter base data                 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/unewlevl.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



/*F---------------------------------------------------------------------
 *	Function:	xUIselnewmenu 
 *					-Mouse button 2 has been pressed, open a new level
 *					-
 *	In:			-std XtActionProc params
 *					-
 *-----------------------------------------------------------------------
 */
XtActionProc xUIselnewmenu( Widget w, XEvent* event, String* s, Cardinal* m)
{
	xUInewlevel( w, 0 ,0 ); 
}




/*F---------------------------------------------------------------------
 *	Function:	xUInewlevel 
 *					-a new menu has to be opened
 *					-
 *	In:			-std callback params
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUInewlevel( Widget w, XtPointer client_data, XtPointer call_data)
{
	extern int	*NewLevel[];
	extern MENU menu[];
	extern MENU glob;
	extern int			aktmenuz;
	extern int			aktmenu[];
	extern int			aktmenuobj[];
	extern int			aktfield[];
	extern int			globfield;
	extern int        zufield[];
	extern Widget     selectpopup;
	extern unsigned char actiontoggle;

	MENU		*a;
	int		i, f;
	unsigned char NewMenu, OldMenu;


	/*--- Check if possible -----------------------*/
	if (globfield != -1)
	{
		xUIbeep(glob.field[globfield], 0, 0, 0);
		return;
	}
	else
	{
		a = &menu[aktmenu[aktmenuz]];
		f = aktfield[aktmenuz];
		if (a->buttontype[f] != SELECTFIELD && a->buttontype[f] != INPNEWLEVEL)
		{
			xUIselectpopdown(a->pushbutton[f], 0, 0, 0);
			xUIbeep(a->pushbutton[f], 0, 0, 0);           
			return;
		}
	}

	/*--- look for new MENUNR -------------------*/
	NewMenu = NewLevel[a->typ][f];
	MENUNR = NewMenu;
	FELDNR = NOFIELD;
	/*--- find new menu -------------------------*/
	for (i=0; i < ANZ_MENU; i++)
		if (menu[i].typ == (int)MENUNR)
			break;

	/*--- menu allowed and not already opened ---*/
	if (!menu[i].flags || menu[i].openedmenu)
	{
		/*--- menu will not be opened ---*/
		xUIselectpopdown( a->pushbutton[f], 0, 0, 0);
		xUIbeep( a->pushbutton[f], 0, 0, 0);
	}
	else
	{
		/*--- close select and disable edit in old menu ---*/
		XtPopdown( selectpopup);
		xUImenufeld( a, 0, FALSE, FALSE, FALSE, FALSE);

		/*--- Call new menu --------*/
		xUIcallpopup( a->popup, (XtPointer)&menu[i], 0);		/* aktmenuz++ */
		zufield[aktmenuz] = f;
	}
}
