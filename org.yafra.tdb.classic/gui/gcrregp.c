/*D************************************************************
 * Modul:		GRAPHIC						gcrregp.c
 *
 *					Create a regionPoint and get the serial number	
 *					No duplicated point exists
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrregp.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

#ifdef DEBUG_REGION
extern 	FILE			*rpfile;
#endif

#define ANZMEMPKT 1000

void xGRcreate_regionpoint(REGIONPOINT *regpkt)
{
	extern unsigned long anzregionPoints;
	extern REGIONPOINT	*regionPoints;

	static unsigned long resregionPoints = 0;

	int xGRcomp_regionpoint_kor(void *, void *);
	int xGRcomp_regionpoint_num(void *, void *);
	int			(*func)(const void *, const void *);
	REGIONPOINT *found;
	long			i, j; 
	Boolean		exist;

	/*--- Alloc for array ---------------------------------------*/
	regionPoints = (REGIONPOINT *)xUIalloc((void *)regionPoints,
								(long *)&resregionPoints, ANZMEMPKT, anzregionPoints+1,
								 sizeof(REGIONPOINT));

#ifdef PS_SEARCH
	/*--- create at end when not existent -----------------------*/
	found = (REGIONPOINT *)lsearch((const void *)regpkt,
										(void *)regionPoints, (size_t)&anzregionPoints,
										sizeof(REGIONPOINT), xGRcomp_regionpoint_kor);
	/*--- search  then add -------------------------------------*/
	func = xGRcomp_regionpoint_num_b;
	found = (REGIONPOINT *)bsearch((const void *)regpkt,
					(void *)regionPoints, (size_t)anzregionPoints,
					sizeof(REGIONPOINT), func);
	if (found->n == 0) {
		found->n = anzregionPoints;
	}

#endif

	/*--- look for matching x,y -------*/
	exist = False;
	for ( j=anzregionPoints, i=0;  (i < anzregionPoints) ;  i++)  {
		found = &regionPoints[i];
		if ((regpkt->p.x == found->p.x) && (regpkt->p.y == found->p.y)) {
			j=i;
			break;
		} 
	}  

#ifdef DEBUG_REGION
	fprintf(rpfile, "i:%ld  ",  i );
#endif

	/*--- check if not found ----------*/
	if (j >= anzregionPoints) {
		found = 0;
		anzregionPoints++;
		found = (REGIONPOINT *)XtMalloc(sizeof(REGIONPOINT));
		found->n = anzregionPoints;
		found->p.x = regpkt->p.x ;
		found->p.y = regpkt->p.y ;
/*!!!		regionPoints[(anzregionPoints)-1] = *found;  */
		memcpy((void *)&regionPoints[anzregionPoints-1], (void *)found, sizeof(REGIONPOINT));

#ifdef DEBUG_REGION
		fprintf(rpfile, "rp:%ld \n",  anzregionPoints );
#endif
	} 
	
	regpkt->n = found->n;
	return;
}

#ifdef DEBUG_REGION
void xGRcreate_regionpoint_file(void)
{
	extern unsigned long anzregionPoints;
	extern REGIONPOINT	*regionPoints;
	extern GRAWIDGETS		grawidgets;

	REGIONPOINT *found;
	long			i; 
	FILE			*fp;

	/*--- Open file to write ----------*/
	fp = fopen( "regionpoints", _P_WRITE_);
	if (!fp) {
		xUIfehler(XGRGRAFILEOPEN, grawidgets.shell);
		return;
	}

	/*--- look for matching x,y -------*/
	for ( i=0; i < anzregionPoints;  i++)  {
		found = &regionPoints[i];
/*		fprintf(fp, "%d %ld %ld \n", found->n, found->p.x, found->p.y );  */
		fprintf(fp, "%d \n", found->n );
	}  

	/*--- close file  ----------*/
	fclose(fp);
}
#endif
