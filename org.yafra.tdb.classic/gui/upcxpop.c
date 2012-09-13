/*D*************************************************************************
 * Modul:		   GUI - Dialog			upcxpop.c
 *
 * Description:	create a message popup and/or a pcx popup
 *
 * Calls:			xUIdialog xUIbeep
 *						
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */
/* INCLUDES */
#include <uinclude.h>
#include <psmume.h>
#include <X11/StringDefs.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/upcxpop.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";

/* globals */
extern RASTERIMAGE *RI[MAXIMAGES];
extern int ImageCnt;
extern int ImageCurr;
extern GC WImgGC;
extern Colormap localCmap; 

/* defines */
#define IMGREDRAW 2
#define IMGRESIZE 1
#define IMGINPUT  3

/* local functions */
static int					PCXdisplay( Widget);
static Widget				PCXshell( Widget, RASTERIMAGE *);
static void					PCXredraw( Widget, SHOWIMG *);
static void					PCXcallback( Widget, caddr_t, caddr_t);
static XtCallbackProc	PCXclose( Widget, XtPointer, XtPointer);



/*F--------------------------------------------------------------------------
 *  Function:	xUIpcxpopup ()
 *					
 *  In:			-parent widget, pcx filename
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int xUIpcxpopup( Widget parent, char *pcxfile)
{
	Dimension		width, height;
	Arg				args[10];
	register int	ac;
	register int	cret;
	RASTERIMAGE		*image;
	Visual			*cmapvisual;
	Status			result;
	XVisualInfo		info;
	Display *disp = XtDisplay(parent);
	Colormap		defCmap; 
	int			i, num, ncells; 
	XColor		ctab[256];
	int			colors[256];
	int			planeMasks[1];


	/*--- Wurde ein Bildname eingegeben ? */
	if (pcxfile == (char *)0 || *pcxfile == '\0')
		return(MNOIMGNAME);

#ifdef ps_winnt
	PSSYShelp(pcxfile);
	return(MPOK);
#endif

	/*--- Alloc a RasterImage struct and put it on the Stack */
	image = (RASTERIMAGE *)XtMalloc( sizeof(RASTERIMAGE));
	if (image == NULL)
		return(MNOMOREIMG);

	defCmap = DefaultColormap(disp, DefaultScreen(disp) );

	result = XMatchVisualInfo( disp, DefaultScreen(disp), 
						DefaultDepth(disp, DefaultScreen(disp)), PseudoColor, &info);
	if (result)
		cmapvisual = info.visual;
	else
		cmapvisual = DefaultVisual( disp, DefaultScreen(disp) );

	/*-- create new colormap -------------*/
	localCmap = XCreateColormap( disp, RootWindow(disp, DefaultScreen(disp)),
										 cmapvisual, AllocNone);				
	if (localCmap)
	{
		ncells    = DisplayCells( disp, DefaultScreen(disp) );
/* XAllocColorCells( disp, localCmap, False, planeMasks, 0, colors, ncells); */  /* r/w cells */   
		for (i=0;  i<ncells;  i++)
		{
			ctab[i].pixel = (unsigned long)i ;
			XQueryColor( disp, defCmap, &ctab[i] );                    
			XAllocColor( disp, localCmap, &ctab[i] );                    
		}
	}
	else 
		return(MALLG);

										

	/*---- RASTERIMAGE init -----------------*/
	strcpy(image->Name, pcxfile);
	image->Show.XImg = NULL;
	image->WImg = parent;
	image->OriginalMap = defCmap;
	image->ImageMap =   localCmap;  


	/*--- ORAS Library call */
	/*--- try to read the file into the RASTERIMAGE struct */
	cret = ORread(image);
	if (cret == MOK)
		{
		ImageCnt++;
		ImageCurr = ImageCnt;
		RI[ImageCurr] = image; /* Neues Bild in globale Struktur uebernehmen */

		/*--- Bild anzeigen */
		cret = PCXdisplay(parent);
		}
	else
		XtFree( (void *)image);

	return(cret);
}



