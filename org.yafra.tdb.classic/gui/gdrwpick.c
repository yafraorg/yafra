/*D************************************************************
 * Modul:		GRAPHIC							gdrwpick.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gdrwpick.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: gdrwpick.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:37  ja
 general version

 * Revision 1.3  94/02/18  10:37:57  10:37:57  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:21  00:16:21  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwpick.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



void xGRdraw_pickbox(
)

{
	extern Display    *display;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;

	XDrawRectangle(display, grawindows.graphik, graglob.gc_cursor,
	(int)(graglob.cursor_data.x - graglob.pickbox.x),
	(int)(graglob.cursor_data.y - graglob.pickbox.y),
	(unsigned int)(2 * graglob.pickbox.x),
	(unsigned int)(2 * graglob.pickbox.y));
}
