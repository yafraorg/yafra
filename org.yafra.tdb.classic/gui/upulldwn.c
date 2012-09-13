/*D************************************************************
 * Modul:     GUI - dialog                          upulldwn.c
 *            Create a pulldown menu system
 *            Handle pulldown sensitivity
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/upulldwn.c,v 1.3 2008-11-23 15:44:39 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIpulldown()
 *					-create a pulldown menu recursively
 *  In:			-parameters to create a pulldown
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget *xUIpulldown( char *title, Widget menubar, MENULIST *menulist, int nitems)
{
	extern MENU menu[];

	Arg		wargs[5];
	int		i, nr;
	Widget	*buttons;
	int		separators=0;
	MENULIST	*pML;						/* direct access to a menulist item */
	XmString		xmStr;


	buttons = (Widget *)XtMalloc(nitems * sizeof(Widget));

	if (title) {
		XtCreateManagedWidget(title, xmLabelWidgetClass, menubar, 0, 0);
		XtCreateManagedWidget(SEPAR, xmSeparatorWidgetClass, menubar, 0, 0);
	}

	/*-- build for as many basic pulldown items ----*/
	for (i=0; i<nitems; i++)
		{
		pML = &menulist[i];
		xmStr = XmStringCreateLtoR(menulist[i].titel, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(wargs[0], XmNlabelString, xmStr );
		XtSetArg(wargs[1], XmNancestorSensitive, menulist[i].status);
		XtSetArg(wargs[2], XmNmnemonic, menulist[i].mnemonic);

		if (!menulist[i].titel)
			{
			/*-- no titel means create a separator ------------------*/
			XtCreateManagedWidget(SEPAR, xmSeparatorWidgetClass, menubar, 0, 0);
			separators++;
			XmStringFree( xmStr);
			}
		else if (menulist[i].func)
			{
			/*-- create normal pushbutton or option/help cascade-button --------*/
			if (menulist[i].anz_subitems == 0)
				{
				/*-- case of option or help ----*/
				buttons[i-separators] = XtCreateWidget( PULLDOWN,
                                    xmCascadeButtonWidgetClass, menubar, wargs, 3);
				}
			else
				{
				buttons[i-separators] = XtCreateWidget( PULLDOWN,
                                    xmPushButtonWidgetClass,    menubar, wargs, 3);
				}
			/*--- last item is help ----*/
			if (i+1==nitems)
				{
				XtSetArg(wargs[0], XmNmenuHelpWidget, buttons[i-separators]);
				XtSetValues(menubar, wargs, 1);
				}
			XtAddCallback(buttons[i-separators], XmNactivateCallback,
							 (XtCallbackProc)menulist[i].func, (XtPointer)menulist[i].data);
			XmStringFree( xmStr);

			/*--- fill menu member "button" with created widget ---------*/
			if (menulist[i].menu == True)    /* grouplist menu */
				{
				nr = (MENU *)menulist[i].data - menu;
				menu[nr].button = buttons[i-separators];
				}
			}
		else if (!menulist[i].submenu)
			{
			/*-- no submenu  then create label leaf -------------*/
			buttons[i-separators] = XtCreateWidget( PULLDOWN,
                                        xmLabelWidgetClass, menubar, wargs, 3);
			XmStringFree( xmStr);
			}
		else
			{
			Widget submenu;
			char tmptit[] = "Submenu";
			menulist[i].submenutitle = tmptit;
			submenu = XmCreatePulldownMenu(menubar, menulist[i].submenutitle, 0, 0);
			XtSetArg(wargs[3], XmNsubMenuId, submenu);
			buttons[i-separators] = XtCreateWidget( PULLDOWN, xmCascadeButtonWidgetClass,
																menubar, wargs, 4);
			/*--- last item is help cascade button ----*/
			if (i+1==nitems)
				{
				XtSetArg(wargs[0], XmNmenuHelpWidget, buttons[i-separators]);
				XtSetValues(menubar, wargs, 1);
				}
			XmStringFree( xmStr);
			/*-- recursion call -----*/
			menulist[i].button = xUIpulldown(NULL, submenu,
														menulist[i].submenu, menulist[i].anz_subitems);
			}
		}/*for*/

	XtManageChildren(buttons, nitems-separators);
	return(buttons);
}



#ifdef COMPILE
/*F--------------------------------------------------------------------------
 *  Function:	xUIpulldownSensitive()
 *					-set sensitivity to enable pulldown menu
 *					-Menus with no enable flag don't need to be insensitivated
 *  In:			-sensitivity flag
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIpulldownSensitive( Boolean sensitivity )
{
	extern MENU    menu[];
	extern int     aktmenuz;
	extern int     aktmenu[];
	extern int     aktmenuobj[];

	int		i;
	MENU		*a;

	/*--- first time, set main menu buttons insensitive ---*/
	if (aktmenuz == -1)
	{
		for (i=0; i<ANZ_MENU; i++)
		{
			a = &menu[i];
			if (a->flags)											/*already insensitive*/
				XtSetSensitive(a->button, sensitivity);
		}
	}
}
#endif



/*F--------------------------------------------------------------------------
 *  Function:	xUIpulldownSensitive()
 *					-set sensitivity to enable pulldown menu BUT option menus
 *					-Special menus are not insensitivated
 *  In:			-sensitivity flag
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIpulldownSensitive( Boolean sensitivity )
{
	extern MENU    menu[];
	extern int     aktmenuz;
	extern int     aktmenu[];
	extern int     aktmenuobj[];

	int		i, g;
	MENU		*a;

	/*--- first time, set main menu buttons insensitive ---*/
	if (aktmenuz == -1)
	{
		for (i=0; i<ANZ_MENU; i++)
		{
			a = &menu[i];
			g = a->zuogruppe;
			/*--- exclusions --------------------*/
			if ( a->flags == False)                          /* not allowed menus  */
				continue;
			if ((g == 0) && (a->typ != _OUTPUT))             /* group 0 but output */
				continue;
			if (g == ANZGROUPS)                              /* group help         */
				continue;
			/*--- set or unset sensitivity ------*/
			XtSetSensitive(a->button, sensitivity);
		}
	}
}




