/*H************************************************************
 * header:    global include for the security/modul library
 *
 * copyright: Yafra.org
 **************************************************************/
/*R
  RCS Information:
  $Header: /yafraorg/cvsroot/foundation/ansic/include/psmodul.h,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $
*/

#ifndef _PSMODUL_H
#define _PSMODUL_H

/*
	(c) Yafra.org, Switzerland

	PSmodul Interface to protect Yafra.org products.
*/


/* Application code values for PSmodul (integer in range 0 to 55)... */

#define PSCMDSRV		1		/* PS General Utilities */

#define MPDBI			10		/* tdb */
#define MPGUI			11
#define MPNET			12

#define NETCAD			20		/* cad */
#define NETCALC			21
#define MATCALC			22
#define PAXCALC			23
#define LINPLAN			24

/* return values */
#define PSMODUL_NOTALLOWED  0
#define PSMODUL_ALLOWED     1
#define PSMODUL_ERROR       2

/* Function prototypes... */
int PSmodul(int, char *, int);

#endif
