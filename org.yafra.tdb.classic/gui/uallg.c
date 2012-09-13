/*D***********************************************************
 * Modul:     GRA                             uallg.c                            
 *                                                            
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uallg.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: uallg.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:30  ja
 general version

 * Revision 1.5  94/02/22  16:10:38  16:10:38  ja (Jean-Marc Adam)
 * Function header for PSCASE tools
 * 
 * Revision 1.4  94/02/18  10:40:07  10:40:07  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/11/09  16:54:36  16:54:36  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.2  92/11/27  02:38:20  02:38:20  mw (Administrator)
 * "new include file"
 * 
 * Revision 1.1  92/11/27  02:29:11  02:29:11  mw ()
 * Initial revision
 * 
*/
#include <math.h>
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uallg.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";


#define EPS 1.E-200

/*F--------------------------------------------------------------------------
 *  Function:	geradeschnitt ()
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int geradeschnitt( double a1, double b1, double c1, double a2, double b2, double c2, double *x, double *y)
{
	double det;

	det = b1*a2-b2*a1;

	if (fabs(det) < EPS) return(0);

	*x = (b2*c1-b1*c2)/det;
	*y = (c2*a1-c1*a2)/det;

	return(1);
}



/*F--------------------------------------------------------------------------
 *  Function:	geradegl ()
 * 			bestimmt die Geradengleichungskoeffizienten aus
 *          zwei Punktepaaren  (AX + BY + C = 0)
 *
 * x1       X-Koordinate 1.Punkt
 * y1       Y-Koordinate 1.Punkt                               
 * x2       X-Koordinate 2.Punkt                               
 * y2       Y-Koordinate 2.Punkt                              
 * a       X-Koeffizient                                      
 * b       Y-Koeffizient                                      
 * c       Absolutglied                                       
 *
 * return   kein Wert                                         
 *---------------------------------------------------------------------------
 */
void geradegl( double x1, double y1, double x2, double y2,
               double *a, double *b, double *c)
{
	double dx, dy;
	
	dx = x2-x1;
	dy = y2-y1;

	*a = -dy;
	*b =  dx;
	*c = x1*dy-y1*dx;
}



/*F--------------------------------------------------------------------------
 * Function:  punktkla 
 *            Punkte Klasse                                          
 *---------------------------------------------------------------------------
 */
int punktkla( double *xalt, double *yalt, int anzalt, double *xneu,
              double *yneu, double px1, double py1, double px2, double py2)
{
	int i, anzneu;
	double a, b, c;

	anzneu=0;

	geradegl(px1, py1, px2, py2, &a, &b, &c);

	for(i=0; i<anzalt; i++) {
		if(a*xalt[i]+b*yalt[i]+c <= 0) {
			xneu[anzneu]=xalt[i];
			yneu[anzneu]=yalt[i];
			anzneu++;
		}
	}
	return(anzneu);
}
