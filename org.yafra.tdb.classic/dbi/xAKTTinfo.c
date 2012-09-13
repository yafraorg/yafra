/*D***********************************************************
 * Modul:     DBI - database info
 *            Liste mit Aktionstypen der Aktionen
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTTinfo.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int AKTTinfo(char *buffer )
{
	extern int sprache;
	extern MEMOBJ sqlmem;
	extern int DebugFlag;
	extern char glob_bez_aktt[];
	extern char sqlquery[];

	AKTIONSPARA *para;
	AKTIONS_TYP aktt;

	char tmp_buffer[_CHARMAXLEN];
	int status=(int)MPOK;
	int i, anzahl, anzchar;

	if (MPAPIselectEntry((int)_AKTIONS_TYP, glob_bez_aktt, (char *)&aktt,
		      sizeof(AKTIONS_TYP), sizeof(aktt.a_typ_id) ) != (int)_UNDEF )
		{
		(void)sprintf(sqlquery, _SEL_PARA_AKTT, aktt.a_typ_id);
		status=MPAPIdb_sqlquery((int)_AKTIONSPARA, &sqlmem.buffer, sqlquery,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);

		if ( anzahl == (int)0 || status != (int)MPOK)
			{
			UtilMsg((int)MPE_NOAKTT, MSGTYP_ERROR, NULL);
			status = (int)MPWARNING;
			}
		else
			{
			para = (AKTIONSPARA *)sqlmem.buffer;

			(void)strcpy(buffer, " Aktionstypinfo mit Parametern\n\n ");
			(void)copyTextTo(tmp_buffer, glob_bez_aktt, (int)_BEZLEN);
			anzchar=(int)strlen(tmp_buffer) - 1;
			(void)strcat(buffer, tmp_buffer);
			(void)strcat(buffer, "\n ");
			for ( i=0; i<anzchar; i++ )
				{
				strcat(buffer, "=");
				}

			if (DebugFlag)
				{
				(void)sprintf(tmp_buffer, "\n\n (AKTT DEBUG-ID: %d)", aktt.a_typ_id);
				(void)strcat(buffer, tmp_buffer);
				}

			(void)strcat(buffer, "\n\n");

			(void)copyTextTo(tmp_buffer, aktt.proz, (int)_PROZLEN);
			(void)strcat(buffer, tmp_buffer);
			for (i=0; i<anzahl; i++)
				{
				(void)strcat(buffer, " ");
				(void)copyTextTo(tmp_buffer, para[i].bez, (int)_PARALEN);
				if (para[i].muss != (int)TRUE)
					{
					strcat(buffer, "[");
					strcat(buffer, tmp_buffer);
					if (para[i].flag != (int)TRUE)
						strcat(buffer, " 999");
					strcat(buffer, "]");
					}
				else
					{
					strcat(buffer, tmp_buffer);
					if (para[i].flag != (int)TRUE)
						strcat(buffer, " 999");
					}
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NOAKTT, MSGTYP_ERROR, NULL);
		status = (int)MPWARNING;
		}

	return(status);
}
