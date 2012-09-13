/*D************************************************************
 * Modul:		GRAPHIC							ginit.c
 *
 *					Init all graphic parameters 	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ginit.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xGRinit_graphic()
 *					-General init when graphikflag is set 
 *					-check if not already done
 *	
 *---------------------------------------------------------------------------
 */
void xGRinit_graphic() 
{
	extern GRAWIDGETS		grawidgets;
	extern GRAGLOB			graglob;
	extern char			graphikallowed;				/* PS modul + graphic allowed  */
	extern Boolean		graphikflag;
	extern Widget		toplevel;

	if (graphikflag && !grawidgets.shell)
	{
		/*--- Actions and widgets ------------------*/
		xGRaction_initialize();
		grawidgets.shell = xGRwidget_shell(toplevel);
		grawidgets.palette = xGRwidget_palette(toplevel);
		grawidgets.bookmain = xGRwidget_booking(toplevel);

		/*--- factors and graphic menus ------------*/
		xGRinit_factors(); 
		xGRinit_context();

		/*--- only 1 dlt can be booked -------------*/
		graglob.bookingMode = XGRBOOK_ONE ; 
	}
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRinit_context()
 *					-init fonts, options, graphic contexts 
 *					-factors are used
 *	
 *---------------------------------------------------------------------------
 */
void xGRinit_context()
{
	extern	Display           *display;
	extern  ApplicationData   app_data;
	extern  GRAGLOB           graglob;
	extern  GRAWIDGETS        grawidgets;
	extern  GRAWINDOWS        grawindows;

	Window             root;
	Screen             *pscreen;
	Colormap           cmap;
	XColor             zcol, rgb;
	XGCValues          values, pixmapvalues;
	unsigned long      value_mask, value_mask_1, value_mask_2, pixmask;
	int                depth, screen, n;
	int                width, height;
	int                i, j, k, l;
	Arg                args[2];
	int                *linewidth, *linestyle;
	Pixel              *col, fg, bg, whitecol, blackcol;
	Pixmap             *pixpatt, *pixcol, *pixstyle, *pixweight, *pixsnap;
	Pixmap             *pixfont, *pix;
	XImage             image;   
	XFontStruct        *newfont, *fixfont; 
	WCVALUE            val;
	int                ival;
	char               *ptr, buf[1024];
	int                xanf, yanf, xend, yend, xcen, ycen, intervall;
	int                xstr, ystr;
	GC                 gcpixmap, gcpixmapback;


	screen  = XDefaultScreen(display);
	cmap    = XDefaultColormap(display, screen);
	pscreen = XDefaultScreenOfDisplay(display);

	blackcol = BlackPixel(display, screen);
	whitecol = WhitePixel(display, screen);

	fixfont  = XLoadQueryFont(display, "fixed");

	root = XDefaultRootWindow(display);

	depth = XDefaultDepth(display, screen);

	pixmapvalues.arc_mode = ArcChord;
	pixmapvalues.function = GXcopy;
	pixmapvalues.join_style = JoinRound;
	pixmapvalues.fill_style = FillSolid;
	pixmask = GCFunction|GCJoinStyle|GCArcMode|GCFillStyle;
	gcpixmap = XtGetGC(grawidgets.graphik, pixmask, &pixmapvalues);

	xanf = app_data.optionProz/100.*app_data.optionPixmapWidth;
	yanf = app_data.optionProz/100.*app_data.optionPixmapHeight;
	xend = (1.-app_data.optionProz/100.)*app_data.optionPixmapWidth;
	yend = (1.-app_data.optionProz/100.)*app_data.optionPixmapHeight;
	xcen = app_data.optionPixmapWidth/2;
	ycen = app_data.optionPixmapHeight/2;

	bg = app_data.optionPixmapbackground;
	fg = app_data.optionPixmapforeground;


/* Die den Graphical Context bestimmenden Elemente initialisieren */ 
/* Wenn weniger als MAX_FILLPATTERN Pixmaps in der Resource Datei */
/* eingetragen sind, muss initialisiert werden !!! sonst Fehler   */


	pixweight = (Pixmap *)malloc(graglob.anzLinewidth * sizeof(Pixmap));
	linewidth = (int *)malloc(graglob.anzLinewidth * sizeof(int));
	for(i=0, ptr=app_data.linewidthListe; i<graglob.anzLinewidth; i++) {
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		j = sscanf(buf, "%f", &val);
		if (j == 1) {
			linewidth[i] = (int)(val * graglob.xfak);
		} else {
			linewidth[i] = 1;
		}
		pixweight[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixweight[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmask = GCForeground;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixweight[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = linewidth[i];
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmask =
			GCForeground|GCBackground|GCLineWidth|GCLineStyle;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XDrawLine(display, pixweight[i], gcpixmap,
			xanf, ycen, xend, ycen);
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixweight[i]);
			XtSetValues(grawidgets.optlinewidth[i], args, 2);
		}
	}	 

	pixstyle = (Pixmap *)malloc(graglob.anzLinestyle * sizeof(Pixmap));
	linestyle = (int *)malloc(graglob.anzLinestyle * sizeof(int));
	for(i=0, ptr=app_data.linestyleListe; i<graglob.anzLinestyle; i++) {
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		j = sscanf(buf, "%d", &ival);
		if (j == 1) {
			linestyle[i] = ival;
		} else {
			linestyle[i] = 0;
		}
		pixstyle[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixstyle[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmask = GCForeground;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixstyle[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = linestyle[i];
			pixmask =
			GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XDrawLine(display, pixstyle[i], gcpixmap,
			xanf, ycen, xend, ycen);
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixstyle[i]);
			XtSetValues(grawidgets.optlinestyle[i], args, 2);
		}
	}	 

	pixcol = (Pixmap *)malloc(graglob.anzColors * sizeof(Pixmap));
	col = (Pixel *)malloc(graglob.anzColors * sizeof(Pixel));
	for(i=0, ptr=app_data.colorListe; i<graglob.anzColors; i++) { 
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		if(XAllocNamedColor(display, cmap, buf, &zcol, &rgb) != 0) {
			col[i] = zcol.pixel;
		} else {
			col[i] = blackcol;
		}
		pixcol[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixcol[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmask = GCForeground;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixcol[i], gcpixmap,
			       0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = col[i];
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmask = GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XDrawLine(display, pixcol[i], gcpixmap, xanf, ycen, xend, ycen);
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixcol[i]);
			XtSetValues(grawidgets.optcolor[i], args, 2);
		}
	}	 

	pix     = (Pixmap *)malloc(graglob.anzPattern * sizeof(Pixmap));
	pixpatt = (Pixmap *)malloc(graglob.anzPattern * sizeof(Pixmap));
	for(i=0, ptr=app_data.patternListe; i<graglob.anzPattern; i++) {
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		pix[i] = XmGetPixmap(pscreen, buf, fg, bg);
		pixpatt[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixpatt[i] != XmUNSPECIFIED_PIXMAP &&
		pix[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmapvalues.fill_style = FillSolid;
			pixmask = GCForeground|GCFillStyle;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixpatt[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmapvalues.tile       = pix[i];
			pixmapvalues.fill_style = FillTiled;
			pixmask = GCTile| GCFillStyle|
			GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XDrawRectangle(display, pixpatt[i], gcpixmap,
			xanf, yanf, xend-xanf, yend-yanf);
			XFillRectangle(display, pixpatt[i], gcpixmap,
			xanf, yanf, xend-xanf, yend-yanf);
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixpatt[i]);
			XtSetValues(grawidgets.optpattern[i], args, 2);
		} else {
			pixmapvalues.foreground = bg;
			pixmapvalues.fill_style = FillSolid;
			pixmask = GCForeground|GCFillStyle;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixpatt[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmapvalues.fill_style = FillSolid;
			pixmask = GCFillStyle|
			GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XDrawRectangle(display, pixpatt[i], gcpixmap,
			xanf, yanf, xend-xanf, yend-yanf);
			XFillRectangle(display, pixpatt[i], gcpixmap,
			xanf, yanf, xend-xanf, yend-yanf);
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixpatt[i]);
			XtSetValues(grawidgets.optpattern[i], args, 2);
		}
	}

	graglob.fonts =
	(XFontStruct **)malloc(graglob.anzFonts * sizeof(XFontStruct *));
	pixfont = (Pixmap *)malloc(graglob.anzFonts * sizeof(Pixmap));
	for(i=0, ptr=app_data.fontListe; i<graglob.anzFonts; i++) {
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		newfont = XLoadQueryFont(display, buf);
		if (newfont) { 
			graglob.fonts[i] = newfont;
		} else {
			graglob.fonts[i] = fixfont;
		}
		pixfont[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixfont[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmapvalues.fill_style = FillSolid;
			pixmask = GCForeground|GCFillStyle;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixfont[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmapvalues.font       = graglob.fonts[i]->fid;
			pixmask = GCFont|
			GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			xstr = (xend-xanf-XTextWidth(graglob.fonts[i], "abc",
			strlen("abc")))/2 + xanf;
			ystr = yend -
			(yend-yanf-(graglob.fonts[i]->max_bounds.ascent))/2;
			XDrawString(display, pixfont[i], gcpixmap,
			xstr, ystr, "abc", strlen("abc"));
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixfont[i]);
			XtSetValues(grawidgets.optfont[i], args, 2);
		}
	}

	pixsnap = (Pixmap *)malloc(graglob.anzSnap * sizeof(Pixmap));
	for(i=0, ptr=app_data.snapListe; i<graglob.anzSnap; i++) {
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ') ptr++;
		j = sscanf(buf, "%d", &ival);
		pixsnap[i] = XCreatePixmap(display, root,
		app_data.optionPixmapWidth, app_data.optionPixmapHeight, depth);
		if(pixsnap[i] != XmUNSPECIFIED_PIXMAP) {
			pixmapvalues.foreground = bg;
			pixmask = GCForeground;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			XFillRectangle(display, pixsnap[i], gcpixmap,
			0, 0, app_data.optionPixmapWidth, app_data.optionPixmapHeight);
			pixmapvalues.line_width = 1;
			pixmapvalues.foreground = fg;
			pixmapvalues.background = bg;
			pixmapvalues.line_style = LineSolid;
			pixmask =
			GCForeground|GCBackground|GCLineStyle|GCLineWidth;
			XChangeGC(display, gcpixmap, pixmask, &pixmapvalues);
			intervall = app_data.optionPixmapWidth/4;
			if (ival == 0) {
				for (j=intervall; j<app_data.optionPixmapWidth; j+=intervall) {
					XDrawLine(display, pixsnap[i], gcpixmap,
					j, 0, j, app_data.optionPixmapHeight);
				}
				for (j=intervall; j<app_data.optionPixmapHeight; j+=intervall) {
					XDrawLine(display, pixsnap[i], gcpixmap,
					0, j, app_data.optionPixmapWidth, j);
				}
				xanf = 1.5*intervall;
				yanf = 1.5*intervall;
				XDrawRectangle(display, pixsnap[i], gcpixmap,
				xanf, yanf, intervall, intervall);
			} else if (ival == 1) {
				xanf = 2*intervall-3;
				yanf = 2*intervall-3;
				XDrawArc(display, pixsnap[i], gcpixmap,
				xanf, yanf, 3, 3, 0, 360*64);
				xanf = 1.5*intervall;
				yanf = 1.5*intervall;
				XDrawRectangle(display, pixsnap[i], gcpixmap,
				xanf, yanf, intervall, intervall);
			} else if (ival == 2) {
				xanf = 2*intervall-3;
				yanf = 2*intervall-3;
				XDrawArc(display, pixsnap[i], gcpixmap,
				xanf, yanf, 3, 3, 0, 360*64);
			}
			XtSetArg(args[0], XmNlabelType, XmPIXMAP);
			XtSetArg(args[1], XmNlabelPixmap, pixsnap[i]);
			XtSetValues(grawidgets.optsnap[i], args, 2);
		}
	}

	/* Default-Widgets setzen */
	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optfont[graglob.indfont]);
	XtSetValues(grawidgets.aktfont, args, 1);

	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optsnap[graglob.indsnap]);
	XtSetValues(grawidgets.aktsnap, args, 1);

	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optcolor[graglob.indcolor]);
	XtSetValues(grawidgets.aktcolor, args, 1);

	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optpattern[graglob.indpattern]);
	XtSetValues(grawidgets.aktpattern, args, 1);

	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optlinestyle[graglob.indstyle]);
	XtSetValues(grawidgets.aktlinestyle, args, 1);

	XtSetArg(args[0], XmNmenuHistory,
	grawidgets.optlinewidth[graglob.indwidth]);
	XtSetValues(grawidgets.aktlinewidth, args, 1);


	/********************************************************/
	/* Graphical Context fuer den Fadenkreuzcursor aufbauen */
	n=0;
	XtSetArg(args[n], XmNforeground, &values.foreground); n++;
	XtSetArg(args[n], XmNbackground, &values.background); n++;
	XtGetValues(grawidgets.graphik, args, n);

	values.foreground = values.foreground ^ values.background;
	values.line_style = app_data.cursorlinestyle;
	if (values.line_style < 0 || values.line_style > 2)
		values.line_style = 0;
	values.line_width = app_data.cursorlinewidth;
	if (values.line_width <= 0)
		values.line_width = 1;
	values.font     = fixfont->fid;
	values.function = GXxor;
	value_mask      =
	GCForeground|GCBackground|GCFunction|GCLineStyle|GCLineWidth|GCFont;
	graglob.gc_cursor = XtGetGC(grawidgets.graphik, value_mask, &values);


	/************************************************/
	/* Graphical Context fuer Rasterlinien aufbauen */
	if (XAllocNamedColor(display, cmap, app_data.gridcolor, &zcol, &rgb))
                         values.foreground = zcol.pixel;
	else             values.foreground = BlackPixel(display, screen);
	values.line_style = app_data.gridlinestyle;
	if (values.line_style < 0 || values.line_style > 2)
		values.line_style = 0;

	values.line_width = app_data.gridwidth;
	if (values.line_width <= 0)
		values.line_width = 1;
	graglob.gc_grid = XtGetGC(grawidgets.graphik,
	GCForeground|GCLineStyle|GCLineWidth, &values);


 /*********************************************************************/
 /* Graphical Context Array fuer die Fuell Zeichenoperationen aufbauen*/
 /* Es muessen MAX_COLOR*MAX_FILLPATTERN Elemente besetzt werden.     */
 /* Arrayname = GCP                                                   */
 /* Arraygrenzen: GCP[MAX_COLOR][MAX_FILLPATTERN]                     */
 /*                                                                   */ 
	XtSetArg(args[0], XmNbackground, &bg);
	XtGetValues(grawidgets.graphik, args, 1);

	values.function   = GXcopy;
	values.plane_mask = AllPlanes;
	values.background = bg;
	values.fill_rule  = EvenOddRule;
	values.arc_mode   = ArcPieSlice;
	value_mask_1 = (GCFunction|GCPlaneMask|GCForeground|GCBackground|
		        GCFillStyle|GCFillRule|GCArcMode);
	value_mask_2 = (GCFunction|GCPlaneMask|GCForeground|GCBackground|
		        GCFillStyle|GCFillRule|GCArcMode|GCTile);
	graglob.GCP = (GC **)malloc(graglob.anzColors*sizeof(GC *));
	graglob.GCR = (GC *)malloc(graglob.anzColors*sizeof(GC));
	for(i=0; i<graglob.anzColors; i++) {
		graglob.GCP[i] = (GC *)malloc(graglob.anzPattern*sizeof(GC));
		values.foreground = col[i];
		for(j=0, ptr=app_data.patternListe; j<graglob.anzPattern; j++) {
			sscanf(ptr, "%s", buf);
			ptr += strlen(buf);
			while (*ptr != 0 && *ptr != ' ') ptr++;
			pix[j] = XmGetPixmap(pscreen, buf, col[i], bg);
			if (pixpatt[j] != XmUNSPECIFIED_PIXMAP &&
			pix[j] != XmUNSPECIFIED_PIXMAP) {
				values.tile = pix[j];
				values.fill_style = FillTiled;
				graglob.GCP[i][j] = XtGetGC(grawidgets.graphik,
				value_mask_2, &values);
			} else {
				values.fill_style = FillSolid;
				graglob.GCP[i][j] = XtGetGC(grawidgets.graphik,
				value_mask_1, &values);
			}
		}
		values.fill_style=FillSolid;
		graglob.GCR[i] = XtGetGC(grawidgets.graphik, value_mask_1,
		&values);
	}

 /*********************************************************************/
 /* Graphical Context Array fuer alle Zeichenoperationen aufbauen     */
 /* Pro Operation koennen Farbe, Linientyp und Linienbreite geaendert */
 /*                                                                   */ 

	values.function   = GXcopy;
	values.plane_mask = AllPlanes;
	values.cap_style  = CapButt;
	values.join_style = JoinMiter;
	values.fill_style = FillSolid;
	values.fill_rule  = EvenOddRule;
	values.background = bg;
	value_mask        = (GCFunction|GCPlaneMask|GCForeground|GCBackground|
			     GCLineWidth|GCLineStyle|GCCapStyle|GCJoinStyle|
			     GCFillStyle|GCFillRule);  
	graglob.GCZ = (GC ***)malloc(graglob.anzColors*sizeof(GC **));
	for(i=0; i<graglob.anzColors; i++) {
		values.foreground = col[i];
		graglob.GCZ[i]=(GC **)malloc(graglob.anzLinewidth*sizeof(GC *));
		for(j=0; j<graglob.anzLinewidth; j++) {
			values.line_width = linewidth[j];
			graglob.GCZ[i][j] =
			(GC *)malloc(graglob.anzLinestyle*sizeof(GC));
			for(k=0; k<graglob.anzLinestyle; k++) {
				values.line_style = linestyle[k];
				graglob.GCZ[i][j][k] =
				XtGetGC(grawidgets.graphik, value_mask, &values);
			}
		}      
	} 

 /*********************************************************************/
 /* Graphical Context Array fuer alle Schreiboperationen aufbauen     */
 /* Pro Operation koennen Farbe und Font geaendert werden.            */
 /* Daher muessen MAX_COLOR*MAX_FONT Elemente festgelegt werden.      */
 /* Arrayname = GCF                                                   */
 /* Im zweidimensionalen Array GCF steht der 1.Index fuer die Farbe,  */
 /* der 2.Index fuer den Font.                                        */
 /*                                                                   */

	values.function   = GXcopy;
	values.plane_mask = AllPlanes;
	values.background = bg;
	values.line_width = 1;
	values.line_style = 0;
	values.cap_style  = CapButt;
	values.join_style = JoinMiter;
	values.fill_style = FillSolid;
	values.fill_rule  = EvenOddRule;
	value_mask = (GCFunction|GCPlaneMask|GCForeground|GCBackground|
		      GCLineWidth|GCLineStyle|GCCapStyle|GCJoinStyle|
		      GCFillStyle|GCFillRule|GCFont);  
	graglob.GCF = (GC **)malloc(graglob.anzColors*sizeof(GC *));
	for(i=0; i<graglob.anzColors; i++) {
		values.foreground = col[i];
		graglob.GCF[i] = (GC *)malloc(graglob.anzFonts*sizeof(GC *));
		for(j=0; j<graglob.anzFonts; j++) {
			values.font = graglob.fonts[j]->fid;
			graglob.GCF[i][j] =
			XtGetGC(grawidgets.graphik, value_mask, &values);
		}      
	}

	/*--- set Active GC ----*/
	graglob.gcz = &graglob.GCZ[graglob.indcolor][graglob.indwidth][graglob.indstyle];
	graglob.gcp = &graglob.GCP[graglob.indcolor][graglob.indpattern];
	graglob.gcf = &graglob.GCF[graglob.indcolor][graglob.indfont];
	graglob.gcr = &graglob.GCR[graglob.indcolor];
	graglob.tempObj = 0;

	/*--- set default Colors ----*/
	graglob.Tempfarbe = (unsigned char)(graglob.anzColors-2);
	for (i=0; i<256; i++) {
		graglob.Buchungsfarbe[i] = (unsigned char)(graglob.anzColors-1);
	}

	free((void *)col);
	free((void *)linestyle);
	free((void *)linewidth);
}



