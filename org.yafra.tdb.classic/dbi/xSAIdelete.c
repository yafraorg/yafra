/*D***********************************************************
 * Modul:     DBI - database delete
 *            Saison
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSAIdelete.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define MSG1	(int)145
#define MSG2	(int)146
#define MSG3	(int)147
#define MSG4	(int)148
#define MSG5	(int)149
#define MSG6	(int)150
#define MSG7	(int)151
#define MSG8	(int)152
#define MSG9	(int)265
#define MSG10	(int)266

int SAIdelete(void)
{
	extern SAISON sai;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if (sai.sai_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_PROGRAMM, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_PREIS, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_REISENDER, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_ARRANGEMENT, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG4, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_DLG_PART, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG5, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_BUCHUNG, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG6, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_RESERVATION, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG7, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_KONTINGENT, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG8, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_DIENSTLEISTUNG, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG9, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_SAISON, (int)_AKT_DETAIL, (char *)&sai) != (int)EMPTY)
		{
		UtilMsg((int)MSG10, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdeleteEntry((int)_SAISON, (char *)&sai);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_SAISON;
		bez.bez_id=sai.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_SAISON, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry( (int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
