/*D***********************************************************
 * Modul:     DBI - booking modul
 *            read the commit buffer
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMRESread.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

static int setTDLid(char *, int **, int *);

int BMRESreadprotocol(char *buffer, RESERVATION *resptr, int **tdlids, int *tdlcnt)
{
	extern int sprache;
	extern REISENDER rei;
	extern DIENSTLEISTUNG dtg;
	extern DIENST_TRAEGER dlt;
	extern TRAEGER_TYP dltt;
	extern STATUS_WERTE sta;
	extern KONTINGENT kon;
	extern KONT_DETAIL k_d;
	extern TEXTE txt;

	MEMOBJ bez;
	struct tm DateTime;
	char bezeichnung[_RECORDLEN];
	char *ptr;
	int section;
	int i;
	int status;
	int len;
	int anzfields;

	/* init */
	bez.buffer = bezeichnung;
	bez.alloclen = _RECORDLEN;
	ptr = buffer;
	resptr->kont_id = (int)_UNDEF;
	txt.typ  = (int)_RESERVATION;
	txt.s_id = sprache;

	/* get number of fields */
	anzfields = MPgetSection(ptr, &len, (char)_MPSYMB_CR);
	if (anzfields != 13)
		{
		resptr->bid=(int)_UNDEF;
		resptr->pers_id=(int)_UNDEF;
		resptr->dlg_id=(int)_UNDEF;
		return((int)MPERROR);
		}
	ptr = ptr + (len+_MPSYMBLEN);

	/* -1- DIENSTLEISTUNG  typ ARR or DL */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	/* I think this is good enough else read sting and make a MPAPIselectEntry */
	resptr->dlg_id = dtg.dlg_id;

	/* -2- BUCHUNG ID */
	resptr->bid = MPgetSection(ptr, &len, (char)_MPSYMB_TAB);
	ptr = ptr + (len+_MPSYMBLEN);

	/* -3- BUCHUNG ref  !!! not neeeded just for information !!! */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);

	/* -4- KATEGORIE  int. ID */
	resptr->kat_id = MPgetSection(ptr, &len, (char)_MPSYMB_TAB);
	ptr = ptr + (len+_MPSYMBLEN);

	/* -5- REISENDER */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	resptr->pers_id = MPAPIselectEntry((int)_REISENDER, bezeichnung, (char *)&rei,
	             sizeof(REISENDER), sizeof(rei.pers_id));

	/* -6- STATUS_WERTE res sta */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung)
		{
		sta.typ = (int)_R_STA;
		status  = getAttribut((int)_R_STA, bezeichnung);
		if (status != (int)MPOK)
			{
			UtilMsg(MPE_NOSTA, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		resptr->r_sta = sta.sta_id;
		}
	else
		{
		UtilMsg(MPE_NOSTA, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* -7- DIENST_TRAEGER */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung)
		{
		if ((strstr(bezeichnung, TRENNER)) == NULL)
			dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
		else
			dlt.stufe = 0;
		resptr->dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, bezeichnung, (char *)&dlt,
	             	sizeof(DIENST_TRAEGER), sizeof(dlt.dlt_id));
		}
	else
		{
		/* it is a booking only with a category */
		resptr->dlt_id = (int)_UNDEF;
		}

	/* -8- TRAEGER_TYP */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung)
		{
		resptr->typ_id = MPAPIselectEntry((int)_TRAEGER_TYP, bezeichnung,
		        (char *)&dltt, sizeof(TRAEGER_TYP), sizeof(dltt.typ_id));
		}
	else
		resptr->typ_id = (int)_UNDEF;

	/* -9- DLG_PARTS Teildienstleistung */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != NULL)
		{
		status = setTDLid(bezeichnung, tdlids, tdlcnt);
		if (status == (int)MPERROR)
			resptr->dl_id = (int)_UNDEF;
		}
	else
		resptr->dl_id = (int)_UNDEF;

	/* -10- _DATUM   dl begin date/time */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != NULL)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&resptr->a_zeit, bezeichnung);
		}
	else
		resptr->a_zeit = (int)_UNDEF;

	/* -11- _DATUM  dl end date/time */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != NULL)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		(void)ReadDate(&DateTime, (time_t *)&resptr->e_zeit, bezeichnung);
		}
	else
		resptr->e_zeit = (int)_UNDEF;

	/* -12- _KONTINGENT  */
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != NULL)
		{
		resptr->kont_id=MPAPIselectEntry((int)_KONTINGENT, bezeichnung, (char *)&kon,
		   sizeof(KONTINGENT), sizeof(resptr->kont_id));
		k_d.kont_id = kon.kont_id;
		}
	else
		{
		resptr->kont_id = (int)_UNDEF;
		k_d.kont_id = (int)_UNDEF;
		}

	/* -13- TEXTE */
	resptr->textid = (int)_UNDEF;
	txt.textid = resptr->textid;
	status = MPgetTextsegment(ptr, &bez, (char)_MPSYMB_TAB);
	if (status != (int)MPOK)
		return(status);
	ptr = ptr + (bez.datalen + _MPSYMBLEN);
	if (*bezeichnung != NULL)
		resptr->textid = xTxtWrite(bezeichnung);

	return((int)MPOK);
}


static int setTDLid(char *bezeichnung, int **tdlids, int *tdlcnt)
{
	char **splitbuffer;
	int anzsplit;
	int splitflag;
	int i, id;
	int status = (int)MPOK;
	unsigned long alloclen = 0;
	DLG_PART tdl;

	/* security check */
	if (*bezeichnung == NULL)
		{
		*tdlcnt = 0;
		return((int)MPOK);
		}

	/* split the buffer */
	splitflag = NOPARTS;
	splitbuffer = (char **)UtilSplitBuffer(bezeichnung, &anzsplit, (char)_MPSYMB_CR);
	if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
		{
		UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	else if (anzsplit == (int)0)
		{
		splitflag = SINGLESEL;
		*tdlcnt = (int)1;

		/* get the ID */
		*tdlids = (int *)MPalloc((void *)*tdlids, &alloclen, 1, (int)1, sizeof(int));
		id = MPAPIselectEntry((int)_DLG_PART, bezeichnung, (char *)&tdl,
		   sizeof(DLG_PART), sizeof(tdl.dl_id));
		if (id != (int)_UNDEF)
			tdlids[0][0] = id;

		}
	else
		{
		splitflag = MULTISEL;
		*tdlcnt = anzsplit;
		*tdlids = (int *)MPalloc((void *)*tdlids, &alloclen, 1, anzsplit, sizeof(int));
		for (i=0; i<anzsplit && status == (int)MPOK; i++)
			{
			id = MPAPIselectEntry((int)_DLG_PART, splitbuffer[i], (char *)&tdl,
			   sizeof(DLG_PART), sizeof(tdl.dl_id));
			if (id != (int)_UNDEF)
				tdlids[0][i] = id;
			else
				{
				status = (int)MPERROR;
				}
			}
		}

	/* free up twin select split buffer */
	if (splitflag == MULTISEL)
		MPfreearray(splitbuffer, anzsplit);

	return(status);
}
