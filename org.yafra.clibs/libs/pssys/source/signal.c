/**************************************************************
 * modul:     signal handling
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/signal.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <signal.h>

/* piso includes */
#include <pssys.h>


/************************************************************
 * install a signal handler
 *
 * install a signal handler
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
void PSSYSinstallSignal(int aSignal,      /* signal */
                        int (*function)() /* function for calling */)
{
	/* install signal handler */
	(void)signal(aSignal, function);
}
