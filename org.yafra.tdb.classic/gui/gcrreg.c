/*D************************************************************
 * Modul:		GRAPHIC							gcrreg.c
 *
 *					Create an X region. Delete old if existent.	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gcrreg.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gcrreg.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:26  ja
 general version

 * Revision 1.3  94/02/18  10:37:46  10:37:46  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:15:46  00:15:46  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrreg.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";



/* xGRbuild_regions kreiert Regions. Vorher muessen Anzahl_Regs  */
/* Regionstructuren eingelesen werden.                           */
/* Die Vaterregions muessen vor den Sohnregions eingelesen       */
/* und definiert werden.                                         */
/* dieses UP wird nach delete, move und beim Start aufgerufen.   */


void xGRcreate_region(
REGOBJ *akt
)

{
	extern GRAGLOB graglob;
	extern long anzregObj;
	extern REGOBJ *regObj;

	REGOBJ *aktvater;
	XPoint *anf;

	Region reg      = XCreateRegion();
	Region leer_reg = XCreateRegion();


	/*--- Pre-condition ------------*/
	if(akt->anzEckpunkte < 4)
		return;

	if (akt->indVater != NOVATER) {
		aktvater = &regObj[akt->indVater];
	} else {
		aktvater = 0;
	}

	/*--- clear old  ---------------*/
	if (akt->region)
		XDestroyRegion(akt->region);

	/*--- Create new polygon -------*/
	anf = &akt->Eckpunkte[1];
	akt->region = XPolygonRegion(anf, akt->anzEckpunkte-1, WindingRule);

	/*--- insert in parent ---------*/
	if (aktvater) {
		XSubtractRegion(aktvater->region, akt->region, reg);
		XUnionRegion(reg, leer_reg, aktvater->region);
	}

	XDestroyRegion(reg);
	XDestroyRegion(leer_reg);
}
