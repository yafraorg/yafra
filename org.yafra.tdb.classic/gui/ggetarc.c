/*D************************************************************
 * Modul:		GRAPHIC							ggetarc.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/ggetarc.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: ggetarc.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:48  ja
 general version

 * Revision 1.3  94/02/18  10:38:10  10:38:10  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:38  00:25:38  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ggetarc.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



/***********************************************************************/
/* gegeben sind 3 Punkte auf dem Umfang eines Bogens :                 */
/* 1. Startpunkt des Bogens                                            */
/* 2. beliebiger Punkt auf Umfang                                      */
/* 3. Endpunkt des Bogens                                              */
/* Berechnet werden Mittelpunkt = arcus.x/arcus.y                      */
/*                  Radius      = arcus.r                              */
/*                  Startwinkel = arcus.a1 in pos. Richtung            */
/*                  Endwinkel   = arcus.a2 in pos. Richtung            */
/* Diese 5 Werte werden in der Struktur arc zurueckgegeben             */
/*                                                                     */
/* Erstellt Sept. 1991 WSp                                             */
/***********************************************************************/

Boolean xGRget_arc(
XPoint *punkt,
XArc *arcus
)

{
	extern GRAWIDGETS grawidgets;

	double x1, y1, x2, y2, x3, y3, dummy;
	double xa, ya, xb, yb, mxa, mya, mxb, myb;
	double a1, b1, c1, a2, b2, c2;
	double mx, my, r, w1, w2;
	int i, j;
	Boolean ok;

	x1 = (double)punkt[0].x;
	x2 = (double)punkt[1].x;
	x3 = (double)punkt[2].x;
	y1 = (double)punkt[0].y;
	y2 = (double)punkt[1].y;
	y3 = (double)punkt[2].y;

	j = punktkla(&x2, &y2, 1, &dummy, &dummy, x1, y1, x3, y3);

	xa = (x2+x1)/2.;
	ya = (y2+y1)/2.;
	mxa = y1-y2;
	mya = x2-x1;

	xb = (x2+x3)/2.;
	yb = (y2+y3)/2.;
	mxb = y2-y3;
	myb = x3-x2;

	geradegl(xa, ya, xa+mxa, ya+mya, &a1, &b1, &c1);
	geradegl(xb, yb, xb+mxb, yb+myb, &a2, &b2, &c2);

	i = geradeschnitt(a1, b1, c1, a2, b2, c2, &mx, &my);

	r = hypot(y1-my, x1-mx);

	if (i) {
		arcus->x = mx-r;
		arcus->y = my-r;
		arcus->width = 2*r;
		arcus->height = 2*r;
		w1 = (WCVALUE)atan2(my-y1, x1-mx);
		w2 = (WCVALUE)atan2(my-y3, x3-mx);
		w1 *= 180./M_PI;
		w2 *= 180./M_PI;
		w2 = w2-w1;
		if (j==0) {
			if (w2 < 0) {
				w2 = 360. + w2;
			}
		} else {
			if (w2 > 0) {
				w2 = w2 - 360.;
			}
		}
		arcus->angle1 = 64*w1;
		arcus->angle2 = 64*w2;
		ok = True;
	} else {
		ok = False;
		xUIbeep(grawidgets.antwort, 0, 0, 0);
	}

	return(ok);
}
