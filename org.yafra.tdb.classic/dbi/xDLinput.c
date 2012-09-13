/*D***********************************************************
 * Modul:     DBI - database insert/update/delete                           
 *            DIENSTLEISTUNG is build with two parts:
 *
 *          - the header of the DIENSTLEISTUNG
 *            (bez, sai_id, textid, a_zeit, akt_id)
 *
 *          - the relations between DLG_PART and DIENSTLEISTUNG
 *            (realized with dlg_dlg tabel)
 *
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f?r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

static int DLcheckORD(int, int);
static int DLmakeNewOrd(int, int);
static int DLdl_dlg(char *, DLG_DLG *, int);

int DLinput(int len, char *buffer)
{
	extern DIENSTLEISTUNG dtg;
	extern DIENST_ANGEBOT dla;
	extern DLG_PART tdl;
	extern DLG_DLG dd;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern AKTIONEN akt;
	extern char glob_bez_dtg[];
	extern int sprache;

	DIENSTLEISTUNG newdl;
	char *to_buffers[MAX_MENU_ITEMS];
	char **splitbuffer;
	char message[_RECORDLEN];
	char dlbez[_RECORDLEN];
	int status=(int)MPOK;
	int anzsplit;
	int splitflag;
	int bezflag;
	int i;
	int docopy;
	int dlgpartid;
	int defaultordnr;
	struct tm DateTime;

	/* init */
	(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	txt.typ  = (int)_DIENSTLEISTUNG;
	txt.s_id = sprache;
	bez.s_id = sprache;
	bez.typ  = (int)_DIENSTLEISTUNG;
	splitflag = NOPARTS;
	docopy   = (int)FALSE;
	bezflag  = (int)FALSE;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dtg.dlg_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* check MUST fields */
	if (*to_buffers[MDL_BEZ] == (char)NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	/* make action */
	switch (ACTIONTYP)
		{
		case MPDELETE:
			/* try to get something with the KEY fields */
			(void)sprintf(dlbez, "%s%s%s", to_buffers[MDL_BEZ], TRENNER,
		              to_buffers[MDL_DAT]);
			dtg.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, dlbez,
			     (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));

			/* set DLG_ID and DL_ID if possible */
			if (*to_buffers[MDL_TDL] == (char)NULL)
				{
				dd.dlg_id = (int)dtg.dlg_id;
				dd.dl_id  = (int)_UNDEF;
				dd.ord    = (int)_UNDEF;
				}
			else
				{
				dd.dlg_id = dtg.dlg_id;
				dd.dl_id = MPAPIselectEntry((int)_DLG_PART, to_buffers[MDL_TDL],
				            (char *)&tdl, sizeof(DLG_PART), sizeof(tdl.dl_id));
				(void)readInteger(&dd.ord, to_buffers[MDL_ORD]); /* must be set */
				}

			/* delete of DLG_DLG is made in DLdelete() */
			/* try to delete DIENSTLEISTUNG */
			status = WriteEntry((int)_DIENSTLEISTUNG, (char *)&dtg, &bez);
			break;

		case INSERT:
			/* initialisiere bei INSERT Werte auf UNDEF */
			newdl.dlg_id = (int)_UNDEF;
			newdl.akt_id = (int)_UNDEF;
			newdl.sai_id = (int)_UNDEF;
			newdl.textid = (int)_UNDEF;
			newdl.a_zeit = (int)_MP_NODATE;
			txt.textid   = (int)_UNDEF;

			/* BEZEICHNUNG */
			(void)copyTextTo(bez.bez, to_buffers[MDL_BEZ], (int)_BEZLEN);

			/* compare DL for DLcopy */
			(void)copyTextTo(dlbez, glob_bez_dtg, (int)_BEZLEN);
			(void)sscanf(glob_bez_dtg, "%[^=]", dlbez);
			UtilDelBlanks(dlbez);
			if (strcmp(to_buffers[MDL_BEZ], dlbez) != (int)MPOK)
				*glob_bez_dtg = (char)NULL;

			/* get DATE/TIME */
			if (*to_buffers[MDL_DAT] != (char)NULL)
				(void)ReadDate(&DateTime, (time_t *)&newdl.a_zeit, to_buffers[MDL_DAT]);

		   /* Code */
		   (void)copyTextTo(newdl.code, to_buffers[MDL_CODE], (int)_KRZLLEN);

			/* set docopy flag if same object, but different date (exept. is no date) */
			if (*glob_bez_dtg != (char)NULL && newdl.a_zeit != dtg.a_zeit && dtg.a_zeit > (int)0)
				docopy = (int)TRUE;

			/* get TDL's now from a twinnselect for inherit and DLG_DLG insert */
			if (docopy != (int)TRUE)
				{
				if (*to_buffers[MDL_TDL] != (char)NULL)
					{
					splitbuffer = (char **)UtilSplitBuffer(to_buffers[MDL_TDL], &anzsplit, (char)_MPSYMB_CR);
					if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
						{
						UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
						status = (int)MPERROR;
						break;
						}
					else if (anzsplit == (int)0)
						splitflag = SINGLESEL;
					else
						splitflag = MULTISEL;
					}
				else
					{
					UtilMsg((int)MPE_NODLTDL, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}

				/* inherit SAISON from HOST TDL of this DL */
				if (splitflag == SINGLESEL)
					tdl.dl_id = MPAPIselectEntry((int)_DLG_PART, to_buffers[MDL_TDL],
					     (char *)&tdl, sizeof(DLG_PART), sizeof(tdl.dl_id));
				else
					tdl.dl_id = MPAPIselectEntry((int)_DLG_PART, splitbuffer[0],
					     (char *)&tdl, sizeof(DLG_PART), sizeof(tdl.dl_id));
				newdl.sai_id = tdl.sai_id;

				/* if no DATE/TIME was set, inherit it from HOST TDL */
				if (*to_buffers[MDL_DAT] == (char)NULL)
					newdl.a_zeit = tdl.a_zeit;

				/*!!! only HOST AKTIONEN permitted */
				akt.a_typ_id = (int)_UNDEF;
				if (*to_buffers[MDL_AKT] != (char)NULL)
					{
					newdl.akt_id = MPAPIselectEntry((int)_AKTIONEN, to_buffers[MDL_AKT],
				         (char *)&akt, sizeof(AKTIONEN), sizeof(akt.akt_id));
					}
				else
					{
					/* inherit AKT from DLA of TDL, because there was no AKT set */
					/* TDL was already selected above for SAISON */
					status = MPAPIselectOneId((int)_DIENST_ANGEBOT, tdl.dla_id, (char *)&dla);
					if (status != (int)_UNDEF)
						newdl.akt_id = dla.akt_id;
					else
						newdl.akt_id = (int)_UNDEF;
					}

				/* TEXTE Segment schreiben */
				newdl.textid = xTxtWrite(to_buffers[MDL_TXT]);
				}

			/* look if to copy or insert a new ARR */
			if (docopy == (int)TRUE)
				{
				strcpy(message, "Dienstleistung kopieren / copy this service ?");
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
				{
					/* through the usage of sequences, this is not needed anymore
					strcpy(message, "Mit neuer Bezeichnung kopieren (Ja/Nein) ?");
					status = UtilImmediatCall(message);
					if (status == (int)TRUE)
						bezflag = (int)TRUE;
					***************************************************************/
					bezflag = (int)FALSE;
					status = DLcopymove(&dtg, to_buffers[MDL_DAT], bezflag );
				}
				else
					status = (int)MPOK;

				if (status == MPNOP)
					{
					UtilMsg((int)MPE_DLCOPY, MSGTYP_ERROR, NULL);
					status=(int)MPERROR;
					}
				break;
				}
			/* look if we have only to insert DLG_DLG, because DL already exists */
			else if (*glob_bez_dtg != (char)NULL)
				{
				/* do nothing ! no insert of DIENSTLEISTUNG */
				/* set only newdl.dlg_id to selected dtg.dlg_id for DLG_DLG insert */
				newdl.dlg_id = dtg.dlg_id;
				}
			else /* insert new DL */
				{
				status = WriteEntry((int)_DIENSTLEISTUNG, (char *)&newdl, &bez);
				}

			if (status != (int)MPOK)
				break;

			/* DIENSTLEISTUNG DETAIL */
			if (*to_buffers[MDL_TDL] != (char)NULL && newdl.dlg_id != (int)_UNDEF)
				{
				dd.dlg_id = newdl.dlg_id;

				/* set default order number */
				defaultordnr = MPAPIid_max((int)_DLG_DLG, (int)_ORD, (char *)&newdl);
				defaultordnr++;
				if (defaultordnr < 1)
					defaultordnr = 1;

				if (*to_buffers[MDL_ORD] == (char)NULL)
					dd.ord = defaultordnr;
				else
					{
					status = readInteger(&dd.ord, to_buffers[MDL_ORD]);
					if (status == (int)MPERROR)
						dd.ord = defaultordnr;
					else
						{
						if (dd.ord < (int)1)
							dd.ord = defaultordnr;
						}
					}

				if (splitflag == SINGLESEL)
					{
					status = DLdl_dlg(to_buffers[MDL_TDL], &dd, defaultordnr);
					dlgpartid = dd.dl_id;
					}
				else
					{
					for (i=0; i<anzsplit && status == MPOK; i++)
						{
						status = DLdl_dlg(splitbuffer[i], &dd, defaultordnr);
						if (i == 0)
							dlgpartid = dd.dl_id;
						defaultordnr++;
						dd.ord++;
						}
					}
				}
			break;

		case UPDATE:
			/* get selected DL if key values has been changed */
			if (dtg.dlg_id == (int)_UNDEF)
				dtg.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, glob_bez_dtg,
			      (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));

			/* update of BEZ is not possible over this menu ! */
			bez.bez_id = dtg.bez_id;

			/* DATE of DL */
			ReadDate(&DateTime, (time_t *)&dtg.a_zeit, to_buffers[MDL_DAT]);

		   /* Code */
		   (void)copyTextTo(dtg.code, to_buffers[MDL_CODE], (int)_KRZLLEN);

			/*!!! only HOST AKTIONEN permitted */
			akt.a_typ_id = (int)_UNDEF;
			if (*to_buffers[MDL_AKT] != (char)NULL)
				{
				dtg.akt_id = MPAPIselectEntry((int)_AKTIONEN, to_buffers[MDL_AKT],
			         (char *)&akt, sizeof(AKTIONEN), sizeof(akt.akt_id));
				}

			/* TEXT */
			txt.textid = dtg.textid;
			dtg.textid = xTxtWrite(to_buffers[MDL_TXT]);

			/* update DIENSTLEISTUNG */
			status = WriteEntry((int)_DIENSTLEISTUNG, (char *)&dtg, &bez);
			if (status != (int)MPOK)
				break;

			/* DIENSTLEISTUNG DETAIL */
			if (*to_buffers[MDL_TDL] != (char)NULL && dtg.dlg_id != (int)_UNDEF)
				{
				dd.dlg_id = dtg.dlg_id;

				splitbuffer = (char **)UtilSplitBuffer(to_buffers[MDL_TDL], &anzsplit, (char)_MPSYMB_CR);
				if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
					{
					UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				else if (anzsplit == (int)0)
					splitflag = SINGLESEL;
				else
					splitflag = MULTISEL;

				/* set default order number */
				defaultordnr = MPAPIid_max((int)_DLG_DLG, (int)_ORD, (char *)&dtg);
				defaultordnr++;
				if (defaultordnr < 1)
					defaultordnr = 1;

				if (*to_buffers[MDL_ORD] == (char)NULL)
					dd.ord = defaultordnr;
				else
					{
					status = readInteger(&dd.ord, to_buffers[MDL_ORD]);
					if (status == (int)MPERROR)
						dd.ord = defaultordnr;
					else
						{
						if (dd.ord < (int)1)
							dd.ord = defaultordnr;
						}
					}

				if (splitflag == SINGLESEL)
					{
					status = DLdl_dlg(to_buffers[MDL_TDL], &dd, defaultordnr);
					dlgpartid = dd.dl_id;
					}
				else
					{
					for (i=0; i<anzsplit && status == MPOK; i++)
						{
						status = DLdl_dlg(splitbuffer[i], &dd, defaultordnr);
						if (i == 0)
							dlgpartid = dd.dl_id;
						defaultordnr++;
						dd.ord++;
						}
					}
				}
			break;

		default:
			break;
		}

	/* free up twin select split buffer */
	if (splitflag == MULTISEL)
		MPfreearray(splitbuffer, anzsplit);

	/* free up menu buffers */
	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}

/*F***********************************************************
 * Function:  add/modify DLG_DLG entry
 **************************************************************/
static int DLdl_dlg(char *dlgbez, DLG_DLG *dd, int defaultord)
{
	extern DLG_PART dlg;
	extern DLG_DLG dd_old;

	int status;

	/* setze alte DLG_DLG structur */
	dd_old.dlg_id = dd->dlg_id;
	dd_old.ord    = dd->ord;

	/* pr?fen ob ORD anzuhaengen oder einf?gen ist */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		status = DLcheckORD(dd->dlg_id, dd->ord);
		if (status != (int)MPOK)
			{
			dd->ord = defaultord;
			status = MPOK;
			}
		}

	dd->dl_id = MPAPIselectEntry((int)_DLG_PART, dlgbez, (char *)&dlg,
	  sizeof(DLG_PART), sizeof(dlg.dl_id));
	if (dd->dl_id == (int)_UNDEF)
		return((int)MPERROR);
	else
		{
		dd_old.dl_id  = dd->dl_id;  /* merke dl_id f?r alte DLG_DLG struct */
		dd->dl_id = dlg.dl_id;
		}

	if (ACTIONTYP != (int)INSERT)
		status = MPAPIdeleteEntry((int)_DLG_DLG, (char *)&dd_old);
	if (status == (int)MPOK && ACTIONTYP != (int)MPDELETE)
		status = MPAPIinsertEntry((int)_DLG_DLG, (char *)dd, (BEZEICHNUNG *)NULL);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_NODLA, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}




