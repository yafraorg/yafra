/*D***********************************************************
 * Modul:     DBI - database info                           
 *            KOMM_DETAIL
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMDinfo.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

static int KOMDkom_info(char *kunbez, char *buffer);
static int KOMDdln_info(char *dlnbez, char *buffer);
static int KOMDkun_info(char *kunbez, char *buffer);
static int KOMDkol_info(char *kunbez, char *buffer);

int KOMDinfo(char *buffer )
{
	extern KOLLEKTIV kol;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	/* set info to text */
	ACTIONTYP = INFOTXT;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* make info for a kommission and
	   for a dln or kol or kun */

	if (*to_buffers[MKOMD_KOM] != NULL)
		status = KOMDkom_info(to_buffers[MKOMD_KOM], buffer);
	else if (*to_buffers[MKOMD_DLN] != NULL)
		status = KOMDdln_info(to_buffers[MKOMD_DLN], buffer);
	else if (*to_buffers[MKOMD_KUN] != NULL)
		status = KOMDkun_info(to_buffers[MKOMD_KUN], buffer);
	else if (*to_buffers[MKOMD_KOL] != NULL)
		status = KOMDkol_info(to_buffers[MKOMD_KOL], buffer);
	else
		{
		UtilSplitFreeMenubuffer(to_buffers);
		UtilMsg((int)MPE_NOINFO, MSGTYP_ERROR, NULL);
		return((int)MPWARNING);
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}

