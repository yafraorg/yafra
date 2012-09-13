/*D***********************************************************
 * Modul:     DBI - database action
 *            DLN Dienstleistungsnehmer
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNinput.c,v 1.4 2009-01-02 16:51:34 mwn Exp $";

int DLNinput(int len , char *buffer)
{
	extern PERSONEN pers;
	extern PERSADR adr;
	extern REISENDER rei;
	extern BCH_DLN bd;                /* it's needed for DELETE */
	extern REISENDER_TYP reit;
	extern SPRACHEN spr;
	extern STATUS_WERTE sta;
	extern LAND land;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int i;

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		pers.pers_id = (int)_UNDEF;
		pers.sta_id = (int)_UNDEF;

		rei.pers_id = (int)_UNDEF;
		rei.rkr_id = (int)_UNDEF;
		adr.land_id = (int)_UNDEF;
		*rei.vor = NULL;
		*rei.passnr = NULL;
		*rei.age = NULL;
		*rei.attr1 = NULL;
		*rei.attr2 = NULL;

		adr.pers_id = (int)_UNDEF;
		*adr.ans = NULL;
		*adr.adr1 = NULL;
		*adr.adr2 = NULL;
		*adr.adr3 = NULL;
		*adr.plz = NULL;
		*adr.kant = NULL;
		*adr.ort = NULL;
		*adr.tel = NULL;
		*adr.handy = NULL;
		*adr.tlx = NULL;
		*adr.fax = NULL;
		*adr.email = NULL;
		*adr.web = NULL;
		adr.sta_id = (int)_UNDEF;
		adr.mail_flag = _UNDEF;
		adr.rch_flag = _UNDEF;
		adr.haupt_flag = _UNDEF;
		}

	/* read menu string */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		rei.pers_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* set PERSONEN to reisender/privat typ */
	pers.pers_typ = (int)_PERS_PRIVAT;

	/* init */
	pers.sta_id = (int)_UNDEF;
	bd.bid = (int)_UNDEF; /* setting undef means del all BCH/RES of DLN */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		pers.pers_id = (int)_UNDEF;
		pers.s_id    = sprache;
		rei.pers_id  = (int)_UNDEF;
		pers.textid  = (int)_UNDEF;
		rei.mutters_id  = (int)_UNDEF;
		}

	/* PERSONEN name */
	if (*to_buffers[MDLN_NAM] != NULL)
		(void)copyTextTo((char *)pers.name, to_buffers[MDLN_NAM], (int)_CHAR512);
	else
		{
		UtilMsg((int)MPE_NONAM, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		rei.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* REISENDER vorname */
	if (*to_buffers[MDLN_VOR] != NULL)
		(void)copyTextTo((char *)rei.vor, to_buffers[MDLN_VOR], (int)_CHAR512);
	else
		{
		UtilMsg((int)MPE_NOVOR, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		rei.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* PERSONEN ort */
	(void)copyTextTo((char *)adr.ort, to_buffers[MDLN_ORT], (int)_CHAR256);

/******** old stuff - FESTIVAL don't have this as a MUST field !!!
	if (*to_buffers[MDLN_ORT] != NULL)
	else
		{
		UtilMsg((int)MPE_NOPERSORT, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		rei.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
*************/


	/* REISENDER_TYP */
	if (*to_buffers[MDLN_DLNT] != NULL)
		rei.rkr_id = MPAPIselectEntry((int)_REISENDER_TYP, to_buffers[MDLN_DLNT],
		               (char *)&reit, sizeof(REISENDER_TYP), sizeof(rei.rkr_id));
	else
		rei.rkr_id = (int)_UNDEF;
	if (rei.rkr_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLNT, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		rei.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* STATUS_WERTE geschlecht */
	if (*to_buffers[MDLN_SEX] != NULL)
		{
		sta.typ = (int)_SEX;
		(void)getAttribut( (int)_SEX, to_buffers[MDLN_SEX]);
		rei.sex = sta.sta_id;
		}
	else
		rei.sex = (int)_UNDEF;
	if (rei.sex == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOSEX, MSGTYP_ERROR, NULL);
		rei.pers_id = (int)_UNDEF;
		status = (int)MPERROR;
		}

	/* PERSONEN sprache */
	if (*to_buffers[MDLN_SPR] != NULL)
		{
		pers.s_id = MPAPIselectEntry((int)_SPRACHEN, to_buffers[MDLN_SPR],
		            (char *)&spr, sizeof(SPRACHEN), sizeof(pers.s_id));
		if (pers.s_id == (int)_UNDEF)
			pers.s_id = sprache;
		}
	else
		pers.s_id = sprache;

	/* LAND */
	if (*to_buffers[MDLN_LAND] != NULL)
		{
		adr.land_id = (int)MPAPIselectEntry((int)_LAND, to_buffers[MDLN_LAND],
			   (char *)&land, sizeof(LAND), sizeof(adr.land_id));
		}
	else
		adr.land_id = (int)_UNDEF;

	/* some other DLN/REISENDER stuff */
	(void)copyTextTo(rei.age, to_buffers[MDLN_ALTER], (int)_CHAR256);
	(void)copyTextTo(rei.passnr, to_buffers[MDLN_PASS], (int)_CHAR256);
	(void)copyTextTo(rei.attr1, to_buffers[MDLN_ATTR1], (int)_CHAR2000);
	(void)copyTextTo(rei.attr2, to_buffers[MDLN_ATTR2], (int)_CHAR2000);

	txt.typ = (int)_PERSONEN;
	txt.s_id = (int)sprache;
	txt.textid = pers.textid;
	pers.textid = xTxtWrite(to_buffers[MDLN_INTTXT]);

	txt.typ = (int)_REISENDER;
	txt.s_id = (int)sprache;
	txt.textid = rei.mutters_id;
	rei.mutters_id = xTxtWrite(to_buffers[MDLN_EXTTXT]);

	/* write PERSONEN entry first, because of new pers_id */
	/* but in DELETE case, this job is done by DLNdelete() */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		status = WriteEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			{
			WriteInfo((int)_PERSONEN, (char *)&pers, buffer);
			rei.pers_id = pers.pers_id;
			adr.pers_id = pers.pers_id;
			}
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			status = (int)MPERROR;
			}
		}

	/* write PERSADR entry after PERSONEN (exept in DELETE case) */
	if (status == (int)MPOK)
		{
		status = WriteEntry((int)_PERSADR, (char *)&adr, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			WriteInfo((int)_PERSADR, (char *)&adr, buffer);
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			adr.pers_id  = (int)_UNDEF;
			return((int)MPERROR);
			}
		}

	/* write REISENDER entry after PERSONEN (exept in DELETE case) */
	if (status == (int)MPOK)
		{
		status = WriteEntry((int)_REISENDER, (char *)&rei, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			WriteInfo((int)_REISENDER, (char *)&rei, buffer);
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			rei.pers_id  = (int)_UNDEF;
			status = (int)MPERROR;
			}
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
