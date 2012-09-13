/*D************************************************************
 * Modul:		GRAPHIC							gcrrect.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcrrect.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gcrrect.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:26  ja
 general version

 * Revision 1.3  94/02/18  10:37:45  10:37:45  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:15:44  00:15:44  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrrect.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


void xGRcreate_rectangle(
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
	GRAFOBJ        obj;
	int            typ;
	XRectangle     *xr;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_RECTANGLE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_RECTANGLE1);
		graglob.eingabe = 2;
	} else if (typ == 2) {
                ok = xGRget_koord(event, &punkt[1]);
                if (!ok) return;
		ok = xGRcheck_rectangle();
                if (!ok) {
			xUIbeep(grawidgets.antwort, 0, 0, 0);
			return;
		}

		obj.text = 0;
		obj.xpoints = (int *)malloc(sizeof(XRectangle));
		xr = (XRectangle *)obj.xpoints;
		xGRobjkoord_rectangle(xr);
		obj.anzRegionPoints = 4;
		obj.regionPoint = (REGIONPOINT *)malloc(4*sizeof(REGIONPOINT));
		obj.regionPoint[0].p.x = punkt[0].x;
		obj.regionPoint[0].p.y = punkt[0].y;
		obj.regionPoint[0].n   = 0;
		obj.regionPoint[1].p.x = punkt[1].x;
		obj.regionPoint[1].p.y = punkt[0].y;
		obj.regionPoint[1].n   = 0;
		obj.regionPoint[2].p.x = punkt[1].x;
		obj.regionPoint[2].p.y = punkt[1].y;
		obj.regionPoint[2].n   = 0;
		obj.regionPoint[3].p.x = punkt[0].x;
		obj.regionPoint[3].p.y = punkt[1].y;
		obj.regionPoint[3].n   = 0;
		if (n == BUTTONCREATE_RECTANGLE) {
			obj.was = OBJ_RECTANGLE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indwidth;
			obj.gc3 = graglob.indstyle;
		} else {
			obj.was = OBJ_FILLEDRECTANGLE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indpattern;
			obj.gc3 = 0;
		}

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_RECTANGLE0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
