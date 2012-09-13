/*D***********************************************************
 * Modul:     DBI - database action
 *            Kommission
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int KOMinput(int len, char *buffer)
{
	extern KOMMISSION kom;
	extern BEZEICHNUNG bez;
	extern KUNDEN kun;
	extern KOSTEN_ART kar;
	extern TRAEGER_TYP dltt;
	extern KATEGORIE kat;
	extern REISENDER_TYP reit;
	extern DIENST_ANGEBOT dla;
	extern DIENSTLEISTUNG dtg;
	extern KONTINGENT kon;
	extern BUCHUNG bch;
	extern STATUS_WERTE sta;
	extern TEXTE txt;
	extern int sprache;

	BEZEICHNUNG tmpbez;
	struct tm DateTime;
	char tmpbuf[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	char **splitbuffer;
	int status = (int)MPOK;
	int summe;
	int count = (int)0;
	int anzsplit;
	int splitflag;
	int i;
	int id;

	/* Menueintraege holen */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~');
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kom.komm_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* Init */
	splitflag = NOPARTS;
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		kom.komm_id=(int)_UNDEF;
		kom.dla_id=(int)_UNDEF;
		kom.dl_id=(int)_UNDEF;
		kom.bid=(int)_UNDEF;
		kom.dltt_id = (int)_UNDEF;
		}

	/* Kommissionsbezeichnung - zwingend */
	if (*to_buffers[MKOM_BEZ] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		kom.komm_id = (int)_UNDEF;
		return((int)MPERROR);
		}
	bez.s_id=(int)sprache;
	bez.typ=(int)_KOMMISSION;
	(void)copyTextTo(bez.bez, to_buffers[MKOM_BEZ], (int)_BEZLEN);
	id = MPAPIselectEntry((int)_KOMMISSION, to_buffers[MKOM_BEZ],
            (char *)&kom, sizeof(KOMMISSION),sizeof(kom.komm_id));
	if (id == (int)_UNDEF && ACTIONTYP != (unsigned char)INSERT)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		kom.komm_id=(int)_UNDEF;
		return((int)MPERROR);
		}
	if (id != (int)_UNDEF && ACTIONTYP == (unsigned char)INSERT)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		return(MPOK);
		}


	/* STATUS_WERTE Kommissiontyp - zwingend */
	if (*to_buffers[MKOM_TYP] != NULL)
		{
		sta.typ = (int)_KOMMTYP;
		if (getAttribut((int)_KOMMTYP, to_buffers[MKOM_TYP]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		kom.komm_typ = sta.sta_id;
		}
	else
		{
		UtilMsg((int)MPE_NOKOMTYP, MSGTYP_ERROR, NULL);
		kom.komm_id=(int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* STATUS_WERTE Satztyp - zwingend */
	if (*to_buffers[MKOM_SATZTYP] != NULL)
		{
		sta.typ = (int)_SATZTYP;
		if (getAttribut((int)_SATZTYP, to_buffers[MKOM_SATZTYP]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		kom.satz_art = sta.sta_id;
		}
	else
		{
		UtilMsg((int)MPE_NOKOMTYP, MSGTYP_ERROR, NULL);
		kom.komm_id=(int)_UNDEF;
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* _UNDEF  SATZ get kommission */
	if (readDouble(&kom.satz, to_buffers[MKOM_SATZ]) == (int)MPERROR)
		kom.satz = (double)0.;

	/* KUNDEN Buchungsstelle Aussteller */
	if (*to_buffers[MKOM_KBST] != NULL )
		kom.kbst = MPAPIselectEntry((int)_KUNDEN, to_buffers[MKOM_KBST],
		   (char *)&kun, sizeof(KUNDEN), sizeof(kom.kbst));
	else
		kom.kbst = (int)_UNDEF;


	/* KOMMISSIONS objects */

	/* KOSTEN_ART */
	if (*to_buffers[MKOM_KAR] != NULL)
		{
		kom.kar_id = MPAPIselectEntry((int)_KOSTEN_ART, to_buffers[MKOM_KAR],
		             (char *)&kar, sizeof(KOSTEN_ART), sizeof(kom.kar_id));
		}
	else
		kom.kar_id = (int)_UNDEF;

	/* TRAEGER_TYP */
	if (*to_buffers[MKOM_DLTT] != NULL)
		{
		kom.dltt_id = MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MKOM_DLTT],
		   (char *)&dltt, sizeof(TRAEGER_TYP), sizeof(kom.dltt_id));
		}
	else
		kom.dltt_id = (int)_UNDEF;

	/* KATEGORIE */
	if (*to_buffers[MKOM_KAT] != NULL)
		{
		kom.kat_id = MPAPIselectEntry((int)_KATEGORIE, to_buffers[MKOM_KAT],
		   (char *)&kat, sizeof(KATEGORIE), sizeof(kom.kat_id));
		}
	else
		kom.kat_id = (int)_UNDEF;

	/* REISENDER_TYP */
	if (*to_buffers[MKOM_DLNT] != NULL)
		{
		kom.rkr_id = MPAPIselectEntry((int)_REISENDER_TYP, to_buffers[MKOM_DLNT],
		   (char *)&reit, sizeof(REISENDER_TYP), sizeof(kom.rkr_id));
		}
	else
		kom.rkr_id = (int)_UNDEF;


	/* Dienstleistung pr�fen */
	if (*to_buffers[MKOM_DL] != NULL)
		{
		splitbuffer = (char **)UtilSplitBuffer(to_buffers[MKOM_DL], &anzsplit, (char)'\n');
		if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
			{
			UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
			dtg.dlg_id = (int)_UNDEF;
			kom.komm_id = (int)_UNDEF;
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		else if (anzsplit == (int)0)
			splitflag = SINGLESEL;
		else
			splitflag = MULTISEL;
		count++;
		kom.dla_id=(int)_UNDEF;

		/* DL von / bis Daten */
		if (*to_buffers[MKOM_DLVON] != NULL)
			{
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			ReadDate(&DateTime,(time_t *)&kom.dl_vondat, to_buffers[MKOM_DLVON]);
			}
		else
			kom.dl_vondat = (int)_UNDEF;
		if (*to_buffers[MKOM_DLBIS] != NULL)
			{
			(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			ReadDate(&DateTime,(time_t *)&kom.dl_bisdat, to_buffers[MKOM_DLBIS]);
			}
		else
			kom.dl_bisdat = (int)_UNDEF;
		}
	else
		{
		kom.dl_id=(int)_UNDEF;
		kom.dl_vondat = (int)_UNDEF;
		kom.dl_bisdat = (int)_UNDEF;

		/* DIENST_ANGEBOT */
		if (*to_buffers[MKOM_DLA] != NULL)
			{
			id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MKOM_DLA],
				 (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(kom.dla_id));
			if (id == (int)_UNDEF)
				kom.dla_id = (int)_UNDEF;
			else
				kom.dla_id = dla.dla_id;
			}
		else
			kom.dla_id = (int)_UNDEF;
		}

	/* KONTINGENT */
	if (*to_buffers[MKOM_KON] != NULL)
		{
		if (MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKOM_KON], (char *)&kon,
				 sizeof(KONTINGENT), sizeof(kon.kont_id)) != (int)_UNDEF)
			kom.kont_id = kon.kont_id;
		else
			kom.kont_id = (int)_UNDEF;
		}
	else
		kom.kont_id = (int)_UNDEF;

	/* BUCHUNG */
	if (*to_buffers[MKOM_BCH] != NULL)
		{
		if (MPAPIselectEntry((int)_BUCHUNG, to_buffers[MKOM_BCH], (char *)&bch,
				 sizeof(BUCHUNG), (size_t)0) != (int)_UNDEF)
			kom.bid=bch.bid;
		else
			kom.bid=(int)_UNDEF;
		}
	else
		kom.bid=(int)_UNDEF;

	/* SAISON */
	kom.sai_id = (int)_UNDEF;

	/* HISTORY */
	kom.history = (int)_UNDEF;

	
	/* Es darf nur entweder DLA oder DL oder BCH definiert sein */
	if (kom.bid != (int)_UNDEF && (kom.dl_id != (int)_UNDEF ||
		 kom.dla_id != (int)_UNDEF))
		{
		status = (int)MPE_KOMDEF;
		}
	if (kom.dl_id != (int)_UNDEF && (kom.bid != (int)_UNDEF ||
		 kom.dla_id != (int)_UNDEF))
		{
		status = (int)MPE_KOMDEF;
		}
	if (kom.dla_id != (int)_UNDEF && (kom.dl_id != (int)_UNDEF ||
		 kom.bid != (int)_UNDEF))
		{
		status = (int)MPE_KOMDEF;
		}

	if (status != MPOK)
		{
		if (splitflag == MULTISEL)
			MPfreearray(splitbuffer, anzsplit);
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)status, MSGTYP_ERROR, NULL);
		kom.komm_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* TEXTE */
	txt.typ		= (int)_KOMMISSION;
	txt.s_id		= sprache;
	txt.textid	= kom.textid;
	kom.textid  = xTxtWrite(to_buffers[MKOM_TXT]);

	/* KOMMISSIONS Eintrag schreiben */
	if (splitflag == SINGLESEL || splitflag == NOPARTS)
		{
		kom.dl_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MKOM_DL],
			  (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
		status = WriteEntry((int)_KOMMISSION, (char *)&kom, &bez);
		}
	else
		{
		len = strlen(bez.bez);
		for (i=0; i<anzsplit && status == MPOK; i++)
			{
			kom.dl_id=MPAPIselectEntry((int)_DIENSTLEISTUNG, splitbuffer[i],
				  (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));

			/* append the first 5 chars of DLbez to the KOMbez for unique KOMbez */
			(void)sprintf(tmpbuf, " %5.5s", splitbuffer[i]);
			if (len > 22)
				(void)strcpy(&bez.bez[22], tmpbuf);
			else
				(void)strcpy(&bez.bez[len], tmpbuf);

			if (kom.dl_id != (int)_UNDEF)
				status=WriteEntry((int)_KOMMISSION, (char *)&kom, &bez);
			else
				status = (int)MPERROR;
			}
		}

	/* free up twin select split buffer */
	if (splitflag == MULTISEL)
		MPfreearray(splitbuffer, anzsplit);
	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
