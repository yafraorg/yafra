/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  callback
 * describe:  pressed OK and CANCEL
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.2 $
 **************************************************************/
static char rcsid[]="$Id: cb-options.c,v 1.2 2004-03-05 14:23:33 mwn Exp $";

#include <gtk/gtk.h>
#include <stdio.h>

#ifdef ps_unix
#ifndef ps_cygwin
#include <unistd.h>
#endif
#include <sys/types.h>
#include <pwd.h>
#endif

#include "callbacks.h"
#include "interface.h"
#include "support.h"

/* MARCO POLO GTK GUI includes */
#include <mpgtk.h>


