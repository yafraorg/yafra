/*D***********************************************************
 * Modul:     DBI - database insert/update/delete
 *            kopieren/bewegen von ganzen Arrangements
 *
 * Copyright: yafra.org, Basel, Switzerland
 * Autor:     Administrator
 **************************************************************/
#include <mpsqlsel.h>
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f?r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xARRcopy.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

int ARRcopymove(char *newdat, char *orgarr_bez)
{
	extern ARRANGEMENT arr;
	extern int sprache;
	extern char glob_bez_arr[];

	DIENSTLEISTUNG org_dl;
	DIENSTLEISTUNG dl;
	ARR_DLG *arr_dl = NULL;
	ARRANGEMENT newarr;
	ARRANGEMENT orgarr;
	BEZEICHNUNG newbez;
	int status=MPOK;
	int cret;
	int id;
	int i;
	int anzahl = 0;
	int newdl_dat;
	int ArrSavepoint;
	int datumsdiff = 0;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	char *buffer_ptr;
	char newdl_datstr[_RECORDLEN];
	char query[_QUERYLEN];
	struct tm DateTime;

	/* DELETE Modus hat keine Kopier/Bewegungs - Funktion */
	if (ACTIONTYP == MPDELETE)
		return(MPNOP);

	orgarr.arr_id = MPAPIselectEntry((int)_ARRANGEMENT, orgarr_bez,
		  (char *)&orgarr, sizeof(ARRANGEMENT), sizeof(orgarr.arr_id));
	if (orgarr.arr_id == _UNDEF)
		return(MPNOP);

	/* wandle neues Datum von String zu time_t um und berechne Differenz */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	(void)ReadDate(&DateTime, (time_t *)&newarr.a_dat, newdat);
	if (newarr.a_dat == orgarr.a_dat)
		return(MPNOP);  /* Datum hat nicht ge?ndert */
	datumsdiff = (newarr.a_dat - orgarr.a_dat);

	/* Neue ARR schreiben */
	status = MPAPIdb_setsavepoint(&ArrSavepoint);
	newarr.arr_id = _UNDEF;
	newarr.bez_id = orgarr.bez_id;
	newarr.textid = orgarr.textid;
	newarr.sai_id = orgarr.sai_id;
	newarr.prg_id = orgarr.prg_id;
	(void)copyTextTo(newarr.code, orgarr.code, (int)_CHAR256);
	newbez.s_id = (int)sprache;
	newbez.bez_id = SelectBez(_ARRANGEMENT, sprache, newarr.bez_id, newbez.bez);
	if (newbez.bez_id == (int)_UNDEF)
		return(MPNOP);
	newbez.typ = (int)_ARRANGEMENT;
	status = MPAPIinsertEntry(_ARRANGEMENT, (char *)&newarr, &newbez);
	if (status != MPOK)
		return(MPNOP);

	/* Alte DL lesen und neue DL schreiben */
	(void)sprintf(query, _SEL_ALL_DTG_ARR, orgarr.arr_id);
	status=MPAPIdb_sqlquery((int)_ARR_DLG, (char **)&arr_dl, query, &anzahl,
	                         &dlen, &alen);
	if (status != MPOK)
		{
		MPfree((char *)arr_dl);
		return(MPNOP);
		}
	for (i = 0; i < anzahl; i++)
		{
		id = MPAPIselectOneId(_DIENSTLEISTUNG, arr_dl[i].dlg_id, (char *)&dl);
		if (id != (int)_UNDEF)
			{
			if (dl.a_zeit > 0)
				{
				newdl_dat = dl.a_zeit + datumsdiff;
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_min  = (int)_UNDEF;
				DateTime.tm_hour = (int)_UNDEF;
				DateTime.tm_mday = (int)_UNDEF;
				DateTime.tm_mon  = (int)_UNDEF;
				DateTime.tm_year = (int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&newdl_dat, newdl_datstr);
				status = DLcopymove(&dl, newdl_datstr, (int)FALSE);
				if (status != MPOK)
					break;
				}
			arr_dl[i].dlg_id = dl.dlg_id;   /* setze jetzt neue DL ID      */
			arr_dl[i].arr_id = newarr.arr_id;  /* setze jetzt neue ARR ID */
			}
		else
			{
			status = (int)MPERROR;
			break;
			}
		}
	if (status == MPOK)
		{
		for (i = 0; i < anzahl; i++)
			{
			status = MPAPIinsertEntry(_ARR_DLG, (char *)&arr_dl[i], NULL);
			if (status != MPOK)
				break;
			}
		}

	if (MENUNR == (unsigned char)_ARRANGEMENT && status == MPOK)
		{
		(void)memcpy((void *)&arr, (void *)&newarr, sizeof(ARRANGEMENT));
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_min  = (int)0;
		DateTime.tm_hour = (int)0;
		DateTime.tm_mday = (int)_UNDEF;
		DateTime.tm_mon  = (int)_UNDEF;
		DateTime.tm_year = (int)_UNDEF;
		buffer_ptr = strstr(glob_bez_arr, TRENNER);
		if (buffer_ptr == NULL)
			buffer_ptr = glob_bez_arr;
		else
			buffer_ptr += (size_t)4;
		(void)WriteDate(&DateTime, (time_t *)&newarr.a_dat, buffer_ptr);
		(void)strcat(buffer_ptr, "\n");
		}

	/* Falls Fehler zur?ck zum savepoint */
	if (status != MPOK)
		cret = MPAPIdb_rollbacksavepoint(&ArrSavepoint);

	MPfree((char *)arr_dl);
	return(status);
}
