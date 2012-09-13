/**************************************************************
 * Modul:		GUI - dialog                            uglob.c
 *
 *					Create the global menu widgets
 *					init the main menu with data from GLOBDATA
 *
 *					
 * 
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uglob.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";




/*F--------------------------------------------------------------------------
 *  Function:	xUIglobBoardCreate ()
 *					create a global board with banner and menu (pushbuttons,fields) 
 *
 *  In:			-the parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xUIglobBoardCreate( Widget mainwindow)
{
	extern  MENU           glob;
	extern  GLOBDATA       globdata;
	extern  XtTranslations fielddelete, edit;
	extern	Widget	globalmenu, bannerboard;

	Widget	board;
	Widget	framemgr, rowcolmgr;
	char			bez[_CHAR80+1], rec[_CHAR200];
	Arg			arglist[10];
	int			ac;

	/*--- General bulletinboard ---------*/
	board = XtCreateManagedWidget(BOARD, xmBulletinBoardWidgetClass, mainwindow, 0, 0); 

	ac = 0;
	XtSetArg(arglist[ac], XmNpacking, XmPACK_TIGHT);  ac++;
	XtSetArg(arglist[ac], XmNorientation, XmVERTICAL); ac++;
	rowcolmgr = XtCreateManagedWidget( ROWCOLBUTTON, xmRowColumnWidgetClass,
														 board, arglist, ac);

	/*--- banner ----------*/
