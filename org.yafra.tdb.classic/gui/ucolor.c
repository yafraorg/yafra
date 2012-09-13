/*D************************************************************
 * Modul:     GUI - dialog        ucolor.c 
 *            handle color calculations, setting ...
 *                                                            
 * Functions: xUIgetdefcolors() xUIsetwidgetcolor()
 *                                                            
 * Callbacks: 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ucolor.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



/*------------------------ PROTOTYPES -------------------------------------*/

 

/*F--------------------------------------------------------------------------
 *  Function:	xUIgetdefcolors ()
 *					-get default colors from a pushbutton
 *					-sets the colors for each kind of pushbutton
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIinitcolors ( Widget aWidget)
{
	extern ApplicationData app_data;
	extern unsigned char getcolor;		 /* TRUE: hole def. Farb FALSE: nop */
	extern OBJCOLORS orgcol;		       /* Original Colorset */
	extern OBJCOLORS keycol;		       /* Key Colorset */
	extern OBJCOLORS nextmenucol;			 /* Next Menu Colorset */
	extern OBJCOLORS gracol;		       /* Graphic Colorset */
	extern OBJCOLORS boardcol;		       /* Board matrix Colorset */

	Arg		arglist[10];
	int		ac;
	Colormap	cmap;
	Screen	*screen;

	/*---- Merke default colorsettings und key colorsetting von einem Pushb. */
	if (getcolor == (unsigned char)TRUE)
	{
		XtVaGetValues(aWidget,
			XmNbackground,         &orgcol.bg,
			XmNforeground,         &orgcol.fg,
			XmNtopShadowColor,     &orgcol.top,
			XmNbottomShadowColor,  &orgcol.bottom,
			XmNselectColor,        &orgcol.select,
			NULL);

		/*--- get color map -----------------------*/
		XtVaGetValues(aWidget, XmNcolormap, &cmap, NULL);
		screen  = XtScreen(aWidget);

		/*--- calculate new correspondent colors ------*/
		XmGetColors(screen, cmap, orgcol.bg, &orgcol.fg, &orgcol.top,
						&orgcol.bottom, &orgcol.select);

		keycol.bg = app_data.ColKey;
		XmGetColors(screen, cmap, keycol.bg, &keycol.fg, &keycol.top, 
						&keycol.bottom, &keycol.select);
		nextmenucol.bg = app_data.ColNextMenu;
		XmGetColors(screen, cmap, nextmenucol.bg,	&nextmenucol.fg, &nextmenucol.top,
						&nextmenucol.bottom, &nextmenucol.select);
		gracol.bg = app_data.ColGra;
		XmGetColors(screen, cmap, gracol.bg, &gracol.fg, &gracol.top, 
						&gracol.bottom, &gracol.select);
		boardcol.bg = app_data.ColBoard;
		XmGetColors(screen, cmap, boardcol.bg, &boardcol.fg, &boardcol.top, 
						&boardcol.bottom, &boardcol.select);
		getcolor = (unsigned char)FALSE;
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIsetwidgetcolor ()
 *					-set the color for a widget to an object color
 *					-
 *  In:			-a widget, a object color 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIsetwidgetcolor( Widget aWidget, OBJCOLORS *pObjcol )
{
	/*----  set all object color members ---------------*/
	XtVaSetValues(aWidget,
		XmNbackground,         pObjcol->bg,
		XmNforeground,         pObjcol->fg,
		XmNborderColor,        pObjcol->fg,
		XmNtopShadowColor,     pObjcol->top,
		XmNbottomShadowColor,  pObjcol->bottom,
		XmNselectColor,        pObjcol->select,
		XmNarmColor,           pObjcol->select,
		NULL);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIreverseColor ()
 *					-if widget exits, foreground becomes bg, and conversely
 *					-
 *  In:			-a widget  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIreverseColor (Widget w)
{
	Pixel			fg, bg;
	Arg			wargs[10];
	int			ac;

#ifdef ps_unix
	/*------ init work ------*/
	if (w) {
		XtSetArg(wargs[0], XmNforeground, &fg);
		XtSetArg(wargs[1], XmNbackground, &bg);
		XtGetValues(w, wargs, 2);

		XtSetArg(wargs[0], XmNforeground, bg);
		XtSetArg(wargs[1], XmNbackground, fg);
		XtSetValues(w, wargs, 2);
	}
#endif

}


/*F--------------------------------------------------------------------------
 *  Function:	xUIcolorInverse ()
 *					-highlight widget 
 *					-
 *  In:			-a widget  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIcolorInverse( Widget w)
{
	extern OBJCOLORS orgcol;		       /* Original Colorset */

	Arg			wargs[10];
	int			ac;

#ifdef ps_unix
	if (w)
	{
		XtSetArg(wargs[0], XmNforeground, orgcol.bg);
		XtSetArg(wargs[1], XmNbackground, orgcol.fg);
		XtSetValues(w, wargs, 2);
	}
#endif

}


/*F--------------------------------------------------------------------------
 *  Function:	xUIcolorNormal ()
 *					-normal color widget 
 *					-
 *  In:			-a widget  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIcolorNormal( Widget w)
{
	extern OBJCOLORS orgcol;		       /* Original Colorset */

	Arg			wargs[10];
	int			ac;

#ifdef ps_unix
	if (w)
	{
		XtSetArg(wargs[0], XmNforeground, orgcol.fg);
		XtSetArg(wargs[1], XmNbackground, orgcol.bg);
		XtSetValues(w, wargs, 2);
	}
#endif
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIsetSelectColor ()
 *					-for a color pushbutton, set colors to show it selected 
 *					-
 *  In:			-a widget  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIsetSelectColor (Widget w)
{
	Pixel			bg, arm, bsc, tsc;

#ifdef ps_unix
	/*------ init work ------*/
	if (w)
	{
		XtVaGetValues(w,	XmNarmColor,				&arm,
								XmNbackground,				&bg,
								XmNbottomShadowColor,	&bsc,	
								XmNtopShadowColor,		&tsc,	
																NULL);
		XtVaSetValues(w,	XmNforeground,				bg,
								XmNbackground,				arm,
								XmNbottomShadowColor,	tsc,	
								XmNtopShadowColor,		bsc,	
																NULL);
	}
#endif

}



/*F--------------------------------------------------------------------------
 *  Function:	xUIsetUnselectColor ()
 *					-restore background found in foreground
 *					-compute best foreground for label text
 *  In:			-a widget  
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUIsetUnselectColor (Widget w)
{
	Pixel			fg, bsc, tsc;

#ifdef ps_unix

	/*------ init work ------*/
	if (w)
	{
		XtVaGetValues(w,	XmNforeground,				&fg,
								XmNbottomShadowColor,	&bsc,	
								XmNtopShadowColor,		&tsc,	
																NULL);
		XtVaSetValues(w,	XmNbackground,				fg,
								XmNbottomShadowColor,	tsc,	
								XmNtopShadowColor,		bsc,	
																NULL);
		xUIsetBestForeground (w);
	}

#endif

}




/*F--------------------------------------------------------------------------
 *  Function:	xUIsetBestForeground ()
 *					-get values and colors for a specified background 
 *					-set the computed foreground value in widget
 *  In:			-a widget  
 *  out:			-
 *  Return:		-best foreground 
 *---------------------------------------------------------------------------
 */
void	xUIsetBestForeground ( Widget w )
{
	Pixel			fg, bg, top, bottom, select ;
	Colormap		cmap;
	Screen		*screen;

	/*--- get colors -------------------------------------*/
	XtVaGetValues(w, XmNcolormap, &cmap, NULL);
	screen  = XtScreen(w);
	XtVaGetValues(w, XmNbackground, &bg, NULL);

	/*--- calculate and set new correspondent colors ------*/
	XmGetColors(screen, cmap, bg, &fg, &top,
					&bottom, &select);
	XtVaSetValues(w,	XmNforeground,				fg,
							XmNtopShadowColor,		top,
							XmNbottomShadowColor,	bottom,
															NULL);

}
