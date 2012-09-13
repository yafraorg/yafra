/*D************************************************************
 * Modul:		GRAPHIC							gwrreg.c
 *
 *					Write regions from memory to DB
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gwrreg.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: gwrreg.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:26  ja
 general version

 * Revision 1.7  94/02/18  10:40:04  10:40:04  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.6  93/10/23  14:20:36  14:20:36  pi (Administrator)
 * CHANGEMENTS for Rel 1.00    TTW 93
 * 
 * Revision 1.5  93/08/21  00:27:06  00:27:06  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwrreg.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";



long xGRwrite_regions_len()
{
	extern long anzregObj;
	extern REGOBJ *regObj;

	long		i, j, totlen;
	REGOBJ	*akt, *vater;
	char    loc[512];

	/*-- Check for total length of stuff ----------------*/
	for (i=0, totlen=0;  i<anzregObj;  i++)
	{
		akt = &regObj[i];
		/*-- Check if region defined ------*/
		if (akt->anzEckpunkte >0)
		{
			totlen += strlen(akt->Regionname);
			if (akt->indVater != NOVATER)				/*add father if any*/
			{
				totlen += TRENNERLEN;					
				vater = &regObj[akt->indVater];
				totlen += strlen(vater->Regionname);
			}
			totlen += sizeof(char);
			sprintf(loc, "%d\n", akt->anzEckpunkte);
			totlen += strlen(loc);
			for (j=0; j<akt->anzEckpunkte; j++) {
				sprintf(loc, "%d\n", akt->Eckpunktnum[j]);
				totlen += strlen(loc);
			}
		}
	}
	return( totlen);
}





Boolean xGRwrite_regions( char *destbuf)
{
	extern long anzregObj;
	extern REGOBJ *regObj;

	long		i, j;
	int		len;
	char		*ptr;
	REGOBJ	*akt, *vater;
	char		buffer[512];

	ptr = destbuf;
	/*--- Send regions Objects --------------------------*/
	for (i=0;  i<anzregObj;  i++) {
		akt = &regObj[i];
		/*--- Only defined regions ------*/
		if (akt->anzEckpunkte >0)
		{
			if (akt->indVater == NOVATER) {
				sprintf( buffer, "%s", akt->Regionname);
			} else {
				vater = &regObj[akt->indVater];
				sprintf( buffer, "%s%s%s", akt->Regionname, TRENNER, vater->Regionname);
			}
			len = strlen(buffer);
			memcpy((void *)ptr, (void *)buffer, len);
			ptr += len;
			*ptr = '\n';
			ptr++;
			sprintf(ptr, "%d\n", akt->anzEckpunkte);
			ptr += strlen(ptr);
			for (j=0; j<akt->anzEckpunkte; j++)
			{
				sprintf(ptr, "%d\n", akt->Eckpunktnum[j]);
				ptr += strlen(ptr);
			}
		}
	}
	*ptr = '\0';
	return(True);
}
