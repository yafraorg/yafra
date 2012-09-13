/*D***********************************************************
 * Modul:     DBI - database select
 *            Dienstleistungstraeger
 *            prepare free DLT select list
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>
#ifdef ps_unix
#include <sys/time.h>
#endif

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTfree.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

static int CheckKONTDETAIL(int, int, int, int *);

#define _SEL_FREE_DLT_DAT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE DLG_ID IN (%s) AND DLT_ID = %d \
	AND (A_ZEIT <= %d AND E_ZEIT >= %d) \
	ORDER BY PERS_ID;"

#define _SEL_FREE_DLT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE DLG_ID IN (%s) AND DLT_ID = %d \
	ORDER BY PERS_ID;"

#define KONT_DLT_free  0
#define KONT_DLT_busy  1
#define KONT_DLT_error 2

/*************************************************************
 * function:  DLTfree
 * typ:       public
 * desc:      check if DLT is free for booking
 * input:     DL / DLG_PART / KAT / KONT
 *            DIENSTLEISTUNG DL_ID MUSS GESETZT SEIN !!!
 *            DLG_PARTS TDL_ID OPTIONAL !!!
 * output:    BCH with No of DLN or KONT
 *************************************************************/
int DLTfree(int dlt_id, int dl_id, int tdl_id, int kont_id,
            time_t dldate, int *countdln, int *bchid, int *kontid)
{
	extern MEMOBJ sqlmem;
	extern BUCHUNG bch;

	PERSONEN rechst;
	KONTINGENT tmpkon;
	DLG_PART tdl;

	DIENSTLEISTUNG *dl = NULL;
	RESERVATION *reservation = NULL;

	char query[_QUERYLEN];
	char tmp_buffer[_RECORDLEN];
	char dl_string[_RECORDLEN];
	int id;
	int status = (int)MPOK;
	int anzres, anzdlg;
	int i;
	int olddln = (int)_UNDEF;
	unsigned long dlen;
	unsigned long alen;
	time_t vondat, bisdat;

	/* init */
	*countdln = (int)0;
	*bchid = (int)_UNDEF;
	*kontid = (int)_UNDEF;

	/* check that at least one of them is set ! */
	if (dl_id == (int)_UNDEF && tdl_id == (int)_UNDEF)
		return(MPERROR);

	/* Alle Dienstleistungen die gefragt sind in buffer schreiben */
	if (dl_id == (int)_UNDEF)
		{
		/* Ist eine g�ltige aktive Dienstleistung vorhanden */
		/* Alle Teildienstleistungen der DIENSTLEISTUNG */
		id = MPAPIselectOneId((int)_DLG_PART, tdl_id, (char *)&tdl);
		if (id == (int)_UNDEF)
			return(MPERROR);
		if (tdl.h_dl_id != (int)_UNDEF)
			id = tdl.h_dl_id;
		else
			id = tdl.dl_id;
		alen = dlen = 0;
		(void)sprintf(query, _SEL_DL_HTDL, id, id);
		status=MPAPIdb_sqlquery((int)_DIENSTLEISTUNG, (char **)&dl,
		                         query, &anzdlg, &dlen, &alen);
		if (status != (int)MPOK)
			{
			MPfree((void *)dl);
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		for (i=0, *dl_string=(char)NULL; i < anzdlg; i++)
			{
			sprintf(tmp_buffer, "%d,", dl[i].dlg_id);
			strcat(dl_string, tmp_buffer);
			}
		dl_string[strlen( dl_string )-1] = NULL;
		MPfree((void *)dl);
		}
	else
		sprintf(dl_string, "%d", dl_id);

	/* Alle Reservationsdaten der Teildienstlesistungen aus der Datenbank lesen */
	if (dldate > 0)
		(void)sprintf(query, _SEL_FREE_DLT_DAT, dl_string, dlt_id,
		      (int)dldate, (int)dldate);
	else
		(void)sprintf(query, _SEL_FREE_DLT, dl_string, dlt_id);
	status = MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer, query,
	                           &anzres, &sqlmem.datalen, &sqlmem.alloclen);
	reservation = (RESERVATION *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL );
		return((int)MPERROR);
		}

	if (anzres < 1)
		{
		*countdln = 0;          /* DLT is free */
		*bchid = (int)_UNDEF;

		/* KONTINGENT case */
		status = CheckKONTDETAIL(kont_id, dl_id, dlt_id, kontid);
		if (status == (int)KONT_DLT_error)
			return((int)MPERROR);
		/* if busy then kontid is set ! */
		if (status == (int)KONT_DLT_busy)
			status = (int)MPOK;
		}
	else
		{
		for (i=0; i<anzres; i++)
			{
			if (tdl_id > 0)
				{
				if (reservation[i].dl_id < 1 || tdl_id == reservation[i].dl_id)
					{
					*bchid = reservation[0].bid;
					if (olddln != reservation[i].pers_id)
						{
						*countdln = *countdln + 1;
						olddln = reservation[i].pers_id;
						}
					}
				}
			else
				{
				*bchid = reservation[0].bid;
				if (olddln != reservation[i].pers_id)
					{
					*countdln = *countdln + 1;
					olddln = reservation[i].pers_id;
					}
				}
			}
		}

	return(status);
}


