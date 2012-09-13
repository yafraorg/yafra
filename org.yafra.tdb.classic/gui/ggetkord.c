/*D************************************************************
 * Modul:		GRAPHIC							ggetkord.c
 *
 *					Get coordinates from	
 *					- user input line 
 *					- graphik (drawing area)
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/ggetkord.c,v 1.2 2008-11-02 19:55:44 mwn Exp $

 Log Information:
 $Log: ggetkord.c,v $
 Revision 1.2  2008-11-02 19:55:44  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:50  ja
 general version

 * Revision 1.3  94/02/18  10:38:12  10:38:12  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:39  00:25:39  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ggetkord.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";


Boolean xGRget_koord(
XEvent *event,
XPoint *newpunkt
)

{
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB graglob;
	XPoint punkt;
	WCVALUE a = -1, b = -1;
	char *koordbuffer;
	Boolean ok;

	punkt.x = -1;
	punkt.y = -1;

	if (event->xany.window == XtWindow(grawidgets.antwort)) {
		koordbuffer = XmTextGetString(grawidgets.antwort);
		if (sscanf(koordbuffer, "%f %f", &a, &b) == 2)
			xGRget_point( (int)(a*graglob.xfak), (int)(b*graglob.yfak), &punkt);
		if (sscanf(koordbuffer, "%f, %f", &a, &b) == 2)
			xGRget_point( (int)(a*graglob.xfak), (int)(b*graglob.yfak), &punkt);
		XtFree((void *)koordbuffer);

	} else if (event->xany.window == XtWindow(grawidgets.graphik)) {
		xGRget_point( event->xbutton.x, event->xbutton.y, &punkt);
	}

	/*--- check results ----*/
	if (punkt.x < 0 || punkt.y < 0) {
		ok = False;
		xUIbeep(grawidgets.antwort, 0, 0, 0);
		newpunkt->x = -1;
		newpunkt->y = -1;
	} else {
		ok = True;
		newpunkt->x = punkt.x;
		newpunkt->y = punkt.y;
	}
	return(ok);
}
