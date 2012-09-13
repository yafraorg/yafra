/*D***********************************************************
 * Modul:		GUI -  BM Dialog			bactionb.c    
 *                                                            
 *					Create actionbar widgets                                                
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/bactionb.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xBMactionbar ()
 *					-create BM action bar (4 actions)
 *  In:			-parent widget, the bm menu in creation
 *  out:			-
 *  Return:		-created widget
 *---------------------------------------------------------------------------
 */
Widget xBMactionbar(Widget parent, BOOKMENU *b )
{
	extern	XtTranslations  softkeytrans;
   extern	char *	 xuiLabelTable[][XUILABMAXTEXTS];

	Widget	rowcol, separator; 
	Widget	child[8];
	char		bez[_LABELLEN+1], fez[_LABELLEN+1];
	char		bezdummy[_LABELLEN+1], fezdummy[_LABELLEN+1];
	Arg		arglist[10];
	int		ac;
	int		i;
	XmString		xmStr, xmStrDum ; 	

	/*----------------- LEVEL 3 ROWCOL -----------------*/
	ac = 0;
	(void)sprintf(bez, "%s%d", ROWCOLACT, _BMDLNNR );
	XtSetArg(arglist[ac], XmNpacking, XmPACK_COLUMN); ac++;
	XtSetArg(arglist[ac], XmNorientation, XmHORIZONTAL); ac++;
	rowcol = XtCreateManagedWidget(bez, xmRowColumnWidgetClass, parent, arglist, ac);


	/*----------------- LEVEL 4 ------------------------*/
	/*--- preparation for dummies ---*/
	(void)sprintf(bezdummy, "%s%d", BUTTONDUMMY, _BMDLNNR);
	(void)sprintf(fezdummy, "%s",	"  ");
	xmStrDum = XmStringCreateLtoR( fezdummy, XmSTRING_DEFAULT_CHARSET);

	/*--- HELP/Info ACTION --------*/
	(void)sprintf(bez, "%s%d", BUTTONHELP, _BMDLNNR);
	(void)sprintf(fez, "%s\n%s",	LABEL_HELP_1, LABEL_HELP_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	child[0] = XmCreatePushButton(rowcol, bez, arglist, 1);
	b->Wgbuttonhelp = child[0];
	XmStringFree( xmStr); 
	XtAddCallback(child[0], XmNactivateCallback, (XtCallbackProc)xUIinfo, (XtPointer)b);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[1] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[2] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[3] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);


	/*--- Separator --------------------------------------------------------*/
	(void)sprintf(bez, "%s%d", SEPAR, _BMDLNNR);
	XtSetArg(arglist[0], XmNseparatorType, XmNO_LINE ); 
	XtSetArg(arglist[1], XmNorientation,   XmVERTICAL    ); 
	XtSetArg(arglist[2], XmNwidth,   25    ); 
	separator = XmCreateSeparator( rowcol, bez, arglist, 3);
	XtManageChild(separator);


	/*--- Dummy button --------*/
	XtSetArg(arglist[0], XmNlabelString, xmStrDum ); 
	child[4] = XmCreatePushButton(rowcol, bezdummy, arglist, 1);

	/*--- OK/Commit  ACTION -------*/
	(void)sprintf(bez, "%s%d", BUTTONACT, _BMDLNNR);
	(void)sprintf(fez, "%s\n%s",	LABEL_COMMIT_1, LABEL_COMMIT_2  );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	child[5] = XmCreatePushButton(rowcol, bez, arglist, 1);
	b->Wgbuttonact = child[5];
	XmStringFree( xmStr); 
	XtAddCallback(child[5], XmNactivateCallback, (XtCallbackProc)b->action, (XtPointer)b);

	/*--- MenuClear ACTION --------*/
	(void)sprintf(bez, "%s%d", BUTTONMENU, _BMDLNNR);
	(void)sprintf(fez, "%s\n%s",	LABEL_DELETEMENU_1, LABEL_DELETEMENU_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	child[6] = XmCreatePushButton(rowcol, bez, arglist, 1);
	b->Wgbuttonmenu = child[6];
	XmStringFree( xmStr); 
	XtAddCallback(child[6], XmNactivateCallback, (XtCallbackProc)xBMfieldDeleteAll, (XtPointer)b);

	/*--- CANCEL/quit ACTION ------*/
	(void)sprintf(bez, "%s%d", BUTTONQUIT, _BMDLNNR);
	(void)sprintf(fez, "%s\n%s",	LABEL_QUITMENU_1, LABEL_QUITMENU_2 );
	xmStr = XmStringCreateLtoR( fez, XmSTRING_DEFAULT_CHARSET);
	XtSetArg(arglist[0], XmNlabelString, xmStr ); 
	child[7] = XmCreatePushButton(rowcol, bez, arglist, 1);
	b->Wgbuttonquit = child[7];
	XmStringFree( xmStr); 
	XtAddCallback(child[7], XmNactivateCallback, (XtCallbackProc)xBMpopdown, (XtPointer)b);

	for (i=0; i<8; i++)
		XtOverrideTranslations(child[i], softkeytrans);

	XtManageChildren(child, 8);
	XmStringFree( xmStrDum); 

	return (rowcol); 
}

