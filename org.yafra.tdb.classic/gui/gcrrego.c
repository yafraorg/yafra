/*D************************************************************
 * Modul:		GRAPHIC							gcrrego.c
 *
 *	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcrrego.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

#define ANZMEMREG 500

void xGRcreate_regobj(REGOBJ *newobj)
{
	extern long anzregObj;
	extern REGOBJ *regObj;

	static long resregObj = 0;

	int			i;
	REGOBJ		*aktobj;
	REGIONPOINT p;

	/*--- check if enough place for new ---*/
	regObj = (REGOBJ *)xUIalloc((void *)regObj, &resregObj, ANZMEMREG,
											anzregObj+1, sizeof(REGOBJ));

	/*--- add at queue of array -----------*/
	aktobj = &regObj[anzregObj];
	memcpy((void *)aktobj, (void *)newobj, sizeof(REGOBJ));

	/*--- find regionPoints  --------------*/
	for (i=0;  i<aktobj->anzEckpunkte;  i++) {
/*		p.p.x = aktobj->Eckpunkte[i].x;  */
/*		p.p.y = aktobj->Eckpunkte[i].y;  */
		p.n = aktobj->Eckpunktnum[i];

		xGRfind_regionpoint( &p, MODE_NUM);             /* n=0 if not found */

		aktobj->Eckpunkte[i].x = p.p.x;
		aktobj->Eckpunkte[i].y = p.p.y;
		aktobj->Eckpunktnum[i] = p.n;
	}
	anzregObj++;
}

#ifdef DEBUG_REGION
void xGRcreate_regobj_file(void)
{
	extern long				anzregObj;
	extern REGOBJ			*regObj;
	extern GRAWIDGETS		grawidgets;

	REGOBJ		*aktobj;
	long			i,j; 
	FILE			*fp;

	/*--- Open file to write ----------*/
	fp = fopen( "regionobjects", "w");
	if (!fp) {
		xUIfehler(XGRGRAFILEOPEN, grawidgets.shell);
		return;
	}

	/*--- region objects -------*/
	for ( i=0; i < anzregObj;  i++)  {
		aktobj = &regObj[i];
		fprintf(fp, "%s   %d \n", aktobj->Regionname, aktobj->anzEckpunkte );
		/*--- eckpunkte -------*/
		for (j=0;  j<aktobj->anzEckpunkte;  j++) {
			fprintf(fp, "%d \n", aktobj->Eckpunktnum[j] );
/*******
			fprintf(fp, "%d %ld %ld \n", aktobj->Eckpunktnum[j], aktobj->Eckpunkte[j].x,
													aktobj->Eckpunkte[j].y       );
*******/
		}
	}  

	/*--- close file  ----------*/
	fclose(fp);
}
#endif
