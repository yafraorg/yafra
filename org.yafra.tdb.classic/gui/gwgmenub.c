/*D*********************************************************
 * Modul:		GRAPHIC                           gwgmenub.c
 *            
 *					Create menubar and menus            
 *            
 * Copyright: yafra.org, Basel, Switzerland
 **********************************************************
 */


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgmenub.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";

#include <uinclude.h>
#include <ginclude.h>



/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_menubar
 *					create a pulldown menu for graphic 
 *  In:			-the parent
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_menubar( Widget parent )
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	static ACTCALLBACK actfilecallback[] = {
		{BUTTONFILE, BUTTONFILE_LOAD     },
		{BUTTONFILE, BUTTONFILE_SAVE     },
		{BUTTONFILE, BUTTONFILE_SAVEAS   },
		{BUTTONFILE, BUTTONFILE_DELETEALL},
		{BUTTONFILE, BUTTONFILE_CANCEL   },
		{BUTTONFILE, BUTTONFILE_QUIT     }
	};
	static ACTCALLBACK actcreatecallback[] = {
		{BUTTONCREATE, BUTTONCREATE_TEXT},
		{BUTTONCREATE, BUTTONCREATE_POINT},
		{BUTTONCREATE, BUTTONCREATE_LINE},
		{BUTTONCREATE, BUTTONCREATE_RECTANGLE},
		{BUTTONCREATE, BUTTONCREATE_CIRCLE},
		{BUTTONCREATE, BUTTONCREATE_ARC},
		{BUTTONCREATE, BUTTONCREATE_ELLIPSE},
		{BUTTONCREATE, BUTTONCREATE_FILLEDRECTANGLE},
		{BUTTONCREATE, BUTTONCREATE_FILLEDCIRCLE},
		{BUTTONCREATE, BUTTONCREATE_FILLEDARC},
		{BUTTONCREATE, BUTTONCREATE_FILLEDELLIPSE}
	};
	static ACTCALLBACK acteditcallback[] = {
		{BUTTONEDIT, BUTTONEDIT_MOVE},
		{BUTTONEDIT, BUTTONEDIT_COPY},
		{BUTTONEDIT, BUTTONEDIT_DELETE}
	};
	static ACTCALLBACK actdefinecallback[] = {
		{BUTTONDEFINE, BUTTONDEFINE_GRID},
		{BUTTONDEFINE, BUTTONDEFINE_PICKBOX},
		{BUTTONDEFINE, BUTTONDEFINE_POINTS},
		{BUTTONDEFINE, BUTTONDEFINE_DRAWAREA}
	};
	static ACTCALLBACK actzoomcallback[] = {
		{BUTTONZOOM, BUTTONZOOM_START},
		{BUTTONZOOM, BUTTONZOOM_ZOOM},
		{BUTTONZOOM, BUTTONZOOM_LAST},
		{BUTTONZOOM, BUTTONZOOM_NEXT}
	};
	static ACTCALLBACK acthilfecallback[] = {
		{BUTTONHILFE, BUTTONHILFE_GRAPHIK}
	};
	static ACTCALLBACK *actcallback[] = {
		actfilecallback,
		actcreatecallback,
		acteditcallback,
		actdefinecallback,
		actzoomcallback,
		acthilfecallback
	};
	static int anz[] = {
		XtNumber(actfilecallback),
		XtNumber(actcreatecallback),
		XtNumber(acteditcallback),
		XtNumber(actdefinecallback),
		XtNumber(actzoomcallback),
		XtNumber(acthilfecallback)
	};

	MENULIST  *grapulldown;
	MENULIST  **gralist;

	Widget           menubar;
	int              i, j, k;
	char             buf[30];

	menubar = XmCreateMenuBar(parent, GRAPHIKMENUBAR, 0, 0);

	grapulldown = (MENULIST *)malloc(XtNumber(actcallback)*sizeof(MENULIST));
	gralist = (MENULIST **)malloc(XtNumber(actcallback)*sizeof(MENULIST *));
	for (i=0;  i<XtNumber(actcallback);  i++) {
		grapulldown[i].titel = xgrLabelTable[_GR_MENU_FILE + i][0];
		grapulldown[i].mnemonic = xgrLabelTable[_GR_MENU_FILE + i][0][0];

		gralist[i] = (MENULIST *)malloc(anz[i]*sizeof(MENULIST));
		for (j=0; j<anz[i]; j++) {
			gralist[i][j].titel = xgrLabelTable[_GR_MENU_FILE + i][j+1];
			gralist[i][j].mnemonic = xgrLabelTable[_GR_MENU_FILE + i][j+1][0];
			gralist[i][j].func = xGRaction;
			gralist[i][j].data = (XtPointer)&actcallback[i][j];
			gralist[i][j].status = True;
			gralist[i][j].menu = False;
			gralist[i][j].submenu = 0;
			gralist[i][j].anz_subitems = 0;
			gralist[i][j].submenutitle = 0;
		}
		grapulldown[i].func = 0;
		grapulldown[i].data = 0;
		grapulldown[i].status = True;
		grapulldown[i].menu = False;
		grapulldown[i].submenu = gralist[i];
		grapulldown[i].anz_subitems = anz[i];
		grapulldown[i].submenutitle = 0;
	}

	/*--- Help special right justified ------*/
	grapulldown[XtNumber(actcallback)-1].func = xGRaction;
	grapulldown[XtNumber(actcallback)-1].data = (XtPointer)&acthilfecallback;
	grapulldown[XtNumber(actcallback)-1].anz_subitems = 0;

	(void)xUIpulldown(0, menubar, grapulldown, XtNumber(actcallback));

	/*--- Restablish Help ------*/
	grapulldown[XtNumber(actcallback)-1].anz_subitems = XtNumber(acthilfecallback);

	grawidgets.menubutton = (Widget **)malloc(XtNumber(actcallback)*sizeof(Widget *));
	for (i=0; i<XtNumber(actcallback); i++) {
		grawidgets.menubutton[i] = grapulldown[i].button;
	}

	return(menubar);
}




