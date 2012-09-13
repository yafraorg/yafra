/*D************************************************************
 * Modul:		GRAPHIC							gfdobjko.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdobjko.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gfdobjko.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:41  ja
 general version

 * Revision 1.3  94/02/18  10:38:02  10:38:02  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:32  00:16:32  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdobjko.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



GRAFOBJ *xGRfind_object_koord(
short x1,
short x2,
short y1,
short y2
)

{
	extern long anzgrafObj;
	extern GRAFOBJ *grafObj;
	extern GRAWIDGETS grawidgets;

	long z, j;
	GRAFOBJ *akt, *aktobj;
	Boolean ok, found;
	short mx, my;
	double mindist, dist;

	mx = (x1+x2)/2;
	my = (y1+y2)/2;
	mindist = 1.e300;
	found = False;
	for(z=0; z<anzgrafObj; z++) {
		akt = &grafObj[z];
		ok = False;
                for(j=0; j<akt->anzRegionPoints; j++) {
			if (x1 <= akt->regionPoint[j].p.x &&
			    x2 >= akt->regionPoint[j].p.x &&
			    y1 <= akt->regionPoint[j].p.y &&
			    y2 >= akt->regionPoint[j].p.y)
				ok = True;
		}
		if (ok) {
			dist = 0;
                	for(j=0; j<akt->anzRegionPoints; j++) {
				dist += hypot(
				(double)(akt->regionPoint[j].p.y-my),
			        (double)(akt->regionPoint[j].p.x-mx));
			}
			if (dist < mindist) {
				mindist = dist;
				aktobj = akt;
				found = True;
			}
		}
	}
	if (found) {
		return(aktobj);
	} else {
		xUIbeep(grawidgets.antwort, 0, 0, 0);
		return(0);
	}
}
