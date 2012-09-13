/*D*********************************************************
 * Modul:		GRAPHIC					gwgoptio.c
 *            
 *					Create Option box and menus            
 *            
 * Copyright: yafra.org, Basel, Switzerland
 ***********************************************************/
/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/gwgoptio.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

   Log Information:
   $Log: gwgoptio.c,v $
   Revision 1.2  2008-11-02 19:55:42  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:03:16  ja
   general version

 * Revision 1.5  94/02/18  10:38:41  10:38:41  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.4  94/02/14  16:21:29  16:21:29  ja (Jean-Marc Adam)
 * free labels
 * 
 * Revision 1.3  93/08/21  00:26:50  00:26:50  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.2  93/01/03  21:47:32  21:47:32  mw ()
 * "new MENU structur"
 * 
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwgoptio.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



#define ANZOPTIONMENUS  6


Widget xGRwidget_optionmenu(Widget parent)
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display				*display;
	extern ApplicationData	app_data;
	extern DatabaseData		db_data;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB		graglob;

	static ACTCALLBACK *callback[ANZOPTIONMENUS];
	static int box[ANZOPTIONMENUS] = { BUTTONFONT, BUTTONCOLOR, BUTTONLINEWIDTH,
												BUTTONPATTERN, BUTTONLINESTYLE, BUTTONSNAP};

	Widget     optionmenu;						/* Rowcol f�r OptionMenuButtons */
	Widget     option[ANZOPTIONMENUS];
	Widget     pulldown[ANZOPTIONMENUS];
	Widget     *button;
	Arg        args[7];
	int        n, i, j, def, len;
	int        screen;
	int        anz[ANZOPTIONMENUS];
	char       bez[50];
	char       ***str;
	XmString   label;
	char       *pLabel;

	screen = XDefaultScreen(display);

	n=0;
	XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);  n++;
	XtSetArg(args[n], XmNnumColumns, 1);           n++;
	optionmenu = XmCreateRowColumn(parent, GRAPHIKOPTIONMENU, args, 2);

	/*--- Count and copy resources in array ------------------------------*/
	str = (char ***)malloc(ANZOPTIONMENUS*sizeof(char **));

	/*--- Fonts --------------------*/
	anz[0] = xGRanz_strings(app_data.fontListe, &str[0]);
	graglob.anzFonts = anz[0];
	/*--- Colors -------------------*/
	anz[1] = xGRanz_strings(app_data.colorListe, &str[1]);
	graglob.anzColors = anz[1];
	/*--- Linewidth ----------------*/
	anz[2] = xGRanz_strings(app_data.linewidthListe, &str[2]);
	graglob.anzLinewidth = anz[2];
	/*--- Pattern ------------------*/
	anz[3] = xGRanz_strings(app_data.patternListe, &str[3]);
	graglob.anzPattern = anz[3];
	/*--- Linestyle ----------------*/
	anz[4] = xGRanz_strings(app_data.linestyleListe, &str[4]);
	graglob.anzLinestyle = anz[4];
	/*--- Snap ---------------------*/
	anz[5] = xGRanz_strings(app_data.snapListe, &str[5]);
	graglob.anzSnap = anz[5];

	for (i=0; i<ANZOPTIONMENUS; i++) {
		callback[i] = (ACTCALLBACK *)malloc((unsigned)anz[i]*sizeof(ACTCALLBACK));
		for (j=0; j<anz[i]; j++) {
			callback[i][j].box = box[i];
			callback[i][j].tog = j;
		}
	}

	/*--- Create pulldown for each option box ------------------------*/
	for (i=0;  i<ANZOPTIONMENUS;  i++) {
		sprintf(bez, "%s%d", GRAPHIKOPTIONPULLDOWN, i);
		pulldown[i] = XmCreatePulldownMenu(optionmenu, bez, 0, 0);
		button = (Widget *)malloc(anz[i]*sizeof(Widget));
		/*--- Push buttons ---------*/
		for (j=0; j<anz[i]; j++) {
			label = XmStringCreateSimple( str[i][j]);  
			XtSetArg(args[0], XmNlabelString, label);
			sprintf(bez, "%s%d%d", GRAPHIKOPTION, i, j);
			button[j] = XmCreatePushButton(pulldown[i], bez, args, 1);
			XtAddCallback(button[j], XmNactivateCallback,
								(XtCallbackProc)xGRaction, (XtPointer)&callback[i][j]);
			XmStringFree(label);
		}
		XtManageChildren(button, anz[i]);

		/*--- Option labels ------------------------------*/
		sprintf(bez, "%s%d", GRAPHIKOPTION, i);
		n=0;
		XtSetArg(args[n], XmNsubMenuId, pulldown[i]);  n++;
		/*--- Align ------*/
		pLabel = xgrLabelTable[_GR_OPTION][i];
		len = strlen( pLabel);
		if (len == 0) {
			sprintf(bez, "          ");
		} else if (len == 1) {
			sprintf(bez, "    %s     ", pLabel);
		} else if (len == 2) {
			sprintf(bez, "    %s    ", pLabel);
		} else if (len == 3) {
			sprintf(bez, "   %s    ", pLabel);
		} else if (len == 4) {
			sprintf(bez, "   %s   ", pLabel);
		} else if (len == 5) {
			sprintf(bez, "  %s   ", pLabel);
		} else if (len == 6) {
			sprintf(bez, "  %s  ", pLabel);
		} else if (len == 7) {
			sprintf(bez, " %s  ", pLabel);
		} else if (len == 8) {
			sprintf(bez, " %s ", pLabel);
		} else if (len == 9) {
			sprintf(bez, "%s ", pLabel);
		} else if (len >= 10) {
			sprintf(bez, "%s", pLabel);
		}

		label = XmStringCreateSimple(bez);
		XtSetArg(args[n], XmNlabelString,label);       n++;
		option[i] = XmCreateOptionMenu(optionmenu, bez, args, n);
		XmStringFree(label);

		switch (i) {
			case 0:
				def = 0;
				grawidgets.optfont = button;
				grawidgets.aktfont = option[i];
				graglob.indfont    = def;
				break;
			case 1:
				def = 0;
				grawidgets.optcolor = button;
				grawidgets.aktcolor = option[i];
				graglob.indcolor   = def;
				break;
			case 2:
				def = 0;
				grawidgets.optlinewidth = button;
				grawidgets.aktlinewidth = option[i];
				graglob.indwidth   = def;
				break;
			case 3:
				def = 0;
				grawidgets.optpattern = button;
				grawidgets.aktpattern = option[i];
				graglob.indpattern = def;
				break;
			case 4:
				def = 0;
				grawidgets.optlinestyle = button;
				grawidgets.aktlinestyle = option[i];
				graglob.indstyle   = def;
				break;
			case 5:
				def = 2;
				grawidgets.optsnap = button;
				grawidgets.aktsnap = option[i];
				graglob.indsnap    = def;
				break;
		}
	}
	XtManageChildren(option, ANZOPTIONMENUS);

	/*--- free labels strings ----------------------*/



	return(optionmenu);
}