static int KOMDkom_info(char *kombez, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern KOMMISSION kom;
	extern KOLLEKTIV kol;

	KOMM_DETAIL *kd;
	int i, anzahl, anzchar, id;
	int status=(int)MPOK;
	int dlntit, kuntit, koltit;
	char tmp_buffer[_RECORDLEN];
	char tmp_buffer2[_RECORDLEN];

	/* init */
	dlntit = FALSE;
	kuntit = FALSE;
	koltit = FALSE;

	/* Kopfzeile */
	(void)strcpy(buffer, kombez);
	anzchar=(int)strlen(buffer);
	(void)strcat(buffer, "\n");
	for (i=0; i<anzchar; i++)
		strcat(buffer, "=");
	(void)strcat(buffer, "\n\n");

	/* lese noetige Daten */
	status = MPAPIselectEntry((int)_KOMMISSION, kombez,
	         (char *)&kom, sizeof(KOMMISSION), sizeof(kom.komm_id));
	if (status == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOKOMM, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(sqlquery, _SEL_KOMMDET_KOMM, kom.komm_id);
	status=MPAPIdb_sqlquery((int)_KOMM_DETAIL, &sqlmem.buffer, sqlquery,
	                        &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	kd = (KOMM_DETAIL *)sqlmem.buffer;

	/* Body */
	if (anzahl > 0)
		{
		for (i=0; i<anzahl; i++)
			{
			if (kd[i].dln_id != (int)_UNDEF)
				{
				if (dlntit == (int)FALSE)
					{
					(void)strcat(buffer, "REISENDER-KOMMISSIONEN:\n\n");
					dlntit = TRUE;
					}
				/* DLN/REISENDER  Kommission */
				id = DLNmkbez(kd[i].dln_id, tmp_buffer2, (int)_RECORDLEN);
				if (id == (int)MPOK)
					{
					(void)sprintf(tmp_buffer, "%40.40s / Buchung: %d", tmp_buffer2,
					              kd[i].bid);
					(void)strcat(buffer, tmp_buffer);
					}
				(void)strcat(buffer, "\n");
				}
			else if (kd[i].kun_id != (int)_UNDEF)
				{
				if (kuntit == (int)FALSE)
					{
					(void)strcat(buffer, "KUNDEN-KOMMISSIONEN:\n\n");
					kuntit = TRUE;
					}
				/* KUNDEN  Kommission */
				id = KUNmkbez(kd[i].kun_id, tmp_buffer, (int)_RECORDLEN);
				if (id == (int)MPOK)
					(void)strcat(buffer, tmp_buffer);
				(void)strcat(buffer, "\n");
				}
			else if (kd[i].kol_id != (int)_UNDEF)
				{
				if (koltit == (int)FALSE)
					{
					(void)strcat(buffer, "KOLLEKTIV-KOMMISSIONEN:\n\n");
					koltit = TRUE;
					}
				/* KOLLEKTIV  Kommission */
				id = MPAPIselectOneId((int)_KOLLEKTIV, kd[i].kol_id, (char *)&kol);
				if (id != (int)_UNDEF)
			      {
			      (void)copyTextTo(tmp_buffer, kol.name, (int)_BEZLEN);
					(void)strcat(buffer, tmp_buffer);
			      }
				(void)strcat(buffer, "\n");
				}
			else
				{
				(void)strcat(buffer, "\n\n! DEFINITIONSFEHLER !\n\n");
				}
			}
		}

	return(status);
}


static int KOMDdln_info(char *dlnbez, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern KOMMISSION kom;
	extern REISENDER rei;

	KOMM_DETAIL *kd;
	int i, anzahl, anzchar, id;
	int status=(int)MPOK;
	char tmp_buffer[_RECORDLEN];
	char tmp_buffer2[_RECORDLEN];

	/* Kopfzeile */
	(void)strcpy(buffer, dlnbez);
	anzchar=(int)strlen(buffer);
	(void)strcat(buffer, "\n");
	for (i=0; i<anzchar; i++)
		strcat(buffer, "=");
	(void)strcat(buffer, "\n\n");

	/* lese noetige Daten */
	status = MPAPIselectEntry((int)_REISENDER, dlnbez,
	         (char *)&rei, sizeof(REISENDER), sizeof(rei.pers_id));
	if (status == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(sqlquery, _SEL_KOMMDET_DLN, rei.pers_id);
	status=MPAPIdb_sqlquery((int)_KOMM_DETAIL, &sqlmem.buffer, sqlquery,
	                        &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK)
		return(status);
	kd = (KOMM_DETAIL *)sqlmem.buffer;

	/* Body */
	if (anzahl > 0)
		{
		for (i=0; i<anzahl; i++)
			{
			/* Kommission */
			id = MPAPIselectOneId((int)_KOMMISSION, kd[i].komm_id, (char *)&kom);
			if (id != (int)_UNDEF && SelectBez((int)_KOMMISSION, sprache,
				    kom.bez_id, tmp_buffer) != (int)_UNDEF)
				{
				(void)sprintf(tmp_buffer2, "%3.0d %s  /  Buchung: %d\n", kd[i].prio,
				              tmp_buffer, kd[i].bid);
				(void)strcat(buffer, tmp_buffer2);
				}
			}
		}

	return(status);
}


static int KOMDkun_info(char *kunbez, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern KOMMISSION kom;
	extern KUNDEN kun;

	KOMM_DETAIL *kd;
	int i, anzahl, anzchar, id;
	int status=(int)MPOK;
	char tmp_buffer[_RECORDLEN];
	char tmp_buffer2[_RECORDLEN];

	/* Kopfzeile */
	(void)strcpy(buffer, kunbez);
	anzchar=(int)strlen(buffer);
	(void)strcat(buffer, "\n");
	for (i=0; i<anzchar; i++)
		strcat(buffer, "=");
	(void)strcat(buffer, "\n\n");

	/* lese noetige Daten */
	status = MPAPIselectEntry((int)_KUNDEN, kunbez,
	         (char *)&kun, sizeof(KUNDEN), sizeof(kun.pers_id));
	if (status == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(sqlquery, _SEL_KOMMDET_KUN, kun.pers_id);
	status=MPAPIdb_sqlquery((int)_KOMM_DETAIL, &sqlmem.buffer, sqlquery,
	                        &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK)
		return(status);
	kd = (KOMM_DETAIL *)sqlmem.buffer;

	/* Body */
	if (anzahl > 0)
		{
		for (i=0; i<anzahl; i++)
			{
			/* Kommission */
			id = MPAPIselectOneId((int)_KOMMISSION, kd[i].komm_id, (char *)&kom);
			if (id != (int)_UNDEF && SelectBez((int)_KOMMISSION, sprache,
				    kom.bez_id, tmp_buffer) != (int)_UNDEF)
				{
				(void)sprintf(tmp_buffer2, "%3.0d %s\n", kd[i].prio, tmp_buffer);
				(void)strcat(buffer, tmp_buffer2);
				}
			}
		}

	return(status);
}



static int KOMDkol_info(char *kolbez, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern KOMMISSION kom;
	extern KOLLEKTIV kol;

	KOMM_DETAIL *kd;
	int i, anzahl, anzchar, id;
	int status=(int)MPOK;
	char tmp_buffer[_RECORDLEN];
	char tmp_buffer2[_RECORDLEN];

	/* Kopfzeile */
	(void)strcpy(buffer, kolbez);
	anzchar=(int)strlen(buffer);
	(void)strcat(buffer, "\n");
	for (i=0; i<anzchar; i++)
		strcat(buffer, "=");
	(void)strcat(buffer, "\n\n");

	/* lese noetige Daten */
	status = MPAPIselectEntry((int)_KOLLEKTIV, kolbez,
	         (char *)&kol, sizeof(KOLLEKTIV), sizeof(kol.k_id));
	if (status == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NODLN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)sprintf(sqlquery, _SEL_KOMMDET_KOL, kol.k_id);
	status=MPAPIdb_sqlquery((int)_KOMM_DETAIL, &sqlmem.buffer, sqlquery,
	                        &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK)
		return(status);
	kd = (KOMM_DETAIL *)sqlmem.buffer;

	/* Body */
	if (anzahl > 0)
		{
		for (i=0; i<anzahl; i++)
			{
			/* Kommission */
			id = MPAPIselectOneId((int)_KOMMISSION, kd[i].komm_id, (char *)&kom);
			if (id != (int)_UNDEF && SelectBez((int)_KOMMISSION, sprache,
				    kom.bez_id, tmp_buffer) != (int)_UNDEF)
				{
				(void)sprintf(buffer, "%3.0d %s\n", kd[i].prio, tmp_buffer);
				(void)strcat(tmp_buffer2, tmp_buffer2);
				}
			}
		}

	return(status);
}
