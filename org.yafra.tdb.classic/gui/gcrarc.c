/*D************************************************************
 * Modul:		GRAPHIC							gcrarc.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcrarc.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gcrarc.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:21  ja
 general version

 * Revision 1.3  94/02/18  10:36:14  10:36:14  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:34  23:54:34  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrarc.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


void xGRcreate_arc(
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
	XArc           arcus;
	XArc           *xa;
	int            typ;
	int            j;
	double         wi, r, mx, my, a1, a2;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_ARC0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_ARC1);
		graglob.eingabe = 2;
	} else if (typ == 2) {
                ok = xGRget_koord(event, &punkt[1]);
                if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_ARC2);
		graglob.eingabe = 3;
	} else if (typ == 3) {
                ok = xGRget_koord(event, &punkt[2]);
                if (!ok) return;
		ok = xGRget_arc(punkt, &arcus);
		if (!ok) return;

		obj.text = 0;
		obj.xpoints = (int *)malloc(sizeof(XArc));
		xa = (XArc *)obj.xpoints;
		memcpy((void *)xa, (void *)&arcus, sizeof(XArc));
		obj.anzRegionPoints = MAXREGOBJ;
		obj.regionPoint = (REGIONPOINT *)malloc(MAXREGOBJ*sizeof(REGIONPOINT));
		a1 = arcus.angle1/64.;
		a2 = arcus.angle2/64.;
		r = arcus.width/2.;
		mx = arcus.x+r;
		my = arcus.y+r;
		for (j=0; j<MAXREGOBJ; j++) {

			wi = (a1+j*a2/(MAXREGOBJ-1))*M_PI/180.;

			obj.regionPoint[j].p.x =  cos(wi)*r + mx;
			obj.regionPoint[j].p.y = -sin(wi)*r + my;
			obj.regionPoint[j].n   = 0;
		}
		if (n == BUTTONCREATE_ARC) {
			obj.was = OBJ_ARC;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indwidth;
			obj.gc3 = graglob.indstyle;

		} else {
			obj.was = OBJ_FILLEDARC;
			obj.gc1 = graglob.indcolor;
			obj.gc2 = graglob.indpattern;
			obj.gc3 = 0;
		}

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_ARC0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
