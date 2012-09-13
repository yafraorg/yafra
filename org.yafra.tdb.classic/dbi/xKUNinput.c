/*D***********************************************************
 * Modul:     DBI - database action
 *            Kunden
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKUNinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int KUNinput(int len, char *buffer)
{
	extern int sprache;
	extern PERSONEN pers;
	extern PERSADR adr;
	extern KUNDEN kun;
	extern SPRACHEN spr;
	extern KUNDEN_TYP kunt;
	extern LAND land;
	extern WAEHRUNG whr;
	extern TEXTE txt;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		pers.pers_id = (int)_UNDEF;
		pers.sta_id = (int)_UNDEF;

		kun.pers_id = (int)_UNDEF;
		kun.leiter = (int)_UNDEF;
		*kun.handy = NULL;
		*kun.attr1 = NULL;
		*kun.attr2 = NULL;
		*kun.email = NULL;
		*kun.fax = NULL;
		*kun.konto = NULL;
		*kun.tel = NULL;
		*kun.web = NULL;

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
		adr.haupt_flag = (int)1;

		}

	/* read menu string */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kun.pers_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* set PERSONEN to firmen/kunden typ */
	pers.pers_typ = (int)_PERS_FIRMEN;

	/* init */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		pers.pers_id = (int)_UNDEF;
		pers.s_id    = sprache;
		kun.pers_id  = (int)_UNDEF;
		pers.textid  = (int)_UNDEF;
		}

	/* PERSONEN name */
	if (*to_buffers[MKUN_NAME] != NULL)
		(void)copyTextTo((char *)pers.name, to_buffers[MKUN_NAME], (int)_CHAR512);
	else
		{
		UtilMsg((int)MPE_NONAM, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* PERSONEN ort */
	if (*to_buffers[MKUN_ORT] != NULL)
		(void)copyTextTo((char *)adr.ort,to_buffers[MKUN_ORT],(int)_CHAR256);
	else
		{
		UtilMsg((int)MPE_NOPERSORT, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KUNDEN kundentyp */
	if (*to_buffers[MKUN_KUNT] != NULL)
		kun.k_typ_id = MPAPIselectEntry((int)_KUNDEN_TYP, to_buffers[MKUN_KUNT],
		               (char *)&kunt, sizeof(KUNDEN_TYP), sizeof(kun.k_typ_id));
	else
		kun.k_typ_id = (int)_UNDEF;
	if (kun.k_typ_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOKUNT, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KUNDEN land */
	if (*to_buffers[MKUN_LAND] != NULL)
		adr.land_id = MPAPIselectEntry((int)_LAND, to_buffers[MKUN_LAND],
		               (char *)&land, sizeof(LAND), sizeof(adr.land_id));
	else
		adr.land_id = (int)_UNDEF;
	if (adr.land_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOLAND, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KUNDEN waehrung */
	if (*to_buffers[MKUN_WHR] != NULL)
		kun.whr_id = MPAPIselectEntry((int)_WAEHRUNG, to_buffers[MKUN_WHR],
		               (char *)&whr, sizeof(WAEHRUNG), sizeof(kun.whr_id));
	else
		kun.whr_id = (int)_UNDEF;
	if (kun.whr_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOWHR, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* PERSONEN sprache */
	if (*to_buffers[MKUN_SPR] != NULL)
		{
		pers.s_id = MPAPIselectEntry((int)_SPRACHEN, to_buffers[MKUN_SPR],
		            (char *)&spr, sizeof(SPRACHEN), sizeof(pers.s_id));
		if (pers.s_id == (int)_UNDEF)
			pers.s_id = sprache;
		}
	else
		pers.s_id = sprache;

	/* KUNDEN diverses */
	(void)copyTextTo((char *)kun.tel,to_buffers[MKUN_TEL],_CHAR256);
	(void)copyTextTo((char *)kun.fax,to_buffers[MKUN_FAX],_CHAR256);
	(void)copyTextTo((char *)kun.tlx,to_buffers[MKUN_TLX],_CHAR256);
	(void)copyTextTo((char *)kun.konto,to_buffers[MKUN_KONTO],_CHAR256);
	(void)copyTextTo((char *)adr.kant,to_buffers[MKUN_KANT],_CHAR256);
	(void)copyTextTo((char *)kun.attr1,to_buffers[MKUN_ATTR1],_CHAR2000);
	(void)copyTextTo((char *)kun.attr2,to_buffers[MKUN_ATTR2],_CHAR2000);

	txt.typ = (int)_PERSONEN;
	txt.s_id = sprache;
	txt.textid = pers.textid;
	pers.textid = xTxtWrite(to_buffers[MKUN_TXT]);

	/* write PERSONEN entry first, because of new pers_id */
	/* but in DELETE case, this job is done by KUNdelete() */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		status = WriteEntry((int)_PERSONEN, (char *)&pers, (BEZEICHNUNG *)NULL);
		if (status == (int)MPOK)
			{
			WriteInfo((int)_PERSONEN, (char *)&pers, buffer);
			kun.pers_id = pers.pers_id;
			adr.pers_id = pers.pers_id;
			}
		else
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			pers.pers_id = (int)_UNDEF;
			kun.pers_id  = (int)_UNDEF;
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
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
				kun.pers_id  = (int)_UNDEF;
				adr.pers_id  = (int)_UNDEF;
				return((int)MPERROR);
				}
			}
		}

	/* write KUNDEN entry after PERSONEN (exept in DELETE case) */
	status = WriteEntry((int)_KUNDEN, (char *)&kun, (BEZEICHNUNG *)NULL);
	if (status == (int)MPOK)
		WriteInfo((int)_KUNDEN, (char *)&kun, buffer);
	else
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		pers.pers_id = (int)_UNDEF;
		kun.pers_id  = (int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
