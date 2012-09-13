/*D************************************************************/
/* Modul:     DBI - database output                           */
/*            start an action process with right parameters   */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>
#ifdef ps_unix
#include <sys/wait.h>
#endif

#define BLANK 0x20

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xOUTexec.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int OUTexec(int len, char *buffer)
{
	extern int sprache;
	extern MEMOBJ sqlmem;
	extern MP_GLOBALPROFIL globprof;
	extern int DebugFlag;
	extern FILE *MP_DBIDEBUGFILE;

	extern SPRACHEN spr;
	extern AKTIONEN akt;
	extern AKTIONS_TYP aktt;
	extern STATUS_WERTE sta;
	extern BUCHUNG bch;
	extern DLG_PART dlg;
	extern DIENSTLEISTUNG dtg;
	extern ARRANGEMENT arr;
	extern KUNDEN_TYP kunt;
	extern KUNDEN kun;
	extern DIENST_TRAEGER dlt;
	extern DIENST_ANGEBOT dla;
	extern KATEGORIE kat;
	extern REISENDER rei;
	extern KOLLEKTIV kol;
	extern HOST_KONT hkon;
	extern KONTINGENT kon;

	AKTIONSPARA *apara;
	char *ptr;
	char *ptrstart;
	char *to_buffers[MAX_MENU_ITEMS];
	char format[RECLAENGE];
	char query[RECLAENGE];
	char prozess[RECLAENGE];
	int i, j;
	int anzahl, error, id;
	int status=(int)MPOK;
	int device, spooltyp, stain, staout;

	(void)memset((void *)format, NULL, (size_t)RECLAENGE);
	*format = NULL;

	(void)memset((void *)&aktt, NULL, sizeof(AKTIONS_TYP));

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* AKTIONS_TYP */
	akt.a_typ_id = 0;
	id = MPAPIselectEntry((int)_AKTIONEN, to_buffers[MOUT_AKTT], (char *)&akt,
	                 sizeof(akt), sizeof(akt.akt_id));
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	id = MPAPIselectOneId((int)_AKTIONS_TYP, akt.a_typ_id, (char *)&aktt);
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOAKTT, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	(void)copyTextTo(prozess, aktt.proz, (int)_PROZLEN);

	/* device */
	sta.typ = (int)_DEVICE;
	if (getAttribut((int)_DEVICE, to_buffers[MOUT_DEV]) != (int)MPOK)
		{
		UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	device = sta.sta_id;

	/* spool typ */
	spooltyp = (int)_AKT_MAN;

	/* execute on reservation state */
	if (*to_buffers[MOUT_STAINRES] != NULL)
		{
		sta.typ = (int)_R_STA;
		if (getAttribut((int)_R_STA, to_buffers[MOUT_STAINRES]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		stain = sta.sta_id;
		}
	else
		stain = (int)_UNDEF;

	/* set reservation state after good execution */
	if (*to_buffers[MOUT_STAOUTRES] != NULL)
		{
		sta.typ = (int)_R_STA;
		if (getAttribut((int)_R_STA, to_buffers[MOUT_STAOUTRES]) != (int)MPOK)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		staout = sta.sta_id;
		}
	else
		staout = (int)_UNDEF;

	/* write DB name with path as first argument ! */
	ptr = prozess;
	ptr += strlen(prozess);
	(void)sprintf(ptr, " -L %d -d %s -U %s,%s -m %d -S %d -t %d -H %s", sprache,
		globprof.database, globprof.user, globprof.password, device, spooltyp,
	   aktt.a_typ_id, globprof.hostname);
	if (staout > (int)_UNDEF)
		{
		ptr += strlen(ptr);
		sprintf(ptr, " -z %d", staout);
		}
	if (stain > (int)_UNDEF)
		{
		ptr += strlen(ptr);
		sprintf(ptr, " -Z %d", stain);
		}

	/* AKTIONSPARA  hole alle Parameter */
	(void)sprintf(query, _SEL_PARA_AKTT, aktt.a_typ_id);
	status=MPAPIdb_sqlquery(_AKTIONSPARA, &sqlmem.buffer, query,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != MPOK || anzahl < 0)
		{
		UtilMsg((int)MPE_OUTPUT, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	apara = (AKTIONSPARA *)sqlmem.buffer;
	for (i=0, j=DEFAULTFIELDS; i<anzahl && anzahl > (int)NULL; i++, j++)
		{
		if (apara[i].muss == TRUE && *to_buffers[j] == NULL)
			{
			if (apara[i].typ != (int)_UNDEF)
				{
				status = (int)MPE_MUSSPARAEMPTY;
				break;
				}
			}

		if (apara[i].muss == FALSE && *to_buffers[j] == NULL)
			continue;

		/* setze ptr auf prozess zum anh�ngen der parameter */
		ptr = prozess;
		ptr += strlen(prozess);
		ptrstart = ptr;
		strcpy(ptr, " ");
		ptr++;

		/* setze parameterbezeichnung */
		if (*apara[i].bez == NULL)
			continue;
		(void)copyTextTo(ptr, apara[i].bez, _PARALEN);
		ptr = prozess;
		ptr += strlen(prozess);

		/* setze ID der typen */
		switch(apara[i].typ)
			{
			case (int)_DIENST_ANGEBOT:
				id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[j], (char *)&dla,
								sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id));
				break;
			case (int)_ARRANGEMENT:
				id = MPAPIselectEntry((int)_ARRANGEMENT, to_buffers[j], (char *)&arr,
								sizeof(ARRANGEMENT), sizeof(arr.arr_id));
				break;
			case (int)_BUCHUNG:
				id=MPAPIselectEntry((int)_BUCHUNG, to_buffers[j], (char *)&bch,
									sizeof(BUCHUNG), sizeof(bch.bid));
				if (bch.bid != (int)_UNDEF)
					id = bch.bid;
				else
					id = (int)_UNDEF;
				break;
			case (int)_DLG_PART:
				id = MPAPIselectEntry((int)_DLG_PART, to_buffers[j], (char *)&dlg,
								sizeof(DLG_PART), sizeof(dlg.dl_id));
				break;
			case (int)_KOLLEKTIV:
				id = MPAPIselectEntry((int)_KOLLEKTIV, to_buffers[j], (char *)&kol,
								sizeof(KOLLEKTIV), sizeof(kol.k_id));
				break;
			case (int)_DIENST_TRAEGER:
				dlt.stufe = (int)1;
				id = MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[j], (char *)&dlt,
								sizeof(DIENST_TRAEGER), sizeof(dlt.dlt_id));
				break;
			case (int)_KUNDEN:
				id = MPAPIselectEntry((int)_KUNDEN, to_buffers[j], (char *)&kun,
								sizeof(KUNDEN), sizeof(kun.pers_id));
				break;
			case (int)_KATEGORIE:
				id = MPAPIselectEntry((int)_KATEGORIE, to_buffers[j], (char *)&kat,
								sizeof(KATEGORIE), sizeof(kat.kat_id));
				break;
			case (int)_SPRACHEN:
				id=MPAPIselectEntry((int)_SPRACHEN, to_buffers[j], (char *)&spr,
						sizeof(SPRACHEN), sizeof(spr.s_id));
				break;
			case (int)_DIENSTLEISTUNG:
				id = MPAPIselectEntry((int)_DIENSTLEISTUNG, to_buffers[j], (char *)&dtg,
								sizeof(DIENSTLEISTUNG), sizeof(dtg.dlg_id));
				break;
			case (int)_REISENDER:
				id = MPAPIselectEntry((int)_REISENDER, to_buffers[j], (char *)&rei,
								sizeof(REISENDER), sizeof(rei.pers_id));
				break;
			case (int)_KUNDEN_TYP:
				id = MPAPIselectEntry((int)_KUNDEN_TYP, to_buffers[j], (char *)&kunt,
								sizeof(KUNDEN_TYP), sizeof(kunt.k_typ_id));
				break;
			case (int)_HOST_KONT:
				id = MPAPIselectEntry((int)_HOST_KONT, to_buffers[j], (char *)&hkon,
								sizeof(HOST_KONT), sizeof(hkon.hostkont_id));
				break;
			case (int)_KONTINGENT:
				id = MPAPIselectEntry((int)_KONTINGENT, to_buffers[j], (char *)&kon,
								sizeof(KONTINGENT), sizeof(kon.kont_id));
				break;
			default:
				id = _UNDEF;
				break;
			}

		if (apara[i].typ == (int)_UNDEF)
			{
			if (apara[i].muss == TRUE)
				{
				if (*to_buffers[j] == NULL) /* only a flag */
					continue;
				else
					{
					strcpy(ptr, " ");
					ptr++;
					(void)copyTextTo(ptr, to_buffers[j], _BEZLEN);
					}
				}
			else
				{
				if (apara[i].flag == TRUE)
					{
					if (*to_buffers[j] != NULL)  /* we set a flag if buffer is set */
						continue;
					else
						{
						ptr = ptrstart;
						*ptr = NULL;
						continue;
						}
					}
				else
					{
					if (*to_buffers[j] == NULL) /* skip this parameter it's empty */
						{
						ptr = ptrstart;
						*ptr = NULL;
						continue;
						}
					else
						{
						strcpy(ptr, " ");
						ptr++;
						(void)copyTextTo(ptr, to_buffers[j], _BEZLEN);
						}
					}
				}
			}
		else
			{
			if (apara[i].muss == TRUE)
				{
				if (*to_buffers[j] == NULL)
					{
					status = (int)MPE_MUSSPARAEMPTY;
					break;
					}
				else if ( id == _UNDEF && *to_buffers[j] != NULL ) 
					(void)sprintf(ptr, " %s", to_buffers[j]);
				else
					(void)sprintf(ptr, " %d", id);
				}
			else
				{
				if (*to_buffers[j] == NULL) /* skip parameter it's empty */
					{
					ptr = ptrstart;
					*ptr = NULL;
					continue;
					}
				else if ( id == _UNDEF && *to_buffers[j] != NULL ) 
					(void)sprintf(ptr, " %s", to_buffers[j]);
				else
					(void)sprintf(ptr, " %d", id);
				}
			}
		} /* end of for all parameters */
	if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}		

	/* Execute the process and set information about it */
	if (DebugFlag)
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "Exec AKTION: %s", prozess);
	error = UtilExec(prozess, (int)BACKGROUND);

	/* make an info */
	UtilMsgGet((int)MPI_AKTEXECDONE1, MSGTYP_INFO, format);
	(void)sprintf(buffer, format, prozess);
	(void)strcat(buffer, "\n\n");
	UtilMsgGet((int)MPI_AKTEXECDONE2, MSGTYP_INFO, format);
	(void)strcat(buffer, format);
	COMMSTAT = MESSAGEOK;
	COMMTYP = INFO;
	ACTIONTYP = INFOTXT;

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