#define _SEL_KOND_DLORDLA "SELECT KD.* \
	FROM TDBADMIN.KONT_DETAIL KD, TDBADMIN.HOST_KONT HK, TDBADMIN.KONTINGENT K \
	WHERE (HK.DL_ID = %d OR (HK.DLA_ID = %d AND HK.DL_ID < 1)) \
	AND K.HOSTKONT_ID = HK.HOSTKONT_ID AND KD.KONT_ID = K.KONT_ID \
	AND KD.DLT_ID = %d ORDER BY KD.KONT_ID;"

#define _SEL_KOND_DLORDLA_KON "SELECT KD.* \
	FROM TDBADMIN.KONT_DETAIL KD \
	WHERE KD.KONT_ID = %d AND KD.DLT_ID = %d;"

static int CheckKONTDETAIL(int kont_id, int dl_id, int dlt_id, int *kontid)
{
	/* check KONTDETAIL if an entry is defined for dlt/kat */
	/* if busy make msg and set status to error */
	/* if exists not in KONT send question to confirm */
	/* else make nothing and set status to ok */

	extern int sprache;
	extern DIENST_ANGEBOT dla;
	extern char sqlquery[];

	DIENST_TRAEGER tmpdlt;
	KONTINGENT tmpkon;
	KONT_DETAIL *Pkond;
	MEMOBJ konmem;

	int status=(int)MPOK;
	int id1, i;
	int anzahl;

	char message[_RECORDLEN];
	char konbez[_RECORDLEN];
	char format[_RECORDLEN];
	char tmpquery[_QUERYLEN];

	/*--- Init values ---*/
	konmem.buffer = NULL;
	konmem.alloclen = 0;
	konmem.datalen = 0;

	/* set the right ANGEBOT */
	if (dl_id != (int)_UNDEF)
		status = MPAPIselectDLT((int)_UNDEF, (int)_UNDEF, dl_id, &tmpdlt);		
	else
		return((int)KONT_DLT_error);

/* dv damit bei zwei Kontingenten ueberpruft wird ob es das richtige ist

	if (kont_id != (int)_UNDEF)
		(void)sprintf(sqlquery, _SEL_KOND_DLORDLA_KON, kont_id, dlt_id);
	else
		(void)sprintf(sqlquery, _SEL_KOND_DLORDLA, dl_id, dla.dla_id, dlt_id);
*/

	(void)sprintf(sqlquery, _SEL_KOND_DLORDLA, dl_id, dla.dla_id, dlt_id);

	status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &konmem.buffer, sqlquery,
	       &anzahl, &konmem.datalen, &konmem.alloclen);
	if (status != (int)MPOK)
		{
		MPfree(konmem.buffer);
		UtilMsg(status, MSGTYP_DBERROR, NULL );
		return((int)KONT_DLT_error);
		}

	Pkond = (KONT_DETAIL *)konmem.buffer;
	if (kont_id == (int)_UNDEF || kont_id != Pkond[0].kont_id )
		{
		if (anzahl > 0)
			{
			*kontid = Pkond[0].kont_id;
			status = (int)KONT_DLT_busy;
			}
		else
			status = (int)KONT_DLT_free;
		}
	else
		{
		if (anzahl > 0)
			status = (int)KONT_DLT_free;
		else
			{
			/*--- DLT is not in the selected KONTINGENT ---*/
			(void)MPAPIselectOneId((int)_KONTINGENT, kont_id, (char *)&tmpkon);
			(void)SelectBez((int)_KONTINGENT, sprache, tmpkon.bez_id, konbez);
			UtilMsgGet((int)MPE_DLTNOTINKON, MSGTYP_ERROR, format);
			sprintf(message, format, konbez);
			status = UtilImmediatCall(message);
			if (status == (int)TRUE)
				status = (int)MPOK;
			else
				return((int)KONT_DLT_error);
			}
		}

	MPfree(konmem.buffer);

	return(status);
}
