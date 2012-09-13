/*D***********************************************************
 * Modul:     DBI - booking modul
 *            insert/update/delete reservation
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMRESinput.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int BMRESinput(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern unsigned char bm_obj;
	extern unsigned int  bm_dlncnt;
	extern unsigned char bm_dlnatonce;
	extern unsigned char bm_state;

	extern char glob_dl_bch[];

	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern REISENDER rei;
	extern RESERVATION res;
	extern DIENSTLEISTUNG dtg;

	BCH_DLN *dln = NULL;
	char message[_RECORDLEN];
	char query[_QUERYLEN];
	int status = (int)MPOK;
	int id;
	int i, j;
	int dlncnt;
	int *tdlids;
	int tdlcnt;
	unsigned long dlen, alen;

	/* check if BCH is still active */
	if (bch.bid == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOBCHACTIV, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	bm_state = (unsigned char)_BM_RES;

	/* init RES structur */
	res.bid      = bd.bid;
	res.pers_id  = bd.dln_id;
	res.dlg_id   = dtg.dlg_id;
	res.k_kon    = (int)_UNDEF;
	res.b_kon    = (int)_UNDEF;
	res.textid   = (int)_UNDEF;

	/* vererbe Saison von Dienstleistung */
	if (bch.sai_id > 0)
		res.sai_id = bch.sai_id;
	else if (dtg.sai_id > 0)
		res.sai_id = dtg.sai_id;
	else
		res.sai_id = (int)_UNDEF;

	/* read menu string and set it to RES */
	tdlids = NULL;
	tdlcnt = 0;
	status = BMRESreadprotocol(buffer, &res, &tdlids, &tdlcnt);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return(status);
		}

	/* set number of DLN to book in something */
	/* this is very important for loop over RESwrite and AKTDwrite */
	if (res.pers_id == (int)_UNDEF)
		(void)sprintf(query, _SEL_DLN_BCH, res.bid);
	else
		(void)sprintf(query, _SEL_ONEDLN, res.bid, res.pers_id); /* for security */
	dlen = alen = 0;
	status = MPAPIdb_sqlquery((int)_BCH_DLN, (char **)&dln, query,
	                         &dlncnt, &dlen, &alen);
	if (status != (int)MPOK || dlncnt < 1)
		{
		UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	bm_dlncnt = dlncnt;

	/*
	this is the main part of a booking !!
	here you write the AKTIONEN-DETAIL and the real RESERVATION

	loop over one (if res.pers_id == _UNDEF) or all in BCH
	!) input mode
      * falls mehr als ein rei buchung auf alle rei die erfasst wurden
      * sonst nur der aktive rei seine reservation
   !) update/delete mode
      * check if a DLN is activ or not
      * falls aktiv nur seine dl updaten/deleten
      * falls nicht, dl aller rei updaten/deleten 
	*/
	for (i=0; i<dlncnt; i++)
		{
		status = RESwrite(res.bid, dln[i].dln_id, res.dlg_id, tdlcnt, tdlids, &res);
		if (status == (int)MPOK)
			status = AKTDwrite(res.bid, dln[i].dln_id, res.dlg_id, &res);
		if (status != (int)MPOK)
			break;
		}
	MPfree((void *)dln);
	MPfree((void *)tdlids);   /* free up the SQL memeory */
	if (status != (int)MPOK)
		return((int)MPERROR);

	(void)MPAPIdb_committrx();
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		return(MPERROR);
		}

	/* update sta of BUCHUNG */
	status = MPAPIupdate_booksta(bch.bid);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* set state to written (that's only for debug reasons) */
	bm_state = (unsigned char)_BM_RESWRITTEN;

	/* start needed actions for this booking */
	status = AKTexec(&bch, res.dlg_id);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_NOAKTSTART, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	/* check up if we need more dl-booking */
	if (status == MPOK)
		{
		if (*glob_dl_bch == NULL)
			{
			UtilMsgGet((int)MPI_MOREDLBOOKING, MSGTYP_INFO, message);
			status = UtilImmediatCall(message);
			}
		else
			status = FALSE;
		if (status == (int)TRUE)
			{
			dtg.dlg_id = (int)_UNDEF;  /* reset DL to get new DL select */
			status = BMobjChoose(len, buffer);
			}
		else
			{
			/* check up if we need more dln-input */
			if (bm_dlnatonce == (int)FALSE)
				{
				UtilMsgGet((int)MPI_MOREDLN, MSGTYP_INFO, message);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = BMDLNsend(len, buffer);
				else
					{
					UtilMsgGet((int)MPI_BOOKEND, MSGTYP_INFO, buffer);
					COMMSTAT = MESSAGEOK;
					COMMTYP = (unsigned char)BMEND;
					ACTIONTYP = (unsigned char)INFOTXT;
					}
				}
			else
				{
				UtilMsgGet((int)MPI_BOOKEND, MSGTYP_INFO, buffer);
				COMMSTAT = MESSAGEOK;
				COMMTYP = (unsigned char)BMEND;
				ACTIONTYP = (unsigned char)INFOTXT;
				}
			}
		}

	return(status);
}

