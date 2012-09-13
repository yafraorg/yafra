/*D***********************************************************
 * modul:     DBI - database insert                           
 *            Sprachen
 *                                                            
 * (c):       yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlbez.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSPRinput.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

static int InsSprBez(SPRACHEN *);

int SPRinput(int len, char *buffer)
{
	extern SPRACHEN spr;
	extern BEZEICHNUNG bez;
	extern int sprache;

	char message[_RECORDLEN];
	char tmp_buffer[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	char **ptr;
	int status=(int)MPOK;
	int anzahl;
	int answer;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		spr.s_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	bez.s_id=(int)sprache;
	bez.typ=(int)_SPRACHEN;
	(void)copyTextTo(bez.bez, to_buffers[MSPR_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
      /* Dialog Flag */
		(void)copyTextTo(tmp_buffer, to_buffers[MSPR_DIALOG], (int)_FLAGLEN);
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
		if (strstr(message, tmp_buffer) != NULL)
			spr.dialog = (int)TRUE;
		else
			spr.dialog = (int)FALSE;

      /* Sprache Systembezeichnung */
		(void)copyTextTo(spr.sysbez, to_buffers[MSPR_SYSBEZ], (int)_CHAR20);

      /* Output Flag */
		(void)copyTextTo(tmp_buffer, to_buffers[MSPR_OUTPUT], (int)_FLAGLEN);
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
		if (strstr(message, tmp_buffer) != NULL)
			spr.output = (int)TRUE;
		else
			spr.output = (int)FALSE;

      /* TO 2000 GUI Flag */
		(void)copyTextTo(tmp_buffer, to_buffers[MSPR_GUI], (int)_FLAGLEN);
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
		if (strstr(message, tmp_buffer) != NULL)
			spr.gui = (int)TRUE;
		else
			spr.gui = (int)FALSE;

		/* Neuer Spracheintrag in Table SPRACHEN */
		status = WriteEntry((int)_SPRACHEN, (char *)&spr, &bez);
		if (status == (int)MPERROR)
			spr.s_id=(int)_UNDEF;

		/* at insert ask for copying an existing SPR to the new one */
		if (ACTIONTYP == (unsigned char)INSERT && status == (int)MPOK &&
		    spr.dialog == (int)TRUE)
			{
			UtilMsgGet((int)MPW_SPRCOPY, MSGTYP_WARNING, message);
			answer = UtilImmediatCall(message);
			if (answer == (int)TRUE)
				{
				/* copy BEZ */
				status=dropIndex("BEZEICHNUNG", (char **)&ptr, &anzahl);
				if (status != (int)MPOK)
					{
					UtilMsg((int)MPE_SPRBEZCOPY, MSGTYP_ERROR, NULL);
					UtilSplitFreeMenubuffer(to_buffers);
					return((int)MPERROR);
					}
				status=InsSprBez(&spr);
				if (status != (int)MPOK)
					{
					UtilMsg((int)MPE_SPRBEZCOPY, MSGTYP_ERROR, NULL);
					UtilSplitFreeMenubuffer(to_buffers);
					return((int)MPERROR);
					}
				(void)createIndex("BEZEICHNUNG", (char **)&ptr, &anzahl);
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NOUNIQUEBEZ, MSGTYP_ERROR, NULL);
		spr.s_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}

static int InsSprBez(SPRACHEN *spr )
{
	extern int sprache;
	extern char sqlquery[];

	int status=(int)MPOK;
	int count;

	/* Texte in TMP_BEZEICHNUNG einlesen */
	(void)sprintf(sqlquery, _INSERT_SPR_BEZ_OUT, spr->s_id, sprache);
	status=MPAPIdb_sqlcommand(sqlquery, &count);
	if (status == (int)MPOK)
		{
		/* Texte in BEZEICHNUNG uebertragen */
		(void)sprintf(sqlquery, _INSERT_SPR_BEZ_IN, spr->s_id);
		status=MPAPIdb_sqlcommand(sqlquery, &count);
		if (status == (int)MPOK)
			{
			/* Texte wieder aus TMP_BEZ loeschen */
			(void)sprintf(sqlquery, _DELETE_TMP_BEZ, spr->s_id);
			status=MPAPIdb_sqlcommand(sqlquery, &count);
			if (status != (int)MPOK)
				{
				UtilMsg(status, MSGTYP_DBERROR, NULL);
				status=(int)MPERROR;
				}
			}
		else
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
