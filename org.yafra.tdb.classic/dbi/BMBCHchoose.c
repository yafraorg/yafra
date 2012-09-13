/*D***********************************************************
 * Modul:     DBI - booking modul
 *            choose a book object
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMBCHchoose.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int BMBCHchoose(int table, char *buffer)
{
	extern int	sprache;
   extern MP_PROFIL prof;
	extern char glob_dlt_bch[];
	extern char glob_arr_bch[];
	extern char glob_dl_bch[];
	extern char glob_dat_bch[];
	extern char glob_dln_bch[];
	extern BUCHUNG			bch;
	extern BCH_DLN       bd;
	extern ARRANGEMENT	arr;
	extern STATUS_WERTE	sta;
	extern KOLLEKTIV		kol;
	extern REISENDER     rei;
	extern int dla_selected;
	extern unsigned char bm_obj;

	BUCHUNG					dbch;
	RESERVATION          aRes;
	DIENSTLEISTUNG			aDl;
	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[_RECORDLEN];
	char	message[RECLAENGE];
	int	id, len;
	int DlEntry;
	int bchselected = (int)FALSE;

	(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, (int)NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	glob_dln_bch[0] = (char)NULL;

	switch(FELDNR)
		{
		case MBME_BCHREF:
			break;
		case MBME_BCHNR:
			len = strlen(buffer);
			if (len > RECLAENGE)
				return(MPOK);
			(void)strcpy(buffer1, buffer);
			*buffer = (char)NULL;
			break;
		case MBME_ARR:
			(void)strcpy(glob_arr_bch, buffer);
			return(MPOK);
			break;
		case MBME_DL:
			(void)strcpy(glob_dl_bch, buffer);
			return(MPOK);
			break;
		case MBME_DAT:
			(void)strcpy(glob_dat_bch, buffer);
			return(MPOK);
			break;
		case MBME_DLT:
			(void)strcpy(glob_dlt_bch, buffer);
			return(MPOK);
			break;
		case MBME_DLA:
			dla_selected = (int)TRUE;
			return(MPOK);
			break;
		case MBME_DLN:
			id = MPAPIselectEntry((int)_REISENDER, buffer, (char *)&rei, sizeof(rei),
			                 sizeof(rei.pers_id));
			return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* select right BCH */
	if (bchselected != (int)TRUE)
		{
		if (*buffer != (char)NULL) /* hole nach BCHREF */
			{
			if (MPAPIselectEntry((int)_BUCHUNG, buffer, (char *)&bch, sizeof(bch),
			               (size_t)0) == (int)_UNDEF)
				bch.bid = (int)_UNDEF;
			}
		else                 /* hole nach BCHNR */
			{
			bch.bid = atoi(buffer1);
			if (bch.bid > (int)0)
				(void)MPAPIselectOneId((int)_BUCHUNG, (int)bch.bid, (char *)&bch);
			else
				bch.bid = (int)_UNDEF;
			}
		}
	if (bch.bid == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* set bid in relation BCH_DLN for further usage */
	bd.bid = bch.bid;

	/* BUCHUNG  eindeutige Buchungsreferenz */
	(void)copyTextTo(bezeichnung, (char *)bch.ref, (int)_CHAR30);
	(void)strcpy(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* BUCHUNG  eindeutige Buchungsnummer */
	(void)sprintf(bezeichnung, "%d", bch.bid);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Zustand der Buchung */
	sta.typ=(int)_BSTA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, bch.sta, (char *)&sta);
	if (id != (int)_UNDEF && SelectBez((int)_BSTA, sprache, sta.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DATUM   Buchungsdatum */
	(void)strcat(buffer, "\t");

	/* ARRANGEMENT */
	id = MPAPIselectOneId((int)_ARRANGEMENT, (int)bch.arr_id, (char *)&arr);
	if (id != (int)_UNDEF && SelectBez((int)_ARRANGEMENT, sprache, arr.bez_id, bezeichnung) != (int)_UNDEF)
		{
		bm_obj = (unsigned char)_ARRANGEMENT;
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, " => ");
		(void)WriteDate(&DateTime, (time_t *)&arr.a_dat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	else
		bm_obj = (unsigned char)_DIENSTLEISTUNG;
	(void)strcat(buffer, "\t");

	/* DIENSTLEISTUNG   (is not in DB / just for info) */
	aRes.teil=(int)_UNDEF;
	aRes.pers_id = (int)_UNDEF;
	aRes.dl_id = (int)_UNDEF;
	aRes.bid = bch.bid;
	id = MPAPIselectOneId((int)_RESERVATION, (int)bch.bid, (char *)&aRes);
	if ( id == (int)_UNDEF )
	{
		(void)strcat(buffer, "\t");
	}
	else
	{
		DlEntry = aRes.pers_id;   /*--- I know, but it' the only way ---*/
		id = MPAPIselectOneId((int)_DIENSTLEISTUNG, DlEntry, (char *)&aDl);
		if (id != (int)_UNDEF && SelectBez((int)_DIENSTLEISTUNG, sprache, aDl.bez_id, bezeichnung) != (int)_UNDEF)
		{
			(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
			DateTime.tm_min  = (int)_UNDEF;
			DateTime.tm_hour = (int)_UNDEF;
			DateTime.tm_mday = (int)_UNDEF;
			DateTime.tm_mon  = (int)_UNDEF;
			DateTime.tm_year = (int)_UNDEF;

			(void)strcat( bezeichnung, TRENNER );
			(void)WriteDate(&DateTime, (time_t *)&aDl.a_zeit, buffer1);
			(void)strcat( bezeichnung, buffer1 );

			(void)strcat(buffer, bezeichnung );
		}
		(void)strcat(buffer, "\t");
	}

	/* KUNDEN  Buchungsstelle */
   if (prof.mpid == bch.anw || prof.mpid == bch.sach)
      {
	   id = KUNmkbez(prof.bchst, buffer1, (int)_RECORDLEN);
	   if (id == (int)MPOK)
		   (void)strcat(buffer, buffer1);
      }
/*#4 get the correct profile for else case - if a stellvertreter is using this booking */
	(void)strcat(buffer, "\t");

	/* KUNDEN  Rechnungsempf�nger */
	id = KUNmkbez(bch.kid, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	(void)strcat(buffer, "\t");  /* DIENST_TRAEGER  (is not in DB / just for info)*/
	(void)strcat(buffer, "\t");  /* KATEGORIE  (is not in DB / just for info)*/

	/* KOLLEKTIV */
	id = MPAPIselectOneId((int)_KOLLEKTIV, bch.k_id, (char *)&kol);
	if (id != (int)_UNDEF)
      {
      (void)copyTextTo(bezeichnung, kol.name, (int)_CHAR512);
		(void)strcat(buffer, bezeichnung);
      }
	(void)strcat(buffer, "\t");

	/* BUCHUNG  Hauptbuchung bei Doppelbuchung */
	if (bch.d_bid != (int)_UNDEF)
		{
		dbch.bid = (int)_UNDEF;
		(void)MPAPIselectOneId((int)_BUCHUNG, (int)bch.d_bid, (char *)&dbch);
		if (dbch.bid != (int)_UNDEF)
			{
			(void)copyTextTo(bezeichnung, (char *)dbch.ref, (int)_CHAR30);
			(void)strcat(buffer, bezeichnung);
			}
		}
	(void)strcat(buffer, "\t");

	/* _UNDEF  Sachbearbeiter */
	(void)copyTextTo(bezeichnung, (char *)prof.mpuser, (int)_CHAR30);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* _UNDEF  Anfrageoption bis Datum */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&bch.opt_bst, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* _UNDEF  Kundenoption bis Datum */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&bch.opt_kid, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* _UNDEF    nextmenu Feld und f�hrt zum History Menu */
	(void)strcat(buffer, "\t");

	/* REISENDER  (is not in DB / just for info) */
	if (*glob_dln_bch != (char)NULL)
		(void)strcat(buffer, glob_dln_bch);
	else
		rei.pers_id = (int)_UNDEF;
	(void)strcat(buffer, "\t");

	bch.anw = (int)-2;	/* Auf dem Anwender String einen NULL-Terminator setzen */

	/* Buchungs TEXTE */
	if (SelFromTxt(bch.b_text, sprache, (int)_BUCHUNG, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
