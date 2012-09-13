/*D***********************************************************
 * Modul:     DBI - booking modul
 *            send choice of DLN's in BCH
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMDLNchoose.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int BMDLNchoose(int len, char *buffer)
{
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern DLN_VIEW dlnv;
	extern REISENDER rei;
	extern PERSONEN pers;

	int status = (int)MPOK;
	int id;

	switch (FELDNR)
		{
		case (unsigned char)MBMDLN_NAME:
			break;

		default:
			return(status);
			break;
		}		

	/* get selected DLN */
	id = MPAPIselectEntry((int)_DLN_VIEW, buffer, (char *)&dlnv, sizeof(dlnv),
	                 sizeof(dlnv.dln_id));
	if (id == (int)_UNDEF)
		{
		dlnv.dln_id = (int)_UNDEF;
		rei.pers_id = (int)_UNDEF;
		pers.pers_id = (int)_UNDEF;
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	/* oh I hate these diffrent names for the same object !!! but never mind */
	bd.dln_id = pers.pers_id = rei.pers_id = dlnv.dln_id;

	/* get PERSONEN & REISENDER */
	id = MPAPIselectOneId((int)_PERSONEN, (int)pers.pers_id, (char *)&pers);
	id = MPAPIselectOneId((int)_REISENDER, (int)rei.pers_id, (char *)&rei);

	/* create new BM-DLN mask */
	status = BMDLNsend(len, buffer);

	return(status);
}


int BMDLNchoosefirst(int bid)
{
	extern MEMOBJ sqlmem;
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern DLN_VIEW dlnv;
	extern REISENDER rei;
	extern PERSONEN pers;
	extern char sqlquery[];

	BCH_DLN *all_bd;
	int status = (int)MPOK;
	int id;
	int count;

	/* get first DLN of a BCH */
	(void)sprintf(sqlquery, _SEL_BD_BCH, bid);
	status=MPAPIdb_sqlquery((int)_BCH_DLN, &sqlmem.buffer, sqlquery, &count,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	all_bd = (BCH_DLN *)sqlmem.buffer;
	if ((status == (int)MPOK) && (count > (int)0))
		(void)memcpy((void *)&bd, (void *)&all_bd[0], sizeof(BCH_DLN));
	else
		return((int)MPERROR);

	pers.pers_id = rei.pers_id = dlnv.dln_id = bd.dln_id;

	/* get DLNV & PERSONEN & REISENDER for further usage in BMDLNsend() */
	id = MPAPIselectOneId((int)_DLN_VIEW, (int)dlnv.dln_id, (char *)&dlnv);
	if (id == (int)_UNDEF)
		{
		dlnv.dln_id = (int)_UNDEF;
		rei.pers_id = (int)_UNDEF;
		pers.pers_id = (int)_UNDEF;
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	id = MPAPIselectOneId((int)_PERSONEN, (int)pers.pers_id, (char *)&pers);
	id = MPAPIselectOneId((int)_REISENDER, (int)rei.pers_id, (char *)&rei);

	return((int)MPOK);
}
