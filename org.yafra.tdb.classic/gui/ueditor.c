/*D************************************************************
 * Modul:		GUI - Dialog		ueditor.c
 *
 *					Create an edit field with dimension management
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ueditor.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";

Widget xUIeditor(char* name, Widget parent, int anz_lines, int anz_columns,
						char* defwert, Position *ypos, short space, XtTranslations edit)
{
	Widget		editor;
	Arg			wargs[15];
	Dimension	height;
	int			ac;
	int         len;

	/* Kreiert ein Text Edit Widget */
	ac = 0;
	XtSetArg(wargs[ac], XmNeditable, False); ac++;
	XtSetArg(wargs[ac], XmNcursorPositionVisible, False); ac++;
	XtSetArg(wargs[ac], XmNy, *ypos);        ac++;
	XtSetArg(wargs[ac], XmNwordWrap, False); ac++;
	if (anz_lines == 1)
		{
		XtSetArg(wargs[ac], XmNeditMode, XmSINGLE_LINE_EDIT); ac++;
		}
	else
		{
		XtSetArg(wargs[ac], XmNeditMode, XmMULTI_LINE_EDIT);  ac++;
		}
	XtSetArg(wargs[ac], XmNrows, (XtArgVal)(short)anz_lines); ac++;
	XtSetArg(wargs[ac], XmNcolumns, (XtArgVal)(short)anz_columns); ac++;
	XtSetArg(wargs[ac], XmNmaxLength, (XtArgVal)anz_columns*anz_lines); ac++;
	if (defwert != (char *)NULL)
		{
		if (*defwert != (char)NULL)
			{
			len = strlen(defwert);
			if (len > 0);
				XtSetArg(wargs[ac], XmNvalue, (XtArgVal)defwert); ac++;
			}
		}
	editor = XtCreateWidget(name, xmTextWidgetClass, parent, wargs, ac);

	/*--- edit translation: start and quit ------*/
	if (edit)
		XtOverrideTranslations(editor, edit);

	/*--- Update position for calling widget ----*/
	XtSetArg(wargs[0], XmNheight, &height);
	XtGetValues(editor, wargs, 1);
	*ypos += height+space;
	
	return(editor);
}
