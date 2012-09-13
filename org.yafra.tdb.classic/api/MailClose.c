/*D***********************************************************
 * Modul:     API - close mail file
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/MailClose.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

int MailClose(FILE *fpmail, char *filename)
{
	extern int errno;
	int status = (int)MPOK;
	char tmpfile[_RECORDLEN];

#ifdef ps_unix
	(void)fclose(fpmail);
	/*-- wait send termination  before unlinking -----*/
	(void)sprintf(tmpfile, "/tmp/%s", filename);
	sleep(3); 
	if (unlink(filename) == (int)-1) 
		{
		MailAdd(fpmail, strerror(errno));
		status = (int)MPERROR;
		}
#endif

	return(status);
}