/*F-------------------------------------------------------------------------
 *  Function:	xGRwidget_menubar_sensitive ()
 *					-some always present pushbuttons in graphik part 
 *					-
 *  In:			-parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xGRwidget_menubar_sensitive() 
{ 
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB		graglob;

	int			i, j, typ;
	static struct {
		int anz;
		Boolean modeinput;
		Boolean modeselect;
		Boolean modeshow;
	} menubarset[] =
		{{BUTTONFILE_QUIT,              True,  False, False},
	 	 {BUTTONCREATE_FILLEDELLIPSE,   True,  False, False},
		 {BUTTONEDIT_DELETE,            True,  False, False},
		 {BUTTONDEFINE_POINTS,          True,  False, False},
		 {BUTTONZOOM_NEXT,              True,  True,  True },
		 {BUTTONHILFE_GRAPHIK,          True,  True,  True } };

	/*--- Typenspezifisch Zugriffe auf Graphik definieren ----------*/
	typ = graglob.mode ;
	switch(typ) {
		case XGRINPGRAFIC:
			for (i=0; i<XtNumber(menubarset); i++) {
				for (j=0; j<=menubarset[i].anz; j++) {
					XtSetSensitive( grawidgets.menubutton[i][j],
											menubarset[i].modeinput);
				}
			}
			XtSetSensitive(grawidgets.select, True);
			XtSetSensitive(grawidgets.booking, False);
			XtSetSensitive(grawidgets.go, False);
			break;

		case XGRSELGRAFIC:
			for (i=0; i<XtNumber(menubarset); i++) {
				for (j=0; j<=menubarset[i].anz; j++) {
					XtSetSensitive( grawidgets.menubutton[i][j],
											menubarset[i].modeselect);
				}
			}
			XtSetSensitive(grawidgets.select, False);
			XtSetSensitive(grawidgets.booking, True);
			XtSetSensitive(grawidgets.go, True);
			break;

		case XGRSHOWGRAFIC:
			for (i=0; i<XtNumber(menubarset); i++) {
				for (j=0; j<=menubarset[i].anz; j++) {
					XtSetSensitive( grawidgets.menubutton[i][j],
											menubarset[i].modeshow);
				}
			}
			XtSetSensitive(grawidgets.select, False);
			XtSetSensitive(grawidgets.booking, False);
			XtSetSensitive(grawidgets.go, False);
			break;
	}
}




/*F-------------------------------------------------------------------------
 *  Function:	xGRwidget_menubar_mini ()
 *					-always present menu buttons in graphik part 
 *					-
 *  In:			-parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
Widget xGRwidget_menubar_mini( Widget parent )
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern GRAWIDGETS grawidgets;

	Widget	minimenu, pulldown[8], pullbutton[8], cascadebutton[8];	
	Arg		args[6];
	int		i, n, ac;
	XmString xmstr;

	static ACTCALLBACK actminicallback[] = {
		{BUTTONFILE, BUTTONFILE_CANCEL    },       
		{BUTTONZOOM, BUTTONZOOM_START     },
		{BUTTONZOOM, BUTTONZOOM_ZOOM      },
		{BUTTONZOOM, BUTTONZOOM_LAST      },
		{BUTTONZOOM, BUTTONZOOM_NEXT      },
		{BUTTONHILFE, BUTTONHILFE_GRAPHIK }
	};

	/*---- menubar --------*/
	minimenu = XmCreateMenuBar(parent, GRAPHIKMENUBAR, 0, 0);
	/*---- build an ONE line menu -----------------------------------------*/
	for (i=0;  i<XtNumber(actminicallback);  i++) {
		/*--- pulldown ----*/
		xmstr = XmStringCreateSimple( xgrLabelTable[_GR_MINI_MENU][i]);
		/*-- menubar cascade button -----*/
		ac = 0;
		XtSetArg(args[ac], XmNlabelString,  xmstr);        ac++;
		XtSetArg(args[ac], XmNmnemonic,     ' ');          ac++;
		cascadebutton[i] = XmCreateCascadeButton( minimenu, GRAPHIKPUSHBUTTON, args, ac);
		XtManageChild(cascadebutton[i]); 
		XtAddCallback(cascadebutton[i], XmNactivateCallback,
							(XtCallbackProc)xGRaction, (XtPointer)&actminicallback[i]);
		XmStringFree( xmstr);
	}
	/*---- Help right justified ---------*/
	ac = 0;
	XtSetArg(args[ac], XmNmenuHelpWidget, cascadebutton[XtNumber(actminicallback)-1]);  ac++;
	XtSetValues( minimenu, args, ac);   
	
	return( minimenu);
}




