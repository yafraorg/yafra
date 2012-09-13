/*D************************************************************
 * Modul:		GRAPHIC							XGRaction.c
 *
 *					General action dispatcher for events
 *					Menu actions and drawing area inputs
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gaction.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

XtCallbackProc xGRaction(Widget w, XtPointer Input, XtPointer Output)
{
	extern Display *display;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB graglob;

	int n;
	ACTCALLBACK *gracallback;
	XmAnyCallbackStruct *any;
	XEvent *event;

	/*--- Callback Qualifier ------------*/
	gracallback = (ACTCALLBACK *)Input;		/*closure*/
	any = (XmAnyCallbackStruct *)Output;
	event = (XEvent *)any->event;

	if (event != (XEvent *)NULL)
		if (event->type == ButtonPressMask)
			return;

	/*--- Callback actions ----------------------------*/
	switch (gracallback->box)
		{
		case BUTTONFILE:
			xGRfile(event, gracallback->tog);
			return;
			break;
		case BUTTONCREATE:
		case BUTTONEDIT:
		case BUTTONDEFINE:
			graglob.aktbox = gracallback->box;
			graglob.akttog = gracallback->tog;
			graglob.eingabe = 0;
			graglob.tempObj = 0;
			XmTextSetString(grawidgets.frage, "");
			XmTextSetString(grawidgets.antwort, "");
			break;
		case BUTTONSELECT:
			if (graglob.mode == XGRINPGRAFIC)
				{
				graglob.aktbox = gracallback->box;
				graglob.akttog = gracallback->tog;
				graglob.eingabe = 0;
				graglob.tempObj = 0;
				XmTextSetString(grawidgets.frage, "");
				XmTextSetString(grawidgets.antwort, "");
				}
			else
				return;
			break;
		case BUTTONZOOM:
			if (gracallback->tog == BUTTONZOOM_ZOOM) {
				graglob.aktbox = gracallback->box;
				graglob.akttog = gracallback->tog;
				graglob.eingabe = 0;
				graglob.tempObj = 0;
				XmTextSetString(grawidgets.frage, "");
				XmTextSetString(grawidgets.antwort, "");
			}
			xGRzoom(event, gracallback->tog);           /*execute callbacks*/
			return;
			break;
		case BUTTONHILFE:
			xGRhelp(event, gracallback->tog);
			return;
			break;
/*see action procedures */
/*		case BUTTONGRAPHIK:
			if (graglob.aktbox != BUTTONZOOM) {
				if (graglob.mode == XGRSELGRAFIC) {
					xGRbook(event, gracallback->tog);
					return;
				}
			}
			break;
*/
		case BUTTONTEXTFELDQUIT:
			graglob.aktbox = BUTTONNONE;
			graglob.akttog = BUTTONNONE;
			graglob.eingabe = 0;
			graglob.tempObj = 0;
			XmTextSetString(grawidgets.frage, "");
			XmTextSetString(grawidgets.antwort, "");
			return;
			break;
		case BUTTONLINESTYLE:
			graglob.indstyle = (unsigned char)gracallback->tog;
			graglob.gcz = &graglob.GCZ[graglob.indcolor]
											[graglob.indwidth][graglob.indstyle];
			return;
			break;
		case BUTTONSNAP:
			graglob.indsnap = (unsigned char)gracallback->tog;
			if (gracallback->tog == BUTTONSNAP_POINT) {
				graglob.showPickbox = True;
			} else {
				graglob.showPickbox = False;
			}
			return;
			break;
		case BUTTONFONT:
			graglob.indfont = (unsigned char)gracallback->tog;
			graglob.gcf = &graglob.GCF[graglob.indcolor][graglob.indfont];
			return;
			break;
		case BUTTONLINEWIDTH:
			graglob.indwidth = (unsigned char)gracallback->tog;
			graglob.gcz = &graglob.GCZ[graglob.indcolor]
											[graglob.indwidth][graglob.indstyle];
			return;
			break;
		case BUTTONPATTERN:
			graglob.indpattern = (unsigned char)gracallback->tog;
			graglob.gcp = &graglob.GCP[graglob.indcolor][graglob.indpattern];
			return;
			break;
		case BUTTONCOLOR:
			graglob.indcolor = (unsigned char)gracallback->tog;
			graglob.gcz = &graglob.GCZ[graglob.indcolor]
											[graglob.indwidth][graglob.indstyle];
			graglob.gcp = &graglob.GCP[graglob.indcolor][graglob.indpattern];
			graglob.gcf = &graglob.GCF[graglob.indcolor][graglob.indfont];
			return;
			break;
		}

	/*--- Callback-follow  or  drawing area input actions ----------------*/
	n = graglob.akttog;
	switch (graglob.aktbox) {
		case BUTTONSELECT:
			xGRselect_region(Output, n);
			break;
		case BUTTONDEFINE:
			xGRask(event, n);
			break;
		case BUTTONZOOM:
			xGRzoom(event, n);
			break;
		case BUTTONCREATE:
			switch(n) {
				case BUTTONCREATE_TEXT:
					xGRcreate_text(event, n);
					break;
				case BUTTONCREATE_POINT:
					xGRcreate_point(event, n);
					break;
				case BUTTONCREATE_LINE:
					xGRcreate_line(event, n);
					break;
				case BUTTONCREATE_ARC:
					xGRcreate_arc(event, n);
					break;
				case BUTTONCREATE_CIRCLE:
					xGRcreate_circle(event, n);
					break;
				case BUTTONCREATE_RECTANGLE:
					xGRcreate_rectangle(event, n);
					break;
				case BUTTONCREATE_ELLIPSE:
					xGRcreate_ellipse(event, n);
					break;
				case BUTTONCREATE_FILLEDARC:
					xGRcreate_arc(event, n);
					break;
				case BUTTONCREATE_FILLEDCIRCLE:
					xGRcreate_circle(event, n);
					break;
				case BUTTONCREATE_FILLEDRECTANGLE:
					xGRcreate_rectangle(event, n);
					break;
				case BUTTONCREATE_FILLEDELLIPSE:
					xGRcreate_ellipse(event, n);
					break;
			}
			break;
		case BUTTONEDIT:
			switch (n) {
				case BUTTONEDIT_MOVE:
					xGRmove(event, n);
					break;
				case BUTTONEDIT_COPY:
					xGRcopy(event, n);
					break;
				case BUTTONEDIT_DELETE:
					xGRdelete(event, n);
					break;
			}
			break;
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRaction_initialize ()
 *					-preapare action procedure for graphic
 *					-this is applicable if only ONE graphic popup 
 *	
 *---------------------------------------------------------------------------
 */
void xGRaction_initialize()
{
	extern XtAppContext mpx_appcontext;
	/*--- action table (name, func) !Caution: XtAddActions removes the name ---*/
	static XtActionsRec graActionsTable[] = {
				{"APCaction_select",       (XtActionProc)xGRbook_one      },  
				{"APCaction_doubleclick",  (XtActionProc)xGRbook_andquit  },  
				{"APCaction_clear",        (XtActionProc)xGRbook_clear    }  
				};
	XtAppAddActions(mpx_appcontext, graActionsTable, XtNumber(graActionsTable));
}
