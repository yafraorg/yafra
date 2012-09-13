/*D***********************************************************
 * Modul:     DBI - database info                           
 *            Kategorien in einem Kontingent
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONinfo.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

#define MSG1	(int)90
#define MSG2	(int)277

int KONinfo(char *buffer )
{
	extern MEMOBJ sqlmem;
	extern int sprache;

	KONTINGENT kon;
	KAT_VIEW kategorie;
	KONT_DETAIL *k_d;
	TTYP_VIEW dltt;
	DLT_VIEW dlt;
	char query[RECLAENGE];
	char message[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[RECLAENGE];
	int status=(int)MPOK;
	int i, anzahl, anzchar, last_id=(int)_UNDEF;

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
	UtilSplitFreeMenubuffer(to_buffers);



/**********
	if (*glob_bez_kon != NULL && (kon.kont_id=MPAPIselectEntry((int)_KONTINGENT, glob_bez_kon,
									(char *)&kon, sizeof(KONTINGENT), sizeof(kon.kont_id))) != (int)_UNDEF)
		{
		(void)sprintf(query, _SELECT_KON_DET, kon.kont_id);
		status=MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, query,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		if ( anzahl > (int)0 )
			{
			k_d = (KONT_DETAIL *)sqlmem.buffer;
			*buffer = NULL;
			anzchar=(int)strlen(glob_bez_kon);
			(void)strcpy(buffer, glob_bez_kon);
			(void)strcat(buffer, "\n");
			for(i=0; i<anzchar; i++) strcat(buffer, "=");
			(void)strcat(buffer, "\n\n");

			for ( i=0; i<anzahl; i++ )
			{
				if ( MPAPIselectOneId((int)_KAT_VIEW, (int)k_d[i].kat_id, (char *)&kategorie) == (int)_UNDEF )
					{
					(void)strcpy ( kategorie.bez, "          " );
					}
				if ( MPAPIselectOneId((int)_DLT_VIEW, k_d[i].dlt_id, (char *)&dlt) == (int)_UNDEF )
					{
					(void)strcpy ( dlt.bez, "          " );
					(void)sprintf(tmp_buffer, "%.30s %.30s %.30s : %3d\n", dltt.bez, kategorie.bez, dlt.bez, k_d[i].anz);
					(void)strcat(buffer, tmp_buffer);
					}
				else
					{
					(void)sprintf(tmp_buffer, "%.30s %.30s %.30s\n", dltt.bez, kategorie.bez, dlt.bez);
					(void)strcat(buffer, tmp_buffer);
					}
				}
			}
		else
			{
			(void)find_text_nr((int)MSG2, message);
			sprintf(buffer, message);
			}
		}
	else
		{
		(void)find_text_nr((int)MSG1, message);
		sprintf(buffer, message);
		}
**********************************/

	return(status);
}
