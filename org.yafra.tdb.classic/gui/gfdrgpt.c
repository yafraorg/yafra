/*D************************************************************
 * Modul:		GRAPHIC							gfdrgpt.c
 *
 *					Find and get a region point in array	
 *					Search by coordinates or by number
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gfdrgpt.c,v 1.2 2008-11-02 19:55:46 mwn Exp $

 Log Information:
 $Log: gfdrgpt.c,v $
 Revision 1.2  2008-11-02 19:55:46  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:45  ja
 general version

 * Revision 1.4  94/02/18  10:38:06  10:38:06  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/10/23  11:08:43  11:08:43  ja (Jean-Marc Adam)
 * no entry
 * 
 * Revision 1.2  93/08/21  00:25:36  00:25:36  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gfdrgpt.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


void xGRfind_regionpoint(
REGIONPOINT *regpkt,
int mode
)

{
	extern unsigned long anzregionPoints;
	extern REGIONPOINT *regionPoints;

	int			(*func)(const void *, const void *);
	REGIONPOINT *found;
	long			i; 

	/*--- compare on Coordinates -----------------------------*/
	if (mode == MODE_KOR) {
#ifdef PS_SEARCH  
		found = (REGIONPOINT *)lfind((const void *)regpkt,
							(void *)regionPoints, (size_t)&anzregionPoints,
							sizeof(REGIONPOINT), xGRcomp_regionpoint_kor);
#endif
		/*--- look for matching x,y -------*/
		for ( i=0; i < anzregionPoints;  i++)  {
			found = &regionPoints[i];
			if ((regpkt->p.x == found->p.x) && (regpkt->p.y == found->p.y))
				break; 
		}  
		/*--- check if not found ----------*/
		if (i >= anzregionPoints)
			found = 0;


	/*--- compare on number ----------------------------------*/
	} else if (mode == MODE_NUM) {
#ifdef PS_SEARCH
		found = (REGIONPOINT *)lfind((const void *)regpkt,
							(void *)regionPoints, (size_t)&anzregionPoints,
							sizeof(REGIONPOINT), xGRcomp_regionpoint_num);

		func = xGRcomp_regionpoint_num_b;
		found = (REGIONPOINT *)bsearch((const void *)regpkt,
						(void *)regionPoints, (size_t)anzregionPoints,
						sizeof(REGIONPOINT), func);
#endif
/******** pb with not ordered points ****
		if (regpkt->n <= anzregionPoints)
			found = &regionPoints[(regpkt->n)-1];
		else 
			found = 0;
**********/

		/*--- look for matching n -------*/
		for ( i=0; i < anzregionPoints;  i++)  {
			found = &regionPoints[i];
			if (regpkt->n == found->n)
				break; 
		}  
		/*--- check if not found ----------*/
		if (i >= anzregionPoints)
			found = 0;


	/*--- no comparison mode ---------------------------------*/
	} else {
		found = 0;
	}


	/*--- results --------------------------------------------*/
	if (found) {
		regpkt->n   = found->n;
		regpkt->p.x = found->p.x;
		regpkt->p.y = found->p.y;
	} else {
		regpkt->n = 0;
	}
	return;
}

