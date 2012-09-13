/*D************************************************************
 * Modul:		GRAPHIC							gfdrggra.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdrggra.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gfdrggra.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:43  ja
 general version

 * Revision 1.3  94/02/18  10:38:04  10:38:04  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:35  00:25:35  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdrggra.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



Boolean xGRfind_regiongraf(
GRAFOBJ *obj
)

{
	extern REGOBJ *regObj;
	extern long   anzregObj;

	long z, i, j;
	REGOBJ *reg;

	for (z=0; z<anzregObj; z++) {
		reg = &regObj[z];
		for (j=0; j<reg->anzEckpunkte; j++) {
			for (i=0; i<obj->anzRegionPoints; i++) {
				if (obj->regionPoint[i].n ==
				reg->Eckpunktnum[j]) {
					return(True);
				}
			}
		}
	}
	return(False);
}
