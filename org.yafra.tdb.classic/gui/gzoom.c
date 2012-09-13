/*D************************************************************
 * Modul:		GRAPHIC							gzoom.c
 *
 *					Zoom functions	and geometry scaling 
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gzoom.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: gzoom.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:27  ja
 general version

 * Revision 1.4  94/02/18  10:40:05  10:40:05  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/08/21  00:27:07  00:27:07  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.2  93/08/05  17:08:20  17:08:20  ja (Jean-Marc Adam)
 * "Pixel units incremental mode "
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gzoom.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


#define _ZOOM_NO_      0
#define _ZOOM_ZERO_    1
#define _ZOOM_NEW_     2
#define _ZOOM_MINUS_   3
#define _ZOOM_PLUS_    4

#define ZOOMBYFACT(a,f) ((short)(((WCVALUE)(a)*(f))+0.5) )

/*-------------- STATIC FUNCTIONS -------------------------------------------*/
static void xGRdestroy_regions();
static void xGRzoom_regionpoints(); 

 
/*F--------------------------------------------------------------------------
 *  Function:	xGRzoom_reset()
 *					-Reset zoom size to global limits 
 *					-Reset nb of steps
 *	
 *---------------------------------------------------------------------------
 */
void xGRzoom_reset() 
{
	extern GRAGLOB graglob;
	extern ZOOM		zoom[MAXZOOM];
	extern int		anzZoom;
	extern ZOOM		*aktzoom;
	extern Boolean zoomingflag;

	/*--- forget previous steps ------*/
	anzZoom = 1;
	aktzoom = &zoom[0];
	zoom[0].faktor = 1;
	zoom[0].p[0].x = 0;
	zoom[0].p[0].y = 0;
	zoom[0].p[1].x = graglob.Limitx;
	zoom[0].p[1].y = graglob.Limity;
	zoomingflag = False;             /* permit other operations */ 
}


/*F--------------------------------------------------------------------------
 *  Function:	xGRzoom()
 *					-Action functions performed by menu or pointer click 
 *					-Reset nb of steps
 *	In:			the event,  the callback box	
 *---------------------------------------------------------------------------
 */
void xGRzoom(
XEvent *event,
int n
)

