/*D***********************************************************
 * Modul:     API - add string to mail file
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/MailAdd.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int MailAdd(FILE *fpmail, char *mailstr)
{
	int status = (int)MPOK;

	(void)fprintf(fpmail, "%s%s", mailstr, _P_EOL_);
	(void)fflush(fpmail) ;

	return(status);
}
