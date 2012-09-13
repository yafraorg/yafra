/*D***********************************************************
 * Modul:     DBI - database graphical booking
 *            choose
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRchoose.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int GRchoose(int len, char *buffer)
{
	extern char glob_dlt_bch[];
	extern char glob_dlt_res[];
	extern DIENSTLEISTUNG dtg;
	extern BUCHUNG bch;
	extern DIENST_TRAEGER dlt;

	DIENST_TRAEGER localdlt;
	int status=(int)MPOK;
	int id;
	int dltbchid;
	int dltkontid;
	int countdln;

	switch (MENUNR)
		{
		case (unsigned char)_BUCHUNG:
			if (ACTIONTYP == (unsigned char)GRASHOWINFO)
				{
				if (*buffer)
					{
					if ((strstr(buffer, TRENNER)) == NULL)
						localdlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
					else
						localdlt.stufe = 0;
					localdlt.host_id = dlt.dlt_id;
					id = MPAPIselectEntry((int)_DIENST_TRAEGER, buffer, (char *)&localdlt,
					      sizeof(DIENST_TRAEGER), sizeof(localdlt.dlt_id));
					status = DLTfree(localdlt.dlt_id, dtg.dlg_id, (int)_UNDEF,
      			       (int)_UNDEF, NULL, &countdln, &dltbchid, &dltkontid);
					if (dltbchid > 0)
						{
						(void)MPAPIselectOneId((int)_BUCHUNG, dltbchid, (char *)&bch);
						if (bch.bid == (int)_UNDEF)
							{
							UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
							return((int)MPERROR);
							}

						/* print res info: */
						status = RESinfo(len, buffer);
						comm.datalen = strlen(comm.buffer);
						COMMTYP = (unsigned char)INFO;
						}
					}
				else
					{
					comm.datalen = 0;
					comm.buffer[0] = NULL;
					}
				}
			else
				{
				(void)strcpy(glob_dlt_bch, buffer);
				comm.datalen = 0;
				comm.buffer[0] = NULL;
				}
			break;
		case (unsigned char)_RESERVATION:
			(void)strcpy(glob_dlt_res, buffer);
			comm.datalen = 0;
			comm.buffer[0] = NULL;
			break;
		default:
			UtilMsg((int)MPE_PROTOCOL, MSGTYP_ERROR, NULL);
			status = (int)MPERROR;
			comm.datalen = 0;
			comm.buffer[0] = NULL;
			break;
		}
	return(status);
}
