/*D************************************************************
 * Modul:		GUI - Dialog					 uiconpix.c
 *                                                        
 * 				Build an ICON for a TOPLEVEL SHELL
 *                                                        
 * Uebergabe: Toplevel Widget               
 *            Bitmap File / Bitmap Buffer 
 *            Vorder- und Hintergrund als Pixel 
 *                                              
 * Copyright: yafra.org, Basel, Switzerland 
 * Autor:     Administrator, yafra 
 **************************************************************/
/*R
   RCS Info
   $Header: /yafra/cvsroot/mapo/source/gui/uiconpix.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

   Log Info
   $Log: uiconpix.c,v $
   Revision 1.2  2008-11-02 19:55:42  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:04:00  ja
   general version

 * Revision 1.5  94/02/18  10:44:16  10:44:16  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.4  93/06/09  10:48:12  10:48:12  ja (Jean-Marc Adam)
 * "Header"
 * 
 * Revision 1.3  93/05/05  21:40:03  21:40:03  mw ()
 * "error handling"
 * 
 * Revision 1.2  93/01/03  21:43:39  21:43:39  mw ()
 * "new app-defaults"
 * 
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uiconpix.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


Boolean xUIiconpixmap(Widget parent, char *bitmap_filename)
{
	extern Display     *display;

	Arg    args[10];
	register int ac;
	Pixmap  pix;
	Screen  *scrn;
	Window window, root;
	int x, y;
	unsigned int width, height, border_width, depth;
	Pixel fg, bg;

	fg = 30;
	bg = 33;
	scrn = XtScreen(parent);
	pix = XmGetPixmap(scrn, bitmap_filename, fg, bg);
	if (pix == (Pixmap)XmUNSPECIFIED_PIXMAP)
		return(False);

	ac = 0;
	XtSetArg(args[ac], XmNiconWindow, &window); ac++;
	XtGetValues(parent, args, ac);
	if (!window)
		{
		if (!XGetGeometry(display, pix, &root, &x, &y, &width, &height,
			&border_width, &depth) || !(window = XCreateSimpleWindow(display,
			root, 0, 0, width, height, (unsigned)0, CopyFromParent,
			CopyFromParent)))
			{
			ac=0;
			XtSetArg(args[ac], XmNiconPixmap, pix); ac++;
			XtSetValues(parent, args, ac);
			return(True);
			}
		ac=0;
		XtSetArg(args[ac], XmNiconWindow, window); ac++;
		XtSetValues(parent, args, ac);
		}
	XSetWindowBackgroundPixmap(display, window, pix);
	XClearWindow(display, window);		
	return(True);
}
