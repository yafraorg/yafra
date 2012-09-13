/**************************************************************
 * Modul:     GUI - user interface              usoftkey.c                           
 *                                                            
 *            check the Softkey action buttons 
 *            (normal and BM menus)  
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/usoftkey.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


/*F---------------------------------------------------------------------
 *	Function:	xUIsoftkey 
 *					-find pressed key and execute corresponding function
 *					-
 *	In:			-std action procedure param
 *					-
 *-----------------------------------------------------------------------
 */
XtActionProc xUIsoftkey( Widget w, XEvent* event, String* s, Cardinal* n)
{
	extern Display *display;
	extern int   aktmenuz;
	extern int   aktmenu[];
	extern MENU			menu[];
	extern BOOKMENU	bm_menu[];
	extern Widget	toplevel;
	extern Boolean	openedoption;				/* option menu (Einstellungen)  */
	extern Widget	WoptionButtonQuit;		/* option button quit           */ 
	extern Widget	WoptionButtonHelp;		/* option button Help           */ 

	Widget		wid[7+ANZ_MENU], button;
	Window		topwin, *win;
	int			j, anzwidgets, found, f, anzchildren, anz;
	int			i;
	KeySym		keysym;
	MENU			*a;
	BOOKMENU		*b;
	XtCallbackProc (*func)();
	XtPointer	para;
	Boolean		ok;


	/*--- inits -----*/
	f = -1;
	button = 0; 
	keysym = XKeycodeToKeysym(display, event->xkey.keycode, 0);
	switch(keysym)
		{
		case XK_F1: f=1; break;
		case XK_Return: f=2; break;
		case XK_F2: f=2; break;
		case XK_F3: f=3; break;
		case XK_F4: f=4; break;
		case XK_F5: f=5; break;
		case XK_F6: f=6; break;
		case XK_F7: f=7; break;
		case XK_F8: f=8; break;
		}

	if (f < 0)
		{
		xUIbeep(toplevel, 0, 0, 0);
		return;
		}
	found = -1;
	anzwidgets = xUIwidgets(wid);
	for (j=0; j<anzwidgets; j++)
		{
		topwin = XtWindow(wid[j]);
		anzchildren = 0;
		anz = 0;
		if (topwin)
			{
			xUIwindows(topwin, &anz, win, 100, FALSE, &ok);
			win = (Window *)XtMalloc(anz * sizeof(Window));
			if (win)
				{
				xUIwindows(topwin, &anzchildren, win, anz, TRUE, &ok);
				for (i=0; i<anzchildren; i++) {
					if (event->xany.window == win[i]) found=j;
					}
				XFree((void *)win);
				}
			}
		}

	if (found < 0)
		{
		xUIbeep(toplevel, 0, 0, 0);
		return;
		}

	/*------ check norm menus --------*/
	a = NULL;
	for (i=0; i<ANZ_MENU; i++)
		{
		if (wid[found] == menu[i].popup)
			a = &menu[i];
		}
	/*------ check BM menus ----------*/
	b = NULL;
	for (i=0; i<ANZ_BMMENU; i++)
		{
		if (wid[found] == bm_menu[i].Wgpopup)
			b = &bm_menu[i];
		}

	if (openedoption) 
		para = (XtPointer)0;     /* Option menu is open */
	else if (b)
		para = (XtPointer)b;     /* check first b, 2 booking menus are allowed */
	else if (a)
		para = (XtPointer)a;
	else
		{
		xUIbeep(toplevel, 0, 0, 0);                   /* no widget >>>>exit */
		return;
		}

	switch (f)
		{
		case 1:
			if (a) 
				button = a->buttonhelp;
			else if (b)
				button = b->Wgbuttonhelp;
			else 
				button = 0;
			if (event->xkey.state > 0)      /* shift     */
				if (a)
					func = a->help;
				else if (b)
					func = b->help;
				else 
					func = xUIhelp;           /* will operate if a menu is defined */
			else                            /* normal F1 */
				func = xUIinfo;
			break;

		case 2:
			if (a) {
				button = a->buttonnext;
				func = xUIfieldnext;
				}
			if (b) {
				button = b->Wgbuttonhelp;    /* simulate button next, nothing Help */
				func = xBMfieldnext;
				}
			break;

		case 3:
			if (a) {
				button = a->buttonlast;
				func = xUIfieldlast;
				}
			break;

		case 4:
			if (a) {
				button = a->buttondel;
				func = xUIeditpurge;
				}
			break;

		case 5:
			if (a) {
				button = a->buttonend;
				func = xUIeditend;
				}
			break;

		case 6:
			if (a) {
				button = a->buttonact;
				func = a->action;
				}
			else {
				button = b->Wgbuttonact;
				func = b->action;
				}
			break;

		case 7:
			if (a) {
				button = a->buttonmenu;
				func = xUIfieldDeleteAll;
				}
			else {
				button = b->Wgbuttonmenu;
				func = xBMfieldDeleteAll;
				}
			break;

		case 8:
			if (openedoption) {                  /* option menu */
				button = WoptionButtonQuit;
				func = xUIoptionPopdown;
				}
			else if (a) {
				button = a->buttonquit;
				func = xUIpopdown;
				}
			else {
				button = b->Wgbuttonquit;
				func = xBMpopdown;
				}
			break;
		}

	/*--- Execute -----------------*/
	if ((XtIsSensitive(button)) && (button != 0))
		(*func)(button, para, 0);
	else
		xUIbeep(toplevel, 0, 0, 0);
	return;
}
