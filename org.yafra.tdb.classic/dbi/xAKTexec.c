/*D***********************************************************
 * Modul:     DBI - database start action
 *            write modify date on bch and start actions
 *            start AKTION only with _AKT_AUTOIMM und _AKT_AUTOSPOOL
 *            and a valid SOURCE RESERVATIONSSTATUS
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTexec.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

#define _ARGINIT (int)-1
#define _ARGEXIT (int)-2
static int AKTfillupArgs(char *, int, BUCHUNG *, AKT_DETAIL *, AKTIONS_TYP *, AKTIONEN *);
static int setID(int, int, char *);

int AKTexec(BUCHUNG *buchung, int dl_id)
{
	extern int logging_user;

	MEMOBJ memres;
	RESERVATION *res;
	MEMOBJ memakt;
	AKT_DETAIL *aktionen;

	AKTIONS_TYP aktt;
	AKTIONEN akt;
	BEZEICHNUNG abez;
	KUNDEN_TYP kunt;
	KUNDEN kun;
	DLG_PART dlg;
	DIENST_ANGEBOT dla;
	DIENST_TRAEGER dlt;

	int id;
	int len;
	int anzahl, error, commit=(int)FALSE;
	int status=(int)MPOK, parts, i, j;
	int olduid;
	int anzakt, anzres;       /* Anzahl Elemente von MPAPIdb_sqlquery */
	char format[RECLAENGE];
	char *ptr, *str;
	char *to_buffers[MAX_MENU_ITEMS];
	char message[RECLAENGE];
	char query[_QUERYLEN];
	char command[RECLAENGE];
	char prozess[RECLAENGE];

	/* Init */
	memres.buffer = NULL;
	memres.alloclen = 0;
	memakt.buffer = NULL;
	memakt.datalen = 0;
	memakt.alloclen = 0;
	(void)AKTfillupArgs(NULL, _ARGINIT, NULL, NULL, NULL, NULL);

	/* get all actions for the buchung->bid */
	(void)sprintf(query, _SEL_AKTD_BCH_DL, buchung->bid, dl_id);
   status=MPAPIdb_sqlquery((int)_AKT_DETAIL, (char **)&memakt.buffer, query,
	                         &anzakt, &memakt.datalen, &memakt.alloclen);
	if (status == MPOK && anzakt > (int)0)
		{
		aktionen = (AKT_DETAIL *)memakt.buffer;
		olduid = aktionen[0].pers_id;

		for (i=0; i < anzakt && aktionen[i].pers_id == olduid && status == MPOK; i++)
			{
			/* check z_flag - pr�fe Zustandsflag der Aktion pro DLN */
			if (aktionen[i].z_flag == (int)_AKT_OK ||
			    aktionen[i].z_flag == (int)_AKT_ONEXECUTION ||
				 aktionen[i].z_flag == (int)_AKT_FATALERROR)
				continue;

			/* get aktion (b_flag) to look with reservation
			 * if we can start the aktion
			 */
			akt.akt_id = aktionen[i].akt_id;
			id = MPAPIselectOneId((int)_AKTIONEN, aktionen[i].akt_id, (char *)&akt);
			if (id == (int)_UNDEF)
				{
				/* Die Aktion nicht gefunden */
				UtilMsg((int)MPE_NOAKT, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				continue;
				}

			/* get reservation of the bid and uid to look if we can
			 * start the aktion
			 */
			memres.datalen = 0;
			(void)sprintf(query, _SEL_RES_BCHDLN_DL, buchung->bid, aktionen[i].pers_id, aktionen[i].dlg_id);
		   status=MPAPIdb_sqlquery((int)_RESERVATION, (char **)&memres.buffer,
			                query, &anzres, &memres.datalen, &memres.alloclen);
			if (status == MPOK && anzres > (int)0)
				{
				res = (RESERVATION *)memres.buffer;
				/* Vergleiche Res.Status mit Aktionsstart-Status */
				if (akt.b_flag != res[0].r_sta)
					continue;
				if (akt.a_flag != _AKT_AUTOIMM)
					if (akt.a_flag != _AKT_AUTOSPOOL)
						continue;
				}
			else
				{
				/* Keine Reservationen unter BID/UID gefunden -> Konsitenzfehler */
				/*!!! Fehlerbehandlung einbauen */
				status = (int)MPERROR;
				continue;
				}

			/* get aktions_typ to get the process name */
			id = MPAPIselectOneId((int)_AKTIONS_TYP, (int)aktionen[i].a_typ_id, (char *)&aktt);
			if (id != (int)_UNDEF)
				{
				int tmplen;

				/* fill up the command buffer to commit with the system cmd */
				(void)copyTextTo(prozess, aktt.proz, (int)_PROZLEN);
				tmplen = strlen(prozess);
				len = (int)(RECLAENGE - tmplen);
				status = AKTfillupArgs(&prozess[tmplen], len, buchung,
				                       &aktionen[i], &aktt, &akt);
				if (status == MPOK)
					{
					/* Execute the process and set information about it */
					error = UtilExec(prozess, (int)BACKGROUND);
					if (logging_user)
						MPlog(_LOGUSER, MPI_AKTSTART, prozess, __FILE__);
					}
				else
					{
					/*!!! internal error at command system() */
					status = (int)MPERROR;
					}
				}
			else
				{
				/* select aktions_typ error */
				UtilMsg((int)MPE_NOAKTT, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			} /* end of for loop */

		}
	else if (anzakt < (int)1)
		{
		/*!!! no akt_detail entries */
		status = (int)MPERROR;
		}

	/* Abschluss */
	if (status != (int)MPOK)
		{
		UtilMsgGet((int)MPE_NOBCHAKTDET, MSGTYP_ERROR, format);
		(void)sprintf(message, format, buchung->bid);
		UtilMsgWrite(message);
		status=(int)MPERROR;
		}

	/* exit - free memory */
	MPfree((void *)memakt.buffer);
	MPfree((void *)memres.buffer);
	(void)AKTfillupArgs(NULL, _ARGEXIT, NULL, NULL, NULL, NULL);

	return(status);
}


/*F***********************************************************
 * Function:  put needed arguments into arg buffer
 * In para:   BUCHUNG     current bookdata
 *            AKT_DETAIL  the action to fill up the arg for
 * InOut:     arg         the buffer to fill in the args
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static int AKTfillupArgs(char *arg, int len, BUCHUNG *buchung,
              AKT_DETAIL *aktdet, AKTIONS_TYP *aktt, AKTIONEN *akt)
{
	extern int sprache;
	extern MP_GLOBALPROFIL globprof;
	extern KUNDEN_TYP kunt;
	extern KUNDEN kun;
	extern DLG_PART dlg;
	extern DIENST_ANGEBOT dla;

	static MEMOBJ mempara;
	AKTIONSPARA *para;
	int i;
	int id;
	int kid, dlg_id, dla_id;
	int status = MPOK;
	int recovery = (int)FALSE;
	int anzahl;
	char query[_QUERYLEN];
	char *ptr;
	char *recover_ptr;

	/* check init or exit step */
	if (len == _ARGINIT)
		{
		mempara.buffer = NULL;
		mempara.alloclen = 0;
		mempara.datalen = 0;
		}
	else if (len == _ARGEXIT)
		MPfree((void *)mempara.buffer);
	else
		{
		/* get all parameters of the aktt */
		/* AKTIONSPARA  hole alle Parameter */
		(void)sprintf(query, _SEL_PARA_AKTT, aktt->a_typ_id);
		status=MPAPIdb_sqlquery(_AKTIONSPARA, &mempara.buffer, query,
	                         &anzahl, &mempara.datalen, &mempara.alloclen);
		if (status != MPOK)
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		para = (AKTIONSPARA *)mempara.buffer;

		/* write standard arguments:
		    fix PI (21.10.93) : support fully language independency of actions
		   - actual dialogue language
		   - DB name with path
		   - output media
		   - execution typ
		   - AKTIONSTYP  */
		(void)sprintf(arg, " -L %d -d %s -U %s,%s -m %d -S %d -t %d", sprache,
		 globprof.database, globprof.user, globprof.password, akt->m_flag,
		 akt->a_flag, aktt->a_typ_id);

		/* set each parameter found for the aktt */
		for (i=0; i<anzahl && anzahl>(int)NULL && status == MPOK; i++)
			{
			/* check flag parameters - set them only if MUSS is true */
			if (para[i].muss == (int)FALSE)
				continue;

			/* set PARAMETERBEZEICHNUNG only if it's here */
			if (*para[i].bez == NULL)
				continue;

			/* setze ptr auf arg zum anh�ngen der parameter */
			ptr = arg;
			ptr += strlen(arg);
			recover_ptr = ptr;  /* set this for recovery if we can not set para */
			strcpy(ptr, " ");
			ptr++;

			(void)copyTextTo(ptr, para[i].bez, _PARALEN);
			ptr = arg;
			ptr += strlen(arg);

			/* set ID of the known typs */
			switch(para[i].typ)
				{
				case (int)_BUCHUNG:
					id = buchung->bid;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_DIENSTLEISTUNG	:
					id = aktdet->dlg_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_DLG_PART	:
					id = aktdet[i].dl_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_KUNDEN_TYP	:
					kid = MPAPIselectOneId((int)_KUNDEN, buchung->kid, (char *)&kun);
					id = MPAPIselectOneId((int)_KUNDEN_TYP, (int)kun.k_typ_id, (char *)&kunt);
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_KUNDEN:
					id = buchung->kid;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_REISENDER:
					id = aktdet[i].pers_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case (int)_KOLLEKTIV:
					id = buchung->k_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_ARRANGEMENT	:
					id = buchung->arr_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_DIENST_TRAEGER	:
					dlg_id = MPAPIselectOneId((int)_DLG_PART, aktdet[i].dl_id, (char *)&dlg);
					dla_id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dlg.dla_id, (char *)&dla);
					id = dla.dlt_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case	(int)_AKTIONS_TYP	:
					id = (int)aktt->a_typ_id;
					recovery = setID(id, para[i].muss, ptr);
					break;

				case (int)_SPRACHEN:
					id = sprache;
					recovery = setID(id, para[i].muss, ptr);
					break;

				default:
					recovery = (int)MPERROR;
					break;
				}

			if (recovery != (int)FALSE)
				*recover_ptr = NULL;

			} /* end of for all parameters */

		if (status != MPOK)
			{
			UtilMsg(status, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}
	return(status);
}


static int setID(int id, int mussflag, char *ptr)
{
	int recovery = (int)FALSE;

	if (id < (int)1)
		recovery = (int)TRUE;
	else
		(void)sprintf(ptr, " %d", id);

	return(recovery);
}
