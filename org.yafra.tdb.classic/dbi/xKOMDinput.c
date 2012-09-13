/*D***********************************************************
 * Modul:     DBI - database action
 *            KOMM_DETAIL
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMDinput.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int KOMDinput(int len, char *buffer)
{
	extern int sprache;
	extern KOMM_DETAIL komd;
	extern KOMMISSION kom;
	extern KUNDEN kun;
	extern BUCHUNG bch;
	extern PERSONEN pers;
	extern REISENDER rei;
	extern KOLLEKTIV kol;

	char message[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	/* Menueintraege holen */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~');
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Init */
	komd.komm_id = (int)_UNDEF;
	komd.bid     = (int)_UNDEF;
	komd.dln_id  = (int)_UNDEF;
	komd.kun_id  = (int)_UNDEF;
	komd.kol_id  = (int)_UNDEF;
	komd.prio    = (int)1;

	/* Kommissionsbezeichnung - zwingend */
	if (*to_buffers[MKOMD_KOM] != NULL)
		{
		komd.komm_id = MPAPIselectEntry((int)_KOMMISSION, to_buffers[MKOMD_KOM],
		       (char *)&kom,	sizeof(KOMMISSION), sizeof(komd.komm_id));
		}
	else
		komd.komm_id = (int)_UNDEF;
	if (komd.komm_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOKOMM, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* REISENDER Kommission */
	if (*to_buffers[MKOMD_DLN] != NULL)
		{
		if (kom.komm_typ == (int)_KOMM_DLN)
			{
			komd.dln_id = MPAPIselectEntry((int)_REISENDER, to_buffers[MKOMD_DLN],
			  (char *)&rei, sizeof(REISENDER), sizeof(komd.dln_id));

			/* BUCHUNG relation DLN to BCH */
			if (*to_buffers[MKOMD_BCH] != NULL)
				{
				if (MPAPIselectEntry((int)_BUCHUNG, to_buffers[MKOMD_BCH], (char *)&bch,
				    sizeof(BUCHUNG), (size_t)0) != (int)_UNDEF)
					komd.bid=bch.bid;
				}
			}
		}

	/* KUNDEN Kommission */
	if (*to_buffers[MKOMD_KUN] != NULL && komd.dln_id == (int)_UNDEF)
		{
		if (kom.komm_typ == (int)_KOMM_KUNDE)
			komd.kun_id = MPAPIselectEntry((int)_KUNDEN, to_buffers[MKOMD_KUN],
			  (char *)&kun, sizeof(KUNDEN), sizeof(komd.kun_id));
		}

	/* KOLLEKTIV Kommission */
	if (*to_buffers[MKOMD_KOL] != NULL && komd.dln_id == (int)_UNDEF &&
	    komd.kun_id == (int)_UNDEF)
		{
		if (kom.komm_typ == (int)_KOMM_KOLLEKTIV)
			komd.kol_id = MPAPIselectEntry((int)_KOLLEKTIV, to_buffers[MKOMD_KOL],
			   (char *)&kol, sizeof(KOLLEKTIV), sizeof(komd.kol_id));
		}

	/* UNDEF ordering */
	if (*to_buffers[MKOMD_ORD] == NULL)
		komd.prio = MPAPIid_max((int)_KOMM_DETAIL, (int)_ORD, (char *)&komd) + (int)1;
	else
		{
		status = readInteger(&komd.prio, to_buffers[MKOMD_ORD]);
		if (status == (int)MPERROR)
			komd.prio = MPAPIid_max((int)_KOMM_DETAIL, (int)_ORD,
			   (char *)&komd) + (int)1;
		else
			{
			if (komd.prio < (int)1)
				komd.prio = MPAPIid_max((int)_KOMM_DETAIL, (int)_ORD,
				   (char *)&komd) + (int)1;
			}
		}

	UtilSplitFreeMenubuffer(to_buffers);

	/* security check if the entry is OK or not */
	if ((komd.dln_id != (int)_UNDEF && komd.bid != (int)_UNDEF) ||
	    (komd.kun_id != (int)_UNDEF) || (komd.kol_id != (int)_UNDEF))
		{
		/* schreibe Kommissionseintrag auf DB */
		status=WriteEntry((int)_KOMM_DETAIL, (char *)&komd, (BEZEICHNUNG *)NULL);
		if (status == (int)MPERROR)
			komd.komm_id = (int)_UNDEF;
		else
			(void)WriteInfo((int)_KOMM_DETAIL, (char *)&komd, message);
		}
	else
		{
		UtilMsg((int)MPE_NOKOMM, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}

int KOMDinput_dln(int komm_id, int dln_id, int bch_id)
{
	extern KOMM_DETAIL komd;
	extern KOMMISSION kom;
	extern BUCHUNG bch;
	extern PERSONEN pers;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	/* Init */
	komd.komm_id = komm_id;
	komd.bid     = bch_id;
	komd.dln_id  = dln_id;
	komd.kun_id  = (int)_UNDEF;
	komd.kol_id  = (int)_UNDEF;
	komd.prio    = MPAPIid_max((int)_KOMM_DETAIL, (int)_ORD,
	                           (char *)&komd) + (int)1;

	/* schreibe Kommissionseintrag auf DB */
	status = MPAPIinsertEntry((int)_KOMM_DETAIL, (char *)&komd, (BEZEICHNUNG *)NULL);

	return(status);
}
