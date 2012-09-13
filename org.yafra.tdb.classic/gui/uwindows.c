/*D***********************************************************
 * Modul:     GUI - dialog			uwindows.c
 *             
 *					Recursiveley find all active windows 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/uwindows.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: uwindows.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:04:51  ja
 general version

 * Revision 1.4  94/02/18  10:45:01  10:45:01  ja (Jean-Marc Adam)
 * Name change for DOS
 * 
 * Revision 1.3  93/11/10  08:32:18  08:32:18  ja (Jean-Marc Adam)
 * rcsid
 * 
 * Revision 1.2  93/04/06  18:02:12  18:02:12  ja (Jean-Marc Adam)
 * "Header"
 * 
			 Erstellt am 17.07.91 pi
 * 
*/

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uwindows.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


void xUIwindows(Window topwin, int *anz, Window *win, int maxwins, Boolean build, Boolean *ok)
{
	extern Display *display;

	Window		root_return, parent_return, *children;
	int			i, j, anzchildren;

	XQueryTree(display, topwin, &root_return, &parent_return, &children, (unsigned int *)&anzchildren);
	if (anzchildren > 0) {
		for (i=0; i<anzchildren; i++) {
			xUIwindows(children[i], anz, win, maxwins, build, ok);
		}
		XFree((void *)children);
	}
	if (build) {
		if (*anz < maxwins)
			win[*anz] = topwin;
	}
	(*anz)++;
	if (*anz <= maxwins) *ok=TRUE;
	else                 *ok=FALSE;
	return;
}
