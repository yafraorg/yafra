/*D************************************************************
 * Modul:		GRAPHIC							gwggraf.c
 *
 *					Build a scrolled window with a drawing area
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gwggraf.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gwggraf.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:14  ja
 general version

 * Revision 1.3  94/02/18  10:38:38  10:38:38  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:26  00:26:26  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwggraf.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

#define MAXPOS(a,b) ((a)>(b)?(a):(b))
#define MINPOS(a,b) ((a)<(b)?(a):(b))



Widget xGRwidget_graphik(
Widget parent
)

{
	extern Display *display;
	extern GRAWIDGETS grawidgets;

	static ACTCALLBACK actgraphik = {BUTTONGRAPHIK, 0};
	static ACTCALLBACK actzoom    = {BUTTONZOOM, BUTTONZOOM_RESIZE};

	Widget scrollgraphik;  /* Scrolled Graphik */
	Arg    args[2];
	int    n, screen;

	screen = XDefaultScreen(display);

	/*--- Scrolled window -----------*/
	n=0;
	XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);    n++;
	XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED); n++;
	scrollgraphik = XmCreateScrolledWindow( parent, GRAPHIKSCROLLEDGRAPHIK, args, n);
	XtManageChild(scrollgraphik);

	/*--- drawing Area --------------*/
	n=0;
/* XtSetArg(args[n], XmNunitType, Xm100TH_MILLIMETERS);   n++;  */
	XtSetArg(args[n], XmNunitType, XmPIXELS);   n++;  
	grawidgets.graphik = XmCreateDrawingArea(scrollgraphik, GRAPHIKDRAWINGAREA, args, n);
	XtManageChild(grawidgets.graphik);

	/*--- Callback and actions ------*/
	XtAddCallback(grawidgets.graphik, XmNinputCallback,
									(XtCallbackProc)xGRaction, (XtPointer)&actgraphik);
	XtAddCallback(grawidgets.graphik, XmNexposeCallback,
									(XtCallbackProc)xGRdraw, (XtPointer)&actgraphik);
	XtAddCallback(grawidgets.graphik, XmNresizeCallback,
									(XtCallbackProc)xGRaction, (XtPointer)&actzoom);

	n=0;
	XtSetArg(args[n], XmNbackground, BlackPixel(display, screen)); n++;
	XtSetValues(XtParent(grawidgets.graphik), args, n);

	return(scrollgraphik);
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_graphik_resize ()
 *					-change the size of the scrolled window of drawing area
 *					-
 *  In:			-the factor modifying the dimension
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xGRwidget_graphik_resize( Boolean windowAdjust)		   
{
	extern GRAGLOB		graglob;
	extern GRAWIDGETS grawidgets;

	Dimension	widthcurrent, heightcurrent;
	Arg			wargs[2];

	/*--- Drawing area size adjustment -----------*/
	widthcurrent  = graglob.Limitx;
	heightcurrent = graglob.Limity;

	XtSetArg(wargs[0], XmNwidth, widthcurrent);
	XtSetArg(wargs[1], XmNheight, heightcurrent);
	XtSetValues(grawidgets.graphik, wargs, 2);        /* triggers ZOOM_RESIZE */

	/*--- Scrolled window size adjustment ---------*/
	if (windowAdjust) {
		widthcurrent  += 8; 
		heightcurrent += 8;
		XtSetArg(wargs[0], XmNwidth,   widthcurrent);
		XtSetArg(wargs[1], XmNheight,  heightcurrent);
		XtSetValues(grawidgets.scrolledgraphik, wargs, 2);
		XtManageChild(grawidgets.scrolledgraphik);
	}

	XtManageChild(grawidgets.graphik);
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_graphik_getsize ()
 *					-get the dimension of the scrolled window containing graphik
 *					-
 *  In:			- 
 *  out:			-ptr to XPoint
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xGRwidget_graphik_getsize( XPoint *windowsize)		   
{
	extern GRAWIDGETS grawidgets;

	Dimension	widthcurrent, heightcurrent;
	Arg			wargs[2];

	/*--- scrolled window --------------------------*/
	XtSetArg(wargs[0], XmNwidth,  &widthcurrent);
	XtSetArg(wargs[1], XmNheight, &heightcurrent);
	XtGetValues( grawidgets.scrolledgraphik, wargs, 2);
	windowsize->x = widthcurrent;
	windowsize->y = heightcurrent;
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRwidget_graphik_scrollpos ()
 *					-set drawing area in middle of scrolled window
 *					-
 *  In:			-positions 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xGRwidget_graphik_scrollpos( int h_position, int v_position)		   
{
	extern GRAWIDGETS grawidgets;

	int			ac; 
	Arg			wargs[10];
	Widget		horizScrollbar, vertScrollbar; 
	int			h_curpos, h_size, h_inc, h_pageinc, h_min, h_max; 
	int			v_curpos, v_size, v_inc, v_pageinc, v_min, v_max; 
	XEvent			event; 

	/*--- get scrollbar ids ----------------*/
	ac = 0;
	XtSetArg(wargs[ac], XmNhorizontalScrollBar, &horizScrollbar); ac++; 
	XtSetArg(wargs[ac], XmNverticalScrollBar,   &vertScrollbar);  ac++;
	XtGetValues( grawidgets.scrolledgraphik, wargs, ac);

	/*--- get Horizontal values ------------*/
	ac = 0;
	XtSetArg(wargs[ac], XmNminimum,       &h_min);    ac++;
	XtSetArg(wargs[ac], XmNmaximum,       &h_max);    ac++;
	XtGetValues( horizScrollbar, wargs, ac);
	XmScrollBarGetValues( horizScrollbar, &h_curpos, &h_size, &h_inc, &h_pageinc); 

	/*--- get Vertical values --------------*/
	ac = 0;
	XtSetArg(wargs[ac], XmNminimum,       &v_min);    ac++;
	XtSetArg(wargs[ac], XmNmaximum,       &v_max);    ac++;
	XtGetValues( vertScrollbar, wargs, ac);
	XmScrollBarGetValues( vertScrollbar, &v_curpos, &v_size, &v_inc, &v_pageinc); 

	/*--- Check and Set new values ---------------------------------*/
	h_curpos = MINPOS( h_position, h_max - h_size) ;
	h_curpos = MAXPOS( h_curpos, h_min) ;
	v_curpos = MINPOS( v_position, v_max - v_size) ;
	v_curpos = MAXPOS( v_curpos, v_min );
	XmScrollBarSetValues( horizScrollbar, h_curpos, h_size, h_inc, h_pageinc, True); 
	XmScrollBarSetValues( vertScrollbar,  v_curpos, v_size, v_inc, v_pageinc, True); 

}