/*F--------------------------------------------------------------------------
 *  Function:	PCXdisplay ()
 *					Create a shell and display image
 *  In:			-parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static int PCXdisplay(Widget parent)
{
	Widget		shell;
	Arg			args[10];
	register	 int ac;
	int			cret = 0;
	Dimension	w;
	Dimension	h;
	Boolean		xret;
	Pixmap		pix;

	/*--- create widget containing image -------*/
	shell = PCXshell( parent, RI[ImageCurr]);
	if (shell == NULL)
		return(MALLG);

	ac = 0;
	XtSetArg(args[ac], XmNwidth, &w); ac++;
	XtSetArg(args[ac], XmNheight, &h); ac++;
	XtGetValues(RI[ImageCurr]->WImg, args, ac);
	RI[ImageCurr]->Show.x = 0;
	RI[ImageCurr]->Show.y = 0;
	RI[ImageCurr]->Show.w = w;
	RI[ImageCurr]->Show.h = h;

	/*--- ORAS Library call for resize ---------*/
	cret = ORresize(RI[ImageCurr], w, h);
	if (cret != MOK)
		return(cret);

	XtRealizeWidget(shell);
	XtPopup(shell, XtGrabNone);

	PCXredraw( RI[ImageCurr]->WImg, &RI[ImageCurr]->Show);

/* this is an other way (OSF/Motif way) to display an image
	xret = XmInstallImage(RI[ImageCurr]->Show.XImg, RI[ImageCurr]->Name);
	pix = XmGetPixmap(XtScreen(RI[ImageCurr]->WImg), RI[ImageCurr]->Name, 0, 1);
	XtVaSetValues(RI[ImageCurr]->WImg, XmNbackgroundPixmap, pix, NULL);
*/

	return( MOK);
}


/*F--------------------------------------------------------------------------
 *  Function:	PCXredraw ()
 *					draw an image
 *  In:			-parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void PCXredraw( Widget parent, SHOWIMG *img)
{
	XPutImage(XtDisplay(parent), XtWindow(parent), img->ImgGC, img->XImg, 0, 0,
	          img->x, img->y, img->w, img->h);
}


/*F--------------------------------------------------------------------------
 *  Function:	PCXshell ()
 *					Create a shell and a drawing area 
 *  In:			-parent widget
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static Widget PCXshell(Widget parent, RASTERIMAGE *img)
{
	Widget		shell, image;
	Arg			args[10];    
	int         ac;
	XGCValues	values;
	int			n, d, f;
	Atom			wm_delete_window;
	Display		*display;

	/********************************************************************/
	/* Toplevelshell fuer Graphik Anwendung                             */
	/********************************************************************/
	d = MWM_DECOR_BORDER|MWM_DECOR_RESIZEH|MWM_DECOR_TITLE|MWM_DECOR_MENU|MWM_DECOR_MINIMIZE|MWM_DECOR_MAXIMIZE;
	f = MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE|MWM_FUNC_RESIZE|MWM_FUNC_CLOSE;
	n=0;
	XtSetArg(args[n], XmNallowShellResize, True); n++;
	XtSetArg(args[n], XmNtitle,            img->Name); n++;
	XtSetArg(args[n], XmNiconName,         img->Name); n++;
	XtSetArg(args[n], XmNmwmFunctions,     f); n++;
	XtSetArg(args[n], XmNmwmDecorations,   d); n++;
	XtSetArg(args[n], XmNsaveUnder,        True); n++;
