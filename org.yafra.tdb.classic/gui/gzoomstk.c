/*D************************************************************
 * Modul:		GRAPHIC							gzoomstk.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gzoomstk.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: gzoomstk.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:28  ja
 general version

 * Revision 1.3  94/02/18  10:40:06  10:40:06  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:27:10  00:27:10  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gzoomstk.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



void xGRzoomstack(
ZOOM *zoom,
int *anzZoom,
int start,
int diff
)

{
	ZOOM *new, *old;
	int i;

	for (i=start; i<*anzZoom-diff; i++) {
		new = &zoom[i];
		old = new+diff;
		memcpy((void *)new, (void *)old, sizeof(ZOOM));
	}
	*anzZoom -= diff;
}
