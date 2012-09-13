/*D************************************************************
 * Modul:		GRAPHIC							gdrwgrid.c
 *
 *					Draw a grid over the drawing area	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdrwgrid.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gdrwgrid.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:36  ja
 general version

 * Revision 1.4  94/02/18  10:37:56  10:37:56  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/08/21  00:16:18  00:16:18  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwgrid.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



void xGRdraw_grid(void)
{
	extern Display    *display;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;

	int g, end, range;

	/* vertikale Gitterlinien */
	end = (int)graglob.Limity;
	range = (int)graglob.Limitx;
	for (g=0; g<range; g+=graglob.griddist)
		XDrawLine(display, grawindows.graphik, graglob.gc_grid, g, 0, g, end);

	/* horizontale Gitterlinien */
	end = (int)graglob.Limitx;
	range = (int)graglob.Limity;
	for (g=0; g<=range; g+=graglob.griddist)
		XDrawLine(display, grawindows.graphik, graglob.gc_grid, 0, g, end, g);
}
