/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Kategorien in einem Kontingent
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONDinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int KONDinfo(char *buffer )
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern KONT_DETAIL k_d;
	extern KONTINGENT kon;
	extern HOST_KONT hkon;
	extern char sqlquery[];

	KAT_VIEW kategorie;
	KONT_DETAIL *Pkd;
	TTYP_VIEW dltt;
	DLT_VIEW dlt;
	char message[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[RECLAENGE];
	char tmp_bez[_RECORDLEN];
	char kontbez[_BEZLEN+1];
	char typbez[_RECORDLEN];
	int status=(int)MPOK;
	int i, id, anzahl, anzchar, last_id=(int)_UNDEF;

	/* init */
	k_d.hostkont_id = (int)_UNDEF;
	k_d.kont_id = (int)_UNDEF;

	/* set info to text */
	ACTIONTYP = INFOTXT;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kon.kont_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* HOST_KONT check FROM kontingent */
	if (*to_buffers[MKOND_HKON] != NULL)
		{
		k_d.hostkont_id = MPAPIselectEntry((int)_HOST_KONT, to_buffers[MKOND_HKON],
		                  (char *)&hkon, sizeof(HOST_KONT), sizeof(kon.hostkont_id));
		}

	/* KONTINGENT check kontingent */
	if (*to_buffers[MKOND_KON] != NULL)
		{
		k_d.kont_id = MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKOND_KON],
		                  (char *)&kon, sizeof(KONTINGENT), sizeof(kon.kont_id));
		}

	/* get info for HOST_KONT  OR  KONTINGENT */
	if (k_d.hostkont_id != (int)_UNDEF)
		{
		(void)strcpy(kontbez, to_buffers[MKOND_HKON]);
		(void)sprintf(sqlquery, _SELECT_KOND_HKON, k_d.hostkont_id);
		}
	else if (k_d.kont_id != (int)_UNDEF)
		{
		(void)strcpy(kontbez, to_buffers[MKOND_KON]);
		(void)sprintf(sqlquery, _SELECT_KOND_KON, k_d.kont_id);
		}
	else
		{
		UtilMsg((int)MPE_NOKON, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, sqlquery,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( anzahl > (int)0 )
		{
		Pkd = (KONT_DETAIL *)sqlmem.buffer;
		*buffer = NULL;
		anzchar=(int)_BEZLEN;
		(void)strcpy(buffer, kontbez);
		(void)strcat(buffer, "\n");
		for(i=0; i<anzchar; i++) strcat(buffer, "=");
			(void)strcat(buffer, "\n\n");

		for ( i=0; i<anzahl; i++ )
			{
			if (Pkd[i].kat_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_KAT_VIEW, (int)Pkd[i].kat_id,
				     (char *)&kategorie);
				(void)copyTextTo(tmp_bez, kategorie.bez, _BEZLEN);

				/*!!! hardcoded */
				(void)sprintf(tmp_buffer, "%s  mit %d Einheiten\n", tmp_bez, Pkd[i].anz);
				}
			else if (Pkd[i].dlt_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_DLT_VIEW, Pkd[i].dlt_id, (char *)&dlt);
				/* get dltt of host dlt */
				id = MPAPIselectOneId((int)_TTYP_VIEW, (int)dlt.typ_id, (char *)&dltt);
				if (id != (int)_UNDEF)
					{
					(void)copyTextTo(typbez, dltt.bez, (int)_BEZLEN);
					(void)strcat(typbez, ": ");
					}
				else
					typbez[0] = (char)NULL;

				(void)copyTextTo(tmp_bez, dlt.bez, _BEZLEN);
				(void)sprintf(tmp_buffer, "%s%s\n", typbez, tmp_bez);
				}
			else
				{
				(void)sprintf(tmp_buffer, "no detail !\n");
				}
			(void)strcat(buffer, tmp_buffer);
			}
		}
	else
		{
		/*!!! make new msg NOKOND */
		UtilMsg((int)MPE_NOKON, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
