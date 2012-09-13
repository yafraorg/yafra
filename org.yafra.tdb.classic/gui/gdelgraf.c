/*D************************************************************
 * Modul:		GRAPHIC                      gdelgraf.c
 *
 *					Delete (remove) one graphic object from array	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdelgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gdelgraf.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:32  ja
 general version

 * Revision 1.3  94/02/18  10:37:51  10:37:51  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/10/23  11:02:21  11:02:21  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.1  93/07/27  09:52:53  09:52:53  ja (Jean-Marc Adam)
 * Initial revision
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdelgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


void xGRdelete_grafobj(
GRAFOBJ *tempObj
)

{
	extern GRAFOBJ *grafObj;
	extern long anzgrafObj;

	GRAFOBJ *akt;

	/*--- Free struct members -------------------------------*/
	if (tempObj->text) {
		XtFree((void *)tempObj->text);
	}
	XtFree((void *)tempObj->xpoints);
	XtFree((void *)tempObj->regionPoint);

	/*--- Array repair no hole shift rest of objects ---------*/
	for(akt=tempObj; akt-grafObj<anzgrafObj-1; akt++) {
		memcpy((void *)akt, (void *)(akt+1), sizeof(GRAFOBJ));
	}
	anzgrafObj--;
}
