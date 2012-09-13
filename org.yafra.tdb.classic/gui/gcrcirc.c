/*D************************************************************
 * Modul:		GRAPHIC							gcrcirc.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcrcirc.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gcrcirc.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:22  ja
 general version

 * Revision 1.3  94/02/18  10:36:15  10:36:15  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:36  23:54:36  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrcirc.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



void xGRcreate_circle(
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
	int            j;
	double         wi;
	WCVALUE        r;
	XArc           *xa;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_CIRCLE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_CIRCLE1);
		graglob.eingabe = 2;
	} else if (typ == 2) {
                ok = xGRget_koord(event, &punkt[1]);
                if (!ok) return;
		r = (WCVALUE)hypot((double)(punkt[0].y - punkt[1].y),
		                   (double)(punkt[0].x - punkt[1].x));
		if (r < (WCVALUE)hypot(EPS, EPS)) return;

		obj.text = 0;
		obj.xpoints = (int *)malloc(sizeof(XArc));
		xa = (XArc *)obj.xpoints;
		xa->x = punkt[0].x - r;
		xa->y = punkt[0].y - r;
		xa->width  = 2 * r;
		xa->height = 2 * r;
		xa->angle1 = 0;
		xa->angle2 = 64*360;
		obj.anzRegionPoints = 5;
		obj.regionPoint = (REGIONPOINT *)malloc(5*sizeof(REGIONPOINT));
		obj.regionPoint[0].p.x = punkt[0].x;
		obj.regionPoint[0].p.y = punkt[0].y;
		obj.regionPoint[0].n   = 0;
		for (j=0; j<obj.anzRegionPoints-1; j++) {

			wi = (double)(j*2./(obj.anzRegionPoints-1)*M_PI);

			obj.regionPoint[j+1].p.x =  cos(wi)*r + punkt[0].x;
			obj.regionPoint[j+1].p.y = -sin(wi)*r + punkt[0].y;
			obj.regionPoint[j+1].n = 0;
		}
		if (n == BUTTONCREATE_CIRCLE) {
			obj.was = OBJ_CIRCLE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indwidth;
			obj.gc3 = graglob.indstyle;

		} else {
			obj.was = OBJ_FILLEDCIRCLE;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indpattern;
			obj.gc3 = 0;
		}

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_CIRCLE0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