{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB graglob;
	extern XPoint punkt[];
	extern ZOOM	zoom[MAXZOOM];
	extern int	anzZoom;
	extern ZOOM	*aktzoom;
	extern Boolean zoomingflag;

	XPoint		windowsize;
	ZOOM			*newzoom;
	Boolean		ok, redraw ;
	int			typ;
	WCVALUE		wold, hold, wnew, hnew, temp, fak;
	Dimension	widthcurrent, heightcurrent;
	Arg			wargs[2];
	WCVALUE		xcurfak, ycurfak ;

	/*--- init defaults ---*/
	redraw  = _ZOOM_NO_;

	/*--- actions ---------*/
	switch (n) {
		case BUTTONZOOM_START:
			/*--- cancel eventuel new zoom ----*/
			graglob.eingabe = 0;
			zoomingflag = False;
			/*--- go back to start coords ---*/
			newzoom = zoom;
			anzZoom = 1;
			punkt[0].x = newzoom->p[0].x;
			punkt[0].y = newzoom->p[0].y;
			punkt[1].x = newzoom->p[1].x;
			punkt[1].y = newzoom->p[1].y;
			/*--- go back to start factor ---*/
			xcurfak = graglob.xfak;               /*x or y have same scaling */
			xGRinit_factors();                    /*initial values*/
			fak = xcurfak / graglob.xfak ;
			graglob.zoomfaktor = 1./fak;
			newzoom->faktor = 1;
			redraw = _ZOOM_ZERO_;
			break;

		case BUTTONZOOM_ZOOM:
		   	typ = graglob.eingabe;
			if (typ == 0) {
				zoomingflag = True;                         /* Inhibit other operations */ 
				XmTextSetString(grawidgets.frage, FRAGE_ZOOM0);
				graglob.eingabe = 1;
			} else if (typ == 1) {
				ok = xGRget_koord(event, &punkt[0]);
				if (!ok)
					return;                               /*>>> invalid coord */
				XmTextSetString(grawidgets.frage, FRAGE_ZOOM1);
				graglob.eingabe = 2;
			} else if (typ == 2) {
				ok = xGRget_koord(event, &punkt[1]);
				if (!ok) 
					return;                               /*>>> invalid coord */
				XmTextSetString(grawidgets.frage, "");
				XmTextSetString(grawidgets.antwort, "");
				graglob.aktbox = BUTTONNONE;
				graglob.akttog = BUTTONNONE;
				graglob.eingabe = 0;
				zoomingflag = False;             /* permit other operations */ 

				/*--- compute factor -----------------*/
				xGRwidget_graphik_getsize( &windowsize);  		   
				wold = (WCVALUE)windowsize.x ;
				hold = (WCVALUE)windowsize.y ;
#ifdef COMPILE
				wold = aktzoom->p[1].x - aktzoom->p[0].x;
				hold = aktzoom->p[1].y - aktzoom->p[0].y;
#endif			
				wnew = punkt[1].x - punkt[0].x;
				hnew = punkt[1].y - punkt[0].y;
				/*--- take greatest factor and smallest expansion will fit -----*/
				fak = (wnew/wold > hnew/hold)? wnew/wold: hnew/hold;

		     /*--- Limit to max zoom ---------*/
				temp = graglob.xfak / fak;
				if (temp > MAXPIXELMMRATIO)
					{
					xUIbeep( grawidgets.shell, 0, 0, 0); 
					xUIfehler( XGRZOOMLIMITREACHED, grawidgets.shell);
					break;
					}

				graglob.xfak /= fak;
				graglob.yfak /= fak;
				graglob.zoomfaktor = 1./fak;

				/*--- scale x and y with same factor ----*/
				punkt[1].x = punkt[0].x + fak*wold;   
				punkt[1].y = punkt[0].y + fak*hold;   

				/*--- Store this step ----------------*/
				if (anzZoom >= MAXZOOM) {
					xGRzoomstack(zoom, &anzZoom, 1, 1);
				}
				anzZoom = (aktzoom - zoom) +1;   /* fork from this step forget old */
				newzoom = &zoom[anzZoom++];   
				newzoom->faktor = fak;
				newzoom->p[0].x = punkt[0].x;
				newzoom->p[0].y = punkt[0].y;
				newzoom->p[1].x = punkt[1].x;
				newzoom->p[1].y = punkt[1].y;
				redraw = _ZOOM_NEW_;
			}
			break;

		case BUTTONZOOM_LAST:
			/*--- cancel eventuel new zoom ----*/
			graglob.eingabe = 0;
			zoomingflag = False;
			/*-- rotate left in steps -----*/
			if (aktzoom-zoom > 0){
				newzoom = aktzoom-1;
				punkt[0].x = newzoom->p[0].x;
				punkt[0].y = newzoom->p[0].y;
				punkt[1].x = newzoom->p[1].x;
				punkt[1].y = newzoom->p[1].y;
				fak = 1./aktzoom->faktor ;    
				redraw  = _ZOOM_MINUS_;
				graglob.xfak /= fak;
				graglob.yfak /= fak;
				graglob.zoomfaktor = 1./fak;
			} else {
				xUIbeep(grawidgets.shell, 0, 0, 0); 
			}
			break;

		case BUTTONZOOM_NEXT:
			/*--- cancel eventuel new zoom ----*/
			graglob.eingabe = 0;
			zoomingflag = False;
			/*-- rotate right in steps -----*/
			if (aktzoom-zoom < anzZoom-1) {
				newzoom = aktzoom +1;
				punkt[0].x = newzoom->p[0].x;
				punkt[0].y = newzoom->p[0].y;
				punkt[1].x = newzoom->p[1].x;
				punkt[1].y = newzoom->p[1].y;
				fak = newzoom->faktor ;
				graglob.xfak /= fak;
				graglob.yfak /= fak;
				graglob.zoomfaktor = 1./fak;
				redraw  = _ZOOM_PLUS_;
			} else {
				xUIbeep(grawidgets.shell, 0, 0, 0);       /*stop at end */
			}
			break;

		case BUTTONZOOM_RESIZE:
			redraw  = _ZOOM_NO_;
			break;

		case BUTTONZOOM_SCROLL:
			redraw  = _ZOOM_NO_;
			break;
	}


	/*--- Zoom common actions -------------------------*/
	if (redraw) {

#ifdef COMPILE
printf( "\n Step: %d   nbmax: %d ", aktzoom-zoom, anzZoom ); 
printf( "\n Zoomfaktor: %f ", graglob.zoomfaktor ); 
printf( "\n graglob.x-y fak: %f  %f", graglob.xfak, graglob.yfak ); 
printf( "\n punkt[0]: %d, %d     ", punkt[0].x, punkt[0].y ); 
printf( "   punkt[1]: %d, %d     ", punkt[1].x, punkt[1].y ); 
#endif
 
		/*--- destroy region polygons -----*/
		xGRdestroy_regions();
		/*--- scale all coordinates and dependent objects ------*/
		xGRzoom_graphik(); 
		xGRzoom_regionpoints(); 
		xGRzoom_regions(); 
		/*--- New drawing area and scrolled window, triggers RESIZE --*/
		xGRwidget_graphik_resize(False);  		   

		/*--- Center image -----------------*/
		xGRwidget_graphik_scrollpos( (WCVALUE)punkt[0].x / newzoom->faktor,
												(WCVALUE)punkt[0].y  / newzoom->faktor);	
	   
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);

		/*--- set active step -------------*/
		aktzoom = newzoom;
	}
}






