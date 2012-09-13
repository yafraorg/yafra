/*D***********************************************************
 * modul:     DBI - database delete
 *            Sprache
 *
 * (c):       yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlbez.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSPRdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

static int DelSprBez(SPRACHEN *);
static int DelSprOther(SPRACHEN *);

int SPRdelete(void)
{
	extern int sprache;
	extern SPRACHEN spr;
	extern BEZEICHNUNG bez;

	char *ptr;
	int status=(int)MPOK;
	int anzahl;

	/* check if id is present */
	if (spr.s_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (spr.s_id == (int)DEFAULTLANG)
		{
		UtilMsg((int)MPE_NODEFAULTSPRDEL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* check if no more DLN are defined with this SPR */
	if (MPAPIid_count((int)_SPRACHEN, (int)_PERSONEN, (char *)&spr) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOSPRDEL_DLN, MSGTYP_ERROR, NULL);
		UtilMsg((int)MPE_NOSPRDEL_KUN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* drop BEZ index and delete all entries with SPR */
	status=dropIndex("BEZEICHNUNG", (char **)&ptr, &anzahl);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSPRDEL_BEZ, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	status=DelSprBez(&spr);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSPRDEL_BEZ, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)createIndex("BEZEICHNUNG", (char **)&ptr, &anzahl);

	/* drop TXT index and delete all entries with SPR in TXT/MSG/LABEL/HELP */
	status = dropIndex("TEXTE", (char **)&ptr, &anzahl);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSPRDEL_TXT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	status = DelSprOther(&spr);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSPRDEL_TXT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)createIndex("TEXTE", (char **)&ptr, &anzahl);

	/* delete SPR */
	status = MPAPIdeleteEntry((int)_SPRACHEN, (char *)&spr);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_SPRACHEN;
		bez.bez_id=spr.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_SPRACHEN, (char *)&bez) != (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
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

static int DelSprBez(SPRACHEN *spr )
{
	char command[_QUERYLEN];
	int status = (int)MPOK;
	int count;

	(void)sprintf(command, _DELETE_SPR_BEZ, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status=(int)MPERROR;
		}
	return(status);
}

static int DelSprOther(SPRACHEN *spr )
{
	char command[_QUERYLEN];
	int status = (int)MPOK;
	int count;

	(void)sprintf(command, _DELETE_SPR_TXT, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(command, _DELETE_SPR_AKTTXT, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(command, _DELETE_SPR_HELP, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(command, _DELETE_SPR_MSG, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(command, _DELETE_SPR_LABEL, spr->s_id);
	status=MPAPIdb_sqlcommand(command, &count);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	return(status);
}