/*   	bannerboard  = xUIbannerCreate( rowcolmgr);*/
	/*--- global menu -----*/
	globalmenu  = xUIglobmenuCreate( rowcolmgr);

	return( board );
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIglobmenuCreate ()
 *					create a global menu with pushbuttons and fields 
 *
 *  In:			-the parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xUIglobmenuCreate( Widget mainwindow)
{
	extern  MENU           glob;
	extern  GLOBDATA       globdata;
	extern  XtTranslations fielddelete, edit;

	Widget	board;
	Widget	framemgr, rowcolmgr;
	Widget	framemenu, rowcolmenu, frameact,  rowcolact;
	Widget	framebutton, rowcolbutton, framefield,  rowcolfield;
	Widget	child[3];
	Widget  feld;
	Position		ypos;
	Dimension	marginheight, marginwidth;
	char			*ptr, *ztr, *tptr, *globptr;
	char			bez[_CHAR80+1], rec[_CHAR200];
	Arg			arglist[10];
	int			i;
	short			space;
	XmString		xmStr; 	
	Dimension		width, maxwidth;

	/* Bulletinboard kreiieren LEVEL 1 */

/*	board = XtCreateManagedWidget(BOARD, xmBulletinBoardWidgetClass, mainwindow, 0, 0);
*/

	/*--- RowColWidget kreiieren LEVEL 2 -------------*/
	framemgr  = XtCreateManagedWidget(FRAMEMGR, xmFrameWidgetClass, mainwindow, 0, 0);
	XtSetArg(arglist[0], XmNpacking, XmPACK_TIGHT);
	XtSetArg(arglist[1], XmNorientation, XmHORIZONTAL);
	rowcolmgr = XtCreateManagedWidget(ROWCOLMGR, xmRowColumnWidgetClass, framemgr, arglist, 2);

	/*--- RowColButtons kreiieren LEVEL 4 MENU  -------*/
	framebutton = XtCreateManagedWidget(FRAMEBUTTON, xmFrameWidgetClass, rowcolmgr, 0, 0);
	XtSetArg(arglist[0], XmNpacking, XmPACK_NONE);
	rowcolbutton = XtCreateManagedWidget( ROWCOLBUTTON, xmRowColumnWidgetClass,
														 framebutton, arglist, 1);
	XtSetArg(arglist[0], XmNspacing, &space);
	XtSetArg(arglist[1], XmNmarginHeight, &marginheight);
	XtSetArg(arglist[2], XmNmarginWidth, &marginwidth);
	XtGetValues(rowcolbutton, arglist, 3);

	/*--- RowColTextfields kreiieren LEVEL 4 MENU  ----*/
	framefield = XtCreateManagedWidget( FRAMEFIELD, xmFrameWidgetClass, rowcolmgr, 0, 0);
	XtSetArg(arglist[0], XmNpacking, XmPACK_NONE);
	rowcolfield = XtCreateManagedWidget( ROWCOLFIELD, xmRowColumnWidgetClass, framefield, arglist, 1);

	/*--- PushButtons und Fields LEVEL 5 ROWCOLBUTTON und ROWCOLFIELD */
	if (space <= 0)
	{
		space = 2;
		XtSetArg(arglist[0], XmNspacing, space);
		XtSetValues(rowcolbutton, arglist, 1);
		XtSetValues(rowcolfield, arglist, 1);
	}

	ypos = marginheight;
	maxwidth = 0;
	glob.pushbutton = (Widget *)XtMalloc(glob.anz * sizeof(Widget));
	glob.field =      (Widget *)XtMalloc(glob.anz * sizeof(Widget));
	for (i=0; i<glob.anz; i++)
	{
		globptr = xUIglobmember(i);
		ptr = globptr;
		/*--- keep only leaf for DB path ----*/
		if (i==0)
			{
			tptr = ptr;
			while (*tptr != 0)
				{
				if(*tptr == '/')
					{
					ptr = ptr+strlen(ptr);
					while (*ptr != '/') ptr--;
					ptr++;
					break;
					}
				tptr++;
				}
			}
		(void)sprintf(bez, "%s%s%d", POPUP, PUSHBUTTON, i);
		xmStr = XmStringCreateLtoR( glob.label[i], XmSTRING_DEFAULT_CHARSET);
		XtSetArg(arglist[0], XmNlabelString, xmStr ); 
		XtSetArg(arglist[1], XmNy, ypos);
		XtSetArg(arglist[2], XmNx, marginwidth);
		XtSetArg(arglist[3], XmNrecomputeSize, False);
		glob.pushbutton[i] = XmCreatePushButton(rowcolbutton, bez, arglist, 4);
		XmStringFree( xmStr); 
		XtSetArg(arglist[0], XmNwidth, &width ); 
		XtGetValues(glob.pushbutton[i], arglist, 1);
		if (width > maxwidth) maxwidth = width;
		XtOverrideTranslations(glob.pushbutton[i], fielddelete);

		(void)sprintf(bez, "%s%s%d", POPUP, FIELD, i);
		glob.field[i] = xUIeditor(bez, rowcolfield, glob.anzlines[i], glob.anzcolumns[i], ptr, &ypos, space, 0); 
		feld = glob.field[i];
		if (glob.buttontype[i] == SELNOFIELD)
		{
			XtAddCallback(glob.pushbutton[i], XmNactivateCallback,
											(XtCallbackProc)xUIselglob, (XtPointer)feld);
			ptr = globptr;
			XmTextSetString( feld, ptr);
		}
	}

	for (i=0; i<glob.anz; i++)
	{
		XtSetArg(arglist[0], XmNwidth, maxwidth ); 
		XtSetValues(glob.pushbutton[i], arglist, 1);
	}

	XtManageChildren(glob.pushbutton, glob.anz);
	XtManageChildren(glob.field,      glob.anz);

	/*--- take one button to find color map -----------*/
	xUIinitcolors (glob.pushbutton[0]);

	return( framemgr );
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIglobmenuSensitive ()
 *					set menu sensitivity. Used by active normal-menus
 *
 *  In:			-true means Enable
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIglobmenuSensitive( Boolean sensflag)
{
	extern MENU	glob;

	/*--- Sensitivity -----------------------------*/
	if (sensflag == TRUE)
		xUImenufeld( &glob, 0, TRUE, TRUE, FALSE, TRUE);
	else
		xUImenufeld( &glob, 0, FALSE, TRUE, TRUE, FALSE);
	/*-- unmanage menu is also a possibility ------*/
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIglobmenuPresence 
 *					display or not the global menu 
 *
 *  In:			-true means display
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIglobmenuPresence( Boolean presenceflag)
{
	extern MENU	glob;
	extern  Widget	globalmenu;
	Arg		arglist[3];
	int		ac;
	Dimension	workareaheight;
	static Dimension height;

	/*--- Sensitivity -----------------------------*/
	if (presenceflag == TRUE) {
		ac = 0;
		XtSetArg(arglist[ac], XmNheight, height);  ac++;
		XtSetValues(XtParent(XtParent(XtParent(XtParent(globalmenu)))), arglist, ac);
		XtManageChild( XtParent(XtParent(globalmenu)));
	} else {
		ac = 0;
		XtSetArg(arglist[ac], XmNheight, &height);  ac++;
		XtGetValues(XtParent(XtParent(XtParent(XtParent(globalmenu)))), arglist, ac);
		ac = 0;
		XtSetArg(arglist[ac], XmNheight, &workareaheight);  ac++;
		XtGetValues(XtParent(XtParent(globalmenu)), arglist, ac);
		ac = 0;
		XtSetArg(arglist[ac], XmNheight, height-workareaheight);  ac++;
		XtSetValues(XtParent(XtParent(XtParent(XtParent(globalmenu)))), arglist, ac);
		XtUnmanageChild( XtParent(XtParent(globalmenu)));
	}
}

