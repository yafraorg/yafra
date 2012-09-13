/*D***********************************************************
 * Modul:	GUI - dialog			umenus.c
 * 	                                       
 *				Menu general handling functions: activation and popdown
 * 	                                       
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */


#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umenus.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xUImenuActive ()
 *					-return current ui active menu
 *  In:			-
 *  out:			-
 *  Return:		-a ptr to menu
 *---------------------------------------------------------------------------
 */
MENU * xUImenuActive()
{
	extern MENU       menu[];
	extern int        aktmenuz;
	extern int        aktmenu[];

	int		nr;
	MENU		*a;

	/*--- check if there is a menu active ------*/
	if (aktmenuz >= 0) 
	{
		nr = aktmenu[aktmenuz];
		a = &menu[nr];
		return( a);
	}
	else
		return(0); 
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIpopdown ()
 *					-Popdown with or without question
 *  				-
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIpopdown(Widget w, XtPointer closure, XtPointer wdata)
{
   extern char *		xuiLabelTable[][XUILABMAXTEXTS];  

	MENU		*a;


	a = (MENU *)closure;

	/*--- free and restore output menu stuff ---------*/
	if (a->typ == _OUTPUT)
		xUIoutmenudown ( a); 

	/*--- question ---------*/
	if (a->enter == FALSE || w == NULL)
		xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_MENUEND,
		            (XtCallbackProc)xUImenudown, closure, a->popup);
	else
		xUImenudown(w, closure, 0);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUImenudown ()
 *					-effective popdown a menu
 *  				-also popdown other satellite BM menus 
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUImenudown( Widget w, XtPointer closure, XtPointer data)
{
	extern MENU       menu[];
	extern int        aktmenuz;
	extern int        aktmenu[];
	extern int        aktfield[];
	extern int        zufield[];
	extern int        holdfield;
	extern Boolean    allmenuflag;
	extern unsigned char actiontoggle;
	extern TWINLIST	*twinList;

	int		i, f, x, nr;
	MENU		*a, *v;
	Arg		wargs[4];
	char		*ptext;

	/*--- Is a menu open ? ------*/
	if (aktmenuz == -1) 
		return ; 

/*???????	x = zufield[aktmenuz];  */
	/*--- field of present menu */
	x = aktfield[aktmenuz];

	/*--- close present menu ----*/
	v = (MENU *)closure;
	v->enter = TRUE;
	v->editfeld = TRUE;
	v->openedmenu = FALSE;				/* is checked for existing window */
	aktmenuz--;
	XtPopdown(v->popup);

	if (aktmenuz == -1)
		{
		/*--- set sensitive all enabled menus -------*/
		xUIpulldownSensitive( True );
		xUIglobmenuSensitive( True );
		}
	else
		{
		/*--- update behaviour of previous menu -------*/
		nr = aktmenu[aktmenuz];
		a = &menu[nr];
		f = aktfield[aktmenuz];
		/*--- re-enable editing --*/
		a->editfeld = TRUE;
		a->alreadywrite = FALSE;
		xUImenufeld(a, a->field[f], TRUE, TRUE, FALSE, TRUE);
		/*--- get text of search field ------*/
		for ( i=0;  i < v->anz;  i++ )
			{
			if (v->suchfields[i] == TRUE)
/*?????			if (v->buttontype[x] == SELECTFIELD || v->buttontype[x] == SEDITFIELD) */
				{
				ptext = XmTextGetString( v->field[i] );
				XtSetArg(wargs[0], XmNvalue, ptext );
				XtSetValues(a->field[f], wargs, 1);
				XtFree((void *)ptext);
				}
			}
		holdfield = f;
		}
	

	/*--- free unless specified by flag,  output is special because of optional fields -*/
	if ((!allmenuflag) || (v->typ == _OUTPUT))
		{
		/*--- current menu ----*/
		XtDestroyWidget(v->popup);
		XtFree((void *)v->field);
		XtFree((void *)v->pushbutton);
		v->pushbutton = NULL;
		v->popup = NULL;
		v->field = NULL;
		}

	/*--- free Twin select widget ---*/
	xUICtwinDestroy( twinList );
	twinList = 0;
}
