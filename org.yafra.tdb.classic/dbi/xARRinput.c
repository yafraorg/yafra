/*D***********************************************************
 * Modul:     DBI - database insert/update/delete                           
 *            Arrangements
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f?r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xARRinput.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int ARRinput(int len, char *buffer)
{
	extern BEZEICHNUNG bez;
	extern ARRANGEMENT arr;
	extern DIENSTLEISTUNG dtg;
	extern PROGRAMM prg;
	extern TEXTE txt;
	extern STATUS_WERTE sta;
	extern ARR_DLG ad;
	extern int sprache;

	extern int AnzParts;
	extern char glob_bez_arr[];
	extern char glob_dtg_arr[];
	extern ARR_DLG ad_old;

	ARRANGEMENT newarr;
	ARR_DLG newad;
	struct tm DateTime;
	char *to_buffers[MAX_MENU_ITEMS];
	char arrbez[_RECORDLEN];
	char message[_RECORDLEN];
	int defaultordnr;
	int status = (int)MPOK;
	int docopy = (int)FALSE;

	char tmp_buffer[_RECORDLEN];

	/* init */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	txt.typ  = (int)_ARRANGEMENT;
	txt.s_id = sprache;
	bez.s_id = sprache;
	bez.typ  = (int)_ARRANGEMENT;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		arr.arr_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* check MUST fields */
	if (*to_buffers[MARR_BEZ] == NULL || *to_buffers[MARR_DAT] == NULL)
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	/* make action */
	switch (ACTIONTYP)
		{
		case MPDELETE:
			/* an ARR has to be active */
			if (arr.arr_id == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOARR, MSGTYP_ERROR, NULL);
				status=(int)MPWARNING;
				break;
				}				

			/* set ARR_ID and DLG_ID, TEIL if possible */
			if (*to_buffers[MARR_DL] == NULL)
				{
				ad.dlg_id = (int)_UNDEF;
				ad.arr_id = (int)arr.arr_id;
				ad.teil   = (int)_UNDEF;
				}
			else
				{
				ad.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MARR_DTG],
				            (char *)&dtg, sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
				ad.dlg_id = dtg.dlg_id;
				ad.arr_id = arr.arr_id;
				(void)readInteger(&ad.teil, to_buffers[MARR_TEILNR]);
				}

			/* delete ARR_DL */
			status = MPAPIdeleteEntry((int)_ARR_DLG, (char *)&ad);
			if (status != (int)MPOK && status != (int)MPE_NOINSUPDDEL)
				break;

			/* try to delete ARRANGEMENT */
			status = WriteEntry((int)_ARRANGEMENT, (char *)&arr, &bez);
			status = (int)MPOK; /* overwrite status because it's OK if we get errors */
			break;

		case INSERT:
			/* initialisiere bei INSERT Werte auf _UNDEF */
			newarr.arr_id = (int)_UNDEF;
			newarr.prg_id = (int)_UNDEF;
			newarr.sai_id = (int)_UNDEF;
			newarr.textid = (int)_UNDEF;
			txt.textid    = (int)_UNDEF;

			/* Verwalte Bezeichnung */
			(void)copyTextTo(bez.bez, to_buffers[MARR_BEZ], (int)_BEZLEN);

			/* Vergleiche Arrangement fuer ARRcopy */
			(void)copyTextTo(arrbez, glob_bez_arr, (int)_BEZLEN);
			(void)sscanf(glob_bez_arr, "%[^=]", arrbez);
			UtilDelBlanks(arrbez);
			if (strcmp(to_buffers[MARR_BEZ], arrbez) != (int)MPOK)
				*glob_bez_arr = (char)NULL;
			if (*glob_bez_arr != NULL)
				docopy = (int)TRUE;

			/* PROGRAMM unbedingt erforderlich */
			if (*to_buffers[MARR_PRG] == NULL)
				{
				UtilMsg((int)MPE_NOPRG, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				break;
				}
			newarr.prg_id = MPAPIselectEntry((int)_PROGRAMM, to_buffers[MARR_PRG],
			    (char *)&prg, sizeof(PROGRAMM), sizeof(newarr.prg_id));

			/* SAISON  taken from PROGRAM */
			newarr.sai_id = prg.sai_id;

			/* DATE of ARRANGEMENT */
			(void)ReadDate(&DateTime, (time_t *)&newarr.a_dat, to_buffers[MARR_DAT]);

	      /* CODE */
		   (void)copyTextTo(newarr.code, to_buffers[MARR_CODE], (int)_KRZLLEN);

			/* TEXT */
			newarr.textid = xTxtWrite(to_buffers[MARR_TXT]);

			/* look if to copy or insert a new ARR */
			if (docopy == (int)TRUE && newarr.a_dat != arr.a_dat)
				{
				strcpy(message, "Arrangement kopieren / copy this package ?");
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					status = ARRcopymove(to_buffers[MARR_DAT], glob_bez_arr);
				else
					status = (int)MPOK;
				if (status == MPNOP)
					{
					UtilMsg((int)MPE_ARRCOPY, MSGTYP_ERROR, NULL);
					status=(int)MPERROR;
					break;
					}
				}
			/* look if we have to insert only ARR_DLG */
			else if (docopy == (int)TRUE && newarr.a_dat == arr.a_dat)
				{
				/* do nothing ! no insert of ARRANGEMENT */
				/* set only newarr.arr_id to selected arr.arr_id for ARR_DLG insert */
				newarr.arr_id = arr.arr_id;
				}
			else
				{
				status = WriteEntry((int)_ARRANGEMENT, (char *)&newarr, &bez);
				if (status != (int)MPOK)
					break;
				}

			/* ARRANGEMENT DETAIL */
			if (*to_buffers[MARR_DTG] != NULL && newarr.arr_id != (int)_UNDEF)
				{
				ad.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[MARR_DTG],
				    (char *)&dtg,	sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
				ad.arr_id = newarr.arr_id;

				/* ARR_DL:  TEIL field */
				defaultordnr = MPAPIid_max((int)_ARR_DLG, (int)_ORD, (char *)&ad);
				defaultordnr++;
				if (defaultordnr < 1)
					defaultordnr = 1;
				if (*to_buffers[MARR_TEILNR] == NULL)
					ad.teil = defaultordnr;
				else
					{
					status = readInteger(&ad.teil, to_buffers[MARR_TEILNR]);
					if (status == (int)MPERROR)
						ad.teil = defaultordnr;
					else
						if (ad.teil < (int)1)
							ad.teil = defaultordnr;
					}

				/* ARR_DL:  PRIO field */
				if (getAttribut((int)_PRIO, to_buffers[MARR_PRIO]) != (int)MPERROR)
					ad.prio=sta.sta_id;
								
				status = MPAPIinsertEntry((int)_ARR_DLG, (char *)&ad, (BEZEICHNUNG *)NULL);
				if (status != (int)MPOK)
					break;
				}
			break;

		case UPDATE:
			/* an ARR has to be active */
			if (arr.arr_id == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOARR, MSGTYP_ERROR, NULL);
				status=(int)MPWARNING;
				break;
				}				

			/* update of BEZ is not possible over this menu ! */
			bez.bez_id = arr.bez_id;

			/* PROGRAMM unbedingt erforderlich */
			if (*to_buffers[MARR_PRG] == NULL || ((MPAPIselectEntry((int)_PROGRAMM,
			    to_buffers[MARR_PRG], (char *)&prg, sizeof(PROGRAMM),
			    sizeof(arr.prg_id))) == (int)_UNDEF))
				{
				UtilMsg((int)MPE_NOPRG, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				break;
				}
			arr.prg_id = prg.prg_id;

			/* SAISON  taken from PROGRAM */
			arr.sai_id = prg.sai_id;

			/* DATE of ARRANGEMENT */
			ReadDate(&DateTime, (time_t *)&arr.a_dat, to_buffers[MARR_DAT]);

	      /* CODE */
		   (void)copyTextTo(arr.code, to_buffers[MARR_CODE], (int)_KRZLLEN);

			/* TEXT */
			txt.textid = arr.textid;
			arr.textid = xTxtWrite(to_buffers[MARR_TXT]);

			/* update ARRANGEMENT */
			status = WriteEntry((int)_ARRANGEMENT, (char *)&arr, &bez);
			if (status != (int)MPOK)
				break;

			/* ARRANGEMENT DETAIL */
			if (*to_buffers[MARR_DTG] != NULL && arr.arr_id != (int)_UNDEF)
				{
				newad.arr_id = arr.arr_id;

				/* ARR_DL:  TEIL field */
				defaultordnr = MPAPIid_max((int)_ARR_DLG, (int)_ORD, (char *)&newad);
				defaultordnr++;
				if (defaultordnr < 1)
					defaultordnr = 1;
				if (*to_buffers[MARR_TEILNR] == NULL)
					newad.teil = defaultordnr;
				else
					{
					status = readInteger(&newad.teil, to_buffers[MARR_TEILNR]);
					if (status == (int)MPERROR)
						newad.teil = defaultordnr;
					else
						if (newad.teil < (int)1)
							newad.teil = defaultordnr;
					}

				/* ARR_DL:  PRIO field */
				if (getAttribut((int)_PRIO, to_buffers[MARR_PRIO]) != (int)MPERROR)
					newad.prio = sta.sta_id;

				if (*to_buffers[MARR_DTG] != NULL)
					{
					newad.dlg_id = MPAPIselectEntry((int)_DIENSTLEISTUNG,
					   to_buffers[MARR_DTG], (char *)&dtg,
						sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
					newad.dlg_id = dtg.dlg_id;
					newad.arr_id = arr.arr_id;
					}
				else
					newad.dlg_id = (int)_UNDEF;
								
				/* try to delete old one and insert new one */
				status = MPAPIdeleteEntry((int)_ARR_DLG, (char *)&ad);
				status = MPAPIinsertEntry((int)_ARR_DLG, (char *)&newad, (BEZEICHNUNG *)NULL);
				}
			break;

		default:
			break;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
