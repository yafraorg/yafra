/*D***********************************************************
 * Modul:     API - send mail file to a user
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/MailSend.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int MailSend(char *user, FILE *fpmail, char *filename)
{
	int status=(int)MPOK;
	char command[_RECORDLEN];
	char *mailhost;

#ifdef ps_unix
	(void)sprintf(command, "mailx -s \"TDB mailing\" %s < /tmp/%s", user, filename);
	status = UtilExec(command, (int)0);
#else
	(void)fclose(fpmail);
	mailhost = getenv( "TDBSMTPHOST" );
	if (mailhost != NULL)
		{
		(void)sprintf(command, "smtpmail -h %s -s \"TDB mailing\" %s < \\\\TEMP\\\\%s", mailhost, user, filename);
		status = UtilExec(command, (int)0);
		}
#endif

	return(status);
}
