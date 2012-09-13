/*D**********************************************************
 * Header:    travelDB
 *            MAIN header for GUI and DBI
 *
 * Copyright: yafra.org, Switzerland, 2004
 ************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpmain.h,v 1.2 2004-01-23 16:48:29 mwn Exp $
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
#include <math.h>

#ifndef ps_win
#include <sys/time.h>      /* Definitionen von time etc. */
#include <sys/param.h>
#include <unistd.h>        /* UNIX System V Definitionen */
#endif

#include <psportable.h>    /* PISO defines to be portable UNIX <-> WIN */
#include <pssys.h>

/************************************************************
 * Sektion:  MarcoPolo includes
 *************************************************************/

/* Message Codes as defines */
#include <mpmsg.h>

/* String length */
#include <mpstrlen.h>

/* Objektdefinitionen (defines and structures) */
#include <mpobjdef.h>
#include <mpobjvar.h>
#include <mpobjact.h>

/* Statusobjektdefinitionen */
#include <mpstadef.h>

/* internal MENU defines */
#include <mpmendef.h>

/* Kommunikationsdefinitionen */
#include <psipc.h>         /* Definitionen f�r IPC und PIPE Kommunikation */
#include <mpcomm.h>        /* Definitionen f�r das MarcoPolo Protokoll    */
extern COMMOBJ comm;
#define SERVICE     "marcopolo"
#define PROT        "tcp"

/* global defines */
#include <mpdef.h>

/*!!! Output Menu nur Temporaer */
#define DEFAULTFIELDS  4
