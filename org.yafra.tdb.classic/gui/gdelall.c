/*D************************************************************
 * Modul:		GRAPHIC							gdelall.c
 *
 *					Delete all grafobjects and regionObj
 *					Deselect region list items
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gdelall.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gdelall.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:30  ja
 general version

 * Revision 1.3  94/02/18  10:37:49  10:37:49  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:16:13  00:16:13  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdelall.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



XtCallbackProc xGRdeleteall(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern unsigned long anzregionPoints;
	extern long		anzgrafObj;
	extern long		anzregObj;
	extern REGOBJ	*regObj;
	extern GRAFOBJ *grafObj;
	extern Display *display;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;

	long i;

	/*--- regionObject clear and free mem of structures --------*/
	for (i=anzregObj-1; i>=0; i--) {
		xGRdelete_region(0, (XtPointer)&regObj[i], 0);
	}
	anzregObj = 0;               /* memory of array is conserved */

	/*--- List deselection -------------------------------------*/
	XmListDeselectAllItems( grawidgets.select);

	/*--- GrafObjects clear and free mem of private xpoints and region points -*/
	for (i=anzgrafObj-1;  i>=1;  i--) {					 
		xGRdelete_grafobj(&grafObj[i]);			/* !keep drawing area grafObj[0] */
	}

	/*--- Delete regionPoints sorted array, keep drawing area ------*/
	anzregionPoints = 4;

}
