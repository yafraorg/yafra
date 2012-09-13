/*D************************************************************
 * Modul:		GRAPHIC						grdregz.c
 *
 *					Read the regions booking status from DBI	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/grdregz.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: grdregz.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:03  ja
 general version

 * Revision 1.3  94/02/18  10:38:27  10:38:27  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:02  00:26:02  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/grdregz.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


Boolean xGRread_regions_zustand()
{
	extern long anzregObj;
	extern REGOBJ *regObj;
	extern char *entries;
	extern Display *display;
	extern GRAWINDOWS grawindows;

	long i;
	char *ptr;
	REGOBJ *akt;

	/* Regions ausgeben */
	for (i=0, ptr=entries; i<anzregObj; i++) {
		akt = &regObj[i];
		memcpy((void *)&akt->zustand, (void *)ptr, sizeof(unsigned char));
		ptr += sizeof(unsigned char);
	}
	XClearArea(display, grawindows.graphik, 0, 0, 0, 0, True);
	return(True);
}
