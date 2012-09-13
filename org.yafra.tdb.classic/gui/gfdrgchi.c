/*D************************************************************
 * Modul:		GRAPHIC						gfdrgchi.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdrgchi.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gfdrgchi.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:42  ja
 general version

 * Revision 1.3  94/02/18  10:38:03  10:38:03  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:33  00:25:33  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdrgchi.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



long xGRfind_regionchildren(
REGOBJ *vater,
long **ind,
int mode
)
{
	extern REGOBJ *regObj;
	extern long anzregObj;

	REGOBJ *akt, *aktvater;
	long z;
	long anzahl;
	long indvater;

	*ind = 0;
	for (anzahl=0, z=0; z<anzregObj; z++) {
		akt = &regObj[z];
		indvater = akt->indVater;
		if (indvater != NOVATER) {
			aktvater = &regObj[indvater];
			if (aktvater == vater) {
				if (mode == REGDEF && akt->region) {
					*ind = (long *)realloc(*ind, (anzahl+1)*sizeof(long));
					(*ind)[anzahl] = z;
					anzahl++;
				} else if (mode == REGALL) {
					*ind = (long *)realloc(*ind, (anzahl+1)*sizeof(long));
					(*ind)[anzahl] = z;
					anzahl++;
				}
			}
		}
	}
	return(anzahl);
}
