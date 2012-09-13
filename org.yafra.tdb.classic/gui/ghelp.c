/*D************************************************************
 * Modul:		GRAPHIC							ghelp.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/ghelp.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: ghelp.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:52  ja
 general version

 * Revision 1.3  94/02/18  10:38:14  10:38:14  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:44  00:25:44  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ghelp.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


void xGRhelp(
XEvent *event,
int n
)

{
	extern GRAWIDGETS grawidgets;
	extern MENU menu[];
	extern MENU glob;
	extern int aktmenuz[];
	extern int aktmenu;

	static MENU tmp;
	MENU *a;

	switch (n) {
		case BUTTONHILFE_GRAPHIK:
			a = &tmp;
			break;
		case BUTTONHILFE_MENUGLOBAL:
			a = &glob;
			break;
		case BUTTONHILFE_MENUNUMMER:
			a = &menu[aktmenu[aktmenuz]];
			break;
		case BUTTONHILFE_APPLICATION:
			a = &glob;
			break;
	}
	xUIhelp(grawidgets.shell, a, 0);
}
