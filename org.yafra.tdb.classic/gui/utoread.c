/*D***********************************************************
 * Modul:	GUI - dialog			utoread.c
 * 	                                       
 *				Turn edit field to read
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/utoread.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";

XtActionProc xUIwritetoread(Widget w, XEvent* event, String* s, Cardinal* m)
{
	extern int      aktmenuz;
	extern int      aktmenu[];
	extern int      aktfield[];
	extern MENU     menu[];
	extern XtTranslations transnoedit;

	Arg	wargs[2];
	MENU	*a;
	int     f, n;

	n = aktmenu[aktmenuz];
	a = &menu[n];
	f = aktfield[aktmenuz];

	if (a->field == NULL)
		return;
	if (a->field[f] == NULL)
		return;

	if (a->editfeld && a->alreadywrite && a->field[f] == w) {
		xUImenufeld(a, w, TRUE, TRUE, FALSE, TRUE);
		XtSetArg(wargs[0], XmNeditable, FALSE);
		XtSetArg(wargs[1], XmNcursorPositionVisible, FALSE);
		XtSetValues(w, wargs, 2);
		XtOverrideTranslations(w, transnoedit);
		a->alreadywrite = FALSE;
	}
}
