/*D************************************************************
 * Modul:		GRAPHIC							gcrtext.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gcrtext.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gcrtext.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:29  ja
 general version

 * Revision 1.3  94/02/18  10:37:48  10:37:48  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:15:51  00:15:51  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrtext.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


void xGRcreate_text(
XEvent *event,
int n
)

{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB graglob;
	extern XPoint   punkt[];


	Boolean        ok;
	int            typ;
	GRAFOBJ        obj;
	XFontStruct    *afont;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_TEXT0);
		XtSetKeyboardFocus(grawidgets.textfeld, grawidgets.antwort);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		if (event->xany.window == XtWindow(grawidgets.antwort)) {
			graglob.antwort = XmTextGetString(grawidgets.antwort);
			XmTextSetString(grawidgets.frage, FRAGE_TEXT1);
			if (strlen(graglob.antwort) > MAXANTWORT) {
				XtFree((void *)graglob.antwort);
				return;
			}
			graglob.eingabe = 2;
		}
	} else if (typ == 2) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;

		obj.was = OBJ_TEXT;
		obj.text = graglob.antwort;
		obj.gc1 = graglob.indcolor;
		obj.gc2 = graglob.indfont;
		obj.gc3 = (unsigned char)strlen(graglob.antwort);
		obj.xpoints = (int *)malloc(2*sizeof(int));
		obj.xpoints[0] = punkt[0].x;
		obj.xpoints[1] = punkt[0].y;

		afont = (XFontStruct *)&graglob.fonts[obj.gc2];
		/*
		obj.graVal[1].x =
		(WCVALUE)XTextWidth(afont, obj.text, (int)obj.gc3)/graglob.xfak;
		obj.graVal[1].y =
		(WCVALUE)(afont->max_bounds.ascent+afont->max_bounds.descent)/
		graglob.yfak;

		obj.graVal[2].x = graglob.zoomfaktor;
		*/

		obj.anzRegionPoints = 1;
		obj.regionPoint = (REGIONPOINT *)malloc(1*sizeof(REGIONPOINT));
		obj.regionPoint[0].p.x = punkt[0].x;
		obj.regionPoint[0].p.y = punkt[0].y;
		obj.regionPoint[0].n = 0;

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_TEXT0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
