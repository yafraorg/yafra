/*D************************************************************
 * Modul:		GRAPHIC							gdrwtemp.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gdrwtemp.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gdrwtemp.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:40  ja
 general version

 * Revision 1.3  94/02/18  10:38:00  10:38:00  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:26  00:16:26  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwtemp.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


void xGRdraw_tempobject(
)

{
	extern Display    *display;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;

	switch (graglob.tempObj->was) {
		case OBJ_POINT:
			XDrawPoints(display, grawindows.graphik, graglob.gc_cursor,
			(XPoint *)graglob.tempObj->xpoints, 1, CoordModeOrigin);
			break;

		case OBJ_LINE:
			XDrawLines(display, grawindows.graphik, graglob.gc_cursor,
			(XPoint *)graglob.tempObj->xpoints, 2, CoordModeOrigin);
			break;

		case OBJ_RECTANGLE:
		case OBJ_FILLEDRECTANGLE:
			XDrawRectangles(display, grawindows.graphik, graglob.gc_cursor,
			(XRectangle *)graglob.tempObj->xpoints, 1);
			break;

		case OBJ_ELLIPSE:
		case OBJ_ARC:
		case OBJ_CIRCLE:
		case OBJ_FILLEDELLIPSE:
		case OBJ_FILLEDARC:
		case OBJ_FILLEDCIRCLE:
			XDrawArcs(display, grawindows.graphik, graglob.gc_cursor,
			(XArc *)graglob.tempObj->xpoints, 1);
			break;

		case OBJ_TEXT:
			XDrawString(display, grawindows.graphik, graglob.gc_cursor,
			graglob.tempObj->xpoints[0], graglob.tempObj->xpoints[1],
			graglob.tempObj->text, (int)graglob.tempObj->gc3);
			break;

	}
}
