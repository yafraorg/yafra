/*D************************************************************
 * Modul:		GRAPHIC							gunbook.c
 *
 *					Remove a booked region from list	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gunbook.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gunbook.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:09  ja
 general version

 * Revision 1.3  94/02/18  10:38:34  10:38:34  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:15  00:26:15  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gunbook.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



XtCallbackProc xGRunbook(
Widget w,
XtPointer Input,
XtPointer Output
)

{
	extern Display *display;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;
	extern REGOBJ *regObj;

	char *str, *end;
	int aktnummer;
	REGOBJ *region;

	XmListCallbackStruct *call_data = (XmListCallbackStruct *)Output;

	XmListDeletePos(grawidgets.booking, call_data->item_position);
	XmStringGetLtoR(call_data->item, XmSTRING_DEFAULT_CHARSET, &str);
	end = strstr(str, TRENNER);
	if (end)
	{
		*end = 0;
		aktnummer = xGRfind_region_name(str);
	}
	else 
		aktnummer = NOVATER;

	if (aktnummer != NOVATER) {
		region = &regObj[aktnummer];
		region->temp = False;
		XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	}
	XtFree((void *)str);
}
