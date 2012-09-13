/*D************************************************************
 * Modul:		GRAPHIC							gmove.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gmove.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gmove.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:56  ja
 general version

 * Revision 1.3  94/02/18  10:38:18  10:38:18  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:52  00:25:52  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gmove.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



void xGRmove(
XEvent *event,
int tog
)

{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
        extern GRAGLOB graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAWINDOWS grawindows;
        extern XPoint   punkt[];

	static GRAFOBJ *tempObj;

	int            typ;
	Boolean        ok;
 
	typ = graglob.eingabe;
	if (typ == 0) {
		XmTextSetString(grawidgets.frage, FRAGE_MOVE0);
		graglob.eingabe = 1;
	} else if (typ == 1) {
		ok = xGRget_koord(event, &punkt[0]);
		if (!ok) return;
		ok = xGRfind_object(punkt[0], &tempObj);
		if (!ok) return;
		XmTextSetString(grawidgets.frage, FRAGE_MOVE1);
		graglob.tempObj = tempObj;
		graglob.eingabe = 2;
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	} else if (typ == 2) {
                ok = xGRget_koord(event, &punkt[1]);
                if (!ok) return;
		xGRcopy_object(punkt[0], punkt[1], tempObj, tog);
		graglob.tempObj = 0;
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);

		XmTextSetString(grawidgets.frage, FRAGE_MOVE0);
		graglob.eingabe = 1;

	}
}
