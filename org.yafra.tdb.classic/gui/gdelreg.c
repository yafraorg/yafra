/*D************************************************************
 * Modul:		GRAPHIC							gdelreg.c
 *
 *					Delete region:
 *					-Free memory and clear struture members
 *					-Xdestroy region polygons
 *					-Deselect region item in list 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdelreg.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gdelreg.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:34  ja
 general version

 * Revision 1.3  94/02/18  10:37:53  10:37:53  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:10  00:16:10  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdelreg.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



XtCallbackProc xGRdelete_region(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern GRAWIDGETS grawidgets;
	extern REGOBJ *regObj;

	REGOBJ *region, *vater;
	int i;

	Region leer = XCreateRegion();
	Region neu  = XCreateRegion();

	region = (REGOBJ *)Input;

	region->anzEckpunkte = 0;
	XtFree((void *)region->Regionname);
	if (region->Eckpunkte) {
		XtFree((void *)region->Eckpunkte);
	}
	if (region->Eckpunktnum) {
		XtFree((void *)region->Eckpunktnum);
	}
	region->Eckpunkte = 0;

	i = region->indVater;
	if (i != NOVATER) {
		if (region->region) {
			XUnionRegion(region->region, regObj[i].region, neu);
			XUnionRegion(neu, leer, regObj[i].region);
			XDestroyRegion(leer);
			XDestroyRegion(neu);
		}
	}
	if (region->region) {
		XDestroyRegion(region->region);
	}
	region->region = 0;

	if (w) {
		XmListDeselectPos(grawidgets.select, region-regObj+1);
	}
}