/*************************************************************************/
/* Dieses UP   ermittelt die Display Dimensionen in x und y Richtung.    */
/* Diese Aufloesungen werden in mm und in Pixel ermittelt. Daraus wird   */
/* anschliessend der Pixel/mm Wert bei normaler Darstellung berechnet.   */
/* Beim Zooming veraendert sich der Pixel/mm Wert. Wird im Zoom Menue das*/
/* Feld normal angewaehlt, so werden die Pixel/mm Werte x_pix_a_mm_n und */
/* y_pix_a_mm_n verwendet. Das ist dann wieder die Voreinstellung.       */
/*************************************************************************/

/*F--------------------------------------------------------------------------
 *  Function:	xGRinit_factors()
 *					-calculate factor mm to pixel,  zoomfactor
 *	
 *---------------------------------------------------------------------------
 */
void xGRinit_factors() 
{
	extern Display           *display;
	extern GRAGLOB           graglob;

	int		screen;
	int		heightmm, heights, widthmm, widths ;


	screen  = XDefaultScreen(display);

	heightmm = XDisplayHeightMM(display, screen);
	heights  = XDisplayHeight(display, screen);

	widthmm  = XDisplayWidthMM(display, screen);
	widths   = XDisplayWidth(display, screen);

	graglob.xfak = (WCVALUE)widths /(WCVALUE)widthmm;
	graglob.yfak = (WCVALUE)heights/(WCVALUE)heightmm;
	graglob.zoomfaktor = 1;

/*--- Graphic scaling ------------------*/
graglob.xfak = graglob.xfak/4 ;          /* 2.6 */
graglob.yfak = graglob.yfak/4 ;

#ifdef MILLIMETER_UNITS
	graglob.xfak = 20.0;
	graglob.yfak = 20.0;
	graglob.zoomfaktor = 1;
#endif
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRinit_cat_colors()
 *					transform color name into pixel
 *					build graphic contexts for all colors 
 *	
 *	CAUTION: db_data is used and NOT app_data !!!!!
 *          This function cannot be used, compatibility with old GCs
 *---------------------------------------------------------------------------
 */
void xGRinit_cat_colors() 
{
	extern Display		*display;
	extern GRACAT		gracat;
	extern DatabaseData      db_data;
	extern GRAWIDGETS        grawidgets;

	int				screen;
	int				i, len, nbColors;
	Pixel				*col, fg, bg, whitecol, blackcol;
	Colormap			cmap;
	XColor			zcol, rgb;
	XGCValues		values;
	unsigned long	value_mask;
	char				*ptr, buf[1024];
	Arg				args[2];
	char			*anf;
	char			tmp[80];

	/*--- General inits -------------------*/
	screen   = XDefaultScreen(display);
	cmap     = XDefaultColormap(display, screen);
	blackcol = BlackPixel(display, screen);
	whitecol = WhitePixel(display, screen);

	/*--- Get number of strings -----------*/
	anf = db_data.colorListe;
	nbColors = 0;
	while (sscanf( anf, "%s", tmp) == 1) {
		while (*anf == ' ') anf++;  
		len = strlen(tmp);
		anf += len;
		nbColors++;
	}
	gracat.anzColors = nbColors;

	/*--- Allocate named colors -----------*/
	col = (Pixel *)malloc( nbColors * sizeof(Pixel));
	for (i=0,  ptr = db_data.colorListe;  i<nbColors;  i++) { 
		sscanf(ptr, "%s", buf);
		ptr += strlen(buf);
		while (*ptr != 0 && *ptr != ' ')  ptr++;
		if (XAllocNamedColor( display, cmap, buf, &zcol, &rgb) != 0) {
			col[i] = zcol.pixel;
		} else {
			col[i] = blackcol;
		}
	}

	/*--- Graphical Context Array GCR ----------------------------------*/
	XtSetArg(args[0], XmNbackground, &bg);
	XtGetValues(grawidgets.graphik, args, 1);

	values.function   = GXcopy;
	values.plane_mask = AllPlanes;
	values.background = bg;
	values.fill_style = FillSolid;
	values.fill_rule  = EvenOddRule;
	values.arc_mode   = ArcPieSlice;
	value_mask = (GCFunction|GCPlaneMask|GCForeground|GCBackground|
		                                  GCFillStyle|GCFillRule|GCArcMode);
	gracat.GCR = (GC *)malloc( nbColors * sizeof(GC));

	/*--- Get a GC for each color --------*/
	for(i=0; i<nbColors; i++) {
		values.foreground = col[i];
		gracat.GCR[i] = XtGetGC(grawidgets.graphik, value_mask, &values);
	}

}