/*F***********************************************************
 * Function:  check if there's something to update in dlg_dlg
 **************************************************************/
static int DLcheckORD(int dl, int ord)
{
	extern MEMOBJ sqlmem;

	int status;
	int anzahl;
	char query[_QUERYLEN];

	(void)sprintf(query, _SEL_DLDLG_ORD, dl, ord);
	status = MPAPIdb_sqlquery((int)_DLG_DLG, &sqlmem.buffer, query, &anzahl,
	            &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK)
		return(status);

	if (anzahl != (int)1)
		return((int)MPERROR);

	status = DLmakeNewOrd(dl, ord);

	return(status);
}

/*F***********************************************************
 * Function:  update the whole dlg_dlg table with the new order
 **************************************************************/
static int DLmakeNewOrd(int dl, int ord)
{
	extern MEMOBJ sqlmem;

	DLG_DLG *dd;
	int status;
	int Savepoint;
	int anzahl;
	int i, j;
	char query[_QUERYLEN];

	status = MPAPIdb_setsavepoint(&Savepoint);

	(void)sprintf(query, _SEL_DLDLG, dl);
	status = MPAPIdb_sqlquery((int)_DLG_DLG, &sqlmem.buffer, query, &anzahl,
	            &sqlmem.datalen, &sqlmem.alloclen);
	if (status == MPOK && anzahl > (int)0)
		{
		dd = (DLG_DLG *)sqlmem.buffer;
		for (i=0; i < anzahl; i++)
			{
			if (dd[i].ord == ord)
				break;
			}
		for (j=(anzahl-1); (j >= i && status == MPOK); j--)
			{
			dd[j].ord++;
			status = MPAPIupdateEntry((int)_DLG_DLG, (char *)&dd[j], (BEZEICHNUNG *)NULL);
			}
		}

	if (status != MPOK)
		status = MPAPIdb_rollbacksavepoint(&Savepoint);

	return(status);
}
