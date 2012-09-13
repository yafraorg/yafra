/*D***********************************************************
 * Modul:     DBI - booking modul
 *            main entry point
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

#define MBCH_TXT 17        /* in mpmendef.h eintragen */
#define MBME_TEXT 17        /* in mpmendef.h eintragen */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMBCHinput.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int BMBCHinput(int len , char *buffer)
{
	extern int sprache;
	extern MP_PROFIL prof;
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern AKTIONEN akt;
	extern ARRANGEMENT arr;
	extern STATUS_WERTE sta;
	extern KOLLEKTIV kol;
	extern DIENSTLEISTUNG dtg;
	extern REISENDER rei;
   extern TEXTE txt;
	extern char glob_arr_bch[];
	extern char glob_dl_bch[];
	extern char userid[];
	extern unsigned char bm_obj;
	extern unsigned char bm_state;
	extern int           bm_dlncnt;
	extern unsigned char bm_lastbid;
	extern unsigned char bm_arrkom;
	extern unsigned char logging_booking;

	BUCHUNG dbch;
	KUNDEN rechnungsadr;
	KUNDEN bchst;

	struct tm DateTime;
	int status=(int)MPOK;
	int id;
	char *to_buffers[MAX_MENU_ITEMS];
	char tmplog[_RECORDLEN];

	status = UtilSplitMenubuffer(buffer, to_buffers, '~');
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		bch.bid = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* make total init of all booking related objects */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		BMinit();
		/* SECURITY: do not allow readonly users access */
		if (prof.seclevel == _SECLEVEL_READONLY || prof.seclevel == _SECLEVEL_NOP)
			{
			UtilMsg((int)MPE_NOPERMISSION, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}

		/* Kunden Buchungsstelle setzen */
		/* [MBME_KUNBCH] not used anymore */

		/* intern - Aktueller User schreiben - intern */
		bch.anw = prof.mpid;
		}

	if (prof.seclevel == _SECLEVEL_USER || prof.seclevel == _SECLEVEL_DBA ||
	  (prof.seclevel == _SECLEVEL_BOOKING && prof.mpid == bch.anw))
      {
		bch.anw = prof.mpid;
		}
	else if (prof.seclevel != _SECLEVEL_DBA)
		{
		UtilMsg((int)MPE_NOPERMISSION, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	else
		{
		/* log DBA action on other BCHST booking */
		}

	/* set type of booking (from which programm) */
	bch.ast = _BCH_LOCAL;

	/* setze Buchungsstatus */
	if (ACTIONTYP == (unsigned char)INSERT)  /* overwrite STA in insert mode ! */
		bch.sta = _BCH_ENTER;
	else
		{
		sta.typ = (int)_BSTA; 	/* Zustand der Buchung */
		status  = getAttribut((int)_BSTA, to_buffers[MBME_BCHSTA]);
		bch.sta = sta.sta_id;
		}

	if (status == (int)MPOK)
		{
		/* Doppelbuchung pruefen */
		if (*to_buffers[MBME_BCHDOPPEL] != NULL &&
			 MPAPIselectEntry((int)_BUCHUNG, to_buffers[MBME_BCHDOPPEL], (char *)&dbch,
			 sizeof( BUCHUNG ), (size_t)0) != (int)_UNDEF)
			{
			bch.d_bid = dbch.bid;
			}
		else
			bch.d_bid = (int)_UNDEF;

		/* Buchungsreferenz setzen (manuell / auto. �ber MPAPIinsertEntry) */
		if (*to_buffers[MBME_BCHREF] != NULL)
			(void)strcpy( bch.ref, to_buffers[MBME_BCHREF]);
		else
			*bch.ref = NULL;

		/* Arrangement setzen */
		if (*to_buffers[MBME_ARR] != NULL)
			{
			bch.arr_id = MPAPIselectEntry((int)_ARRANGEMENT, to_buffers[MBME_ARR],
		        (char *)&arr, sizeof(ARRANGEMENT), sizeof(bch.arr_id));
			}
		else
			{
			bch.arr_id = (int)_UNDEF;
			arr.arr_id = (int)_UNDEF;
			*glob_arr_bch = NULL;
			}

		/* Dienstleistung setzen */
		if (*to_buffers[MBME_DL] != NULL)
			{
			dtg.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MBME_DL],
		        (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
			}
		else
			{
			dtg.dlg_id = (int)_UNDEF;
			*glob_dl_bch = NULL;
			}

		/* set book object (arr or dl) for further ops */
		if (bch.arr_id != (int)_UNDEF)
			bm_obj = (unsigned char)_ARRANGEMENT;
		else
			bm_obj = (unsigned char)_DIENSTLEISTUNG;

		/* Kollektiv setzen */
		if (*to_buffers[MBME_KOL] != NULL)
			{
			bch.k_id = MPAPIselectEntry((int)_KOLLEKTIV, to_buffers[MBME_KOL],
			       (char *)&kol,	sizeof( KOLLEKTIV ), sizeof(bch.k_id));
			}
		else
			bch.k_id = (int)_UNDEF;

		/* Kunden Rechnungsadresse setzen */
		if (*to_buffers[MBME_KUNRECH] != NULL)
			{
			bch.kid = MPAPIselectEntry((int)_KUNDEN, to_buffers[MBME_KUNRECH],
			       (char *)&rechnungsadr,	sizeof(KUNDEN), sizeof(bch.kid));
			}
		else
			bch.kid = (int)_UNDEF;

		/*TODO fix this - was a string befor now an int Sachbearbeiter der Rechnungsstelle setzen */
		bch.sach = prof.mpid;

		/* set booking date of insert */
		if (ACTIONTYP == (unsigned char)INSERT)
			(void)time( (time_t *)&bch.b_dat ); /* Buchungsdatum setzen */

		/* set booking date of last modification */
		(void)time((time_t *)&bch.m_dat);      /* Modifikationsdatum */

		/* Kundenoption bis Datum */
		if (*to_buffers[MBME_KUNOPT] != NULL)
			{
			(void)memset( (void *)&DateTime, NULL, sizeof( DateTime ));
			DateTime.tm_mday = (int)_UNDEF;
			DateTime.tm_mon  = (int)_UNDEF;
			DateTime.tm_year = (int)_UNDEF;
			ReadDate( &DateTime, (time_t *)&bch.opt_kid, to_buffers[MBME_KUNOPT] );
			}
		else
			bch.opt_kid = (int)_UNDEF;

		/* Buchungsoption bis Datum */
		if (*to_buffers[MBME_ANFOPT] != NULL)
			{
			(void)memset( (void *)&DateTime, NULL, sizeof( DateTime ) );
			DateTime.tm_mday = (int)_UNDEF;
	      DateTime.tm_mon  = (int)_UNDEF;
			DateTime.tm_year = (int)_UNDEF;
			ReadDate( &DateTime, (time_t *)&bch.opt_bst, to_buffers[MBME_ANFOPT]);
			}
		else
			bch.opt_bst = (int)_UNDEF;

		/* Saison vererben */
		if (arr.arr_id != (int)_UNDEF)
			bch.sai_id = arr.sai_id;
		else if (dtg.dlg_id != (int)_UNDEF)
			bch.sai_id = dtg.sai_id;
		else
			bch.sai_id = (int)_UNDEF; /* we must set it later */

		/* set booking text */
		if (*to_buffers[MBME_TEXT] != NULL)
			{
			txt.typ    = (int)_BUCHUNG;
			txt.s_id   = sprache;
			txt.textid = bch.b_text;
			bch.b_text = xTxtWrite(to_buffers[MBME_TEXT]);
			}
		else
			bch.b_text = (int)_UNDEF;

		status = WriteEntry((int)_BUCHUNG, (char *)&bch, (BEZEICHNUNG *)NULL);
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			BMinit();
			bch.bid = (int)_UNDEF;
			}
		else
			{
			/* set bm to active */
			bm_state = (unsigned char)_BM_BCH;
			bd.bid = bch.bid;

			/* execution time logging */
			if (logging_booking)
				{
				if (ACTIONTYP == (unsigned char)INSERT)
					(void)sprintf(tmplog, "%d: Dossier eroeffnet mit Arrangement %d und Gruppe %d",
					      bch.bid, bch.arr_id, bch.k_id);
				else if (ACTIONTYP == (unsigned char)UPDATE)
					(void)sprintf(tmplog, "%d: Dossier mutiert mit Arrangement %d und Kollektiv %d",
					      bch.bid, bch.arr_id, bch.k_id);
				else
					(void)sprintf(tmplog, "%d: Dossier geloescht", bch.bid);
				MPlog(_LOGBOOKING, status, tmplog, __FILE__);
				}

			/* set last BID */
			if (bm_lastbid != bch.bid)
				{
				bm_lastbid = bch.bid;
				bm_arrkom  = (unsigned char)FALSE;
				}

			/* start now the bookingmask dialog with GUI */
			if (ACTIONTYP == (unsigned char)INSERT)
				status = BMDLNsend(len, buffer);
			else if (ACTIONTYP == (unsigned char)UPDATE &&
			   *to_buffers[MBME_DLN] != NULL)
				{
				/* go directly to BMRES mask */
				id = MPAPIselectEntry((int)_REISENDER, to_buffers[MBME_DLN],
				    (char *)&rei, sizeof(rei), sizeof(rei.pers_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
					UtilSplitFreeMenubuffer(to_buffers);
					return(MPOK);
					}
				bm_dlncnt = 1; /* one REISENDER is active */
				bd.dln_id = rei.pers_id;
				status = BMobjChoose(len, buffer);
				}
			else if (ACTIONTYP == (unsigned char)UPDATE)
				{
				status = MPAPIupdate_booksta(bch.bid); /* update sta of BUCHUNG */
				status = BMDLNchoosefirst(bch.bid);
				status = BMDLNsend(len, buffer);
				}

			/* if DELETE we do nothing more - gone is gone */
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBCHST, MSGTYP_ERROR, NULL);
		bch.bid = (int)_UNDEF;
		status  = (int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return( status );
}
