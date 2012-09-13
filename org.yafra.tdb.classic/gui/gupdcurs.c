/*D************************************************************
 * Modul:		GRAPHIC							gupdcurs.c
 *
 *					Update the cursor, the temporary objects,	
 *					the region name and coordinates when motion
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gupdcurs.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gupdcurs.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:10  ja
 general version

 * Revision 1.3  94/02/18  10:38:35  10:38:35  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:16  00:26:16  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gupdcurs.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


/**************************************************************************/
/* Up update_cursor erstellt                                              */
/* 1. zeichnet ein Fadenkreuz an der zuletzt registrierten Stelle         */
/* 2. zeichnet das Fadenkreuz an der Stelle, an der ein Pointer Motion    */
/*    Event im Grafik Window empfangen wurde,                             */
/* 3. schreibt diese Koordinaten in mm umgerechnet ins Koordinatenwidget. */
/* Da der Graphicalcursor als Zeichenfunktion das exklusive Oder GXxor    */
/* verwendet, wird immer abwechselnd mit Hinter- und Vordergrundfarbe     */
/* gezeichnet, das zuletzt gezeichnete Kreuz also geloescht.              */
/*                                                                        */
/* Nach Expose Events kann es vorkommen, dass ein EnterNotify Event       */
/* geschickt wird, und kurz darauf ein PointerMotion Event. Wenn das      */
/* PointerMotion Event frueher ankommt, bleibt ein Fadenkreuz stehen.     */
/* Es muss hier also ueberprueft werden, ob ein EnterNotify Event in der  */
/* Queue ist.                                                             */
/*                                                                        */
/* Eingabeparameter :  w      = rufendes Widget, Grafik3                  */
/*                     coord  = ID des CoordinatenLabelWidgets            */
/*                     event  = bei EnterNotify uebergebene Event Struktur*/
/*                                                                        */
/* Erstellt : Sept. 1991  WSp                                             */
/**************************************************************************/


