/*D************************************************************
 * Modul:		GRAPHIC                gcmpreg.c
 *
 *					Compare two region points by means of number or coor	
 *					Equality for linear lsearch
 *					Position results for Bsearch
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gcmpreg.c,v 1.2 2008-11-02 19:55:45 mwn Exp $

 Log Information:
 $Log: gcmpreg.c,v $
 Revision 1.2  2008-11-02 19:55:45  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:17  ja
 general version

 * Revision 1.4  94/02/18  10:36:11  10:36:11  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  94/02/14  15:54:42  15:54:42  ja (Jean-Marc Adam)
 * one file for num and koor compare functions
 * 
 * Revision 1.2  93/08/20  23:54:29  23:54:29  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gcmpreg.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";


int xGRcomp_regionpoint_num(
void *v1,
void *v2
)

{
	REGIONPOINT *p1 = v1;
	REGIONPOINT *p2 = v2;

	if (p1->n == p2->n) {
		return(0);
	} else {
		return(1);
	}
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRcomp_regionpoint_num_b ()
 *					-compares point numbers (PKTNR) in regionPoint structures
 *	
 *	In:			pointer to key, pointer to a value
 *	Out:
 *	Return:		 -1 (less than),  0 (equal), 1 (greater than)
 *---------------------------------------------------------------------------
 */
int xGRcomp_regionpoint_num_b( const void *vkey, const void *v )
{
	PKTNR key   = ((REGIONPOINT *)vkey)->n;
	PKTNR value = ((REGIONPOINT *)v)->n;

	if (key < value) 
		return(-1);
	else if (key == value)
		return(0);
	else 	
		return(1);		
}



/*F--------------------------------------------------------------------------
 *  Function:	xGRcomp_regionpoint_kor ()
 *	            Compare two region points by means of coordinates
 *	In:			2 regionpoints
 *	Out:
 *	Return:		0 (equal), 1 (not equal),
 *---------------------------------------------------------------------------
 */
int xGRcomp_regionpoint_kor(
void *v1,
void *v2
)

{
	REGIONPOINT *p1 = v1;
	REGIONPOINT *p2 = v2;

	if ((p1->p.x - p2->p.x) == 0 && (p1->p.y - p2->p.y) == 0) {
		return(0);
	} else {
		return(1);
	}
}
