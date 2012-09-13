/*D************************************************************
 * Modul:		GRAPHIC							gdelete.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdelete.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: gdelete.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:31  ja
 general version

 * Revision 1.3  94/02/18  10:37:50  10:37:50  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:15:52  00:15:52  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdelete.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


void xGRdelete(
XEvent *event,
int tog
)

{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
        extern GRAGLOB graglob;
        extern XPoint   punkt[];

	static GRAFOBJ *tempObj;

	int            typ;
	Boolean        ok;
 
	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_DELETE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		ok = xGRfind_object(punkt[0], &tempObj);
		if (!ok) return;
		graglob.tempObj = tempObj;
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
		graglob.eingabe = 2;
	} else if (typ == 2) {
		graglob.tempObj = 0;
		xGRdelete_grafobj(tempObj);
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
		XmTextSetString(grawidgets.frage, FRAGE_DELETE0);
		graglob.eingabe = 1;
	} 
}
