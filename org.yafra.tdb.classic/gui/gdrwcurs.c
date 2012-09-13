/*D************************************************************
 * Modul:		GRAPHIC							gdrwcurs.c
 *
 *					Draw the cursor lines streched to window limits	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdrwcurs.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gdrwcurs.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:35  ja
 general version

 * Revision 1.3  94/02/18  10:37:55  10:37:55  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:16  00:16:16  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwcurs.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



void xGRdraw_cursor(
)

{
	extern Display    *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;

	int x, y;

	x = (int)graglob.Limitx;
	y = (int)graglob.cursor_data.y;
	XDrawLine(display, grawindows.graphik, graglob.gc_cursor, 0, y, x, y);

	x = (int)graglob.cursor_data.x;
	y = (int)graglob.Limity;
	XDrawLine(display, grawindows.graphik, graglob.gc_cursor, x, 0, x, y);
}
