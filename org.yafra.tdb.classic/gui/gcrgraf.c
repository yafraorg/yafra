/*D************************************************************
 * Modul:		GRAPHIC							gcrgraf.c
 *
 *					Add a grafObject to array	
 *					Registrate private regionPoints to public array
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gcrgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gcrgraf.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:23  ja
 general version

 * Revision 1.3  94/02/18  10:36:17  10:36:17  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:40  23:54:40  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


#define ANZMEMOBJ 500

void xGRcreate_grafobj(
GRAFOBJ *newobj
)

{
	extern long anzgrafObj;
	extern GRAFOBJ *grafObj;

	static long resgrafObj = 0;

	int i;
	GRAFOBJ *aktobj;

	/*--- add a grafObject to array ----------------------------*/
	grafObj = (GRAFOBJ *)xUIalloc((void *)grafObj, &resgrafObj, ANZMEMOBJ,
												anzgrafObj+1, sizeof(GRAFOBJ));
	aktobj = &grafObj[anzgrafObj];
	memcpy((void *)aktobj, (void *)newobj, sizeof(GRAFOBJ));

	/*--- Registrate privite regiopoints to public array --------------*/
	for (i=0;  i<aktobj->anzRegionPoints;  i++) {
		xGRcreate_regionpoint( &aktobj->regionPoint[i]);
	}
	anzgrafObj++;
}
