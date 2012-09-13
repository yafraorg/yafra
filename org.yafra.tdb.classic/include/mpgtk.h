/*DH**********************************************************
 * header:    MPGTK - main include for all gtk gui files
 *
 * copyright: yafra.org, Switzerland, 2004
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.4 $
 **************************************************************/

/* PISO Includes */
#include <psipc.h>
#include <pssys.h>

/* travelDB API includes */
#include <mpnet.h>
#include <mpwww.h>

/* set it to NULL if you need output on console else set it to a filename */
#define MPGTK_DBGFILE NULL
#define MPGTK_PRGNAME "mpgtk"

/* some GTK/XML error codes */
#define MPE_GTKERROR 601
#define MPE_GTKXMLERROR 602

/* some global MPGTK functions */
void MPGTKexit(int);
