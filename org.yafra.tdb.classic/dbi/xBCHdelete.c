/*D***********************************************************
 * Modul:     DBI - database delete
 *            delete an BCH object
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpsqldel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xBCHdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";
static int DeleteAllDLN(BUCHUNG *);

int BCHdelete(void)
{
	extern BUCHUNG bch;

	char command[RECLAENGE];
	int status=(int)MPOK;
	int anzahl;

	if (bch.bid == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* check Doppelbuchungs Eintraege */
	if (MPAPIid_count((int)_BUCHUNG, (int)_BUCHUNG, (char *)&bch) != (int)EMPTY)
		{
		UtilMsg((int)MPE_DBIDPTR, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* l�sche alle Kommissionen dieser Buchung/DLN */
	(void)sprintf(command, _DELETE_KOMD_BCH, bch.bid);
	status=MPAPIdb_sqlcommand(command, &anzahl);
	if (status != (int)MPOK)
		{
		UtilMsg((int)status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* l�sche alle Reservationen dieser Buchung */
	(void)sprintf(command, _DELETE_RES_BCH, bch.bid);
	status=MPAPIdb_sqlcommand(command, &anzahl);
	if (status != (int)MPOK)
		{
		UtilMsg((int)status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* l�sche alle Aktionsdetails dieser Buchung */
	(void)sprintf(command, _DELETE_AKTDET_BCH, bch.bid);
	status=MPAPIdb_sqlcommand(command, &anzahl);
	if (status != (int)MPOK)
		{
		UtilMsg((int)status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* l�sche alle DLN dieser Buchung */
	status = DeleteAllDLN(&bch);
	if (status != (int)MPOK)
		{
		UtilMsg((int)status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* l�sche Buchung */
	status = MPAPIdeleteEntry((int)_BUCHUNG, (char *)&bch);
	if (status == (int)MPERROR)
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	return(status);
}

static int DeleteAllDLN(BUCHUNG *buchung)
{
	int status = MPOK;
	int anzahl = 0;
	int count;
	int i;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	char query[RECLAENGE];
	BCH_DLN *Pbd = NULL;

	(void)sprintf(query, _SEL_BD_BCH, buchung->bid);
	status=MPAPIdb_sqlquery((int)_BCH_DLN, (char **)&Pbd, query, &anzahl,
		                      &dlen, &alen);
	if (status == MPOK && anzahl > 0)
		{
		/* l�sche alle DLN-Buchung verknuepfungen */
		(void)sprintf(query, _DELETE_BDBCH, buchung->bid);
		status=MPAPIdb_sqlcommand(query, &count);
		if (status != (int)MPOK)
			{
			MPfree((void *)Pbd);
			return((int)MPERROR);
			}

		/* loesche alle DLN/PERS/PERSADR Eintraege */
		for (i=0;i<anzahl;i++)
			{
			(void)sprintf(query, _DELETE_PERSADR, Pbd[i].dln_id);
			status=MPAPIdb_sqlcommand(query, &count);
			if (status != (int)MPOK)
				{
				MPfree((void *)Pbd);
				return(status);
				}
			(void)sprintf(query, _DELETE_DLN, Pbd[i].dln_id);
			status=MPAPIdb_sqlcommand(query, &count);
			if (status != (int)MPOK)
				{
				MPfree((void *)Pbd);
				return(status);
				}
			(void)sprintf(query, _DELETE_PERS, Pbd[i].dln_id);
			status=MPAPIdb_sqlcommand(query, &count);
			if (status != (int)MPOK)
				{
				MPfree((void *)Pbd);
				return(status);
				}
			}
		}
	else if (status != (int)MPOK)
		status = (int)MPERROR;

	MPfree((void *)Pbd);

	return(status);
}
