/*D************************************************************
 * Modul:		GRAPHIC							gregname.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gregname.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gregname.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:04  ja
 general version

 * Revision 1.3  94/02/18  10:38:28  10:38:28  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:26:04  00:26:04  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gregname.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


XmString xGRregion_name(
REGOBJ *region,
int maxlen
)

{
	extern REGOBJ *regObj;

	char buf[90];
	XmString regionlabel;

	strcpy(buf, region->Regionname);
	if (region->indVater != NOVATER)
	{
		strcat(buf, TRENNER);
		strcat(buf, regObj[region->indVater].Regionname);
	}

	if (maxlen > 0) {
		xGRstringpos(buf, maxlen, XGRLEFT);
	}

	regionlabel = XmStringCreateSimple(buf);
	return(regionlabel);
}
