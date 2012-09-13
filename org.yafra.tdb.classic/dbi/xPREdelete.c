/*D***********************************************************
 * Modul:     DBI - database delete
 *            PREIS
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPREdelete.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

static int PREdeleteAllFrom(char *);
static int PREdeleteOneEntry(PREIS *);

int PREdelete( void )
{
	extern PREIS pre;

	char query[_QUERYLEN];
	int status=(int)MPOK;

	if (pre.dla_id != (int)_UNDEF && pre.dl_id == (int)_UNDEF &&
		 pre.kont_id == (int)_UNDEF && pre.kar_id == (int)_UNDEF &&
		 pre.kat_id == (int)_UNDEF && pre.rkr_id == (int)_UNDEF)
		{
		sprintf(query, _SEL_PRE_DLA, pre.dla_id);
		status = PREdeleteAllFrom(query);
		}
	else if (pre.dl_id != (int)_UNDEF && pre.dla_id == (int)_UNDEF &&
		 pre.kont_id == (int)_UNDEF && pre.kar_id == (int)_UNDEF &&
		 pre.kat_id == (int)_UNDEF && pre.rkr_id == (int)_UNDEF)
		{
		sprintf(query, _SEL_PRE_DL, pre.dl_id);
		status = PREdeleteAllFrom(query);
		}
	else if (pre.kat_id != (int)_UNDEF && pre.dla_id == (int)_UNDEF &&
		 pre.kont_id == (int)_UNDEF && pre.kar_id == (int)_UNDEF &&
		 pre.dl_id == (int)_UNDEF && pre.rkr_id == (int)_UNDEF)
		{
		sprintf(query, _SEL_PRE_KAT, pre.kat_id);
		status = PREdeleteAllFrom(query);
		}
	else if (pre.kont_id != (int)_UNDEF && pre.dla_id == (int)_UNDEF &&
		 pre.kat_id == (int)_UNDEF && pre.kar_id == (int)_UNDEF &&
		 pre.dl_id == (int)_UNDEF && pre.rkr_id == (int)_UNDEF)
		{
		(void)sprintf(query, _SEL_PRE_KON, pre.kont_id);
		status = PREdeleteAllFrom(query);
		}
	else
		{
		status=MPAPIdeleteEntry((int)_PREIS, (char *)&pre);
		if (status == (int)MPERROR)
			{
			UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	
	return(status);
}


/*************************************************************
 * Function:  PREdeleteAllFrom
 * Typ:       private for PREdelete
 * Desc:      delete alle PRE from an object
 *************************************************************/
static int PREdeleteAllFrom(char *query)
{
	extern MEMOBJ sqlmem;
	PREIS *preptr;
	int anzahl = 0;
	int i;
	int status = MPOK;

	status = MPAPIdb_sqlquery((int)_PREIS, &sqlmem.buffer, query,
                        &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}
	if (anzahl > 0)
		{
		preptr = (PREIS *)sqlmem.buffer;
		for (i = (anzahl - 1); i > -1 && status == MPOK; i--)
			status=PREdeleteOneEntry(&preptr[i]);
		}

	return(status);
}


/*************************************************************
 * Function:  PREdeleteOneEntry
 * Typ:       private for PREdelete
 * Desc:      delete one PRE with TXT
 *************************************************************/
static int PREdeleteOneEntry(PREIS *localpre)
{
	extern TEXTE txt;
	int status = MPOK;

	/* L�sche nun DLT */
	status=MPAPIdeleteEntry((int)_PREIS, (char *)localpre);
	if (status == (int)MPOK)
		{
		if (localpre->textid != (int)_UNDEF)
			{
			txt.typ=(int)_PREIS;
			txt.textid=localpre->textid;
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
