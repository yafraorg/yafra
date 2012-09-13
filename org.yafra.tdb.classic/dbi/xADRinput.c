/*D***********************************************************
 * modul:     DBI - database action
 *            ins/upd/del a PERSADR
 *
 *            there are two typs of persons:
 *            - a privat client (DLN/REISENDER)
 *            - a company (KUN)
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xADRinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int ADRinput(int len, char *buffer)
{
	extern int sprache;

	extern KUNDEN kun;
	extern DLN_VIEW dlnv;
	extern PERSADR adr;
	extern PERSONEN pers;
	extern STATUS_WERTE sta;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int id;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~' );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		adr.pers_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* init */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		adr.pers_id = (int)_UNDEF;
		adr.sta_id = (int)_UNDEF;
		}

	/* check if KUNDEN */
	if (MPAPIselectEntry((int)_KUNDEN, to_buffers[MADR_KUN], (char *)&kun,
		sizeof(KUNDEN), sizeof(kun.pers_id)) != (int)_UNDEF)
		{
		adr.pers_id = kun.pers_id;
		}
	else if (MPAPIselectEntry((int)_DLN_VIEW, to_buffers[MADR_DLN],
		(char *)&dlnv, sizeof(dlnv), sizeof(dlnv.dln_id)) != (int)_UNDEF)
		{
		adr.pers_id = dlnv.dln_id;
		}
	else
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* get correct PERSONEN entry */
	id = MPAPIselectOneId((int)_PERSONEN, adr.pers_id, (char *)&pers);

	/* ADRESSE Anschrift */
	if (*to_buffers[MADR_ANR] != NULL)
		(void)copyTextTo((char *)adr.ans, to_buffers[MADR_ANR], (int)_CHAR256);

	/* ADRESSE Zeile 1 */
	if (*to_buffers[MADR_ADR1] != NULL)
		(void)copyTextTo((char *)adr.adr1, to_buffers[MADR_ADR1], (int)_CHAR2000);

	/* ADRESSE Zeile 2 */
	if (*to_buffers[MADR_ADR2] != NULL)
		(void)copyTextTo((char *)adr.adr2, to_buffers[MADR_ADR2], (int)_CHAR2000);

	/* ADRESSE Zeile 3 */
	if (*to_buffers[MADR_ADR3] != NULL)
		(void)copyTextTo((char *)adr.adr3, to_buffers[MADR_ADR3], (int)_CHAR2000);

	/* ADRESSE Ort */
	if (*to_buffers[MADR_ORT] != NULL)
		(void)copyTextTo((char *)adr.ort, to_buffers[MADR_ORT], (int)_CHAR256);

	/* ADRESSE PLZ */
	if (*to_buffers[MADR_PLZ] != NULL)
		(void)copyTextTo((char *)adr.plz, to_buffers[MADR_PLZ], (int)_CHAR256);

	/* STATUS_WERTE Versandcode */
	if (*to_buffers[MADR_STA] != NULL)
		{
		sta.typ = (int)_ADRSTA;
		status = getAttribut((int)_ADRSTA, to_buffers[MADR_STA]);
		if (status == (int)MPOK)
			adr.sta_id = sta.sta_id;
		else
			adr.sta_id = (int)_UNDEF;
		}
	else
		adr.sta_id = (int)_UNDEF;

	UtilSplitFreeMenubuffer(to_buffers);

	/* write ADRESSE */
	status = WriteEntry((int)_PERSADR, (char *)&adr, (BEZEICHNUNG *)NULL);
	if (status == (int)MPOK)
		{
		WriteInfo((int)_PERSADR, (char *)&adr, buffer);
		status = MPAPIupdateEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
		}
	else
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		adr.pers_id  = (int)_UNDEF;
		status = (int)MPERROR;
		}

	return(status);
}

