/*D************************************************************
 * Modul:		GRAPHIC						gselstat.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gselstat.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gselstat.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:06  ja
 general version

 * Revision 1.3  94/02/18  10:38:30  10:38:30  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:05  00:26:05  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gselstat.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";




void xGRselect_changestatus( REGOBJ *region, Boolean status )
{
	extern char			*xgrLabelTable[][XGRLABMAXTEXTS];
	extern Display *display;
	extern GRAWIDGETS grawidgets;
	extern REGOBJ  *regObj;

	char		selbuf[512];
	char		*staptr;
	int		pos, i;
	XmString eintrag;

	if (status)	{
		staptr = LABEL_REGIONDEFINED;
	} else {
		staptr = LABEL_REGIONUNDEFINED;
	}
	pos = region-regObj+1;
	XmListDeletePos(grawidgets.select, pos);
	i = region->indVater;
	if (i != NOVATER) {
		sprintf(selbuf, "%s%s%s%s%s", staptr, SELECTTRENNER,
							region->Regionname, TRENNER, regObj[i].Regionname);
	} else {
		sprintf(selbuf, "%s%s%s", staptr, SELECTTRENNER,
							region->Regionname);
	}
	eintrag = XmStringCreateSimple(selbuf);
	XmListAddItem(grawidgets.select, eintrag, pos);
	XmStringFree(eintrag);
}
