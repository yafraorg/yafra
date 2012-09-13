/*D***********************************************************
 * descr:     Action - include               mpact.h
 *            main include for action main() function defined
 *            in mpactdb.h and mpactmem.h
 *
 * Copyright: yafra.org, Switzerland, 2004
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpact.h,v 1.2 2004-01-23 16:48:29 mwn Exp $
*/


/************************************************************
 * Sektion:  default/system includes
 *************************************************************/
#include <stdio.h>         /* Standart Includefile */
#include <ctype.h>         /* Standart Typendefinitionen */
#include <memory.h>        /* Definitionen von memset etc. */
#include <errno.h>         /* Fehlermeldungen im System */
#include <string.h>        /* Sring Konst. und Memory Definitionwn */
#include <malloc.h>        /* Definitionen von alloc etc. */
#include <sys/types.h>     /* File Status Definitionen */
#include <sys/stat.h>      /* File Status Definitionen */
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <math.h>

#ifndef ps_win
#include <sys/time.h>      /* Definitionen von time etc. */
#include <sys/param.h>
#include <unistd.h>        /* UNIX System V Definitionen */
#endif

#include <psportable.h>
#include <pssys.h>

/************************************************************
 * Sektion:  MARCO POLO includes
 *************************************************************/

/* comm defines for MARCO POLO library */
#include <mpcomm.h>        /* Definitionen f�r das MarcoPolo Protokoll    */
extern COMMOBJ comm;

/* Object length */
#include <mpstrlen.h>

/* Objektdefinitionen (defines and structures) */
#include <mpobjdef.h>
#include <mpobjvar.h>
#include <mpobjact.h>

/* Statusobjektdefinitionen */
#include <mpstadef.h>

/* General definitions */
#include <mpdef.h>

/* Action definitions and typedefs */
#include <mpdefact.h>


/*--- Prototypes ------------------*/
#include <mpproapi.h>
#include <mpproact.h>
#include <mpprolib.h>