/*F--------------------------------------------------------------------------
 *  Function:	xGRzoom_graphik()
 *					-recalculate with new factor and build new region points
 *	
 *---------------------------------------------------------------------------
 */
void xGRzoom_graphik() 
{
	extern long				anzgrafObj;
	extern GRAFOBJ			*grafObj;
	extern GRAGLOB		graglob;

	GRAFOBJDISC discobj;
	GRAFOBJ		*pGrafobj;
	char			was;
	long			i;
	int			j;
	WCVALUE		newfact;
	XPoint		*xp;
	XRectangle	*xr;
	XArc			*xa;
	

	/*--- inits ---------*/
	newfact = graglob.zoomfaktor; 

	/*--- Go for all graphical objects ----------------------------------*/
	for (i=0;  i < anzgrafObj;  i++ ) 
	{
		pGrafobj = &grafObj[i];

		/*--- scale private RegionPoints, serial number not touched --*/
		for (j=0;  j < pGrafobj->anzRegionPoints;  j++) {
			pGrafobj->regionPoint[j].p.x = 
									ZOOMBYFACT(pGrafobj->regionPoint[j].p.x, newfact);
			pGrafobj->regionPoint[j].p.y = 
									ZOOMBYFACT(pGrafobj->regionPoint[j].p.y, newfact);
		}

		/*--- scale grafical x points ------------------------*/
		switch (pGrafobj->was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
				pGrafobj->xpoints[0] = ZOOMBYFACT(pGrafobj->xpoints[0], newfact); 
				pGrafobj->xpoints[1] = ZOOMBYFACT(pGrafobj->xpoints[1], newfact); 
				break;
			case OBJ_POINT:
				xp = (XPoint *)pGrafobj->xpoints;
				xp->x = ZOOMBYFACT(xp->x, newfact); 
				xp->y = ZOOMBYFACT(xp->y, newfact); 
				break;
			case OBJ_LINE:
				xp = (XPoint *)pGrafobj->xpoints;
				xp->x = ZOOMBYFACT(xp->x, newfact); 
				xp->y = ZOOMBYFACT(xp->y, newfact); 
				xp++;
				xp->x = ZOOMBYFACT(xp->x, newfact); 
				xp->y = ZOOMBYFACT(xp->y, newfact); 
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				xr = (XRectangle *)pGrafobj->xpoints;
				xr->x = ZOOMBYFACT(xr->x, newfact); 
				xr->y = ZOOMBYFACT(xr->y, newfact); 
				xr->width  = ZOOMBYFACT(xr->width, newfact); 
				xr->height = ZOOMBYFACT(xr->height, newfact); 
				break;
			case OBJ_ELLIPSE:
			case OBJ_ARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_FILLEDARC:
			case OBJ_FILLEDCIRCLE:
				xa = (XArc *)pGrafobj->xpoints;
				xa->x = ZOOMBYFACT(xa->x, newfact); 
				xa->y = ZOOMBYFACT(xa->y, newfact); 
				xa->width  = ZOOMBYFACT(xa->width, newfact); 
				xa->height = ZOOMBYFACT(xa->height, newfact); 
				break;
		}

		/*--- get Drawing area parameters (already scaled) -----------------*/
		if (i == 0) {
			graglob.Limitx = (short)pGrafobj->xpoints[0] ;
			graglob.Limity = (short)pGrafobj->xpoints[1] ;
		}
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRzoom_regionpoints()
 *					-scale sorted array of region points
 *	
 *---------------------------------------------------------------------------
 */
static void xGRzoom_regionpoints() 
{
	extern unsigned long anzregionPoints;
	extern REGIONPOINT	*regionPoints;
	extern GRAGLOB			graglob;

	REGIONPOINT *akt;
	long			i;

	/*--- scale regionPoints ----------*/
	for (i=0;  i < anzregionPoints;  i++ ) 
	{
		akt = &regionPoints[i];
		akt->p.x = ZOOMBYFACT(akt->p.x, graglob.zoomfaktor) ;
		akt->p.y = ZOOMBYFACT(akt->p.y, graglob.zoomfaktor) ;
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRzoom_regions()
 *					-create new regions with scaled regionPoints
 *					-Pre-condition: Coordinates must have new factor
 *	
 *---------------------------------------------------------------------------
 */
void xGRzoom_regions() 
{
	extern GRAGLOB graglob;
	extern long       anzregObj;
	extern REGOBJ     *regObj;

	REGOBJ		*pReg;
	long			i;
	int			j;
	REGIONPOINT p;


	/*--- Scan all region objects ------------------------*/
	for (i=0;  i < anzregObj;  i++)
	{
		pReg = &regObj[i];

		/*--- Find regionpoints ------------------*/
		for (j=0;  j < pReg->anzEckpunkte;  j++)
		{
			p.p.x = pReg->Eckpunkte[j].x;
			p.p.y = pReg->Eckpunkte[j].y;
			p.n   = pReg->Eckpunktnum[j];

			xGRfind_regionpoint( &p, MODE_NUM);      /* p is updated if n found*/

			pReg->Eckpunkte[j].x = p.p.x;
			pReg->Eckpunkte[j].y = p.p.y;
			pReg->Eckpunktnum[j] = p.n;
		}

		/*--- create new X region polygon ----*/
		if (pReg->anzEckpunkte >= 4) 
			xGRcreate_region( pReg);
	}
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRdestroy_regions()
 *					-remove region objects polygons 
 *	
 *---------------------------------------------------------------------------
 */
static void xGRdestroy_regions() 
{
	extern GRAGLOB			graglob;
	extern REGOBJ	*regObj;
	extern long		anzregObj;

	REGOBJ		*pRO;
	long			i;
	int			v;
	Region		leer ;
	Region		neu  ;

	/*--- scan regionObjects begin at END because parenting -------*/
	for (i=anzregObj-1;  i>=0;  i--)
	{
		pRO = &regObj[i] ;

		v = pRO->indVater;
		if (v != NOVATER) {
			if (pRO->region) {
				leer = XCreateRegion();
				neu  = XCreateRegion();
				XUnionRegion(pRO->region, regObj[v].region, neu);
				XUnionRegion(neu, leer, regObj[v].region);
				XDestroyRegion(leer);
				XDestroyRegion(neu);
			}
		}
		if (pRO->region) {
			XDestroyRegion(pRO->region);
		}
		pRO->region = 0;

	}

}