XtSetArg(args[n], XtNcolormap,         localCmap); n++;
	shell = XtCreatePopupShell("picshell", topLevelShellWidgetClass, parent, args, n);

	/********************************************************************/
	/* Iconpixmap  fuer Toplevelshell  aufbauen                         */
	/********************************************************************
	xUIiconpixmap(shell, app_data.iconbitmapgraphik);
	*/

	n = 0;
	XtSetArg(args[n], XmNwidth, img->Width); n++;
	XtSetArg(args[n], XmNheight, img->Height); n++;
	image = XmCreateDrawingArea(shell, "Img", args, n);
	XtManageChild(image);

	XtAddCallback(image, XmNresizeCallback, (XtCallbackProc)PCXcallback, (XtPointer)IMGRESIZE);
	XtAddCallback(image, XmNexposeCallback, (XtCallbackProc)PCXcallback, (XtPointer)IMGREDRAW);
	XtAddCallback(image, XmNinputCallback, (XtCallbackProc)PCXcallback, (XtPointer)IMGINPUT);

	/*--- Add a callback for protocol Motif Close --------*/
	display = XtDisplay( shell);
	wm_delete_window = XmInternAtom( display, "WM_DELETE_WINDOW", False);
	XmAddWMProtocolCallback( shell, wm_delete_window,
									 (XtCallbackProc)PCXclose, (XtPointer)shell );


	/* Create GC
	 *
	 * Use the foreground and background colors
	 * of the child to create a graphics context. */
	ac = 0;
	XtSetArg(args[ac], XtNforeground, &values.foreground);ac++;
	XtSetArg(args[ac], XtNbackground, &values.background);ac++;
	XtGetValues(image, args, ac);
	WImgGC = XtGetGC(image, GCForeground | GCBackground, &values);

	img->WImg = image;
	img->Show.ImgGC = WImgGC;

	return(shell);
}



/*F--------------------------------------------------------------------------
 *  Function:	PCXcallback ()
 *					common callback for expose, resize and input
 *  In:			-std CB params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void PCXcallback(Widget w, caddr_t client, caddr_t callback)
{
	Arg     args[10];
	register int ac;
	register int cret;
	XmDrawingAreaCallbackStruct *ImgCallback;
	XEvent *ImgEvent;
	XButtonEvent *MBEvent;
	Dimension Eventw;
	Dimension Eventh;

	ImgCallback = (XmDrawingAreaCallbackStruct *)callback;
	ImgEvent = ImgCallback->event;

	if (ImageCurr == -1)
		return;

	switch((int)client)
		{
		case IMGREDRAW:
			ac = 0;
			XtSetArg(args[ac], XmNwidth, &Eventw); ac++;
			XtSetArg(args[ac], XmNheight, &Eventh); ac++;
			XtGetValues(RI[ImageCurr]->WImg, args, ac);
			RI[ImageCurr]->Show.w = Eventw;
			RI[ImageCurr]->Show.h = Eventh;
			PCXredraw(RI[ImageCurr]->WImg, &RI[ImageCurr]->Show);
			break;
		case IMGRESIZE:
			ac = 0;
			XtSetArg(args[ac], XmNwidth, &Eventw); ac++;
			XtSetArg(args[ac], XmNheight, &Eventh); ac++;
			XtGetValues(RI[ImageCurr]->WImg, args, ac);
			cret = ORresize(RI[ImageCurr], Eventw, Eventh);
			if (cret != MOK)
				return;
			break;
		case IMGINPUT:
			break;

		default:
			exit(0);
			break;
		}
	XFlush(XtDisplay(w));
}




/*F--------------------------------------------------------------------------
 *  Function:	PCXclose ()
 *					User whishes to close image window 
 *  In:			-std CB params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc PCXclose(Widget w, XtPointer client, XtPointer callback)
{
	Arg				args[2];    
	int         	ac;

	/*--- shut image -------*/
	if (client) 
		{ 
		ac = 0;
		XtSetArg(args[ac], XtNcolormap, RI[ImageCurr]->OriginalMap);ac++;
		XtSetValues(w, args, ac);

		free((void *)RI[ImageCurr]->Data);
		XtFree((void *)RI[ImageCurr]);
		ImageCnt--;
		ImageCurr = ImageCnt;

		XtDestroyWidget(client);

		if (localCmap)
			{
			XFreeColormap( XtDisplay(w), localCmap  ); 
			localCmap = 0;
			}
		}

}
