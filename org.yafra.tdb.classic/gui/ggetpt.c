/*D************************************************************
 * Modul:		GRAPHIC							ggetpt.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/ggetpt.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: ggetpt.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:51  ja
 general version

 * Revision 1.3  94/02/18  10:38:13  10:38:13  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:41  00:25:41  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ggetpt.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



/* erhaelt Punkt Koordinate in Pixel, liefert Snap gerechte Koordinate in mm  */
/* case 0: Snapoption Grid gewaehlt. Wenn kein Raster eingegeben wurde, wird  */
/*         der erhaltene Punkt zurueckgegeben.                                */
/* case 1: Snapoption Point gewaehlt. Wenn im Punkte Puffer Werte sind, wird  */
/*         der dem erhaltenen Punkt am naechsten gelegene Punkt des Punkte-   */
/*         puffers zurueckgegeben, andernfalls wird -1 zurueckgegeben.        */
/* case 2 : Snapoption Snap not gewaehlt. Der erhaltene Punkt = return Wert   */
/*                                                                            */


void xGRget_point(
int x,
int y,
XPoint *punkt
)

{
	extern GRAGLOB graglob;

	WCVALUE ag;

	punkt->x = x;
	punkt->y = y;

	switch(graglob.indsnap) {

	/* SNAP gridded */
	case BUTTONSNAP_GRID:

		if (graglob.showGrid) {
			ag = (WCVALUE)punkt->x/(WCVALUE)graglob.griddist;
			if((ag-(int)ag) > 0.5) {
				punkt->x = ((int)ag+1)*graglob.griddist;
			} else {
				punkt->x = ((int)ag  )*graglob.griddist;
			}

			ag = (WCVALUE)punkt->y/(WCVALUE)graglob.griddist;
			if((ag-(int)ag) > 0.5) {
				punkt->y = ((int)ag+1)*graglob.griddist;
			} else {
				punkt->y = ((int)ag  )*graglob.griddist;
			}
		} else {
			punkt->x = -1;
			punkt->y = -1;
		}

		return;

	/* SNAP point */
	case BUTTONSNAP_POINT:
		xGRfind_point(punkt);
		return;

	/* no SNAP */
	case BUTTONSNAP_NONE:
	default:
		return;

	}
}
