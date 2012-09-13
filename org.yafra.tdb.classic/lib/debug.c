/**************************************************************/
/* Modul:     debugging function for MARCO POLO               */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpdef.h>
#include <mpprolib.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/debug.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

void MPdebug(int debugtyp, char *msg, char *file)
{
	(void)fprintf(stderr, "debug: %s", msg);
}
