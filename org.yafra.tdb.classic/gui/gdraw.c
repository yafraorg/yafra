/*D************************************************************
 * Modul:		GRAPHIC							gdraw.c
 *
 *					General draw functions for all objects	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdraw.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gdraw.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:34  ja
 general version

 * Revision 1.3  94/02/18  10:37:54  10:37:54  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:15  00:16:15  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdraw.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


XtCallbackProc xGRdraw(
Widget w,
XtPointer input,
XtPointer output
)

{

	extern long anzgrafObj;
	extern long anzregObj;
	extern GRAFOBJ *grafObj;
	extern REGOBJ  *regObj;
	extern Display *display;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;
	extern GRAGLOB graglob;
	extern Boolean undraw;

	XEvent         get_event;
	GRAFOBJ        *obj;
	REGOBJ         *reg;
	long           z;
	XmAnyCallbackStruct *cb;

	cb = (XmAnyCallbackStruct *)output;

	/* Expose Event Cursor setzen */
	XDefineCursor(display, grawindows.graphik, graglob.wait);

	/* Fensterflaeche loeschen */
	XClearWindow(display, grawindows.graphik);

	/* Regionobjekte zeichnen */
	for(z=0; z<anzregObj; z++) {
		reg = &regObj[z];
		xGRdraw_region(reg);
	}

	/* Graphikobjekte zeichnen */
	for(z=0; z<anzgrafObj; z++) {
		obj = &grafObj[z];
		xGRdraw_object(obj);
	}

	if (graglob.tempObj) {
		xGRdraw_tempobject();
	}

	/* Regionpunkte zeichnen */
	if (graglob.showPoints) {
		xGRdraw_regionpoints();
	}

	/* Gitter zeichnen */
	if (graglob.showGrid) {
		xGRdraw_grid();
	}

	/* altes Cursor Zeichen reinstallieren */
	XDefineCursor(display, grawindows.graphik, graglob.work);

	/* alle Expose Events fuer Grafik Window aus Queue entfernen, damit */
	/* nicht mehrfach gezeichnet wird, wenn z.B. 2 Fenster ueber dem    */
	/* Grafikwindow und Scrollbar lagen.                                */
	while(XCheckWindowEvent(display, grawindows.graphik, ExposureMask, &get_event));

	undraw = False;
}
