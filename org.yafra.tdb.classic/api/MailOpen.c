/*D***********************************************************
 * Modul:     API - open mail file
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

#include <fcntl.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/MailOpen.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

#define DEFAULTMAILHEADER "Default mailheader for MARCO POLO actions"

#define _MAIL_TMPFILE   "MAIL_XXXXXX"

FILE *MailOpen(char *filename, int a_typ_id, int sprache)
{
	FILE *fpmail;
	AKTIONS_TYP aktt;
	char bezeichnung[_CHAR30+1];
	char *tmpfilename;
	char tmptxt[_RECORDLEN];
	int id, i;
	int status = (int)MPOK;

	(void)strcpy(tmptxt, _MAIL_TMPFILE);
	tmpfilename = mktemp(tmptxt);
	if (tmpfilename == NULL)
		return(NULL);
#ifdef ps_win
	(void)sprintf(filename, "%s.txt", tmpfilename);
	(void)sprintf(tmptxt, "\\TEMP\\%s", filename);
#else
	(void)strcpy(filename, tmpfilename);
	(void)sprintf(tmptxt, "/tmp/%s", filename);
#endif
	fpmail = fopen (tmptxt, _P_WRITE_ );
	if (fpmail == NULL)
		{
		perror("MailOpen: file open error");
		return(NULL);
		}

	if (a_typ_id != (int)_UNDEF)
		{
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		if (status == (int)MPOK)
			{
			id = MPAPIselectOneId((int)_AKTIONS_TYP, a_typ_id, (char *)&aktt);
			if (id != (int)UNDEF && SelectBez((int)_AKTIONS_TYP, sprache,
			    aktt.bez_id, bezeichnung) != (int)UNDEF)
				{
				(void)fprintf(fpmail, "%s%s%s%s", _P_EOL_, _P_EOL_, bezeichnung, _P_EOL_);
				for ( i=0; i<strlen(bezeichnung); i++ )
					(void)fprintf( fpmail, "=" );
				(void)fprintf( fpmail, "%s", _P_EOL_ );
				(void)fflush( fpmail );
				}
			else
				{
				(void)fprintf(fpmail, DEFAULTMAILHEADER);
				(void)fflush(fpmail);
				}
			(void)MPAPIdb_committrx();
			}
		}
	else
		{
		(void)fprintf(fpmail, DEFAULTMAILHEADER);
		(void)fprintf( fpmail, "%s%s", _P_EOL_, _P_EOL_ );
		(void)fflush(fpmail);
		}

	return(fpmail);
}
