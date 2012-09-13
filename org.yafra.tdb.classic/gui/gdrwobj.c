/*D************************************************************
 * Modul:		GRAPHIC							gdrwobj.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwobj.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


void xGRdraw_object(
GRAFOBJ *obj
)

{
	extern Display    *display;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;

	GC gc;
	int ind1, ind2, ind3;

	switch (obj->was) {
		case OBJ_POINT:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzLinewidth) ind2 = graglob.anzLinewidth-1;
			ind3 = obj->gc3;
			if (ind3 >= graglob.anzLinestyle) ind3 = graglob.anzLinestyle-1;
			gc = graglob.GCZ[ind1][ind2][ind3];
			XDrawPoints(display, grawindows.graphik, gc,
			(XPoint *)obj->xpoints, 1, CoordModeOrigin);
			break;

		case OBJ_LINE:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzLinewidth) ind2 = graglob.anzLinewidth-1;
			ind3 = obj->gc3;
			if (ind3 >= graglob.anzLinestyle) ind3 = graglob.anzLinestyle-1;
			gc = graglob.GCZ[ind1][ind2][ind3];
			XDrawLines(display, grawindows.graphik, gc,
			(XPoint *)obj->xpoints, 2, CoordModeOrigin);
			break;

		case TEMP_LINE:
			gc = graglob.gc_cursor;
			XDrawLines(display, grawindows.graphik, gc,
			(XPoint *)obj->xpoints, 2, CoordModeOrigin);
			break;

		case OBJ_RECTANGLE:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzLinewidth) ind2 = graglob.anzLinewidth-1;
			ind3 = obj->gc3;
			if (ind3 >= graglob.anzLinestyle) ind3 = graglob.anzLinestyle-1;
			gc = graglob.GCZ[ind1][ind2][ind3];
			XDrawRectangles(display, grawindows.graphik, gc,
			(XRectangle *)obj->xpoints, 1);
			break;

		case TEMP_RECTANGLE:
			gc = graglob.gc_cursor;
			XDrawRectangles(display, grawindows.graphik, gc,
			(XRectangle *)obj->xpoints, 1);
			break;

		case OBJ_FILLEDRECTANGLE:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzPattern) ind2 = graglob.anzPattern-1;
			gc = graglob.GCP[ind1][ind2];
			XFillRectangles(display, grawindows.graphik, gc,
			(XRectangle *)obj->xpoints, 1);
			break;

		case OBJ_ELLIPSE:
		case OBJ_ARC:
		case OBJ_CIRCLE:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzLinewidth) ind2 = graglob.anzLinewidth-1;
			ind3 = obj->gc3;
			if (ind3 >= graglob.anzLinestyle) ind3 = graglob.anzLinestyle-1;
			gc = graglob.GCZ[ind1][ind2][ind3];
			XDrawArcs(display, grawindows.graphik, gc,
			(XArc *)obj->xpoints, 1);
			break;

		case TEMP_CIRCLE:
			gc = graglob.gc_cursor;
			XDrawArcs(display, grawindows.graphik, gc,
			(XArc *)obj->xpoints, 1);
			break;

		case OBJ_FILLEDELLIPSE:
		case OBJ_FILLEDARC:
		case OBJ_FILLEDCIRCLE:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzPattern) ind2 = graglob.anzPattern-1;
			gc = graglob.GCP[ind1][ind2];
			XFillArcs(display, grawindows.graphik, gc,
			(XArc *)obj->xpoints, 1);
			break;

		case OBJ_TEXT:
			ind1 = obj->gc1;
			if (ind1 >= graglob.anzColors) ind1 = graglob.anzColors-1;
			ind2 = obj->gc2;
			if (ind2 >= graglob.anzFonts) ind2 = graglob.anzFonts-1;
			gc = graglob.GCF[ind1][ind2];
			XDrawString(display, grawindows.graphik, gc,
			obj->xpoints[0], obj->xpoints[1],
			obj->text, (int)obj->gc3);
			break;

		case TEMP_TEXT:
			gc = graglob.gc_cursor;
			XDrawString(display, grawindows.graphik, gc,
			obj->xpoints[0], obj->xpoints[1],
			obj->text, (int)obj->gc3);
			break;
	}
}
