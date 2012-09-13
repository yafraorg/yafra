/*D************************************************************
 * Modul:		GRAPHIC							gcrline.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcrline.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gcrline.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:24  ja
 general version

 * Revision 1.3  94/02/18  10:36:19  10:36:19  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:42  23:54:42  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrline.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


void xGRcreate_line(
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
	XPoint         *xp;

	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_LINE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_LINE1);
		graglob.eingabe = 2;
	} else if (typ == 2) {
                ok = xGRget_koord(event, &punkt[1]);
                if (!ok) return;

		obj.was = OBJ_LINE;
		obj.text = 0;
		obj.gc1 = graglob.indcolor;
		obj.gc2 = graglob.indwidth;
		obj.gc3 = graglob.indstyle;
		obj.xpoints = (int *)malloc(2*sizeof(XPoint));
		xp = (XPoint *)obj.xpoints;
		xp->x = punkt[0].x;
		xp->y = punkt[0].y;
		xp++;
		xp->x = punkt[1].x;
		xp->y = punkt[1].y;
		obj.anzRegionPoints = 2;
		obj.regionPoint = (REGIONPOINT *)malloc(2*sizeof(REGIONPOINT));
		obj.regionPoint[0].p.x = punkt[0].x;
		obj.regionPoint[0].p.y = punkt[0].y;
		obj.regionPoint[0].n   = 0;
		obj.regionPoint[1].p.x = punkt[1].x;
		obj.regionPoint[1].p.y = punkt[1].y;
		obj.regionPoint[1].n   = 0;

		xGRcreate_grafobj(&obj);

		XmTextSetString(grawidgets.frage, FRAGE_LINE0);
		graglob.eingabe = 1;

		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
}
