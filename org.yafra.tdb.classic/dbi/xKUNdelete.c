/*D***********************************************************
 * Modul:     DBI - database delete
 *            Kunden
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKUNdelete.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

#define MSG1	(int)163
#define MSG2	(int)164
#define MSG3	(int)261
#define MSG4	(int)262
#define MSG5	(int)263

int KUNdelete(void)
{
	extern PERSONEN pers;
	extern PERSADR adr;
	extern KUNDEN kun;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;
	
	if (kun.pers_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	adr.pers_id = pers.pers_id = kun.pers_id;

	if (MPAPIid_count((int)_KUNDEN, (int)_DLG_PART, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KUNDEN, (int)_BUCHUNG, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KUNDEN, (int)_KOLLEKTIV, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KUNDEN, (int)_KOMMISSION, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG4, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KUNDEN, (int)_KONTINGENT, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG5, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	if (MPAPIid_count((int)_KUNDEN, (int)_HOST_KONT, (char *)&kun) != (int)EMPTY)
		{
		UtilMsg((int)MSG5, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}


	status=MPAPIdeleteEntry((int)_KUNDEN, (char *)&kun);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	/* delete PERSADR entry */
	status = MPAPIdeleteEntry((int)_PERSADR, (char *)&adr);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		}

	status=MPAPIdeleteEntry((int)_PERSONEN, (char *)&pers);
	if (status == (int)MPOK)
		{
		if (pers.textid != (int)_UNDEF)
			{
			txt.typ=(int)_PERSONEN;
			txt.textid=pers.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
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
