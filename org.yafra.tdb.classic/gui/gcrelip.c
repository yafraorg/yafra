/*D************************************************************
 * Modul:		GRAPHIC							gcrelip.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcrelip.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gcrelip.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:23  ja
 general version

 * Revision 1.3  94/02/18  10:36:16  10:36:16  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:38  23:54:38  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrelip.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


void xGRcreate_ellipse(
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
	XArc           *xa;
	XRectangle     *xr;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_ELLIPSE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_ELLIPSE1);
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
		obj.xpoints = (int *)malloc(sizeof(XArc));
		xa = (XArc *)obj.xpoints;
		xr = (XRectangle *)obj.xpoints;
		xGRobjkoord_rectangle(xr);
		xa->angle1 = 0;
		xa->angle2 = 64*360;
		obj.anzRegionPoints = 5;
		obj.regionPoint = (REGIONPOINT *)malloc(5*sizeof(REGIONPOINT));
		obj.regionPoint[0].p.x = punkt[0].x+xa->width/2;
		obj.regionPoint[0].p.y = punkt[0].y+xa->height/2;
		obj.regionPoint[0].n   = 0;
		obj.regionPoint[1].p.x = xa->x;
		obj.regionPoint[1].p.y = xa->y+xa->height/2;
		obj.regionPoint[1].n   = 0;
		obj.regionPoint[2].p.x = xa->x+xa->width;
		obj.regionPoint[2].p.y = xa->y+xa->height/2;
		obj.regionPoint[2].n   = 0;
		obj.regionPoint[3].p.x = xa->x+xa->width/2;
		obj.regionPoint[3].p.y = xa->y;
		obj.regionPoint[3].n   = 0;
		obj.regionPoint[4].p.x = xa->x+xa->width/2;
		obj.regionPoint[4].p.y = xa->y+xa->height;
		obj.regionPoint[4].n   = 0;
		if (n == BUTTONCREATE_ELLIPSE) {
			obj.was = OBJ_ELLIPSE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indwidth;
			obj.gc3 = graglob.indstyle;
		} else {
			obj.was = OBJ_FILLEDELLIPSE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indpattern;
			obj.gc3 = 0;
		}

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_ELLIPSE0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
