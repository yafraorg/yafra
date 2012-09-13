/*D************************************************************
 * Modul:		GRAPHIC							gfdpoint.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdpoint.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gfdpoint.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:42  ja
 general version

 * Revision 1.3  94/02/18  10:38:02  10:38:02  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:34  00:16:34  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdpoint.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


void xGRfind_point(
XPoint *point
)

{
	extern unsigned long anzregionPoints;
	extern REGIONPOINT *regionPoints;

	double lot, minlot;
	unsigned long i;
	REGIONPOINT *nearest, *akt;

	nearest = 0;
	minlot = HUGE_VAL;
	for (i=0; i<anzregionPoints; i++) {
		akt = &regionPoints[i];
		lot = hypot((double)(point->y - akt->p.y),
		            (double)(point->x - akt->p.x));
		if (lot<minlot) {
			nearest = akt;
			minlot = lot;
		}
	}
	if (nearest) {
		point->x = nearest->p.x;
		point->y = nearest->p.y;
	} else {
		point->x = -1;
		point->y = -1;
	}
}
