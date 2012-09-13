/*D************************************************************
 * Modul:		GRAPHIC							gcpobj.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gcpobj.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gcpobj.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:20  ja
 general version

 * Revision 1.3  94/02/18  10:36:12  10:36:12  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:32  23:54:32  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcpobj.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


void xGRcopy_object(
XPoint von,
XPoint nach,
GRAFOBJ *tempObj,
int tog
)

{
	extern GRAGLOB graglob;

	GRAFOBJ new;
	GRAFOBJ *cop;
	short dx;
	short dy;
	int i;
	XArc *xa;
	XRectangle *xr;
	XPoint *xp;
	unsigned long len;

	if (tog == BUTTONEDIT_MOVE) {
		cop = tempObj;
	} else {
		cop = &new;
		memcpy((void *)cop, (void*)tempObj, sizeof(GRAFOBJ));
		switch (cop->was) {
			case OBJ_TEXT:
				len = 2*sizeof(int);
				break;
			case OBJ_POINT:
				len = sizeof(XPoint);
				break;
			case OBJ_LINE:
				len = 2*sizeof(XPoint);
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				len = sizeof(XRectangle);
				break;
			case OBJ_ARC:
			case OBJ_FILLEDARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDCIRCLE:
			case OBJ_ELLIPSE:
			case OBJ_FILLEDELLIPSE:
				len = sizeof(XArc);
				break;
		}
		cop->xpoints = (int *)malloc(len);
		cop->regionPoint =
		(REGIONPOINT *)malloc(cop->anzRegionPoints*sizeof(REGIONPOINT));
		memcpy((void *)cop->xpoints, (void *)tempObj->xpoints, len);
		memcpy((void *)cop->regionPoint, (void *)tempObj->regionPoint,
		tempObj->anzRegionPoints*sizeof(REGIONPOINT));
	}
	dx = nach.x - von.x;
	dy = nach.y - von.y;

	switch (cop->was) {
		case OBJ_TEXT:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indfont;
			cop->xpoints[0] += dx;
			cop->xpoints[1] += dy;
			break;
		case OBJ_POINT:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indwidth;
			cop->gc3 = graglob.indstyle;
			xp = (XPoint *)cop->xpoints;
			xp->x += dx;
			xp->y += dy;
			break;
		case OBJ_LINE:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indwidth;
			cop->gc3 = graglob.indstyle;
			xp = (XPoint *)cop->xpoints;
			xp->x += dx;
			xp->y += dy;
			xp++;
			xp->x += dx;
			xp->y += dy;
			break;
		case OBJ_RECTANGLE:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indwidth;
			cop->gc3 = graglob.indstyle;
			xr = (XRectangle *)cop->xpoints;
			xr->x += dx;
			xr->y += dy;
			break;
		case OBJ_FILLEDRECTANGLE:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indpattern;
			xr = (XRectangle *)cop->xpoints;
			xr->x += dx;
			xr->y += dy;
			break;
		case OBJ_ARC:
		case OBJ_CIRCLE:
		case OBJ_ELLIPSE:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indwidth;
			cop->gc3 = graglob.indstyle;
			xa = (XArc *)cop->xpoints;
			xa->x += dx;
			xa->y += dy;
			break;
		case OBJ_FILLEDARC:
		case OBJ_FILLEDCIRCLE:
		case OBJ_FILLEDELLIPSE:
			cop->gc1 = graglob.indcolor;
			cop->gc2 = graglob.indpattern;
			xa = (XArc *)cop->xpoints;
			xa->x += dx;
			xa->y += dy;
			break;
	}
	for (i=0; i<cop->anzRegionPoints; i++) {
		cop->regionPoint[i].p.x += dx;
		cop->regionPoint[i].p.y += dy;
		cop->regionPoint[i].n = 0;
		if (tog == BUTTONEDIT_MOVE) {
			xGRcreate_regionpoint(&cop->regionPoint[i]);
		}
	}
	if (tog == BUTTONEDIT_COPY) {
		xGRcreate_grafobj(cop);
	}
}
