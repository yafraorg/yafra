/**************************************************************/
/* Modul:     Erstelle ICON fuer eine TOPLEVEL SHELL          */
/*                                                            */
/* Uebergabe: Toplevel Widget                                 */
/*            Bitmap File / Bitmap Buffer                     */
/*            Vorder- und Hintergrund als Pixel               */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   June 1992 mw Erstellung                         */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psgui/source/icon.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* INCLUDES */
#include <X11/Xlib.h>        /* Xlib header */
#include <X11/Intrinsic.h>   /* X Toolkit prototypes */
#include <Xm/Xm.h>           /* OSF/Motif Resources */

#include <psgui.h>          /* Prototypes of Utilities */

void OSFCreateIcon(Widget parent, char *bitmap_filename, Pixel fg, Pixel bg)
{
	Arg     args[10];
	register int ac;
	Pixmap  orasicon;
	Screen  *scrn;
	Window window, root;
	Display *dpl;
	unsigned int x, y, width, height, border_width, depth;

	dpl = XtDisplay(parent);
	scrn = XtScreen(parent);
	orasicon = XmGetPixmap(scrn, bitmap_filename, fg, bg);

	ac = 0;
	XtSetArg(args[ac], XmNiconWindow, &window); ac++;
	XtGetValues(parent, args, ac);
	if (!window)
		{
		if (!XGetGeometry(dpl, orasicon, &root, &x, &y, &width, &height,
			&border_width, &depth) || !(window = XCreateSimpleWindow(dpl,
			root, 0, 0, width, height, (unsigned)0, CopyFromParent,
			CopyFromParent)))
			{
			ac=0;
			XtSetArg(args[ac], XmNiconPixmap, orasicon); ac++;
			XtSetValues(parent, args, ac);
			return;
			}
		ac=0;
		XtSetArg(args[ac], XmNiconWindow, window); ac++;
		XtSetValues(parent, args, ac);
		}
	XSetWindowBackgroundPixmap(dpl, window, orasicon);
	XClearWindow(dpl, window);		
}
