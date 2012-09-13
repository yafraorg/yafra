/*D*************************************************************************
 * Modul:			GUI - Dialog		   ucursor.c 
 *            
 * Description:	Build a cursor with a bitmap
 *						
 *
 * Functions:
 * 
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

/*R
   RCS Information:
   $Header: /yafra/cvsroot/mapo/source/gui/ucursor.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

   Log Information:
   $Log: ucursor.c,v $
   Revision 1.2  2008-11-02 19:55:43  mwn
   re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

   Revision 1.1.1.1  2002-10-26 21:10:43  mwn
   inital release

   Revision 3.1  1997/04/02 06:50:03  mw
   NT 4.0 release und WWW Teil

   Revision 2.1  1994/03/28 11:03:47  ja
   general version

 * Revision 1.3  94/02/18  10:40:17  10:40:17  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/06/09  10:46:29  10:46:29  ja (Jean-Marc Adam)
 * "Header"
 * 
 * 
			 erstellt am 10.10.91 pi
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ucursor.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xUIcursor ()
 *					-create a cursor
 *					-
 *  In:			-ptrs to display, bitmapfore, bitmapback, fgcolor, bgcolor
 *  out:			-
 *  Return:		-0 or cursor
 *---------------------------------------------------------------------------
 */
Cursor xUIcursor( Display *display, char *bitmapfore, char *bitmapback,
						char *fgcolor, char *bgcolor )
{
	Pixmap   fgcurspix;
	Pixmap   bgcurspix;
	Cursor   cursor;
	XColor   fg;
	XColor   bg;
	XColor   dummy;
	Colormap cmap;
	unsigned long hotspot_x;
	unsigned long hotspot_y;
	unsigned long hotspot_z;

	cursor = 0;
	fgcurspix = xUIpixmap(display, bitmapfore, &hotspot_x, &hotspot_y);
	bgcurspix = xUIpixmap(display, bitmapback, &hotspot_z, &hotspot_z);
	if (fgcurspix && bgcurspix) {
		cmap = XDefaultColormap(display, 0);
		XLookupColor(display, cmap, fgcolor, &fg, &dummy);
		XLookupColor(display, cmap, bgcolor, &bg, &dummy);
		cursor = XCreatePixmapCursor(display, fgcurspix, bgcurspix,
		&fg, &bg, hotspot_x, hotspot_y);
	}
	return(cursor);
}
