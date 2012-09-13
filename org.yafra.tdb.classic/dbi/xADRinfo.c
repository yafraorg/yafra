/*D***********************************************************
 * Modul:     DBI - database info                           
 *            show an address like on an envelope
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xADRinfo.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int ADRinfo(char *buffer )
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

	UtilSplitFreeMenubuffer(to_buffers);

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
				(void)copyTextTo(tmp_bez, dlt.bez, _BEZLEN);
				(void)sprintf(tmp_buffer, "%s\n", tmp_bez);
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

	return(status);
}
