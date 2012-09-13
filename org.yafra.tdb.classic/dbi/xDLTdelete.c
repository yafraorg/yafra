/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungstr�ger
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

/* local prototypes */
static int DLTdeleteOneEntry(DIENST_TRAEGER);

int DLTdelete(void)
{
	extern MEMOBJ sqlmem;
	extern DIENST_TRAEGER dlt;
	DIENST_TRAEGER hostdlt;
	DIENST_TRAEGER *dlts;
	char message[_RECORDLEN];
	char query[_QUERYLEN];
	int anzahl;
	int status=(int)MPOK;
	int i;

	if (dlt.dlt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLT noch im DLA vorhanden ? */
	if (MPAPIid_count((int)_DIENST_TRAEGER, (int)_DIENST_ANGEBOT, (char *)&dlt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTDEL_DLA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLT noch in RES vorhanden ? */
	if (MPAPIid_count((int)_DIENST_TRAEGER, (int)_RESERVATION, (char *)&dlt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTDEL_RES, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLT noch in GRA/REG vorhanden ? */
	if (MPAPIid_count((int)_DIENST_TRAEGER, (int)_GRAPHIK, (char *)&dlt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLTDEL_GRA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLT noch in PCX vorhanden ? */
	/*!!! muss noch codiert werden mit MSG5 */

	/* Hat es noch unterhalb etwas vorhanden (H_DLT_ID) ? */
	if (MPAPIid_count((int)_DIENST_TRAEGER, (int)_DIENST_TRAEGER, (char *)&dlt) != (int)EMPTY)
		{
		UtilMsgGet((int)MPW_NODLTDEL_DLT, MSGTYP_WARNING, message);
		status = UtilImmediatCall(message);
		if (status == (int)TRUE)
			{
			sprintf(query, _SEL_DLT_ALLFROMHOST, dlt.host_id);
			status = MPAPIdb_sqlquery((int)_DIENST_TRAEGER, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
			if (status != MPOK)
				{
				UtilMsg((int)status, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			if (anzahl < 2)
				return((int)MPOK);
			dlts = (DIENST_TRAEGER *)sqlmem.buffer;
			(void)MPAPIdb_committrx();
			for (i = (anzahl - 1); i > -1 && status == MPOK; i--)
				{
				status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_ERROR, NULL);
					return(MPERROR);
					}
				status = DLTdeleteOneEntry(dlts[i]);
				(void)MPAPIdb_committrx();
				}
			status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
			if (status != MPOK)
				{
				UtilMsg((int)status, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		else
			status = MPOK;
		}
	else /* l�sche den einzelnen Eintrag */
		status = DLTdeleteOneEntry(dlt);

	return(status);
}


/*************************************************************
 * Function:  DLTdeleteOneEntry
 * Typ:       private for DLTdelete
 * Desc:      delete one DLT with TXT and BEZ
 *************************************************************/
static int DLTdeleteOneEntry(DIENST_TRAEGER localdlt)
{
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	int status = MPOK;
	int count = 0;

	/* L�sche nun DLT */
	status=MPAPIdeleteEntry((int)_DIENST_TRAEGER, (char *)&localdlt);
	if (status == (int)MPOK)
		{
		/* L�sche Bezeichnung und Texte */
		bez.bez_id=localdlt.bez_id;
		count = MPAPIid_count((int)_BEZEICHNUNG, (int)_DIENST_TRAEGER, (char *)&bez);
		if (count == EMPTY && localdlt.bez_id != _UNDEF)
			{
			bez.typ=(int)_DIENST_TRAEGER;
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (localdlt.textid != _UNDEF)
			{
			txt.typ=(int)_DIENST_TRAEGER;
			txt.textid=localdlt.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else /* konnte Objekt nicht l�schen */
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