XtCallbackProc xGRupdate_cursor(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB   graglob;
	extern Display   *display;
	extern XPoint     punkt[];
	extern Boolean   undraw;
	extern REGOBJ    *regObj;

	static GRAFOBJ tempObj;
	static int     xi[2];
	static XArc    xa;
	static XRectangle xr;
	static XPoint  xp[2];
	static Boolean temp = False;
	static Boolean zooming = False;   /*no cursor while zooming */
	static Boolean firstenter=True;

	XArc      arcus;
	WCVALUE   r;
	XEvent    *event = (XEvent *)Output;
	Arg       args[1];
	REGOBJ    *region;
	int       x, y;
	XmString  label;
	char      buf[XGRCOORDLEN+1];
	int       nr;
	Boolean   ok;
	long      aktnummer;
	char      strleer3[XGRREGIONLEN+1] = "*";


	if (event->type == EnterNotify) {   /*--------- EnterNotify   */
		if (firstenter) {
			firstenter=False;
		} else {
			return;
		}
	} else {                             /*--------- PointerMotion */
		firstenter=True;
		if (undraw) {
			if ((graglob.mode == XGRINPGRAFIC) && (!zooming)) 
				xGRdraw_cursor();
			if (graglob.showPickbox)
				xGRdraw_pickbox();
			if (temp)
				xGRdraw_object(&tempObj);
		}
	} 

	if (event->type == LeaveNotify) {
		return;
	}

	/*--- defaults --------*/
	zooming = False; 
	temp = False;
	undraw = True;

	x = event->xmotion.x;
	y = event->xmotion.y;

	graglob.cursor_data.x = x;
	graglob.cursor_data.y = y;

	if (graglob.eingabe > 0) {
		switch (graglob.aktbox) {
			case BUTTONZOOM:
				if (graglob.akttog == BUTTONZOOM_ZOOM && graglob.eingabe == 2) {
					tempObj.was = TEMP_RECTANGLE;
					tempObj.xpoints = (int *)&xr;
					punkt[1].x = x;
					punkt[1].y = y;
					ok = xGRcheck_rectangle();
					if (ok) {
						xGRobjkoord_rectangle(&xr);          /*get rect params*/
						temp = True;
						zooming = True; 
					}
				}
				break;
			case BUTTONCREATE:
				switch (graglob.akttog) {
					case BUTTONCREATE_TEXT:
						if (graglob.eingabe == 2) {
							tempObj.was = TEMP_TEXT;
							tempObj.xpoints = xi;
							xi[0] = x;
							xi[1] = y;
							tempObj.text = graglob.antwort;
							tempObj.gc3=(unsigned char)strlen(graglob.antwort);
							temp = True;
						}
						break;
					case BUTTONCREATE_POINT:
						break;
					case BUTTONCREATE_ARC:
					case BUTTONCREATE_FILLEDARC:
						/*if (graglob.eingabe == 3) {
							tempObj.was = TEMP_CIRCLE;
							punkt[2].x = x;
							punkt[2].y = y;
							ok = xGRget_arc(punkt, &arcus);
							if (ok) {
								tempObj.xpoints = (int *)&xa;
								xa.x = arcus.x - arcus.r;
								xa.y = arcus.y - arcus.r;
								xa.width = 2. * arcus.r;
								xa.height = 2. * arcus.r;
								xa.angle1 = 64. * arcus.a1;
								xa.angle2 = 64. * arcus.a2;
								temp = True;
							} else {
								temp = False;
							}
						}*/
						break;
					case BUTTONCREATE_LINE:
						if (graglob.eingabe == 2) {
							tempObj.was = TEMP_LINE;
							tempObj.xpoints = (int *)punkt;
							punkt[1].x = x;
							punkt[1].y = y;
							temp = True;
						}
						break;
					case BUTTONCREATE_CIRCLE:
					case BUTTONCREATE_FILLEDCIRCLE:
						if (graglob.eingabe == 2) {
							tempObj.was = TEMP_RECTANGLE;
							tempObj.xpoints = (int *)&xr;
							punkt[1].x = x;
							punkt[1].y = y;
							if (fabs((double)(punkt[0].y - punkt[1].y)) < EPS && 
							    fabs((double)(punkt[0].x - punkt[1].x)) < EPS) {
								temp = False;
							} else {
								r = (WCVALUE)hypot((double)(punkt[0].y - punkt[1].y),
							                      (double)(punkt[0].x - punkt[1].x));
								tempObj.xpoints = (int *)&xr;
								xr.x = punkt[0].x - r;
								xr.y = punkt[0].y - r;
								xr.width = 2 * r;
								xr.height = 2 * r;
								/*xa.angle1 = 0.;
								xa.angle2= 64. * 360.;*/
								temp = True;
							}
						}
						break;
					case BUTTONCREATE_RECTANGLE:
					case BUTTONCREATE_ELLIPSE:
					case BUTTONCREATE_FILLEDRECTANGLE:
					case BUTTONCREATE_FILLEDELLIPSE:
						if (graglob.eingabe == 2) {
							tempObj.was = TEMP_RECTANGLE;
							tempObj.xpoints = (int *)&xr;
							punkt[1].x = x;
							punkt[1].y = y;
							ok = xGRcheck_rectangle();
							if (ok) {
								xGRobjkoord_rectangle(&xr);
								temp = True;
							}
						}
						break;
				}
				break;
			case BUTTONEDIT:
				switch (graglob.akttog) {
					case BUTTONEDIT_MOVE:
					case BUTTONEDIT_COPY:
						if (graglob.eingabe == 2) {
							tempObj.was = TEMP_LINE;
							tempObj.xpoints = (int *)punkt;
							punkt[1].x = x;
							punkt[1].y = y;
							temp = True;
						}
						break;
					case BUTTONEDIT_DELETE:
						break;
				}
				break;
			case BUTTONSELECT:
				nr = graglob.eingabe-2;
				if (nr < 0) {
					tempObj.was = TEMP_TEXT;
					tempObj.xpoints = xi;
					xi[0] = x;
					xi[1] = y;
					tempObj.text = graglob.antwort;
					tempObj.gc3=(unsigned char)strlen(graglob.antwort);
					temp = True;
				} else if (nr > 0) {
					tempObj.was = TEMP_LINE;
					tempObj.xpoints = (int *)xp;
					xp[0].x = punkt[0].x;
					xp[0].y = punkt[0].y;
					xp[1].x = x;
					xp[1].y = y;
					temp = True;
				}
				break;
		}
	}

	/*--- Draw what ---------------------------------------------------*/
	if ((graglob.mode == XGRINPGRAFIC) && (!zooming)) 
		xGRdraw_cursor();
	if (graglob.showPickbox)
		xGRdraw_pickbox();
	if (temp)
		xGRdraw_object(&tempObj);

	/*--- aktuelle Pointerregion bestimmen -----------------------------*/
	aktnummer = xGRfind_region_koord(x, y);
	if(aktnummer != NOVATER) {
		region = &regObj[aktnummer];
		/*--- Pointer war beim letzten up_curs Aufruf in anderer Region */
		if (region != graglob.aktregion) {
			graglob.aktregion = region;
			label = xGRregion_name( region, 0);           /* XGRREGIONLEN  */
			XtSetArg(args[0], XmNlabelString, label);
			XtSetValues(grawidgets.aktregion, args, 1);
			XmStringFree(label);
		}
	} else {
		/*--- clear Region val --------*/
/*		xGRstringpos( strleer3, XGRREGIONLEN, XGRLEFT);  */
		label = XmStringCreateSimple(strleer3);
		XtSetArg(args[0], XmNlabelString, label);
		XtSetValues(grawidgets.aktregion, args, 1);
		XmStringFree(label);
		graglob.aktregion = 0;
	}

	/*--- Koordinatenlabel setzen ------------------------------------*/
	if (graglob.mode == XGRINPGRAFIC) {
		sprintf(buf, "%6.1fmm / %6.1fmm",
									(WCVALUE)x/graglob.xfak, (WCVALUE)y/graglob.yfak);
		xGRstringpos( buf, XGRCOORDLEN, XGRRIGHT);
		label = XmStringCreateSimple(buf);
		XtSetArg(args[0], XmNlabelString, label);
		XtSetValues(grawidgets.koord, args, 1);
		XmStringFree(label);
	}

}
