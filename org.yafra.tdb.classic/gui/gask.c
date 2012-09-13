/*D************************************************************
 * Modul:		GRAPHIC							gask.c
 *
 *					Ask user for input> Alphanum option	are entered.
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gask.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gask.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:13  ja
 general version

 * Revision 1.4  94/02/18  10:36:07  10:36:07  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/08/20  23:54:19  23:54:19  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gask.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



void xGRask(
XEvent *event,
int n
)

{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB graglob;
	extern GRAFOBJ *grafObj;

	static char    *antwort;

	WCVALUE        a, b;
	short          m;
	GRAFOBJ        obj;
	int            typ;
	Boolean        redraw;
	char           *ptr;
	unsigned int   width, height;
	Arg            args[2];

	switch (n) {
		case BUTTONDEFINE_GRID:
			ptr = FRAGE_GRID0;
			break;
		case BUTTONDEFINE_PICKBOX:
			ptr = FRAGE_PICKBOX0;
			break;
		case BUTTONDEFINE_DRAWAREA:
			ptr = FRAGE_DRAWAREA0;
			break;
		case BUTTONDEFINE_POINTS:
			ptr = FRAGE_POINTS0;
			break;
	}
	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, ptr);
		XtSetKeyboardFocus(grawidgets.textfeld, grawidgets.antwort);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		if (event->xany.window == XtWindow(grawidgets.antwort)) {
			antwort = XmTextGetString(grawidgets.antwort);
			switch (n) {
				case BUTTONDEFINE_GRID:
					redraw = xGRvalues(&graglob.griddist,
					antwort, XGRMM);
					if (graglob.griddist > 0.) {
						graglob.showGrid = True;
					} else {
						graglob.showGrid = False;
					}
					break;
				case BUTTONDEFINE_PICKBOX:
					m = graglob.pickbox.x;
					redraw = xGRvalues(&m, antwort, XGRPIXEL);
					graglob.pickbox.x = m;
					graglob.pickbox.y = m;
					if (graglob.pickbox.x > 0) {
						graglob.showPickbox = True;
					} else {
						graglob.showPickbox = False;
					}
					redraw = False;
					break;
				case BUTTONDEFINE_DRAWAREA:
					if (strcmp(antwort, "A0")) {
						graglob.Limitx = 1189;
						graglob.Limity =  841;
					}
					if (strcmp(antwort, "A1")) {
						graglob.Limitx =  841;
						graglob.Limity =  594;
					}
					if (strcmp(antwort, "A2")) {
						graglob.Limitx =  594;
						graglob.Limity =  420;
					}
					if (strcmp(antwort, "A3")) {
						graglob.Limitx =  420;
						graglob.Limity =  297;
					}
					if (strcmp(antwort, "A4")) {
						graglob.Limitx =  297;
						graglob.Limity =  210;
					}
					if (strcmp(antwort, "A5")) {
						graglob.Limitx =  210;
						graglob.Limity =  148;
					}
					if (sscanf(antwort, "%f &f", &a, &b) ==
					2) {
						if (a>0.0 && a<32000.0 &&
						    b>0.0 && b<32000.0) {
							graglob.Limitx = a;
							graglob.Limity = b;
						}
					}
					redraw = True;
					graglob.Limitx =
					(short)(graglob.Limitx*graglob.xfak);
					graglob.Limity =
					(short)(graglob.Limity*graglob.yfak);
					/* 1.Graphikdatensatz ist immer der */
					/* Drawing Area Record 'D'          */
					grafObj[0].was = OBJ_DRAWINGAREA;
					grafObj[0].gc1 = 0;
					grafObj[0].gc2 = 0;
					grafObj[0].gc3 = 0;
					grafObj[0].text = 0;
					grafObj[0].xpoints[0] = graglob.Limitx;
					grafObj[0].xpoints[1] = graglob.Limity;
					grafObj[0].anzRegionPoints = 4;
					grafObj[0].regionPoint[0].p.x = 0;
					grafObj[0].regionPoint[0].p.y = 0;
					grafObj[0].regionPoint[1].p.x = graglob.Limitx;
					grafObj[0].regionPoint[1].p.y = 0;
					grafObj[0].regionPoint[2].p.x = graglob.Limitx;
					grafObj[0].regionPoint[2].p.y = graglob.Limity;
					grafObj[0].regionPoint[3].p.x = 0;
					grafObj[0].regionPoint[3].p.y = graglob.Limity;

					width = (unsigned)(graglob.Limitx);
					height = (unsigned)(graglob.Limity);
					XtSetArg(args[0], XmNwidth,  width);
					XtSetArg(args[1], XmNheight, height);
					XtSetValues(grawidgets.graphik,
					args, 2);
					break;
				case BUTTONDEFINE_POINTS:
					redraw = xGRvalues(&graglob.RadiusPoints,
					antwort, XGRPIXEL);
					if (graglob.RadiusPoints > 0) {
						graglob.showPoints = True;
					} else {
						graglob.showPoints = False;
					}
					break;
			}
			XmTextSetString(grawidgets.frage, "");
			XmTextSetString(grawidgets.antwort, "");
			graglob.eingabe = 0;
			graglob.aktbox = BUTTONNONE;
			graglob.akttog = BUTTONNONE;
			XtFree((void *)antwort);
			if (redraw) {
				XClearArea(display, grawindows.graphik,
				0, 0, 0, 0, True);
			}
		}
	}
}
