/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungsangebot
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLAdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

static int DLAdeleteOneEntry(DIENST_ANGEBOT *);

int DLAdelete(void)
{
	extern MEMOBJ sqlmem;
	extern DIENST_ANGEBOT dla;

	DIENST_ANGEBOT *dlaptr;
	int status=(int)MPOK;
	int anzahl, i;
	char query[_QUERYLEN];

	if (dla.dla_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLA noch in PREIS vorhanden ? */
	if (MPAPIid_count((int)_DIENST_ANGEBOT, (int)_PREIS, (char *)&dla) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLADEL_PRE, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLA noch in KOMMISSION vorhanden ? */
	if (MPAPIid_count((int)_DIENST_ANGEBOT, (int)_KOMMISSION, (char *)&dla) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLADEL_KOM, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLA noch in KONTINGENT vorhanden ? */
	if (MPAPIid_count((int)_DIENST_ANGEBOT, (int)_KONTINGENT, (char *)&dla) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLADEL_KON, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLA noch in TDL vorhanden ? */
	if (MPAPIid_count((int)_DIENST_ANGEBOT, (int)_DLG_PART, (char *)&dla) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NODLADEL_TDL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist DLA noch in DLA vorhanden ? */
	if (MPAPIid_count((int)_DIENST_ANGEBOT, (int)_DIENST_ANGEBOT, (char *)&dla) != (int)EMPTY)
		{
		sprintf(query, _SEL_DLA_ALLFROMHOST, dla.dla_id);
		status = MPAPIdb_sqlquery((int)_DIENST_ANGEBOT, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != MPOK)
			{
			UtilMsg((int)MPE_NODLADEL_DLA, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		if (anzahl > 0)
			{
			dlaptr = (DIENST_ANGEBOT *)sqlmem.buffer;
			for (i = (anzahl - 1); i > -1 && status == MPOK; i--)
				status = DLAdeleteOneEntry(&dlaptr[i]);
			if (status != MPOK)
				{
				UtilMsg((int)MPE_NODLADEL_DLA, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		}

	status = DLAdeleteOneEntry(&dla);
	
	return(status);
}


/*************************************************************
 * Function:  DLAdeleteOneEntry
 * Typ:       private for DLGdelete
 * Desc:      delete one DLA with TXT and BEZ
 *************************************************************/
static int DLAdeleteOneEntry(DIENST_ANGEBOT *localdla)
{
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;
	int status = MPOK;

	/* L�sche nun DLT */
	status=MPAPIdeleteEntry((int)_DIENST_ANGEBOT, (char *)localdla);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_DIENST_ANGEBOT;
		bez.bez_id=localdla->bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG, (int)_DIENST_ANGEBOT,
		    (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (localdla->textid != _UNDEF)
			{
			txt.typ=(int)_DIENST_ANGEBOT;
			txt.textid=localdla->textid;
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
