/*D***********************************************************
 * Modul:		GUI - Dialog			uactionb.c    
 *                                                            
 *					Create actionbar: a frame and 8 buttons                                               
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uactionb.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:  xUIactionbar ()
 *            create buttons and labels strings 
 *            labels come from a label table[_ACTIONBAR][0] 
 *            Prepare childs and callbacks 
 *            -
 *            -
 *  In:       pointer to a menu struct,  the parent widget 
 *  out:      -
 *  Return:   -
 *---------------------------------------------------------------------------
 */
void xUIactionbar(MENU *a, Widget parent)
{
	extern MENU		 menu[];
	extern			 XtTranslations softkeytrans;
   extern char *	 xuiLabelTable[][XUILABMAXTEXTS];

	Widget child[8], frameact, rowcolact, separator;
	char   bez[_LABELLEN+1], fez[_LABELLEN+1];
	Arg    arglist[10];
	int    ac, nr, i;
	XmString		xmStr; 	

	/*-- general inits ------*/
	nr = a-menu;

   /*------ LEVEL 3  Abschnitt Action kreieren --------------------------*/
	(void)sprintf(bez, "%s%d", FRAMEACT, nr);
	frameact = xUIframelabel(parent, NULL, bez, LABEL_FRAMEACTION );	
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLACT, nr); 
	XtSetArg(arglist[ac], XmNpacking,    XmPACK_TIGHT); ac++;	
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcolact = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, frameact, arglist, ac);


	/*-- Help and Info Button  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONHELP, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_HELP_1, LABEL_HELP_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonhelp = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[5] = a->buttonhelp;
	XmStringFree( xmStr); 
	XtAddCallback(child[5], XmNactivateCallback, (XtCallbackProc)xUIinfo, (XtPointer)a);

	/*-- NextfieldButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONNEXT, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_NEXTITEM_1, LABEL_NEXTITEM_2  );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonnext = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[0] = a->buttonnext;
	XmStringFree( xmStr); 
	XtAddCallback(child[0], XmNactivateCallback, (XtCallbackProc)xUIfieldnext, (XtPointer)a);

	/*-- LastfieldButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONLAST, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_LASTITEM_1, LABEL_LASTITEM_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonlast = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[1] = a->buttonlast;
	XmStringFree( xmStr); 
	XtAddCallback(child[1], XmNactivateCallback, (XtCallbackProc)xUIfieldlast, (XtPointer)a);

	/* DeletefieldButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONDEL, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_DELETEITEM_1, LABEL_DELETEITEM_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttondel = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[2] = a->buttondel;
	XtAddCallback(child[2], XmNactivateCallback, (XtCallbackProc)xUIeditpurge, (XtPointer)a);
	XmStringFree( xmStr); 
	XtSetSensitive(a->buttondel, FALSE);

	/*--- Separator --------------------------------------------------------*/
	(void)sprintf(bez, "%s%d", SEPAR, nr);
	XtSetArg(arglist[0], XmNseparatorType, XmNO_LINE ); 
	XtSetArg(arglist[1], XmNorientation,   XmVERTICAL    ); 
	XtSetArg(arglist[2], XmNwidth,   25    ); 
	separator = XmCreateSeparator( rowcolact, bez, arglist, 3);
	XtManageChild(separator);


	/* EndfieldButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONEND, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_ENDEDIT_1, LABEL_ENDEDIT_2  );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonend = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[3] = a->buttonend;
	XtAddCallback(child[3], XmNactivateCallback, (XtCallbackProc)xUIeditend, (XtPointer)a);
	XmStringFree( xmStr); 
	XtSetSensitive(a->buttonend, FALSE);

	/* ActionButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONACT, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_COMMIT_1, LABEL_COMMIT_2  );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonact = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[4] = a->buttonact;
	XmStringFree( xmStr); 
	XtAddCallback(child[4], XmNactivateCallback, (XtCallbackProc)a->action, (XtPointer)a);

	/* MenuClearButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONMENU, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_DELETEMENU_1, LABEL_DELETEMENU_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonmenu = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[6] = a->buttonmenu;
	XmStringFree( xmStr); 
	XtAddCallback(child[6], XmNactivateCallback, (XtCallbackProc)xUIfieldDeleteAll, (XtPointer)a);

	/* QuitButton  kreiieren LEVEL 4 ACTION */
	(void)sprintf(bez, "%s%d", BUTTONQUIT, nr);
	(void)sprintf(fez, "%s\n%s",	LABEL_QUITMENU_1, LABEL_QUITMENU_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	a->buttonquit = XmCreatePushButton( rowcolact, bez, arglist, 1);
	child[7] = a->buttonquit;
	XmStringFree( xmStr); 
	XtAddCallback(child[7], XmNactivateCallback, (XtCallbackProc)xUIpopdown, (XtPointer)a);

	for (i=0; i<8; i++)
		XtOverrideTranslations(child[i], softkeytrans);

	XtManageChildren(child, 8);
}

