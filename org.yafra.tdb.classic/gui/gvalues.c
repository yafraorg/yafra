/*D************************************************************
 * Modul:		GRAPHIC							gvalues.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gvalues.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gvalues.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:12  ja
 general version

 * Revision 1.3  94/02/18  10:38:36  10:38:36  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:18  00:26:18  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gvalues.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";



Boolean xGRvalues(
short *value,
char *str,
int mode
)

{
	extern GRAGLOB graglob;

	short old;
	Boolean redraw;
	double wert;

	old = *value;
	wert = atof(str);
	if (mode == XGRMM) {
		wert = wert*graglob.xfak;
	}
	*value = wert;
	if (*value <= 0 || *value > 32000)
		*value = 0.;
	if (old != *value)
		redraw = True;
	else
		redraw = False;
	return(redraw);
}
