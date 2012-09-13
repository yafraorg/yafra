/*D************************************************************
 * Modul:		GRAPHIC							gfdobj.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdobj.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gfdobj.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:40  ja
 general version

 * Revision 1.3  94/02/18  10:38:01  10:38:01  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:31  00:16:31  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdobj.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



/* Alle Regionpunkte m�ssen vollst�ndig in der Pickbox liegen            */


Boolean xGRfind_object(
XPoint punkt,
GRAFOBJ **grafobj
)

{
	extern GRAGLOB graglob;
	extern GRAWIDGETS grawidgets;

	GRAFOBJ *obj;
	short x1, x2, y1, y2;
	Boolean ok;

	*grafobj = 0;
	if (graglob.indsnap == BUTTONSNAP_POINT) {

		x1 = punkt.x-graglob.pickbox.x;
		x2 = punkt.x+graglob.pickbox.x;
		y1 = punkt.y-graglob.pickbox.y;
		y2 = punkt.y+graglob.pickbox.y;

		obj = xGRfind_object_koord(x1, x2, y1, y2);
		if (obj) {
			ok = xGRfind_regiongraf(obj);
			if (!ok) {
				*grafobj = obj;
				return(True);
			} else {
				xUIfehler(XGRREGIONDEFINED, grawidgets.shell);
				return(False);
			}
		} else {
			xUIfehler(XGRIDENTOBJECT, grawidgets.shell);
			return(False);
		}
	} else {
		xUIfehler(XGRIDENTSNAP, grawidgets.shell);
		return(False);
	}
}
