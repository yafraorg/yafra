/*D************************************************************
 * Modul:		GRAPHIC							gfdrgnam.c
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
 $Header: /yafra/cvsroot/mapo/source/gui/gfdrgnam.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: gfdrgnam.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:44  ja
 general version

 * Revision 1.3  94/02/18  10:38:06  10:38:06  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/21  00:25:31  00:25:31  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdrgnam.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";



long xGRfind_region_name(
char *name
)
{
	extern REGOBJ *regObj;
	extern long anzregObj;

	REGOBJ *akt;
	long z;

	if (name)
	{
		for (z=0; z<anzregObj; z++) {
			akt = &regObj[z];
			if (strcmp(akt->Regionname, name) == 0)
				return(z);
		}
	}
	return(NOVATER);
}
